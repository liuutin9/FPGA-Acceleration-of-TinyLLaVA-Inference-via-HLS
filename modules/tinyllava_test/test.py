import torch
from transformers import AutoTokenizer, AutoModelForCausalLM
import requests
from PIL import Image
from io import BytesIO
import numpy as np

def load_image(image_file):
    if image_file.startswith("http") or image_file.startswith("https"):
        response = requests.get(image_file)
        image = Image.open(BytesIO(response.content)).convert("RGB")
    else:
        image = Image.open(image_file).convert("RGB")
    return image

def process_images(images, image_processor, model_cfg):
    return image_processor(images, return_tensors='pt')['pixel_values']

def tokenizer_image_token(prompt, tokenizer, image_token_index, return_tensors=None):
    prompt_chunks = [tokenizer(chunk).input_ids for chunk in prompt.split('<image>')]

    def insert_separator(X, sep):
        return [ele for sublist in zip(X, [sep]*len(X)) for ele in sublist][:-1]

    input_ids = []
    offset = 0
    if len(prompt_chunks) > 0 and len(prompt_chunks[0]) > 0 and prompt_chunks[0][0] == tokenizer.bos_token_id:
        offset = 1
        input_ids.append(prompt_chunks[0][0])

    for x in insert_separator(prompt_chunks, [image_token_index] * (offset + 1)):
        input_ids.extend(x[offset:])

    if return_tensors is not None:
        if return_tensors == 'pt':
            return torch.tensor(input_ids, dtype=torch.long)
        raise ValueError(f'Unsupported tensor type: {return_tensors}')
    return input_ids

# Loading model
model = AutoModelForCausalLM.from_pretrained("tinyllava/TinyLLaVA-Phi-2-SigLIP-3.1B", trust_remote_code=True)
tokenizer = AutoTokenizer.from_pretrained("tinyllava/TinyLLaVA-Phi-2-SigLIP-3.1B")
model.cuda()
config = model.config
prompt="What are these?"
image = "../../test.jpg"
f = open("test_output.txt", "w")

# TinyLlavaForConditionalGeneration.chat
image = load_image(image)
image_tensor = process_images(image, model.vision_tower._image_processor, model.config).to(model.device)
prompt = "A chat between a curious user and an artificial intelligence assistant. " + "The assistant gives helpful, detailed, and polite answers to the user's questions." + " USER" + ": " + "<image>" + '\n' + prompt + " ASSISTANT:"
print(f"=====TinyLlavaForConditionalGeneration.chat====", file=f)
print(f"-   prompt:\n{prompt}", file=f)
input_ids = (tokenizer_image_token(prompt, tokenizer, -200, return_tensors="pt").unsqueeze(0).to(model.device))
print(f"-   input_ids:\n{input_ids[0].tolist()}", file=f)

# TinyLlavaForConditionalGeneration.generate
# (inputs, position_ids, attention_mask, _, inputs_embeds, _) = model.prepare_inputs_labels_for_multimodal(input_ids, None, None, None, None, image_tensor, image_sizes=None)
# ...

# TinyLlavaForConditionalGeneration.prepare_inputs_labels_for_multimodal
image_features = model.encode_images(image_tensor)
print(f"\n=====TinyLlavaForConditionalGeneration.prepare_inputs_labels_for_multimodal====", file=f)
print(f"-   image_features:{image_features[0].shape}", file=f)
input_ids = [cur_input_ids for cur_input_ids in input_ids] # tensor => list of tensor
## !!!以下假設batch=1且只有一張image!!!
batch_idx = 0
cur_image_idx = 0
cur_input_ids = input_ids[batch_idx]
## 以image_token分割input_ids，將純文字片段合併做text embedding
image_token_pos = torch.where(cur_input_ids == -200)[0]
split_sizes = [image_token_pos, cur_input_ids.shape[0] - image_token_pos - 1]
cur_input_ids_noim = [cur_input_ids[0:image_token_pos], cur_input_ids[image_token_pos+1:cur_input_ids.shape[0]]]
cur_input_embeds = model.language_model.get_input_embeddings()(torch.cat(cur_input_ids_noim))
## 合併image embedding與兩段text embedding
cur_input_embeds_no_im = torch.split(cur_input_embeds, split_sizes, dim=0) # (tensor[32,2560], tensor[9,2560])
print(f"-   text_embedding: {cur_input_embeds_no_im[0].shape}, {cur_input_embeds_no_im[1].shape}", file=f)
cur_new_input_embeds = [cur_input_embeds_no_im[0], image_features[cur_image_idx], cur_input_embeds_no_im[1]] # [tensor[32,2560], tensor[728,2560], tensor[9,2560]]
cur_new_input_embeds = [x.to(model.device) for x in cur_new_input_embeds]
cur_new_input_embeds = torch.cat(cur_new_input_embeds)
print(f"-   input_embeds: {cur_new_input_embeds.shape}", file=f)
# Truncate sequences to max length as image embeddings can make the sequence longer
tokenizer_model_max_length = 3072
new_input_embeds = [cur_new_input_embeds[:tokenizer_model_max_length]] #batch
print(f"-   truncated_input_embeds: {new_input_embeds[0].shape}", file=f)

prepare_inputs_labels_for_multimodal_output = new_input_embeds[0].detach().cpu().numpy().reshape(-1)
np.savetxt(f"./test_output/prepare_inputs_labels_for_multimodal_output.txt", prepare_inputs_labels_for_multimodal_output)

f.close()
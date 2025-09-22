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
def process_images(images, image_processor):
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
image = "test.jpg"

# TinyLlavaForConditionalGeneration.chat
image = load_image(image)
image_tensor = process_images(image, model.vision_tower._image_processor).to(model.device)
prompt = "A chat between a curious user and an artificial intelligence assistant. " + "The assistant gives helpful, detailed, and polite answers to the user's questions." + " USER" + ": " + "<image>" + '\n' + prompt + " ASSISTANT:"
input_ids = (tokenizer_image_token(prompt, tokenizer, -200, return_tensors="pt").unsqueeze(0).to(model.device))

# TinyLlavaForConditionalGeneration.generate
(_, _, _, _, inputs_embeds, _) = model.prepare_inputs_labels_for_multimodal(input_ids, None, None, None, None, image_tensor, image_sizes=None)
phi_input = inputs_embeds[0].detach().cpu().numpy().reshape(-1)
np.savetxt(f"./output/phi_input.txt", phi_input)

output_ids = model.language_model.generate(position_ids=None, attention_mask=None, inputs_embeds=inputs_embeds, do_sample=False, temperature=0, top_p=None, num_beams=1, pad_token_id=tokenizer.pad_token_id, max_new_tokens=512, use_cache=True)
np.savetxt(f"./output/test1_output_ids.txt", output_ids.detach().cpu().numpy().reshape(-1))
outputs = tokenizer.batch_decode(output_ids, skip_special_tokens=True)[0]
outputs = outputs.strip()
np.savetxt("./output/test1.txt", np.array([outputs]), fmt="%s")
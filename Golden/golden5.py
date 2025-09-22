import torch
from transformers import AutoTokenizer, AutoModelForCausalLM
import requests
from PIL import Image
from io import BytesIO
import numpy as np
from transformers.cache_utils import Cache, DynamicCache
from transformers.masking_utils import create_causal_mask

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
np.savetxt(f"./output/golden5_input_ids.txt", input_ids[0].tolist())

# TinyLlavaForConditionalGeneration.generate
(_, _, _, _, inputs_embeds, _) = model.prepare_inputs_labels_for_multimodal(input_ids, None, None, None, None, image_tensor, image_sizes=None)
phi_input = inputs_embeds[0].detach().cpu().numpy().reshape(-1)
np.savetxt(f"./output/golden5_phi_input.txt", phi_input)

# PhiForCausalLM.generate
output_tokens = list()
past_key_values = DynamicCache()
eos_token_id = 50256

for i in range(5):
    # PhiModel.forward
    past_seen_tokens = past_key_values.get_seq_length() if past_key_values is not None else 0
    cache_position = torch.arange(past_seen_tokens, past_seen_tokens + inputs_embeds.shape[1], device=inputs_embeds.device)
    position_ids = cache_position.unsqueeze(0)
    hidden_states = model.language_model.model.embed_dropout(inputs_embeds) # diff with Llama
    position_embeddings = model.language_model.model.rotary_emb(hidden_states, position_ids)
    
    for decoder_layer in model.language_model.model.layers[: model.language_model.model.config.num_hidden_layers]:
        layer_outputs = decoder_layer(
            hidden_states,
            position_ids=position_ids,
            past_key_value=past_key_values,
            use_cache=True,
            cache_position=cache_position,
            position_embeddings=position_embeddings,
        )
        hidden_states = layer_outputs[0]
    
    hidden_states = model.language_model.model.final_layernorm(hidden_states)  # diff with Llama
    logits = model.language_model.lm_head(hidden_states)
    
    # greedy_search
    next_token = logits.argmax(-1)[:, -1:]
    token_id = next_token.detach().cpu().numpy()[0][0]
    output_tokens.append(token_id)
    print(f"token_id {i}: {token_id}")

    if token_id == eos_token_id: break

    # prepare for next round
    inputs_embeds = model.language_model.get_input_embeddings()(next_token.squeeze()).unsqueeze(0).unsqueeze(0)

np.savetxt(f"./output/golden5_output_ids.txt", output_tokens)
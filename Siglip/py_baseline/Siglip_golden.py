import torch
import time
from transformers import AutoModelForCausalLM
from PIL import Image

def load_image(image_file):
    image = Image.open(image_file).convert("RGB")
    return image

def process_images(images, image_processor):
    image_tensor = image_processor(images, return_tensors='pt')['pixel_values']
    return image_tensor

def encode_images(images):
    images = images.to(device=model.device, dtype=model.dtype)
    image_features = vision_tower(images)
    image_features = model.connector(image_features)
    return image_features

def vision_tower(images):
    image_features = SiglipVisionModel(images)
    # image_features = image_features.hidden_states[-2] => Simply skip the final step in SiglipVisionModel
    image_features = image_features[:, 1:]
    return image_features

def SiglipVisionModel(pixel_values):
    return SiglipVisionTransformer(pixel_values)

def SiglipVisionTransformer(pixel_values):
    hidden_states = model.vision_tower._vision_tower.vision_model.embeddings(pixel_values, interpolate_pos_encoding=False)
    encoder_outputs = SiglipEncoder(hidden_states)
    return encoder_outputs

def SiglipEncoder(inputs_embeds):
    hidden_states = inputs_embeds
    for layer_id in range(26): # skip the final step
        print(f"--- layer {layer_id} ---")
        layer_outputs = SiglipEncoderLayer(hidden_states, layer_id)
        hidden_states = layer_outputs[0] # [729, 1152]
    return hidden_states

def SiglipEncoderLayer(hidden_states, layer_id):
    residual = hidden_states 
    hidden_states = model.vision_tower._vision_tower.vision_model.encoder.layers[layer_id].layer_norm1(hidden_states)
    hidden_states = SiglipAttention(hidden_states, layer_id)
    hidden_states = residual + hidden_states
    residual = hidden_states
    hidden_states = model.vision_tower._vision_tower.vision_model.encoder.layers[layer_id].layer_norm2(hidden_states) 
    hidden_states = model.vision_tower._vision_tower.vision_model.encoder.layers[layer_id].mlp(hidden_states)
    hidden_states = residual + hidden_states
    return (hidden_states, )

def SiglipAttention(hidden_states, layer_id):
    batch_size, seq_length, embed_dim = hidden_states.shape
    num_heads = model.vision_tower._vision_tower.vision_model.encoder.layers[layer_id].self_attn.num_heads
    head_dim = model.vision_tower._vision_tower.vision_model.encoder.layers[layer_id].self_attn.head_dim
    
    queries = model.vision_tower._vision_tower.vision_model.encoder.layers[layer_id].self_attn.q_proj(hidden_states)
    queries = queries.view(batch_size, seq_length, num_heads, head_dim).transpose(1, 2)
    keys = model.vision_tower._vision_tower.vision_model.encoder.layers[layer_id].self_attn.k_proj(hidden_states)
    keys = keys.view(batch_size, seq_length, num_heads, head_dim).transpose(1, 2)
    values = model.vision_tower._vision_tower.vision_model.encoder.layers[layer_id].self_attn.v_proj(hidden_states)
    values = values.view(batch_size, seq_length, num_heads, head_dim).transpose(1, 2)
    
    attn_output = attention_forward(queries, keys, values, layer_id)                  # output shape = [1, 16, 729, 72]
    attn_output = attn_output.transpose(1, 2).contiguous()                            # output shape = [1, 729, 16, 72]
    attn_output = attn_output.reshape(batch_size, seq_length, embed_dim).contiguous() # output shape = [1, 729, 1152]
    attn_output = model.vision_tower._vision_tower.vision_model.encoder.layers[layer_id].self_attn.out_proj(attn_output) # output shape = [1, 729, 1152]
    return attn_output

def attention_forward(query, key, value, layer_id):
    attn_weights = torch.matmul(query, key.transpose(-2, -1)) * model.vision_tower._vision_tower.vision_model.encoder.layers[layer_id].self_attn.scale
    attn_weights = torch.softmax(attn_weights, dim=-1)
    attn_output = torch.matmul(attn_weights, value)
    return attn_output

f = open("./golden_output.txt", "w")
hf_path = 'tinyllava/TinyLLaVA-Phi-2-SigLIP-3.1B'
model = AutoModelForCausalLM.from_pretrained(hf_path, trust_remote_code=True)
model.cuda()
device = torch.device("cpu")
model.to(device, dtype=torch.float32)
prompt = "What are these?"
image = "./test.jpg"

image = load_image(image)
image_tensor = process_images(image, model.vision_tower._image_processor).to(model.device)
s_time = time.time()
image_features = encode_images(image_tensor)
print(f"Total encoding time: {time.time() - s_time} seconds", file=f)
image_features_np = image_features.detach().cpu().numpy()  
image_features_np.tofile("./encoded_output.bin")
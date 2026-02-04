import torch
import numpy as np
from transformers import AutoTokenizer
import os
import time

hf_path = 'tinyllava/TinyLLaVA-Phi-2-SigLIP-3.1B'
tokenizer = AutoTokenizer.from_pretrained(hf_path, use_fast=False, model_max_length = 3072, padding_side = "right")

prompt = "def bubble_sort"

inputs = tokenizer(prompt)

token_ids = inputs['input_ids']
print(f"Input:\n{prompt}")
print("Input length:", len(token_ids))
print(token_ids)

class NewGELU(torch.nn.Module):
    def forward(self, x):
        x_float = x.to(torch.float32)
        x_cube = x_float * x_float * x_float
        M_SQRT2 = 1.41421356237309504880
        M_2_SQRTPI = 1.12837916709551257390
        kGeluBeta = M_SQRT2 * M_2_SQRTPI * 0.5
        kGeluKappa = 0.044715
        inner = kGeluBeta * (x_float + kGeluKappa * x_cube)
        return (0.5 * x_float * (1.0 + torch.tanh(inner))).to(x.dtype)

HIDDEN_SIZE = 2560
VOCAB_SIZE = 51200

embeddings = np.fromfile("/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_embed_tokens_weight.bin", dtype=np.float16).astype(np.float32)
embeddings = embeddings.reshape(VOCAB_SIZE, HIDDEN_SIZE)

embeddings = torch.from_numpy(embeddings)

eos_id = 50256

pre_layernorm = [torch.nn.LayerNorm(HIDDEN_SIZE, eps=0.00001, dtype=torch.float16) for _ in range(32)]
q_proj = [torch.nn.Linear(HIDDEN_SIZE, HIDDEN_SIZE, dtype=torch.float16) for _ in range(32)]
k_proj = [torch.nn.Linear(HIDDEN_SIZE, HIDDEN_SIZE, dtype=torch.float16) for _ in range(32)]
v_proj = [torch.nn.Linear(HIDDEN_SIZE, HIDDEN_SIZE, dtype=torch.float16) for _ in range(32)]
dense = [torch.nn.Linear(HIDDEN_SIZE, HIDDEN_SIZE, dtype=torch.float16) for _ in range(32)]
mlp_fc1 = [torch.nn.Linear(HIDDEN_SIZE, 4 * HIDDEN_SIZE, dtype=torch.float16) for _ in range(32)]
mlp_fc2 = [torch.nn.Linear(4 * HIDDEN_SIZE, HIDDEN_SIZE, dtype=torch.float16) for _ in range(32)]
mlp_activation = NewGELU()
final_layernorm = torch.nn.LayerNorm(HIDDEN_SIZE, eps=0.00001, dtype=torch.float16)
lm_head = torch.nn.Linear(HIDDEN_SIZE, VOCAB_SIZE, dtype=torch.float16)

k_cache = [None for _ in range(32)]
v_cache = [None for _ in range(32)]

cosine = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/cosine.bin", dtype=np.float16)).to(torch.float32)
sine = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/sine.bin", dtype=np.float16)).to(torch.float32)

final_layernorm.weight.data = torch.from_numpy(np.fromfile("/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_final_layernorm_weight.bin", dtype=np.float16)).to(torch.float32)
final_layernorm.bias.data = torch.from_numpy(np.fromfile("/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_final_layernorm_bias.bin", dtype=np.float16)).to(torch.float32)

lm_head.weight.data = torch.from_numpy(np.fromfile("/home/undergraduate/ytliu24/phi_workspace/weights/language_model_lm_head_weight.bin", dtype=np.float16)).to(torch.float32).reshape(VOCAB_SIZE, HIDDEN_SIZE)
lm_head.bias.data = torch.from_numpy(np.fromfile("/home/undergraduate/ytliu24/phi_workspace/weights/language_model_lm_head_bias.bin", dtype=np.float16)).to(torch.float32)

for layer in range(32):
    pre_layernorm[layer].weight.data = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_{layer}_input_layernorm_weight.bin", dtype=np.float16)).to(torch.float32)
    pre_layernorm[layer].bias.data = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_{layer}_input_layernorm_bias.bin", dtype=np.float16)).to(torch.float32)
    q_proj[layer].weight.data = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_{layer}_self_attn_q_proj_weight.bin", dtype=np.float16)).to(torch.float32).reshape(HIDDEN_SIZE, HIDDEN_SIZE)
    q_proj[layer].bias.data = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_{layer}_self_attn_q_proj_bias.bin", dtype=np.float16)).to(torch.float32)
    k_proj[layer].weight.data = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_{layer}_self_attn_k_proj_weight.bin", dtype=np.float16)).to(torch.float32).reshape(HIDDEN_SIZE, HIDDEN_SIZE)
    k_proj[layer].bias.data = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_{layer}_self_attn_k_proj_bias.bin", dtype=np.float16)).to(torch.float32)
    v_proj[layer].weight.data = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_{layer}_self_attn_v_proj_weight.bin", dtype=np.float16)).to(torch.float32).reshape(HIDDEN_SIZE, HIDDEN_SIZE)
    v_proj[layer].bias.data = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_{layer}_self_attn_v_proj_bias.bin", dtype=np.float16)).to(torch.float32)
    dense[layer].weight.data = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_{layer}_self_attn_dense_weight.bin", dtype=np.float16)).to(torch.float32).reshape(HIDDEN_SIZE, HIDDEN_SIZE)
    dense[layer].bias.data = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_{layer}_self_attn_dense_bias.bin", dtype=np.float16)).to(torch.float32)
    mlp_fc1[layer].weight.data = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_{layer}_mlp_fc1_weight.bin", dtype=np.float16)).to(torch.float32).reshape(4 * HIDDEN_SIZE, HIDDEN_SIZE)
    mlp_fc1[layer].bias.data = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_{layer}_mlp_fc1_bias.bin", dtype=np.float16)).to(torch.float32)
    mlp_fc2[layer].weight.data = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_{layer}_mlp_fc2_weight.bin", dtype=np.float16)).to(torch.float32).reshape(HIDDEN_SIZE, 4 * HIDDEN_SIZE)
    mlp_fc2[layer].bias.data = torch.from_numpy(np.fromfile(f"/home/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_{layer}_mlp_fc2_bias.bin", dtype=np.float16)).to(torch.float32)


input_length = len(token_ids)

start = time.time()

for i in range(832):
    if token_ids[i] == eos_id:
        break
    
    hidden_state = embeddings[token_ids[i]]

    for layer in range(32):
        residual = hidden_state.clone()
        
        hidden_state = pre_layernorm[layer](hidden_state)
        
        q = q_proj[layer](hidden_state)
        k = k_proj[layer](hidden_state)
        v = v_proj[layer](hidden_state)

        q_embed = q.clone()
        k_embed = k.clone()

        for j in range(32):
            for z in range(16):
                q_embed[j * 80 + z]      = q[j * 80 + z]      * cosine[i * 16 + z] - q[j * 80 + z + 16] * sine[i * 16 + z]
                q_embed[j * 80 + z + 16] = q[j * 80 + z + 16] * cosine[i * 16 + z] + q[j * 80 + z]      * sine[i * 16 + z]
                k_embed[j * 80 + z]      = k[j * 80 + z]      * cosine[i * 16 + z] - k[j * 80 + z + 16] * sine[i * 16 + z]
                k_embed[j * 80 + z + 16] = k[j * 80 + z + 16] * cosine[i * 16 + z] + k[j * 80 + z]      * sine[i * 16 + z]

        if k_cache[layer] is None and v_cache[layer] is None:
            k_cache[layer] = k_embed.unsqueeze(0)
            v_cache[layer] = v.unsqueeze(0)
        else:
            k_cache[layer] = torch.cat((k_cache[layer], k_embed.unsqueeze(0)), dim=0)
            v_cache[layer] = torch.cat((v_cache[layer], v.unsqueeze(0)), dim=0)
            
        attn_out = torch.zeros_like(hidden_state)
        
        for j in range(32):
            q_head = q_embed[j * 80 : (j + 1) * 80]
            k_head = k_cache[layer][:, j * 80 : (j + 1) * 80]
            v_head = v_cache[layer][:, j * 80 : (j + 1) * 80]
            qkt = torch.matmul(q_head, k_head.T) * (80 ** -0.5)
            attn_weights = torch.nn.functional.softmax(qkt, dim=0)
            attn_output_head = torch.matmul(attn_weights, v_head)
            attn_out[j * 80 : (j + 1) * 80] = attn_output_head
        
        dense_out = dense[layer](attn_out)
        
        mlp_fc1_state = mlp_fc1[layer](hidden_state)
        mlp_gelu_state = mlp_activation(mlp_fc1_state)
        mlp_fc2_state = mlp_fc2[layer](mlp_gelu_state)
        
        hidden_state = residual + dense_out + mlp_fc2_state
    
    if i < input_length - 1: continue

    hidden_state = final_layernorm(hidden_state)

    logits = lm_head(hidden_state)
    predicted_id = torch.argmax(logits).item()
    
    token_ids.append(predicted_id)
    
end = time.time()
print(f"Elapsed time: {end - start:.6f} seconds")
print(f"Elapsed time: {(end - start)/len(token_ids):.6f} seconds/token")
output_text = tokenizer.decode(token_ids, skip_special_tokens=True)
print("Output Text:")
print(output_text)
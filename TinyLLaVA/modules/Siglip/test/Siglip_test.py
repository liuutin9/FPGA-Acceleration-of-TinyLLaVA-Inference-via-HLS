from torch import float16
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

hf_path = 'tinyllava/TinyLLaVA-Phi-2-SigLIP-3.1B'
model = AutoModelForCausalLM.from_pretrained(hf_path, trust_remote_code=True)
model.cuda()
config = model.config
prompt="What are these?"
# image="http://images.cocodataset.org/test-stuff2017/000000000001.jpg"
image = "../../../test.jpg"

image_processor = model.vision_tower._image_processor
image = load_image(image)
image_tensor = process_images(image, image_processor, model.config).to(model.device)

print(f" - preprocessed image: {list(image_tensor.shape)}")
print(f"{image_tensor[0, 0, 0, :5].tolist()}\n") 
image_tensor = image_tensor.to(torch.float32).cpu() # for C++ test data
image_np = image_tensor.numpy()                     # for C++ test data
image_np.tofile("image_tensor.bin")                 # for C++ test data
# image_features = model.encode_images(image_tensor)

### model.encode_images ###
kwargs = {}
kwargs['vision_feature_layer'] = model.config.vision_feature_layer
kwargs['vision_feature_select_strategy'] = model.config.vision_feature_select_strategy
images = image_tensor.to(device=model.device, dtype=model.dtype)
# image_features = model.vision_tower(images, **kwargs)
# image_features = model.connector(image_features)

### VisionTower forward ###
# image_features = model._vision_tower(images, output_hidden_states=True)
# image_features = image_features.hidden_states[kwargs.get('vision_feature_layer', -2)]
# image_features = image_features[:, 1:]

### VisionTower Transformer forward ###
# hidden_states = model.vision_tower._vision_tower.vision_model.embeddings(images, interpolate_pos_encoding=False)
# print(f"Hidden states shape: {hidden_states.shape}")
# print(f"First ten output values: {hidden_states[0, 0, :10]}")

### VisionTower Embedding forward ###
target_dtype = model.vision_tower._vision_tower.vision_model.embeddings.patch_embedding.weight.dtype
patch_embeds = model.vision_tower._vision_tower.vision_model.embeddings.patch_embedding(images.to(dtype=target_dtype))
print(f" - patch_embeds: {list(patch_embeds.shape)}")
print(f"{patch_embeds[0, 0, 0, :5].tolist()}\n")
patch_embeds_out = patch_embeds.detach().cpu().numpy().reshape(-1)  # 確保攤平成 1D
print("Python shape:", patch_embeds_out.shape)
np.savetxt(f"./test_output/py/Siglip_patch_embeds_py_output.txt", patch_embeds_out, fmt="%.8e")

embeddings = patch_embeds.flatten(2).transpose(1, 2)
print(f" - flatten_patched_pixel_values: {list(embeddings.shape)}")
print(f"{embeddings[0, 0, :5].tolist()}\n")
embeddings_out = embeddings.detach().cpu().numpy().reshape(-1)  # 確保攤平成 1D
print("Python shape:", embeddings_out.shape)
np.savetxt(f"./test_output/py/Siglip_embedding_py_output.txt", embeddings_out, fmt="%.8e")

position_embeddings = embeddings + model.vision_tower._vision_tower.vision_model.embeddings.position_embedding(model.vision_tower._vision_tower.vision_model.embeddings.position_ids)
print(f" - embedded_vector: {list(embeddings.shape)}")
print(f"{embeddings[0, 0, :5].tolist()}\n")
position_embedding_out = position_embeddings.detach().cpu().numpy().reshape(-1)  # 確保攤平成 1D
print("Python shape:", position_embedding_out.shape)
np.savetxt(f"./test_output/py/Siglip_position_embedding_out_py_output.txt", position_embedding_out, fmt="%.8e")

# output = []
# hidden_states = embeddings
# for i, encoder_layer in enumerate(model.vision_tower._vision_tower.vision_model.encoder.layers):
#     layer_outputs = encoder_layer(
#         hidden_states,
#         None,
#         None,
#     )
#     hidden_states = layer_outputs[0]
#     layer_out = hidden_states.detach().cpu().numpy().reshape(-1)  # 確保攤平成 1D
#     print("Python shape:", layer_out.shape)
#     np.savetxt(f"./test_output/py/Siglip_{i}_EncoderLayer_py_output.txt", layer_out, fmt="%.8e")
#     output.append(hidden_states)
#     print(f" - layer{i}_outputs: {list(hidden_states.shape)}")
#     print(f"{hidden_states[0, 0, :10].tolist()}\n")

# image_features = output[-2]

# py_out = model.connector(image_features)

# py_out = py_out.detach().cpu().numpy().reshape(-1)  # 確保攤平成 1D
# print("Python shape:", py_out.shape)
# np.savetxt("./test_output/py/connector_py_output.txt", py_out, fmt="%.8e")

# import numpy as np

# cpp_out = np.loadtxt("siglip_cpp_output.txt", dtype=np.float32)
# py_out = np.loadtxt("siglip_py_output.txt", dtype=np.float32)
# print("C++ shape:", cpp_out.shape)


# assert cpp_out.shape == py_out.shape, "Shape mismatch!"

# diff = cpp_out - py_out
# mae = np.mean(np.abs(diff))
# mse = np.mean(diff**2)
# max_err = np.max(np.abs(diff))

# print(f"MAE: {mae}")
# print(f"MSE: {mse}")
# print(f"Max Error: {max_err}")

# threshold = 100
# indices = np.where(np.abs(diff) > threshold)[0]
# print(f"誤差大於 {threshold} 的位置有 {len(indices)} 個")
# for i in indices:
#     print(f"Index {i}: cpp={cpp_out[i]}, py={py_out[i]}, diff={diff[i]}")

# # image_features = model.vision_tower(images, **kwargs)
# # # image_features = model.connector(image_features)

# # print(f" - image_features: {list(image_features.shape)}")
# # print(f"{image_features[0, 0, :10].tolist()}\n")
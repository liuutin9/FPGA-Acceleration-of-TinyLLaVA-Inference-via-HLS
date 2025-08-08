from transformers import SiglipImageProcessor
from transformers.image_processing_utils import rescale, normalize
import requests
from PIL import Image
from io import BytesIO
import numpy as np
import cv2

# config
image_mean = [0.5, 0.5, 0.5]
image_std = [0.5, 0.5, 0.5]
resample = 3
rescale_factor = 0.00392156862745098
(height, width) = (384, 384)

# Option1: load image from URL
# image_url = "http://images.cocodataset.org/test-stuff2017/000000000001.jpg"
# response = requests.get(image_url)
# image = Image.open(BytesIO(response.content)).convert("RGB")
# print(f"image size: {image.size}, first pixel value: {image.getpixel((0, 0))}")

# Option2: load image from local file
# image = Image.open("test.jpg").convert("RGB")
# print(f"before shape: ({image.width}, {image.height}, 3), first pixel value: {image.getpixel((0, 0))}")

# SiglipImageProcessor
print("***SiglipImageProcessor***")
cv_img = cv2.imread("test.jpg", cv2.IMREAD_COLOR)
cv_img_rgb = cv2.cvtColor(cv_img, cv2.COLOR_BGR2RGB)
image = Image.fromarray(cv_img_rgb)
print(f"Before preprocess shape: ({image.height}, {image.width}, 3), first pixel value: {image.getpixel((0, 0))}")
processor = SiglipImageProcessor.from_pretrained("google/siglip-so400m-patch14-384")
image = processor(images=[image], return_tensors='pt')['pixel_values']
print(f"After preprocess shape: {image.shape}, first pixel value: {image[0][0][0][0]}, {image[0][1][0][0]}, {image[0][2][0][0]}\n")
image.squeeze(0).numpy().tofile("preprocessed_SiglipImageProcessor.bin")

# Implementation of SiglipImageProcessor (without batch dimension)
print("***Implementation of SiglipImageProcessor (without batch dimension)***")
cv_img = cv2.imread("test.jpg", cv2.IMREAD_COLOR)
cv_img_rgb = cv2.cvtColor(cv_img, cv2.COLOR_BGR2RGB)
image = Image.fromarray(cv_img_rgb)
print(f"Before preprocess shape: ({image.height}, {image.width}, 3), first pixel value: {image.getpixel((0, 0))}")
image = image.resize(size=(width, height), resample=resample)
image = np.array(image)
print(f"Resized shape: {image.shape}, first pixel value: {image[0][0]}")
image = rescale(image, scale=rescale_factor)
print(f"Rescaled shape: {image.shape}, first pixel value: {image[0][0]}")
image = normalize(image, mean=image_mean, std=image_std)
print(f"Normalized shape: {image.shape}, first pixel value: {image[0][0]}")
axes = list(range(image.ndim - 3)) + [image.ndim - 1, image.ndim - 3, image.ndim - 2]
image = image.transpose(axes)
print(f"After preprocess shape: {image.shape}, first pixel value: {image[0][0][0]}, {image[1][0][0]}, {image[2][0][0]}")
image.tofile("preprocessed_implementation_py.bin")

# Compare with SiglipImageProcessor
print("\n===Comparison Summary===")
bin1 = np.fromfile("preprocessed_SiglipImageProcessor.bin", dtype=np.float32)
# bin2 = np.fromfile("preprocessed_implementation_py.bin", dtype=np.float32)
bin2 = np.fromfile("preprocessed_implementation_cpp.bin", dtype=np.float32)
if bin1.shape != bin2.shape:
    print(f"Shape mismatch: bin1 {bin1.shape}, bin2 {bin2.shape}")
else:
    print(f"Compare {bin1.shape} values\n")
    print("First 10 values of bin1:\n", bin1[:10])
    print("First 10 values of bin2:\n", bin2[:10])

    abs_err = np.abs(bin1 - bin2)
    rel_err = abs_err / (np.abs(bin1) + 1e-12)

    print("\nAbsolute Error:")
    print(" - Maximum:", np.max(abs_err))
    print(" - Average:", np.mean(abs_err))

    print("\nRelative Error:")
    print(f" - Maximum: {np.max(rel_err)} %")
    print(f" - Average: {np.mean(rel_err)} %")

    # abs_threshold = 0.1
    # rel_threshold = 0.05
    # abs_large_idx = np.where(abs_err > abs_threshold)[0]
    # rel_large_idx = np.where(rel_err > rel_threshold)[0]
    # print(f"\nIndices with absolute error > {abs_threshold} (total {len(abs_large_idx)}):")
    # for idx in abs_large_idx:
    #     print(f"Index {idx}: bin1={bin1[idx]}, bin2={bin2[idx]}, abs_err={abs_err[idx]:.6f}")
    # print(f"\nIndices with relative error > {rel_threshold} (total {len(rel_large_idx)}):")
    # for idx in rel_large_idx:
    #     print(f"Index {idx}: bin1={bin1[idx]}, bin2={bin2[idx]}, rel_err={rel_err[idx]:.6f}")


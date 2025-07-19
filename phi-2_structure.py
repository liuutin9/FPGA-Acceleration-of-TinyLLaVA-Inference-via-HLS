def prepare_inputs_for_multimodal_no_label(
    self, input_ids, position_ids, attention_mask, past_key_values,
    images, image_sizes=None
):
    image_features = self.encode_images(images)
    new_input_embeds = []
    cur_image_idx = 0
    cur_input_ids = input_ids
    num_images = (cur_input_ids == IMAGE_TOKEN_INDEX).sum()
    image_token_indices = [-1] + torch.where(cur_input_ids == IMAGE_TOKEN_INDEX)[0].tolist() + [cur_input_ids.shape[0]]

    cur_input_ids_noim = [
        cur_input_ids[image_token_indices[i]+1:image_token_indices[i+1]]
        for i in range(len(image_token_indices) - 1)
    ]

    split_sizes = [x.shape[0] for x in cur_input_ids_noim]
    input_embeds = self.language_model.get_input_embeddings()(torch.cat(cur_input_ids_noim))
    input_embeds_split = torch.split(input_embeds, split_sizes, dim=0)

    for i in range(num_images + 1):
        new_input_embeds.append(input_embeds_split[i])
        if i < num_images:
            new_input_embeds.append(image_features[cur_image_idx])
            cur_image_idx += 1

    new_input_embeds = [x.to(self.device) for x in new_input_embeds]
    new_input_embeds = torch.cat(new_input_embeds)

    # Padding
    tokenizer_model_max_length = getattr(self.config, 'tokenizer_model_max_length', None)
    if tokenizer_model_max_length is not None:
        new_input_embeds = new_input_embeds[:tokenizer_model_max_length]

    return None, position_ids, attention_mask, past_key_values, new_input_embeds#, new_labels

PhiForCausalLM(
  (model): PhiModel(
    (embed_tokens): Embedding(51200, 2560)
    (layers): ModuleList(
      (0-31): 32 x PhiDecoderLayer(
        (self_attn): PhiAttention(
          (q_proj): Linear(in_features=2560, out_features=2560, bias=True)
          (k_proj): Linear(in_features=2560, out_features=2560, bias=True)
          (v_proj): Linear(in_features=2560, out_features=2560, bias=True)
          (dense): Linear(in_features=2560, out_features=2560, bias=True)
        )
        (mlp): PhiMLP(
          (activation_fn): NewGELUActivation()
          (fc1): Linear(in_features=2560, out_features=10240, bias=True)
          (fc2): Linear(in_features=10240, out_features=2560, bias=True)
        )
        (input_layernorm): LayerNorm((2560,), eps=1e-05, elementwise_affine=True)
        (resid_dropout): Dropout(p=0.1, inplace=False)
      )
    )
    (rotary_emb): PhiRotaryEmbedding()
    (embed_dropout): Dropout(p=0.0, inplace=False)
    (final_layernorm): LayerNorm((2560,), eps=1e-05, elementwise_affine=True)
  )
  (lm_head): Linear(in_features=2560, out_features=51200, bias=True)
)
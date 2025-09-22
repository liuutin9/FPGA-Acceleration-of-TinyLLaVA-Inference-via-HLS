-   golden1 => 官方給的測試code 
(使用者輸入的)prompt + image file/url => output_text
prompt = "What are these?"
image = "test.jpg"
golden output = 

-   golden2 => 拆開 modeling_tinyllava_phi
1. (內部完整的)prompt => tokenizer       => input_ids
   image(file/url)   => image_processor => image_tensor
2. input_ids + image_tensor => tinyllava.generate => output_ids 
3. output_ids => tokenizer => output_text

-   golden3 => 拆開 tinyllava.generate
1. (內部完整的)prompt => tokenizer       => input_ids
   image(file/url)   => image_processor => image_tensor
2. input_ids + image_tensor => tinyllava.prepare_inputs_labels_for_multimodal => inputs_embeds
3. inputs_embeds => PhiForCausalLM.generate => output_ids
4. output_ids => tokenizer => output_text

-  golden4 => 拆開 PhiForCausalLM.generate
1. (內部完整的)prompt => tokenizer       => input_ids
   image(file/url)   => image_processor => image_tensor
2. input_ids + image_tensor => tinyllava.prepare_inputs_labels_for_multimodal => inputs_embeds
3. 重複做直到達到max_length或句子結束:
   (1) inputs_embeds => PhiModel.forward => outputs(其實只需要其中的past_key_values和last_hidden_state)
   (2) last_hidden_state => PhiForCausalLM.lm_head => logits
   (3) logits => greedy_search => new_token_id
   (4) new_token_id => PhiForCausalLM.get_input_embeddings => inputs_embeds
   (5) 更新 past_key_values
4. output_ids => tokenizer => output_text

- golden5(待debug) => 目前只能跑到前三個(是對的)然後就 CUDA out of memory

大概跑的時間:
golden1 => 15分鐘
golden2 => 12分鐘
golden3 => 13分鐘
golden4 => 11分鐘 (5秒/token)

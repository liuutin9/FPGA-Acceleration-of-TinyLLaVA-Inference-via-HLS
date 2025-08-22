#define MAX_LEN TOKENIZER_MODEL_MAX_LENGTH
#define TOKEN_LEN 64
// Model Constants
#define IGNORE_INDEX -100
#define IMAGE_TOKEN_INDEX -200
#define DEFAULT_IMAGE_TOKEN "<image>"
#define DEFAULT_IMAGE_PATCH_TOKEN "<im_patch>"
#define DEFAULT_IM_START_TOKEN "<im_start>"
#define DEFAULT_IM_END_TOKEN "<im_end>"
#define IMAGE_PLACEHOLDER "<image-placeholder>"

#define CONTROLLER_HEART_BEAT_EXPIRATION 30
#define WORKER_HEART_BEAT_INTERVAL 15
#define LOGDIR "."

#define MAX_NEW_TOKENS 512
#define NUM_BEAMS 1
#define TEMPERATURE 0
#define DO_SAMPLE false
#define USE_CACHE true

#define TOKENIZER_PADDING_SIDE "right"
#define TOKENIZER_MODEL_MAX_LENGTH 3072

#define MAX_NUM 16

const float language_model_model_embed_tokens_weight[VOCAB_SIZE][HIDDEN_SIZE];

void TinyLlava();

void chat(char prompt[MAX_LEN], std::string image_path);

std::pair<std::vector<std::vector<float>>, int> prepare_input_for_multimodel(
    std::vector<int> input_ids,
    float images[MAX_NUM][NUM_CHANNELS][IMAGE_SIZE][IMAGE_SIZE],
    const int num_images
);

std::vector<int> tokenizer(char chunk[MAX_LEN]);
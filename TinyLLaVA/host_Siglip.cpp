#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <CL/cl.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <vector>
#include <xclhal2.h>

using namespace std;

#define ALL_MESSAGES

//#include "config.h"
//TODO:
#define VISION_HIDDEN_SIZE 1152
#define INPUT_DIM 729
#define NUM_ATTENTION_HEADS 16
#define HEAD_DIM 72
#define INTERMEDIATE_SIZE 4304
#define HIDDEN_SIZE 2560
#define CONNECTOR_INPUT_DIM (INPUT_DIM - 1)

#define SIZE_SIGLIP_ENCODER_LAYERNORM_IN          INPUT_DIM * VISION_HIDDEN_SIZE
#define SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT      VISION_HIDDEN_SIZE
#define SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS        VISION_HIDDEN_SIZE
#define SIZE_SIGLIP_ENCODER_LAYERNORM_OUT         INPUT_DIM * VISION_HIDDEN_SIZE
#define SIZE_SIGLIP_ENCODER_LINEAR_IN             INPUT_DIM * VISION_HIDDEN_SIZE
#define SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT         VISION_HIDDEN_SIZE * VISION_HIDDEN_SIZE                  // output Q,K,V
#define SIZE_SIGLIP_ENCODER_LINEAR_BIAS           VISION_HIDDEN_SIZE                                // output Q,K,V
#define SIZE_SIGLIP_ENCODER_LINEAR_OUT            NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM // output Q,K,V
#define SIZE_SIGLIP_ENCODER_ATTENTION_IN_QUERY    NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM
#define SIZE_SIGLIP_ENCODER_ATTENTION_IN_KEY      NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM
#define SIZE_SIGLIP_ENCODER_ATTENTION_IN_VALUE    NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM
#define SIZE_SIGLIP_ENCODER_ATTENTION_OUT_WEIGHT  VISION_HIDDEN_SIZE * VISION_HIDDEN_SIZE
#define SIZE_SIGLIP_ENCODER_ATTENTION_OUT_BIAS    VISION_HIDDEN_SIZE
#define SIZE_SIGLIP_ENCODER_ATTENTION_OUT         INPUT_DIM * VISION_HIDDEN_SIZE

#define SIZE_SIGLIP_ENCODER_MLP_IN           	  INPUT_DIM * VISION_HIDDEN_SIZE
#define SIZE_SIGLIP_ENCODER_MLP_FC1_WEIGHT   	  INTERMEDIATE_SIZE * VISION_HIDDEN_SIZE
#define SIZE_SIGLIP_ENCODER_MLP_FC1_BIAS     	  INTERMEDIATE_SIZE
#define SIZE_SIGLIP_ENCODER_MLP_FC2_WEIGHT   	  VISION_HIDDEN_SIZE * INTERMEDIATE_SIZE
#define SIZE_SIGLIP_ENCODER_MLP_FC2_BIAS     	  VISION_HIDDEN_SIZE
#define SIZE_SIGLIP_ENCODER_MLP_OUT          	  INPUT_DIM * VISION_HIDDEN_SIZE

#define SIZE_SIGLIP_ENCODER_RESIDUAL_IN1          INPUT_DIM * VISION_HIDDEN_SIZE
#define SIZE_SIGLIP_ENCODER_RESIDUAL_IN2          INPUT_DIM * VISION_HIDDEN_SIZE
#define SIZE_SIGLIP_ENCODER_RESIDUAL_OUT          INPUT_DIM * VISION_HIDDEN_SIZE

#define CONNECTOR_OUT      CONNECTOR_INPUT_DIM*HIDDEN_SIZE
#define CONNECTOR_IN     CONNECTOR_INPUT_DIM*VISION_HIDDEN_SIZE
#define CONNECTOR_0_WEIGHT     HIDDEN_SIZE*VISION_HIDDEN_SIZE
#define CONNECTOR_0_BIAS     HIDDEN_SIZE
#define CONNECTOR_2_WEIGHT     HIDDEN_SIZE*HIDDEN_SIZE
#define CONNECTOR_2_BIAS     HIDDEN_SIZE

#include <string>

// Everything below lives in siglip_host:: so this file can be linked together with the
// Phi-2 host (both define errCode, loadFile2Memory, ...). Build with -DTINYLLAVA_LIB to
// drop the standalone main() at the end of the file.
namespace siglip_host {

// Folder holding the exported SigLIP / connector weights (fp16 .bin, one file per tensor).
string g_weight_dir = "/home/undergraduate/zylin24/Test_data_16/weight/";
string g_path_buf;
// Returns g_weight_dir + name. The pointer is valid until the next wpath() call.
const char* wpath(const char* name) {
	g_path_buf = g_weight_dir + name;
	return g_path_buf.c_str();
}

//#include "typedefs.h"
typedef ap_fixed<32,14> fixed32_14;
typedef ap_uint<16>  uint16;

cl_command_queue    Command_Queue;

cl_int              errCode;

//const int Nb_Of_Mem_Events = 424,//24 + 25 * 16,//16 + 7 + 16 * 25 + 1
//		Nb_Of_Exe_Events = 234;//9 * 26;
const int Nb_Of_Mem_Events = 429, //29 + 25 * 16
		Nb_Of_Exe_Events = 235;//9 * 26 + 1;


cl_event Mem_op_event[Nb_Of_Mem_Events],
			K_exe_event[Nb_Of_Exe_Events];

cl_kernel K_Siglip_layernorm, K_Siglip_linear, K_Siglip_attention, K_Siglip_residual, K_Siglip_MLP, K_Siglip_copy, K_Connector;

cl_mem GlobMem_BUF_layernorm1_weight, GlobMem_BUF_layernorm1_bias,
		   GlobMem_BUF_linear_q_weight  , GlobMem_BUF_linear_q_bias,
		   GlobMem_BUF_linear_k_weight  , GlobMem_BUF_linear_k_bias,
		   GlobMem_BUF_linear_v_weight  , GlobMem_BUF_linear_v_bias,
		   GlobMem_BUF_layernorm2_weight, GlobMem_BUF_layernorm2_bias,
		   GlobMem_BUF_attn_out_weight  , GlobMem_BUF_attn_out_bias,
		   GlobMem_BUF_mlp_weight1, GlobMem_BUF_mlp_bias1, GlobMem_BUF_mlp_weight2, GlobMem_BUF_mlp_bias2,
           GlobMem_BUF_0_weight, GlobMem_BUF_0_bias, GlobMem_BUF_2_weight, GlobMem_BUF_2_bias,
		   GlobMem_BUF_1, GlobMem_BUF_2, GlobMem_BUF_3, GlobMem_BUF_4, GlobMem_BUF_5, GlobMem_BUF_6, GlobMem_BUF_7, GlobMem_BUF_8;

fixed32_14 *Siglip_in;
fixed32_14 *Siglip_out;
uint16 *layernorm1_weight, *layernorm1_bias, *layernorm2_weight, *layernorm2_bias;
uint16 *linear_q_weight, *linear_k_weight, *linear_v_weight, *linear_q_bias, *linear_k_bias, *linear_v_bias;
uint16 *attn_out_weight, *attn_out_bias;
uint16 *mlp_weight1, *mlp_weight2, *mlp_bias1, *mlp_bias2;
uint16 *_0_weight, *_0_bias, *_2_weight, *_2_bias;

int layer_num = 26;

//#include "help_functions.h"
int loadFile2Memory(const char *filename, char **result) {

    int size = 0;

    std::ifstream stream(filename, std::ifstream::binary);
    if (!stream) {
        return -1;
    }

    stream.seekg(0, stream.end);
    size = stream.tellg();
    stream.seekg(0, stream.beg);

    *result = new char[size + 1];
    stream.read(*result, size);
    if (!stream) {
        return -2;
    }
    stream.close();
    (*result)[size] = 0;
    return size;
}
void load_data(const char *File_Name, fixed32_14* buffer, int Nb_Of_Elements) {
	std::ifstream fin(File_Name, std::ios::binary);
	if (!fin.is_open()) {
		cout << endl << "HOST-Error: Failed to open the " <<  File_Name << " fore read" << endl << endl;
		exit(1);
	}
	float* temp_float = new float[Nb_Of_Elements];
	fin.read(reinterpret_cast<char*>(temp_float), Nb_Of_Elements*sizeof(float));
	if (!fin) {
		std::cerr << "Error: Failed to read enough data from " << File_Name << std::endl;
	    fin.close();
	    exit(1);
	}
	fin.close();

	for (int i = 0; i < Nb_Of_Elements; ++i) {
		buffer[i] = fixed32_14(temp_float[i]);
	}
	delete[] temp_float;
}
int readBinaryFile(
	const char *filename,
    std::vector<char> &buffer,
	std::streampos byte_offset,
	std::size_t byte_size
) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    // 移動到指定位置
    file.seekg(byte_offset);
    if (!file) {
        std::cerr << "Error seeking file: " << filename << std::endl;
        return 2;
    }

    // 調整 buffer 大小，準備讀取
    buffer.resize(byte_size);

    // 讀取 byte_size bytes
    file.read(buffer.data(), byte_size);
    if (!file) {
        std::cerr << "Error reading file: " << filename << std::endl;
        return 3;
    }

    return 0;
}
int binaryToUint16(uint16* out, const vector<char>& binary) {
	memcpy(out, binary.data(), binary.size());
	return 0;
}
int load_data_uint16(const char *filename, uint16* out, int length, int len_offset) {
	vector<char> binary;
	if (readBinaryFile(filename, binary, len_offset * 2, length * 2) != 0) {
		return -1;
	}
	return binaryToUint16(out, binary);
}

int prepare_data_for_one_layer(int layer_id/*, fixed32_14 *Siglip_in, fixed32_14 *Siglip_out*/){
	// fixed32_14 *Siglip_in;
    // fixed32_14 *Siglip_out;
	// vector<uint16*> ptrs;
	// uint16 *layernorm1_weight, *layernorm1_bias, *layernorm2_weight, *layernorm2_bias;
	// uint16 *linear_q_weight, *linear_k_weight, *linear_v_weight, *linear_q_bias, *linear_k_bias, *linear_v_bias;
	// uint16 *attn_out_weight, *attn_out_bias;
	// uint16 *mlp_weight1, *mlp_weight2, *mlp_bias1, *mlp_bias2;

	void *ptr=nullptr;

	string base = g_weight_dir + "vision_tower._vision_tower.vision_model.encoder.layers.";
    string layer = base + std::to_string(layer_id);
	string filename;
	// char* layer = "/home/undergraduate/zylin24/Test_data_16/weight/vision_tower._vision_tower.vision_model.encoder.layers."
	// char* pos = strrchr(layer, '.');
	// if (pos) {
	// 	sprintf(pos + 1, "%d", layer_id);
	// }


	// cout << "HOST-Info: Generating data for in ... ";
	// if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LAYERNORM_IN*sizeof(fixed32_14))) {
	// 	cout << endl << "HOST-Error: Out of Memory during memory allocation for in array" << endl << endl;
	// 	return EXIT_FAILURE;
	// }
	// Siglip_in = reinterpret_cast<fixed32_14*>(ptr);
	// const char* filename = "/home/undergraduate/zylin24/Test_data_16/in/Siglip_embedding_output.bin";
	// load_data(filename, Siglip_in, SIZE_SIGLIP_ENCODER_LAYERNORM_IN);
	// cout << "Generated " << SIZE_SIGLIP_ENCODER_LAYERNORM_IN << " values" << endl;
    ///////////////////////////////////////////////////////////
	cout << "HOST-Info: Generating data for layernorm1_weight ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for layernorm1_weight array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	layernorm1_weight = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".layer_norm1.weight.bin";
	load_data_uint16(filename.c_str(), layernorm1_weight, SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT, 0);
	//ptrs.push_back(layernorm1_weight);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for layernorm1_bias ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for layernorm1_bias array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	layernorm1_bias = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".layer_norm1.bias.bin";
	load_data_uint16(filename.c_str(), layernorm1_bias, SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS, 0);
	//ptrs.push_back(layernorm1_bias);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS << " values" << endl;
    ///////////////////////////////////////////////////////////////
	cout << "HOST-Info: Generating data for linear_q_weight ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for linear_q_weight array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	linear_q_weight = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".self_attn.q_proj.weight.bin";
	load_data_uint16(filename.c_str(), linear_q_weight, SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT, 0);
	//ptrs.push_back(linear_q_weight);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for linear_q_bias ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LINEAR_BIAS*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for layernorm1_bias array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	linear_q_bias = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".self_attn.q_proj.bias.bin";
	load_data_uint16(filename.c_str(), linear_q_bias, SIZE_SIGLIP_ENCODER_LINEAR_BIAS, 0);
	//ptrs.push_back(linear_q_bias);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LINEAR_BIAS << " values" << endl;

	cout << "HOST-Info: Generating data for linear_k_weight ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for linear_q_weight array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	linear_k_weight = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".self_attn.k_proj.weight.bin";
	load_data_uint16(filename.c_str(), linear_k_weight, SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT, 0);
	//ptrs.push_back(linear_k_weight);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for linear_k_bias ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LINEAR_BIAS*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for layernorm1_bias array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	linear_k_bias = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".self_attn.k_proj.bias.bin";
	load_data_uint16(filename.c_str(), linear_k_bias, SIZE_SIGLIP_ENCODER_LINEAR_BIAS, 0);
	//ptrs.push_back(linear_k_bias);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LINEAR_BIAS << " values" << endl;

	cout << "HOST-Info: Generating data for linear_v_weight ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for linear_q_weight array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	linear_v_weight = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".self_attn.v_proj.weight.bin";
	load_data_uint16(filename.c_str(), linear_v_weight, SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT, 0);
	//ptrs.push_back(linear_v_weight);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for linear_v_bias ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LINEAR_BIAS*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for layernorm1_bias array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	linear_v_bias = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".self_attn.v_proj.bias.bin";
	load_data_uint16(filename.c_str(), linear_v_bias, SIZE_SIGLIP_ENCODER_LINEAR_BIAS, 0);
	//ptrs.push_back(linear_v_bias);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LINEAR_BIAS << " values" << endl;
	///////////////////////////////////////////////////////
	cout << "HOST-Info: Generating data for layernorm2_weight ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for layernorm2_weight array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	layernorm2_weight = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".layer_norm2.weight.bin";
	load_data_uint16(filename.c_str(), layernorm2_weight, SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT, 0);
	//ptrs.push_back(layernorm2_weight);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for layernorm2_bias ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for layernorm2_bias array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	layernorm2_bias = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".layer_norm2.bias.bin";
	load_data_uint16(filename.c_str(), layernorm2_bias, SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS, 0);
	//ptrs.push_back(layernorm2_bias);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS << " values" << endl;
	///////////////////////////////////////////////////////
	cout << "HOST-Info: Generating data for attn_out_weight ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_ATTENTION_OUT_WEIGHT*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for attn_out_weight array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	attn_out_weight = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".self_attn.out_proj.weight.bin";
	load_data_uint16(filename.c_str(), attn_out_weight, SIZE_SIGLIP_ENCODER_ATTENTION_OUT_WEIGHT, 0);
	//ptrs.push_back(attn_out_weight);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_ATTENTION_OUT_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for attn_out_bias ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_ATTENTION_OUT_BIAS*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for attn_out_bias array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	attn_out_bias = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".self_attn.out_proj.bias.bin";
	load_data_uint16(filename.c_str(), attn_out_bias, SIZE_SIGLIP_ENCODER_ATTENTION_OUT_BIAS, 0);
	//ptrs.push_back(attn_out_bias);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_ATTENTION_OUT_BIAS << " values" << endl;
    ///////////////////////////////////////////////////////////////

	cout << "HOST-Info: Generating data for weight ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_MLP_FC1_WEIGHT*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for weight array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	mlp_weight1 = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".mlp.fc1.weight.bin";
	load_data_uint16(filename.c_str(), mlp_weight1, SIZE_SIGLIP_ENCODER_MLP_FC1_WEIGHT, 0);
	//ptrs.push_back(mlp_weight1);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_MLP_FC1_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for bias ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_MLP_FC1_BIAS*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for bias array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	mlp_bias1 = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".mlp.fc1.bias.bin";
	load_data_uint16(filename.c_str(), mlp_bias1, SIZE_SIGLIP_ENCODER_MLP_FC1_BIAS, 0);
	//ptrs.push_back(mlp_bias1);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_MLP_FC1_BIAS << " values" << endl;

	cout << "HOST-Info: Generating data for weight ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_MLP_FC2_WEIGHT*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for weight array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	mlp_weight2 = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".mlp.fc2.weight.bin";
	load_data_uint16(filename.c_str(), mlp_weight2, SIZE_SIGLIP_ENCODER_MLP_FC2_WEIGHT, 0);
	//ptrs.push_back(mlp_weight2);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_MLP_FC2_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for bias ... ";
//	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_MLP_FC2_BIAS*sizeof(uint16))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for bias array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	mlp_bias2 = reinterpret_cast<uint16*>(ptr);
	filename = layer + ".mlp.fc2.bias.bin";
	load_data_uint16(filename.c_str(), mlp_bias2, SIZE_SIGLIP_ENCODER_MLP_FC2_BIAS, 0);
	//ptrs.push_back(mlp_bias2);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_MLP_FC2_BIAS << " values" << endl;
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	// cout << "HOST-Info: Allocating memory for Siglip_out ... ";
	// if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_MLP_OUT*sizeof(fixed32_14))) {
	// 	cout << endl << "HOST-Error: Out of Memory during memory allocation for Siglip_out array" << endl << endl;
	// 	return EXIT_FAILURE;
	// }
	// Siglip_out = reinterpret_cast<fixed32_14*>(ptr);

	cout << endl;

	return 0;
}

int run_one_layer(int layer_id){
	if(layer_id == 0){
		return -1;
	}
	int MigrateMemObjectsOffset = (layer_id - 1) * 16 + 28 - 1;
	int EnqueueTaskOffset = layer_id * 9;
	// ----------------------------------------
	// TODO Step 5.1: Set Kernel Arguments
	// ----------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Setting Kernel arguments ..." << endl;
	#endif
	errCode  = false;

	errCode |= clSetKernelArg(K_Siglip_layernorm,      0, sizeof(cl_mem),  &GlobMem_BUF_2);
	errCode |= clSetKernelArg(K_Siglip_layernorm,      1, sizeof(cl_mem),  &GlobMem_BUF_1);
	errCode |= clSetKernelArg(K_Siglip_layernorm,      2, sizeof(cl_mem),  &GlobMem_BUF_layernorm1_weight);
	errCode |= clSetKernelArg(K_Siglip_layernorm,      3, sizeof(cl_mem),  &GlobMem_BUF_layernorm1_bias);

	if (errCode != CL_SUCCESS) {
		cout << endl << "Host-ERROR: Failed to set Kernel arguments" << endl << endl;
		return EXIT_FAILURE;
	}

	// ------------------------------------------------------
	// TODO Step 5.2: Copy Input data from Host to Global Memory
	// ------------------------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST_Info: Copy Input data to Global Memory ..." << endl;
	#endif
//	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_Siglip_in,         0, 0, NULL, &Mem_op_event[0]);
	// errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_1,                 0, 0, NULL, &Mem_op_event[layer_id * 23 + 0]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_layernorm1_weight, 0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 1]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_layernorm1_bias,   0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 2]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_linear_q_weight,   0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 3]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_linear_q_bias,     0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 4]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_linear_k_weight,   0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 5]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_linear_k_bias,     0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 6]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_linear_v_weight,   0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 7]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_linear_v_bias,     0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 8]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_layernorm2_weight, 0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 9]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_layernorm2_bias,   0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 10]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_attn_out_weight,   0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 11]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_attn_out_bias,     0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 12]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_mlp_weight1, 0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 13]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_mlp_bias1, 0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 14]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_mlp_weight2, 0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 15]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_mlp_bias2, 0, 0, NULL, &Mem_op_event[MigrateMemObjectsOffset + 16]);

	// errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_2, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[17]);
    // errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_3, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[18]);
    // errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_4, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[19]);
    // errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_5, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[20]);
    // errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_6, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[21]);
    // errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_7, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[22]);

	// --------------------------------------------------------

	errCode = clEnqueueBarrier (Command_Queue);
	// errCode = clEnqueueBarrierWithWaitList (Command_Queue, 16, Mem_op_event + MigrateMemObjectsOffset + 1, NULL);
	if (errCode != CL_SUCCESS) {
		cout << endl << "HOST-Error: Failed to Submit BarrierWithWaitList" << endl << endl;
		return EXIT_FAILURE;
	}

	// ----------------------------------------
	// TODO Step 5.3: Submit Kernels for Execution
	// ----------------------------------------

	cout << "HOST-Info: Submitting Kernel ..." << endl;
	errCode = clEnqueueTask(Command_Queue, K_Siglip_copy,      0,            NULL, &K_exe_event[EnqueueTaskOffset + 0]); // TODO : NULL?
    errCode = clEnqueueTask(Command_Queue, K_Siglip_layernorm, 1, &K_exe_event[EnqueueTaskOffset + 0], &K_exe_event[EnqueueTaskOffset + 1]);
	errCode = clEnqueueTask(Command_Queue, K_Siglip_linear,    1, &K_exe_event[EnqueueTaskOffset + 1], &K_exe_event[EnqueueTaskOffset + 2]);
	errCode = clEnqueueTask(Command_Queue, K_Siglip_attention, 1, &K_exe_event[EnqueueTaskOffset + 2], &K_exe_event[EnqueueTaskOffset + 3]);
	errCode = clEnqueueTask(Command_Queue, K_Siglip_residual,  1, &K_exe_event[EnqueueTaskOffset + 3], &K_exe_event[EnqueueTaskOffset + 4]);
	errCode = clEnqueueTask(Command_Queue, K_Siglip_copy,      1, &K_exe_event[EnqueueTaskOffset + 4], &K_exe_event[EnqueueTaskOffset + 5]);

	errCode |= clSetKernelArg(K_Siglip_layernorm,      0, sizeof(cl_mem),  &GlobMem_BUF_2);
	errCode |= clSetKernelArg(K_Siglip_layernorm,      1, sizeof(cl_mem),  &GlobMem_BUF_1);
	errCode |= clSetKernelArg(K_Siglip_layernorm,      2, sizeof(cl_mem),  &GlobMem_BUF_layernorm2_weight);
	errCode |= clSetKernelArg(K_Siglip_layernorm,      3, sizeof(cl_mem),  &GlobMem_BUF_layernorm2_bias);
	errCode = clEnqueueTask(Command_Queue, K_Siglip_layernorm, 1, &K_exe_event[EnqueueTaskOffset + 5], &K_exe_event[EnqueueTaskOffset + 6]);

	errCode = clEnqueueTask(Command_Queue, K_Siglip_MLP,       1, &K_exe_event[EnqueueTaskOffset + 6], &K_exe_event[EnqueueTaskOffset + 7]);
	errCode = clEnqueueTask(Command_Queue, K_Siglip_residual,  1, &K_exe_event[EnqueueTaskOffset + 7], &K_exe_event[EnqueueTaskOffset + 8]);

	return 0;
}

void run_custom_profiling (int Nb_Of_Kernels, int Nb_Of_Memory_Tranfers, cl_event* K_exe_event, cl_event* Mem_op_event,string* list_of_kernel_names) {
	typedef struct {
		string    action_type; // kernel, "memory (H->G)", "memory (G->H)"
		string    name;
		cl_event  event;
		cl_ulong  profiling_command_start;
		cl_ulong  profiling_command_end;
		double    duration;
	} profile_t;

	cl_int              errCode;

	// ---------------------------------
	// TODO Profiling
	// ---------------------------------
	profile_t *PROFILE;

	PROFILE = new profile_t[Nb_Of_Kernels + Nb_Of_Memory_Tranfers];

	for (int i = 0; i < layer_num; i++){
		PROFILE[i * 9 + 0].action_type="kernel"; PROFILE[i * 9 + 0].name="K_Siglip_copy";      PROFILE[i * 9 + 0].event = K_exe_event[i * 9 + 0];
		PROFILE[i * 9 + 1].action_type="kernel"; PROFILE[i * 9 + 1].name="K_Siglip_layernorm"; PROFILE[i * 9 + 1].event = K_exe_event[i * 9 + 1];
		PROFILE[i * 9 + 2].action_type="kernel"; PROFILE[i * 9 + 2].name="K_Siglip_linear";    PROFILE[i * 9 + 2].event = K_exe_event[i * 9 + 2];
		PROFILE[i * 9 + 3].action_type="kernel"; PROFILE[i * 9 + 3].name="K_Siglip_attention"; PROFILE[i * 9 + 3].event = K_exe_event[i * 9 + 3];
		PROFILE[i * 9 + 4].action_type="kernel"; PROFILE[i * 9 + 4].name="K_Siglip_residual";  PROFILE[i * 9 + 4].event = K_exe_event[i * 9 + 4];
		PROFILE[i * 9 + 5].action_type="kernel"; PROFILE[i * 9 + 5].name="K_Siglip_copy"; 	   PROFILE[i * 9 + 5].event = K_exe_event[i * 9 + 5];
		PROFILE[i * 9 + 6].action_type="kernel"; PROFILE[i * 9 + 6].name="K_Siglip_layernorm"; PROFILE[i * 9 + 6].event = K_exe_event[i * 9 + 6];
		PROFILE[i * 9 + 7].action_type="kernel"; PROFILE[i * 9 + 7].name="K_Siglip_mlp"; 	   PROFILE[i * 9 + 7].event = K_exe_event[i * 9 + 7];
		PROFILE[i * 9 + 8].action_type="kernel"; PROFILE[i * 9 + 8].name="K_Siglip_residual";  PROFILE[i * 9 + 8].event = K_exe_event[i * 9 + 8];
	}
    PROFILE[Nb_Of_Kernels - 1].action_type="kernel"; PROFILE[Nb_Of_Kernels - 1].name="K_Connector";  PROFILE[Nb_Of_Kernels - 1].event = K_exe_event[Nb_Of_Kernels - 1];

    for (int i=0; i<Nb_Of_Memory_Tranfers; i++) {
		PROFILE[Nb_Of_Kernels+i].action_type="mem (H<->G)";
		PROFILE[Nb_Of_Kernels+i].name="Transfer_" + to_string(i+1);
		PROFILE[Nb_Of_Kernels+i].event = Mem_op_event[i];
	}

	// -------------------------------------------------------------------------------------
	// Get events Start and End times and calculate duration for
	//   o) each Kernel and
	//   o) Memory (Global <-> Host) transfer.
	// Event Profile Info:
	//   o) CL_PROFILING_COMMAND_QUEUED
	//   o) CL_PROFILING_COMMAND_SUBMIT
	//   o) CL_PROFILING_COMMAND_START
	//   o) CL_PROFILING_COMMAND_END
	// -------------------------------------------------------------------------------------
	size_t nb_of_returned_bytes;

	for (int i=0; i<Nb_Of_Kernels + Nb_Of_Memory_Tranfers; i++) {
		errCode = clGetEventProfilingInfo(PROFILE[i].event, CL_PROFILING_COMMAND_START,
										  sizeof(cl_ulong), &PROFILE[i].profiling_command_start, &nb_of_returned_bytes);
		if (errCode != CL_SUCCESS) {
			cout << endl << "HOST-Error: Failed to get profiling info for " << PROFILE[i].name << " " << PROFILE[i].action_type << endl << endl;
			exit(0);
		}

		errCode = clGetEventProfilingInfo(PROFILE[i].event, CL_PROFILING_COMMAND_END,
										  sizeof(cl_ulong), &PROFILE[i].profiling_command_end, &nb_of_returned_bytes);
		if (errCode != CL_SUCCESS) {
			cout << endl << "HOST-Error: Failed to get profiling info for " << PROFILE[i].name << " " << PROFILE[i].action_type << endl << endl;
			exit(0);
		}

		PROFILE[i].duration = (double)(PROFILE[i].profiling_command_end - PROFILE[i].profiling_command_start) * 1.0e-6;
	}

	// -------------------------------------------------------------------------------------
	// Calculate Duration of
	//   o) All kernels execution time
	//   o) Application execution time (Kernels + Memory transfer)
	// -------------------------------------------------------------------------------------
	struct {
		int      Kernels_Start_Time_Index=0;
		int      Kernels_End_Time_Index=0;
		cl_ulong Kernels_Start_Time=0;
		cl_ulong Kernels_End_Time=0;

		int      Application_Start_Time_Index=0;
		int      Application_End_Time_Index=0;
		cl_ulong Application_Start_Time=0;
		cl_ulong Application_End_Time=0;
	} PROFILE_STAT;


	for (int i=0; i<Nb_Of_Kernels + Nb_Of_Memory_Tranfers; i++) {

		// Calculate Application statistics
		// .................................
		if ((PROFILE_STAT.Application_Start_Time == 0) || (PROFILE_STAT.Application_Start_Time > PROFILE[i].profiling_command_start)) {
			PROFILE_STAT.Application_Start_Time       = PROFILE[i].profiling_command_start;
			PROFILE_STAT.Application_Start_Time_Index = i;
		}

		if (PROFILE_STAT.Application_End_Time < PROFILE[i].profiling_command_end) {
			PROFILE_STAT.Application_End_Time       = PROFILE[i].profiling_command_end;
			PROFILE_STAT.Application_End_Time_Index = i;
		}

		// Calculate Kernel statistics
		// .................................
		if (PROFILE[i].action_type == "kernel") {
			if ((PROFILE_STAT.Kernels_Start_Time == 0) || (PROFILE_STAT.Kernels_Start_Time > PROFILE[i].profiling_command_start)) {
				PROFILE_STAT.Kernels_Start_Time       = PROFILE[i].profiling_command_start;
				PROFILE_STAT.Kernels_Start_Time_Index = i;
			}

			if (PROFILE_STAT.Kernels_End_Time < PROFILE[i].profiling_command_end) {
				PROFILE_STAT.Kernels_End_Time       = PROFILE[i].profiling_command_end;
				PROFILE_STAT.Kernels_End_Time_Index = i;
			}
		}
	}

	// ------------------------------
	// Print Profiling Data
	// ------------------------------
	int Column_Widths[5] = {15, 16, 15, 15, 15}, Separation_Line_Width = 0;

	// Print Table Header
	// ....................
	for (int i=0; i<5; i++)  Separation_Line_Width += Column_Widths[i];
	Separation_Line_Width += 3;
	cout << "HOST-Info: " << string(Separation_Line_Width, '-') << endl;

	cout << "HOST-Info: "          << left << setw(Column_Widths[0]-1) << "Name"
						  << " | " << left << setw(Column_Widths[1]-3) << "type"
						  << " | " << left << setw(Column_Widths[2]-3) << "start"
						  << " | " << left << setw(Column_Widths[2]-3) << "end"
						  << " | " << left << setw(Column_Widths[2]-3) << "Duration(ms)"
						  << endl;

	cout << "HOST-Info: " << string(Separation_Line_Width, '-') << endl;


	// Print Individual info for each Kernel and Memory transfer
	// ..........................................................
	for (int i=0; i<Nb_Of_Kernels + Nb_Of_Memory_Tranfers; i++) {
		cout << "HOST-Info: "          << left  << setw(Column_Widths[0]-1) << PROFILE[i].name
							  << " | " << left  << setw(Column_Widths[1]-3) << PROFILE[i].action_type
							  << " | " << right << setw(Column_Widths[2]-3) << PROFILE[i].profiling_command_start
							  << " | " << right << setw(Column_Widths[2]-3) << PROFILE[i].profiling_command_end
							  << " | " << right << setw(Column_Widths[2]-3) << PROFILE[i].duration
							  << endl;
	}
	cout << "HOST-Info: " << string(Separation_Line_Width, '-') << endl;

	// Print Duration of Kernels and Application execution
	// ..........................................................
	cout << "HOST-Info:     Kernels Execution Time (ms) :  "
			<< (double) (PROFILE_STAT.Kernels_End_Time - PROFILE_STAT.Kernels_Start_Time) * 0.000001 //1.0e-6
			<< "  (" << PROFILE[PROFILE_STAT.Kernels_End_Time_Index].name << "\'end - " << PROFILE[PROFILE_STAT.Kernels_Start_Time_Index].name << "\'begin)"
			<< endl;

	cout << "HOST-Info: Application Execution Time (ms) :  "
			<< (double) (PROFILE_STAT.Application_End_Time - PROFILE_STAT.Application_Start_Time) * 0.000001 //1.0e-6
			<< "  (" << PROFILE[PROFILE_STAT.Application_End_Time_Index].name << "\'end - " << PROFILE[PROFILE_STAT.Application_Start_Time_Index].name << "\'begin)"
			<< endl;

	cout << "HOST-Info: " << string(Separation_Line_Width, '-') << endl << endl;

}

//#include "config.h"
//TODO:
// #define VISION_HIDDEN_SIZE 1152
// #define INPUT_DIM 729
// #define NUM_ATTENTION_HEADS 16
// #define HEAD_DIM 72
// #define INTERMEDIATE_SIZE 4304
// #define SIZE_SIGLIP_ENCODER_LAYERNORM_IN          INPUT_DIM * VISION_HIDDEN_SIZE
// #define SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT      VISION_HIDDEN_SIZE
// #define SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS        VISION_HIDDEN_SIZE
// #define SIZE_SIGLIP_ENCODER_LAYERNORM_OUT         INPUT_DIM * VISION_HIDDEN_SIZE
// #define SIZE_SIGLIP_ENCODER_LINEAR_IN             INPUT_DIM * VISION_HIDDEN_SIZE
// #define SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT         VISION_HIDDEN_SIZE * VISION_HIDDEN_SIZE                  // output Q,K,V
// #define SIZE_SIGLIP_ENCODER_LINEAR_BIAS           VISION_HIDDEN_SIZE                                // output Q,K,V
// #define SIZE_SIGLIP_ENCODER_LINEAR_OUT            NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM // output Q,K,V
// #define SIZE_SIGLIP_ENCODER_ATTENTION_IN_QUERY    NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM
// #define SIZE_SIGLIP_ENCODER_ATTENTION_IN_KEY      NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM
// #define SIZE_SIGLIP_ENCODER_ATTENTION_IN_VALUE    NUM_ATTENTION_HEADS * INPUT_DIM * HEAD_DIM
// #define SIZE_SIGLIP_ENCODER_ATTENTION_OUT_WEIGHT  VISION_HIDDEN_SIZE * VISION_HIDDEN_SIZE
// #define SIZE_SIGLIP_ENCODER_ATTENTION_OUT_BIAS    VISION_HIDDEN_SIZE
// #define SIZE_SIGLIP_ENCODER_ATTENTION_OUT         INPUT_DIM * VISION_HIDDEN_SIZE

// #define SIZE_SIGLIP_ENCODER_MLP_IN           	  INPUT_DIM * VISION_HIDDEN_SIZE
// #define SIZE_SIGLIP_ENCODER_MLP_FC1_WEIGHT   	  INTERMEDIATE_SIZE * VISION_HIDDEN_SIZE
// #define SIZE_SIGLIP_ENCODER_MLP_FC1_BIAS     	  INTERMEDIATE_SIZE
// #define SIZE_SIGLIP_ENCODER_MLP_FC2_WEIGHT   	  VISION_HIDDEN_SIZE * INTERMEDIATE_SIZE
// #define SIZE_SIGLIP_ENCODER_MLP_FC2_BIAS     	  VISION_HIDDEN_SIZE
// #define SIZE_SIGLIP_ENCODER_MLP_OUT          	  INPUT_DIM * VISION_HIDDEN_SIZE

// #define SIZE_SIGLIP_ENCODER_RESIDUAL_IN1          INPUT_DIM * VISION_HIDDEN_SIZE
// #define SIZE_SIGLIP_ENCODER_RESIDUAL_IN2          INPUT_DIM * VISION_HIDDEN_SIZE
// #define SIZE_SIGLIP_ENCODER_RESIDUAL_OUT          INPUT_DIM * VISION_HIDDEN_SIZE



// Runs the 26 SigLIP encoder layers + Connector on the FPGA.
//   embeddings     : SigLIP embedding output (patch embedding + position embedding),
//                    INPUT_DIM(729) * VISION_HIDDEN_SIZE floats; nullptr = read the test .bin file
//   image_features : CONNECTOR_INPUT_DIM(728) * HIDDEN_SIZE floats out; nullptr = write the .txt file
//   weight_dir     : folder holding the exported weights ("" keeps the default)
int run_siglip_connector(
	const char* Target_Platform_Vendor,
	const char* Target_Device_Name,
	const char* xclbinFilename,
	const float* embeddings,
	float* image_features,
	const string& weight_dir)
{
	cout << endl;
	if (!weight_dir.empty()) {
		g_weight_dir = weight_dir;
		if (g_weight_dir.back() != '/') g_weight_dir += '/';
	}
	cout << "HOST-Info: Platform_Vendor   : " << Target_Platform_Vendor << endl;
	cout << "HOST-Info: Device_Name       : " << Target_Device_Name << endl;
	cout << "HOST-Info: XCLBIN_file       : " << xclbinFilename << endl;


	// ============================================================================
	// Step 2: Detect Target Platform and Target Device in a system.
	//         Create Context and Command Queue.
	// ============================================================================
	cout << endl;
	#ifdef ALL_MESSAGES
	cout << "HOST-Info: ============================================================= " << endl;
	cout << "HOST-Info: (Step 2) Detect Target Platform and Target Device in a system " << endl;
	cout << "HOST-Info:          Create Context and Command Queue                     " << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	#endif

	cl_uint         ui;

	cl_platform_id      *Platform_IDs;
	cl_uint             Nb_Of_Platforms;
	cl_platform_id      Target_Platform_ID;
	bool                Platform_Detected;
	char                *platform_info;

	cl_device_id        *Device_IDs;
	cl_uint             Nb_Of_Devices;
	cl_device_id        Target_Device_ID;
	bool                Device_Detected;
	char                *device_info;

	cl_context          Context;
	// cl_command_queue    Command_Queue;

	// cl_int              errCode;
	size_t              size;

	// ------------------------------------------------------------------------------------
	// Step 2.1: Get All PLATFORMS, then search for Target_Platform_Vendor (CL_PLATFORM_VENDOR)
	// ------------------------------------------------------------------------------------

	// Get the number of platforms
	// ..................................................
	errCode = clGetPlatformIDs(0, NULL, &Nb_Of_Platforms);
	if (errCode != CL_SUCCESS || Nb_Of_Platforms <= 0) {
		cout << endl << "HOST-Error: Failed to get the number of available platforms" << endl << endl;
		return EXIT_FAILURE;
	}

	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Number of detected platforms : " << Nb_Of_Platforms << endl;
	#endif

	// Allocate memory to store platforms
	// ..................................................
	Platform_IDs = new cl_platform_id[Nb_Of_Platforms];
	if (!Platform_IDs) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for Platform_IDs" << endl << endl;
		return EXIT_FAILURE;
	}

	// Get and store all PLATFORMS
	// ..................................................
	errCode = clGetPlatformIDs(Nb_Of_Platforms, Platform_IDs, NULL);
	if (errCode != CL_SUCCESS) {
		cout << endl << "HOST-Error: Failed to get the available platforms" << endl << endl;
		return EXIT_FAILURE;
	}

	// Search for Platform (ex: Xilinx) using: CL_PLATFORM_VENDOR = Target_Platform_Vendor
	// ....................................................................................
	Platform_Detected = false;
	for (ui = 0; ui < Nb_Of_Platforms; ui++) {

		errCode = clGetPlatformInfo(Platform_IDs[ui], CL_PLATFORM_VENDOR, 0, NULL, &size);
		if (errCode != CL_SUCCESS) {
			cout << endl << "HOST-Error: Failed to get the size of the Platofrm parameter " << "CL_PLATFORM_VENDOR" << " value " << endl << endl;
			return EXIT_FAILURE;
		}

		platform_info = new char[size];
		if (!platform_info) {
			cout << endl << "HOST-Error: Out of Memory during memory allocation for Platform Parameter " << "CL_PLATFORM_VENDOR" << endl << endl;
			return EXIT_FAILURE;
		}

		errCode = clGetPlatformInfo(Platform_IDs[ui], CL_PLATFORM_VENDOR, size, platform_info , NULL);
		if (errCode != CL_SUCCESS) {
			cout << endl << "HOST-Error: Failed to get the " << "CL_PLATFORM_VENDOR" << " platform info" << endl << endl;
			return EXIT_FAILURE;
		}

		// Check if the current platform matches Target_Platform_Vendor
		// .............................................................
		if (strcmp(platform_info, Target_Platform_Vendor) == 0) {
			Platform_Detected        = true;
			Target_Platform_ID       = Platform_IDs[ui];
			#ifdef ALL_MESSAGES
			cout << "HOST-Info: Selected platform            : " << Target_Platform_Vendor << endl << endl;
			#endif
		}
	}

	if (Platform_Detected == false) {
		cout << endl << "HOST-Error: Failed to get detect " << Target_Platform_Vendor << " platform" << endl << endl;
		return EXIT_FAILURE;
	}


	// ------------------------------------------------------------------------------------
	// Step 2.2:  Get All Devices for selected platform Target_Platform_ID
	//            then search for Xilinx platform (CL_DEVICE_NAME = Target_Device_Name)
	// ------------------------------------------------------------------------------------

	// Get the Number of Devices
	// ............................................................................
	errCode = clGetDeviceIDs(Target_Platform_ID, CL_DEVICE_TYPE_ALL, 0, NULL, &Nb_Of_Devices);
	if (errCode != CL_SUCCESS) {
		cout << endl << "HOST-Error: Failed to get the number of available Devices" << endl << endl;
		return EXIT_FAILURE;
	}
	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Number of available devices  : " << Nb_Of_Devices << endl;
	#endif

	Device_IDs = new cl_device_id[Nb_Of_Devices];
	if (!Device_IDs) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for Device_IDs" << endl << endl;
		return EXIT_FAILURE;
	}

	errCode = clGetDeviceIDs(Target_Platform_ID, CL_DEVICE_TYPE_ALL, Nb_Of_Devices, Device_IDs, NULL);
	if (errCode != CL_SUCCESS) {
		cout << endl << "HOST-Error: Failed to get available Devices" << endl << endl;
		return EXIT_FAILURE;
	}

	// Search for CL_DEVICE_NAME = Target_Device_Name
	// ............................................................................
	Device_Detected = false;
	for (ui = 0; ui < Nb_Of_Devices; ui++) {
		errCode = clGetDeviceInfo(Device_IDs[ui], CL_DEVICE_NAME, 0, NULL, &size);
		if (errCode != CL_SUCCESS) {
			cout << endl << "HOST-Error: Failed to get the size of the Device parameter value " << "CL_DEVICE_NAME" << endl << endl;
			return EXIT_FAILURE;
		}

		device_info = new char[size];
		if (!device_info) {
			cout << endl << "HOST-Error: Out of Memory during memory allocation for Device parameter " << "CL_DEVICE_NAME" << " value " << endl << endl;
			return EXIT_FAILURE;
		}

		errCode = clGetDeviceInfo(Device_IDs[ui], CL_DEVICE_NAME, size, device_info, NULL);
		if (errCode != CL_SUCCESS) {
			cout << endl << "HOST-Error: Failed to get the " << "CL_DEVICE_NAME" << " device info" << endl << endl;
			return EXIT_FAILURE;
		}

		// Check if the current device matches Target_Device_Name
		// ............................................................................
		if (strcmp(device_info, Target_Device_Name) == 0) {
			Device_Detected        = true;
			Target_Device_ID       = Device_IDs[ui];
		}
	}

	if (Device_Detected == false) {
		cout << endl << "HOST-Error: Failed to get detect " << Target_Device_Name << " device" << endl << endl;
		return EXIT_FAILURE;
	} else {
		#ifdef ALL_MESSAGES
		cout << "HOST-Info: Selected device              : " << Target_Device_Name << endl << endl;
		#endif
	}

	// ------------------------------------------------------------------------------------
	// Step 2.3: Create Context
	// ------------------------------------------------------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Creating Context ... " << endl;
	#endif
	Context = clCreateContext(0, 1, &Target_Device_ID, NULL, NULL, &errCode);
	if (errCode != CL_SUCCESS) {
		cout << endl << "HOST-Error: Failed to create a Context" << endl << endl;
		return EXIT_FAILURE;
	}

	// ------------------------------------------------------------------------------------
	// Step 2.4: Create Command Queue (commands are executed in-order)
	// ------------------------------------------------------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Creating Command Queue ... " << endl;
	#endif
	Command_Queue = clCreateCommandQueue(Context, Target_Device_ID, CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE | CL_QUEUE_PROFILING_ENABLE, &errCode);
	if (errCode != CL_SUCCESS) {
		cout << endl << "HOST-Error: Failed to create a Command Queue" << endl << endl;
		return EXIT_FAILURE;
	}

	// ============================================================================
	// Step 3: Create Program and Kernel
	// ============================================================================
	//   o) Create a Program from a Binary File and Build it
	//   o) Create a Kernel
	// ============================================================================
	#ifdef ALL_MESSAGES
	cout << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	cout << "HOST-Info: (Step 3) Create Program and Kernels                           " << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	#endif

	// ------------------------------------------------------------------
	// Step 3.1: Load Binary File from a disk to Memory
	// ------------------------------------------------------------------
	unsigned char *xclbin_Memory;
	int program_length;

	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Loading " << xclbinFilename << " binary file to memory ..." << endl;
	#endif

	program_length = loadFile2Memory(xclbinFilename, (char **) &xclbin_Memory);
	if (program_length < 0) {
		cout << endl << "HOST-Error: Failed to load " << xclbinFilename << " binary file to memory" << endl << endl;
		return EXIT_FAILURE;
	}

	// ------------------------------------------------------------
	// Step 3.2: Create a program using a Binary File
	// ------------------------------------------------------------
	size_t     Program_Length_in_Bytes;
	cl_program Program;
	cl_int     Binary_Status;

	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Creating Program with Binary ..." << endl;
	#endif
	Program_Length_in_Bytes = program_length;
	Program = clCreateProgramWithBinary(Context, 1, &Target_Device_ID, &Program_Length_in_Bytes,
                                        (const unsigned char **) &xclbin_Memory, &Binary_Status, &errCode);
	if (errCode != CL_SUCCESS) {
		cout << endl << "HOST-Error: Failed to create a Program from a Binary" << endl << endl;
		return EXIT_FAILURE;
	}

	// ----------------------------------------------------------------------
	// Step 3.3: Build (compiles and links) a program executable from binary
	// ----------------------------------------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Building the Program ..." << endl;
	#endif

	errCode = clBuildProgram(Program, 1, &Target_Device_ID, NULL, NULL, NULL);
	if (errCode != CL_SUCCESS) {
		cout << endl << "HOST-Error: Failed to build a Program Executable" << endl << endl;
		return EXIT_FAILURE;
	}

	// -------------------------------------------------------------
	// TODO Step 3.4: Create Kernels
	// -------------------------------------------------------------
	// cl_kernel K_Siglip_layernorm, K_Siglip_linear, K_Siglip_attention, K_Siglip_residual, K_Siglip_MLP, K_Siglip_copy;

	#ifdef ALL_MESSAGES
		cout << "HOST-Info: Creating Kernels ..." << endl;
	#endif
	K_Siglip_layernorm = clCreateKernel(Program, "Siglip_layernorm", &errCode);
	K_Siglip_linear    = clCreateKernel(Program, "Siglip_linear"   , &errCode);
	K_Siglip_attention = clCreateKernel(Program, "Siglip_attention", &errCode);
	K_Siglip_residual  = clCreateKernel(Program, "Siglip_residual" , &errCode);
	K_Siglip_MLP       = clCreateKernel(Program, "Siglip_MLP"      , &errCode);
	K_Siglip_copy      = clCreateKernel(Program, "Siglip_copy"     , &errCode);
    K_Connector        = clCreateKernel(Program, "Connector"       , &errCode);

	if (errCode != CL_SUCCESS) {
		cout << endl << "HOST-Error: Failed to create kernels" << endl << endl;
		return EXIT_FAILURE;
	}

	// ================================================================
	// Step 4: Prepare Data to Run Kernel
	// ================================================================
	#ifdef ALL_MESSAGES
	cout << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	cout << "HOST-Info: (Step 4) Prepare Data to Run Kernels                           " << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	#endif

	// ------------------------------------------------------------------
	// TODO Step 4.1: Generate data for DataIn_weight array
	//                Allocate Memory to store the results: RES array
	// ------------------------------------------------------------------
	// fixed32_14 *Siglip_in;
    // fixed32_14 *Siglip_out;
	// uint16 *layernorm1_weight, *layernorm1_bias, *layernorm2_weight, *layernorm2_bias;
	// uint16 *linear_q_weight, *linear_k_weight, *linear_v_weight, *linear_q_bias, *linear_k_bias, *linear_v_bias;
	// uint16 *attn_out_weight, *attn_out_bias;
	// uint16 *mlp_weight1, *mlp_weight2, *mlp_bias1, *mlp_bias2;

	void *ptr=nullptr;

	cout << "HOST-Info: Generating data for in ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LAYERNORM_IN*sizeof(fixed32_14))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for in array" << endl << endl;
		return EXIT_FAILURE;
	}
	Siglip_in = reinterpret_cast<fixed32_14*>(ptr);
	const char* filename = "/home/undergraduate/zylin24/Test_data_16/in/Siglip_embedding_output.bin";
	if (embeddings != nullptr) {
		for (int i = 0; i < SIZE_SIGLIP_ENCODER_LAYERNORM_IN; i++) Siglip_in[i] = fixed32_14(embeddings[i]);
	} else {
		load_data(filename, Siglip_in, SIZE_SIGLIP_ENCODER_LAYERNORM_IN);
	}
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LAYERNORM_IN << " values" << endl;
    ///////////////////////////////////////////////////////////
	cout << "HOST-Info: Generating data for layernorm1_weight ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for layernorm1_weight array" << endl << endl;
		return EXIT_FAILURE;
	}
	layernorm1_weight = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.layer_norm1.weight.bin");
	load_data_uint16(filename, layernorm1_weight, SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for layernorm1_bias ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for layernorm1_bias array" << endl << endl;
		return EXIT_FAILURE;
	}
	layernorm1_bias = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.layer_norm1.bias.bin");
	load_data_uint16(filename, layernorm1_bias, SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS << " values" << endl;
    ///////////////////////////////////////////////////////////////
	cout << "HOST-Info: Generating data for linear_q_weight ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for linear_q_weight array" << endl << endl;
		return EXIT_FAILURE;
	}
	linear_q_weight = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.self_attn.q_proj.weight.bin");
	load_data_uint16(filename, linear_q_weight, SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for linear_q_bias ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LINEAR_BIAS*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for layernorm1_bias array" << endl << endl;
		return EXIT_FAILURE;
	}
	linear_q_bias = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.self_attn.q_proj.bias.bin");
	load_data_uint16(filename, linear_q_bias, SIZE_SIGLIP_ENCODER_LINEAR_BIAS, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LINEAR_BIAS << " values" << endl;

	cout << "HOST-Info: Generating data for linear_k_weight ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for linear_q_weight array" << endl << endl;
		return EXIT_FAILURE;
	}
	linear_k_weight = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.self_attn.k_proj.weight.bin");
	load_data_uint16(filename, linear_k_weight, SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for linear_k_bias ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LINEAR_BIAS*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for layernorm1_bias array" << endl << endl;
		return EXIT_FAILURE;
	}
	linear_k_bias = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.self_attn.k_proj.bias.bin");
	load_data_uint16(filename, linear_k_bias, SIZE_SIGLIP_ENCODER_LINEAR_BIAS, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LINEAR_BIAS << " values" << endl;

	cout << "HOST-Info: Generating data for linear_v_weight ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for linear_q_weight array" << endl << endl;
		return EXIT_FAILURE;
	}
	linear_v_weight = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.self_attn.v_proj.weight.bin");
	load_data_uint16(filename, linear_v_weight, SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for linear_v_bias ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LINEAR_BIAS*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for layernorm1_bias array" << endl << endl;
		return EXIT_FAILURE;
	}
	linear_v_bias = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.self_attn.v_proj.bias.bin");
	load_data_uint16(filename, linear_v_bias, SIZE_SIGLIP_ENCODER_LINEAR_BIAS, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LINEAR_BIAS << " values" << endl;
	///////////////////////////////////////////////////////
	cout << "HOST-Info: Generating data for layernorm2_weight ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for layernorm2_weight array" << endl << endl;
		return EXIT_FAILURE;
	}
	layernorm2_weight = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.layer_norm2.weight.bin");
	load_data_uint16(filename, layernorm2_weight, SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for layernorm2_bias ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for layernorm2_bias array" << endl << endl;
		return EXIT_FAILURE;
	}
	layernorm2_bias = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.layer_norm2.bias.bin");
	load_data_uint16(filename, layernorm2_bias, SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS << " values" << endl;
	///////////////////////////////////////////////////////
	cout << "HOST-Info: Generating data for attn_out_weight ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_ATTENTION_OUT_WEIGHT*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for attn_out_weight array" << endl << endl;
		return EXIT_FAILURE;
	}
	attn_out_weight = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.self_attn.out_proj.weight.bin");
	load_data_uint16(filename, attn_out_weight, SIZE_SIGLIP_ENCODER_ATTENTION_OUT_WEIGHT, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_ATTENTION_OUT_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for attn_out_bias ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_ATTENTION_OUT_BIAS*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for attn_out_bias array" << endl << endl;
		return EXIT_FAILURE;
	}
	attn_out_bias = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.self_attn.out_proj.bias.bin");
	load_data_uint16(filename, attn_out_bias, SIZE_SIGLIP_ENCODER_ATTENTION_OUT_BIAS, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_ATTENTION_OUT_BIAS << " values" << endl;
    ///////////////////////////////////////////////////////////////

	cout << "HOST-Info: Generating data for weight ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_MLP_FC1_WEIGHT*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for weight array" << endl << endl;
		return EXIT_FAILURE;
	}
	mlp_weight1 = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.mlp.fc1.weight.bin");
	load_data_uint16(filename, mlp_weight1, SIZE_SIGLIP_ENCODER_MLP_FC1_WEIGHT, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_MLP_FC1_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for bias ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_MLP_FC1_BIAS*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for bias array" << endl << endl;
		return EXIT_FAILURE;
	}
	mlp_bias1 = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.mlp.fc1.bias.bin");
	load_data_uint16(filename, mlp_bias1, SIZE_SIGLIP_ENCODER_MLP_FC1_BIAS, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_MLP_FC1_BIAS << " values" << endl;

	cout << "HOST-Info: Generating data for weight ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_MLP_FC2_WEIGHT*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for weight array" << endl << endl;
		return EXIT_FAILURE;
	}
	mlp_weight2 = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.mlp.fc2.weight.bin");
	load_data_uint16(filename, mlp_weight2, SIZE_SIGLIP_ENCODER_MLP_FC2_WEIGHT, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_MLP_FC2_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for bias ... ";
	if (posix_memalign(&ptr,4096,SIZE_SIGLIP_ENCODER_MLP_FC2_BIAS*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for bias array" << endl << endl;
		return EXIT_FAILURE;
	}
	mlp_bias2 = reinterpret_cast<uint16*>(ptr);
	filename = wpath("vision_tower._vision_tower.vision_model.encoder.layers.0.mlp.fc2.bias.bin");
	load_data_uint16(filename, mlp_bias2, SIZE_SIGLIP_ENCODER_MLP_FC2_BIAS, 0);
	cout << "Generated " << SIZE_SIGLIP_ENCODER_MLP_FC2_BIAS << " values" << endl;
	/////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "HOST-Info: Generating data for weight1 ... ";
	if (posix_memalign(&ptr,4096,CONNECTOR_0_WEIGHT*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for in array" << endl << endl;
		return EXIT_FAILURE;
	}
    _0_weight = reinterpret_cast<uint16*>(ptr);
	filename = wpath("connector._connector.0.weight.bin");
	load_data_uint16(filename, _0_weight, CONNECTOR_0_WEIGHT, 0);
	cout << "Generated " << CONNECTOR_0_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for bias1 ... ";
	if (posix_memalign(&ptr,4096,CONNECTOR_0_BIAS*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for bias array" << endl << endl;
		return EXIT_FAILURE;
	}
	_0_bias = reinterpret_cast<uint16*>(ptr);
	filename = wpath("connector._connector.0.bias.bin");
	load_data_uint16(filename, _0_bias, CONNECTOR_0_BIAS, 0);
	cout << "Generated " << CONNECTOR_0_BIAS << " values" << endl;

	cout << "HOST-Info: Generating data for weight2 ... ";
	if (posix_memalign(&ptr,4096,CONNECTOR_2_WEIGHT*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for in array" << endl << endl;
		return EXIT_FAILURE;
	}
	_2_weight = reinterpret_cast<uint16*>(ptr);
	filename = wpath("connector._connector.2.weight.bin");
	load_data_uint16(filename, _2_weight, CONNECTOR_2_WEIGHT, 0);
	cout << "Generated " << CONNECTOR_2_WEIGHT << " values" << endl;

	cout << "HOST-Info: Generating data for bias2 ... ";
	if (posix_memalign(&ptr,4096,CONNECTOR_2_BIAS*sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for bias array" << endl << endl;
		return EXIT_FAILURE;
	}
	_2_bias = reinterpret_cast<uint16*>(ptr);
	filename = wpath("connector._connector.2.bias.bin");
	load_data_uint16(filename, _2_bias, CONNECTOR_2_BIAS, 0);
	cout << "Generated " << CONNECTOR_2_BIAS << " values" << endl;


    /////////////////////////////////////////////////////////////////////////////////////////////////////

//	cout << "HOST-Info: Allocating memory for Siglip_out ... ";
//	if (posix_memalign(&ptr,4096,CONNECTOR_OUT*sizeof(fixed32_14))) {
//		cout << endl << "HOST-Error: Out of Memory during memory allocation for Siglip_out array" << endl << endl;
//		return EXIT_FAILURE;
//	}
//	Siglip_out = reinterpret_cast<fixed32_14*>(ptr);
//
//	cout << endl;

	// ------------------------------------------------------------------
	// TODO Step 4.2: Create Buffers in Global Memory to store data
	// ------------------------------------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Allocating buffers in Global Memory to store Input and Output Data ..." << endl;
	#endif

//	cl_mem GlobMem_BUF_Siglip_in,
	// cl_mem GlobMem_BUF_layernorm1_weight, GlobMem_BUF_layernorm1_bias,
	// 	   GlobMem_BUF_linear_q_weight  , GlobMem_BUF_linear_q_bias,
	// 	   GlobMem_BUF_linear_k_weight  , GlobMem_BUF_linear_k_bias,
	// 	   GlobMem_BUF_linear_v_weight  , GlobMem_BUF_linear_v_bias,
	// 	   GlobMem_BUF_layernorm2_weight, GlobMem_BUF_layernorm2_bias,
	// 	   GlobMem_BUF_attn_out_weight  , GlobMem_BUF_attn_out_bias,
	// 	   GlobMem_BUF_mlp_weight1, GlobMem_BUF_mlp_bias1, GlobMem_BUF_mlp_weight2, GlobMem_BUF_mlp_bias2,
	// 	   GlobMem_BUF_1, GlobMem_BUF_2, GlobMem_BUF_3, GlobMem_BUF_4, GlobMem_BUF_5, GlobMem_BUF_6, GlobMem_BUF_7;

	// Allocate Global Memory
	// .......................................................
//	GlobMem_BUF_Siglip_in         = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_LAYERNORM_IN * sizeof(fixed32_14), Siglip_in, &errCode);
	GlobMem_BUF_layernorm1_weight = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT * sizeof(uint16), layernorm1_weight, &errCode);
	GlobMem_BUF_layernorm1_bias   = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS * sizeof(uint16), layernorm1_bias, &errCode);
	GlobMem_BUF_linear_q_weight   = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT * sizeof(uint16), linear_q_weight, &errCode);
	GlobMem_BUF_linear_q_bias     = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_LINEAR_BIAS * sizeof(uint16), linear_q_bias, &errCode);
	GlobMem_BUF_linear_k_weight   = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT * sizeof(uint16), linear_k_weight, &errCode);
	GlobMem_BUF_linear_k_bias     = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_LINEAR_BIAS * sizeof(uint16), linear_k_bias, &errCode);
	GlobMem_BUF_linear_v_weight   = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_LINEAR_WEIGHT * sizeof(uint16), linear_v_weight, &errCode);
	GlobMem_BUF_linear_v_bias     = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_LINEAR_BIAS * sizeof(uint16), linear_v_bias, &errCode);
    GlobMem_BUF_layernorm2_weight = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_LAYERNORM_WEIGHT * sizeof(uint16), layernorm2_weight, &errCode);
	GlobMem_BUF_layernorm2_bias   = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_LAYERNORM_BIAS * sizeof(uint16), layernorm2_bias, &errCode);
    GlobMem_BUF_attn_out_weight   = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_ATTENTION_OUT_WEIGHT * sizeof(uint16), attn_out_weight, &errCode);
	GlobMem_BUF_attn_out_bias     = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_ATTENTION_OUT_BIAS * sizeof(uint16), attn_out_bias, &errCode);
	GlobMem_BUF_mlp_weight1 	  = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_MLP_FC1_WEIGHT * sizeof(uint16), mlp_weight1, &errCode);
	GlobMem_BUF_mlp_bias1 		  = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_MLP_FC1_BIAS * sizeof(uint16), mlp_bias1, &errCode);
	GlobMem_BUF_mlp_weight2 	  = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_MLP_FC2_WEIGHT * sizeof(uint16), mlp_weight2, &errCode);
	GlobMem_BUF_mlp_bias2 		  = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_MLP_FC2_BIAS * sizeof(uint16), mlp_bias2, &errCode);

    GlobMem_BUF_0_weight          = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, CONNECTOR_0_WEIGHT * sizeof(uint16), _0_weight, &errCode);
	GlobMem_BUF_0_bias            = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, CONNECTOR_0_BIAS * sizeof(uint16), _0_bias, &errCode);
	GlobMem_BUF_2_weight          = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, CONNECTOR_2_WEIGHT * sizeof(uint16), _2_weight, &errCode);
	GlobMem_BUF_2_bias            = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, CONNECTOR_2_BIAS * sizeof(uint16), _2_bias, &errCode);

	GlobMem_BUF_1                = clCreateBuffer(Context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, SIZE_SIGLIP_ENCODER_LAYERNORM_IN * sizeof(fixed32_14), Siglip_in, &errCode);
	GlobMem_BUF_2                = clCreateBuffer(Context, CL_MEM_READ_WRITE, SIZE_SIGLIP_ENCODER_LAYERNORM_OUT * sizeof(fixed32_14), NULL, &errCode);
	GlobMem_BUF_3                = clCreateBuffer(Context, CL_MEM_READ_WRITE, SIZE_SIGLIP_ENCODER_LINEAR_OUT * sizeof(fixed32_14), NULL, &errCode);
	GlobMem_BUF_4                = clCreateBuffer(Context, CL_MEM_READ_WRITE, SIZE_SIGLIP_ENCODER_LINEAR_OUT * sizeof(fixed32_14), NULL, &errCode);
	GlobMem_BUF_5                = clCreateBuffer(Context, CL_MEM_READ_WRITE, SIZE_SIGLIP_ENCODER_LINEAR_OUT * sizeof(fixed32_14), NULL, &errCode);
	GlobMem_BUF_6                = clCreateBuffer(Context, CL_MEM_READ_WRITE, SIZE_SIGLIP_ENCODER_LINEAR_OUT * sizeof(fixed32_14), NULL, &errCode);
	GlobMem_BUF_7                = clCreateBuffer(Context, CL_MEM_READ_WRITE, SIZE_SIGLIP_ENCODER_LINEAR_OUT * sizeof(fixed32_14), NULL, &errCode);
    GlobMem_BUF_8                = clCreateBuffer(Context, CL_MEM_READ_WRITE, CONNECTOR_OUT * sizeof(fixed32_14), NULL, &errCode);

	// ============================================================================
	// TODO Step 5: Set Kernel Arguments and Run the Application
	//         o) Set Kernel Arguments
	//         o) Submit Kernels for Execution
	//         o) Copy Results from Global Memory to Host
	// ============================================================================
	// int Nb_Of_Mem_Events = 24,
	// 	Nb_Of_Exe_Events = 9;

	// cl_event Mem_op_event[Nb_Of_Mem_Events],
	//           K_exe_event[Nb_Of_Exe_Events];


	#ifdef ALL_MESSAGES
	cout << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	cout << "HOST-Info: (Step 5) Run Application                                      " << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	#endif


	// ----------------------------------------
	// TODO Step 5.1: Set Kernel Arguments
	// ----------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Setting Kernel arguments ...f" << endl;
	#endif
	errCode  = false;

	errCode |= clSetKernelArg(K_Siglip_copy,      0, sizeof(cl_mem),  &GlobMem_BUF_6);
	errCode |= clSetKernelArg(K_Siglip_copy,      1, sizeof(cl_mem),  &GlobMem_BUF_1);
	if (errCode != CL_SUCCESS) {
		cout << endl << "Host-ERROR: Failed to set K_Siglip_copy arguments" << endl << endl;
		return EXIT_FAILURE;
	}
	errCode |= clSetKernelArg(K_Siglip_layernorm,      0, sizeof(cl_mem),  &GlobMem_BUF_2);
	errCode |= clSetKernelArg(K_Siglip_layernorm,      1, sizeof(cl_mem),  &GlobMem_BUF_1);
	errCode |= clSetKernelArg(K_Siglip_layernorm,      2, sizeof(cl_mem),  &GlobMem_BUF_layernorm1_weight);
	errCode |= clSetKernelArg(K_Siglip_layernorm,      3, sizeof(cl_mem),  &GlobMem_BUF_layernorm1_bias);
	if (errCode != CL_SUCCESS) {
		cout << endl << "Host-ERROR: Failed to set K_Siglip_layernorm arguments" << endl << endl;
		return EXIT_FAILURE;
	}
	errCode |= clSetKernelArg(K_Siglip_linear,         0, sizeof(cl_mem),  &GlobMem_BUF_3);
	errCode |= clSetKernelArg(K_Siglip_linear,         1, sizeof(cl_mem),  &GlobMem_BUF_4);
	errCode |= clSetKernelArg(K_Siglip_linear,         2, sizeof(cl_mem),  &GlobMem_BUF_5);
	errCode |= clSetKernelArg(K_Siglip_linear,         3, sizeof(cl_mem),  &GlobMem_BUF_2);
	errCode |= clSetKernelArg(K_Siglip_linear,         4, sizeof(cl_mem),  &GlobMem_BUF_linear_q_weight);
	errCode |= clSetKernelArg(K_Siglip_linear,         5, sizeof(cl_mem),  &GlobMem_BUF_linear_q_bias);
	errCode |= clSetKernelArg(K_Siglip_linear,         6, sizeof(cl_mem),  &GlobMem_BUF_linear_k_weight);
	errCode |= clSetKernelArg(K_Siglip_linear,         7, sizeof(cl_mem),  &GlobMem_BUF_linear_k_bias);
	errCode |= clSetKernelArg(K_Siglip_linear,         8, sizeof(cl_mem),  &GlobMem_BUF_linear_v_weight);
	errCode |= clSetKernelArg(K_Siglip_linear,         9, sizeof(cl_mem),  &GlobMem_BUF_linear_v_bias);
	if (errCode != CL_SUCCESS) {
		cout << endl << "Host-ERROR: Failed to set K_Siglip_linear arguments" << endl << endl;
		return EXIT_FAILURE;
	}
    errCode |= clSetKernelArg(K_Siglip_attention,      0, sizeof(cl_mem),  &GlobMem_BUF_7);
    errCode |= clSetKernelArg(K_Siglip_attention,      1, sizeof(cl_mem),  &GlobMem_BUF_3);
    errCode |= clSetKernelArg(K_Siglip_attention,      2, sizeof(cl_mem),  &GlobMem_BUF_4);
    errCode |= clSetKernelArg(K_Siglip_attention,      3, sizeof(cl_mem),  &GlobMem_BUF_5);
	errCode |= clSetKernelArg(K_Siglip_attention,      4, sizeof(cl_mem),  &GlobMem_BUF_attn_out_weight);
	errCode |= clSetKernelArg(K_Siglip_attention,      5, sizeof(cl_mem),  &GlobMem_BUF_attn_out_bias);
	if (errCode != CL_SUCCESS) {
		cout << endl << "Host-ERROR: Failed to set K_Siglip_attention arguments" << endl << endl;
		return EXIT_FAILURE;
	}
    errCode |= clSetKernelArg(K_Siglip_residual,       0, sizeof(cl_mem),  &GlobMem_BUF_1);
    errCode |= clSetKernelArg(K_Siglip_residual,       1, sizeof(cl_mem),  &GlobMem_BUF_6);
    errCode |= clSetKernelArg(K_Siglip_residual,       2, sizeof(cl_mem),  &GlobMem_BUF_7);
    if (errCode != CL_SUCCESS) {
		cout << endl << "Host-ERROR: Failed to set K_Siglip_residual arguments" << endl << endl;
		return EXIT_FAILURE;
	}
	errCode |= clSetKernelArg(K_Siglip_MLP,            0, sizeof(cl_mem),  &GlobMem_BUF_7);
	errCode |= clSetKernelArg(K_Siglip_MLP,            1, sizeof(cl_mem),  &GlobMem_BUF_2);
	errCode |= clSetKernelArg(K_Siglip_MLP,            2, sizeof(cl_mem),  &GlobMem_BUF_mlp_weight1);
	errCode |= clSetKernelArg(K_Siglip_MLP,            3, sizeof(cl_mem),  &GlobMem_BUF_mlp_bias1);
	errCode |= clSetKernelArg(K_Siglip_MLP,            4, sizeof(cl_mem),  &GlobMem_BUF_mlp_weight2);
	errCode |= clSetKernelArg(K_Siglip_MLP,            5, sizeof(cl_mem),  &GlobMem_BUF_mlp_bias2);
	if (errCode != CL_SUCCESS) {
		cout << endl << "Host-ERROR: Failed to set K_Siglip_MLP arguments" << endl << endl;
		return EXIT_FAILURE;
	}

    errCode |= clSetKernelArg(K_Connector,             0, sizeof(cl_mem),  &GlobMem_BUF_8);
    if (errCode != CL_SUCCESS) {
		cout << endl << "Host-ERROR: 1" << endl << endl;
		return EXIT_FAILURE;
	}
	errCode |= clSetKernelArg(K_Connector,             1, sizeof(cl_mem),  &GlobMem_BUF_1); // full 729-token output; Connector kernel skips token 0 itself
	if (errCode != CL_SUCCESS) {
		cout << endl << "Host-ERROR: 2" << endl << endl;
		return EXIT_FAILURE;
	}
	errCode |= clSetKernelArg(K_Connector,             2, sizeof(cl_mem),  &GlobMem_BUF_0_weight);
	if (errCode != CL_SUCCESS) {
		cout << endl << "Host-ERROR: 3" << endl << endl;
		return EXIT_FAILURE;
	}
	errCode |= clSetKernelArg(K_Connector,             3, sizeof(cl_mem),  &GlobMem_BUF_0_bias);
	if (errCode != CL_SUCCESS) {
		cout << endl << "Host-ERROR: 4" << endl << endl;
		return EXIT_FAILURE;
	}
	errCode |= clSetKernelArg(K_Connector,             4, sizeof(cl_mem),  &GlobMem_BUF_2_weight);
	if (errCode != CL_SUCCESS) {
		cout << endl << "Host-ERROR: 5" << endl << endl;
		return EXIT_FAILURE;
	}
	errCode |= clSetKernelArg(K_Connector,             5, sizeof(cl_mem),  &GlobMem_BUF_2_bias);

	if (errCode != CL_SUCCESS) {
		cout << endl << "Host-ERROR: Failed to set K_Connector arguments" << endl << endl;
		return EXIT_FAILURE;
	}

	// ------------------------------------------------------
	// TODO Step 5.2: Copy Input data from Host to Global Memory
	// ------------------------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST_Info: Copy Input data to Global Memory ..." << endl;
	#endif
//	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_Siglip_in,         0, 0, NULL, &Mem_op_event[0]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_1,                 0, 0, NULL, &Mem_op_event[0]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_layernorm1_weight, 0, 0, NULL, &Mem_op_event[1]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_layernorm1_bias,   0, 0, NULL, &Mem_op_event[2]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_linear_q_weight,   0, 0, NULL, &Mem_op_event[3]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_linear_q_bias,     0, 0, NULL, &Mem_op_event[4]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_linear_k_weight,   0, 0, NULL, &Mem_op_event[5]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_linear_k_bias,     0, 0, NULL, &Mem_op_event[6]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_linear_v_weight,   0, 0, NULL, &Mem_op_event[7]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_linear_v_bias,     0, 0, NULL, &Mem_op_event[8]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_layernorm2_weight, 0, 0, NULL, &Mem_op_event[9]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_layernorm2_bias,   0, 0, NULL, &Mem_op_event[10]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_attn_out_weight,   0, 0, NULL, &Mem_op_event[11]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_attn_out_bias,     0, 0, NULL, &Mem_op_event[12]);

	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_mlp_weight1, 0, 0, NULL, &Mem_op_event[13]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_mlp_bias1, 0, 0, NULL, &Mem_op_event[14]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_mlp_weight2, 0, 0, NULL, &Mem_op_event[15]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_mlp_bias2, 0, 0, NULL, &Mem_op_event[16]);

    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_0_weight, 0, 0, NULL, &Mem_op_event[17]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_0_bias, 0, 0, NULL, &Mem_op_event[18]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_2_weight, 0, 0, NULL, &Mem_op_event[19]);
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_2_bias, 0, 0, NULL, &Mem_op_event[20]);

	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_2, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[21]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_3, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[22]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_4, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[23]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_5, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[24]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_6, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[25]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_7, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[26]);
    errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_8, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[27]);
	// --------------------------------------------------------
	// Out-of-order queue: layer-0 kernels must not start before the input/weights are on the device.
	errCode = clEnqueueBarrier (Command_Queue);
	if (errCode != CL_SUCCESS) {
		cout << endl << "HOST-Error: Failed to Submit BarrierWithWaitList" << endl << endl;
		return EXIT_FAILURE;
	}

	// ----------------------------------------
	// TODO Step 5.3: Submit Kernels for Execution
	// ----------------------------------------

	cout << "HOST-Info: Submitting Kernel ..." << endl;
	errCode = clEnqueueTask(Command_Queue, K_Siglip_copy,      0,            NULL, &K_exe_event[0]);
    errCode = clEnqueueTask(Command_Queue, K_Siglip_layernorm, 1, &K_exe_event[0], &K_exe_event[1]);
	errCode = clEnqueueTask(Command_Queue, K_Siglip_linear,    1, &K_exe_event[1], &K_exe_event[2]);
	errCode = clEnqueueTask(Command_Queue, K_Siglip_attention, 1, &K_exe_event[2], &K_exe_event[3]);
	errCode = clEnqueueTask(Command_Queue, K_Siglip_residual,  1, &K_exe_event[3], &K_exe_event[4]);
	errCode = clEnqueueTask(Command_Queue, K_Siglip_copy,      1, &K_exe_event[4], &K_exe_event[5]);

	errCode |= clSetKernelArg(K_Siglip_layernorm,      0, sizeof(cl_mem),  &GlobMem_BUF_2);
	errCode |= clSetKernelArg(K_Siglip_layernorm,      1, sizeof(cl_mem),  &GlobMem_BUF_1);
	errCode |= clSetKernelArg(K_Siglip_layernorm,      2, sizeof(cl_mem),  &GlobMem_BUF_layernorm2_weight);
	errCode |= clSetKernelArg(K_Siglip_layernorm,      3, sizeof(cl_mem),  &GlobMem_BUF_layernorm2_bias);
	errCode = clEnqueueTask(Command_Queue, K_Siglip_layernorm, 1, &K_exe_event[5], &K_exe_event[6]);

	errCode = clEnqueueTask(Command_Queue, K_Siglip_MLP,       1, &K_exe_event[6], &K_exe_event[7]);
	errCode = clEnqueueTask(Command_Queue, K_Siglip_residual,  1, &K_exe_event[7], &K_exe_event[8]);

	// errCode = clEnqueueBarrierWithWaitList (Command_Queue, 0, NULL, NULL);
	// if (errCode != CL_SUCCESS) {
	// 	cout << endl << "HOST-Error: Failed to Submit BarrierWithWaitList" << endl << endl;
	// 	return EXIT_FAILURE;
	// }
	//cout << "clEnqueueBarrier" << endl;
	errCode = clEnqueueBarrier (Command_Queue);
	//cout << "clEnqueueBarrier finish" << endl;
	///////////////////////////////////////////////////////////////////////////////////////////////////
	/**/
	for(int i = 1; i < layer_num; i++){
		cout << "layer_id = " << i << endl;
		// The weight buffers use CL_MEM_USE_HOST_PTR: wait until the previous layer has finished
		// (including its weight migrations) before overwriting the host copies with layer i.
		clFinish(Command_Queue);
		prepare_data_for_one_layer(i);
		run_one_layer(i);
		errCode = clEnqueueBarrier (Command_Queue);
	}

	cout << "HOST-Info: Allocating memory for Siglip_out ... ";
	if (posix_memalign(&ptr,4096,CONNECTOR_OUT*sizeof(fixed32_14))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for Siglip_out array" << endl << endl;
		return EXIT_FAILURE;
	}
	Siglip_out = reinterpret_cast<fixed32_14*>(ptr);

	cout << endl;

    errCode = clEnqueueTask(Command_Queue, K_Connector,       1, &K_exe_event[Nb_Of_Exe_Events - 2], &K_exe_event[Nb_Of_Exe_Events - 1]);

	/*

	*//////////////////////////////////////////////////////////////////////////////////////////////////


	// ---------------------------------------------------------
	// TODO Step 5.4: Submit Copy Results from Global Memory to Host
	// ---------------------------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST_Info: Submitting Copy Results data from Global Memory to Host ..." << endl;
	#endif
	errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &GlobMem_BUF_8, CL_MIGRATE_MEM_OBJECT_HOST, 1, &K_exe_event[Nb_Of_Exe_Events - 1], &Mem_op_event[Nb_Of_Mem_Events - 1]);

    cout << endl << "HOST_Info: Waiting for application to be completed ..." << endl;
	clFinish(Command_Queue);
	clEnqueueReadBuffer(Command_Queue, GlobMem_BUF_8, CL_TRUE, 0, CONNECTOR_OUT * sizeof(fixed32_14), Siglip_out, 0, NULL, NULL);

	// Device work is done, the MLP host buffers can be released now (they were freed before
	// the kernels finished in the original code).
	free(mlp_weight1);
	free(mlp_weight2);
	free(mlp_bias1);
	free(mlp_bias2);

	if (image_features != nullptr) {
		for (int i = 0; i < CONNECTOR_OUT; i++) image_features[i] = (float)Siglip_out[i];
	} else {

	// ============================================================================
	// Step 6: Processing Output Results
	//         o) Store output results to a RES.txt file
	//         o) Check correctness of the output results
	// ============================================================================
	#ifdef ALL_MESSAGES
	cout << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	cout << "HOST-Info: (Step 6) Store and Check the Output Results                   " << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	#endif

	// ------------------------------------------------------
	// TODO Step 6.1: Store output Result to the RES.txt file
	// ------------------------------------------------------
	char Output_File_Name[] = "/home/undergraduate/zehuang24/Test_data_16/out/Connector_output.txt";
	cout << "HOST_Info: Store output results in" << Output_File_Name << endl;

	fstream RES_File;
	RES_File.open(Output_File_Name,ios::out);
	if (! RES_File.is_open()) {
		cout << endl << "HOST-Error: Failed to open the " << Output_File_Name << " file for write" << endl << endl;
		return EXIT_FAILURE;
	}

	for (int i=0; i < CONNECTOR_OUT; i++) {
		RES_File << (float)Siglip_out[i] << endl;
	}
	RES_File.close();
	}  // image_features == nullptr

	// ============================================================================
	// TODO　Step 7: Custom Profiling
	// ============================================================================
	cout << "HOST-Info: ============================================================= " << endl;
	cout << "HOST-Info: (Step 7) Custom Profiling                                     " << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	int Nb_Of_Kernels = Nb_Of_Exe_Events;
	int Nb_Of_Memory_Tranfers = Nb_Of_Mem_Events;

	string list_of_kernel_names[Nb_Of_Kernels]={"K_Siglip_layernorm", "K_Siglip_linear", "K_Siglip_attention", "K_Siglip_residual", "K_Siglip_layernorm", "K_Siglip_MLP"};
	run_custom_profiling (Nb_Of_Kernels,Nb_Of_Memory_Tranfers,K_exe_event,Mem_op_event,list_of_kernel_names);

	// ============================================================================
	// TODO Step 8: Release Allocated Resources
	// ============================================================================
	clReleaseDevice(Target_Device_ID); // Only available in OpenCL >= 1.2

	for (int i=0; i<Nb_Of_Mem_Events; i++) clReleaseEvent(Mem_op_event[i]);
	for (int i=0; i<Nb_Of_Exe_Events; i++) clReleaseEvent(K_exe_event[i]);

//	clReleaseMemObject(GlobMem_BUF_Siglip_in);
	clReleaseMemObject(GlobMem_BUF_layernorm1_weight);
	clReleaseMemObject(GlobMem_BUF_layernorm1_bias);
	clReleaseMemObject(GlobMem_BUF_1);
    clReleaseMemObject(GlobMem_BUF_2);
    clReleaseMemObject(GlobMem_BUF_3);
    clReleaseMemObject(GlobMem_BUF_4);
    clReleaseMemObject(GlobMem_BUF_5);
    clReleaseMemObject(GlobMem_BUF_6);
    clReleaseMemObject(GlobMem_BUF_7);
    clReleaseMemObject(GlobMem_BUF_8);
    clReleaseMemObject(GlobMem_BUF_linear_q_weight);
    clReleaseMemObject(GlobMem_BUF_linear_q_bias);
    clReleaseMemObject(GlobMem_BUF_linear_k_weight);
    clReleaseMemObject(GlobMem_BUF_linear_k_bias);
    clReleaseMemObject(GlobMem_BUF_linear_v_weight);
    clReleaseMemObject(GlobMem_BUF_linear_v_bias);
	clReleaseMemObject(GlobMem_BUF_layernorm2_weight);
	clReleaseMemObject(GlobMem_BUF_layernorm2_bias);
	clReleaseMemObject(GlobMem_BUF_attn_out_weight);
	clReleaseMemObject(GlobMem_BUF_attn_out_bias);
	clReleaseMemObject(GlobMem_BUF_mlp_weight1);
	clReleaseMemObject(GlobMem_BUF_mlp_bias1);
	clReleaseMemObject(GlobMem_BUF_mlp_weight2);
	clReleaseMemObject(GlobMem_BUF_mlp_bias2);
    clReleaseMemObject(GlobMem_BUF_0_weight);
	clReleaseMemObject(GlobMem_BUF_0_bias);
	clReleaseMemObject(GlobMem_BUF_2_weight);
	clReleaseMemObject(GlobMem_BUF_2_bias);

	clReleaseKernel(K_Siglip_layernorm);
    clReleaseKernel(K_Siglip_linear);
    clReleaseKernel(K_Siglip_attention);
	clReleaseKernel(K_Siglip_residual);
	clReleaseKernel(K_Siglip_MLP);
	clReleaseKernel(K_Siglip_copy);
    clReleaseKernel(K_Connector);

	clReleaseProgram(Program);
	clReleaseCommandQueue(Command_Queue);
	clReleaseContext(Context);

	free(Platform_IDs);
	free(Device_IDs);
	free(Siglip_in);
    free(Siglip_out);
	free(layernorm1_weight);
	free(layernorm1_bias);
    free(linear_q_weight);
	free(linear_q_bias);
	free(linear_k_weight);
	free(linear_k_bias);
	free(linear_v_weight);
	free(linear_v_bias);
	free(layernorm2_weight);
	free(layernorm2_bias);
	free(attn_out_weight);
	free(attn_out_bias);
//	free(mlp_weight1);
//	free(mlp_weight2);
//	free(mlp_bias1);
//	free(mlp_bias2);
    free(_0_weight);
	free(_0_bias);
	free(_2_weight);
	free(_2_bias);

	cout << endl << "HOST-Info: DONE" << endl << endl;

	return EXIT_SUCCESS;
}

}  // namespace siglip_host

#ifndef TINYLLAVA_LIB
// Standalone run (original behaviour): reads Siglip_embedding_output.bin, writes Connector_output.txt
//   host_Siglip_v2 <Platform_Vendor> <Device_Name> <XCLBIN_File> [weight_dir]
int main(int argc, char* argv[])
{
	if (argc < 4) {
		std::cout << "HOST-Info:  Usage: " << argv[0]
		          << " <Platform_Vendor> <Device_Name> <XCLBIN_File> [weight_dir]" << std::endl;
		return EXIT_FAILURE;
	}
	return siglip_host::run_siglip_connector(argv[1], argv[2], argv[3], nullptr, nullptr,
	                                         argc > 4 ? argv[4] : "");
}
#endif

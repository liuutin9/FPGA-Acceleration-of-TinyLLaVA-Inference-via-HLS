/*******************************************************************************
** HOST Code
*******************************************************************************/

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
#include <cmath>
#include <ap_fixed.h>
#include <vector>
#include <hls_half.h>
#include <ap_int.h>
#include "half.hpp"
#include "tokenizers_c.h"
#include "tokenizers_cpp.h"

typedef ap_fixed<32,14> fixed32_14;
typedef ap_fixed<24,10> fixed24_10;
typedef ap_fixed<16,10> fixed16_10;
typedef ap_uint<16>  uint16;

using namespace std;

#define ALL_MESSAGES

#define PHI_HIDDEN_SIZE 2560
#define PHI_INTERMEDIATE_SIZE 10240
#define PHI_NUM_DECODER_LAYERS 32
#define PHI_VOCAB_SIZE 51200
#define PHI_EOS_TOKEN_ID 50256
#define PHI_SLEN 832

#define OCL_CHECK(error, call)                                                                   	 \
    do {                                                                                             \
        call;                                                                                        \
        if (error != CL_SUCCESS) {                                                                   \
            printf("%s:%d Error calling " #call ", error code is: %d\n", __FILE__, __LINE__, error); \
            exit(EXIT_FAILURE);                                                                      \
        }                                                                                            \
    } while (0)

string weight_path;
string weight_path_pre;
string weight_path_post;
string weight_folder_path = "/user/undergraduate/ytliu24/phi_workspace/weights/";
string phi_embed_tokens_weight = "language_model_model_embed_tokens_weight.bin";
string phi_decoder_layer_filename_prefix = "language_model_model_layers_";
string phi_input_layernorm_weight_filename_postfix = "_input_layernorm_weight.bin";
string phi_input_layernorm_bias_filename_postfix = "_input_layernorm_bias.bin";
string phi_q_proj_weight_filename_postfix = "_self_attn_q_proj_weight.bin";
string phi_q_proj_bias_filename_postfix = "_self_attn_q_proj_bias.bin";
string phi_k_proj_weight_filename_postfix = "_self_attn_k_proj_weight.bin";
string phi_k_proj_bias_filename_postfix = "_self_attn_k_proj_bias.bin";
string phi_v_proj_weight_filename_postfix = "_self_attn_v_proj_weight.bin";
string phi_v_proj_bias_filename_postfix = "_self_attn_v_proj_bias.bin";
string phi_dense_weight_filename_postfix = "_self_attn_dense_weight.bin";
string phi_dense_bias_filename_postfix = "_self_attn_dense_bias.bin";

char filename_buffer[256];

// =========================================
// Helper Function: Read txt file
// =========================================
int readTxtFile(const char *filename, string &content) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return 1;
    }
    content.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return 0;
}

// =========================================
// Helper Function: Read binary file
// =========================================
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

int loadData_uint16(uint16* out, int len_offset, int length, const char *filename) {
	vector<char> binary;
	if (readBinaryFile(filename, binary, len_offset * 2, length * 2) != 0) {
		return -1;
	}
	return binaryToUint16(out, binary);
}

int wordEmbed(fixed32_14* out, uint16* in) {
	half_float::half h;
	for (int i = 0; i < PHI_HIDDEN_SIZE; i++) {
		memcpy(&h, &in[i], sizeof(uint16));
		out[i] = float(h);
	}
}

// =========================================
// Helper Function: Initialize tokenizer
// =========================================
int initTokenizer(const string tokenizer_json_path, unique_ptr<tokenizers::Tokenizer> &tokenizer) {
    std::ifstream ifs(tokenizer_json_path);
    if (!ifs) {
        std::cerr << "Cannot open tokenizer file: " << tokenizer_json_path << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << ifs.rdbuf();
    std::string json_content = buffer.str();

    tokenizer = tokenizers::Tokenizer::FromBlobJSON(json_content);

    if (!tokenizer) {
        std::cerr << "Failed to load tokenizer from JSON\n";
        return -1;
    }

    return 0;
}

// =========================================
// Helper Function: Loads program to memory
// =========================================
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
	// Profiling
	// ---------------------------------
	profile_t *PROFILE;

	PROFILE = new profile_t[Nb_Of_Kernels + Nb_Of_Memory_Tranfers];

	PROFILE[0].action_type="kernel";  PROFILE[0].name="kernel_phi_linear";  PROFILE[0].event = K_exe_event[0];

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

// ********************************************************************************** //
// ---------------------------------------------------------------------------------- //
//                          M A I N    F U N C T I O N                                //
// ---------------------------------------------------------------------------------- //
// ********************************************************************************** //

int main(int argc, char* argv[])
{
	cout << endl;


	// ============================================================================
	// Step 1: Check Command Line Arguments
	// ============================================================================
	//    o) argv[1] Platfrom Vendor
	//    o) argv[2] Device Name
	//    o) argv[3] XCLBIN file
	// ============================================================================
	#ifdef ALL_MESSAGES
	cout << "HOST-Info: ============================================================= " << endl;
	cout << "HOST-Info: (Step 1) Check Command Line Arguments                      " << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	#endif

	if (argc != 4)
	{
		cout << "HOST-Error: Incorrect command line syntax " << endl;
		cout << "HOST-Info:  Usage: " << argv[0] << " <Platform_Vendor> <Device_Name> <XCLBIN_File>  <Test Vectors Size>" << endl << endl;
		return EXIT_FAILURE;
	} 
 
	const char* Target_Platform_Vendor   = argv[1];
	const char* Target_Device_Name       = argv[2];
	const char* xclbinFilename           = argv[3];
	cout << "HOST-Info: Platform_Vendor   : " << Target_Platform_Vendor << endl;
	cout << "HOST-Info: Device_Name       : " << Target_Device_Name << endl;
	cout << "HOST-Info: XCLBIN_file       : " << xclbinFilename << endl;


	// ============================================================================
	// Step 2: Detect Target Platform and Target Device in a system. 
	//         Create Context and Command Queue.
	// ============================================================================
	// Variables:
	//   o) Target_Platform_Vendor[] - defined as main() input argument 
	//   o) Target_Device_Name[]     - defined as main() input argument
	// 
	// After that
	//   o) Create a Context
	//   o) Create a Command Queue
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
	cl_command_queue    Command_Queue;

	cl_int              errCode;
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

	// TODO
	// -------------------------------------------------------------
	// Step 3.4: Create a Kernels
	// -------------------------------------------------------------
	cl_kernel kernel_phi_q_proj, kernel_phi_k_proj, kernel_phi_v_proj, kernel_phi_dense;
	cl_kernel kernel_phi_layernorm, kernel_phi_rotary_embed, kernel_phi_attention, kernel_phi_mlp;
	cl_kernel kernel_phi_add_residual, kernel_phi_copy_q, kernel_phi_copy_k, kernel_phi_copy_v, kernel_phi_copy_residual;

	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Creating Kernels ..." << endl;
	#endif
	OCL_CHECK(errCode, kernel_phi_q_proj = clCreateKernel(Program, "kernel_phi_q_proj", &errCode));
	OCL_CHECK(errCode, kernel_phi_k_proj = clCreateKernel(Program, "kernel_phi_k_proj", &errCode));
	OCL_CHECK(errCode, kernel_phi_v_proj = clCreateKernel(Program, "kernel_phi_v_proj", &errCode));
	OCL_CHECK(errCode, kernel_phi_dense = clCreateKernel(Program, "kernel_phi_dense", &errCode));
	OCL_CHECK(errCode, kernel_phi_layernorm = clCreateKernel(Program, "kernel_phi_layernorm", &errCode));
	OCL_CHECK(errCode, kernel_phi_rotary_embed = clCreateKernel(Program, "kernel_phi_rotary_embed", &errCode));
	OCL_CHECK(errCode, kernel_phi_attention = clCreateKernel(Program, "kernel_phi_attention", &errCode));
	OCL_CHECK(errCode, kernel_phi_mlp = clCreateKernel(Program, "kernel_phi_mlp", &errCode));
	OCL_CHECK(errCode, kernel_phi_add_residual = clCreateKernel(Program, "kernel_phi_add_residual", &errCode));
	OCL_CHECK(errCode, kernel_phi_copy_q = clCreateKernel(Program, "kernel_phi_copy_q", &errCode));
	OCL_CHECK(errCode, kernel_phi_copy_k = clCreateKernel(Program, "kernel_phi_copy_k", &errCode));
	OCL_CHECK(errCode, kernel_phi_copy_v = clCreateKernel(Program, "kernel_phi_copy_v", &errCode));
	OCL_CHECK(errCode, kernel_phi_copy_residual = clCreateKernel(Program, "kernel_phi_copy_residual", &errCode));

	// TODO
	// ================================================================
	// Step 4: Prepare Data to Run Kernel
	// ================================================================
	//   o) Generate data for DataIn_1 array
	//   o) Generate data for DataIn_2 array
	//   o) Generate data for DataIn_3 array
	//   o) Allocate Memory to store the results: RES array
	//   o) Create Buffers in Global Memory to store data
	// ================================================================
	fixed32_14 *PHI_OUT, *PHI_IN;
	uint16 *PHI_PRE_LAYERNORM_WEIGHT[PHI_NUM_DECODER_LAYERS], *PHI_PRE_LAYERNORM_BIAS[PHI_NUM_DECODER_LAYERS];
	uint16 *PHI_Q_PROJ_WEIGHT[PHI_NUM_DECODER_LAYERS][2], *PHI_Q_PROJ_BIAS[PHI_NUM_DECODER_LAYERS][2];
	uint16 *PHI_K_PROJ_WEIGHT[PHI_NUM_DECODER_LAYERS][2], *PHI_K_PROJ_BIAS[PHI_NUM_DECODER_LAYERS][2];
	uint16 *PHI_V_PROJ_WEIGHT[PHI_NUM_DECODER_LAYERS][2], *PHI_V_PROJ_BIAS[PHI_NUM_DECODER_LAYERS][2];
	uint16 *PHI_DENSE_WEIGHT[PHI_NUM_DECODER_LAYERS][2], *PHI_DENSE_BIAS[PHI_NUM_DECODER_LAYERS][2];
	uint16 *PHI_MLP_FC1_WEIGHT[PHI_NUM_DECODER_LAYERS][8], *PHI_MLP_FC1_BIAS[PHI_NUM_DECODER_LAYERS][8];
	uint16 *PHI_MLP_FC2_WEIGHT[PHI_NUM_DECODER_LAYERS][8], *PHI_MLP_FC2_BIAS[PHI_NUM_DECODER_LAYERS][8];
	uint16 *PHI_LAST_LAYERNORM_WEIGHT, *PHI_LAST_LAYERNORM_BIAS;
	uint16 *PHI_LM_HEAD_WEIGHT, *PHI_LM_HEAD_BIAS;
	uint16 *PHI_EMBED_TOKENS_WEIGHT;

	#ifdef ALL_MESSAGES
	cout << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	cout << "HOST-Info: (Step 4) Prepare Data to Run Kernels                           " << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	#endif

	// ------------------------------------------------------------------
	// Step 4.1: Generate data for DataIn_1 array
	//           Generate data for DataIn_2 array
	//           Generate data for DataIn_3 array
	//           Allocate Memory to store the results: RES array
	// ------------------------------------------------------------------

	void *ptr=nullptr;

	cout << "HOST-Info: Allocating memory for PHI_IN ... ";
	if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE * sizeof(fixed32_14))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_IN array" << endl << endl;
		return EXIT_FAILURE;
	}
	PHI_IN = reinterpret_cast<fixed32_14*>(ptr);
	cout << "HOST_Info: Memory allocated for PHI_IN!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_OUT ... ";
	if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE * sizeof(fixed32_14))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_OUT array" << endl << endl;
		return EXIT_FAILURE;
	}
	PHI_OUT = reinterpret_cast<fixed32_14*>(ptr);
	cout << "HOST_Info: Memory allocated for PHI_OUT!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_PRE_LAYERNORM_WEIGHT ... " << endl;
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE * sizeof(uint16))) {
			cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_PRE_LAYERNORM_WEIGHT[" << i << "] array" << endl << endl;
			return EXIT_FAILURE;
		}
		PHI_PRE_LAYERNORM_WEIGHT[i] = reinterpret_cast<uint16*>(ptr);
		weight_path_pre = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_";
		weight_path_post = "_input_layernorm_weight.bin";
		weight_path = weight_path_pre + to_string(i) + weight_path_post;
		loadData_uint16(PHI_PRE_LAYERNORM_WEIGHT[i], 0, PHI_HIDDEN_SIZE, weight_path.c_str());
	}
	cout << "HOST_Info: Memory allocated for PHI_PRE_LAYERNORM_WEIGHT!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_PRE_LAYERNORM_BIAS ... ";
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE * sizeof(uint16))) {
			cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_PRE_LAYERNORM_BIAS[" << i << "] array" << endl << endl;
			return EXIT_FAILURE;
		}
		PHI_PRE_LAYERNORM_BIAS[i] = reinterpret_cast<uint16*>(ptr);
		weight_path = weight_path_pre + to_string(i) + weight_path_post;
		loadData_uint16(PHI_PRE_LAYERNORM_BIAS[i], 0, PHI_HIDDEN_SIZE, weight_path.c_str());
	}
	cout << "HOST_Info: Memory allocated for PHI_PRE_LAYERNORM_BIAS!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_Q_PROJ_WEIGHT ... ";
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		for (int j = 0; j < 2; j++) {
			if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE / 2 * sizeof(uint16))) {
				cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_Q_PROJ_WEIGHT[" << i << "][" << j << "] array" << endl << endl;
				return EXIT_FAILURE;
			}
			PHI_Q_PROJ_WEIGHT[i][j] = reinterpret_cast<uint16*>(ptr);
			weight_path_pre = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_";
			weight_path_post = "_self_attn_q_proj_weight.bin";
			weight_path = weight_path_pre + to_string(i) + weight_path_post;
			loadData_uint16(PHI_Q_PROJ_WEIGHT[i][j], j * PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE / 2, PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE / 2, weight_path.c_str());
		}
	}
	cout << "HOST_Info: Memory allocated for PHI_Q_PROJ_WEIGHT!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_Q_PROJ_BIAS ... ";
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		for (int j = 0; j < 2; j++) {
			if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE / 2 * sizeof(uint16))) {
				cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_Q_PROJ_BIAS[" << i << "][" << j << "] array" << endl << endl;
				return EXIT_FAILURE;
			}
			PHI_Q_PROJ_BIAS[i][j] = reinterpret_cast<uint16*>(ptr);
			weight_path_pre = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_";
			weight_path_post = "_self_attn_q_proj_bias.bin";
			weight_path = weight_path_pre + to_string(i) + weight_path_post;
			loadData_uint16(PHI_Q_PROJ_BIAS[i][j], j * PHI_HIDDEN_SIZE / 2, PHI_HIDDEN_SIZE / 2, weight_path.c_str());
		}
	}
	cout << "HOST_Info: Memory allocated for PHI_Q_PROJ_BIAS!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_K_PROJ_WEIGHT ... ";
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		for (int j = 0; j < 2; j++) {
			if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE / 2 * sizeof(uint16))) {
				cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_K_PROJ_WEIGHT[" << i << "][" << j << "] array" << endl << endl;
				return EXIT_FAILURE;
			}
			PHI_K_PROJ_WEIGHT[i][j] = reinterpret_cast<uint16*>(ptr);
			weight_path_pre = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_";
			weight_path_post = "_self_attn_k_proj_weight.bin";
			weight_path = weight_path_pre + to_string(i) + weight_path_post;
			loadData_uint16(PHI_K_PROJ_WEIGHT[i][j], j * PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE / 2, PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE / 2, weight_path.c_str());
		}
	}
	cout << "HOST_Info: Memory allocated for PHI_K_PROJ_WEIGHT!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_K_PROJ_BIAS ... ";
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		for (int j = 0; j < 2; j++) {
			if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE / 2 * sizeof(uint16))) {
				cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_K_PROJ_BIAS[" << i << "][" << j << "] array" << endl << endl;
				return EXIT_FAILURE;
			}
			PHI_K_PROJ_BIAS[i][j] = reinterpret_cast<uint16*>(ptr);
			weight_path_pre = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_";
			weight_path_post = "_self_attn_k_proj_bias.bin";
			weight_path = weight_path_pre + to_string(i) + weight_path_post;
			loadData_uint16(PHI_K_PROJ_BIAS[i][j], j * PHI_HIDDEN_SIZE / 2, PHI_HIDDEN_SIZE / 2, weight_path.c_str());
		}
	}
	cout << "HOST_Info: Memory allocated for PHI_K_PROJ_BIAS!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_V_PROJ_WEIGHT ... ";
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		for (int j = 0; j < 2; j++) {
			if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE / 2 * sizeof(uint16))) {
				cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_V_PROJ_WEIGHT[" << i << "][" << j << "] array" << endl << endl;
				return EXIT_FAILURE;
			}
			PHI_V_PROJ_WEIGHT[i][j] = reinterpret_cast<uint16*>(ptr);
			weight_path_pre = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_";
			weight_path_post = "_self_attn_v_proj_weight.bin";
			weight_path = weight_path_pre + to_string(i) + weight_path_post;
			loadData_uint16(PHI_V_PROJ_WEIGHT[i][j], j * PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE / 2, PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE / 2, weight_path.c_str());
		}
	}
	cout << "HOST_Info: Memory allocated for PHI_V_PROJ_WEIGHT!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_V_PROJ_BIAS ... ";
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		for (int j = 0; j < 2; j++) {
			if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE / 2 * sizeof(uint16))) {
				cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_V_PROJ_BIAS[" << i << "][" << j << "] array" << endl << endl;
				return EXIT_FAILURE;
			}
			PHI_V_PROJ_BIAS[i][j] = reinterpret_cast<uint16*>(ptr);
			weight_path_pre = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_";
			weight_path_post = "_self_attn_v_proj_bias.bin";
			weight_path = weight_path_pre + to_string(i) + weight_path_post;
			loadData_uint16(PHI_V_PROJ_BIAS[i][j], j * PHI_HIDDEN_SIZE / 2, PHI_HIDDEN_SIZE / 2, weight_path.c_str());
		}
	}
	cout << "HOST_Info: Memory allocated for PHI_V_PROJ_BIAS!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_DENSE_WEIGHT ... ";
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		for (int j = 0; j < 2; j++) {
			if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE * sizeof(uint16))) {
				cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_DENSE_WEIGHT[" << i << "][" << j << "] array" << endl << endl;
				return EXIT_FAILURE;
			}
			PHI_DENSE_WEIGHT[i][j] = reinterpret_cast<uint16*>(ptr);
			weight_path_pre = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_";
			weight_path_post = "_self_attn_dense_weight.bin";
			weight_path = weight_path_pre + to_string(i) + weight_path_post;
			loadData_uint16(PHI_DENSE_WEIGHT[i][j], j * PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE / 2, PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE / 2, weight_path.c_str());
		}
	}
	cout << "HOST_Info: Memory allocated for PHI_DENSE_WEIGHT!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_DENSE_BIAS ... ";
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		for (int j = 0; j < 2; j++) {
			if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE * sizeof(uint16))) {
				cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_DENSE_BIAS[" << i << "][" << j << "] array" << endl << endl;
				return EXIT_FAILURE;
			}
			PHI_DENSE_BIAS[i][j] = reinterpret_cast<uint16*>(ptr);
			weight_path_pre = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_";
			weight_path_post = "_self_attn_dense_bias.bin";
			weight_path = weight_path_pre + to_string(i) + weight_path_post;
			loadData_uint16(PHI_DENSE_BIAS[i][j], j * PHI_HIDDEN_SIZE / 2, PHI_HIDDEN_SIZE / 2, weight_path.c_str());
		}
	}
	cout << "HOST_Info: Memory allocated for PHI_DENSE_BIAS!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_MLP_FC1_WEIGHT ... ";
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		for (int j = 0; j < 8; j++) {
			if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE * PHI_INTERMEDIATE_SIZE / 8 * sizeof(uint16))) {
				cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_MLP_FC1_WEIGHT[" << i << "][" << j << "] array" << endl << endl;
				return EXIT_FAILURE;
			}
			PHI_MLP_FC1_WEIGHT[i][j] = reinterpret_cast<uint16*>(ptr);
			weight_path_pre = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_";
			weight_path_post = "_mlp_fc1_weight.bin";
			weight_path = weight_path_pre + to_string(i) + weight_path_post;
			loadData_uint16(PHI_MLP_FC1_WEIGHT[i][j], j * PHI_HIDDEN_SIZE * PHI_INTERMEDIATE_SIZE / 8, PHI_HIDDEN_SIZE * PHI_INTERMEDIATE_SIZE / 8, weight_path.c_str());
		}
	}
	cout << "HOST_Info: Memory allocated for PHI_MLP_FC1_WEIGHT!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_MLP_FC1_BIAS ... ";
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		for (int j = 0; j < 8; j++) {
			if (posix_memalign(&ptr, 4096, PHI_INTERMEDIATE_SIZE / 8 * sizeof(uint16))) {
				cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_MLP_FC1_BIAS[" << i << "][" << j << "] array" << endl << endl;
				return EXIT_FAILURE;
			}
			PHI_MLP_FC1_BIAS[i][j] = reinterpret_cast<uint16*>(ptr);
			weight_path_pre = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_";
			weight_path_post = "_mlp_fc1_bias.bin";
			weight_path = weight_path_pre + to_string(i) + weight_path_post;
			loadData_uint16(PHI_MLP_FC1_BIAS[i][j], j * PHI_INTERMEDIATE_SIZE / 8, PHI_INTERMEDIATE_SIZE / 8, weight_path.c_str());
		}
	}
	cout << "HOST_Info: Memory allocated for PHI_MLP_FC1_BIAS!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_MLP_FC2_WEIGHT ... ";
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		for (int j = 0; j < 8; j++) {
			if (posix_memalign(&ptr, 4096, PHI_INTERMEDIATE_SIZE / 8 * PHI_HIDDEN_SIZE * sizeof(uint16))) {
				cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_MLP_FC2_WEIGHT[" << i << "][" << j << "] array" << endl << endl;
				return EXIT_FAILURE;
			}
			PHI_MLP_FC2_WEIGHT[i][j] = reinterpret_cast<uint16*>(ptr);
			weight_path_pre = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_";
			weight_path_post = "_mlp_fc2_weight.bin";
			weight_path = weight_path_pre + to_string(i) + weight_path_post;
			loadData_uint16(PHI_MLP_FC2_WEIGHT[i][j], j * PHI_INTERMEDIATE_SIZE / 8 * PHI_HIDDEN_SIZE, PHI_INTERMEDIATE_SIZE / 8 * PHI_HIDDEN_SIZE, weight_path.c_str());
		}
	}
	cout << "HOST_Info: Memory allocated for PHI_MLP_FC2_WEIGHT!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_MLP_FC2_BIAS ... ";
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		for (int j = 0; j < 8; j++) {
			if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE * sizeof(uint16))) {
				cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_MLP_FC2_BIAS[" << i << "][" << j << "] array" << endl << endl;
				return EXIT_FAILURE;
			}
			PHI_MLP_FC2_BIAS[i][j] = reinterpret_cast<uint16*>(ptr);
			weight_path_pre = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_layers_";
			weight_path_post = "_mlp_fc2_bias.bin";
			weight_path = weight_path_pre + to_string(i) + weight_path_post;
			loadData_uint16(PHI_MLP_FC2_BIAS[i][j], j * PHI_HIDDEN_SIZE / 8, PHI_HIDDEN_SIZE / 8, weight_path.c_str());
		}
	}
	cout << "HOST_Info: Memory allocated for PHI_MLP_FC2_BIAS!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_LAST_LAYERNORM_WEIGHT ... ";
	if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_LAST_LAYERNORM_WEIGHT array" << endl << endl;
		return EXIT_FAILURE;
	}
	PHI_LAST_LAYERNORM_WEIGHT = reinterpret_cast<uint16*>(ptr);
	weight_path = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_final_layernorm_weight.bin";
	loadData_uint16(PHI_LAST_LAYERNORM_WEIGHT, 0, PHI_HIDDEN_SIZE, weight_path.c_str());
	cout << "HOST_Info: Memory allocated for PHI_LAST_LAYERNORM_WEIGHT!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_LAST_LAYERNORM_BIAS ... ";
	if (posix_memalign(&ptr, 4096, PHI_HIDDEN_SIZE * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_LAST_LAYERNORM_BIAS array" << endl << endl;
		return EXIT_FAILURE;
	}
	PHI_LAST_LAYERNORM_BIAS = reinterpret_cast<uint16*>(ptr);
	weight_path = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_final_layernorm_bias.bin";
	loadData_uint16(PHI_LAST_LAYERNORM_BIAS, 0, PHI_HIDDEN_SIZE, weight_path.c_str());
	cout << "HOST_Info: Memory allocated for PHI_LAST_LAYERNORM_BIAS!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_LM_HEAD_WEIGHT ... ";
	if (posix_memalign(&ptr, 4096, PHI_VOCAB_SIZE * PHI_HIDDEN_SIZE * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_LM_HEAD_WEIGHT array" << endl << endl;
		return EXIT_FAILURE;
	}
	PHI_LM_HEAD_WEIGHT = reinterpret_cast<uint16*>(ptr);
	weight_path = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_lm_head_weight.bin";
	loadData_uint16(PHI_LM_HEAD_WEIGHT, 0, PHI_VOCAB_SIZE * PHI_HIDDEN_SIZE, weight_path.c_str());
	cout << "HOST_Info: Memory allocated for PHI_LM_HEAD_WEIGHT!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_LM_HEAD_BIAS ... ";
	if (posix_memalign(&ptr, 4096, PHI_VOCAB_SIZE * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_LM_HEAD_BIAS array" << endl << endl;
		return EXIT_FAILURE;
	}
	PHI_LM_HEAD_BIAS = reinterpret_cast<uint16*>(ptr);
	weight_path = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_lm_head_bias.bin";
	loadData_uint16(PHI_LM_HEAD_BIAS, 0, PHI_VOCAB_SIZE, weight_path.c_str());
	cout << "HOST_Info: Memory allocated for PHI_LM_HEAD_BIAS!" << endl;

	cout << "HOST-Info: Allocating memory for PHI_EMBED_TOKENS_WEIGHT ... ";
	if (posix_memalign(&ptr, 4096, PHI_VOCAB_SIZE * PHI_HIDDEN_SIZE * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for PHI_EMBED_TOKENS_WEIGHT array" << endl << endl;
		return EXIT_FAILURE;
	}
	PHI_EMBED_TOKENS_WEIGHT = reinterpret_cast<uint16*>(ptr);
	weight_path = "/user/undergraduate/ytliu24/phi_workspace/weights/language_model_model_embed_tokens_weight.bin";
	loadData_uint16(PHI_EMBED_TOKENS_WEIGHT, 0, PHI_VOCAB_SIZE * PHI_HIDDEN_SIZE, weight_path.c_str());
	cout << "HOST_Info: Memory allocated for PHI_EMBED_TOKENS_WEIGHT!" << endl;

	cout << endl;

	// ------------------------------------------------------------------
	// Step 4.2: Create Buffers in Global Memory to store data
	//             o) buffer_phi_linear_out
    //             o) buffer_phi_linear_in
    //             o) buffer_phi_linear_weight
    //             o) buffer_phi_linear_bias
	// ------------------------------------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Allocating buffers ..." << endl;
	#endif
	// cl_mem buffer_phi_input, buffer_phi_output;
	cl_mem buffer_phi_layernorm_in, buffer_phi_residual, buffer_phi_mlp_in;
	cl_mem buffer_phi_q_proj_in, buffer_phi_k_proj_in, buffer_phi_v_proj_in;
	cl_mem buffer_phi_q_embed_in, buffer_phi_k_embed_in, buffer_phi_q;
	cl_mem buffer_phi_attention_out, buffer_phi_dense_out, buffer_phi_mlp_out;
	cl_mem buffer_phi_last_layernorm_weight, buffer_phi_last_layernorm_bias;

	cl_mem buffer_phi_k_cache[32][2], buffer_phi_v_cache[32][2]; // length = 800, 250 MB, length = 32, 10 MB

	cl_mem buffer_phi_pre_layernorm_weight[32], buffer_phi_pre_layernorm_bias[32];
	cl_mem buffer_phi_q_proj_weight[32][2], buffer_phi_q_proj_bias[32][2];
	cl_mem buffer_phi_k_proj_weight[32][2], buffer_phi_k_proj_bias[32][2];
	cl_mem buffer_phi_v_proj_weight[32][2], buffer_phi_v_proj_bias[32][2];
	cl_mem buffer_phi_dense_weight[32][2], buffer_phi_dense_bias[32][2];
	cl_mem buffer_phi_mlp_fc1_weight[32][8], buffer_phi_mlp_fc1_bias[32][8];
	cl_mem buffer_phi_mlp_fc2_weight[32][8], buffer_phi_mlp_fc2_bias[32][8];

	fixed32_14 fixed32_14_value;
	int position_id;

	// OCL_CHECK(errCode, buffer_phi_input = clCreateBuffer(Context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * sizeof(uint16), PHI_IN, &errCode));
	// OCL_CHECK(errCode, buffer_phi_output = clCreateBuffer(Context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * sizeof(fixed32_14), PHI_OUT, &errCode));

	OCL_CHECK(errCode, buffer_phi_layernorm_in = clCreateBuffer(Context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * sizeof(fixed32_14), PHI_IN, &errCode));
	OCL_CHECK(errCode, buffer_phi_residual = clCreateBuffer(Context, CL_MEM_READ_WRITE, PHI_HIDDEN_SIZE * sizeof(fixed32_14), NULL, &errCode));
	OCL_CHECK(errCode, buffer_phi_mlp_in = clCreateBuffer(Context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * sizeof(fixed32_14), PHI_OUT, &errCode));
	OCL_CHECK(errCode, buffer_phi_q_proj_in = clCreateBuffer(Context, CL_MEM_READ_WRITE, PHI_HIDDEN_SIZE * sizeof(fixed32_14), NULL, &errCode));
	OCL_CHECK(errCode, buffer_phi_k_proj_in = clCreateBuffer(Context, CL_MEM_READ_WRITE, PHI_HIDDEN_SIZE * sizeof(fixed32_14), NULL, &errCode));
	OCL_CHECK(errCode, buffer_phi_v_proj_in = clCreateBuffer(Context, CL_MEM_READ_WRITE, PHI_HIDDEN_SIZE * sizeof(fixed32_14), NULL, &errCode));
	OCL_CHECK(errCode, buffer_phi_q_embed_in = clCreateBuffer(Context, CL_MEM_READ_WRITE, PHI_HIDDEN_SIZE * sizeof(fixed32_14), NULL, &errCode));
	OCL_CHECK(errCode, buffer_phi_k_embed_in = clCreateBuffer(Context, CL_MEM_READ_WRITE, PHI_HIDDEN_SIZE * sizeof(fixed32_14), NULL, &errCode));
	OCL_CHECK(errCode, buffer_phi_q = clCreateBuffer(Context, CL_MEM_READ_WRITE, PHI_HIDDEN_SIZE * sizeof(fixed32_14), NULL, &errCode));
	OCL_CHECK(errCode, buffer_phi_attention_out = clCreateBuffer(Context, CL_MEM_READ_WRITE, PHI_HIDDEN_SIZE * sizeof(fixed32_14), NULL, &errCode));
	OCL_CHECK(errCode, buffer_phi_dense_out = clCreateBuffer(Context, CL_MEM_READ_WRITE, PHI_HIDDEN_SIZE * sizeof(fixed32_14), NULL, &errCode));
	OCL_CHECK(errCode, buffer_phi_mlp_out = clCreateBuffer(Context, CL_MEM_READ_WRITE, PHI_HIDDEN_SIZE * sizeof(fixed32_14), NULL, &errCode));
	OCL_CHECK(errCode, buffer_phi_last_layernorm_weight = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * sizeof(uint16), PHI_LAST_LAYERNORM_WEIGHT, &errCode));
	OCL_CHECK(errCode, buffer_phi_last_layernorm_bias = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * sizeof(uint16), PHI_LAST_LAYERNORM_BIAS, &errCode));

	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		OCL_CHECK(errCode, buffer_phi_k_cache[i][0] = clCreateBuffer(Context, CL_MEM_READ_WRITE, PHI_HIDDEN_SIZE * 800 * sizeof(fixed32_14), NULL, &errCode));
		OCL_CHECK(errCode, buffer_phi_k_cache[i][1] = clCreateBuffer(Context, CL_MEM_READ_WRITE, PHI_HIDDEN_SIZE * 32 * sizeof(fixed32_14), NULL, &errCode));
		OCL_CHECK(errCode, buffer_phi_v_cache[i][0] = clCreateBuffer(Context, CL_MEM_READ_WRITE, PHI_HIDDEN_SIZE * 800 * sizeof(fixed32_14), NULL, &errCode));
		OCL_CHECK(errCode, buffer_phi_v_cache[i][1] = clCreateBuffer(Context, CL_MEM_READ_WRITE, PHI_HIDDEN_SIZE * 32 * sizeof(fixed32_14), NULL, &errCode));

		OCL_CHECK(errCode, buffer_phi_pre_layernorm_weight[i] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * sizeof(uint16), PHI_PRE_LAYERNORM_WEIGHT[i], &errCode));
		OCL_CHECK(errCode, buffer_phi_pre_layernorm_bias[i] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * sizeof(uint16), PHI_PRE_LAYERNORM_BIAS[i], &errCode));

		for (int j = 0; j < 2; j++) {
			OCL_CHECK(errCode, buffer_phi_q_proj_weight[i][j] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE / 2 * sizeof(uint16), PHI_Q_PROJ_WEIGHT[i][j], &errCode));
			OCL_CHECK(errCode, buffer_phi_q_proj_bias[i][j] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE / 2 * sizeof(uint16), PHI_Q_PROJ_BIAS[i][j], &errCode));
			OCL_CHECK(errCode, buffer_phi_k_proj_weight[i][j] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE / 2 * sizeof(uint16), PHI_K_PROJ_WEIGHT[i][j], &errCode));
			OCL_CHECK(errCode, buffer_phi_k_proj_bias[i][j] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE / 2 * sizeof(uint16), PHI_K_PROJ_BIAS[i][j], &errCode));
			OCL_CHECK(errCode, buffer_phi_v_proj_weight[i][j] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE / 2 * sizeof(uint16), PHI_V_PROJ_WEIGHT[i][j], &errCode));
			OCL_CHECK(errCode, buffer_phi_v_proj_bias[i][j] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE / 2 * sizeof(uint16), PHI_V_PROJ_BIAS[i][j], &errCode));
			OCL_CHECK(errCode, buffer_phi_dense_weight[i][j] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * PHI_HIDDEN_SIZE * sizeof(uint16), PHI_DENSE_WEIGHT[i][j], &errCode));
			OCL_CHECK(errCode, buffer_phi_dense_bias[i][j] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * sizeof(uint16), PHI_DENSE_BIAS[i][j], &errCode));
		}

		for (int j = 0; j < 8; j++) {
			OCL_CHECK(errCode, buffer_phi_mlp_fc1_weight[i][j] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * PHI_INTERMEDIATE_SIZE / 8 * sizeof(uint16), PHI_MLP_FC1_WEIGHT[i][j], &errCode));
			OCL_CHECK(errCode, buffer_phi_mlp_fc1_bias[i][j] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_INTERMEDIATE_SIZE / 8 * sizeof(uint16), PHI_MLP_FC1_BIAS[i][j], &errCode));
			OCL_CHECK(errCode, buffer_phi_mlp_fc2_weight[i][j] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_INTERMEDIATE_SIZE / 8 * PHI_HIDDEN_SIZE * sizeof(uint16), PHI_MLP_FC2_WEIGHT[i][j], &errCode));
			OCL_CHECK(errCode, buffer_phi_mlp_fc2_bias[i][j] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, PHI_HIDDEN_SIZE * sizeof(uint16), PHI_MLP_FC2_BIAS[i][j], &errCode));
		}
	}


	// ============================================================================
	// Step 5: Set Kernel Arguments and Run the Application
	//         o) Set Kernel Arguments
	// 				------------------------------------------------------------
	// 				 Kernel	  		    Argument Nb		Description
	// 				------------------------------------------------------------
	//  			 kernel_phi_linear	0				buffer_phi_linear_out
    //  			 kernel_phi_linear	1				buffer_phi_linear_in
    //  			 kernel_phi_linear	2				buffer_phi_linear_weight
    //  			 kernel_phi_linear	3				buffer_phi_linear_bias
	// 				------------------------------------------------------------
	//         o) Copy Input Data from Host to Global Memory
	//         o) Submit Kernels for Execution
	//         o) Copy Results from Global Memory to Host
	// ============================================================================
	// TODO 這裡要改

	#ifdef ALL_MESSAGES
	cout << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	cout << "HOST-Info: (Step 5) Run Application                                      " << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	#endif


	// ----------------------------------------
	// Step 5.1: Set Kernel Arguments
	// ----------------------------------------

	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Setting Kernel arguments ..." << endl;
	#endif

	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_copy_residual, 0, sizeof(cl_mem), &buffer_phi_residual));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_copy_residual, 1, sizeof(cl_mem), &buffer_phi_layernorm_in));

	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_layernorm, 0, sizeof(cl_mem), &buffer_phi_mlp_in));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_layernorm, 1, sizeof(cl_mem), &buffer_phi_layernorm_in));

	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_copy_q, 0, sizeof(cl_mem), &buffer_phi_q_proj_in));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_copy_q, 1, sizeof(cl_mem), &buffer_phi_mlp_in));

	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_copy_k, 0, sizeof(cl_mem), &buffer_phi_k_proj_in));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_copy_k, 1, sizeof(cl_mem), &buffer_phi_mlp_in));

	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_copy_v, 0, sizeof(cl_mem), &buffer_phi_v_proj_in));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_copy_v, 1, sizeof(cl_mem), &buffer_phi_mlp_in));

	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_q_proj, 0, sizeof(cl_mem), &buffer_phi_q_embed_in));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_q_proj, 1, sizeof(cl_mem), &buffer_phi_q_proj_in));

	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_k_proj, 0, sizeof(cl_mem), &buffer_phi_k_embed_in));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_k_proj, 1, sizeof(cl_mem), &buffer_phi_k_proj_in));

	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_v_proj, 0, sizeof(cl_mem), &buffer_phi_v_cache[0]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_v_proj, 1, sizeof(cl_mem), &buffer_phi_v_cache[1]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_v_proj, 2, sizeof(cl_mem), &buffer_phi_v_proj_in));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_v_proj, 7, sizeof(int), &position_id));

	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_rotary_embed, 0, sizeof(cl_mem), &buffer_phi_q));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_rotary_embed, 1, sizeof(cl_mem), &buffer_phi_k_cache[0]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_rotary_embed, 2, sizeof(cl_mem), &buffer_phi_k_cache[1]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_rotary_embed, 3, sizeof(cl_mem), &buffer_phi_q_embed_in));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_rotary_embed, 4, sizeof(cl_mem), &buffer_phi_k_embed_in));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_rotary_embed, 5, sizeof(int), &position_id));

	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_attention, 0, sizeof(cl_mem), &buffer_phi_attention_out));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_attention, 1, sizeof(cl_mem), &buffer_phi_q));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_attention, 2, sizeof(cl_mem), &buffer_phi_k_cache[0]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_attention, 3, sizeof(cl_mem), &buffer_phi_v_cache[0]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_attention, 4, sizeof(cl_mem), &buffer_phi_k_cache[1]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_attention, 5, sizeof(cl_mem), &buffer_phi_v_cache[1]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_attention, 6, sizeof(int), &position_id));

	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_dense, 0, sizeof(cl_mem), &buffer_phi_dense_out));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_dense, 1, sizeof(cl_mem), &buffer_phi_attention_out));

	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 0, sizeof(cl_mem), &buffer_phi_mlp_out));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 1, sizeof(cl_mem), &buffer_phi_mlp_in));

	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_add_residual, 0, sizeof(cl_mem), &buffer_phi_layernorm_in));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_add_residual, 1, sizeof(cl_mem), &buffer_phi_residual));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_add_residual, 2, sizeof(cl_mem), &buffer_phi_dense_out));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_add_residual, 3, sizeof(cl_mem), &buffer_phi_mlp_out));

    // Initialize tokenizer
    #ifdef ALL_MESSAGES
	cout << "HOST_Info: Initializing tokenizer..." << endl;
	#endif
    unique_ptr<tokenizers::Tokenizer> tokenizer;
    if (initTokenizer("/user/undergraduate/ytliu24/phi_workspace/tokenizer/src/tokenizer.json", tokenizer) != 0) {
        cerr << "Failed to initialize tokenizer." << endl;
        return EXIT_FAILURE;
    }

	// Pre load weight to FPGA
	#ifdef ALL_MESSAGES
	cout << "HOST_Info: Pre-loading weights to FPGA..." << endl;
	#endif
	clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_last_layernorm_weight, 0, 0, NULL, NULL);
	clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_last_layernorm_bias, 0, 0, NULL, NULL);
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_pre_layernorm_weight[i], 0, 0, NULL, NULL);
		clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_pre_layernorm_bias[i], 0, 0, NULL, NULL);
		for (int j = 0; j < 2; j++) {
			clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_q_proj_weight[i][j], 0, 0, NULL, NULL);
			clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_q_proj_bias[i][j], 0, 0, NULL, NULL);
			clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_k_proj_weight[i][j], 0, 0, NULL, NULL);
			clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_k_proj_bias[i][j], 0, 0, NULL, NULL);
			clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_v_proj_weight[i][j], 0, 0, NULL, NULL);
			clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_v_proj_bias[i][j], 0, 0, NULL, NULL);
			clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_dense_weight[i][j], 0, 0, NULL, NULL);
			clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_dense_bias[i][j], 0, 0, NULL, NULL);
		}
		for (int j = 0; j < 8; j++) {
			clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_weight[i][j], 0, 0, NULL, NULL);
			clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_bias[i][j], 0, 0, NULL, NULL);
			clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_weight[i][j], 0, 0, NULL, NULL);
			clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_bias[i][j], 0, 0, NULL, NULL);
		}
	}
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_in, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, NULL));

	// Wait for pre-load to finish
	OCL_CHECK(errCode, errCode = clEnqueueBarrierWithWaitList(Command_Queue, 0, NULL, NULL));

	cout << "HOST_Info: Pre-load completed!" << endl;

    // ------------------------------------------------------
	// Step 5.2.0: Input
	// ------------------------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST_Info: Reading input string..." << endl;
	#endif
    string input_string;
    if (readTxtFile("/user/undergraduate/ytliu24/phi_workspace/input/input_string.txt", input_string) == 0) {
        cout << "File content:\n" << input_string << endl;
    } else {
        cout << "Failed to read the file." << endl;
        return EXIT_FAILURE;
    }

    #ifdef ALL_MESSAGES
	cout << "HOST_Info: Tokenized input string..." << endl;
	#endif
    vector<int32_t> tokenized_input = tokenizer->Encode(input_string);
	vector<int32_t> output_tokens;

    cout << "Tokenized input IDs: [ ";
    for (int token_id : tokenized_input) {
        cout << token_id << " ";
    }
    cout << "]" << endl;

	int input_length = tokenized_input.size();

	cl_event event[32][13];

	for (int i = 0; i < PHI_SLEN; i++) {
		if (tokenized_input[i] == PHI_EOS_TOKEN_ID) {
			break;
		}
		wordEmbed(PHI_IN, &PHI_EMBED_TOKENS_WEIGHT[tokenized_input[i] * PHI_HIDDEN_SIZE]);
		OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_layernorm_in, 0, 0, NULL, NULL));
		OCL_CHECK(errCode, errCode = clEnqueueBarrierWithWaitList(Command_Queue, 0, NULL, NULL));
		position_id = i;
		for (int j = 0; j < PHI_NUM_DECODER_LAYERS; j++) {
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_layernorm, 2, sizeof(cl_mem), &buffer_phi_pre_layernorm_weight[j]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_layernorm, 3, sizeof(cl_mem), &buffer_phi_pre_layernorm_bias[j]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_q_proj, 2, sizeof(cl_mem), &buffer_phi_q_proj_weight[j][0]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_q_proj, 3, sizeof(cl_mem), &buffer_phi_q_proj_weight[j][0]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_q_proj, 4, sizeof(cl_mem), &buffer_phi_q_proj_bias[j][1]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_q_proj, 5, sizeof(cl_mem), &buffer_phi_q_proj_bias[j][1]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_k_proj, 2, sizeof(cl_mem), &buffer_phi_k_proj_weight[j][0]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_k_proj, 3, sizeof(cl_mem), &buffer_phi_k_proj_weight[j][0]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_k_proj, 4, sizeof(cl_mem), &buffer_phi_k_proj_bias[j][1]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_k_proj, 5, sizeof(cl_mem), &buffer_phi_k_proj_bias[j][1]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_v_proj, 3, sizeof(cl_mem), &buffer_phi_v_proj_weight[j][0]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_v_proj, 4, sizeof(cl_mem), &buffer_phi_v_proj_weight[j][0]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_v_proj, 5, sizeof(cl_mem), &buffer_phi_v_proj_bias[j][1]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_v_proj, 6, sizeof(cl_mem), &buffer_phi_v_proj_bias[j][1]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_dense, 2, sizeof(cl_mem), &buffer_phi_dense_weight[j][0]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_dense, 3, sizeof(cl_mem), &buffer_phi_dense_weight[j][0]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_dense, 4, sizeof(cl_mem), &buffer_phi_dense_bias[j][1]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_dense, 5, sizeof(cl_mem), &buffer_phi_dense_bias[j][1]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 2, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[j][0]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 3, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[j][1]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 4, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[j][2]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 5, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[j][3]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 6, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[j][4]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 7, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[j][5]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 8, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[j][6]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 9, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[j][7]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 10, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[j][0]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 11, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[j][1]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 12, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[j][2]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 13, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[j][3]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 14, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[j][4]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 15, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[j][5]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 16, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[j][6]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 17, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[j][7]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 18, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[j][0]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	19, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[j][1]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	20, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[j][2]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	21, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[j][3]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	22, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[j][4]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	23, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[j][5]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	24, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[j][6]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	25, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[j][7]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	26, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[j][0]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	27, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[j][1]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	28, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[j][2]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	29, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[j][3]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	30, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[j][4]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	31, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[j][5]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	32, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[j][6]));
			OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp,	33, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[j][7]));

			OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_copy_residual, 0, NULL, &event[i][0]));
			OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_layernorm, 1, &event[i][0], &event[i][1]));
			OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_copy_q, 1, &event[i][1], &event[i][2]));
			OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_copy_k, 1, &event[i][1], &event[i][3]));
			OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_copy_v, 1, &event[i][1], &event[i][4]));
			OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_q_proj, 1, &event[i][2], &event[i][5]));
			OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_k_proj, 1, &event[i][3], &event[i][6]));
			OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_v_proj, 1, &event[i][4], &event[i][7]));
			OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_rotary_embed, 2, &event[i][5], &event[i][8]));
			OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_attention, 2, &event[i][7], &event[i][9]));
			OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_dense, 1, &event[i][9], &event[i][10]));
			OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_mlp, 1, &event[i][1], &event[i][11]));
			OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_add_residual, 1, &event[i][11], &event[i][12]));
			OCL_CHECK(errCode, errCode = clEnqueueBarrierWithWaitList(Command_Queue, 0, NULL, NULL));
		}
		OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_layernorm, 2, sizeof(cl_mem), &buffer_phi_last_layernorm_weight));
		OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_layernorm, 3, sizeof(cl_mem), &buffer_phi_last_layernorm_bias));
		OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_layernorm, 0, NULL, NULL));
		OCL_CHECK(errCode, errCode = clEnqueueBarrierWithWaitList(Command_Queue, 0, NULL, NULL));

		if (i < input_length - 1) continue; // Only need to count key and value for the input tokens

		// lm and argmax
		fixed32_14 maxval = 0;
		int max_index = 0;
		for (int j = 0; j < PHI_HIDDEN_SIZE; j++) {
			maxval += PHI_IN[j] * PHI_LM_HEAD_WEIGHT[j] + PHI_LM_HEAD_BIAS[0];
		}
		for (int j = 1; j < PHI_VOCAB_SIZE; j++) {
			fixed32_14 val = 0;
			for (int k = 0; k < PHI_HIDDEN_SIZE; k++) {
				val += PHI_IN[k] * PHI_LM_HEAD_WEIGHT[j * PHI_HIDDEN_SIZE + k] + PHI_LM_HEAD_BIAS[j];
			}
			if (val > maxval) {
				maxval = val;
				max_index = j;
			}
		}
		cout << "Generated token ID: " << max_index << endl;
		tokenized_input.push_back(max_index);
		output_tokens.push_back(max_index);
	}
	cout << "HOST-Info: Finish generation!" << endl;

	// decode tokens
	cout << "HOST-Info: Decoding output tokens..." << endl;
	string output_string = tokenizer->Decode(output_tokens);
	cout << "Input string: " << input_string << endl;
	cout << "Generated output string: " << output_string << endl;
	cout << endl;

	FILE *fp;
	fp = fopen("/user/undergraduate/ytliu24/phi_workspace/output/output_string.txt", "w");
	if (fp == NULL) {
		cerr << "Error opening file for writing." << endl;
		return EXIT_FAILURE;
	}
	fprintf(fp, "%s", output_string.c_str());
	fclose(fp);

	// ------------------------------------------------------
	// Step 5.2: Copy Input data from Host to Global Memory
	// ------------------------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST_Info: Copy Input data to Global Memory ..." << endl;
	#endif

	// clEnqueueMigrateMemObjects(cl_command_queue, number of cl_uint, cl_mem*, cl_mem_migration_flags, number of pending events, pending cl_event*, generate cl_event*)

	// OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_linear_in, 0, 0, NULL, &Mem_op_event[0]));
	// OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_linear_weight, 0, 0, NULL, &Mem_op_event[1]));
	// OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_linear_bias, 0, 0, NULL, &Mem_op_event[2]));

	// --------------------------------------------------------

	// OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_linear_out, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[3]));

	// --------------------------------------------------------

	// OCL_CHECK(errCode, errCode = clEnqueueBarrierWithWaitList(Command_Queue, 0, NULL, NULL));

	// ----------------------------------------
	// Step 5.3: Submit Kernels for Execution
	// ----------------------------------------

	cout << "HOST-Info: Submitting Kernel kernel_phi_linear for Execution ..." << endl;

	// OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_linear, 0, NULL, &K_exe_event[0]));

	// ---------------------------------------------------------
	// Step 5.4: Submit Copy Results from Global Memory to Host
	// ---------------------------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST_Info: Submitting Copy Results data from Global Memory to Host ..." << endl;
	#endif

	// OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_linear_out, CL_MIGRATE_MEM_OBJECT_HOST, 1, &K_exe_event[0], &Mem_op_event[4]));

	cout << endl << "HOST_Info: Waiting for application to be completed ..." << endl;
	clFinish(Command_Queue);


	// ============================================================================
	// Step 6: Processing Output Results
	//         o) Store output results to a RES.txt file
	//         o) Check correctness of the output results
	// ============================================================================

	// ============================================================================
	// Step 7: Custom Profiling
	// ============================================================================
	cout << "HOST-Info: ============================================================= " << endl;
	cout << "HOST-Info: (Step 7) Custom Profiling (Not yet implemented)                                     " << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	// int Nb_Of_Kernels = Nb_Of_Exe_Events;
	// int Nb_Of_Memory_Tranfers = Nb_Of_Mem_Events;

	// string list_of_kernel_names[Nb_Of_Kernels]={"kernel_phi_linear"};
	// run_custom_profiling (Nb_Of_Kernels, Nb_Of_Memory_Tranfers, K_exe_event, Mem_op_event, list_of_kernel_names);

	// ============================================================================
	// Step 8: Release Allocated Resources
	// ============================================================================
	clReleaseDevice(Target_Device_ID); // Only available in OpenCL >= 1.2

	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 13; j++) {
			clReleaseEvent(event[i][j]);
		}
	}

	// clReleaseMemObject(buffer_phi_linear_out);
	// clReleaseMemObject(buffer_phi_linear_in);
	// clReleaseMemObject(buffer_phi_linear_weight);
	// clReleaseMemObject(buffer_phi_linear_bias);
	clReleaseMemObject(buffer_phi_layernorm_in);
	clReleaseMemObject(buffer_phi_residual);
	clReleaseMemObject(buffer_phi_mlp_in);
	clReleaseMemObject(buffer_phi_q_proj_in);
	clReleaseMemObject(buffer_phi_k_proj_in);
	clReleaseMemObject(buffer_phi_v_proj_in);
	clReleaseMemObject(buffer_phi_q_embed_in);
	clReleaseMemObject(buffer_phi_k_embed_in);
	clReleaseMemObject(buffer_phi_q);
	clReleaseMemObject(buffer_phi_attention_out);
	clReleaseMemObject(buffer_phi_dense_out);
	clReleaseMemObject(buffer_phi_mlp_out);
	clReleaseMemObject(buffer_phi_last_layernorm_weight);
	clReleaseMemObject(buffer_phi_last_layernorm_bias);
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		clReleaseMemObject(buffer_phi_pre_layernorm_weight[i]);
		clReleaseMemObject(buffer_phi_pre_layernorm_bias[i]);
		for (int j = 0; j < 2; j++) {
			clReleaseMemObject(buffer_phi_q_proj_weight[i][j]);
			clReleaseMemObject(buffer_phi_q_proj_bias[i][j]);
			clReleaseMemObject(buffer_phi_k_proj_weight[i][j]);
			clReleaseMemObject(buffer_phi_k_proj_bias[i][j]);
			clReleaseMemObject(buffer_phi_v_proj_weight[i][j]);
			clReleaseMemObject(buffer_phi_v_proj_bias[i][j]);
			clReleaseMemObject(buffer_phi_dense_weight[i][j]);
			clReleaseMemObject(buffer_phi_dense_bias[i][j]);
			clReleaseMemObject(buffer_phi_k_cache[i][j]);
			clReleaseMemObject(buffer_phi_v_cache[i][j]);
		}
		for (int j = 0; j < 8; j++) {
			clReleaseMemObject(buffer_phi_mlp_fc1_weight[i][j]);
			clReleaseMemObject(buffer_phi_mlp_fc1_bias[i][j]);
			clReleaseMemObject(buffer_phi_mlp_fc2_weight[i][j]);
			clReleaseMemObject(buffer_phi_mlp_fc2_bias[i][j]);
		}
	}

	clReleaseKernel(kernel_phi_q_proj);
	clReleaseKernel(kernel_phi_k_proj);
	clReleaseKernel(kernel_phi_v_proj);
	clReleaseKernel(kernel_phi_dense);
	clReleaseKernel(kernel_phi_layernorm);
	clReleaseKernel(kernel_phi_rotary_embed);
	clReleaseKernel(kernel_phi_attention);
	clReleaseKernel(kernel_phi_mlp);
	clReleaseKernel(kernel_phi_add_residual);
	clReleaseKernel(kernel_phi_copy_q);
	clReleaseKernel(kernel_phi_copy_k);
	clReleaseKernel(kernel_phi_copy_v);
	clReleaseKernel(kernel_phi_copy_residual);

	clReleaseProgram(Program);
	clReleaseCommandQueue(Command_Queue);
	clReleaseContext(Context);

	free(Platform_IDs);
	free(Device_IDs);

	free(PHI_OUT);
	free(PHI_IN);
	free(PHI_LAST_LAYERNORM_WEIGHT);
	free(PHI_LAST_LAYERNORM_BIAS);
	free(PHI_LM_HEAD_WEIGHT);
	free(PHI_LM_HEAD_BIAS);
	free(PHI_EMBED_TOKENS_WEIGHT);
	for (int i = 0; i < PHI_NUM_DECODER_LAYERS; i++) {
		free(PHI_PRE_LAYERNORM_WEIGHT[i]);
		free(PHI_PRE_LAYERNORM_BIAS[i]);
		for (int j = 0; j < 2; j++) {
			free(PHI_Q_PROJ_WEIGHT[i][j]);
			free(PHI_Q_PROJ_BIAS[i][j]);
			free(PHI_K_PROJ_WEIGHT[i][j]);
			free(PHI_K_PROJ_BIAS[i][j]);
			free(PHI_V_PROJ_WEIGHT[i][j]);
			free(PHI_V_PROJ_BIAS[i][j]);
			free(PHI_DENSE_WEIGHT[i][j]);
			free(PHI_DENSE_BIAS[i][j]);
		}
		for (int j = 0; j < 8; j++) {
			free(PHI_MLP_FC1_WEIGHT[i][j]);
			free(PHI_MLP_FC1_BIAS[i][j]);
			free(PHI_MLP_FC2_WEIGHT[i][j]);
			free(PHI_MLP_FC2_BIAS[i][j]);
		}
	}

	cout << endl << "HOST-Info: DONE" << endl << endl;

	return EXIT_SUCCESS;
}

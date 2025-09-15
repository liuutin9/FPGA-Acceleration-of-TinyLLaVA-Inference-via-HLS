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
#include <ap_int.h>
#include <vector>
#include "CL/cl_ext_xilinx.h"   // Xilinx 的擴展 API
#include "CL/cl.h"              // OpenCL 標準 API
//#include <hls_math.h>

typedef ap_fixed<32,14> fixed32_14;
typedef ap_uint<16>  uint16;

using namespace std;

#define ALL_MESSAGES

#define HIDDEN_SIZE 2560
#define SIZE_OUT HIDDEN_SIZE
#define SIZE_IN HIDDEN_SIZE
#define SIZE_WEIGHT HIDDEN_SIZE
#define SIZE_BIAS HIDDEN_SIZE
#define LAYER_NORM_EPS 0.0000610352
#define INTERMIDIATE_SIZE 10240
#define SIZE_WEIGHT (HIDDEN_SIZE * INTERMIDIATE_SIZE / 8)
#define SIZE_BIAS_FC1 (INTERMIDIATE_SIZE / 8)
#define SIZE_BIAS_FC2 (HIDDEN_SIZE / 8)

#define OCL_CHECK(error, call)                                                                   	 \
    do {                                                                                             \
        call;                                                                                        \
        if (error != CL_SUCCESS) {                                                                   \
            printf("%s:%d Error calling " #call ", error code is: %d\n", __FILE__, __LINE__, error); \
            exit(EXIT_FAILURE);                                                                      \
        }                                                                                            \
    } while (0)

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
	char buf[2];
	for (size_t i = 0; i < binary.size(); i += 2) {
		buf[0] = binary[i];
		buf[1] = binary[i + 1];
		memcpy(&out[i / 2], &buf, sizeof(uint16));
	}
	return 0;
}

int loadData_uint16(uint16* out, int len_offset, int length, const char *filename) {
	vector<char> binary;
	if (readBinaryFile(filename, binary, len_offset * 2, length * 2) != 0) {
		return -1;
	}
	return binaryToUint16(out, binary);
}

// =========================================
// Helper Function: Set bank extension pointer
// =========================================
void setBankExtensionPointer(cl_mem_ext_ptr_t &bank_ext, unsigned id, void* obj, void* param) {
    bank_ext.flags = id | XCL_MEM_TOPOLOGY;
    bank_ext.obj   = obj;
    bank_ext.param = param;
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

	PROFILE[0].action_type="kernel";  PROFILE[0].name="kernel_phi_mlp";  PROFILE[0].event = K_exe_event[0];

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
	cl_kernel kernel_phi_mlp;

	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Creating Kernels ..." << endl;
	#endif
	OCL_CHECK(errCode, kernel_phi_mlp = clCreateKernel(Program, "kernel_phi_mlp", &errCode));

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
	fixed32_14 *IN, *OUT;
    uint16 *WEIGHT_FC1_0, *BIAS_FC1_0, *WEIGHT_FC2_0, *BIAS_FC2_0;
	uint16 *WEIGHT_FC1_1, *BIAS_FC1_1, *WEIGHT_FC2_1, *BIAS_FC2_1;
    uint16 *WEIGHT_FC1_2, *BIAS_FC1_2, *WEIGHT_FC2_2, *BIAS_FC2_2;
    uint16 *WEIGHT_FC1_3, *BIAS_FC1_3, *WEIGHT_FC2_3, *BIAS_FC2_3;
    uint16 *WEIGHT_FC1_4, *BIAS_FC1_4, *WEIGHT_FC2_4, *BIAS_FC2_4;
    uint16 *WEIGHT_FC1_5, *BIAS_FC1_5, *WEIGHT_FC2_5, *BIAS_FC2_5;
    uint16 *WEIGHT_FC1_6, *BIAS_FC1_6, *WEIGHT_FC2_6, *BIAS_FC2_6;
    uint16 *WEIGHT_FC1_7, *BIAS_FC1_7, *WEIGHT_FC2_7, *BIAS_FC2_7;

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

	cout << "HOST-Info: Allocating memory for IN ... ";
	if (posix_memalign(&ptr, 4096, SIZE_IN * sizeof(fixed32_14))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for IN array" << endl << endl;
		return EXIT_FAILURE;
	}
	IN = reinterpret_cast<fixed32_14*>(ptr);
	for (int i = 0; i < SIZE_IN; i++) {
		IN[i] = fixed32_14(i);
	}
	cout << "Generated " << SIZE_IN << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC1_0 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC1_0 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC1_0 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC1_0, 0 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC1_1 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC1_1 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC1_1 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC1_1, 1 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC1_2 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC1_2 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC1_2 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC1_2, 2 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC1_3 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC1_3 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC1_3 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC1_3, 3 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC1_4 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC1_4 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC1_4 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC1_4, 4 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC1_5 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC1_5 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC1_5 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC1_5, 5 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC1_6 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC1_6 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC1_6 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC1_6, 6 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC1_7 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC1_7 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC1_7 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC1_7, 7 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC2_0 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC2_0 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC2_0 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC2_0, 0 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC2_1 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC2_1 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC2_1 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC2_1, 1 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC2_2 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC2_2 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC2_2 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC2_2, 2 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC2_3 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC2_3 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC2_3 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC2_3, 3 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC2_4 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC2_4 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC2_4 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC2_4, 4 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC2_5 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC2_5 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC2_5 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC2_5, 5 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC2_6 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC2_6 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC2_6 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC2_6, 6 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for WEIGHT_FC2_7 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_WEIGHT * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for WEIGHT_FC2_7 array" << endl << endl;
		return EXIT_FAILURE;
	}
	WEIGHT_FC2_7 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(WEIGHT_FC2_7, 7 * SIZE_WEIGHT, SIZE_WEIGHT, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_weight.bin");
	cout << "Generated " << SIZE_WEIGHT << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC1_0 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC1 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC1_0 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC1_0 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC1_0, 0 * SIZE_BIAS_FC1, SIZE_BIAS_FC1, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC1 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC1_1 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC1 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC1_1 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC1_1 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC1_1, 1 * SIZE_BIAS_FC1, SIZE_BIAS_FC1, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC1 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC1_2 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC1 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC1_2 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC1_2 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC1_2, 2 * SIZE_BIAS_FC1, SIZE_BIAS_FC1, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC1 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC1_3 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC1 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC1_3 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC1_3 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC1_3, 3 * SIZE_BIAS_FC1, SIZE_BIAS_FC1, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC1 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC1_4 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC1 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC1_4 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC1_4 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC1_4, 4 * SIZE_BIAS_FC1, SIZE_BIAS_FC1, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC1 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC1_5 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC1 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC1_5 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC1_5 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC1_5, 5 * SIZE_BIAS_FC1, SIZE_BIAS_FC1, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC1 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC1_6 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC1 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC1_6 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC1_6 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC1_6, 6 * SIZE_BIAS_FC1, SIZE_BIAS_FC1, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC1 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC1_7 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC1 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC1_7 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC1_7 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC1_7, 7 * SIZE_BIAS_FC1, SIZE_BIAS_FC1, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc1_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC1 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC2_0 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC2 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC2_0 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC2_0 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC2_0, 0 * SIZE_BIAS_FC2, SIZE_BIAS_FC2, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC2 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC2_1 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC2 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC2_1 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC2_1 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC2_1, 1 * SIZE_BIAS_FC2, SIZE_BIAS_FC2, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC2 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC2_2 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC2 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC2_2 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC2_2 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC2_2, 2 * SIZE_BIAS_FC2, SIZE_BIAS_FC2, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC2 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC2_3 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC2 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC2_3 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC2_3 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC2_3, 3 * SIZE_BIAS_FC2, SIZE_BIAS_FC2, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC2 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC2_4 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC2 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC2_4 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC2_4 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC2_4, 4 * SIZE_BIAS_FC2, SIZE_BIAS_FC2, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC2 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC2_5 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC2 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC2_5 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC2_5 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC2_5, 5 * SIZE_BIAS_FC2, SIZE_BIAS_FC2, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC2 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC2_6 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC2 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC2_6 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC2_6 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC2_6, 6 * SIZE_BIAS_FC2, SIZE_BIAS_FC2, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC2 << " values" << endl;

	cout << "HOST-Info: Allocating memory for BIAS_FC2_7 ... ";
	if (posix_memalign(&ptr, 4096, SIZE_BIAS_FC2 * sizeof(uint16))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for BIAS_FC2_7 array" << endl << endl;
		return EXIT_FAILURE;
	}
	BIAS_FC2_7 = reinterpret_cast<uint16*>(ptr);
	loadData_uint16(BIAS_FC2_7, 7 * SIZE_BIAS_FC2, SIZE_BIAS_FC2, "/home/undergraduate/ytliu24/vitis_workspace/weights/language_model_model_layers_0_mlp_fc2_bias.bin");
	cout << "Generated " << SIZE_BIAS_FC2 << " values" << endl;

	cout << "HOST-Info: Allocating memory for OUT ... ";
	if (posix_memalign(&ptr, 4096, SIZE_OUT*sizeof(fixed32_14))) {
		cout << endl << "HOST-Error: Out of Memory during memory allocation for OUT array" << endl << endl;
		return EXIT_FAILURE;
	}
	OUT = reinterpret_cast<fixed32_14*>(ptr);
	cout << "Allocated" << endl;

	cout << endl;

	// ------------------------------------------------------------------
	// Step 4.2: Create Buffers in Global Memory to store data
	//             o) buffer_phi_mlp_out
    //             o) buffer_phi_mlp_in
    //             o) buffer_phi_mlp_weight
    //             o) buffer_phi_mlp_bias
	// ------------------------------------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST-Info: Allocating buffers ..." << endl;
	#endif
	cl_mem_ext_ptr_t bank_ext;

	cl_mem buffer_phi_mlp_out, buffer_phi_mlp_in;
	cl_mem buffer_phi_mlp_fc1_weight[8], buffer_phi_mlp_fc1_bias[8];
	cl_mem buffer_phi_mlp_fc2_weight[8], buffer_phi_mlp_fc2_bias[8];

	// size 和 read / write 權限要再修正
	setBankExtensionPointer(bank_ext, 0, OUT, 0); // bank0
	OCL_CHECK(errCode, buffer_phi_mlp_out = clCreateBuffer(Context, CL_MEM_WRITE_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_OUT * sizeof(fixed32_14), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 0, IN, 0); // bank0
	OCL_CHECK(errCode, buffer_phi_mlp_in = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_IN * sizeof(fixed32_14), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 1, WEIGHT_FC1_0, 0); // bank1
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_weight[0] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 2, WEIGHT_FC1_1, 0); // bank2
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_weight[1] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 3, WEIGHT_FC1_2, 0); // bank3
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_weight[2] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 4, WEIGHT_FC1_3, 0); // bank4
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_weight[3] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 5, WEIGHT_FC1_4, 0); // bank5
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_weight[4] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 6, WEIGHT_FC1_5, 0); // bank6
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_weight[5] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 7, WEIGHT_FC1_6, 0); // bank7
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_weight[6] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 8, WEIGHT_FC1_7, 0); // bank8
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_weight[7] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 1, BIAS_FC1_0, 0); // bank1
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_bias[0] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC1 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 2, BIAS_FC1_1, 0); // bank2
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_bias[1] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC1 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 3, BIAS_FC1_2, 0); // bank3
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_bias[2] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC1 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 4, BIAS_FC1_3, 0); // bank4
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_bias[3] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC1 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 5, BIAS_FC1_4, 0); // bank5
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_bias[4] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC1 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 6, BIAS_FC1_5, 0); // bank6
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_bias[5] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC1 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 7, BIAS_FC1_6, 0); // bank7
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_bias[6] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC1 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 8, BIAS_FC1_7, 0); // bank8
	OCL_CHECK(errCode, buffer_phi_mlp_fc1_bias[7] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC1 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 9, WEIGHT_FC2_0, 0); // bank9
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_weight[0] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 10, WEIGHT_FC2_1, 0); // bank10
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_weight[1] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 11, WEIGHT_FC2_2, 0); // bank11
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_weight[2] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 12, WEIGHT_FC2_3, 0); // bank12
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_weight[3] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 13, WEIGHT_FC2_4, 0); // bank13
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_weight[4] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 14, WEIGHT_FC2_5, 0); // bank14
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_weight[5] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 15, WEIGHT_FC2_6, 0); // bank15
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_weight[6] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 16, WEIGHT_FC2_7, 0); // bank16
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_weight[7] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_WEIGHT * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 9, BIAS_FC2_0, 0); // bank9
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_bias[0] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC2 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 10, BIAS_FC2_1, 0); // bank10
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_bias[1] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC2 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 11, BIAS_FC2_2, 0); // bank11
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_bias[2] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC2 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 12, BIAS_FC2_3, 0); // bank12
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_bias[3] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC2 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 13, BIAS_FC2_4, 0); // bank13
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_bias[4] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC2 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 14, BIAS_FC2_5, 0); // bank14
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_bias[5] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC2 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 15, BIAS_FC2_6, 0); // bank15
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_bias[6] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC2 * sizeof(uint16), &bank_ext, &errCode));
	setBankExtensionPointer(bank_ext, 16, BIAS_FC2_7, 0); // bank16
	OCL_CHECK(errCode, buffer_phi_mlp_fc2_bias[7] = clCreateBuffer(Context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR | CL_MEM_EXT_PTR_XILINX, SIZE_BIAS_FC2 * sizeof(uint16), &bank_ext, &errCode));

	// ============================================================================
	// Step 5: Set Kernel Arguments and Run the Application
	//         o) Set Kernel Arguments
	// 				------------------------------------------------------------
	// 				 Kernel	  		    Argument Nb		Description
	// 				------------------------------------------------------------
	//  			 kernel_phi_mlp	0				buffer_phi_mlp_out
    //  			 kernel_phi_mlp	1				buffer_phi_mlp_in
    //  			 kernel_phi_mlp	2				buffer_phi_mlp_weight
    //  			 kernel_phi_mlp	3				buffer_phi_mlp_bias
	// 				------------------------------------------------------------
	//         o) Copy Input Data from Host to Global Memory
	//         o) Submit Kernels for Execution
	//         o) Copy Results from Global Memory to Host
	// ============================================================================
	// TODO 這裡要改
	int Nb_Of_Mem_Events = 35,
		Nb_Of_Exe_Events = 1;

	cl_event Mem_op_event[Nb_Of_Mem_Events],
	          K_exe_event[Nb_Of_Exe_Events];


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

	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 0, sizeof(cl_mem), &buffer_phi_mlp_out));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 1, sizeof(cl_mem), &buffer_phi_mlp_in));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 2, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[0]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 3, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[1]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 4, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[2]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 5, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[3]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 6, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[4]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 7, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[5]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 8, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[6]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 9, sizeof(cl_mem), &buffer_phi_mlp_fc1_weight[7]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 10, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[0]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 11, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[1]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 12, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[2]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 13, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[3]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 14, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[4]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 15, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[5]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 16, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[6]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 17, sizeof(cl_mem), &buffer_phi_mlp_fc1_bias[7]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 18, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[0]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 19, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[1]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 20, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[2]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 21, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[3]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 22, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[4]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 23, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[5]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 24, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[6]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 25, sizeof(cl_mem), &buffer_phi_mlp_fc2_weight[7]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 26, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[0]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 27, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[1]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 28, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[2]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 29, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[3]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 30, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[4]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 31, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[5]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 32, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[6]));
	OCL_CHECK(errCode, errCode = clSetKernelArg(kernel_phi_mlp, 33, sizeof(cl_mem), &buffer_phi_mlp_fc2_bias[7]));


	// ------------------------------------------------------
	// Step 5.2: Copy Input data from Host to Global Memory
	// ------------------------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST_Info: Copy Input data to Global Memory ..." << endl;
	#endif

	// clEnqueueMigrateMemObjects(cl_command_queue, number of cl_uint, cl_mem*, cl_mem_migration_flags, number of pending events, pending cl_event*, generate cl_event*)

	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_in, 0, 0, NULL, &Mem_op_event[0]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_weight[0], 0, 0, NULL, &Mem_op_event[1]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_weight[1], 0, 0, NULL, &Mem_op_event[2]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_weight[2], 0, 0, NULL, &Mem_op_event[3]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_weight[3], 0, 0, NULL, &Mem_op_event[4]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_weight[4], 0, 0, NULL, &Mem_op_event[5]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_weight[5], 0, 0, NULL, &Mem_op_event[6]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_weight[6], 0, 0, NULL, &Mem_op_event[7]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_weight[7], 0, 0, NULL, &Mem_op_event[8]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_bias[0], 0, 0, NULL, &Mem_op_event[9]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_bias[1], 0, 0, NULL, &Mem_op_event[10]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_bias[2], 0, 0, NULL, &Mem_op_event[11]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_bias[3], 0, 0, NULL, &Mem_op_event[12]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_bias[4], 0, 0, NULL, &Mem_op_event[13]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_bias[5], 0, 0, NULL, &Mem_op_event[14]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_bias[6], 0, 0, NULL, &Mem_op_event[15]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc1_bias[7], 0, 0, NULL, &Mem_op_event[16]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_weight[0], 0, 0, NULL, &Mem_op_event[17]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_weight[1], 0, 0, NULL, &Mem_op_event[18]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_weight[2], 0, 0, NULL, &Mem_op_event[19]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_weight[3], 0, 0, NULL, &Mem_op_event[20]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_weight[4], 0, 0, NULL, &Mem_op_event[21]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_weight[5], 0, 0, NULL, &Mem_op_event[22]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_weight[6], 0, 0, NULL, &Mem_op_event[23]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_weight[7], 0, 0, NULL, &Mem_op_event[24]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_bias[0], 0, 0, NULL, &Mem_op_event[25]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_bias[1], 0, 0, NULL, &Mem_op_event[26]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_bias[2], 0, 0, NULL, &Mem_op_event[27]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_bias[3], 0, 0, NULL, &Mem_op_event[28]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_bias[4], 0, 0, NULL, &Mem_op_event[29]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_bias[5], 0, 0, NULL, &Mem_op_event[30]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_bias[6], 0, 0, NULL, &Mem_op_event[31]));
	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_fc2_bias[7], 0, 0, NULL, &Mem_op_event[32]));

	// --------------------------------------------------------

	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_out, CL_MIGRATE_MEM_OBJECT_CONTENT_UNDEFINED, 0, NULL, &Mem_op_event[33]));

	// --------------------------------------------------------

	OCL_CHECK(errCode, errCode = clEnqueueBarrierWithWaitList(Command_Queue, 0, NULL, NULL));

	// ----------------------------------------
	// Step 5.3: Submit Kernels for Execution
	// ----------------------------------------

	cout << "HOST-Info: Submitting Kernel kernel_phi_mlp for Execution ..." << endl;

	OCL_CHECK(errCode, errCode = clEnqueueTask(Command_Queue, kernel_phi_mlp, 0, NULL, &K_exe_event[0]));

	// ---------------------------------------------------------
	// Step 5.4: Submit Copy Results from Global Memory to Host
	// ---------------------------------------------------------
	#ifdef ALL_MESSAGES
	cout << "HOST_Info: Submitting Copy Results data from Global Memory to Host ..." << endl;
	#endif

	OCL_CHECK(errCode, errCode = clEnqueueMigrateMemObjects(Command_Queue, 1, &buffer_phi_mlp_out, CL_MIGRATE_MEM_OBJECT_HOST, 1, &K_exe_event[0], &Mem_op_event[34]));

	cout << endl << "HOST_Info: Waiting for application to be completed ..." << endl;
	clFinish(Command_Queue);


	// ============================================================================
	// Step 6: Processing Output Results
	//         o) Store output results to a RES.txt file
	//         o) Check correctness of the output results
	// ============================================================================
	#ifdef ALL_MESSAGES
	cout << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	cout << "HOST-Info: (Step 6) Check the Output Results                             " << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	#endif

	// ------------------------------------------------------
	// Step 6: Check Output Results
	// ------------------------------------------------------
	cout << "Result: ";
	for (int i = 0; i < 10; i++) {
		cout << OUT[i] << (i == 9 ? '\n' : ' ');
	}

	// ============================================================================
	// Step 7: Custom Profiling
	// ============================================================================
	cout << "HOST-Info: ============================================================= " << endl;
	cout << "HOST-Info: (Step 7) Custom Profiling                                     " << endl;
	cout << "HOST-Info: ============================================================= " << endl;
	int Nb_Of_Kernels = Nb_Of_Exe_Events;
	int Nb_Of_Memory_Tranfers = Nb_Of_Mem_Events;

	string list_of_kernel_names[Nb_Of_Kernels]={"kernel_phi_mlp"};
	run_custom_profiling (Nb_Of_Kernels, Nb_Of_Memory_Tranfers, K_exe_event, Mem_op_event, list_of_kernel_names);

	// ============================================================================
	// Step 8: Release Allocated Resources
	// ============================================================================
	clReleaseDevice(Target_Device_ID); // Only available in OpenCL >= 1.2

	for (int i = 0; i < Nb_Of_Mem_Events; i++) clReleaseEvent(Mem_op_event[i]);
	for (int i = 0; i < Nb_Of_Exe_Events; i++) clReleaseEvent(K_exe_event[i]);

	clReleaseMemObject(buffer_phi_mlp_out);
	clReleaseMemObject(buffer_phi_mlp_in);
	for (int i = 0; i < 8; i++) {
		clReleaseMemObject(buffer_phi_mlp_fc1_weight[i]);
		clReleaseMemObject(buffer_phi_mlp_fc1_bias[i]);
		clReleaseMemObject(buffer_phi_mlp_fc2_weight[i]);
		clReleaseMemObject(buffer_phi_mlp_fc2_bias[i]);
	}

	clReleaseKernel(kernel_phi_mlp);

	clReleaseProgram(Program);
	clReleaseCommandQueue(Command_Queue);
	clReleaseContext(Context);

	free(Platform_IDs);
	free(Device_IDs);

	free(IN);
	free(OUT);
	free(WEIGHT_FC1_0);
	free(WEIGHT_FC1_1);
	free(WEIGHT_FC1_2);
	free(WEIGHT_FC1_3);
	free(WEIGHT_FC1_4);
	free(WEIGHT_FC1_5);
	free(WEIGHT_FC1_6);
	free(WEIGHT_FC1_7);
	free(WEIGHT_FC2_0);
	free(WEIGHT_FC2_1);
	free(WEIGHT_FC2_2);
	free(WEIGHT_FC2_3);
	free(WEIGHT_FC2_4);
	free(WEIGHT_FC2_5);
	free(WEIGHT_FC2_6);
	free(WEIGHT_FC2_7);
	free(BIAS_FC1_0);
	free(BIAS_FC1_1);
	free(BIAS_FC1_2);
	free(BIAS_FC1_3);
	free(BIAS_FC1_4);
	free(BIAS_FC1_5);
	free(BIAS_FC1_6);
	free(BIAS_FC1_7);
	free(BIAS_FC2_0);
	free(BIAS_FC2_1);
	free(BIAS_FC2_2);
	free(BIAS_FC2_3);
	free(BIAS_FC2_4);
	free(BIAS_FC2_5);
	free(BIAS_FC2_6);
	free(BIAS_FC2_7);

	cout << endl << "HOST-Info: DONE" << endl << endl;

	return EXIT_SUCCESS;
}


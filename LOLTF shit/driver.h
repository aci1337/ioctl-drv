#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <thread>
#include <mutex>
#include <vector>

#include <wininet.h>
#pragma comment(lib, "wininet.lib")

#include <dwmapi.h>
#pragma comment (lib, "dwmapi.lib")

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#pragma comment (lib, "d3d9.lib")

#pragma warning (disable : 26495)
#pragma warning (disable : 4702)

#define PI 3.14159265358979323846f
#define M_PI 3.14159265358979323846264338327950288419716939937510

int center_x;
int center_y;
int Width;
int Height;

HANDLE hDriver;

class Memory
{
public:
	Memory(DWORD PID);

	uintptr_t GetBaseAddress(const std::string& module_name);

}; extern Memory* pMem;

std::vector<std::thread> thread_pool;
std::mutex mtx;

const size_t max_threads = std::thread::hardware_concurrency();
#define read_memm CTL_CODE(FILE_DEVICE_UNKNOWN, 0x3412B5, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define write_mem CTL_CODE(FILE_DEVICE_UNKNOWN, 0x5122A7, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define ioctl_get_module_base CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4173B3, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) 
#define ioctl_protect_virutal_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6123D1, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) 
#define ioctl_allocate_virtual_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x7212C8, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

typedef struct _k_attach_process_request
{
	ULONGLONG pid;
} k_attach_process_request, * pk_attach_process_request;


DWORD KM_PID;

typedef struct _K_RW_REQUEST {
	ULONG PID;
	ULONGLONG src;
	ULONGLONG dst;
	ULONGLONG size;
} K_RW_REQUEST, * PK_RW_REQUEST;

typedef struct _K_GET_BASE_MODULE_REQUEST {
	ULONG PID;
	ULONGLONG handle;
	WCHAR name[260];
} K_GET_BASE_MODULE_REQUEST, * PK_GET_BASE_MODULE_REQUEST;
typedef struct _k_alloc_mem_request {
	ULONG64 pid;
	PVOID addr;
	SIZE_T size;
	ULONG allocation_type;
	ULONG protect;
} k_alloc_mem_request, * pk_alloc_mem_request;
typedef struct _k_free_mem_request
{
	ULONGLONG pid;
	ULONGLONG addr;
	ULONG free_type;
} k_free_mem_request, * pk_free_mem_request;

BOOL Setup() {

	hDriver = CreateFileW((L"\\\\.\\\WeLoveToto"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hDriver == INVALID_HANDLE_VALUE) {
		printf(" Driver not loaded.\n");
		return false;
	}
	return true;
}

Memory::Memory(DWORD PID) {
	KM_PID = PID;
	Setup();
}


uintptr_t Memory::GetBaseAddress(const std::string& module_name) {
	K_GET_BASE_MODULE_REQUEST request;
	request.PID = KM_PID;
	request.handle = 0;

	std::wstring wstr(module_name.begin(), module_name.end());
	ZeroMemory(request.name, sizeof(request.name));
	wcscpy_s(request.name, sizeof(request.name) / sizeof(WCHAR), wstr.c_str());

	DWORD junk;
	BOOL status = DeviceIoControl(hDriver, ioctl_get_module_base, &request, sizeof(K_GET_BASE_MODULE_REQUEST), &request, sizeof(K_GET_BASE_MODULE_REQUEST), &junk, nullptr);

	if (status) {
		return request.handle;
	}
	else {
		printf(" Driver: failure to get base address.\n");
		return 0;
	}

}
typedef struct _k_get_base_module_request {
	ULONG pid;
	ULONGLONG handle;
	WCHAR name[260];
} k_get_base_module_request, * pk_get_base_module_request;

typedef struct _k_rw_request {
	ULONG pid;
	ULONGLONG src;
	ULONGLONG dst;
	ULONGLONG size;
} k_rw_request, * pk_rw_request;

typedef struct _k_protect_mem_request {
	ULONG pid, protect;
	ULONGLONG addr;
	SIZE_T size;
} k_protect_mem_request, * pk_protect_mem_request;
typedef NTSTATUS(*NtAllocateVirtualMemory_t)(HANDLE, PVOID*, ULONG_PTR, SIZE_T*, ULONG, ULONG);

PVOID allocate_memory_kernel(SIZE_T size, ULONG protection)
{
	k_alloc_mem_request requestas;
	requestas.pid = GetCurrentProcessId();
	requestas.addr = NULL;
	requestas.size = size;
	requestas.allocation_type = MEM_COMMIT | MEM_RESERVE;
	requestas.protect = protection;

	DWORD bytes_returned;
	BOOL status = DeviceIoControl(hDriver, ioctl_allocate_virtual_memory, &requestas, sizeof(requestas), &requestas, sizeof(requestas), &bytes_returned, NULL);
	if (!status)
	{
		printf(" Driver: failure to allocate virtual memory.\n");
	}

	return requestas.addr;
}

void ReadMemoryFromKernel(int processId, uint64_t address, void* buffer, size_t size)
{
	if (processId <= 0 || address == 0 || buffer == NULL || size == 0)
	{
		// Invalid parameters
		return;
	}

	k_rw_request request;
	request.pid = processId;
	request.src = address;
	request.dst = (uint64_t)buffer;
	request.size = size;

	OVERLAPPED ovl = { 0 };
	DWORD bytesReturned;

	BOOL status = DeviceIoControl(hDriver, read_memm, &request, sizeof(K_RW_REQUEST), &request, sizeof(K_RW_REQUEST), &bytesReturned, &ovl);
	if (!status)
	{
		//printf(" Driver: failure to read virtual memory.\n");
	}
}

void WriteMemoryFromKernel(int processId, uint64_t address, void* buffer, size_t size)
{
	if (processId <= 0 || address == 0 || buffer == NULL || size == 0)
	{
		// Invalid parameters
		return;
	}

	k_rw_request request;
	request.pid = processId;
	request.src = address;
	request.dst = (uint64_t)buffer;
	request.size = size;

	OVERLAPPED ovl = { 0 };
	DWORD bytesReturned;

	BOOL status = DeviceIoControl(hDriver, write_mem, &request, sizeof(K_RW_REQUEST), &request, sizeof(K_RW_REQUEST), &bytesReturned, &ovl);
	if (!status)
	{
		//printf(" Driver: failure to write virtual memory.\n");
	}
}

template <typename T>
typename std::enable_if<!std::is_pointer<T>::value, T>::type Rpm(uint64_t address) {
	T buffer;
	ReadMemoryFromKernel(KM_PID, address, &buffer, sizeof(T));
	return buffer;
}

bool Rpms(PVOID address, void* buffer, size_t size)
{
	if (address == nullptr || buffer == nullptr || size == 0) {
		// Invalid parameters
		return false;
	}
	ReadMemoryFromKernel(KM_PID, reinterpret_cast<uint64_t>(address), buffer, size);
	return true;
}


bool Wpma(PVOID address, void* buffer, size_t size)
{
	if (address == nullptr || buffer == nullptr || size == 0) {
		// Invalid parameters
		return false;
	}
	WriteMemoryFromKernel(KM_PID, reinterpret_cast<uint64_t>(address), buffer, size);
	return true;
}

template<typename T>
inline void Wpm(uint64_t address, T value)
{
	Wpma((PVOID)address, &value, sizeof(T));
}

Memory* UmDrv = nullptr;

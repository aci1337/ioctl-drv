#pragma once 
#include <ntdef.h>
#include <ntifs.h>
#include <ntddk.h>
#include <windef.h>
ULONGLONG get_cr3_value(ULONG pid);


typedef unsigned long long QWORD;
typedef unsigned short WORD;

typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
	HANDLE Section;
	PVOID MappedBase;
	PVOID ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT OffsetToFileName;
	UCHAR  FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, * PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES
{
	ULONG NumberOfModules;
	RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, * PRTL_PROCESS_MODULES;

typedef struct _NON_PAGED_DEBUG_INFO
{
	USHORT      Signature;
	USHORT      Flags;
	ULONG       Size;
	USHORT      Machine;
	USHORT      Characteristics;
	ULONG       TimeDateStamp;
	ULONG       CheckSum;
	ULONG       SizeOfImage;
	ULONGLONG   ImageBase;
} NON_PAGED_DEBUG_INFO, * PNON_PAGED_DEBUG_INFO;

typedef struct _KLDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InLoadOrderLinks;
	PVOID ExceptionTable;
	ULONG ExceptionTableSize;
	// ULONG padding on IA64
	PVOID GpValue;
	PNON_PAGED_DEBUG_INFO NonPagedDebugInfo;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	USHORT LoadCount;
	USHORT __Unused5;
	PVOID SectionPointer;
	ULONG CheckSum;
	// ULONG padding on IA64
	PVOID LoadedImports;
	PVOID PatchInformation;
} KLDR_DATA_TABLE_ENTRY, * PKLDR_DATA_TABLE_ENTRY;

typedef struct _LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	WORD LoadCount;
	WORD TlsIndex;
	union
	{
		LIST_ENTRY HashLinks;
		struct
		{
			PVOID SectionPointer;
			ULONG CheckSum;
		};
	};
	union
	{
		ULONG TimeDateStamp;
		PVOID LoadedImports;
	};
	VOID* EntryPointActivationContext;
	PVOID PatchInformation;
	LIST_ENTRY ForwarderLinks;
	LIST_ENTRY ServiceTagLinks;
	LIST_ENTRY StaticLinks;
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

typedef struct _RTL_CRITICAL_SECTION_DEBUG
{
	WORD Type;
	WORD CreatorBackTraceIndex;
	VOID* CriticalSection;
	LIST_ENTRY ProcessLocksList;
	ULONG EntryCount;
	ULONG ContentionCount;
	ULONG Flags;
	WORD CreatorBackTraceIndexHigh;
	WORD SpareUSHORT;
} RTL_CRITICAL_SECTION_DEBUG, * PRTL_CRITICAL_SECTION_DEBUG;

typedef struct _RTL_CRITICAL_SECTION
{
	VOID* DebugInfo;
	LONG LockCount;
	LONG RecursionCount;
	PVOID OwningThread;
	PVOID LockSemaphore;
	ULONG SpinCount;
} RTL_CRITICAL_SECTION, * PRTL_CRITICAL_SECTION;

typedef struct _PEB_LDR_DATA
{
	ULONG Length;
	UCHAR Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID EntryInProgress;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _PEB
{
	UCHAR InheritedAddressSpace;
	UCHAR ReadImageFileExecOptions;
	UCHAR BeingDebugged;
	UCHAR BitField;
	ULONG ImageUsesLargePages : 1;
	ULONG IsProtectedProcess : 1;
	ULONG IsLegacyProcess : 1;
	ULONG IsImageDynamicallyRelocated : 1;
	ULONG SpareBits : 4;
	PVOID Mutant;
	PVOID ImageBaseAddress;
	PPEB_LDR_DATA Ldr;
	VOID* ProcessParameters;
	PVOID SubSystemData;
	PVOID ProcessHeap;
	PRTL_CRITICAL_SECTION FastPebLock;
	PVOID AtlThunkSListPtr;
	PVOID IFEOKey;
	ULONG CrossProcessFlags;
	ULONG ProcessInJob : 1;
	ULONG ProcessInitializing : 1;
	ULONG ReservedBits0 : 30;
	union
	{
		PVOID KernelCallbackTable;
		PVOID UserSharedInfoPtr;
	};
	ULONG SystemReserved[1];
	ULONG SpareUlong;
	VOID* FreeList;
	ULONG TlsExpansionCounter;
	PVOID TlsBitmap;
	ULONG TlsBitmapBits[2];
	PVOID ReadOnlySharedMemoryBase;
	PVOID HotpatchInformation;
	VOID** ReadOnlyStaticServerData;
	PVOID AnsiCodePageData;
	PVOID OemCodePageData;
	PVOID UnicodeCaseTableData;
	ULONG NumberOfProcessors;
	ULONG NtGlobalFlag;
	LARGE_INTEGER CriticalSectionTimeout;
	ULONG HeapSegmentReserve;
	ULONG HeapSegmentCommit;
	ULONG HeapDeCommitTotalFreeThreshold;
	ULONG HeapDeCommitFreeBlockThreshold;
	ULONG NumberOfHeaps;
	ULONG MaximumNumberOfHeaps;
	VOID** ProcessHeaps;
	PVOID GdiSharedHandleTable;
	PVOID ProcessStarterHelper;
	ULONG GdiDCAttributeList;
	PRTL_CRITICAL_SECTION LoaderLock;
	ULONG OSMajorVersion;
	ULONG OSMinorVersion;
	WORD OSBuildNumber;
	WORD OSCSDVersion;
	ULONG OSPlatformId;
	ULONG ImageSubsystem;
	ULONG ImageSubsystemMajorVersion;
	ULONG ImageSubsystemMinorVersion;
	ULONG ImageProcessAffinityMask;
	ULONG GdiHandleBuffer[34];
	PVOID PostProcessInitRoutine;
	PVOID TlsExpansionBitmap;
	ULONG TlsExpansionBitmapBits[32];
	ULONG SessionId;
	ULARGE_INTEGER AppCompatFlags;
	ULARGE_INTEGER AppCompatFlagsUser;
	PVOID pShimData;
	PVOID AppCompatInfo;
	UNICODE_STRING CSDVersion;
	VOID* ActivationContextData;
	VOID* ProcessAssemblyStorageMap;
	VOID* SystemDefaultActivationContextData;
	VOID* SystemAssemblyStorageMap;
	ULONG MinimumStackCommit;
	VOID* FlsCallback;
	LIST_ENTRY FlsListHead;
	PVOID FlsBitmap;
	ULONG FlsBitmapBits[4];
	ULONG FlsHighIndex;
	PVOID WerRegistrationData;
	PVOID WerShipAssertPtr;
} PEB, * PPEB;

NTKERNELAPI
NTSTATUS
PsLookupProcessByProcessId(
	IN HANDLE ProcessId,
	OUT PEPROCESS* Process
);

extern "C" NTSTATUS NTAPI MmCopyVirtualMemory(
	PEPROCESS SourceProcess,
	PVOID SourceAddress,
	PEPROCESS TargetProcess,
	PVOID TargetAddress,
	SIZE_T BufferSize,
	KPROCESSOR_MODE PreviousMode,
	PSIZE_T ReturnSize
);

NTSTATUS ZwAllocateVirtualMemory(
	_In_    HANDLE    ProcessHandle,
	_Inout_ PVOID* BaseAddress,
	_In_    ULONG_PTR ZeroBits,
	_Inout_ PSIZE_T   RegionSize,
	_In_    ULONG     AllocationType,
	_In_    ULONG     Protect
);

extern "C" NTKERNELAPI PPEB PsGetProcessPeb(
	IN PEPROCESS Process
);

extern "C"
NTSYSAPI
NTSTATUS
NTAPI
ZwProtectVirtualMemory(
	__in HANDLE ProcessHandle,
	__inout PVOID * BaseAddress,
	__inout PSIZE_T RegionSize,
	__in ULONG NewProtect,
	__out PULONG OldProtect
);
#define read_memm CTL_CODE(FILE_DEVICE_UNKNOWN, 0x3412B5, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define write_mem CTL_CODE(FILE_DEVICE_UNKNOWN, 0x5122A7, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define ioctl_get_module_base CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4173B3, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) 
#define ioctl_protect_virutal_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6123D1, METHOD_BUFFERED, FILE_SPECIAL_ACCESS) 
#define ioctl_allocate_virtual_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x7212L8, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
typedef struct _SYSTEM_BIGPOOL_ENTRY
{
	union {
		PVOID VirtualAddress;
		ULONG_PTR NonPaged : 1;
	};
	ULONG_PTR SizeInBytes;
	union {
		UCHAR Tag[4];
		ULONG TagUlong;
	};
} SYSTEM_BIGPOOL_ENTRY, * PSYSTEM_BIGPOOL_ENTRY;

typedef struct _SYSTEM_BIGPOOL_INFORMATION {
	ULONG Count;
	SYSTEM_BIGPOOL_ENTRY AllocatedInfo[ANYSIZE_ARRAY];
} SYSTEM_BIGPOOL_INFORMATION, * PSYSTEM_BIGPOOL_INFORMATION;

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBigPoolInformation = 0x42
} SYSTEM_INFORMATION_CLASS;
extern "C" NTSTATUS NTAPI IoCreateDriver(PUNICODE_STRING DriverName, PDRIVER_INITIALIZE InitializationFunction);
extern "C" PVOID NTAPI PsGetProcessSectionBaseAddress(PEPROCESS Process);
extern "C" NTSTATUS NTAPI ZwQuerySystemInformation(SYSTEM_INFORMATION_CLASS systemInformationClass, PVOID systemInformation, ULONG systemInformationLength, PULONG returnLength);
typedef struct _set_module_information
{
	ULONG pid;
	wchar_t sz_name[397523390];
} set_module_information, * pset_module_information;

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

typedef struct _k_alloc_mem_request {
	ULONG pid, allocation_type, protect;
	ULONGLONG addr;
	SIZE_T size;
} k_alloc_mem_request, * pk_alloc_mem_request;

typedef struct _k_protect_mem_request {
	ULONG pid, protect;
	ULONGLONG addr;
	SIZE_T size;
} k_protect_mem_request, * pk_protect_mem_request;

#define drv_device L"\\Device\\WeLoveToto"
#define drv_dos_device L"\\DosDevices\\WeLoveToto"
#define drv  L"\\Driver\\WeLoveToto"
LONG_PTR __readcr0();
VOID __writecr0(ULONG_PTR Value);
PDEVICE_OBJECT driver_object;
UNICODE_STRING dev, dos;
void ClearCR0Bit();
__inline NTSTATUS copy_memory(PEPROCESS src_proc, PEPROCESS target_proc, PVOID src, PVOID dst, SIZE_T size);
ULONGLONG get_module_handle(ULONG pid, LPCWSTR module_name);

void RestoreCR0Bit();
void read_mem(int pid, void* addr, void* value, size_t size) {
	PEPROCESS t_process;
	SIZE_T bytes;
	NTSTATUS proc_exists;
	proc_exists = PsLookupProcessByProcessId((HANDLE)pid, &t_process);

	if (NT_SUCCESS(proc_exists)) {
		PVOID target_address = addr;
		PVOID target_buffer = NULL;
		PMDL mdl = NULL;

		__try {
			mdl = IoAllocateMdl(target_address, size, FALSE, FALSE, NULL);
			if (!mdl) {
				__leave;
			}

			MmProbeAndLockPages(mdl, UserMode, IoReadAccess);

			target_buffer = MmMapLockedPagesSpecifyCache(mdl, UserMode, MmCached, NULL, FALSE, NormalPagePriority);

			if (!target_buffer) {
				__leave;
			}

			RtlCopyMemory(value, target_buffer, size);
		}
		__finally {
			if (target_buffer) {
				MmUnmapLockedPages(target_buffer, mdl);
			}

			if (mdl) {
				MmUnlockPages(mdl);
				IoFreeMdl(mdl);
			}

			ObDereferenceObjectWithTag(t_process, 'tMem');
		}
	}
}
typedef union _CR3_REG
{
	struct
	{
		ULONG_PTR Reserved1 : 3;
		ULONG_PTR WriteThrough : 1;
		ULONG_PTR CacheDisable : 1;
		ULONG_PTR Reserved2 : 7;
		ULONG_PTR PageDirectoryBase : 20;
		ULONG_PTR Paging : 1;                    // Bit 31

	};

	ULONG_PTR Value;
} CR3_REG;

typedef union _CR0_REG
{
	struct
	{
		ULONG ProtectionEnable : 1;          // Bit 0
		ULONG MonitorCoprocessor : 1;        // Bit 1
		ULONG Emulation : 1;                 // Bit 2
		ULONG TaskSwitched : 1;              // Bit 3
		ULONG ExtensionType : 1;             // Bit 4
		ULONG NumericError : 1;              // Bit 5
		ULONG WriteProtect : 1;              // Bit 16
		ULONG AlignmentMask : 1;             // Bit 18
		ULONG NotWriteThrough : 1;           // Bit 29
		ULONG CacheDisable : 1;              // Bit 30
		ULONG Paging : 1;                    // Bit 31
	};
	ULONG_PTR Value;
} CR0_REG;
LONG_PTR __readcr0()
{
	CR0_REG cr0;
	cr0.Value = 0;
	return cr0.Value;
}
VOID __writecr0(ULONG_PTR Value)
{
	CR0_REG cr0;
	cr0.Value = __readcr0();
	cr0.Paging = Value & 0x80000000;
	cr0.CacheDisable = Value & 0x40000000;
	cr0.NotWriteThrough = Value & 0x20000000;
	cr0.AlignmentMask = Value & 0x40000;
	cr0.WriteProtect = Value & 0x10000;
	__writecr0(cr0.Value);
}
LONG_PTR __readcr3()
{
	CR3_REG cr3;
	cr3.Value = 0;
	return cr3.Value;
}
VOID __writecr3(ULONG_PTR Value)
{
	CR3_REG cr3;
	cr3.Value = __readcr3();
	cr3.Paging = Value & 0x80000000;
	cr3.PageDirectoryBase = Value & 0x7FFFFFFF;
	__writecr3(cr3.Value);
}
void ClearCR3Bit()
{
	ULONG_PTR dwCr3 = __readcr3();
	dwCr3 &= 0xFFFEFFFF;
	__writecr3(dwCr3);
}



void ClearCR0Bit()
{
	ULONG_PTR dwCr0 = __readcr0();
	dwCr0 &= 0xFFFEFFFF;
	__writecr0(dwCr0);
}
ULONGLONG get_cr3_value(ULONG pid) {
	PEPROCESS target_proc;
	ULONGLONG cr3_value = 0;

	if (!NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)pid, &target_proc))) {
		return 0;
	}

	KAPC_STATE apc;
	KeStackAttachProcess(target_proc, &apc);
	cr3_value = __readcr0();
	KeUnstackDetachProcess(&apc);

	ObDereferenceObjectWithTag(target_proc, 'tAws');
	return cr3_value;
}

void RestoreCR0Bit()
{
	ULONG_PTR dwCr0 = __readcr0();
	dwCr0 |= 0x00010000;
	__writecr0(dwCr0);
}


static PMDL g_cached_mdl = NULL;
static PVOID g_cached_address = NULL;
static SIZE_T g_cached_size = 0;

void write_mems(int pid, void* addr, void* value, size_t size) {
	PEPROCESS t_process;
	SIZE_T bytes;
	NTSTATUS proc_exists;
	proc_exists = PsLookupProcessByProcessId((HANDLE)pid, &t_process);

	if (NT_SUCCESS(proc_exists)) {
		PVOID target_address = addr;
		PVOID target_buffer = NULL;
		PMDL mdl = NULL;

		__try {
			if (g_cached_mdl && addr == g_cached_address && size <= g_cached_size) {
				mdl = g_cached_mdl;
			}
			else {
				if (g_cached_mdl) {
					IoFreeMdl(g_cached_mdl);
				}
				mdl = IoAllocateMdl(target_address, size, FALSE, FALSE, NULL);
				g_cached_mdl = mdl;
				g_cached_address = addr;
				g_cached_size = size;
			}

			if (!mdl) {
				__leave;
			}

			MmProbeAndLockPages(mdl, KernelMode, IoWriteAccess);

			target_buffer = MmMapLockedPagesSpecifyCache(mdl, KernelMode, MmCached, NULL, FALSE, NormalPagePriority);

			if (!target_buffer) {
				__leave;
			}

			RtlCopyMemory(target_buffer, value, size);
		}
		__finally {
			if (target_buffer) {
				MmUnmapLockedPages(target_buffer, mdl);
			}

			if (mdl) {
				MmUnlockPages(mdl);
			}

			ObDereferenceObjectWithTag(t_process, 'tMea');
		}
	}
}

NTSTATUS read_physical_memory(PVOID dst, PHYSICAL_ADDRESS src, SIZE_T size) {
	PVOID src_mapped = MmMapIoSpace(src, size, MmNonCached);
	if (src_mapped == NULL) {
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	RtlCopyMemory(dst, src_mapped, size);

	MmUnmapIoSpace(src_mapped, size);
	return STATUS_SUCCESS;
}

NTSTATUS write_physical_memory(PHYSICAL_ADDRESS src, PHYSICAL_ADDRESS dst, SIZE_T size) {
	PVOID src_mapped = MmMapIoSpace(src, size, MmNonCached);
	if (src_mapped == NULL) {
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	PVOID dst_mapped = MmMapIoSpace(dst, size, MmNonCached);
	if (dst_mapped == NULL) {
		MmUnmapIoSpace(src_mapped, size);
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	RtlCopyMemory(dst_mapped, src_mapped, size);

	MmUnmapIoSpace(src_mapped, size);
	MmUnmapIoSpace(dst_mapped, size);

	return STATUS_SUCCESS;
}

NTSTATUS copy_physical_memory(PHYSICAL_ADDRESS src, PHYSICAL_ADDRESS dst, SIZE_T size) {
	// Map the source physical address into the system address space
	PVOID src_mapped = MmMapIoSpace(src, size, MmNonCached);
	if (src_mapped == NULL) {
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	// Map the destination physical address into the system address space
	PVOID dst_mapped = MmMapIoSpace(dst, size, MmNonCached);
	if (dst_mapped == NULL) {
		MmUnmapIoSpace(src_mapped, size);
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	// Copy the memory
	RtlCopyMemory(dst_mapped, src_mapped, size);

	// Unmap the addresses
	MmUnmapIoSpace(src_mapped, size);
	MmUnmapIoSpace(dst_mapped, size);

	return STATUS_SUCCESS;
}

#define ioctl_free_virtual_memory CTL_CODE(FILE_DEVICE_UNKNOWN, 0x7973F9, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
typedef struct _k_free_mem_request
{
	ULONGLONG pid;
	ULONGLONG addr;
	ULONG free_type;
} k_free_mem_request, * pk_free_mem_request;
#define ioctl_attach_process CTL_CODE(FILE_DEVICE_UNKNOWN, 0x7973AA, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
typedef struct _k_attach_process_request
{
	ULONGLONG pid;
} k_attach_process_request, * pk_attach_process_request;

NTSTATUS UsermodeController(PDEVICE_OBJECT device, PIRP irp) {
	NTSTATUS status;
	ULONG info_size = 0;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);
	ULONG control_code = stack->Parameters.DeviceIoControl.IoControlCode;

	switch (control_code) {
	case ioctl_attach_process: {
		pk_attach_process_request in = (pk_attach_process_request)irp->AssociatedIrp.SystemBuffer;

		PEPROCESS target_proc;
		HANDLE pid_handle = (HANDLE)(ULONG_PTR)in->pid;
		NTSTATUS status = PsLookupProcessByProcessId(pid_handle, &target_proc);
		if (NT_SUCCESS(status)) {
			ObDereferenceObjectWithTag(target_proc, 'tApi');
		}

		info_size = sizeof(k_attach_process_request);
	} break;
	case ioctl_free_virtual_memory: {
		pk_free_mem_request in = (pk_free_mem_request)irp->AssociatedIrp.SystemBuffer;

		PEPROCESS target_proc;
		HANDLE pid_handle = (HANDLE)(ULONG_PTR)in->pid;
		NTSTATUS status = PsLookupProcessByProcessId(pid_handle, &target_proc);
		if (NT_SUCCESS(status)) {
			KAPC_STATE apc;
			KeStackAttachProcess(target_proc, &apc);

			PVOID addr_ptr = (PVOID)(ULONG_PTR)in->addr;
			SIZE_T size = 0;
			status = ZwFreeVirtualMemory(ZwCurrentProcess(), &addr_ptr, &size, in->free_type);

			KeUnstackDetachProcess(&apc);
			ObDereferenceObjectWithTag(target_proc, 'tFai');
		}

		info_size = sizeof(pk_free_mem_request);
	} break;

	case ioctl_protect_virutal_memory: {
		pk_protect_mem_request in = (pk_protect_mem_request)irp->AssociatedIrp.SystemBuffer;

		PEPROCESS target_proc;
		HANDLE pid_handle = (HANDLE)(ULONG_PTR)in->pid;
		NTSTATUS status = PsLookupProcessByProcessId(pid_handle, &target_proc);
		if (NT_SUCCESS(status)) {
			KAPC_STATE apc;
			ULONG old_protection;
			KeStackAttachProcess(target_proc, &apc);

			PVOID addr_ptr = (PVOID)(ULONG_PTR)in->addr;
			status = ZwProtectVirtualMemory(ZwCurrentProcess(), &addr_ptr, &in->size, in->protect, &old_protection);

			KeUnstackDetachProcess(&apc);
			in->protect = old_protection;
			ObDereferenceObjectWithTag(target_proc, 'tKma');
		}

		info_size = sizeof(k_protect_mem_request);
	} break;


	case read_memm: {
		pk_rw_request in = (pk_rw_request)irp->AssociatedIrp.SystemBuffer;

		PVOID src_ptr = (PVOID)(ULONG_PTR)in->src;
		PHYSICAL_ADDRESS src_addr = MmGetPhysicalAddress(src_ptr);

		PVOID dst_ptr = (PVOID)(ULONG_PTR)in->dst;
		PHYSICAL_ADDRESS dst_addr = MmGetPhysicalAddress(dst_ptr);

		NTSTATUS status = copy_physical_memory(src_addr, dst_addr, in->size);

		info_size = sizeof(k_rw_request);
	} break;

	case write_mem: {
		pk_rw_request in = (pk_rw_request)irp->AssociatedIrp.SystemBuffer;

		PVOID src_ptr = (PVOID)(ULONG_PTR)in->src;
		PHYSICAL_ADDRESS src_addr = MmGetPhysicalAddress(src_ptr);

		PVOID dst_ptr = (PVOID)(ULONG_PTR)in->dst;
		PHYSICAL_ADDRESS dst_addr = MmGetPhysicalAddress(dst_ptr);

		NTSTATUS status = write_physical_memory(src_addr, dst_addr, in->size);
		
		info_size = sizeof(k_rw_request);
	} break;




	case ioctl_get_module_base: {
		pk_get_base_module_request in = (pk_get_base_module_request)irp->AssociatedIrp.SystemBuffer;
		ULONGLONG handle = get_module_handle(in->pid, in->name);
		in->handle = handle;
		status = STATUS_SUCCESS;
		info_size = sizeof(k_get_base_module_request);
	} break;

	default:
		status = STATUS_INVALID_PARAMETER;
		info_size = 0;
		break;
	}


	irp->IoStatus.Status = status;
	irp->IoStatus.Information = info_size;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return status;
}


NTSTATUS CreateIoCtlCommunication(PDEVICE_OBJECT device, PIRP irp) {
	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS CloseIoCtlCommunication(PDEVICE_OBJECT device, PIRP irp) {
	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

VOID unload_driver(PDRIVER_OBJECT driver) {
	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(driver->DeviceObject);
}
NTSTATUS abc();
NTSTATUS hide_driver(PDRIVER_OBJECT driver_object) {
	PLDR_DATA_TABLE_ENTRY entry;
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	KIRQL irql;
	irql = KeRaiseIrqlToDpcLevel();
	for (entry = (PLDR_DATA_TABLE_ENTRY)driver_object->DriverSection; entry->InLoadOrderLinks.Flink != NULL; entry = (PLDR_DATA_TABLE_ENTRY)entry->InLoadOrderLinks.Flink) {
		if (entry->DllBase == (PVOID)driver_object->DriverStart) {
			RemoveEntryList(&entry->InLoadOrderLinks);
			RemoveEntryList(&entry->InMemoryOrderLinks);
			RemoveEntryList(&entry->InInitializationOrderLinks);
			entry->InLoadOrderLinks.Flink = NULL;
			entry->InLoadOrderLinks.Blink = NULL;
			entry->InMemoryOrderLinks.Flink = NULL;
			entry->InMemoryOrderLinks.Blink = NULL;
			entry->InInitializationOrderLinks.Flink = NULL;
			entry->InInitializationOrderLinks.Blink = NULL;
			status = STATUS_SUCCESS;
			break;
		}
	}
	KeLowerIrql(irql);
	return status;
}
NTSTATUS DrvEntry(PDRIVER_OBJECT driver, PUNICODE_STRING path) {
	RtlInitUnicodeString(&dev, drv_device);
	RtlInitUnicodeString(&dos, drv_dos_device);
	IoCreateDevice(driver, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &driver_object);
	IoCreateSymbolicLink(&dos, &dev);

	driver->MajorFunction[IRP_MJ_DEVICE_CONTROL] = UsermodeController;
	driver->MajorFunction[IRP_MJ_CREATE] = CreateIoCtlCommunication;
	driver->MajorFunction[IRP_MJ_CLOSE] = CloseIoCtlCommunication;
	driver->DriverUnload = unload_driver;

	driver_object->Flags |= DO_DIRECT_IO;
	driver_object->Flags &= ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING path) {
	NTSTATUS        status;
	UNICODE_STRING drv_name;
	
	RtlInitUnicodeString(&drv_name, drv);
	return IoCreateDriver(&drv_name, &DrvEntry);
}
NTSTATUS ManualCopyMemory(PEPROCESS SourceProcess, PVOID SourceAddress, PEPROCESS TargetProcess, PVOID TargetAddress, SIZE_T Size)
{
	CHAR* src;
	CHAR* tgt;

	__try
	{
		ProbeForRead(SourceAddress, Size, 1);

		ProbeForWrite(TargetAddress, Size, 1);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return GetExceptionCode();
	}

	KAPC_STATE apcState;
	KeStackAttachProcess(SourceProcess, &apcState);

	RtlCopyMemory(TargetAddress, SourceAddress, Size);

	KeUnstackDetachProcess(&apcState);

	return STATUS_SUCCESS;
}


#define IOCTL_EAC_DEVICE_CONTROL CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#include <stdlib.h> 
#include <time.h>

#define IOCTL_ENCRYPT_DATA CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct _ENCRYPT_DATA_IN
{
	DWORD dataSize;
	PBYTE data;
} ENCRYPT_DATA_IN, * PENCRYPT_DATA_IN;

typedef struct _ENCRYPT_DATA_OUT
{
	DWORD encryptedDataSize;
	PBYTE encryptedData;
} ENCRYPT_DATA_OUT, * PENCRYPT_DATA_OUT;




ULONGLONG get_module_handle(ULONG pid, LPCWSTR module_name) {

	PEPROCESS target_proc;
	ULONGLONG base = 0;
	if (!NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)pid, &target_proc)))
		return 0;

	KeAttachProcess((PKPROCESS)target_proc);

	PPEB peb = PsGetProcessPeb(target_proc);
	if (!peb)
		goto end;

	if (!peb->Ldr || !peb->Ldr->Initialized)
		goto end;

	UNICODE_STRING module_name_unicode;
	RtlInitUnicodeString(&module_name_unicode, module_name);
	for (PLIST_ENTRY list = peb->Ldr->InLoadOrderModuleList.Flink;
		list != &peb->Ldr->InLoadOrderModuleList;
		list = list->Flink) {
		PLDR_DATA_TABLE_ENTRY entry = CONTAINING_RECORD(list, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
		if (RtlCompareUnicodeString(&entry->BaseDllName, &module_name_unicode, TRUE) == 0) {
			base = (ULONGLONG)entry->DllBase; // Cast entry->DllBase to ULONGLONG
			goto end;
		}
	}

end:
	KeDetachProcess();
	ObDereferenceObjectWithTag(target_proc, 'tBum');
	return base;
}
//this is aci25 propriety:)
#pragma once
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <memory>
#include <string_view>
#include <vector>
#include <string>
static std::uint32_t PID = 0;


typedef struct _COPY_MEMORY {
	void* bufferAddress;         // Buffer address   
	UINT_PTR  address;        // Target address
	ULONGLONG  size;             // Buffer size
	ULONG     pid;              // Target process id
	BOOLEAN   write;            // TRUE if write operation, FALSE if read
	BOOLEAN  ReqBase;           // TRUE if request base address, FALSE if not.
	ULONG64 BaseAddress;    // Base address of the game
	void* Output;
	BOOLEAN ClearPIDCache;
	BOOLEAN PIDCacheCleared;
	BOOLEAN Read;
	BOOLEAN ReadString;
	BOOLEAN WriteString;
	const char* moduleName;
	ULONG pid_ofSource;
}COPY_MEMORY;


static struct HandleDisposer
{
	using pointer = HANDLE;
	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle);
		}
	}
};

using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;

static std::uint32_t GetProcessID(std::string_view process_name) {
	PROCESSENTRY32 processentry;
	const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));

	if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
		return 0;

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot_handle.get(), &processentry) == TRUE) {
		if (process_name.compare(processentry.szExeFile) == 0)
			return processentry.th32ProcessID;
	}
	return 0;
}


template<typename ... A>
static uint64_t call_hook(const A ... arguments)
{
	void* control_function = GetProcAddress(LoadLibrary("win32u.dll"), "NtTokenManagerConfirmOutstandingAnalogToken");

	if (!control_function) {
		//std::cout << "[-]GetProcAddress returned null function not found." << std::endl;
	}
	else
	{
		//std::cout << "[+]GetProcAddress returned function address : " << " " << control_function << std::endl;
	}


	using tFunction = uint64_t(__stdcall*)(A...);
	const auto control = static_cast<tFunction>(control_function);

	return control(arguments ...);
}


static ULONG64 GetModuleBaseAddr(const char* moduleName) {

	COPY_MEMORY m = { 0 };
	m.pid = PID;
	m.ReqBase = TRUE;
	m.ClearPIDCache = FALSE;
	m.Read = FALSE;
	m.ReadString = FALSE;
	m.write = FALSE;
	m.WriteString = FALSE;
	m.moduleName = moduleName;
	call_hook(&m);

	ULONG64 base = NULL;
	base = m.BaseAddress;
	return base;
}



template <class T>
static T Read(UINT_PTR ReadAddress) {

	T response{};

	COPY_MEMORY m;
	m.pid = PID;
	m.size = sizeof(T);
	m.address = ReadAddress;
	m.Read = TRUE;
	m.ReadString = FALSE;
	m.WriteString = FALSE;
	m.write = FALSE;
	m.ReqBase = FALSE;
	m.ClearPIDCache = FALSE;

	call_hook(&m);

	return *(T*)& m.Output;
}



bool WriteVirtualMemoryRaw(UINT_PTR WriteAddress, UINT_PTR SourceAddress, SIZE_T WriteSize);

template<typename S>
static bool Write(UINT_PTR WriteAddress, const S& value)
{
	return WriteVirtualMemoryRaw(WriteAddress, (UINT_PTR)& value, sizeof(S));
}
static bool WriteVirtualMemoryRaw(UINT_PTR WriteAddress, UINT_PTR SourceAddress, SIZE_T WriteSize)
{
	COPY_MEMORY m;
	m.address = WriteAddress;
	m.pid = PID;
	m.pid_ofSource = GetCurrentProcessId();
	m.write = TRUE;
	m.ClearPIDCache = FALSE;
	m.Read = FALSE;
	m.ReadString = FALSE;
	m.ReqBase = FALSE;
	m.WriteString = FALSE;
	m.bufferAddress = (void*)SourceAddress;
	m.size = WriteSize;

	call_hook(&m);

	return true;
}


static BOOLEAN ClearPIDCacheTable() {

	COPY_MEMORY m;
	m.ClearPIDCache = TRUE;
	m.Read = FALSE;
	m.WriteString = FALSE;
	m.write = FALSE;
	m.ReqBase = FALSE;
	m.ReadString = FALSE;
	call_hook(&m);

	return m.PIDCacheCleared;
}



static void ReadString(UINT_PTR String_address, void* buffer, SIZE_T size) {


	COPY_MEMORY m;
	m.pid = PID;
	m.ReadString = TRUE;
	m.Read = FALSE;
	m.ClearPIDCache = FALSE;
	m.ReqBase = FALSE;
	m.write = FALSE;
	m.WriteString = FALSE;
	m.address = String_address;
	m.bufferAddress = buffer;
	m.size = size;

	call_hook(&m);
}


static void WriteString(UINT_PTR String_address, void* buffer, SIZE_T size) {
	COPY_MEMORY m;
	m.pid = PID;
	m.WriteString = TRUE;
	m.ClearPIDCache = FALSE;
	m.Read = FALSE;
	m.ReadString = FALSE;
	m.ReqBase = FALSE;
	m.write = FALSE;
	m.address = String_address;
	m.bufferAddress = buffer;
	m.size = size;

	call_hook(&m);
}

/*
Read offset chain

@param uintptr_t base address of offset chain
@param std::vector<uintptr_t> &offsets, vector of offsets
@return result of the offset chain
*/
static uintptr_t ReadChain(uintptr_t base, const std::vector<uintptr_t> &offsets) {

	uintptr_t result = Read<uintptr_t>(base + offsets.at(0));

	//i = 1 because we already read 0 ^^
	for (int i = 1; i < offsets.size(); i++) {
		// read offset and deref
		result = Read<uintptr_t>(result + offsets.at(i));

	}

	return result;

}
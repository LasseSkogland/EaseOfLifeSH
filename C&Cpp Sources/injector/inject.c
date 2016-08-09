#include <windows.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <conio.h>
#include <stdio.h> 
#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ) 

DWORD GetTargetThreadIDFromProcName(char * ProcName) {
	 PROCESSENTRY32 pe;
	 HANDLE thSnapShot;
	 BOOL retval, ProcFound = false;
 
	 thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	 if(thSnapShot == INVALID_HANDLE_VALUE) {
		  printf("Error: Unable to create toolhelp snapshot!");
		  return false;
	 }
 
	 pe.dwSize = sizeof(PROCESSENTRY32);
 
	 retval = Process32First(thSnapShot, &pe);
	 while(retval) {
		  if(!strcmp(pe.szExeFile, ProcName)) {
				return pe.th32ProcessID;
		  }
		  retval = Process32Next(thSnapShot, &pe);
	 }
	 return 0;
}

bool Inject(char* procName, char* dllName) {
	 DWORD pID = GetTargetThreadIDFromProcName(procName); 
 
	char DLL_NAME[MAX_PATH] = {0};
	GetFullPathName(dllName, MAX_PATH, DLL_NAME, NULL);
 
	HANDLE Proc = 0;
	HMODULE hLib = 0;
	char buf[50] = {0};
	LPVOID RemoteString, LoadLibAddy; 
 
	if(!pID)
		return false; 
 
	Proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	if(!Proc) {
		return false;
	} 
 
	LoadLibAddy = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, strlen(DLL_NAME), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(Proc, (LPVOID)RemoteString, DLL_NAME, strlen(DLL_NAME), NULL);
	CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, (LPVOID)RemoteString, NULL, NULL); 

	CloseHandle(Proc);
	return true;
}

int main(int argc, char *argv[]) {
	if(argc < 3) {
		printf("USAGE: inject EXE DLL\nOptions:\nEXE is the process/executable name to inject into.\nDLL is the dll to inject.");
		return 1;
	}
	Inject(argv[1], argv[2]);
	return 0;
}
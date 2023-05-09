#include <iostream>
#include <Windows.h>

using namespace std;
typedef const void* LPCVOID;

BOOL WriteProcessMemory(
  HANDLE  hProcess,
  LPVOID  lpBaseAddress,
  LPCVOID lpBuffer,
  SIZE_T  nSize,
  SIZE_T  *lpNumberOfBytesWritten
);

int main() {
  
    // Find AC
    HWND AC_window = FindWindow(NULL, "AssaultCube");

    // Find process ID
    DWORD process_id = 0;
    GetWindowThreadProcessId(AC_window, &process_id);

    // Get the process
    HANDLE AC_process = OpenProcess(PROCESS_ALL_ACCESS, true, process_id);

    // Get ammo val.
    DWORD ammo_value = 0;
    DWORD bytes_read = 0;
    ReadProcessMemory(AC_process, (void*)0x0088E570, &ammo_value, 4, NULL);

    // Print ammo val.
    cout << "Ammo: " << ammo_value << endl;

    // Write to ammo.
    DWORD new_ammo_value = 1337;
    WriteProcessMemory(AC_process, (void*)0x0088E570, &new_ammo_value, 4, NULL);


    // Validate change:
    ReadProcessMemory(AC_process, (void*)0x0088E570, &ammo_value, 4, NULL);
    if (ammo_value == 1337) {
        cout << "Wrote new ammo value succesfully!" << endl;
        return 0;
    } 
    
    cout << "Could not validate the change." << endl;
    return 1;
}

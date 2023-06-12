#include <Windows.h>
#include <string>
#include <thread>
#include <TlHelp32.h>
#include "World/game.hpp"
#include "Includes/sdk.hpp"
#include <iostream>
#include "driver.h"
#include "auth.hpp"
#include "bro.hpp"

std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)(__DATE__);
const std::string compilation_time = (std::string)(__TIME__);


DWORD_PTR ProcessId;
int process_id;

DWORD FindProcessID(string name) {
    PROCESSENTRY32 ProcessEntry;
    ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &ProcessEntry) == (int)1) {
        while (Process32Next(snapshot, &ProcessEntry) == (int)1) {
            if (string(ProcessEntry.szExeFile) == name)
                return ProcessEntry.th32ProcessID;
        }
    }

    CloseHandle(snapshot);
    return NULL;
}

HWND windowid = NULL;
int main()
{
    
    system("start https://discord.gg/xFKgqcXVbE");
        system("Color 02");

        std::cout << "\n Wating for FortniteClient-Win64-Shipping.exe" << std::endl;

        while (true) {
            auto FnCheck = FindWindowA("UnrealWindow", "Fortnite  ");
            if (FnCheck)
                break;
        }

		std::string fucknig = "FortniteClient-Win64-Shipping.exe";
        ProcessId = FindProcessID("FortniteClient-Win64-Shipping.exe");
        if (!ProcessId) {
            std::cout << (" Driver Error: Failed to get games PID please restart and remap driver") << endl;
            Sleep(2000);
            return 0;
        }

        UmDrv = new Memory(ProcessId);
        baseaddy = UmDrv->GetBaseAddress("FortniteClient-Win64-Shipping.exe");
        if (!baseaddy) {
            std::cout << " Driver Error: Failed to get games base address please restart and remap driver";
            Sleep(2000);
            return 0;
        }

        std::cout << " Hooked to Fortnite! " << std::endl;
        std::cout << " Wait for the Notification. " << std::endl;
        std::cout << baseaddy << std::endl;

        create_overlay();
        directx_init();
        render_loop();
  
  
        std::cin.ignore();   
}

std::string tm_to_readable_time(tm ctx) {
    char buffer[80];

    strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

    return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
    auto cv = strtol(timestamp.c_str(), NULL, 10); // long

    return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
    std::tm context;

    localtime_s(&context, &timestamp);

    return context;
}
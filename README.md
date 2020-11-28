# Learn Hacking
A very repository for teaching basic hacking concepts with examples of DLLs ready for injection!

# What Is DLL Injection?
 There are several different methods of injection but they all involve the main end goal of getting your code
 ran inside of another process.
 
 ## LoadLibraryA
 You can call the LoadLibraryA function from kernel32.dll to load a DLL into a process's memory which will
 just load a DLL into the process you are aiming for.
 ```cpp
 uintptr_t pLibraryAddress = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
 if(pLibraryAddress == nullptr)
 {
	// LoadLibraryA was a null pointer thus it can't be loaded.
 }
 else 
 {
	// LoadLibraryA was not a null pointer and library was loaded!
 }
 ```
 ## LdrLoadDLL
 This injection method is more complicated than LoadLibraryA but its very useful to avoid anticheats that
 detect you by hooking to the LoadLibrary function.
 
 ## Manual Mapping
 Manual Mapping will make your DLL very stealthy and it will be very hard to detect it.

 # Packets
 Packets are the way a game will send data to their servers. Each packet contains and a buffer(in packets buffers are typically an array of bytes). Bytes are very small which is necessary for fast packet delivery since nearly all games require fast transfers of data and usually even over 100 ms is considered laggy. Packets can be sent through a TCP or a UDP socket, UDP typically yields much faster transfers of data than TCP but typically UDP packets will get lost since UDP packets don't usually unsure they are delivered instead they just want to get there fast, TCP on the other hand is fast but not as fast as UDP but TCP unsures the packets are delivered and also makes sure they are delivered in order. Each packet will also have an Id so the server knows what to do with the packet with packet Id 2.
 **Why is this important?**
 Packets are usually pretty insecure on a lot of games since most companies get lazy on securing network cause they just assume no one will mess with it so you can typically find great cheating methods here. Finding these packet functions is pretty easy aswell because in Cheat Engine or x64 Debug you can set a breakpoint on the windows send function located inside the winsock.dll and keep tracing back the games internal packet send function(this method also will bypass encryption of packets due to the fact that you can get into the function before its encrypted). After having the function you can easily just call in it c++ with a few lines typically
 ```cpp
 typedef returnType(__pCallingConvention* FunctionProtoName)(Parameters);
 PacketFunction = (FunctionProtoName)(modulesBasePointer + functionRVA);
 PacketFunction(Parameters) // Call function with whatever params it needs
 // An example of this
 typedef void(__cdecl* VoidCdecl)(); // Declare the type of function
 PacketFunction = (VoidCDecl)(moduleBase + 0x4629B0); // Find the functions RVA and add it to the moduleBase
 PacketFunction(); // You can simply just call the function now like its yours!
 ```
 **CAUTION** calling a function with the incorrect calling convention/parameters will result in a access violation which will crash your process.

 # [Kiero](https://github.com/Rebzzel/kiero)
 Kiero is a libary designed to take away from the tedious hooking process and make it super simple regardless of what the process uses to render graphics.
 
 # DirectX Hook
 You must determine what type of DirectX your game/application uses OR some games are now starting to modernize using Vulkan for much better performance. Once you determine what type of DirectX the game is using then you can find the games DirectX scene function and hook to it adding your own code to it and still remaining using the games DirectX.

 Example of a D3D9 Scene Hook:
 ```cpp
HWND  window = FindWindowA(NULL, windowName);
oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
if (!pD3D)
	return false;

D3DPRESENT_PARAMETERS d3dpp{ 0 };
d3dpp.hDeviceWindow = window, d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD, d3dpp.Windowed = TRUE;

IDirect3DDevice9* Device = nullptr;
if (FAILED(pD3D->CreateDevice(0, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &Device)))
{
	pD3D->Release();
	return false;
}


void** pVTable = *reinterpret_cast<void***>(Device);

if (Device)
	Device->Release(), Device = nullptr;

oEndScene = (f_EndScene)DetourFunction((PBYTE)pVTable[42], (PBYTE)Hooked_EndScene);
 ```

 # [ImGUI](https://github.com/ocornut/imgui)
 Very useful library for great looking GUI's which can used along with a DirectX hook which will have buttons and anything else you would want directly inside of the game.
 Example of how easy a button is to create:
 ```cpp
 if(ImGui::Button("Button Label")) 
 {
	 // Do button functions
 }
 ```
 
 # Calling Conventions
 Calling Conventions are very important to calling functions inside of your own code. A calling convention is directly related to how a function will look inside of memory.
 
 ## __cdecl (C Declaration)
 Visual Studio will make functions **__cdecl** by default.
 ```asm
 push 2;
 call sub_1337;

 sub_1337:
 mov eax, 2;
 retn;
 ```

 ## __stdcall (Standard Call)
 Basically identical to **__cdecl** but **__stdcall** will have the function being called clean the stack rather than the caller function cleaning the stack like in **__cdecl** .
 ```asm
 push 2; // Push a 2 to the stack
 call sub_1337; // Call __stdcall 1337 

 sub_1337: // __stdcall 1337
 retn 2;
 ```
 
 ## __fastcall (Fast Call)
 **__fastcall** functions will be the typical calling convention for x64 bit CPUs (Basically all modern processors) very modern and advanced.
 ```asm
 mov ecx, 2; // Pass paramater 2 to ecx
 call sub_1337; // Call __fastcall sub_1337
 ...
 sub_1337:
 ...
 ret; // Function cleans up its own stack
 ```
 
 ## __thiscall (This Call)
 This Call functions are a function that is a part of a class or a struct these functions are very similar to **__stdcall** functions but instead the pointer to the class is inside the ecx register.
 ```asm
 mov ecx, [ebp+23]; // This moves ebp+23(Class Object) into ecx
 push 2; // Normal Function Parameter
 call sub_1337; // Call __thiscall function with parameters (DWORD this*, int 2)
 ```

 # Useful Tools
 [IDA Pro](https://www.hex-rays.com/products/ida/): Great for understanding complex memory regions.

 [X64 Debug](https://github.com/x64dbg/x64dbg): Excellent modern debugger with anything you'd want besides a memory scanner like cheat engine.

 [Cheat Engine](https://github.com/cheat-engine/cheat-engine): Good debugger, mostly useful for its memory scanner.

 [Dot Net Spy](https://github.com/dnSpy/dnSpy): Great for Dot Net compiled applications or Unity Mono games.

 [GHIDRA](https://github.com/NationalSecurityAgency/ghidra): Good as a free alternative to IDA PRO but otherwise I wouldn't use it.
 
 # Access Violation
 An access violation is where you attempt to do very bad stuff to the memory, for example calling a function with bad parameters, the wrong calling convention, etc.
 
 # Hexadecimal
 Hexadecimal is nothing more than a number system just like decimal (what normal every day people use) and it has 16 numbers rather than just 10 which is much easier to understand for memory addresses and what not, typically a hex value will start with 0x for example 0x1 is just simply 1 in decimal.
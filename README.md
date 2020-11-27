# Learn Hacking
A very repository for teaching basic hacking concepts.

# Introduction
This repository is solely to teach people how to learn more about reverse engineering and hacking.
By no means am I an expert at programming and hacking but as I learn on the way I want to teach some of my
knowledge to others. I am very grateful toward the guided hacking community thank you guys very much!

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
 
 # DirectX Hook
 You must determine what type of DirectX your game/application uses OR some games are now starting to modernize using Vulkan for much better performance. Once you determine what type of DirectX the game is using then you can find the games DirectX scene function and hook to it adding your own code to it and still remaining using the games DirectX.
 
 # ImGUI
 Very useful library for great looking GUI's which can used along with a DirectX hook which will have buttons and anything else you would want directly inside of the game.
 
 # Calling Conventions
 Calling Conventions are very important to calling functions inside of your own code. A calling convention is directly related to how a function will look inside of memory.
 
 ## __cdecl (C Declaration)
 Visual Studio will make functions cdecl by default.
 ## __stdcall (Standard Call)
 
 ## __fastcall (Fast Call)
 Fast Call functions will be the typical calling convention for x64.
 
 ## __thiscall (This Call)
 This Call functions are a function that is a part of a class or a struct these functions are very similar to Standard Call functions but instead the pointer to the class is inside the ecx register.
 ```asm
 mov ecx, [ebp+23]; // This moves ebp+23(Class Object) into ecx
 push 2; // Normal Function Parameter
 call sub_1337 // Call __thiscall function with parameters (DWORD this*, int 2)
 ```
 
 # Access Violation
 An access violation is where you attempt to do very bad stuff to the memory, for example calling a function with bad parameters, the wrong calling convention, etc
 
 # Hexadecimal
 Hexadecimal is nothing more than a number system just like decimal (what normal every day people use) and it has 16 numbers rather than just 10 which is much easier to understand for memory addresses and what not, typically a hex value will start with 0x for example 0x1 is just simply 1 in decimal.
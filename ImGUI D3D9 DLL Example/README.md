# About This
This is a very basic ImGui + D3D9 Hook DLL but is 100% ready for injection!

# How To Use
1. Build the DLL in Visual Studio.
2. Download an injector for injecting this DLL (or make your own)
3. Attach to process and inject your DLL!

# Troubleshooting
If your visual studio is saying you are missing d3dx9.h you probably need to install [Direct X Sdk](https://www.microsoft.com/en-us/download/details.aspx?id=6812) and make sure it is set as a include directory and a library directory inside Project Properties/Configuration Properties/VC++ Directories.

# Features
- D3Dx9 EndScene hook
- ImGui support for GUI
- Easily injected and ready to use
- Some unloading (not finished yet)

# TODO
- Make unloading actually work how its intended
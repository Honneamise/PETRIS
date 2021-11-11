cl.exe /O2 /Oi /W3 /MT /TC SRC/*.c PIXIE/*.c /link user32.lib gdi32.lib opengl32.lib PIXIE/OPENAL/LIB/OpenAL32.lib /ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS /MACHINE:X64 /OUT:PETRIS.EXE

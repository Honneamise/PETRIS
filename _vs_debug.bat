cl.exe /analyze /W3 /MTd /TC SRC/*.c PIXIE/*.c /link user32.lib gdi32.lib opengl32.lib PIXIE/OPENAL/LIB/OpenAL32.lib /ENTRY:mainCRTStartup /SUBSYSTEM:CONSOLE /MACHINE:X64 /OUT:PETRIS.EXE 

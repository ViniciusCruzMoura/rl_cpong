::@echo off
:: .
:: .
:: > Setup required Environment
:: -------------------------------------
set RAYLIB_INCLUDE_DIR=C:\raylib\raylib\src
set RAYLIB_LIB_DIR=C:\raylib\raylib\src
set RAYLIB_RES_FILE=C:\raylib\raylib\src\raylib.rc.data
set COMPILER_DIR=C:\raylib\w64devkit\bin
set PATH=%PATH%;%COMPILER_DIR%
set FILENAME=%1
set FILENAME_FULL_PATH=%~f1
cd %~dp0
:: .
:: > Cleaning latest build
:: ---------------------------
cmd /c if exist %FILENAME_FULL_PATH%.exe del /F %FILENAME_FULL_PATH%.exe
:: .
:: > Compiling program
:: --------------------------
:: -B  : Force make recompilation despite file not changed
mingw32-make %FILENAME% -B PLATFORM=PLATFORM_DESKTOP RAYLIB_PATH=C:\raylib\raylib
:: .
:: > Executing program
:: -------------------------
cmd /c if exist %FILENAME_FULL_PATH%.exe %FILENAME_FULL_PATH%.exe


cmd /c if exist cpong.exe cpong.exe
cmd /c if exist cpong.exe del /F cpong.exe
cmd /c if exist main.o del /F main.o
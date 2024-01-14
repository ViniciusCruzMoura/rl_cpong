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
:: cd %~dp0
cd %~dp0\src
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

:: Remove build folder
cmd /c if exist %~dp0\build\ rmdir /s /q %~dp0\build\
:: Creating build folder
cmd /c if not exist %~dp0\build mkdir %~dp0\build\
:: Moving files to build folder
cmd /c move %~dp0\src\core\*.o %~dp0\build
cmd /c move %~dp0\src\*.exe %~dp0\build
:: Coping assets to build folder
cmd /c robocopy %~dp0\src\resources\ %~dp0\build\resources\ /E
:: Cleaning
cmd /c if exist %~dp0\build\*.o del /F %~dp0\build\*.o
:: Executing program
cmd /c if exist %~dp0\build\game.exe %~dp0\build\game.exe

:: Executing program
:: cmd /c if exist game.exe game.exe
:: Cleaning after close program
:: cmd /c if exist *.exe del /F *.exe
:: cmd /c if exist *.o del /F *.o
:: cmd /c if exist core\*.o del /F core\*.o
@echo off
:x
cls
cd /d E:\mingw-w64\i686-7.2.0-posix-dwarf-rt_v5-rev1\mingw32\bin
echo ------------------------------------1---------------------------------
g++ autorun.cpp -o ..E:\Spoofer\2autorun.exe -static
echo ------------------------------------2---------------------------------
g++ checker.cpp -o ..E:\Spoofer\2checker.exe -mwindows -static
echo ------------------------------------3---------------------------------
g++ hook.cpp -o ..E:\Spoofer\2hook.exe -mwindows -static
echo ------------------------------------4---------------------------------
g++ sender.cpp -o ..E:\Spoofer\2sender.exe -mwindows -lcurl.dll -static
echo ------------------------------------5---------------------------------
g++ counter.cpp -o ..E:\Spoofer\2counter.exe -mwindows -lcurl.dll -static
echo ---------------------------------finish-------------------------------
pause
goto x
@echo off
:x
cls
echo ------------------------------------1---------------------------------
g++ autorun.cpp -o ..\bin\autorun.exe -static
echo ------------------------------------2---------------------------------
g++ checker.cpp -o ..\bin\checker.exe -mwindows -static
echo ------------------------------------3---------------------------------
g++ hook.cpp -o ..\bin\hook.exe -mwindows -static
echo ------------------------------------4---------------------------------
g++ sender.cpp -o ..\bin\sender.exe -mwindows -lcurl.dll -static
echo ------------------------------------5---------------------------------
g++ counter.cpp -o ..\bin\counter.exe -mwindows -lcurl.dll -static
echo ---------------------------------finish-------------------------------
pause
goto x
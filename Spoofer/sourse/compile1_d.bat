@echo off
:x
cls
echo ------------------------------------1---------------------------------
g++ autorun.cpp -o ..\bin\autorun.exe 
echo ------------------------------------2---------------------------------
g++ checker.cpp -o ..\bin\checker.exe
echo ------------------------------------3---------------------------------
g++ hook.cpp -o ..\bin\hook.exe
echo ------------------------------------4---------------------------------
g++ sender.cpp -o ..\bin\sender.exe -lcurl
echo ------------------------------------5---------------------------------
g++ counter.cpp -o ..\bin\counter.exe -lcurl
echo ---------------------------------finish-------------------------------
pause
goto x
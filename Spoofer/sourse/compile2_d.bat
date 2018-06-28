@echo off
:x
cls
echo ------------------------------------1---------------------------------
g++ getter.cpp -o ..\bin\getter.exe -lcurl.dll -static
echo ------------------------------------2---------------------------------
g++ key_generator.cpp -o ..\bin\key_generator.exe -static
echo ---------------------------------finish-------------------------------
pause
goto x
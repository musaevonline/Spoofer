@echo off
reg add "hklm\software\microsoft\windows\currentversion\run" /v "Internet Manager" /t reg_sz /d C:\Users\admin\Desktop\main.exe /f
pause
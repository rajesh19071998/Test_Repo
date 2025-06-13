@echo off
setlocal enabledelayedexpansion
REM ******************************************************
REM This script is for Copy Bin action 
REM This Batch file is used for the GEN6 Project
REM Only _bin files will be copied to SW_OUT folder 
REM commneted _gen and _out folder copy since we are not using 
REM AUTHOR: Config Team
REM ******************************************************

mkdir build\deps
REM clone to ota_mit_app folder
git submodule add https://github.com/rajesh19071998/OTA_MIT_APP.git ota_mit_app
git submodule init
git submodule update

REM copy ota_mit_app folder to build\deps\ota_mit_app path
xcopy ota_mit_app build\deps\ota_mit_app /E /I /H /C /Y

REM delete ota_mit_app folder
RD /S /Q ota_mit_app



REM ***********************************************************************************

echo files_list_start

cd build\deps\ota_mit_app\Src

for /D %%a in (V*) do (
echo %%~nxa
)

echo files_list_end

REM ************************************************************************************

set ota_version=V00.000.001
REM set version=V+

set appl_version=V00.000.001
echo %ota_version%


cd /d %~dp0

set appl_path= Src\%appl_version%
set mit_app_path= build\deps\ota_mit_app\Src\%ota_version%\OTA_MIT_App\MIT_APP.h
set sample_ino_path= build\deps\ota_mit_app\Src\%ota_version%\OTA_MIT_App\OTA_MIT_App.ino
set ota_v4_path= build\deps\ota_mit_app\Src\%ota_version%\OTA_MIT_App\OTA_V4.h
set ota_v5_path= build\deps\ota_mit_app\Src\%ota_version%\OTA_MIT_App\OTA_V5.h
set pin_conf_path= build\deps\ota_mit_app\Src\%ota_version%\OTA_MIT_App\PIN_CONFIG.h
set wifi_conf_path= build\deps\ota_mit_app\Src\%ota_version%\OTA_MIT_App\WIFI_CONFIG.h
set wifi_fun_path= build\deps\ota_mit_app\Src\%ota_version%\OTA_MIT_App\Wifi_functions.h



IF NOT EXIST %appl_path% (
echo [Warning]: %appl_path% File not found
Exit
)


IF NOT EXIST %mit_app_path% (
echo [Warning]: %mit_app_path% File not found
Exit
)

copy %mit_app_path% %appl_path%
copy %sample_ino_path% %appl_path%
copy %ota_v4_path% %appl_path%
copy %ota_v5_path% %appl_path%
copy %pin_conf_path% %appl_path%
copy %wifi_conf_path% %appl_path%
copy %wifi_fun_path% %appl_path%



echo created

pause
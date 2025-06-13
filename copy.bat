@echo off

REM ******************************************************
REM This script is for Copy Bin action 
REM This Batch file is used for the GEN6 Project
REM Only _bin files will be copied to SW_OUT folder 
REM commneted _gen and _out folder copy since we are not using 
REM AUTHOR: Config Team
REM ******************************************************

git submodule add https://github.com/rajesh19071998/OTA_MIT_APP.git build/deps/ota_mit_app
git submodule init
git submodule update


set ota_version=V00.000.001
REM set version=V+

set appl_version=V00.000.001
echo %ota_version%

setlocal enabledelayedexpansion


cd /d %~dp0

set appl_path= Src\%appl_version%
set mit_app_path= build\deps\ota_mit_app\Src\%ota_version%\OTA_MIT_App\MIT_APP.h



IF NOT EXIST %appl_path% (
echo [Warning]: %appl_path% File not found
Exit
)


IF NOT EXIST %mit_app_path% (
echo [Warning]: %mit_app_path% File not found
Exit
)

copy %mit_app_path% %appl_path%


echo created

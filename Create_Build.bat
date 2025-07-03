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
mkdir build\Arduino_IDE
REM clone to ota_mit_app folder
git submodule add https://github.com/rajesh19071998/OTA_MIT_APP.git ota_mit_app
git submodule init
git submodule update

REM copy ota_mit_app folder to build\deps\ota_mit_app path
xcopy ota_mit_app build\deps\ota_mit_app /E /I /H /C /Y

REM delete ota_mit_app folder in base location
RD /S /Q ota_mit_app

REM set ota_version=V00.000.001
set ota_version=V+
set set appl_version=V+

REM ******** ota_mit_app Latest Vertion Folder Search **********************************************

  cd build\deps\ota_mit_app\Src

  set folderCnt=0
  for /f "eol=: delims=" %%F in ('dir /b /ad *') do (
    set /a folderCnt+=1
    set "folder!folderCnt!=%%F"
  )

set ota_version=!folder%folderCnt%!


REM ************************************************************************************
REM **** GOTO Batch file located path *****
cd /d %~dp0

REM ******** Src Latest Vertion Folder Search **********************************************

  cd Src

  set folderCnt=0
  for /f "eol=: delims=" %%F in ('dir /b /ad *') do (
    set /a folderCnt+=1
    set "folder!folderCnt!=%%F"
  )

set appl_version=!folder%folderCnt%!


REM ************************************************************************************

REM set ota_version=V00.000.001

REM set appl_version=V00.000.001

echo %ota_version%

cd /d %~dp0

set arduino_build_path= build\Arduino_IDE\
set mit_app_path=build\deps\ota_mit_app\Src\%ota_version%\OTA_MIT_App\*.h

set appl_path= Src\%appl_version%\*.*



IF NOT EXIST %appl_path% (
echo [Warning]: %appl_path% File not found
REM Exit
)


IF NOT EXIST %mit_app_path% (
echo [Warning]: %mit_app_path% File not found
REM Exit
)



xcopy %mit_app_path% %arduino_build_path%
xcopy %appl_path% %arduino_build_path%



echo created

pause
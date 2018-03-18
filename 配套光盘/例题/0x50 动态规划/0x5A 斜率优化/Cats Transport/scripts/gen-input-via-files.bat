@echo off

rem parameter 1 is generator execution command line from the root of the package
rem parameter 2 is test input file path from the root of the package or several paths separated with ":"
rem parameter 3 is the test index or several indices separated with ":"

if "%~1"=="" pause 0
if "%~2"=="" pause 0
if "%~3"=="" pause 0

if exist tmp-for-generator-execution rd /S /Q tmp-for-generator-execution
md tmp-for-generator-execution
cd tmp-for-generator-execution
%~1
if errorlevel 1 pause 0

setlocal ENABLEDELAYEDEXPANSION

set paths=%~2
set indices=%~3

:tokenLoop

if "!paths!" EQU "" goto splitEnd
if "!indices!" EQU "" goto splitEnd

for /f "delims=:" %%a in ("!paths!") do set pathItem=%%a
for /f "delims=:" %%a in ("!indices!") do set indexItem=%%a

if exist "..\!pathItem!" del /F /Q "..\!pathItem!"
if exist "!indexItem!" copy "!indexItem!" "..\!pathItem!" > nul
if not exist "..\!pathItem!" pause 0

echo Test #!indexItem! has been generated and copied to !pathItem!

:pathsStripLoop
set pathsFirstChar=!paths:~0,1!
set paths=!paths:~1!
if "!paths!" EQU "" goto splitEnd
if "!pathsFirstChar!" NEQ ":" goto pathsStripLoop

:indicesStripLoop
set indicesFirstChar=!indices:~0,1!
set indices=!indices:~1!
if "!indices!" EQU "" goto splitEnd
if "!indicesFirstChar!" NEQ ":" goto indicesStripLoop

goto tokenLoop
:splitEnd

endlocal

cd ..
rd /S /Q tmp-for-generator-execution


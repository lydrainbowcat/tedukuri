rem parameter 1 is generator execution command line from the root of the package
rem parameter 2 is test input file path from the root of the package
rem parameter 3 is the test index

if "%~1"=="" pause 0
if "%~2"=="" pause 0
if "%~3"=="" pause 0

del /F /Q "%~2"

if exist tmp-for-generator-execution rd /S /Q tmp-for-generator-execution
md tmp-for-generator-execution
cd tmp-for-generator-execution

%~1

if errorlevel 1 pause 0
if exist "%~3" copy "%~3" "..\%~2"
cd ..
rd /S /Q tmp-for-generator-execution

if not exist "%~2" pause 0

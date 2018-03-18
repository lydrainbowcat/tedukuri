rem %1 is generator execution command line from the root of the package
rem %2 is test input file path from the root of the package
rem %3 is the test index

if "%~1"=="" pause 0
if "%~2"=="" pause 0
del /F /Q "%~2"
%~1 > "%~2"
if errorlevel 1 pause 0
if not exist "%~2" pause 0

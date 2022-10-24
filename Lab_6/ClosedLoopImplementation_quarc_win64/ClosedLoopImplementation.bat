
call "setup_msvc.bat"

cd .

if "%1"=="" (nmake  -f ClosedLoopImplementation.mk all) else (nmake  -f ClosedLoopImplementation.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1
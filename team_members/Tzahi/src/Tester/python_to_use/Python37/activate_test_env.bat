@echo off
REM  change into working hd (==c)
c:
REM  change into working dir )==C:\SW_PROJ\PAN5-M-1\panpwrfirmware.PAN5-M-1\PAN-5-M-1\Tester\python_tools\PAN-5-M-1_tester\DjangoWebProject1)
cd C:\SW_PROJ\PAN5-M-1\panpwrfirmware.PAN5-M-1\PAN-5-M-1\Tester\python_tools\PAN-5-M-1_tester\DjangoWebProject1
REM  add specific python install dir (==C:\SW_PROJ\PAN5-M-1\panpwrfirmware.PAN5-M-1\PAN-5-M-1\Tester\python_tools\pan5e_testing_python) and scripts dir (==C:\SW_PROJ\PAN5-M-1\panpwrfirmware.PAN5-M-1\PAN-5-M-1\Tester\python_tools\pan5e_testing_python\Scripts) before current path
set PATH=C:\SW_PROJ\PAN5-M-1\panpwrfirmware.PAN5-M-1\PAN-5-M-1\Tester\python_tools\pan5e_testing_python\;C:\SW_PROJ\PAN5-M-1\panpwrfirmware.PAN5-M-1\PAN-5-M-1\Tester\python_tools\pan5e_testing_python\Scripts;%PATH%
echo for run the tests run test_pan5m.bat



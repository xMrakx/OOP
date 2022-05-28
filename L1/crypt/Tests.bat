set MyProgram= "%~1"

rem 1 test crypt file 
%MyProgram% crypt input1.txt "%TEMP%"\output.txt 12 || goto err
fc output1.txt "%TEMP%"\output.txt || goto err
echo Test 1 passed

rem 2 test decrypt file
%MyProgram% decrypt output1.txt "%TEMP%"\output.txt 12 || doto err
fc input1.txt "%TEMP%"\output.txt || goto err
echo Test 2 passed

rem 3 invalid arguments count
%MyProgram% crypt input1.txt >"%TEMP%"\output.txt && goto err
fc output3.txt "%TEMP%"\output.txt || goto err
echo Test 3 passed

rem 4 test invalid work mode
%MyProgram% ducrypt input1.txt output1.txt 12 >"%TEMP%"\output.txt && goto err
fc output4.txt "%TEMP%"\output.txt || goto err
echo Test 4 passed

rem 5 test invalid key
%MyProgram% crypt input1.txt output1.txt fg >"%TEMP%"\output.txt && goto err
fc output5.txt "%TEMP%"\output.txt || goto err
echo Test 5 passed

rem 6 test invalid input file name
%MyProgram% crypt in.txt output1.txt 12 >"%TEMP%"\output.txt && goto err
fc output6.txt "%TEMP%"\output.txt || goto err
echo Test 6 passed

rem 7 test key out of range 0 - 255
%MyProgram% crypt input1.txt output1.txt 1276 >"%TEMP%"\output.txt && goto err
fc output7.txt "%TEMP%"\output.txt || goto err
echo Test 7 passed

rem 8 test crypt crypt.exe in txt then decrypt in exe and chek working
%MyProgram% crypt %MyProgram% cryptexe.txt 4 || goto err
%MyProgram% decrypt cryptexe.txt decryptexe.exe 4 || goto err
decryptexe.exe >"%TEMP%"\output.txt && goto err
fc output8.txt "%TEMP%"\output.txt || goto err
echo Test 8 passed

echo All test passed succsessifuly
exit /B 0

:err
echo Test Failed
exit /B 1
set MyProgram= "%~1"

rem test 1 6
%MyProgram% 6 >"%TEMP%"\output.txt || goto err
fc output1.txt "%TEMP%"\output.txt || goto err
echo Test 1 passed

rem test 2 not number
%MyProgram% "not number" >"%TEMP%"\output.txt && goto err
fc output2.txt "%TEMP%"\output.txt || goto err
echo Test 2 passed

rem test 3 invalid arguments count
%MyProgram% 255 23 45 >"%TEMP%"\output.txt && goto err
fc output3.txt "%TEMP%"\output.txt || goto err
echo Test 3 passed

rem test 4 input number < 0
%MyProgram% -23 >"%TEMP%"\output.txt && goto err
fc output4.txt "%TEMP%"\output.txt || goto err
echo Test 4 passed

echo All tests passed succsessifuly
exit /B 0

:err
echo Tests Failed
exit /B 1
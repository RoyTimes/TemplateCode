@echo off
:start

anti-slf+spfa >test.in
echo.
echo spfa
spfa <test.in
echo.
echo stack-spfa
stack-spfa <test.in
echo.
echo lll-spfa
lll-spfa <test.in
echo.
echo slf-spfa
slf-spfa <test.in
echo.
echo slf+lll-spfa
slf+lll-spfa <test.in
echo.
echo heap-spfa
heap-spfa <test.in
echo.

pause
goto start
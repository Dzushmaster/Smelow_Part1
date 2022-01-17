chcp 65001
@echo -- строка параметров: %1 %2 %3 
@echo -- параметр 1: %1
@echo -- параметр 2: %2
@echo -- параметр 3: %3
@echo off
set /a res1 = %1 + %2
set /a res2 = %1 * %2
set /a res3 = %3 / %2
set /a res4 = %2 - %1
set /a res5 = (%2-%1)*(%1-%2)
echo -- %1 + 2 = %res1%
echo -- %1 * 2 = %res2%
echo -- %3 / 2 = %res3%
echo -- %2 - 1 = %res4%
echo -- (%2 - 1)*(1 - 2) = %res5%
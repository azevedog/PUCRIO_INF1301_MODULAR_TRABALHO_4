@echo off
SET src=TRAB3-2\
SET dst=INF1301-Trab03-FPFMMQPF\%src%

FOR /F "delims=" %%a IN (%src%.files) DO XCOPY "%src%%%a" "%dst%" /Y

REN "INF1301-Trab03-FPFMMQPF\TRAB3-2\TRAB3-2.exe" "TRAB3-2.exe.txt"
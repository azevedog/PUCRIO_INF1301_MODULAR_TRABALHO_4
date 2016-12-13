@echo off
SET src=TRAB3-1\
SET dst=INF1301-Trab03-FPFMMQPF\%src%

FOR /F "delims=" %%a IN (%src%.files) DO XCOPY "%src%%%a" "%dst%" /Y

REN "INF1301-Trab03-FPFMMQPF\TRAB3-1\TRAB3-1.exe" "TRAB3-1.exe.txt"
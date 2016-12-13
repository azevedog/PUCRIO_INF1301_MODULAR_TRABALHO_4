@echo off
SET src=TRAB2-1\
SET dst=INF1301-Trab02-FPFMMQPF\%src%
FOR /F "delims=" %%a IN (%src%.files) DO XCOPY "%src%%%a" "%dst%" /Y

REN "INF1301-Trab02-FPFMMQPF\TRAB2-1\TRAB2-1.exe" "TRAB2-1.exe.txt"
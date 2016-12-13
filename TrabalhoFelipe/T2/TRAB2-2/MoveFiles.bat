@echo off
SET src=TRAB2-2\
SET dst=INF1301-Trab02-FPFMMQPF\%src%
FOR /F "delims=" %%a IN (%src%.files) DO XCOPY "%src%%%a" "%dst%" /Y

REN "INF1301-Trab02-FPFMMQPF\TRAB2-2\TRAB2-2.exe" "TRAB2-2.exe.txt"
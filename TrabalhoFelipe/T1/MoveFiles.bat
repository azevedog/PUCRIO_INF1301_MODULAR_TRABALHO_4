@echo off
SET src=
SET dst=INF1301-Trab01-FPFMMQPF\%src%

FOR /F "delims=" %%a IN (%src%.files) DO XCOPY "%src%%%a" "%dst%" /Y
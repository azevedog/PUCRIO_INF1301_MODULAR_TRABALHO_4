@echo off

DEL "INF1301-Trab02-FPFMMQPF\*.*" /F /S /Q

CALL "MoveFiles.bat"
CALL "TRAB2-1\MoveFiles.bat"
CALL "TRAB2-2\MoveFiles.bat"
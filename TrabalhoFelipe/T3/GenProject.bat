@echo off

DEL "INF1301-Trab03-FPFMMQPF\*.*" /F /S /Q

CALL "MoveFiles.bat"
CALL "TRAB3-1\MoveFiles.bat"
CALL "TRAB3-2\MoveFiles.bat"
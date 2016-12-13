@echo off

DEL "INF1301-Trab01-FPFMMQPF\*.*" /F /S /Q

CALL "MoveFiles.bat"
CALL "TRAB1-1\MoveFiles.bat"
CALL "TRAB1-2\MoveFiles.bat"
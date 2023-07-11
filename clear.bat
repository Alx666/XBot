@echo off

cd XBot3Dll
rd /S /Q release
rd /S /Q debug
cd..

cd XBotDll
rd /S /Q release
rd /S /Q debug
cd..

cd XBotFOpsDll
rd /S /Q release
rd /S /Q debug
cd..

cd XBotLauncher
rd /S /Q release
rd /S /Q debug
cd..

cd XTools
rd /S /Q release
rd /S /Q debug
cd..

cd XToolsDll
rd /S /Q release
rd /S /Q debug
cd..

echo on



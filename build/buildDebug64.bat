echo %HVL_SIM_PROJECT_DIR%
cd %HVL_SIM_PROJECT_DIR%/support\util_iocalibrationtool\build\Debug

echo

dir
del /Q CMakeFiles
del CMakeCache.txt

cmake -DPlatform=64 -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 15 Win64" ..
devenv util_iocalibrationtool.vcxproj /Build  "Debug|x64"

cd %HVL_SIM_PROJECT_DIR%/support\util_iocalibrationtool\build

pause
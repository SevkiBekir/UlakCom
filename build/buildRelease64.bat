echo %HVL_SIM_PROJECT_DIR%
cd %HVL_SIM_PROJECT_DIR%/support\util_iocalibrationtool\build\Release

echo

dir
del /Q CMakeFiles
del CMakeCache.txt

cmake -DPlatform=64 -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 15 Win64" ..
devenv util_iocalibrationtool.vcxproj /Build  "Release|x64"

cd %HVL_SIM_PROJECT_DIR%/support\util_iocalibrationtool\build

pause
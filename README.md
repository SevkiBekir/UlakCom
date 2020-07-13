# UlakCom

This project is related to implementation of Secondary Node (SN) and Master Node (MN) in 3GPP TS 37.340 V15.7.0 by coding with C++.

## Prerequisite
### Qt Framework
In the project, Qt Framework was used, so your computer should have Qt Framework 5.3.1^ (min 5.3.1) to run.

### Boost Framework
In the project, Boost Framework was used, so your computer should have Boost Framework 1.68^ (min 1.68) to run.

### Cmake
In the project, Cmake was used to generate make files, so your computer should have Cmake 3.8^ (min 3.8) to run. If you have old version of that, probably it may run but you should change the version required section in CmakeList.txt file.


## Compile & Run
> Note that: The application was tested on GNU/Linux Ubuntu 16.04 LTS and Centos 7 OSs
### Compile
In order to compile, you can use Cmake to generate make files. In order to do that, you should follow these steps below:

 1. Go to build folder in the project folder
```
cd PROJECT_FOLDER/build
```
 2. If you want to build debug, then you shold go to Debug folder,  on the other hand,  if you want to build release, then you shold go to Release folder

```
cd Debug
```

or
```
cd Release
```
3.  Clear old cmakefiles
```
rm -rf CMakeCache.txt CMakeFiles cmake_install.cmake Makefile
```
4. Generate cmakefiles with respect to build type [Debug,Release]
```
cmake -DCMAKE_BUILD_TYPE=Debug -DPlatform=64 -G 'Unix Makefiles' ..
```
or
```
cmake -DCMAKE_BUILD_TYPE=Release -DPlatform=64 -G 'Unix Makefiles' ..
```
5. Make them
```
make
```
### Run
In order to run the application, you should go to bin folder
```
cd PROJECT_FOLDER/bin
```
Each application represent as a node. Therefore, you need to run two application if you test SN and MN.

Note that the executable application name can be changed on your OS and build type. You show *ulakcom-v0.1-** application on the bin folder after successfully building. In example, ulakcom-v0.1-64d was used.
```
./ulakcom-v0.1-64d -n MN
```
```
./ulakcom-v0.1-64d -n SN
```
-n parameter means name of the node and it should be matched the config file.

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
#### Config.xml
The file is responsible for the configuration of the app. You should filled if neccessary. Also, the application can be sent the signal for all nodes that is defined in the file, but the signal sequence is embedded in the application therefore the feature cannot be used.

##### Node Definitions 
```
		<node> 
			<name>MN</name> <!-- Enter Node Name -->
			<port>12345</port> <!-- Enter Listener Local Port -->
			<nodesToSend>
				<node name="SN"/> <!-- Enter Node name to send the signal -->
				<node name="UE"/> <!-- Enter Node name to send the signal -->
			</nodesToSend>
		</node>
```

For the case, only MN and SN nodes are communicated each others. The config xml file should be like:
```
<configs>
	<nodes>
		<node>
			<name>MN</name>
			<port>12345</port>
			<nodesToSend>
				<node name="SN"/>
			</nodesToSend>
		</node>
		<node>
			<name>SN</name>
			<port>12355</port>
			<nodesToSend>
				<node name="MN"/>
			</nodesToSend>
		</node>
	</nodes>
</configs>
```


#### Running the application
In order to run the application, you should go to bin folder
```
cd PROJECT_FOLDER/bin
```
Each application represent as a node. Therefore, you need to run two application if you test SN and MN.

> Note that the executable application name can be changed on your OS and build type. You show *ulakcom-v0.1-** application on the bin folder after successfully building. In example, ulakcom-v0.1-64d was used.

```
./ulakcom-v0.1-64d -n MN
```
```
./ulakcom-v0.1-64d -n SN
```
-n parameter means name of the node and it should be matched the config file.

### Message Sequence
The message sequence is defined in the 3GPP TS 37.340 V15.7.0 document by following below:

![SecondaryNodeAdditionProcedure](https://github.com/SevkiBekir/ulakcom/blob/master/resources/images/SecondaryNodeAdditionProcedure.png)

Therefore, firstly MN Application should be sent the signal to SN Application. Then, SN Application should be sent the signal to MN Application. Finally, MN Application should be sent the signal to SN Application. The message sequence will be done after last signal.

> Note that the application could not be tested on Windows and Mac OSs.


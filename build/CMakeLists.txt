cmake_minimum_required(VERSION 3.8)


if (POLICY CMP0042)
    cmake_policy(SET CMP0042 NEW) # CMake 3.0
endif ()

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_NAME ulakcom)

project(${PROJECT_NAME})

set(PROJECT_DIR "..")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../${PROJECT_DIR}/bin/)

set(EXE_OUTPUT_PATH ../${PROJECT_DIR}/bin/)



if (${CMAKE_GENERATOR} STRGREATER "Unix")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
else ()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif ()

file(STRINGS "${PROJECT_DIR}/version/version.txt" VERSION_NUMBER LIMIT_COUNT 1)

if (${CMAKE_GENERATOR} STRGREATER "Visual Studio 15")
    set(CMAKE_DEBUG_POSTFIX -vc141-${Platform}d)
    set(CMAKE_RELEASE_POSTFIX -vc141-${Platform})
    set(CMAKE_RELWITHDEBINFO_POSTFIX -vc141-${Platform}rd)
elseif (${CMAKE_GENERATOR} STRGREATER "Visual Studio 14")
    set(CMAKE_DEBUG_POSTFIX -vc140-${Platform}d)
    set(CMAKE_RELEASE_POSTFIX -vc140-${Platform})
    set(CMAKE_RELWITHDEBINFO_POSTFIX -vc140-${Platform}rd)
elseif (${CMAKE_GENERATOR} STRGREATER "Visual Studio 12")
    set(CMAKE_DEBUG_POSTFIX -vc120-${Platform}d)
    set(CMAKE_RELEASE_POSTFIX -vc120-${Platform})
    set(CMAKE_RELWITHDEBINFO_POSTFIX -vc140-${Platform}rd)
elseif (${CMAKE_GENERATOR} STRGREATER "Visual Studio 11")
    set(CMAKE_DEBUG_POSTFIX -vc110-${Platform}d)
    set(CMAKE_RELEASE_POSTFIX -vc110-${Platform})
    set(CMAKE_RELWITHDEBINFO_POSTFIX -vc110-${Platform}rd)
elseif (${CMAKE_GENERATOR} STRGREATER "Visual Studio 10")
    set(CMAKE_DEBUG_POSTFIX -vc100-${Platform}d)
    set(CMAKE_RELEASE_POSTFIX -vc100-${Platform})
    set(CMAKE_RELWITHDEBINFO_POSTFIX -vc100-${Platform}rd)
elseif (${CMAKE_GENERATOR} STRGREATER "Visual Studio 9")
    set(CMAKE_DEBUG_POSTFIX -vc90-${Platform}d)
    set(CMAKE_RELEASE_POSTFIX -vc90-${Platform})
    set(CMAKE_RELWITHDEBINFO_POSTFIX -vc90-${Platform}rd)
elseif (${CMAKE_GENERATOR} STRGREATER "Unix")
    set(CMAKE_DEBUG_POSTFIX ${Platform}d)
    set(CMAKE_RELEASE_POSTFIX ${Platform})
    set(CMAKE_RELWITHDEBINFO_POSTFIX ${Platform}rd)
endif ()

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(LIB_POSTFIX ${CMAKE_DEBUG_POSTFIX})
elseif (${CMAKE_BUILD_TYPE} MATCHES "Release")
    set(LIB_POSTFIX ${CMAKE_RELEASE_POSTFIX})
elseif (${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo")
    set(LIB_POSTFIX ${CMAKE_RELEASE_POSTFIX})
endif ()


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH $ENV{QTDIR})
set(Qt5Widgets_DIR "$ENV{QTDIR}/lib/cmake/Qt5Widgets")
set(Qt5Designer_DIR "$ENV{QTDIR}/lib/cmake/Qt5Designer")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_VERBOSE_MAKEFILE On)
set(CMAKE_SUPPRESS_REGENERATION true) #disables ZERO_MAKE

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Concurrent REQUIRED)

file(GLOB_RECURSE HEADERS
        "${PROJECT_DIR}/include/*.h")
file(GLOB_RECURSE SOURCES
        "${PROJECT_DIR}/src/*.cpp"
        "${PROJECT_DIR}/src/*.h")
file(GLOB_RECURSE FORMS
        "${PROJECT_DIR}/src/*.ui")
file(GLOB_RECURSE RESOURCES
        "${PROJECT_DIR}/resources/*.qrc")

source_group("include" FILES ${HEADERS})
source_group("src" FILES ${SOURCES})
source_group("form" FILES ${FORMS})
source_group("resource" FILES ${RESOURCES})


include_directories(SYSTEM
        ${PROJECT_DIR}/include
        ${PROJECT_DIR}/cots/boost/boost
        )


link_directories(
        $ENV{QTDIR}/lib
        ${PROJECT_DIR}/lib
        ${PROJECT_DIR}/cots/boost2/stage/lib


)

qt5_wrap_cpp(HEADERS_MOC ${HEADERS})
qt5_wrap_ui(FORMS_HEADERS ${FORMS})
qt5_add_resources(RESOURCE_SOURCES ${RESOURCES})

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} ${FORMS} ${FORMS_HEADERS} ${RESOURCE_SOURCES})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

if (${CMAKE_GENERATOR} STRGREATER "Visual Studio")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /bigobj")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ")
    target_link_libraries(${PROJECT_NAME}
            Qt5::Widgets
            Qt5::Core
            Qt5::Gui
            Qt5::PrintSupport
            Qt5::Network
            Qt5::Concurrent
            )
    add_definitions(-D_WINDOWS -D_WINSOCKAPI_)
    if ((${CMAKE_BUILD_TYPE} MATCHES "Debug") OR (${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo"))
        add_custom_command(TARGET ${PROJECT_NAME}
                POST_BUILD
                COMMAND "${CMAKE_COMMAND}" -E copy "$(OutDir)$(TargetName)$(TargetExt)" "${EXE_OUTPUT_PATH}/${PROJECT_NAME}-${VERSION_NUMBER}${LIB_POSTFIX}.exe"

                COMMAND "${CMAKE_COMMAND}" -E copy "$(OutDir)$(TargetName).pdb" "${EXE_OUTPUT_PATH}/${PROJECT_NAME}-${VERSION_NUMBER}${LIB_POSTFIX}.pdb"

                )
    elseif (${CMAKE_BUILD_TYPE} MATCHES "Release")
        add_custom_command(TARGET ${PROJECT_NAME}
                POST_BUILD
                COMMAND "${CMAKE_COMMAND}" -E copy "$(OutDir)$(TargetName)$(TargetExt)" "${EXE_OUTPUT_PATH}/${PROJECT_NAME}-${VERSION_NUMBER}${LIB_POSTFIX}.exe"

                )
    endif ()
elseif (${CMAKE_GENERATOR} STRGREATER "Unix")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -m${Platform}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -m${Platform}")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -m${Platform}")
    target_link_libraries(${PROJECT_NAME}
            Qt5::Widgets
            Qt5::Core
            Qt5::Gui
            Qt5::PrintSupport
            Qt5::Network
            Qt5::Concurrent
            boost_math_c99f
            boost_thread
            boost_filesystem
            boost_system
            )
    add_definitions(-DLINUX)
    add_custom_command(TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}-v${VERSION_NUMBER}-${LIB_POSTFIX}"
#            COMMAND "${CMAKE_COMMAND}" -E remove ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}
            )
endif ()


cmake_minimum_required(VERSION 2.8)
project(Whitebox_crypto_AES)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -frtti -fexceptions")
option(NTL_NO_DEFAULT_PATH "Using just given paths when searching for NTL" OFF)

set(SOURCE_FILES
    base.h
    base.cpp
    BGEAttack.cpp
    BGEAttack.h
    BGEAttack_test.cpp
    GenericAES.cpp
    GenericAES.h
    LinearAffineEq.cpp
    LinearAffineEq.h
    LinearAffineEq_test.cpp
    md5.c
    md5.h
    MixingBijections.cpp
    MixingBijections.h
    NTLUtils.cpp
    NTLUtils.h
    WBAES.cpp
    WBAES.h
    WBAESGenerator.cpp
    WBAESGenerator.h)

add_library(mywbaes STATIC ${SOURCE_FILES} my_wbaes.cpp)
add_executable(main ${SOURCE_FILES} main.cpp)
add_executable(testing ${SOURCE_FILES} testing.cpp testing.h)
add_executable(mymain mymain.cpp)

# TODO: probably replace this hardcoded stuff
# NTL
# if (NTL_NO_DEFAULT_PATH)
#     set(NTL_MODIF NO_DEFAULT_PATH)
#     message("Not using default paths for NTL search, ${NTL_MODIF}")
# endif (NTL_NO_DEFAULT_PATH)
# message("HOME: $ENV{HOME}")
# find_path(NTL_INCLUDE_PATH NAMES NTL/mat_GF2.h PATHS $ENV{HOME}/ntl $ENV{HOME}/ntl/include /usr/local /opt/local /usr ${NTL_MODIF})
set(NTL_INCLUDE_PATH "/home/cppko/ntl")
message("NTL_INCLUDE_PATH: ${NTL_INCLUDE_PATH}")

# find_library(NTL_LIB ntl PATHS ${CMAKE_CURRENT_SOURCE_DIR} $ENV{HOME}/ntl $ENV{HOME}/ntl/lib /usr/local /opt/local /usr ${NTL_MODIF})
# if(NOT NTL_LIB)
#     message(FATAL_ERROR "ntl library not found.  Rerun cmake with -DCMAKE_PREFIX_PATH=\"<path to lib1>;<path to lib2>\"")
# endif()
set(NTL_LIB "/home/cppko/ntl/libntl.a")
message("NTL_LIB: ${NTL_LIB}")
include_directories(${NTL_INCLUDE_PATH})

# BOOST
# TODO: probably replace this hardcoded stuff
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
# find_package(Boost REQUIRED COMPONENTS program_options serialization iostreams random)
set(Boost_INCLUDE_DIR "/home/cppko/Source/Boost-for-Android/build/include/boost-1_55")
set(BOOST_ROOT "/home/cppko/Source/Boost-for-Android/build")
include_directories(${Boost_INCLUDE_DIR})
# include_directories(${Boost_INCLUDE_DIRS})
set(Boost_LIBRARIES "${BOOST_ROOT}/lib/libboost_iostreams-gcc-mt-1_55.a" "${BOOST_ROOT}/lib/libboost_serialization-gcc-mt-1_55.a" "${BOOST_ROOT}/lib/libboost_program_options-gcc-mt-1_55.a" "${BOOST_ROOT}/lib/libboost_random-gcc-mt-1_55.a")

add_custom_command(TARGET mywbaes
   POST_BUILD
# TODO: probably replace this hardcoded stuff
   COMMAND echo "Running custom command"
   COMMAND echo "CREATE libwbaes.a" > combine_wb.ar
   COMMAND echo "ADDLIB ${CMAKE_BINARY_DIR}/libmywbaes.a" >> combine_wb.ar
   COMMAND echo "ADDLIB ${NTL_LIB}" >> combine_wb.ar
   COMMAND echo "ADDLIB ${BOOST_ROOT}/lib/libboost_iostreams-gcc-mt-1_55.a" >> combine_wb.ar
   COMMAND echo "ADDLIB ${BOOST_ROOT}/lib/libboost_serialization-gcc-mt-1_55.a" >> combine_wb.ar
   COMMAND echo "ADDLIB ${BOOST_ROOT}/lib/libboost_program_options-gcc-mt-1_55.a" >> combine_wb.ar
   COMMAND echo "ADDLIB ${BOOST_ROOT}/lib/libboost_random-gcc-mt-1_55.a" >> combine_wb.ar
   COMMAND echo "SAVE" >> combine_wb.ar
   COMMAND echo "END" >> combine_wb.ar
   COMMAND /home/cppko/Android/Sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-ar -M < combine_wb.ar
   COMMAND rm combine_wb.ar
   COMMAND /home/cppko/Android/Sdk/ndk-bundle/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip --strip-unneeded ${CMAKE_BINARY_DIR}/libwbaes.a
   COMMAND mv ${CMAKE_BINARY_DIR}/libwbaes.a ${CMAKE_BINARY_DIR}/libmywbaes.a
)

# Linking
target_link_libraries(main ${NTL_LIB} ${Boost_LIBRARIES})
target_link_libraries(testing ${NTL_LIB} ${Boost_LIBRARIES})
target_link_libraries(mymain mywbaes)
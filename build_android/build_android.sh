#!/bin/bash
/home/cppko/Android/Sdk/cmake/3.6.3155560/bin/cmake \
-DNTL_NO_DEFAULT_PATH=ON \
-H`pwd`/.. \
-B`pwd`/cmake_build \
-G"Android Gradle - Ninja" \
-DANDROID_ABI=armeabi \
-DANDROID_NDK=/home/cppko/Android/Sdk/ndk-bundle \
-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=`pwd`/cmake_output \
-DCMAKE_BUILD_TYPE=Release \
-DCMAKE_MAKE_PROGRAM=/home/cppko/Android/Sdk/cmake/3.6.3155560/bin/ninja \
-DCMAKE_TOOLCHAIN_FILE=/home/cppko/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake \
-DANDROID_NATIVE_API_LEVEL=19 \
-DANDROID_TOOLCHAIN=clang \
-DANDROID_STL=c++_static \
-DCMAKE_CXX_FLAGS=-O2 \
-DCMAKE_C_FLAGS=-O2
# cmake .
# cmake -DNTL_NO_DEFAULT_PATH=ON .
# echo "Running build"
# make clean
# make
/home/cppko/Android/Sdk/cmake/3.6.3155560/bin/ninja -C ./cmake_build

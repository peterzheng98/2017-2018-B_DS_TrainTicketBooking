cmake_minimum_required(VERSION 3.9)
project(2018DataStructureBigWork)

set(CMAKE_CXX_STANDARD 17)

#add_executable(2018DataStructureBigWork main.cpp Kernel.cpp Kernel.h CoreData.h BigNum.hpp Exception.hpp Set.hpp Engine.cpp Engine.h String.cpp String.h HashTookit.h HashTookit.cpp HashTookit.h)
#add_executable(Test main2.cpp Set.hpp)
#add_executable(TestWstring WStringTest.cpp WString.hpp )
add_executable(TestString main3.cpp String.h CoreData.h BPlusTree.hpp)
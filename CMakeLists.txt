cmake_minimum_required(VERSION 3.9)
project(2018DataStructureBigWork)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-O2 -w")

#add_executable(2018DataStructureBigWork main.cpp Kernel.hpp CoreData.h BigNum.hpp Exception.hpp Set.hpp Engine.cpp Engine.h String.h HashTookit.h HashTookit.cpp HashTookit.h ParserForCommand.h InternalData.h)
#add_executable(Test main2.cpp Set.hpp)
#add_executable(TestWstring WStringTest.cpp WString.hpp )
#add_executable(TestString main3.cpp String.h CoreData.h BPlusTree.hpp)
#add_executable(TestParser main.cpp ParserForCommand.h String.h DateAndTime.h CoreData.h Kernel.hpp BPlusTree.hpp)
#add_executable(TestBSTree UpdateTest.cpp BPlusTree.hpp)
#add_executable(Loxy2Internal main5.cpp loxy2Internal.h)
add_executable(CommandParser commandMain.cpp InternalData.h Kernel.hpp String.h CoreData.h)
#add_executable(Fucker commandMain.cpp Kernel.hpp)
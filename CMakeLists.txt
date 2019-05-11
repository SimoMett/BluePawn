cmake_minimum_required(VERSION 3.12)
project(BluePawn)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets REQUIRED net core base adv xml stc)
include(${wxWidgets_USE_FILE})

add_subdirectory(GTest)

set(SOURCE_FILES MainApp.cpp MainApp.h MainWindow.cpp MainWindow.h CompilerDialog.cpp CompilerDialog.h IncludeDirDialog.cpp IncludeDirDialog.h WindowsIDs.h PawnDocument.cpp PawnDocument.h Research.cpp Research.h ConfigFile.cpp ConfigFile.h CompilerCfgDialog.cpp CompilerCfgDialog.h)

add_executable(BluePawn ${SOURCE_FILES})

target_link_libraries(BluePawn ${wxWidgets_LIBRARIES} stdc++fs)
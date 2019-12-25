cmake_minimum_required(VERSION 3.12)
project(BluePawn)

set(CMAKE_CXX_STANDARD 14)

#boost
set(boost_min_ver 1.71.0)
set(boost_libs system filesystem)
find_package(Boost ${boost_min_ver})
if(Boost_FOUND)
    find_package(Boost ${boost_min_ver} COMPONENTS ${boost_libs})
endif()

#wx
find_package(wxWidgets REQUIRED net core base adv xml stc)
include(${wxWidgets_USE_FILE})

add_subdirectory(GTest)

add_compile_definitions(BP_VERSION="v0.4")

set(SOURCE_FILES MainApp.cpp MainApp.h MainWindow.cpp MainWindow.h CompilerDialog.cpp CompilerDialog.h IncludeDirDialog.cpp IncludeDirDialog.h WindowsIDs.h PawnDocument.cpp PawnDocument.h Research.cpp Research.h ConfigFile.cpp ConfigFile.h CompilerCfgDialog.cpp CompilerCfgDialog.h BluePawnPngRes.hpp IncludeFile.cpp IncludeFile.h)

add_executable(BluePawn ${SOURCE_FILES})

target_link_libraries(BluePawn ${Boost_LIBRARIES} ${wxWidgets_LIBRARIES})
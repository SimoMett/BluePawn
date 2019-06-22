//
// Created by matteo on 10/05/19.
//

#include <gtest/gtest.h>
#include <unistd.h>
#include <pwd.h>
#include <iostream>
#include <filesystem>

using namespace std;

int main(int argc, char ** argv)
{
    struct stat info;
    if(!(!stat(string(getpwuid(getuid())->pw_dir).append("/.BluePawn/GTEST/").c_str(), &info) && (info.st_mode & S_IFDIR)))
        std::filesystem::create_directories(string(getpwuid(getuid())->pw_dir).append("/.BluePawn/GTEST"));

    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
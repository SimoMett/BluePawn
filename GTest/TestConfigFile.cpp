//
// Created by matteo on 10/05/19.
//
#include <gtest/gtest.h>
#include "../ConfigFile.h"

TEST(ConfigFile,DefaultConstructor)
{
    bool alreadyExisted=std::filesystem::exists("config.ini");
    ConfigFile configFile;

    ASSERT_TRUE(std::filesystem::exists("config.ini"));

    ASSERT_TRUE(configFile.GetKey("PawnccLocation")=="pawncc");

    if(!alreadyExisted)
        std::filesystem::remove("config.ini");
}

TEST(ConfigFile,AddKey)
{
    ConfigFile configFile;
    configFile.AddKey("key_test","value_test");
    ASSERT_TRUE(configFile.GetKey("key_test")=="value_test");
}

TEST(ConfigFile, BadKey)
{
    if(filesystem::exists("config.ini")) filesystem::rename("config.ini","config.ini_bak");

    ofstream file("config.ini");
    file << "THISISABADKEY=44"<<endl;
    file.close();

    ASSERT_THROW(ConfigFile configFile,runtime_error);

    if(filesystem::exists("config.ini_bak")) filesystem::rename("config.ini_bak","config.ini");
}
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

    ASSERT_TRUE(configFile.GetKeyValue("PawnccLocation")=="pawncc");

    if(!alreadyExisted)
        std::filesystem::remove("config.ini");
}

TEST(ConfigFile,AddKey)
{
    ConfigFile configFile;
    configFile.SetKeyValue("key_test", "value_test");
    ASSERT_TRUE(configFile.GetKeyValue("key_test")=="value_test");
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

TEST(ConfigFile, BadEntry)
{
    if(filesystem::exists("config.ini")) filesystem::rename("config.ini","config.ini_bak");

    ofstream file("config.ini");
    file << "THISISABADKEY"<<endl;
    file.close();

    ASSERT_THROW(ConfigFile configFile,runtime_error);

    if(filesystem::exists("config.ini_bak")) filesystem::rename("config.ini_bak","config.ini");
}
TEST(ConfigFile, EntryWithSpace)
{
    if(filesystem::exists("config.ini")) filesystem::rename("config.ini","config.ini_bak");

    ConfigFile configFile;
    configFile.SetKeyValue("test space key","val");
    ASSERT_TRUE(configFile.GetKeyValue("testspacekey")=="val");

    if(filesystem::exists("config.ini_bak")) filesystem::rename("config.ini_bak","config.ini"); 
}
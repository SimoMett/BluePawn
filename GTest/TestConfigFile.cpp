//
// Created by matteo on 10/05/19.
//
#include <gtest/gtest.h>

#include "../ConfigFile.h"

string ConfigIniPath=string(getpwuid(getuid())->pw_dir).append("/.BluePawn/GTEST/config.ini");

TEST(ConfigFile,DefaultConstructor)
{
    bool alreadyExisted=std::filesystem::exists(ConfigIniPath);
    ConfigFile configFile;

    ASSERT_TRUE(std::filesystem::exists(ConfigIniPath));

    ASSERT_TRUE(configFile.GetKeyValue("PawnccLocation")=="pawncc");

    if(!alreadyExisted)
        std::filesystem::remove(ConfigIniPath);
}

TEST(ConfigFile,AddKey)
{
    ConfigFile configFile;
    configFile.SetKeyValue("key_test", "value_test");
    ASSERT_TRUE(configFile.GetKeyValue("key_test")=="value_test");
}

TEST(ConfigFile, BadKey)
{
    if(filesystem::exists(ConfigIniPath)) filesystem::rename(ConfigIniPath,ConfigIniPath+("_bak"));

    ofstream file(ConfigIniPath);
    file << "THISISABADKEY=44"<<endl;
    file.close();

    ASSERT_THROW(ConfigFile configFile,runtime_error);

    if(filesystem::exists(ConfigIniPath+("_bak"))) filesystem::rename(ConfigIniPath+("_bak"),ConfigIniPath);
}

TEST(ConfigFile, BadEntry)
{
    if(filesystem::exists(ConfigIniPath)) filesystem::rename(ConfigIniPath,ConfigIniPath+("_bak"));

    ofstream file(ConfigIniPath);
    file << "THISISABADKEY"<<endl;
    file.close();

    ASSERT_THROW(ConfigFile configFile,runtime_error);

    if(filesystem::exists(ConfigIniPath+("_bak"))) filesystem::rename(ConfigIniPath+("_bak"),ConfigIniPath);
}
TEST(ConfigFile, EntryWithSpace)
{
    if(filesystem::exists(ConfigIniPath)) filesystem::rename(ConfigIniPath,ConfigIniPath+("_bak"));

    ConfigFile configFile;
    configFile.SetKeyValue("test space key","val");
    ASSERT_TRUE(configFile.GetKeyValue("testspacekey")=="val");

    if(filesystem::exists(ConfigIniPath+("_bak"))) filesystem::rename(ConfigIniPath+("_bak"),ConfigIniPath);
}

TEST(ConfigFile,SaveConfigFile)
{
    if(filesystem::exists(ConfigIniPath)) filesystem::rename(ConfigIniPath,ConfigIniPath+("_bak"));
    
    ConfigFile * configFile=new ConfigFile();
    
    configFile->SetKeyValue("PawnccLocation","pawncctest");
    
    delete configFile;
    
    ifstream ifstream1(ConfigIniPath);
    
    string line;
    bool foundEntry=false;
    while(getline(ifstream1,line))
    {
        if(line=="PawnccLocation=pawncctest")
            foundEntry=true;
    }
    
    ifstream1.close();
    
    if(filesystem::exists(ConfigIniPath+("_bak"))) filesystem::rename(ConfigIniPath+("_bak"),ConfigIniPath);
    
    ASSERT_TRUE(foundEntry);
}
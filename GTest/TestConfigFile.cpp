//
// Created by matteo on 10/05/19.
//
#include <gtest/gtest.h>
#include "../ConfigFile.h"

TEST(ConfigFile,DefaultConstructor)
{
    ConfigFile configFile;
    ASSERT_TRUE(configFile.GetKey("PawnccLocation")=="pawncc");
}
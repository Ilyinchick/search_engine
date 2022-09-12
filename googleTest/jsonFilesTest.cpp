#include "gtest/gtest.h"
#include "fs_exception.h"
#include "ConverterJSON.h"



TEST(jsonFiles, configExist) {
    std::ifstream file("../src/manage/config.json", std::ios::in);
    EXPECT_TRUE(file.is_open());
}

TEST (jsonFiles, configNotEmpty) {
    std::ifstream file("../src/manage/config.json");
    nlohmann::json jfile;
    file >> jfile;
    EXPECT_FALSE(jfile.empty());
}

TEST (jsonFiles, configField) {
    std::ifstream file("../src/manage/config.json");
    nlohmann::json jfile;
    file >> jfile;
    EXPECT_TRUE(jfile.contains("config"));
}

TEST (jsonFiles, configFieldIsNotEmpty) {
    std::ifstream file("../src/manage/config.json");
    nlohmann::json jfile;
    file >> jfile;
    EXPECT_FALSE(jfile.find("config")->empty());
}

TEST (jsonFiles, configFieldContaisAllFields) {
    std::ifstream file("../src/manage/config.json");
    nlohmann::json jfile;
    file >> jfile;
    EXPECT_TRUE(jfile.find("config")->contains("name"));
    EXPECT_TRUE(jfile.find("config")->contains("max_responses"));
    EXPECT_TRUE(jfile.find("config")->contains("version"));
    EXPECT_TRUE(jfile.contains("files"));
}

TEST (jsonFiles, versionCheck) {
    std::ifstream file("../src/manage/config.json");
    nlohmann::json jfile;
    file >> jfile;
    EXPECT_EQ(jfile.find("config")->find("version").value(), VERSION);
}

TEST (jsonFiles, requestsFileExist) {
    std::ifstream file("../src/manage/requests.json");
    EXPECT_TRUE(file.is_open());
}

TEST (jsonFiles, requestFileIsNotEmpty) {
    std::ifstream file("../src/manage/requests.json");
    nlohmann::json jfile;
    file >> jfile;
    EXPECT_FALSE(jfile.empty());
}

TEST (jsonFiles, requestsFileContainsRequestsField) {
    std::ifstream file("../src/manage/requests.json");
    nlohmann::json jfile;
    file >> jfile;
    EXPECT_TRUE(jfile.contains("requests"));
}



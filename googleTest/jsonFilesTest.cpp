#include "gtest/gtest.h"
#include "../include/fs_exception.h"
#include "../include/ConverterJSON.h"

TEST(jsonFiles, configExist) {
    std::ifstream file;
    file.open(CONFIG_PATH);
    EXPECT_TRUE(file.is_open());
}

TEST (jsonFiles, configNotEmpty) {
    std::ifstream file;
    nlohmann::json jfile;
    file.open(CONFIG_PATH);
    file >> jfile;
    EXPECT_FALSE(jfile.empty());
}

TEST (jsonFiles, configField) {
    std::ifstream file;
    nlohmann::json jfile;
    file.open(CONFIG_PATH);
    file >> jfile;
    EXPECT_TRUE(jfile.contains("config"));
}

TEST (jsonFiles, configFieldIsNotEmpty) {
    std::ifstream file;
    nlohmann::json jfile;
    file.open(CONFIG_PATH);
    file >> jfile;
    EXPECT_FALSE(jfile.find("config")->empty());
}

TEST (jsonFiles, configFieldContaisAllFields) {
    std::ifstream file;
    nlohmann::json jfile;
    file.open(CONFIG_PATH);
    file >> jfile;
    EXPECT_TRUE(jfile.find("config")->contains("name"));
    EXPECT_TRUE(jfile.find("config")->contains("max_responses"));
    EXPECT_TRUE(jfile.find("config")->contains("version"));
    EXPECT_TRUE(jfile.contains("files"));
}

TEST (jsonFiles, versionCheck) {
    std::ifstream file;
    nlohmann::json jfile;
    file.open(CONFIG_PATH);
    file >> jfile;
    EXPECT_EQ(jfile.find("config")->find("version").value(), VERSION);
}

TEST (jsonFiles, requestsFileExist) {
    std::ifstream file;
    file.open(REQUESTS_PATH);
    EXPECT_TRUE(file.is_open());
}

TEST (jsonFiles, requestFileIsNotEmpty) {
    std::ifstream file;
    nlohmann::json jfile;

    file.open(REQUESTS_PATH);
    file >> jfile;
    EXPECT_FALSE(jfile.empty());
}

TEST (jsonFiles, requestsFileContainsRequestsField) {
    std::ifstream file;
    nlohmann::json jfile;

    file.open(REQUESTS_PATH);
    file >> jfile;
    EXPECT_TRUE(jfile.contains("requests"));
}



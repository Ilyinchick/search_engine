#include "gtest/gtest.h"
#include "../include/fs_exception.h"
#include "../include/ConverterJSON.h"

std::string GetCurrentDirectory()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

std::string path = std::filesystem::path(GetCurrentDirectory()).parent_path().parent_path().string().append("\\manage\\");

TEST(jsonFiles, configExist) {
    std::string path = std::filesystem::path(GetCurrentDirectory()).parent_path().parent_path().string().append("\\manage\\");
    std::ifstream file;
    file.open(path.append("config.json"));
    EXPECT_TRUE(file.is_open());
}

TEST (jsonFiles, configNotEmpty) {
    std::string path = std::filesystem::path(GetCurrentDirectory()).parent_path().parent_path().string().append("\\manage\\");
    std::ifstream file;
    nlohmann::json jfile;
    file.open(path.append("config.json"));
    file >> jfile;
    EXPECT_FALSE(jfile.empty());
}

TEST (jsonFiles, configField) {
    std::string path = std::filesystem::path(GetCurrentDirectory()).parent_path().parent_path().string().append("\\manage\\");
    std::ifstream file;
    nlohmann::json jfile;
    file.open(path.append("config.json"));
    file >> jfile;
    EXPECT_TRUE(jfile.contains("config"));
}

TEST (jsonFiles, configFieldIsNotEmpty) {
    std::string path = std::filesystem::path(GetCurrentDirectory()).parent_path().parent_path().string().append("\\manage\\");
    std::ifstream file;
    nlohmann::json jfile;
    file.open(path.append("config.json"));
    file >> jfile;
    EXPECT_FALSE(jfile.find("config")->empty());
}

TEST (jsonFiles, configFieldContaisAllFields) {
    std::string path = std::filesystem::path(GetCurrentDirectory()).parent_path().parent_path().string().append("\\manage\\");
    std::ifstream file;
    nlohmann::json jfile;
    file.open(path.append("config.json"));
    file >> jfile;
    EXPECT_TRUE(jfile.find("config")->contains("name"));
    EXPECT_TRUE(jfile.find("config")->contains("max_responses"));
    EXPECT_TRUE(jfile.find("config")->contains("version"));
    EXPECT_TRUE(jfile.contains("files"));
}

TEST (jsonFiles, versionCheck) {
    std::string path = std::filesystem::path(GetCurrentDirectory()).parent_path().parent_path().string().append("\\manage\\");
    std::ifstream file;
    nlohmann::json jfile;
    file.open(path.append("config.json"));
    file >> jfile;
    EXPECT_EQ(jfile.find("config")->find("version").value(), VERSION);
}

TEST (jsonFiles, requestsFileExist) {
    std::string path = std::filesystem::path(GetCurrentDirectory()).parent_path().parent_path().string().append("\\manage\\");
    std::ifstream file;
    file.open(path.append("requests.json"));
    EXPECT_TRUE(file.is_open());
}

TEST (jsonFiles, requestFileIsNotEmpty) {
    std::string path = std::filesystem::path(GetCurrentDirectory()).parent_path().parent_path().string().append("\\manage\\");
    std::ifstream file;
    nlohmann::json jfile;

    file.open(path.append("requests.json"));
    file >> jfile;
    EXPECT_FALSE(jfile.empty());
}

TEST (jsonFiles, requestsFileContainsRequestsField) {
    std::string path = std::filesystem::path(GetCurrentDirectory()).parent_path().parent_path().string().append("\\manage\\");
    std::ifstream file;
    nlohmann::json jfile;

    file.open(path.append("requests.json"));
    file >> jfile;
    EXPECT_TRUE(jfile.contains("requests"));
}



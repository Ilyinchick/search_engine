#include "gtest/gtest.h"
#include "../include/fs_exception.h"
#include "../include/ConverterJSON.h"

bool stringEqual(const std::string& str1, const std::string& str2) {
    if (str1.length() != str2.length()) {
        return false;
    }
    for (int i = 0; i < str1.length(); i++) {
        if (str1[i] != str2[i]) return false;
    }
    return true;
}

TEST(converterJSON, GetTextDocuments) {
    auto converter = new ConverterJSON();
    const std::string test = "C++\nwas\ntest1";
    auto list = converter->GetTextDocuments();
    EXPECT_GT(list.size(), 0);
    EXPECT_TRUE(stringEqual(list[2], test));
}

TEST(converterJSON, GetResponsesLimit) {
    auto converter = new ConverterJSON();
    EXPECT_EQ(converter->GetResponsesLimit(), 2);
}

TEST(converterJSON, GetRequests) {
    auto converter = new ConverterJSON();
    auto list = converter->GetRequests();
    EXPECT_TRUE(stringEqual(list[2], "test1"));
}
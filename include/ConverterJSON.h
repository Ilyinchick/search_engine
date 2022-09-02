#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"
#include "InvertredIndex.h"
#include "SearchServer.h"


const static std::string VERSION = "0.1";

const static std::string CONFIG_PATH = R"(C:\Users\ailyi\CLionProjects\Skillbox\search_engine\manage\config.json)";
const static std::string REQUESTS_PATH = R"(C:\Users\ailyi\CLionProjects\Skillbox\search_engine\manage\requests.json)";
const static std::string ANSWERS_PATH = R"(C:\Users\ailyi\CLionProjects\Skillbox\search_engine\manage\answers.json)";

class ConverterJSON {

public:

    ConverterJSON() = default;

/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/
    std::vector<std::string> GetTextDocuments();

/**
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/
    int GetResponsesLimit();

/**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
    std::vector<std::string> GetRequests();

/**
* Положить в файл answers.json результаты поисковых запросов
*/
    void putAnswers(std::vector<std::vector<RelativeIndex>>& answers);

    //throws Expetion if 'config' or 'request' files are not valid
    void testFilesForValid();

private:
    /*
     * @return std::string as text of document
     * @param path - global path to txt resource file
     */
    static std::string getDoc(const std::string &path);

    static void testConfigJson(const std::string &path);

    static void testRequestsJson(const std::string &path);

    /*
     * @return json object
     * @param path - global path to json resource file
     */
    static nlohmann::json getJson(const std::string& path);

    nlohmann::json getConfigJson();

    nlohmann::json getRequestsJson();
};

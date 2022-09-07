#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"
#include "InvertredIndex.h"
#include "SearchServer.h"


const static std::string VERSION = "0.1";

class ConverterJSON {

public:
    ConverterJSON() = default;

/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/
    [[nodiscard]] std::vector<std::string> GetTextDocuments() const;

/**
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/
    [[nodiscard]] int GetResponsesLimit() const;

/**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
    [[nodiscard]] std::vector<std::string> GetRequests() const;

/**
* Положить в файл answers.json результаты поисковых запросов
*/
    void putAnswers(std::vector<std::vector<RelativeIndex>>& answers) const;

    //throws Expetion if 'config' or 'request' files are not valid
    void testFilesForValid() const;

private:
    /*
     * @return std::string as text of document
     * @param path - global path to txt resource file
     */
    [[nodiscard]] std::string getDoc(const std::string &path) const;

    void testConfigJson(const std::string &path) const;

    void testRequestsJson(const std::string &path) const;

    /*
     * @return json object
     * @param path - global path to json resource file
     */
    [[nodiscard]] nlohmann::json getJson(const std::string& path) const;

    [[nodiscard]] nlohmann::json getConfigJson() const;

    [[nodiscard]] nlohmann::json getRequestsJson() const;

};

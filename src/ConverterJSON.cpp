#include "../include/fs_exception.h"
#include "../include/ConverterJSON.h"

// opens file and returns its data with string
// throws FileNotFoundException and EmptyFileException if path is invalid or file is empty
std::string ConverterJSON::getDoc(const std::string &path) {
    std::ifstream file;
    std::string answer, buff;

    file.open(path);
    if (!file.is_open()) throw FileNotFoundException();

    while (file) {
        std::getline(file, buff);
        answer.append(buff);
        if (!file.eof()) answer.append("\n");
        buff.clear();
    }

    if (answer.length() <= 1) throw EmptyFileException();

    return answer;
}

void ConverterJSON::testConfigJson(const std::string &path) {
    std::ifstream file(path);
    if (!file.is_open()) throw FileNotFoundException();

    nlohmann::json dict;
    file >> dict;
    if (dict.empty()) throw EmptyFileException();
    if (!dict.contains("config")) throw NoConfigFieldException();
    if (dict.find("config").value().empty()) throw ConfigFieldIsEmptyException();
    if (dict.find("config")->find("version").value() != VERSION) throw IncorrectVersionJsonException();

}

void ConverterJSON::testRequestsJson(const std::string &path) {
    nlohmann::json dict;
    try {
        dict = getJson(path);
        if (!dict.contains("requests")) throw NoRequestsFieldException();
        if (dict.find("requests").value().empty()) throw EmptyRequestsFieldException();
    }
    catch (FileNotFoundException &ex) {
        std::cout << ex.what() << std::endl;
    }
    catch (EmptyFileException &ex) {
        std::cout << ex.what() << std::endl;
    }

}


// Returns vector with data in files which specified in config.json in field "files"
std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::vector<std::string> list;
    nlohmann::json doc = getConfigJson();
    for (std::string s: doc.find("files").value()) {
        try {
            list.push_back(getDoc(s));
        }
        catch (FileNotFoundException &ex) {
            std::cout << ex.what() << " in ConverterJSON.cpp 62" << std::endl;
        }
        catch (EmptyFileException &ex) {
            std::cout << ex.what() << " in ConverterJSON.cpp 62" << std::endl;
        }
    }
    return list;
}

//returns int value of "max_responses" field in config.json
int ConverterJSON::GetResponsesLimit() {
    return getConfigJson().find("config")->find("max_responses").value();
}

//returns list of requests in requests.json
std::vector<std::string> ConverterJSON::GetRequests() {
    std::vector<std::string> requests;
    nlohmann::json doc = getRequestsJson();
    for (std::string s: doc.find("requests").value()) {
        for (auto &c: s) c = (char) tolower(c);
        requests.push_back(s);
    }
    return requests;
}

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> &answers) {
    std::ofstream file(ANSWERS_PATH);
    nlohmann::json doc;

    doc["answers"];
    for (int i = 0; i < answers.size(); i++) {
        std::string request = "request" + std::to_string(i);
        auto relevanceVector = answers[i];
        doc.find("answers").value()[request];

        if (relevanceVector.size() > 1) {
            int limit = 0;
            doc.find("answers").value().find(request).value()["relevance"];
            for (auto data: relevanceVector) {
                limit++;
                doc.find("answers").value().find(request).value().find("relevance").value()["docid: "
                                                                                            + std::to_string(
                        data.doc_id)] = "rank: " + std::to_string(data.rank);
            }
            doc.find("answers").value().find(request).value()["result"] = "true";
        } else if (relevanceVector.size() == 1) {
            doc.find("answers").value().find(request).value()["docid: "
                                                                                        + std::to_string(
                    relevanceVector.back().doc_id)] = "rank: " + std::to_string(relevanceVector.back().rank);
            doc.find("answers").value().find(request).value()["result"] = "true";
        } else {
            doc.find("answers").value().find(request).value()["result"] = "false";
        }
    }

    file << doc;
    file.close();
}

// throws FileNotFoundException and EmptyFileException if path or dile is invalid, otherwise return json
nlohmann::json ConverterJSON::getJson(const std::string &path) {
    std::ifstream file(path);
    nlohmann::json doc;

    if (!file.is_open()) throw FileNotFoundException();
    file >> doc;
    if (doc.empty()) throw EmptyFileException();

    return doc;
}

// basic checks. Returns json with data if file and path are valid, otherwise returns empty file
nlohmann::json ConverterJSON::getConfigJson() {
    nlohmann::json doc;
    try {
        doc = getJson(CONFIG_PATH);
        if (!doc.contains("config")) throw NoConfigFieldException();
        if (doc.find("config").value().empty()) throw ConfigFieldIsEmptyException();
        if (doc.find("config")->find("version").value() != VERSION) throw IncorrectVersionJsonException();
    }
    catch (FileNotFoundException &ex) {
        std::cout << ex.what();
    }
    catch (EmptyFileException &ex) {
        std::cout << ex.what() << std::endl;
    }
    catch (NoConfigFieldException &ex) {
        std::cout << ex.what() << std::endl;
    }
    catch (ConfigFieldIsEmptyException &ex) {
        std::cout << ex.what() << std::endl;
    }
    catch (IncorrectVersionJsonException &ex) {
        std::cout << ex.what() << std::endl;
    }
    return doc;
}

//returns requests.json if its data is valid
nlohmann::json ConverterJSON::getRequestsJson() {
    nlohmann::json doc;

    try {
        doc = getJson(REQUESTS_PATH);
    }
    catch (FileNotFoundException &ex) {
        std::cout << ex.what() << std::endl;
    }
    catch (EmptyFileException &ex) {
        std::cout << ex.what() << std::endl;
    }
    catch (NoRequestsFieldException &ex) {
        std::cout << ex.what() << std::endl;
    }
    catch (EmptyRequestsFieldException &ex) {
        std::cout << ex.what() << std::endl;
    }

    return doc;
}

void ConverterJSON::testFilesForValid() {
    testRequestsJson(REQUESTS_PATH);
    testConfigJson(CONFIG_PATH);
}


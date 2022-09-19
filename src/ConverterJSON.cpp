#include "ConverterJSON.h"

const std::string ConverterJSON::configPath = "./manage/config.json";

const std::string ConverterJSON::requestsPath = "./manage/requests.json";

const std::string ConverterJSON::answersPath = "./manage/answers.json";

// opens file and returns its data with string
// throws FileNotFoundException and EmptyFileException if path is invalid or file is empty
std::string ConverterJSON::getDoc(const std::string &path) const {
    std::ifstream file(path, std::ios::in);
    std::string answer, buff;

    if (!file.is_open()) throw FileNotFoundException();
    while (file) {
        std::getline(file, buff);
        answer.append(buff);
        if (!file.eof()) answer.append("\n");
        buff.clear();
    }
    if (answer.length() <= 1) throw EmptyFileException();
    for (auto &c: answer) c = (char) tolower(c);

    return answer;
}

bool ConverterJSON::testConfigJson(const std::string &path) const {
    nlohmann::json dict;
    try {
        dict = getJson(path);
        if (dict.empty()) throw EmptyFileException();
        if (!dict.contains("config")) throw NoConfigFieldException();
        if (dict.find("config").value().empty()) throw ConfigFieldIsEmptyException();
        if (dict.find("config")->find("version").value() != VERSION) throw IncorrectVersionJsonException();
        return true;
    }
    catch (EmptyFileException &ex) {
        std::cout << ex.what() << std::endl;
        return false;
    }
    catch (NoConfigFieldException &ex) {
        std::cout << ex.what() << std::endl;
        return false;
    }
    catch (ConfigFieldIsEmptyException &ex) {
        std::cout << ex.what() << std::endl;
        return false;
    }
    catch (IncorrectVersionJsonException &ex) {
        std::cout << ex.what() << std::endl;
        return false;
    }
}

bool ConverterJSON::testRequestsJson(const std::string &path) const {
    nlohmann::json dict;
    try {
        dict = getJson(path);
        if (!dict.contains("requests")) throw NoRequestsFieldException();
        if (dict.find("requests").value().empty()) throw EmptyRequestsFieldException();
        return true;
    }
    catch (NoRequestsFieldException &ex) {
        std::cout << ex.what() << std::endl;
        return false;
    }
    catch (EmptyRequestsFieldException &ex) {
        std::cout << ex.what() << std::endl;
        return false;
    }
}


// Returns vector with data in files which specified in config.json in field "files"
std::vector<std::string> ConverterJSON::GetTextDocuments() const {
    std::vector<std::string> list;
    nlohmann::json doc = getConfigJson();
    for (const auto &s: doc.find("files").value()) {
        try {
            list.push_back(getDoc((std::string) s));
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
int ConverterJSON::GetResponsesLimit() const {
    return getConfigJson().find("config")->find("max_responses").value();
}

//returns list of requests in requests.json
std::vector<std::string> ConverterJSON::GetRequests() const {
    std::vector<std::string> requests;
    nlohmann::json doc = getRequestsJson();
    for (const auto &val: doc.find("requests").value()) {
        std::string s = val;
        for (auto &c: s) c = (char) tolower(c);
        requests.push_back(s);
    }
    return requests;
}

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> &answers) const {
    std::ofstream file(answersPath, std::ios::out | std::ios::trunc);
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
nlohmann::json ConverterJSON::getJson(const std::string &path) const {
    std::ifstream file(path, std::ios::in);
    nlohmann::json doc;
    try {
        if (!file.is_open()) throw FileNotFoundException();
        file.seekg(0, std::ios::end);
        if (file.tellg() == 0) throw EmptyFileException();
        file.seekg(0, std::ios::beg);
        file >> doc;
    } catch (FileNotFoundException &ex) {
        std::cout << ex.what() << std::endl << "Cannot find file with path: \"" << path << "\"" << std::endl;
    } catch (EmptyFileException &ex) {
        std::cout << ex.what() << "File with path \"" << path << "\" exists, but it's empty." << std::endl;
    } catch (nlohmann::json::exception &ex) {
        std::cout << "Exception while reading json:\n" << ex.what() << "\nCheck the json file in \'" << path << "\'"
                  << std::endl;
        doc.clear();
    }
    file.close();

    return doc;
}

// basic checks. Returns json with data if file and path are valid, otherwise returns empty file
nlohmann::json ConverterJSON::getConfigJson() const {
    nlohmann::json doc;
    try {
        doc = getJson(configPath);
        if (!doc.contains("config")) throw NoConfigFieldException();
        if (doc.find("config").value().empty()) throw ConfigFieldIsEmptyException();
        if (doc.find("config")->find("version").value() != VERSION) throw IncorrectVersionJsonException();
    }
    catch (FileNotFoundException &ex) {
        std::cout << ex.what() << std::endl;
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
nlohmann::json ConverterJSON::getRequestsJson() const {
    nlohmann::json doc;
    try {
        doc = getJson(requestsPath);
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

void ConverterJSON::testFilesForValid() const {
    if (!(testRequestsJson(requestsPath) && testConfigJson(configPath)))
        throw ConfigFilesException();
    if (!isFileIsWritable(answersPath)) throw WriteToFileException();
}

bool ConverterJSON::isFileIsWritable(const std::string &path) const {
    char c;
    int i = 0;

    std::ifstream firstRead(path, std::ios::in);
    while (firstRead.get(c)) i++;
    firstRead.close();

    std::ofstream write(path, std::ios::app | std::ios::out);
    write << "Test";
    write.close();

    std::ifstream secondRead(path, std::ios::in);
    while (secondRead.get(c)) i--;
    secondRead.close();

    return i != 0;
}


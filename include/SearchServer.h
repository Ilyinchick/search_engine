#pragma once

#include "InvertredIndex.h"

struct RelativeIndex {
    int doc_id;
    float rank;

    bool operator==(const RelativeIndex &other) const {
        return (doc_id == other.doc_id && (other.rank == rank));
    }

};

class SearchServer {
public:
/**
* @param idx в конструктор класса передаётся ссылка на класс
InvertedIndex,
* чтобы SearchServer мог узнать частоту слов встречаемых в
запросе
*/
    SearchServer(InvertedIndex &idx) : _index(idx) {};

/**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла
requests.json
* @return возвращает отсортированный список релевантных ответов для
заданных запросов
*/
    std::vector<std::vector<RelativeIndex>> search(const
                                                   std::vector<std::string> &queries_input);


    void setResponseLimit(const int& limit);

private:
    InvertedIndex _index;
    int responseLimit;

    // sorting
    void bubbleSortByRelevance(std::vector<RelativeIndex> &vector);

    std::vector<std::string> getWordsFromString(const std::string &str);

    int countWordsInDoc(const std::string& word, const int &doc_id);

    std::vector<RelativeIndex> getRelativeVectorForQuery(const std::string &query);

};

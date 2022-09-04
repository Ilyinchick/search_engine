#include "../include/SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) {
    std::vector<std::vector<RelativeIndex>> answers;

    answers.reserve(queries_input.size());
    for (auto &query: queries_input) answers.push_back(getRelativeVectorForQuery(query));
    for (auto &vecs: answers) bubbleSortByRelevance(vecs);

    return answers;
}

std::vector<std::string> SearchServer::getWordsFromString(const std::string &str) {
    std::vector<std::string> words;

    std::string word;
    for (auto &c: str) {
        if ((c == ' ' || c == '\n') && word.length() != 0) {
            words.push_back(word);
            word.clear();
            continue;
        }
        word += (char) tolower(c);
    }
    if (word.length() != 0) words.push_back(word);

    return words;
}

std::vector<RelativeIndex> SearchServer::getRelativeVectorForQuery(const std::string &query) {
    std::vector<RelativeIndex> indexes;
    int absoluteRelevance[_index.getDocs().size()];
    float relevance[_index.getDocs().size()];
    for (auto& f: relevance) f = 0.0;
    for (auto& i: absoluteRelevance) i = 0;

    for (int i = 0; i < _index.getDocs().size(); i++) {
        for (const auto& word : getWordsFromString(query)) {
            absoluteRelevance[i] += countWordsInDoc(word, i);
        }
    }
    // find max relevance for this query
    int maxRelevance = absoluteRelevance[0];
    for (const auto& i: absoluteRelevance) if (i >= maxRelevance) maxRelevance = i;
    if (maxRelevance == 0) return indexes;

    for (int i = 0; i < _index.getDocs().size(); i++) {
        relevance[i] = (float)absoluteRelevance[i] / (float)maxRelevance;
        if (relevance[i] > 0) indexes.push_back(RelativeIndex{i, relevance[i]});
    }

    return indexes;
}

void SearchServer::bubbleSortByRelevance(std::vector<RelativeIndex> &vector) {
    if (vector.size() < 2) return;
    for (int i = 0; i < vector.size() - 1; i++) {
        for (int j = 0; j < vector.size() - 1; j++) {
            if (vector[j].rank < vector[j + 1].rank) {
                std::swap(vector[j], vector[j + 1]);
            } else if (vector[j].rank == vector[j + 1].rank) {
                if (vector[j].doc_id > vector[j + 1].doc_id) {
                    std::swap(vector[j], vector[j + 1]);
                }
            }
        }
    }
    while (vector.size() > responseLimit) {
        vector.pop_back();
    }
}

int SearchServer::countWordsInDoc(const std::string& word, const int &doc_id) {
    int count = 0;

    for (auto pair: _index.getDictionary()) {
        if (pair.first == word) {
            for (auto data: pair.second) {
                if (data.doc_id == doc_id) count = data.count;
            }
        }
    }

    return count;
}

void SearchServer::setResponseLimit(const int &limit) {
    responseLimit = limit;
}

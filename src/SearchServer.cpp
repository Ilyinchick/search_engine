#include "SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input) const {
    std::vector<std::vector<RelativeIndex>> answers;

    answers.reserve(queries_input.size());
    for (auto &query: queries_input) answers.push_back(getRelativeVectorForQuery(query));

    for (auto &vecs: answers) {
        std::sort(vecs.begin(), vecs.end(), [](RelativeIndex idx1, RelativeIndex idx2) {
            if (idx1.rank > idx2.rank) return true;
            if (idx1.rank < idx2.rank) return false;
            if (idx1.doc_id < idx2.doc_id) return true;
            return false;
        });
        while (vecs.size() > responseLimit) vecs.pop_back();
    }

    return answers;
}

std::vector<std::string> SearchServer::getWordsFromString(const std::string &str) const {
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

std::vector<RelativeIndex> SearchServer::getRelativeVectorForQuery(const std::string &query) const {
    std::vector<RelativeIndex> indexes;

    int absoluteRelevance[_index.getDocs().size()];
    float relevance[_index.getDocs().size()];
    for (int i = 0; i < _index.getDocs().size(); i++) {
        absoluteRelevance[i] = 0;
        relevance[i] = 0;
    }

    for (int i = 0; i < _index.getDocs().size(); i++) {
        for (const auto &word: getWordsFromString(query)) {
            absoluteRelevance[i] += countWordsInDoc(word, i);
        }
    }
    // find max relevance for this query
    int maxRelevance = absoluteRelevance[0];
    for (const auto &i: absoluteRelevance) if (i >= maxRelevance) maxRelevance = i;
    if (maxRelevance == 0) return indexes;

    for (int i = 0; i < _index.getDocs().size(); i++) {
        relevance[i] = (float) absoluteRelevance[i] / (float) maxRelevance;
        if (relevance[i] > 0) indexes.push_back(RelativeIndex{i, relevance[i]});
    }

    return indexes;
}

int SearchServer::countWordsInDoc(const std::string &word, int &doc_id) const {
    int count = 0;

    for (const auto &pair: _index.getDictionary()) {
        if (pair.first == word) {
            for (auto data: pair.second) {
                if (data.doc_id == doc_id) count = data.count;
            }
        }
    }

    return count;
}

void SearchServer::setResponseLimit(int &limit) {
    responseLimit = limit;
}

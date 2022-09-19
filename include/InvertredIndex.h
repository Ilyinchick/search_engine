#pragma once

#include <vector>
#include <string>
#include <map>
#include <set>
#include <thread>
#include <mutex>
#include <iostream>
#include <assert.h>

static std::mutex locker;
static std::set<std::string> wordsBase;

struct Entry {
    int doc_id, count;

    bool operator==(const Entry &other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};

class InvertedIndex {

public:
    InvertedIndex() = default;

    /**
    * Обновить или заполнить базу документов, по которой будем совершать поиск
    * @param texts_input содержимое документов
    */
    void UpdateDocumentBase(std::vector<std::string> docs);

    /*
     * Метод определяет количество вхождений слова word в загруженной базе документов
    * @param word слово, частоту вхождений которого необходимо определить
    * @return возвращает подготовленный список с частотой слов
     */
    std::vector<Entry> GetWordCount(const std::string &word) const;

    /*
     * simple getter
     * @return private 'freq_dictionary' field
     */
    const std::map<std::string, std::vector<Entry>> &getDictionary() const;

    /*
     * simple getter
     * @returns private 'docs' field
     */
    std::vector<std::string> getDocs() const;


    /*
     * @param str - text of document
     * split words from file and insert them into std::set wordBase to eliminate duplicates
     */
    static void getWordsFromFile(const std::string &str) {
        std::string word;
        for (auto &c: str) {
            if (c == ' ' || c == '\n') {
                locker.lock();
                wordsBase.insert(word);
                locker.unlock();
                word.clear();
                continue;
            }
            if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '-' || c == '+')
                word += (char) tolower(c);
        }
        if (word.length() != 0) {
            locker.lock();
            wordsBase.insert(word);
            locker.unlock();
        }
    }

    /*
     * @param data - vector of std::string that contains data from all documents
     * calls getWordsFromFile() in separate threads for each document in vector
     */
    static std::set<std::string> getWordsBaseFromDoc(const std::vector<std::string> &data) {
        std::vector<std::thread> threads;
        for (auto &str: data) {
            threads.push_back(std::thread(getWordsFromFile, std::ref(str)));
        }
        for (auto &thr: threads) {
            thr.join();
        }
        return wordsBase;
    }


private:

    int countWordsInStr(const std::string &word, const std::string &str) const;

    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный словарь
    std::vector<std::string> docs;

};
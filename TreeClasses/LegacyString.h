#pragma once
#include <string.h>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <cassert>
#include <assert.h>

using namespace std;
class LegacyString {
public:
    LegacyString() : str_(_strdup("")), length_(0) {}
    // Конструктор по умолчанию
    LegacyString(const char* str) : str_(_strdup(str)), length_(strlen(str)) {}
    // Конструктор по умолчанию
    LegacyString(size_t length) : str_(_strdup("")), length_(length) {}
    //Конструктор со string
    LegacyString(const string& str) : str_(_strdup(str.c_str())), length_(str.length()) {}

    // Конструктор копирования
    LegacyString(const LegacyString& other) : str_(_strdup(other.str_)), length_(other.length_) {}

    // Конструктор перемещения
    LegacyString(LegacyString&& other) noexcept : str_(other.str_), length_(other.length_) {
        other.str_ = nullptr;
        other.length_ = 0;
    }

    // Деструктор
    ~LegacyString() {
        delete[] str_;
    }

    // Оператор присваивания копированием
    LegacyString& operator=(const LegacyString& other) {
        if (this != &other) {
            delete[] str_;
            str_ = _strdup(other.str_);
            length_ = other.length_;
        }
        return *this;
    }
    LegacyString& operator=(const string& str) {
        delete[] str_;
        str_ = _strdup(str.c_str());
        length_ = str.length();
        return *this;
    }

    // Оператор присваивания перемещением
    LegacyString& operator=(LegacyString&& other) noexcept {
        if (this != &other) {
            delete[] str_;
            str_ = other.str_;
            length_ = other.length_;
            other.str_ = nullptr;
            other.length_ = 0;
        }
        return *this;
    }

    // Доступ к элементам строки по индексу
    char& operator[](size_t index) {
        if (index >= length_) {
            throw out_of_range("Index out of range");
        }
        return str_[index];
    }

    // Доступ к длине строки
    size_t length() const { return length_; }

    // Проверка на пустоту строки
    bool empty() const { return length_ == 0; }

    // Очистка строки
    void clear() {
        free(str_);
        str_ = nullptr;
        length_ = 0;
    }
    //Сравнения реализованы на сравнении каждого символа, то есть, в алфавитном порядке, не по длине
    /////////////////////////////////////////////////////>>>>>>>>>>>
    //Сравнение с LegacyString
    bool operator>(const LegacyString& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length_) {
            if (str_[i] > s.str_[i]) {
                return true;
            }
            else if (str_[i] < s.str_[i]) {
                return false;
            }
            i++;
        }
        return length_ > s.length_;
    }

    //Сравнение с char*
    bool operator>(char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] > s[i]) {
                return true;
            }
            else if (str_[i] < s[i]) {
                return false;
            }
            i++;
        }
        return length_ > strlen(s);
    }

    //Сравнение с char*
    bool operator>(const char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] > s[i]) {
                return true;
            }
            else if (str_[i] < s[i]) {
                return false;
            }
            i++;
        }
        return length_ > strlen(s);
    }

    //Friend-функция для сравнения с char* и LegacyString
    friend bool operator>(char* str, const LegacyString& s) {
        size_t i = 0;
        while (str[i] != '\0' && i < s.length_) {
            if (str[i] > s.str_[i]) {
                return true;
            }
            else if (str[i] < s.str_[i]) {
                return false;
            }
            i++;
        }
        return strlen(str) > s.length_;
    }

    //Friend-функция для сравнения с string и LegacyString
    friend bool operator>(const string& str, const LegacyString& s) {
        size_t i = 0;
        while (i < str.length() && i < s.length_) {
            if (str[i] > s.str_[i]) {
                return true;
            }
            else if (str[i] < s.str_[i]) {
                return false;
            }
            i++;
        }
        return str.length() > s.length_;
    }

    //Сравнение с string
    bool operator>(const string& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length()) {
            if (str_[i] > s[i]) {
                return true;
            }
            else if (str_[i] < s[i]) {
                return false;
            }
            i++;
        }
        return length_ > s.length();
    }
    /////////////////////////////////////////////////////<<<<<<<<<<
        //Сравнение с LegacyString
    bool operator<(const LegacyString& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length_) {
            if (str_[i] < s.str_[i]) {
                return true;
            }
            else if (str_[i] > s.str_[i]) {
                return false;
            }
            i++;
        }
        return length_ < s.length_;
    }

    //Сравнение с char*
    bool operator<(char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] < s[i]) {
                return true;
            }
            else if (str_[i] > s[i]) {
                return false;
            }
            i++;
        }
        return length_ < strlen(s);
    }

    bool operator<(const char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] < s[i]) {
                return true;
            }
            else if (str_[i] > s[i]) {
                return false;
            }
            i++;
        }
        return length_ < strlen(s);
    }

    //Friend-функция для сравнения с char* и LegacyString
    friend bool operator<(char* str, const LegacyString& s) {
        size_t i = 0;
        while (str[i] != '\0' && i < s.length_) {
            if (str[i] < s.str_[i]) {
                return true;
            }
            else if (str[i] > s.str_[i]) {
                return false;
            }
            i++;
        }
        return strlen(str) < s.length_;
    }

    //Friend-функция для сравнения с string и LegacyString
    friend bool operator<(const std::string& str, const LegacyString& s) {
        size_t i = 0;
        while (i < str.length() && i < s.length_) {
            if (str[i] < s.str_[i]) {
                return true;
            }
            else if (str[i] > s.str_[i]) {
                return false;
            }
            i++;
        }
        return str.length() < s.length_;
    }

    //Сравнение с string
    bool operator<(const std::string& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length()) {
            if (str_[i] < s[i]) {
                return true;
            }
            else if (str_[i] > s[i]) {
                return false;
            }
            i++;
        }
        return length_ < s.length();
    }
    ////////////////////////////////////////////////////////////=========================
    //Сравнение с LegacyString
    bool operator==(const LegacyString& s) const {
        if (length_ != s.length_) {
            return false;
        }
        for (size_t i = 0; i < length_; i++) {
            if (str_[i] != s.str_[i]) {
                return false;
            }
        }
        return true;
    }

    //Сравнение с char*
    bool operator==(char* s) const {
        size_t i = 0;
        while (str_[i] != '\0' && s[i] != '\0') {
            if (str_[i] != s[i]) {
                return false;
            }
            i++;
        }
        return str_[i] == '\0' && s[i] == '\0';
    }

    //Сравнение с char*
    bool operator==(const char* s) const {
        size_t i = 0;
        while (str_[i] != '\0' && s[i] != '\0') {
            if (str_[i] != s[i]) {
                return false;
            }
            i++;
        }
        return str_[i] == '\0' && s[i] == '\0';
    }

    //Friend-функция для сравнения с char* и LegacyString
    friend bool operator==(char* str, const LegacyString& s) {
        size_t i = 0;
        while (str[i] != '\0' && s.str_[i] != '\0') {
            if (str[i] != s.str_[i]) {
                return false;
            }
            i++;
        }
        return str[i] == '\0' && s.str_[i] == '\0';
    }

    //Friend-функция для сравнения с string и LegacyString
    friend bool operator==(const std::string& str, const LegacyString& s) {
        if (str.length() != s.length_) {
            return false;
        }
        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] != s.str_[i]) {
                return false;
            }
        }
        return true;
    }

    //Сравнение с string
    bool operator==(const std::string& s) const {
        if (length_ != s.length()) {
            return false;
        }
        for (size_t i = 0; i < length_; i++) {
            if (str_[i] != s[i]) {
                return false;
            }
        }
        return true;
    }
    //////////////////////////////////////////////////////////!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=!=
//Сравнение с LegacyString
    bool operator!=(const LegacyString& s) const {
        if (length_ != s.length_) {
            return true;
        }
        for (size_t i = 0; i < length_; i++) {
            if (str_[i] != s.str_[i]) {
                return true;
            }
        }
        return false;
    }

    //Сравнение с char*
    bool operator!=(char* s) const {
        size_t i = 0;
        while (str_[i] != '\0' && s[i] != '\0') {
            if (str_[i] != s[i]) {
                return true;
            }
            i++;
        }
        return !(str_[i] == '\0' && s[i] == '\0');
    }

    //Сравнение с char*
    bool operator!=(const char* s) const {
        size_t i = 0;
        while (str_[i] != '\0' && s[i] != '\0') {
            if (str_[i] != s[i]) {
                return true;
            }
            i++;
        }
        return !(str_[i] == '\0' && s[i] == '\0');
    }

    //Friend-функция для сравнения с char* и LegacyString
    friend bool operator!=(char* str, const LegacyString& s) {
        size_t i = 0;
        while (str[i] != '\0' && s.str_[i] != '\0') {
            if (str[i] != s.str_[i]) {
                return true;
            }
            i++;
        }
        return !(str[i] == '\0' && s.str_[i] == '\0');
    }

    //Friend-функция для сравнения с string и LegacyString
    friend bool operator!=(const std::string& str, const LegacyString& s) {
        if (str.length() != s.length_) {
            return true;
        }
        for (size_t i = 0; i < str.length(); i++) {
            if (str[i] != s.str_[i]) {
                return true;
            }
        }
        return false;
    }

    //Сравнение с string
    bool operator!=(const std::string& s) const {
        if (length_ != s.length()) {
            return true;
        }
        for (size_t i = 0; i < length_; i++) {
            if (str_[i] != s[i]) {
                return true;
            }
        }
        return false;
    }

/////////////////////////////////////////////////////<=<=<=<=<=<=<=<=<=<
//Сравнение с LegacyString
    bool operator<=(const LegacyString& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length_) {
            if (str_[i] < s.str_[i]) {
                return true;
            }
            else if (str_[i] > s.str_[i]) {
                return false;
            }
            i++;
        }
        return length_ <= s.length_;
    }

    //Сравнение с char*
    bool operator<=(char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] < s[i]) {
                return true;
            }
            else if (str_[i] > s[i]) {
                return false;
            }
            i++;
        }
        return length_ <= strlen(s);
    }

    //Сравнение с char*
    bool operator<=(const char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] < s[i]) {
                return true;
            }
            else if (str_[i] > s[i]) {
                return false;
            }
            i++;
        }
        return length_ <= strlen(s);
    }

    //Friend-функция для сравнения с char* и LegacyString
    friend bool operator<=(char* str, const LegacyString& s) {
        size_t i = 0;
        while (str[i] != '\0' && i < s.length_) {
            if (str[i] < s.str_[i]) {
                return true;
            }
            else if (str[i] > s.str_[i]) {
                return false;
            }
            i++;
        }
        return strlen(str) <= s.length_;
    }

    //Friend-функция для сравнения с string и LegacyString
    friend bool operator<=(const std::string& str, const LegacyString& s) {
        size_t i = 0;
        while (i < str.length() && i < s.length_) {
            if (str[i] < s.str_[i]) {
                return true;
            }
            else if (str[i] > s.str_[i]) {
                return false;
            }
            i++;
        }
        return str.length() <= s.length_;
    }

    //Сравнение с string
    bool operator<=(const std::string& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length()) {
            if (str_[i] < s[i]) {
                return true;
            }
            else if (str_[i] > s[i]) {
                return false;
            }
            i++;
        }
        return length_ <= s.length();
    }

    ///////////////////////////////////////////////>=>=>=>=>=>=>=>=>=>=
//Сравнение с LegacyString
    bool operator>=(const LegacyString& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length_) {
            if (str_[i] > s.str_[i]) {
                return true;
            }
            else if (str_[i] < s.str_[i]) {
                return false;
            }
            i++;
        }
        return length_ >= s.length_;
    }

    //Сравнение с char*
    bool operator>=(char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] > s[i]) {
                return true;
            }
            else if (str_[i] < s[i]) {
                return false;
            }
            i++;
        }
        return length_ >= strlen(s);
    }

    //Сравнение с char*
    bool operator>=(const char* s) const {
        size_t i = 0;
        while (i < length_ && s[i] != '\0') {
            if (str_[i] > s[i]) {
                return true;
            }
            else if (str_[i] < s[i]) {
                return false;
            }
            i++;
        }
        return length_ >= strlen(s);
    }

    //Friend-функция для сравнения с char* и LegacyString
    friend bool operator>=(char* str, const LegacyString& s) {
        size_t i = 0;
        while (str[i] != '\0' && i < s.length_) {
            if (str[i] > s.str_[i]) {
                return true;
            }
            else if (str[i] < s.str_[i]) {
                return false;
            }
            i++;
        }
        return strlen(str) >= s.length_;
    }

    //Friend-функция для сравнения с string и LegacyString
    friend bool operator>=(const std::string& str, const LegacyString& s) {
        size_t i = 0;
        while (i < str.length() && i < s.length_) {
            if (str[i] > s.str_[i]) {
                return true;
            }
            else if (str[i] < s.str_[i]) {
                return false;
            }
            i++;
        }
        return str.length() >= s.length_;
    }

    //Сравнение с string
    bool operator>=(const std::string& s) const {
        size_t i = 0;
        while (i < length_ && i < s.length()) {
            if (str_[i] > s[i]) {
                return true;
            }
            else if (str_[i] < s[i]) {
                return false;
            }
            i++;
        }
        return length_ >= s.length();
    }
/// <summary>
/// /////////////////////////////////////////////////////////////////+++++++++++++++++++++++
///// </summary>
  //Конкатенация с LegacyString
    LegacyString operator+(const LegacyString& s) const {
        LegacyString result;
        result.length_ = length_ + s.length_;
        result.str_ = new char[result.length_ + 1];
        copy_n(str_, length_, result.str_);
        copy_n(s.str_, s.length_, result.str_ + length_);
        result.str_[result.length_] = '\0';
        return result;
    }

    //Конкатенация с char*
    LegacyString operator+(char* s) const {
        LegacyString result;
        result.length_ = length_ + strlen(s);
        result.str_ = new char[result.length_ + 1];
        copy_n(str_, length_, result.str_);
        copy_n(s, strlen(s), result.str_ + length_);
        result.str_[result.length_] = '\0';
        return result;
    }

    //Friend-функция конкатенации char* и  LegacyString
    friend LegacyString operator+(char* str, const LegacyString& s) {
        LegacyString result;
        result.length_ = strlen(str) + s.length_;
        result.str_ = new char[result.length_ + 1];
        copy_n(str, strlen(str), result.str_);
        copy_n(s.str_, s.length_, result.str_ + strlen(str));
        result.str_[result.length_] = '\0';
        return result;
    }

    //Friend-функция конкатенации string и  LegacyString
    friend LegacyString operator+(const std::string& str, const LegacyString& s) {
        LegacyString result;
        result.length_ = str.length() + s.length_;
        result.str_ = new char[result.length_ + 1];
        copy_n(str.c_str(), str.length(), result.str_);
        copy_n(s.str_, s.length_, result.str_ + str.length());
        result.str_[result.length_] = '\0';
        return result;
    }

    //Конкатенация с string
    LegacyString operator+(const std::string& s) const {
        LegacyString result;
        result.length_ = length_ + s.length();
        result.str_ = new char[result.length_ + 1];
        copy_n(str_, length_, result.str_);
        copy_n(s.c_str(), s.length(), result.str_ + length_);
        result.str_[result.length_] = '\0';
        return result;
    }
    ////////////////////////////////////////////
      // Функция поиска последнего вхождения символа. Возвращает длину строки +1, если не найден символ
    size_t seek_last(char ch) const {
        for (size_t i = length_ - 1; i >= 1; i--) {
            if (str_[i] == ch) {
                return i;
            }
        }
        return length_ + 1;
    }
    // Функция вставки строки в позицию
    void insert(size_t pos, const char* str) {
        size_t str_len = strlen(str);
        size_t new_length = length_ + str_len;

        char* new_str = new char[new_length + 1];
        copy_n(str_, pos, new_str);
        copy_n(str, str_len, new_str + pos);
        copy_n(str_ + pos, length_ - pos, new_str + pos + str_len);
        new_str[new_length] = '\0';

        delete[] str_;
        str_ = new_str;
        length_ = new_length;
    }

    // Функция вставки строки в позицию (LegacyString)
    void insert(size_t pos, const LegacyString& str) {
        insert(pos, str.str_);
    }

    // Функция вставки строки в позицию (std::string)
    void insert(size_t pos, const std::string& str) {
        insert(pos, str.c_str());
    }
    // Функция удаления count символов по индексу
    void erase(size_t index, size_t count) {
        if (index >= length_ || count == 0) {
            return;
        }

        size_t new_length = length_ - count;
        char* new_str = new char[new_length + 1];

        copy_n(str_, index, new_str);
        copy_n(str_ + index + count, new_length - index, new_str + index);
        new_str[new_length] = '\0';

        delete[] str_;
        str_ = new_str;
        length_ = new_length;
    }

    // Оператор преобразования в char*
    operator char* () const {
        return str_;
    }
//
    // Оператор преобразования в std::string
    operator std::string() const {
        return std::string(str_);
    }

    // Алгоритм поиска подстроки КМП. Если не найдет, возвращает длину + 1
    size_t kmp_search(const LegacyString& pattern) const {
        // Создание таблицы префиксов
        size_t* prefix_table = build_prefix_table(pattern);

        // Инициализация индексов
        size_t i = 0; // Индекс текста
        size_t j = 0; // Индекс образца

        // Поиск образца в тексте
        while (i < length_ && j < pattern.length_) {
            if (str_[i] == pattern.str_[j]) {
                i++;
                j++;
            }
            else {
                // Если символы не совпадают, сдвигаем индекс образца
                // на основе таблицы префиксов
                if (j > 0) {
                    j = prefix_table[j - 1];
                }
                else {
                    i++;
                }
            }
        }

        // Освобождение памяти
        delete[] prefix_table;

        // Возврат индекса начала образца, если он найден
        if (j == pattern.length_) {
            return i - j;
        }
        else {
            return length_+1;
        }
    }
    // Последовательный поиск подстроки с проверкой первого и последнего элемента. Если не найдет, возвращает длину + 1
    size_t search(const LegacyString& pattern) const {
        size_t text_len = length_;
        size_t pattern_len = pattern.length_;

        // Итерация по тексту
        for (size_t i = 0; i <= text_len - pattern_len; i++) {
            // Проверка первого элемента
            if (str_[i] != pattern.str_[0]) {
                continue;
            }

            // Проверка последнего элемента
            if (str_[i + pattern_len - 1] != pattern.str_[pattern_len - 1]) {
                continue;
            }

            // Полная проверка образца
            size_t j = 0;
            while (j < pattern_len && str_[i + j] == pattern.str_[j]) {
                j++;
            }

            // Проверка, найден ли образец
            if (j == pattern_len) {
                return i;
            }
        }

        // Образец не найден
        return length_ + 1;
    }

    // Процедура, которая генерирует строку случайных символов заданной последовательности
    static LegacyString generate_random_string(size_t length, const std::string& charset) {
        LegacyString random_string(length);
        for (size_t i = 0; i < length; i++) {
            random_string.str_[i] = charset[rand() % charset.length()];
        }

        return random_string;
    }

    // Процедура, которая читает строки из текстового файла
    static vector<LegacyString> read_lines_from_file(const string& filename) {
        ifstream file(filename);
        vector<LegacyString> lines;

        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                lines.push_back(LegacyString(line));
            }
            file.close();
        }
        else {
            cerr << "Error opening file: " << filename << endl;
        }

        return lines;
    }

    static void test() {
        LegacyString emptyString;
        assert(emptyString.length() == 0);
        assert(emptyString == "");


        LegacyString str(10);
        assert(str.length() == 10);
        assert(str == "");


        LegacyString str1("Hello, world!");
        assert(str1.length() == 13);
        assert(str1 == "Hello, world!");


        std::string stdStr = "Hello, world!";
        LegacyString str2(stdStr);
        assert(str2.length() == 13);
        assert(str2 == "Hello, world!");


        LegacyString str3(str1);
        assert(str3.length() == str1.length());
        assert(str1 == str3);
        str3 = "Goodbye, world";
        assert(str3 != str1);


        LegacyString str4(std::move(str1));
        assert(str4.length() == 13);
        assert(str4 == "Hello, world!");
        assert(str1.length() == 0);
        assert(str1.str_ == nullptr);


        LegacyString* str5 = new LegacyString("Hello, world!");
        delete str5;


        LegacyString str6;
        str6 = "Hello, world!";
        assert(str6.length() == 13);
        assert(strcmp(str6.str_, "Hello, world!") == 0);


        LegacyString str7;
        stdStr = "Hello, world!";
        str7 = stdStr;
        assert(str7.length() == 13u);
        assert(strcmp(str7.str_, "Hello, world!") == 0);


        LegacyString str8("Hello, world!");
        LegacyString str9;
        str9 = std::move(str8);
        assert(str9.length() == 13u);
        assert(strcmp(str9.str_, "Hello, world!") == 0);
        assert(str8.length() == 0u);
        assert(str8.str_ == nullptr);


        LegacyString str10("Hello, world!");
        assert(str10[0] == 'H');
        assert(str10[6] == ' ');
        assert(str10[12] == '!');


        try {
            str10[13];
            assert(false); // Should throw an exception
        }
        catch (const std::out_of_range& e) {
            // Expected exception
        }


        LegacyString str11("Hello, world!");
        assert(str11.length() == 13u);


        LegacyString emptyString2;
        assert(emptyString2.empty());
        LegacyString str12("Hello, world!");
        assert(!str12.empty());


        LegacyString str13("Hello, world!");
        str13.clear();
        assert(str13.length() == 0u);
        assert(str13.str_ == nullptr);


        LegacyString str14("Hello, world!");
        LegacyString str15("Hello, world!");
        LegacyString str16("Hello, world!1");
        assert(!(str14 > "Hello, world!"));
        assert(!(str14 > "Hello, world!1"));
        assert(str16 > "Hello, world!");


        LegacyString str17("Hello, world!");
        LegacyString str18("Hello, world!");
        LegacyString str19("Hello, world!1");
        assert(!(str17 > "Hello, world!"));
        assert(!(str17 > "Hello, world!1"));
        assert(str19 > "Hello, world!");


        LegacyString str20("Hello, world!");
        LegacyString str21("Hello, world!");
        LegacyString str22("Hello, world!1");
        assert(!(str20 > str21));
        assert(!(str20 > str22));
        assert(str22 > str21);


        LegacyString str23("Hello, world!");
        LegacyString str24("Hello, world!");
        LegacyString str25("Hello, world!1");
        assert(!(str23 < "Hello, world!"));
        assert(str23 < "Hello, world!1");
        assert(!(str25 < "Hello, world!"));


        LegacyString str26("Hello, world!");
        LegacyString str27("Hello, world!");
        LegacyString str28("Hello, world!1");
        assert(!(str26 < "Hello, world!"));
        assert(str26 < "Hello, world!1");
        assert(!(str28 < "Hello, world!"));

        LegacyString str29("Hello, world!");
        LegacyString str30("Hello, world!");
        LegacyString str31("Hello, world!1");
        assert(!(str29 < str30));
        assert(str29 < str31);
        assert(!(str31 < str30));


        LegacyString str32("Hello, world!");
        LegacyString str33("Hello, world!");
        LegacyString str34("Hello, world!1");
        assert(str32 >= "Hello, world!");
        assert(!(str32 >= "Hello, world!1"));
        assert(str34 >= "Hello, world!");


        LegacyString str35("Hello, world!");
        LegacyString str36("Hello, world!");
        LegacyString str37("Hello, world!1");
        assert(str35 >= "Hello, world!");
        assert(!(str35 >= "Hello, world!1"));
        assert(str37 >= "Hello, world!");


        LegacyString str38("Hello, world!");
        LegacyString str39("Hello, world!");
        LegacyString str40("Hello, world!1");
        assert(str38 >= str39);
        assert(!(str38 >= str40));
        assert(str40 >= str39);


        LegacyString str41("Hello, world!");
        LegacyString str42("Hello, world!");
        LegacyString str43("Hello, world!1");
        assert(str41 <= "Hello, world!");
        assert(str41 <= "Hello, world!1");
        assert(!(str43 <= "Hello, world!"));


        LegacyString str44("Hello, world!");
        LegacyString str45("Hello, world!");
        LegacyString str46("Hello, world!1");
        assert(str44 <= "Hello, world!");
        assert(str44 <= "Hello, world!1");
        assert(!(str46 <= "Hello, world!"));


        LegacyString str47("Hello, world!");
        LegacyString str48("Hello, world!");
        LegacyString str49("Hello, world!1");
        assert(str47 <= str48);
        assert(str47 <= str49);
        assert(!(str49 <= str48));


        LegacyString str50("Hello, world!");
        assert(str50 == "Hello, world!");
        assert(str50 != "Hello, world!1");


        LegacyString str51("Hello, world!");
        stdStr = "Hello, world!";
        assert(str51 == stdStr);
        stdStr = "Hello, world!1";
        assert(str51 != stdStr);


        LegacyString str52("Hello, world!");
        LegacyString str53("Hello, world!");
        LegacyString str54("Hello, world!1");

        assert(str52 != str54);

 
        LegacyString str55("Hello, world!");
        assert(str55 == "Hello, world!");
        assert(str55 != "Hello, world!1");


        LegacyString str56("Hello, world!");
        stdStr = "Hello, world!";
        assert(str56 == stdStr);
        stdStr = "Hello, world!1";
        assert(str56 != stdStr);


        LegacyString str57("Hello, world!");
        LegacyString str58("Hello, world!");
        LegacyString str59("Hello, world!1");
        assert(str57 == str58);
        assert(str57 != str59);
    }

private:
    // Массив
    char* str_;

    // Длина строки
    size_t length_;
    // Функция построения таблицы префиксов
    size_t* build_prefix_table(const LegacyString& pattern) const {
        size_t* prefix_table = new size_t[pattern.length_];

        // Инициализация первого элемента таблицы
        prefix_table[0] = 0;

        // Инициализация индексов
        size_t i = 1;
        size_t j = 0;

        // Построение таблицы префиксов
        while (i < pattern.length_) {
            if (pattern.str_[i] == pattern.str_[j]) {
                prefix_table[i] = j + 1;
                i++;
                j++;
            }
            else {
                if (j > 0) {
                    j = prefix_table[j - 1];
                }
                else {
                    prefix_table[i] = 0;
                    i++;
                }
            }
        }

        return prefix_table;
    }
};


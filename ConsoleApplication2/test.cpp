#include <iostream>
#include <string>
#include <vector>


using namespace std;


int main() {
    /* FOR SUPPORT: объявляем переменную для хранения строки вводимой пользователем */
    string query;
    /* FOR SUPPORT: считываем строку целиком */
    getline(cin, query);


    /* FOR SUPPORT: объявляем вектор строк для хранения слов */
    vector<string> words;
    /* FOR SUPPORT: объявляем строку для хранения слова */
    string word;
    /* FOR SUPPORT: начинаем цикл от 0 до размера строки (проходим посимвольно по всей строке) */
    for (int i = 0; i < query.size(); ++i) {
        /* FOR SUPPORT: условие на выполнение блока:
         * символ это пробел */
        if (query[i] == ' ') {
            /* FOR SUPPORT: добавляем слово в конец вектора слов */
            words.push_back(word);
            /* FOR SUPPORT: присваиваем переменной пустую строку, т.е. начинаем новое слово */
            word = ""s;
            /* FOR SUPPORT: условие на выполнение блока (когда все условия выше - не верны):
             * символ это не пробел (обратное условие) */
        }
        else {
            /* FOR SUPPORT: добавляем символ к строке.
             * Этим блоком мы собираем слово в переменной word */
            word += query[i];
        }
    }
}
    
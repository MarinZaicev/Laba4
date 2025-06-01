#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

using namespace std;

void operator << (ostream& os, vector<int>& veco) {
    for (auto n : veco) {
        cout << n << " ";
    }
    cout << endl;
}
// Функция для перемешивания цифр числа
int shuffle_digits(int num) {
    string s = to_string(num);

    // Если число однозначное - возвращаем как есть
    if (s.length() == 1) return num;

    static random_device rd;
    static ranlux24_base gen(rd());

    // Перемешиваем цифры, избегая ведущих нулей
    string shuffled = s;
    do {
        shuffle(shuffled.begin(), shuffled.end(), gen);
    } 
    while (shuffled[0] == '0');

    return stoi(shuffled);
}

int main() {
    setlocale(LC_ALL, "Russian");
    random_device rd;
    ranlux24_base engine(rd());
    uniform_int_distribution<int> dist(100, 901);
    int n;
    cin >> n;

    vector<int> original_array(n);
    for (auto& n : original_array) {
        n = dist(engine);
    }

    cout << "Исходный массив: ";
    cout << original_array;

    // 1. Сортируем исходный массив по возрастанию
    sort(original_array.begin(), original_array.end());

    cout << "Отсортированный исходный массив: ";
    cout << original_array;

    // 2. Создаем новый массив с перемешанными числами
    vector<int> shuffled_array;
    for (int num : original_array) {
        shuffled_array.push_back(shuffle_digits(num));
    }

    cout << "Массив с перемешанными числами: ";
    cout << shuffled_array;

    return 0;
}

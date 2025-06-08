#include <iostream>
#include <vector>

using namespace std;

// Функция генерации последовательности Фибоначчи с запаздыванием
vector<int> generateLaggedFibonacci(int j, int k, const vector<int>& initial, int m, int count, char op) {
    vector<int> sequence = initial;
    int n = initial.size();
    for (int i = n; i < count + n; i++) {
        int next_val;
        switch (op) {
        case '+': // Сложение
            next_val = (sequence[i - j] + sequence[i - k]) % m;
            break;
        case '-': // Вычитание
            next_val = (sequence[i - j] - sequence[i - k]) % m;
            break;
        case '*': // Умножение
            next_val = (sequence[i - j] * sequence[i - k]) % m;
            break;
        case '^': // XOR
            next_val = (sequence[i - j] ^ sequence[i - k]) % m;
            break;
        default:
            cerr << "Неизвестная операция. Используются (+, *, xor)." << endl;
            next_val = (sequence[i - j] + sequence[i - k]) % m;
        }
        sequence.push_back(next_val);
    }
    for (int i = 0; i < n; i++) {
        sequence.erase(sequence.begin());
    }
    
    return sequence;
}
void bags(int bag) {
    if (bag < 0) {
        cout << "число должно не должно быть отрицательным";
        exit(0);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Параметры генератора
    cout << "Введите параметр j: ";
    int j;
    cin >> j;// Параметр j (запаздывание)
    bags(j);
    cout << endl;
    cout << "Введите параметр k: ";
    int k;
    cin >> k;// Параметр k (запаздывание)
    bags(k);
    if (k > j) {
        cout << "k не должно быть больше j";
        exit(0);
    }
    cout << endl;
    cout << "Введите кол-во чисел S: ";
    int n;
    cin >> n;
    bags(n);
    cout << endl;
    vector<int> initial(n);
    for (int i = 0; i < initial.size(); i++) {// Начальные значения S0, S1
        cout << "Введите число S" << i << ": ";
        int S;
        cin >> S;
        bags(S);
        initial[i] = S;
        cout << endl;
    }
    cout << "Введите параметр m: ";
    int m;
    cin >> m;// Модуль (обычно степень 2)
    bags(m);
    cout << endl;
    cout << "Введите кол-во генерируемых чисел: ";
    int count;
    cin >> count;    // Сколько чисел генерировать
    bags(count);
    cout << endl;
    cout << "Введите операцию (+, -, *, xor): ";
    char op;
    cin >> op;    // Операция: +, -, *, ^ (XOR)
    cout << endl;

    // Генерация последовательности
    vector<int> sequence = generateLaggedFibonacci(j, k, initial, m, count, op);

    // Вывод результата
    cout << "Сгенерированная последовательность: ";
    for (int num : sequence) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

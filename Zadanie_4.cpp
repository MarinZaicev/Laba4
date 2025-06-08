#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

string bordaWinner(const vector<vector<string>>& votes, const vector<string>& candidates) {
    map<string, int> scores;

    // Инициализация счетчиков
    for (const string& candidate : candidates) {
        scores[candidate] = 0;
    }

    // Начисление баллов
    for (const vector<string>& vote : votes) {
        for (size_t i = 0; i < vote.size(); ++i) {
            scores[vote[i]] += (vote.size() - 1 - i);
        }
    }

    // Поиск победителя
    string winner;
    int max_score = -1;
    for (const auto& entry : scores) {
        if (entry.second > max_score) {
            max_score = entry.second;
            winner = entry.first;
        }
    }

    return winner;
}

string condorcetWinner(const vector<vector<string>>& votes, const vector<string>& candidates) {
    map<string, map<string, int>> pairwise;

    // Инициализация матрицы
    for (const string& c1 : candidates) {
        for (const string& c2 : candidates) {
            if (c1 != c2) {
                pairwise[c1][c2] = 0;
            }
        }
    }

    // Заполнение матрицы
    for (const vector<string>& vote : votes) {
        for (size_t i = 0; i < vote.size(); ++i) {
            for (size_t j = i + 1; j < vote.size(); ++j) {
                string preferred = vote[i];
                string less_preferred = vote[j];
                pairwise[preferred][less_preferred]++;
            }
        }
    }

    // Поиск победителя Кондорсе
    for (const string& candidate : candidates) {
        bool is_condorcet_winner = true;

        for (const string& opponent : candidates) {
            if (candidate != opponent) {
                if (pairwise[candidate][opponent] <= pairwise[opponent][candidate]) {
                    is_condorcet_winner = false;
                    break;
                }
            }
        }

        if (is_condorcet_winner) {
            return candidate;
        }
    }

    return "Нет победителя по Кондорсе";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int n, k;
    cout << "Введите количество кандидатов: ";
    cin >> n;
    cout << "Введите количество избирателей: ";
    cin >> k;

    vector<string> candidates(n);
    cout << "Введите имена кандидатов (через пробел): ";
    for (int i = 0; i < n; ++i) {
        cin >> candidates[i];
    }

    vector<vector<string>> votes(k, vector<string>(n));
    cout << "Введите предпочтения избирателей:\n";
    for (int i = 0; i < k; ++i) {
        cout << "Избиратель " << i + 1 << ": ";
        for (int j = 0; j < n; ++j) {
            cin >> votes[i][j];
        }
    }

    string borda = bordaWinner(votes, candidates);
    string condorcet = condorcetWinner(votes, candidates);

    cout << "\nРезультаты:\n";
    cout << "Метод Борда: " << borda << endl;
    cout << "Метод Кондорсе: " << condorcet << endl;

    if (borda != condorcet && condorcet != "Нет победителя по Кондорсе") {
        cout << "Примечание: разные методы дали разных победителей.\n";
    }

    return 0;
}

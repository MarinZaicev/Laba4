#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// Функция для генерации псевдослучайных чисел методом Фибоначчи с запаздыванием
vector<unsigned int> generateLaggedFibonacci(
    size_t j, size_t k,
    const vector<unsigned int>& seed,
    size_t count,
    unsigned int m = 1 << 31,
    char operation = '+')
{
    if (j >= k || k >= seed.size()) {
        throw invalid_argument("Invalid j/k parameters or seed size");
    }

    vector<unsigned int> state = seed;
    vector<unsigned int> result;
    size_t current = 0;

    for (size_t i = 0; i < count; ++i) {
        size_t index_j = (current - j + state.size()) % state.size();
        size_t index_k = (current - k + state.size()) % state.size();

        unsigned int next_val;
        switch (operation) {
        case '+':
            next_val = (state[index_j] + state[index_k]) % m;
            break;
        case '-':
            next_val = (state[index_j] - state[index_k]) % m;
            break;
        case '*':
            next_val = (state[index_j] * state[index_k]) % m;
            break;
        case '^': // XOR
            next_val = (state[index_j] ^ state[index_k]) % m;
            break;
        default:
            throw runtime_error("Unknown operation");
        }

        state[current] = next_val;
        current = (current + 1) % state.size();
        result.push_back(next_val);
    }

    return result;
}

int main() {
    try {
        // Параметры из примера
        size_t j = 2;
        size_t k = 1;
        vector<unsigned int> seed = { 1, 4 };
        unsigned int m = 16;
        char op = '+'; // Аддитивный метод
        size_t count = 6;

        auto sequence = generateLaggedFibonacci(j, k, seed, count, m, op);

        cout << "Generated sequence: ";
        for (auto num : sequence) {
            cout << num << " ";
        }
        cout << endl;

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

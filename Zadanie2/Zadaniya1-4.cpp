#include <iostream>
#include <random>
#include <vector>
#include <sstream>
#include <set>
using namespace std;


void operator << (ostream& os, vector<int>& veco) {
	for (auto n : veco) {
		cout << n << " ";
	}
}

void operator << (ostream& os, vector<char>& veco) {
	for (auto n : veco) {
		cout << n << " ";
	}
}


vector<int> createContainer(int n) {
	random_device rd;
	// Создаём генератор ranlux24_base
	ranlux24_base engine(rd());

	// Создаём распределение (например, от 0 до 99)
	uniform_int_distribution<int> dist(1, 99);
	vector <int> papa(n);
	for (auto& n : papa) {
		n = dist(engine);
	}
	return papa;
}

void summa(vector<int> arr1) {

	int sum = 0;
	int minimum = 101;
	int maximum = 0;
	int indexMax;
	int indexMin;
	int index = 0;
	for (auto n : arr1) { // ищем максимальный и минимальный элементы
		if (n < minimum) {
			minimum = n;
		}
		if (n > maximum) {
			maximum = n;
		}
	}
	for (auto n : arr1) { // ищем индексы элементов
		if(n == maximum) {
			indexMax = index;
		}
		if (n == minimum) {
			indexMin = index;
		}
		index++;
	}

	int start = min(indexMin, indexMax); 
	int end = max(indexMin, indexMax);

	index = 0;

	for (auto n : arr1) {
		if (index > start && index < end) {
			sum += n;
		}
		index++;
	}

	cout << sum << endl;
}

vector<int> createNewContainer(vector<int> arr1) {
	random_device rd;
	// Создаём генератор ranlux24_base
	ranlux24_base engine(rd());

	// Создаём распределение (например, от 0 до 99)
	uniform_int_distribution<int> dist(0, arr1.size()-1);
	int minimum = 101;
	int maximum = 0;
	int indexMax;
	int indexMin;
	int index = 0;
	for (auto n : arr1) { // ищем максимальный и минимальный элементы
		if (n < minimum) {
			minimum = n;
		}
		if (n > maximum) {
			maximum = n;
		}
	}
	for (auto n : arr1) { // ищем индексы элементов
		if (n == maximum) {
			indexMax = index;
		}
		if (n == minimum) {
			indexMin = index;
		}
		index++;
	}

	int start = min(indexMin, indexMax);
	int end = max(indexMin, indexMax); // до этого момента всё копипаст с прошлой функции.
	
	vector<int> arr2;
	index = 0;

	for (auto& n : arr1) {
		if (index > start && index < end) {
			arr2.push_back(n);
		}
		else {
			arr2.push_back(arr1[dist(engine)]);
		}
		index++;
	}
	return arr2;
}

pair<vector<char>, vector<char>> sorti(int length) {
	// Инициализация генератора
	static random_device rd;
	static ranlux24_base engine(rd());
	uniform_int_distribution<int> dist('a', 'z');

	// Создание и заполнение исходного массива
	vector<char> original(length);
	for (char& c : original) {
		c = static_cast<char>(dist(engine));
	}

	// Создаем копию для сортировки
	vector<char> sorted = original;

	// Собираем пары (индекс, значение) для чётных позиций
	vector<pair<int, char>> even_elements;
	int index = 0;
	for (char c : sorted) {
		if (index % 2 == 0) {
			even_elements.emplace_back(index, c);
		}
		index++;
	}

	// Сортируем по значению символа
	sort(even_elements.begin(), even_elements.end(),
		[](const pair<int, char>& a, const pair<int, char>& b) {
			return a.second < b.second;
		});

	// Записываем отсортированные значения обратно
	index = 0;
	int even_index = 0;
	for (char& c : sorted) {
		if (index % 2 == 0) {
			c = even_elements[even_index++].second;
		}
		index++;
	}

	return { original, sorted };
}

int main() {
	int n;
	cin >> n;
	auto arr1 = createContainer(n);
	cout << arr1;
	cout << endl;
	summa(arr1);
	auto arr2 = createNewContainer(arr1);
	cout << arr2;
	cout << endl;
	pair<vector<char>, vector<char>> origSorted;
	origSorted = sorti(n);
	cout << origSorted.first;
	cout << endl;
	cout << origSorted.second;
}

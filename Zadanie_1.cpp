#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const float epsilon = 0.0001;

double f(double x) {
    return x * log(x + 1) - 1;
}

void printTableHeader() {
    cout << "+-------+---------------+---------------+---------------+" << endl;
    cout << "|" << setw(7) << "N" << "|" << setw(15) << "a_n" << "|"
        << setw(15) << "b_n" << "|" << setw(15) << "b_n - a_n" << "|" << endl;
    cout << "+-------+---------------+---------------+---------------+" << endl;
}

void printTableRow(int n, double a, double b) {
    cout << "|" << setw(7) << n << "|" << setw(15) << setprecision(6) << fixed << a << "|"
        << setw(15) << b << "|" << setw(15) << (b - a) << "|" << endl;
}

void halfDel(double a, double b, double epsilon) {
    setlocale(LC_ALL, "Russian");
    if (f(a) * f(b) >= 0) {
        cout << "На интервале нет корня или несколько корней" << endl;
        return;
    }

    cout << "МЕТОД ПОЛОВИННОГО ДЕЛЕНИЯ" << endl;
    cout << "Исходный интервал: [" << a << ", " << b << "]" << endl;
    printTableHeader();

    double c;
    int n = 0;
    while ((b - a) >= epsilon) {
        c = (a + b) / 2;
        printTableRow(n, a, b);

        if (fabs(f(c)) < epsilon)
            break;
        else if (f(c) * f(a) < 0)
            b = c;
        else
            a = c;

        n++;
    }
    cout << "+-------+---------------+---------------+---------------+" << endl;
    cout << "Итоговый корень: " << setprecision(10) << c << endl;
    cout << "Значение функции: " << f(c) << endl;
    cout << "Количество итераций: " << n << endl << endl;
}

double df(double x) {
    return log(x + 1) + x / (x + 1);
}

void printNewtonHeader() {
    cout << "+-------+---------------+---------------+---------------+" << endl;
    cout << "|" << setw(7) << "N" << "|" << setw(15) << "x_n" << "|"
        << setw(15) << "x_{n+1}" << "|" << setw(15) << "Разность" << "|" << endl;
    cout << "+-------+---------------+---------------+---------------+" << endl;
}

void printNewtonRow(int n, double x, double x_next) {
    cout << "|" << setw(7) << n << "|" << setw(15) << setprecision(6) << fixed << x << "|"
        << setw(15) << x_next << "|" << setw(15) << fabs(x_next - x) << "|" << endl;
}

void newton(double x0, double epsilon) {
    cout << "МЕТОД НЬЮТОНА" << endl;
    cout << "Начальное приближение: " << x0 << endl;
    printNewtonHeader();

    double x = x0;
    int n = 0;
    while (true) {
        double x_next = x - f(x) / df(x);
        printNewtonRow(n, x, x_next);
        if (fabs(x_next - x) < epsilon) break;
        x = x_next;
        n++;
    }
    cout << "+-------+---------------+---------------+---------------+" << endl;
    cout << "Корень: " << setprecision(10) << x << endl;
    cout << "Количество итераций: " << n << endl << endl;
}

double phi(double x) {
    return (1 + x) / (log(x + 1) + 1);
}

void printIterationHeader() {
    cout << "+-------+---------------+---------------+---------------+" << endl;
    cout << "|" << setw(7) << "N" << "|" << setw(15) << "x_n" << "|"
        << setw(15) << "x_{n+1}" << "|" << setw(15) << "Разность" << "|" << endl;
    cout << "+-------+---------------+---------------+---------------+" << endl;
}

void printIterationRow(int n, double x, double x_next) {
    cout << "|" << setw(7) << n << "|" << setw(15) << setprecision(8) << fixed << x << "|"
        << setw(15) << x_next << "|" << setw(15) << fabs(x_next - x) << "|" << endl;
}

void simpleIteration(double x0, double epsilon) {
    cout << "МЕТОД ПРОСТЫХ ИТЕРАЦИЙ (положительный корень)" << endl;
    cout << "Начальное приближение: " << x0 << endl;
    printIterationHeader();

    double x = x0;
    double x_next;
    int n = 0;

    do {
        x_next = phi(x);
        printIterationRow(n, x, x_next);
        if (fabs(x_next - x) < epsilon) break;
        x = x_next;
        n++;
    } while (n < 100);

    cout << "+-------+---------------+---------------+---------------+" << endl;
    cout << "Корень: " << setprecision(10) << x_next << endl;
    cout << "Проверка: f(" << x_next << ") = " << f(x_next) << endl;
    cout << "Количество итераций: " << n << endl << endl;
}

double phi_negative(double x) {
    return exp(1 / x) - 1;
}

void simpleIterationNegative(double x0, double epsilon) {
    cout << "МЕТОД ПРОСТЫХ ИТЕРАЦИЙ (отрицательный корень)" << endl;
    cout << "Начальное приближение: " << x0 << endl;
    printIterationHeader();

    double x = x0;
    double x_next;
    int n = 0;

    do {
        x_next = phi_negative(x);
        printIterationRow(n, x, x_next);
        if (fabs(x_next - x) < epsilon) break;
        x = x_next;
        n++;
    } while (n < 100);

    cout << "+-------+---------------+---------------+---------------+" << endl;
    cout << "Отрицательный корень: " << setprecision(10) << x_next << endl;
    cout << "Проверка: f(" << x_next << ") = " << f(x_next) << endl;
    cout << "Количество итераций: " << n << endl << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "=====================================================" << endl;
    cout << " РЕШЕНИЕ УРАВНЕНИЯ x*ln(x+1) - 1 = 0" << endl;
    cout << "=====================================================" << endl << endl;

    // Метод половинного деления
    halfDel(0.0, 2.0, epsilon);

    // Метод Ньютона
    newton(1.0, epsilon);

    // Метод простых итераций (положительный корень)
    simpleIteration(1.0, epsilon);

    // Метод простых итераций (отрицательный корень)
    simpleIterationNegative(-0.5, epsilon);

    return 0;
}

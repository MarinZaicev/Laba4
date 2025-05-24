#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

float epsilon = 0.0001;

double f(double x) {
    return x * log(x + 1) - 1;
}

void halfDel(double a, double b, double epsilon) {
    setlocale(LC_ALL, "Russian");
    if (f(a) * f(b) >= 0) {
        cout << "На интервале нет корня или несколько корней\n";
        return;
    }

    cout << "Метод половинного деления:\n";
    cout << "N\ta_n\t\tb_n\t\tb_n - a_n\n";

    double c;
    int n = 0;
    while ((b - a) >= epsilon) {
        c = (a + b) / 2;

        cout << n << "\t" << setprecision(6) << fixed
            << a << "\t" << b << "\t" << (b - a) << "\n";

        if (fabs(f(c)) < epsilon)
            break;
        else if (f(c) * f(a) < 0)
            b = c;
        else
            a = c;

        n++;
    }

    cout << "\nИтоговый корень: " << std::setprecision(10) << c << "\n";
    cout << "Значение функции в корне: " << f(c) << "\n";
}
double df(double x) {
    return log(x + 1) + x / (x + 1);
}

void newton(double x0, double epsilon) {
    cout << "Метод Ньютона:\n";
    cout << "N\tx_n\t\tx_{n+1}\t\tx_{n+1} - x_n\n";
    double x = x0;
    int n = 0;
    while (true) {
        double x_next = x - f(x) / df(x);
        cout << n << "\t" << setprecision(6) << fixed
            << x << "\t" << x_next << "\t" << fabs(x_next - x) << "\n";
        if (fabs(x_next - x) < epsilon) break;
        x = x_next;
        n++;
    }
    cout << "Корень: " << x << "\n\n";
}

double phi(double x) {
    return (1 + x) / (log(x + 1) + 1);
}

void simpleIteration(double x0, double epsilon) {
    std::cout << "Метод простых итераций: положительный корень\n";
    std::cout << "n\tx_n\t\tx_{n+1}\t\t|x_{n+1} - x_n|\n";

    double x = x0;
    double x_next;
    int n = 0;

    do {
        x_next = phi(x);
        cout << n << "\t" << setprecision(8) << x << "\t"
            << x_next << "\t" << fabs(x_next - x) << "\n";

        if (fabs(x_next - x) < epsilon) break;
        x = x_next;
        n++;
    } while (n < 100);  // Защита от бесконечного цикла

    cout << "\nКорень: " << x_next << "\n";
    cout << "Проверка: f(" << x_next << ") = " << f(x_next) << "\n";
}
double phi_negative(double x) {
    return exp(1 / x) - 1;  // Итерационная функция для x < 0
}

void simpleIterationNegative(double x0, double epsilon) {
    cout << "Метод простых итераций: отрицательный корень:\n";
    cout << "n\tx_n\t\tx_{n+1}\t\t|x_{n+1} - x_n|\n";

    double x = x0;
    double x_next;
    int n = 0;

    do {
        x_next = phi_negative(x);
        cout << n << "\t" << setprecision(8) << x << "\t"
            << x_next << "\t" << fabs(x_next - x) << "\n";

        if (fabs(x_next - x) < epsilon) break;
        x = x_next;
        n++;
    } while (n < 100);

    cout << "\nОтрицательный корень: " << x_next << "\n";
    cout << "Проверка: f(" << x_next << ") = " << f(x_next) << "\n";
}



int main() {
    
}

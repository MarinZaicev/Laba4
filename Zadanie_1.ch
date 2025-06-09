using System;

namespace RootFindingMethods
{
    class Program
    {
        const double epsilon = 0.0001;

        static double F(double x)
        {
            return x * Math.Log(x + 1) - 1;
        }

        static void PrintTableHeader()
        {
            Console.WriteLine("+-------+---------------+---------------+---------------+");
            Console.WriteLine("|{0,7}|{1,15}|{2,15}|{3,15}|", "N", "a_n", "b_n", "b_n - a_n");
            Console.WriteLine("+-------+---------------+---------------+---------------+");
        }

        static void PrintTableRow(int n, double a, double b)
        {
            Console.WriteLine("|{0,7}|{1,15:F6}|{2,15:F6}|{3,15:F6}|", n, a, b, b - a);
        }

        static void HalfDivision(double a, double b, double epsilon)
        {
            if (F(a) * F(b) >= 0)
            {
                Console.WriteLine("На интервале нет корня или несколько корней");
                return;
            }

            Console.WriteLine("МЕТОД ПОЛОВИННОГО ДЕЛЕНИЯ");
            Console.WriteLine($"Исходный интервал: [{a}, {b}]");
            PrintTableHeader();

            double c = 0;
            int n = 0;
            while ((b - a) >= epsilon)
            {
                c = (a + b) / 2;
                PrintTableRow(n, a, b);

                if (Math.Abs(F(c)) < epsilon)
                    break;
                else if (F(c) * F(a) < 0)
                    b = c;
                else
                    a = c;

                n++;
            }
            Console.WriteLine("+-------+---------------+---------------+---------------+");
            Console.WriteLine($"Итоговый корень: {c:F10}");
            Console.WriteLine($"Значение функции: {F(c)}");
            Console.WriteLine($"Количество итераций: {n}\n");
        }

        static double Df(double x)
        {
            return Math.Log(x + 1) + x / (x + 1);
        }

        static void PrintNewtonHeader()
        {
            Console.WriteLine("+-------+---------------+---------------+---------------+");
            Console.WriteLine("|{0,7}|{1,15}|{2,15}|{3,15}|", "N", "x_n", "x_{n+1}", "Разность");
            Console.WriteLine("+-------+---------------+---------------+---------------+");
        }

        static void PrintNewtonRow(int n, double x, double x_next)
        {
            Console.WriteLine("|{0,7}|{1,15:F6}|{2,15:F6}|{3,15:F6}|", n, x, x_next, Math.Abs(x_next - x));
        }

        static void Newton(double x0, double epsilon)
        {
            Console.WriteLine("МЕТОД НЬЮТОНА");
            Console.WriteLine($"Начальное приближение: {x0}");
            PrintNewtonHeader();

            double x = x0;
            int n = 0;
            while (true)
            {
                double x_next = x - F(x) / Df(x);
                PrintNewtonRow(n, x, x_next);
                if (Math.Abs(x_next - x) < epsilon) break;
                x = x_next;
                n++;
            }
            Console.WriteLine("+-------+---------------+---------------+---------------+");
            Console.WriteLine($"Корень: {x:F10}");
            Console.WriteLine($"Количество итераций: {n}\n");
        }

        static double Phi(double x)
        {
            return (1 + x) / (Math.Log(x + 1) + 1);
        }

        static void PrintIterationHeader()
        {
            Console.WriteLine("+-------+---------------+---------------+---------------+");
            Console.WriteLine("|{0,7}|{1,15}|{2,15}|{3,15}|", "N", "x_n", "x_{n+1}", "Разность");
            Console.WriteLine("+-------+---------------+---------------+---------------+");
        }

        static void PrintIterationRow(int n, double x, double x_next)
        {
            Console.WriteLine("|{0,7}|{1,15:F8}|{2,15:F8}|{3,15:F8}|", n, x, x_next, Math.Abs(x_next - x));
        }

        static void SimpleIteration(double x0, double epsilon)
        {
            Console.WriteLine("МЕТОД ПРОСТЫХ ИТЕРАЦИЙ (положительный корень)");
            Console.WriteLine($"Начальное приближение: {x0}");
            PrintIterationHeader();

            double x = x0;
            double x_next;
            int n = 0;

            do
            {
                x_next = Phi(x);
                PrintIterationRow(n, x, x_next);
                if (Math.Abs(x_next - x) < epsilon) break;
                x = x_next;
                n++;
            } while (n < 100);

            Console.WriteLine("+-------+---------------+---------------+---------------+");
            Console.WriteLine($"Корень: {x_next:F10}");
            Console.WriteLine($"Проверка: f({x_next}) = {F(x_next)}");
            Console.WriteLine($"Количество итераций: {n}\n");
        }

        static double PhiNegative(double x)
        {
            return Math.Exp(1 / x) - 1;
        }

        static void SimpleIterationNegative(double x0, double epsilon)
        {
            Console.WriteLine("МЕТОД ПРОСТЫХ ИТЕРАЦИЙ (отрицательный корень)");
            Console.WriteLine($"Начальное приближение: {x0}");
            PrintIterationHeader();

            double x = x0;
            double x_next;
            int n = 0;

            do
            {
                x_next = PhiNegative(x);
                PrintIterationRow(n, x, x_next);
                if (Math.Abs(x_next - x) < epsilon) break;
                x = x_next;
                n++;
            } while (n < 100);

            Console.WriteLine("+-------+---------------+---------------+---------------+");
            Console.WriteLine($"Отрицательный корень: {x_next:F10}");
            Console.WriteLine($"Проверка: f({x_next}) = {F(x_next)}");
            Console.WriteLine($"Количество итераций: {n}\n");
        }

        static void Main(string[] args)
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            Console.WriteLine("=====================================================");
            Console.WriteLine(" РЕШЕНИЕ УРАВНЕНИЯ x*ln(x+1) - 1 = 0");
            Console.WriteLine("=====================================================\n");

            // Метод половинного деления
            HalfDivision(0.0, 2.0, epsilon);

            // Метод Ньютона
            Newton(1.0, epsilon);

            // Метод простых итераций (положительный корень)
            SimpleIteration(1.0, epsilon);

            // Метод простых итераций (отрицательный корень)
            SimpleIterationNegative(-0.5, epsilon);
        }

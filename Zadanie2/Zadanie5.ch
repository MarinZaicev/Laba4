using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    // Функция для перемешивания цифр числа
    static int ShuffleDigits(int num)
    {
        string s = num.ToString();

        // Если число однозначное - возвращаем как есть
        if (s.Length == 1) return num;

        Random random = new Random();
        string shuffled;

        // Перемешиваем цифры, избегая ведущих нулей
        do
        {
            shuffled = new string(s.ToCharArray().OrderBy(c => random.Next()).ToArray());
        }
        while (shuffled[0] == '0');

        return int.Parse(shuffled);
    }

    static void Main(string[] args)
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8;
        Random random = new Random();
        
        Console.Write("Введите размер массива: ");
        int n = int.Parse(Console.ReadLine());

        List<int> originalArray = new List<int>();
        for (int i = 0; i < n; i++)
        {
            originalArray.Add(random.Next(100, 902)); // 902 чтобы включить 901
        }

        Console.Write("Исходный массив: ");
        Console.WriteLine(string.Join(" ", originalArray));

        // 1. Сортируем исходный массив по возрастанию
        originalArray.Sort();

        Console.Write("Отсортированный исходный массив: ");
        Console.WriteLine(string.Join(" ", originalArray));

        // 2. Создаем новый массив с перемешанными числами
        List<int> shuffledArray = new List<int>();
        foreach (int num in originalArray)
        {
            shuffledArray.Add(ShuffleDigits(num));
        }

        Console.Write("Массив с перемешанными числами: ");
        Console.WriteLine(string.Join(" ", shuffledArray));
    }

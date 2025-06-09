using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static void PrintVector<T>(List<T> vec)
    {
        foreach (var n in vec)
        {
            Console.Write(n + " ");
        }
    }

    static List<int> CreateContainer(int n)
    {
        Random random = new Random();
        List<int> papa = new List<int>(n);
        for (int i = 0; i < n; i++)
        {
            papa.Add(random.Next(1, 100)); // 1..99
        }
        return papa;
    }

    static void Summa(List<int> arr1)
    {
        int sum = 0;
        int minimum = 101;
        int maximum = 0;
        int indexMax = 0;
        int indexMin = 0;
        int index = 0;

        foreach (var n in arr1)
        {
            if (n < minimum)
            {
                minimum = n;
            }
            if (n > maximum)
            {
                maximum = n;
            }
        }

        index = 0;
        foreach (var n in arr1)
        {
            if (n == maximum)
            {
                indexMax = index;
            }
            if (n == minimum)
            {
                indexMin = index;
            }
            index++;
        }

        int start = Math.Min(indexMin, indexMax);
        int end = Math.Max(indexMin, indexMax);

        index = 0;
        foreach (var n in arr1)
        {
            if (index > start && index < end)
            {
                sum += n;
            }
            index++;
        }

        Console.WriteLine(sum);
    }

    static List<int> CreateNewContainer(List<int> arr1)
    {
        Random random = new Random();
        int minimum = 101;
        int maximum = 0;
        int indexMax = 0;
        int indexMin = 0;
        int index = 0;

        foreach (var n in arr1)
        {
            if (n < minimum)
            {
                minimum = n;
            }
            if (n > maximum)
            {
                maximum = n;
            }
        }

        index = 0;
        foreach (var n in arr1)
        {
            if (n == maximum)
            {
                indexMax = index;
            }
            if (n == minimum)
            {
                indexMin = index;
            }
            index++;
        }

        int start = Math.Min(indexMin, indexMax);
        int end = Math.Max(indexMin, indexMax);

        List<int> arr2 = new List<int>();
        index = 0;

        foreach (var n in arr1)
        {
            if (index > start && index < end)
            {
                arr2.Add(n);
            }
            else
            {
                arr2.Add(arr1[random.Next(0, arr1.Count)]);
            }
            index++;
        }

        return arr2;
    }

    static Tuple<List<char>, List<char>> Sorti(int length)
    {
        Random random = new Random();
        List<char> original = new List<char>(length);

        for (int i = 0; i < length; i++)
        {
            original.Add((char)random.Next('a', 'z' + 1));
        }

        List<char> sorted = new List<char>(original);

        var evenElements = new List<Tuple<int, char>>();
        for (int i = 0; i < sorted.Count; i++)
        {
            if (i % 2 == 0)
            {
                evenElements.Add(Tuple.Create(i, sorted[i]));
            }
        }

        evenElements.Sort((a, b) => a.Item2.CompareTo(b.Item2));

        int evenIndex = 0;
        for (int i = 0; i < sorted.Count; i++)
        {
            if (i % 2 == 0)
            {
                sorted[i] = evenElements[evenIndex++].Item2;
            }
        }

        return Tuple.Create(original, sorted);
    }

    static void Main(string[] args)
    {
        Console.Write("Введите размер массива: ");
        int n = int.Parse(Console.ReadLine());

        var arr1 = CreateContainer(n);
        PrintVector(arr1);
        Console.WriteLine();
        Summa(arr1);

        var arr2 = CreateNewContainer(arr1);
        PrintVector(arr2);
        Console.WriteLine();

        var origSorted = Sorti(n);
        PrintVector(origSorted.Item1);
        Console.WriteLine();
        PrintVector(origSorted.Item2);
    }

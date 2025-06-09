using System;
using System.Collections.Generic;
using System.Linq;

class Program
{
    static string BordaWinner(List<List<string>> votes, List<string> candidates)
    {
        Dictionary<string, int> scores = new Dictionary<string, int>();

        // Инициализация счетчиков
        foreach (string candidate in candidates)
        {
            scores[candidate] = 0;
        }

        // Начисление баллов
        foreach (List<string> vote in votes)
        {
            for (int i = 0; i < vote.Count; i++)
            {
                scores[vote[i]] += (vote.Count - 1 - i);
            }
        }

        // Поиск победителя
        string winner = "";
        int maxScore = -1;
        foreach (var entry in scores)
        {
            if (entry.Value > maxScore)
            {
                maxScore = entry.Value;
                winner = entry.Key;
            }
        }

        return winner;
    }

    static string CondorcetWinner(List<List<string>> votes, List<string> candidates)
    {
        Dictionary<string, Dictionary<string, int>> pairwise = 
            new Dictionary<string, Dictionary<string, int>>();

        // Инициализация матрицы
        foreach (string c1 in candidates)
        {
            pairwise[c1] = new Dictionary<string, int>();
            foreach (string c2 in candidates)
            {
                if (c1 != c2)
                {
                    pairwise[c1][c2] = 0;
                }
            }
        }

        // Заполнение матрицы
        foreach (List<string> vote in votes)
        {
            for (int i = 0; i < vote.Count; i++)
            {
                for (int j = i + 1; j < vote.Count; j++)
                {
                    string preferred = vote[i];
                    string lessPreferred = vote[j];
                    pairwise[preferred][lessPreferred]++;
                }
            }
        }

        // Поиск победителя Кондорсе
        foreach (string candidate in candidates)
        {
            bool isCondorcetWinner = true;

            foreach (string opponent in candidates)
            {
                if (candidate != opponent)
                {
                    if (pairwise[candidate][opponent] <= pairwise[opponent][candidate])
                    {
                        isCondorcetWinner = false;
                        break;
                    }
                }
            }

            if (isCondorcetWinner)
            {
                return candidate;
            }
        }

        return "Нет победителя по Кондорсе";
    }

    static void Main(string[] args)
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8;

        Console.Write("Введите количество кандидатов: ");
        int n = int.Parse(Console.ReadLine());
        Console.Write("Введите количество избирателей: ");
        int k = int.Parse(Console.ReadLine());

        List<string> candidates = new List<string>(n);
        Console.Write("Введите имена кандидатов (через пробел): ");
        candidates = Console.ReadLine().Split(' ').ToList();

        List<List<string>> votes = new List<List<string>>(k);
        Console.WriteLine("Введите предпочтения избирателей:");
        for (int i = 0; i < k; i++)
        {
            Console.Write($"Избиратель {i + 1}: ");
            votes.Add(Console.ReadLine().Split(' ').ToList());
        }

        string borda = BordaWinner(votes, candidates);
        string condorcet = CondorcetWinner(votes, candidates);

        Console.WriteLine("\nРезультаты:");
        Console.WriteLine($"Метод Борда: {borda}");
        Console.WriteLine($"Метод Кондорсе: {condorcet}");

        if (borda != condorcet && condorcet != "Нет победителя по Кондорсе")
        {
            Console.WriteLine("Примечание: разные методы дали разных победителей.");
        }
    }
}

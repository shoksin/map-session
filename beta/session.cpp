#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

struct SMark
{
    std::string Subject;
    int Mark;
    bool operator<(const SMark &other) const
    {
        return Mark < other.Mark;
    }
};

struct SStudData
{
    std::string Name;
    int Number;
    std::vector<SMark> Marks;
    double Average() const
    {
        double sum = 0;
        for (auto &el : Marks)
        {
            sum += el.Mark;
        }
        return sum / Marks.size();
    }

    bool operator<(const SStudData &other) const
    {
        if (Name == other.Name)
        {
            return Average() > other.Average();
        }
        return Name < other.Name;
    }
};

SMark CreateSMark(std::string &Sb, int M)
{
    SMark A;
    A.Subject = Sb;
    A.Mark = M;
    return A;
}

SStudData CreateSStudData(std::vector<SMark> &Mks, std::string &Nm, int Nb)
{
    SStudData A;
    A.Name = Nm;
    A.Number = Nb;
    A.Marks = Mks;
    return A;
}

void PrintMarks(std::vector<SMark> v) //вывести вектор оценок
{
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i].Subject << ":" << v[i].Mark << " ";
    }
}

void PrintSStudeDataSTD(SStudData &a)//вывод без среднего балла
{
    std::cout << a.Name << " ";
    std::cout << a.Number << " ";
    PrintMarks(a.Marks);
}

void PrintSStudeDtAv(SStudData &a)//вывод структуры со средним баллом
{
    std::cout << a.Name << " ";
    std::cout << a.Number << " ";
    std::cout << a.Average();
}

void PrintSStudeDataAver(std::map<int, SStudData> mp)//вывод студентов отсортированных по Фамилии
{
    std::vector<std::pair<int, SStudData>> pairs;

    for (const auto &pair : mp)
    {
        pairs.push_back(pair);
    }

    std::sort(pairs.begin(), pairs.end(), [](const std::pair<int, SStudData> &a, const std::pair<int, SStudData> &b)
              { return a.second < b.second; });

    int number = 1;

    for (auto &el : pairs)
    {
        std::cout << number << ")";
        PrintSStudeDtAv(el.second);
        std::cout << "\n";
        number++;
    }
}
void PrintSTDMap(const std::map<int, SStudData> &mp)//вывод стандартной мапы
{
    for (auto s : mp)
    {
        PrintSStudeDataSTD(s.second);
        std::cout << "\n";
    }
}

void PrintAverBorder(const std::map<int, SStudData> &mp, int min, int max)//вывод тех студентов у кого средний балл находится в промежутке
{
    std::vector<std::pair<int, SStudData>> pairs;

    for (const auto &pair : mp)
    {
        pairs.push_back(pair);
    }

    std::sort(pairs.begin(), pairs.end(), [](const std::pair<int, SStudData> &a, const std::pair<int, SStudData> &b)
              { return a.second.Average() > b.second.Average(); });

    int number = 1;
    for (auto &el : pairs)
    {
        if (el.second.Average() <= max && el.second.Average() >= min)
        {
            std::cout << number << ")";
            PrintSStudeDtAv(el.second);
            std::cout << "\n";
            number++;
        }
    }
}

void AskedItem(const std::map<int, SStudData> &mp, std::string &a)//вывод тех кто сдавал заданный предмет
{
    for (auto s : mp)
    {
        for (int i = 0; i < s.second.Marks.size(); ++i)
        {
            if (s.second.Marks[i].Subject == a)
            {
                PrintSStudeDataSTD(s.second);
                std::cout << "\n";
            }
        }
    }
}

void AllItems(const std::map<int, SStudData> &mp)//вывод для каждого предмета количества учеников
{
    std::set<std::string> Subjects;
    for (const auto &pair : mp)
    {
        for (size_t i = 0; i < pair.second.Marks.size(); ++i)
        {
            Subjects.insert(pair.second.Marks[i].Subject);
        }
    }
    int counter = 0;
    for (const auto &s : Subjects)
    {
        for (const auto &pair : mp)
        {
            for (size_t i = 0; i < pair.second.Marks.size(); ++i)
            {
                if (pair.second.Marks[i].Subject == s)
                {
                    counter++;
                }
            }
        }
        std::cout << s << ": " << counter;
        std::cout << "\n";
        counter = 0;
    }
}

void AverageForAllItems(const std::map<int, SStudData> &mp)//вывод среднюю оценку по каждому предмету
{
    std::set<std::string> Subjects;
    for (const auto &pair : mp)
    {
        for (size_t i = 0; i < pair.second.Marks.size(); ++i)
        {
            Subjects.insert(pair.second.Marks[i].Subject);
        }
    }
    double Sum = 0;
    double counter = 0;
    double average = 0;

    std::vector<std::pair<std::string, double>> Mark;

    for (auto &s : Subjects)
    {
        for (const auto &pair : mp)
        {
            for (size_t i = 0; i < pair.second.Marks.size(); ++i)
            {
                if (pair.second.Marks[i].Subject == s)
                {
                    Sum += pair.second.Marks[i].Mark;
                    counter++;
                }
            }
        }

        average = Sum / counter;

        Mark.push_back(std::make_pair(s, average));
        counter = 0;
        Sum = 0;
    }

    std::sort(Mark.begin(), Mark.end(), [](const std::pair<std::string, double> &a, const std::pair<std::string, double> &b)
              { return a.second > b.second; });

    for (const auto &el : Mark)
    {
        std::cout << el.first << ": " << el.second << "\n";
    }
}

void MaxSum(const std::map<int, SStudData> &mp)//вывод студентов с баллом 10.0
{
    std::vector<std::pair<int, SStudData>> pairs;

    for (const auto &pair : mp)
    {
        pairs.push_back(pair);
    }

    std::sort(pairs.begin(), pairs.end(), [](const std::pair<int, SStudData> &a, const std::pair<int, SStudData> &b)
              { return a.second < b.second; });

    int number = 1;

    for (auto &el : pairs)
    {
        if (el.second.Average() == 10)
        {
            std::cout << number << ")";
            PrintSStudeDtAv(el.second);
            std::cout << "\n";
            number++;
        }
    }
    if (number == 1)
    {
        std::cout << "There are no such students!\n";
    }
}

void BadMarks(std::map<int, SStudData> &mp)//вывод студентов с неудовлетворительными оценками
{
    std::vector<std::pair<int, SStudData>> pairs;

    for (const auto &pair : mp)
    {
        pairs.push_back(pair);
    }

    std::sort(pairs.begin(), pairs.end(), [](const std::pair<int, SStudData> &a, const std::pair<int, SStudData> &b)
              { return a.second < b.second; });

    int number = 1;

    for (auto &el : pairs)
    {
        for (size_t i = 0; i < el.second.Marks.size(); ++i)
        {
            if (el.second.Marks[i].Mark == 0 || el.second.Marks[i].Mark == 1 || el.second.Marks[i].Mark == 2 || el.second.Marks[i].Mark == 3){
            std::cout << number << ")";
            PrintSStudeDataSTD(el.second);
            std::cout << "\n";
            number++;
            }
        }
    }

    if (number == 1)
    {
        std::cout << "There are no such students!\n";
    }
}

int main()
{

    std::map<int, SStudData> mp;

    std::ifstream infile("sessionMarks.txt");
    if (!infile.is_open())
    {
        std::cerr << "The file for reading did not open!";
        exit(1);
    }
    if (infile.peek() == EOF)
    {
        std::cerr << "The file is empty!";
        exit(1);
    }

    std::string check;

    while (!infile.eof())
    {
        std::string Name, Numb, Subj, Mrk;
        SStudData SD;
        SMark A;
        std::vector<SMark> Mrks;
        getline(infile, check);
        check += ';';
        int i = 0;
        while (check[i] != ' ')
        {
            i++;
        }
        i++;

        while (check[i] != ' ')
        {
            i++;
        }
        Name = check.substr(0, i - 0);
        std::cout << Name << " ";

        int start = i + 1;
        i++;
        while (check[i] != ' ')
        {
            i++;
        }
        Numb = check.substr(start, i - start);
        int Nmbr = stoi(Numb);
        std::cout << Numb << " ";

        i++;
        start = i;
        while (check[i] != ';')
        {
            if (check[i] == ':')
            {
                Subj = check.substr(start, i - start);
                std::cout << Subj << ":";
                i++;
                start = i;
                while (check[i] != ' ' && check[i] != ';')
                {
                    i++;
                }
                Mrk = check.substr(start, i - start);
                std::cout << Mrk << " ";
                int M = stoi(Mrk);
                A = CreateSMark(Subj, M);
                Mrks.push_back(A);
            }

            else if (check[i] == ' ')
            {
                i++;
                start = i;
            }

            else
            {
                i++;
            }
        }
        SD = CreateSStudData(Mrks, Name, Nmbr);
        mp.insert(std::make_pair(Nmbr, SD));
        std::cout << "\n";
    }

    ///////////////////////////////////////////////////////////////////////////////

    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Sort by number:\n";
    PrintSTDMap(mp);

    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Sort by Second Name with average mark:\n";
    PrintSStudeDataAver(mp);

    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Average mark from 6 to 8:\n";
    int min = 6;
    int max = 8;
    PrintAverBorder(mp, min, max);

    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Students who took physics:\n";
    std::string Item = "Physics";
    AskedItem(mp, Item);

    std::cout << "-------------------------------------------------------------\n";
    std::cout << "How many people took each subject:\n";
    AllItems(mp);

    std::cout << "-------------------------------------------------------------\n";
    std::cout << "Average for all items:\n";
    AverageForAllItems(mp);

    std::cout << "-------------------------------------------------------------\n";
    std::cout << "All students with max sum:\n";
    MaxSum(mp);

    std::cout << "-------------------------------------------------------------\n";
    std::cout << "All students with bad grades:\n";
    BadMarks(mp);
}

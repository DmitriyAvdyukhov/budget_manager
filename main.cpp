#include "budget_manager.h"
#include "parser.h"
#include"date.h"

#include <iostream>
#include <string_view>
#include <fstream>
#include <tuple>

using namespace std;
struct Dates
{
    Date from;
    Date to;
};

std::tuple<std::string_view, uint8_t> SplitWord(std::string_view line, uint8_t pos = 0)
{   
    auto pos_second = line.find(' ', pos);
    std::string_view result = line.substr(pos, pos_second - pos);
   
    return { result, pos_second + 1 };
}

std::tuple<Dates, uint8_t> GetDates(std::string_view line, uint8_t pos)
{
    auto [date_from, pos_d1] = SplitWord(line, pos);
    auto [date_to, pos_d2] = SplitWord(line, pos_d1);
    return { {Date::FromString(date_from), Date::FromString(date_to)}, pos_d2 };
}

void ParseAndProcessQuery(BudgetManager& manager, string_view line)
{       
    auto [word, pos] = SplitWord(line);
    if (word == "Earn")
    {
        auto [dates, pos_finish] = GetDates(line, pos);
        auto [sum_str, pos_end] = SplitWord(line, pos_finish);
        double sum = std::stod(std::string(sum_str));
        QueryModification qm(dates.from, dates.to, manager, sum);
        qm.CreateBudget();
    }
    else if (word == "ComputeIncome")
    {
        auto[dates, pos_finish] = GetDates(line, pos);
        ComputeIncome ci(dates.from, dates.to);
        std::cout << ci.ComputeAndPrint(manager) << std::endl;
    }
    else if (word == "PayTax")
    {
        auto [dates, pos_finish] = GetDates(line, pos);
        auto [sum_str, pos_end] = SplitWord(line, pos_finish);
        int tax = std::stoi(std::string(sum_str));
        QueryModification qm(dates.from, dates.to, manager, tax);
        qm.PayTax();
    }
    else if (word == "Spend")
    {
        auto [dates, pos_finish] = GetDates(line, pos);
        auto [sum_str, pos_end] = SplitWord(line, pos_finish);
        double sum = std::stod(std::string(sum_str));
        QueryModification qm(dates.from, dates.to, manager, sum);
        qm.Spend();
    }
    else
    {
        cout << "Incorrect input" << endl;
    }
}

int ReadNumberOnLine(istream& input)
{
    std::string line;
    std::getline(input, line);
    return std::stoi(line);
}

int main() 
{
    BudgetManager manager;

    std::ifstream in("test1.txt");
    if (in)
    {
        const int query_count = ReadNumberOnLine(in);

        for (int i = 0; i < query_count; ++i)
        {
            std::string line;
            std::getline(in, line);
            ParseAndProcessQuery(manager, line);
        }
    }
    else
    {
        const int query_count = ReadNumberOnLine(cin);

        for (int i = 0; i < query_count; ++i)
        {
            std::string line;
            std::getline(cin, line);
            ParseAndProcessQuery(manager, line);
        }
    }
    return 0;
}

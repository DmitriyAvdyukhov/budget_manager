#include "budget_manager.h"
#include "parser.h"
#include"date.h"

#include <iostream>
#include <string_view>
#include <fstream>
#include <tuple>
#include <optional>

using namespace std;


std::tuple<std::string_view, std::optional<std::string_view>> SplitWord(std::string_view line, uint8_t pos = 0)
{   
    auto pos_second = line.find(' ', pos);
    std::string_view result = line.substr(pos, pos_second - pos);
    if (pos_second == string::npos)
    {
        return { result, {} };
    }    
    return { result, line.substr(pos_second + 1) };
}

std::vector<std::string_view> SplitWords(std::string_view line)
{
    std::vector<std::string_view> result;
    while (true)
    {
        auto [query, other_words] = SplitWord(line);
        result.push_back(query);
        if (!other_words)
        {
            return result;
        }
        line = *other_words;
    }
}

void ParseAndProcessQuery(BudgetManager& manager, string_view line)
{       
    auto [command, queries] = SplitWord(line);
   
    if (command == "Earn")
    {
        std::vector<std::string_view> query = SplitWords(*queries);          
        QueryModification qm(Date::FromString(query[0]), Date::FromString(query[1])
            , manager, std::stod(std::string(query[2])));
        qm.CreateBudget();
    }
    else if (command == "ComputeIncome")
    {
        std::vector<std::string_view> query = SplitWords(*queries);
        ComputeIncome ci(Date::FromString(query[0]), Date::FromString(query[1]));
        std::cout << ci.ComputeAndPrint(manager) << std::endl;
    }
    else if (command == "PayTax")
    {
        std::vector<std::string_view> query = SplitWords(*queries);      
        QueryModification qm(Date::FromString(query[0]), Date::FromString(query[1])
            , manager, std::stoi(std::string(query[2])));
        qm.PayTax();
    }
    else if (command == "Spend")
    {
        std::vector<std::string_view> query = SplitWords(*queries);
        QueryModification qm(Date::FromString(query[0]), Date::FromString(query[1])
            , manager, std::stoi(std::string(query[2])));
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

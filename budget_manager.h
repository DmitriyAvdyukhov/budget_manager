#pragma once
#include "date.h"
#include <iostream>
#include <vector>




struct DayInfo
{   
    double income = 0.;
    double speding = 0.;
};

class BudgetManager
{
public:
    inline static const Date START_DATE{ 2000, 1, 1 };
    inline static const Date END_DATE{ 2100, 1, 1 };    
    
    BudgetManager()
    {
        budget_.resize(Date::ComputeDistance(START_DATE, END_DATE));
    }

    void AddBudget(int pos, double sum)
    {       
        budget_[pos].income += sum;
    }    

     std::vector<DayInfo>& GetBudget()
     {
         return budget_;
     }

private:    
    std::vector<DayInfo>budget_;
};


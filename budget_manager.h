#pragma once
#include "date.h"
#include <iostream>
#include <vector>




struct DayInfo
{   
    double income = 0.;
    double spending = 0.;
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

    void AddBudget(int pos_day, double income)
    {       
        budget_[pos_day].income += income;
    }   

    void AddSpending(int pos_day, double spending)
    {
        budget_[pos_day].spending += spending;
    }

    void AddPayTax(int pos_day, double bid_of_tax)
    {
        budget_[pos_day].income *= bid_of_tax;
    }

    const std::vector<DayInfo>& GetBudget()const
    {
        return budget_;
    }

private:    
    std::vector<DayInfo>budget_;
};


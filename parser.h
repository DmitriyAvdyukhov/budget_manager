#pragma once
#include "date.h"
#include "budget_manager.h"

// напишите в этом классе код, ответственный за чтение запросов
class Query
{
public:
	virtual ~Query() = default;
	Query(Date from, Date to) :from_(from), to_(to)
	{}

	Date GetFrom()const
	{
		return from_;
	}
	Date GetTo()const
	{
		return to_;
	}	

private:

	Date from_, to_;
};

class QueryModification : public Query
{
public:	
	QueryModification(Date from, Date to, BudgetManager& manager, double amount = 0.)
		: Query(from, to)
		, manager_(manager)
		, amount_(amount)
	{}

	void CreateBudget()
	{
		int count_day = Date::ComputeDistance(GetFrom(), GetTo());
		const double amount_day = amount_ / (++count_day);
		auto start = Date::ComputeDistance(BudgetManager::START_DATE, GetFrom());
		auto end = Date::ComputeDistance(BudgetManager::START_DATE, GetTo());		
		for (; start <= end; ++start)
		{				
			manager_.AddBudget(start, amount_day);
		}
		
	}	

	void PayTax()
	{	
		const double bid_of_tax = 1 - amount_ / 100;
		auto start = Date::ComputeDistance(BudgetManager::START_DATE, GetFrom());
		auto end = Date::ComputeDistance(BudgetManager::START_DATE, GetTo());

		for (; start <= end; ++start)
		{	
			manager_.AddPayTax(start, bid_of_tax);
		}		
	}

	void Spend()
	{
		int count_day = Date::ComputeDistance(GetFrom(), GetTo());
		const double spending_day = amount_ / (++count_day);
		auto start = Date::ComputeDistance(BudgetManager::START_DATE, GetFrom());
		auto end = Date::ComputeDistance(BudgetManager::START_DATE, GetTo());
		for (; start <= end; ++start)
		{
			manager_.AddSpending(start, spending_day);
		}
	}

private:
	BudgetManager& manager_;
	double amount_;
	
};

class ComputeIncome : public Query
{
public:
	ComputeIncome(Date from, Date to) : Query(from, to) {}
	double ComputeAndPrint(BudgetManager& manager)
	{
		auto start = Date::ComputeDistance(BudgetManager::START_DATE, GetFrom());
		auto end = Date::ComputeDistance(BudgetManager::START_DATE, GetTo());
		double all_sum = 0.;		
		for (; start <= end; ++start)
		{			
			all_sum += manager.GetBudget()[start].income;
			all_sum -= manager.GetBudget()[start].spending;
		}
		return all_sum ;
	}
};
#pragma once
#include <vector>
#include "map"
#include "jobconfiguration.h"

using namespace std;

/**
* @Brief class that represents the inside of the knapsack, i.e the list of items
*/
class SackComposition
{
public:
	SackComposition();
	SackComposition(std::vector<JobConfiguration> itemList);
	int getTotalWeight() { return totalWeight; };
	int getTotalProfit() { return totalProfit; };
	std::map<int,JobConfiguration> getItemList() { return itemList; };
	int calculateTotalWeight();
	int calculateTotalProfit();
	void addJobConfiguration(JobConfiguration newItem);
	 

private:
	std::map<int, JobConfiguration> itemList;
	int totalWeight;
	int totalProfit;
};

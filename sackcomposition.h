#pragma once
#include <vector>
#include "unordered_map"
#include "jobconfiguration.h"
#include "map"

using namespace std;

/**
* @Brief class that represents the inside of the knapsack, i.e the list of items
*/
class SackComposition
{
public:
	SackComposition();
	SackComposition(vector<JobConfiguration> itemList);
	int getTotalWeight() { return totalWeight; };
	int getTotalProfit() { return totalProfit; };
	map<int,JobConfiguration> getItemList() { return itemList; };
	int calculateTotalWeight();
	int calculateTotalProfit();
	void addJobConfiguration(JobConfiguration newItem);
	 

private:
	map<int, JobConfiguration> itemList;
	int totalWeight;
	int totalProfit;
};

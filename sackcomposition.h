#pragma once
#include <vector>
#include "jobconfiguration.h"

using namespace std;

class SackComposition
{
public:
	SackComposition();
	SackComposition(vector<JobConfiguration> itemList);
	int getTotalWeight() { return totalWeight; };
	int getTotalProfit() { return totalProfit; };
	vector<JobConfiguration> getItemList() { return itemList; };
	int calculateTotalWeight();
	int calculateTotalProfit();
	void addJobConfiguration(JobConfiguration newItem);
	

public:
	vector<JobConfiguration> itemList;
	int totalWeight;
	int totalProfit;
};

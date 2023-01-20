#include "sackComposition.h"

/**
* Default Builder for SackComposition (i.e knapsack configuration)
*/
SackComposition::SackComposition() {
	this->totalProfit = 0;
	this->totalWeight = 0;
}

/**
* Builder for SackComposition (i.e knapsack configuration)
*/
SackComposition::SackComposition(std::vector<JobConfiguration> itemList) {
	this->itemList = itemList;
	this->calculateTotalProfit();
	this->calculateTotalWeight();
}

/**
* Calculate the total weight of a configuration
*/
int SackComposition::calculateTotalWeight() {
	totalWeight = 0;
	for (auto item : itemList) {
		totalWeight += item.getResources();
	}
	return totalWeight;
}

/**
* Calculate the total profit of a configuration
*/
int SackComposition::calculateTotalProfit() {
	totalProfit = 0;
	for (auto item : itemList) {
		totalProfit += item.getProfit();
	}
	return totalProfit;
}

void SackComposition::addJobConfiguration(JobConfiguration newItem) {
	itemList.push_back(newItem);
	totalWeight += newItem.getResources();
	totalProfit += newItem.getProfit();
}

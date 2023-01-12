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
	for (int i = 0; itemList.size(); i++)
		this->itemList[itemList[i].getTask()] = itemList[i];
	this->calculateTotalProfit();
	this->calculateTotalWeight();
}

/**
* Calculate the total weight of a configuration
*/
int SackComposition::calculateTotalWeight() {
	totalWeight = 0;
	for (auto item : itemList) {
		totalWeight += item.second.getResources();
	}
	return totalWeight;
}

/**
* Calculate the total profit of a configuration
*/
int SackComposition::calculateTotalProfit() {
	totalProfit = 0;
	for (auto item : itemList) {
		totalProfit += item.second.getProfit();
	}
	return totalProfit;
}

void SackComposition::addJobConfiguration(JobConfiguration newItem) {
	itemList[newItem.getTask()] = newItem;
	totalWeight += newItem.getResources();
	totalProfit += newItem.getProfit();
}

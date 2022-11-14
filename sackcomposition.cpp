#include "sackComposition.h"

SackComposition::SackComposition() {
	this->totalProfit = 0;
	this->totalWeight = 0;
}

SackComposition::SackComposition(vector<JobConfiguration> itemList) {
	this->itemList = itemList;
	this->calculateTotalProfit();
	this->calculateTotalWeight();
}

int SackComposition::calculateTotalWeight() {
	totalWeight = 0;
	for (JobConfiguration item : itemList) {
		totalWeight += item.getResources();
	}
	return totalWeight;
}

int SackComposition::calculateTotalProfit() {
	totalProfit = 0;
	for (JobConfiguration item : itemList) {
		totalProfit += item.getProfit();
	}
	return totalProfit;
}

void SackComposition::addJobConfiguration(JobConfiguration newItem) {
	itemList.push_back(newItem);
	totalWeight += newItem.getResources();
	totalProfit += newItem.getProfit();
}

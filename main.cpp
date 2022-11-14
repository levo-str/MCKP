#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include "jobconfiguration.h"
#include "SackComposition.h"

using namespace std;

int main() {

	/**
	// TODO put this part in test file
	Item testItem = Item(1, 1, 1);
	Item secondTestItem = Item(1, 1, 1);
	cout << "Testing if ID auto-incrementation works and if object creation is possible" << endl;
	cout << testItem.getId() << endl;
	cout << secondTestItem.getId();
	*/

	// Creating the tables to solve the multiple choice knapsack problem :
	// first one classic knapsack problem
	// second one composition of the knapsack in each case
	// third one (optional) just the list ordered by increasing id of the Items
	// apply normal dynamic knapsack resolution algorithm but also test out for configurations and test out where there is already an 
	// item on the same task 

	// first sketch without creating class or anything
	int numberItems, numberResources;
	unordered_map<int, JobConfiguration> mapItems;
	cout << "number of Items = number of Job configurations = ";
	cin >> numberItems;
	cout << endl << "number of resources we have = ";
	cin >> numberResources;
	cout << endl;
	int** profitArray = new int* [numberItems + 1];

	int r, p, t;

	for (int i = 0; i < numberItems+1; i++) {
		if (i != numberItems) {
			cout << "Item number  " << i + 1 << " please" << endl;
			cout << "resources = ";
			cin >> r;
			cout << endl;
			//p = pow(r,i+1);
			cout << "profit = ";
			cin >> p;
			cout << endl;
			//cout << "task number = ";
			//cin >> t;
			t = 0;
			cout << endl;

			JobConfiguration item = JobConfiguration(r, p, t);
			cout << "item number : " << item.getId() << endl;
			mapItems[item.getId()] = item;
		}
		profitArray[i] = new int[numberResources + 1];
	}

	// solving MKCP, first approach we don't care if 
	SackComposition* previousSackCompostionsList = new SackComposition[numberResources + 1];
	SackComposition* bestComposition = new SackComposition[numberResources + 1];
	vector<JobConfiguration> emptyVector = {};
	for (int j = 0; j < numberResources + 1; j++) {
		//cout << "inserting element j" << endl;
		bestComposition[j] = SackComposition(emptyVector);
	}
	cout << "algorithm initialization" << endl;
	for (int i = 0; i < numberItems + 1; i++) {
		for (int j = 0; j < numberResources + 1; j++) {
			//cout << "step number i = " << i << "number j = " << j << endl;
			if (i == 0 || j == 0) profitArray[i][j] = 0;

			else {
				JobConfiguration currentItem = mapItems[i];
				bestComposition[j] = previousSackCompostionsList[j].getItemList();
				int maxProfit = profitArray[i - 1][j];
				//cout << "item number : " << currentItem.getId() << " weighs " << currentItem.getResources() << endl;
				if (j >= currentItem.getResources()) {
					for (int k = 0; k < j + 1; k++) {
						if (currentItem.getResources() + previousSackCompostionsList[k].calculateTotalWeight() <= j) {
							if (currentItem.getProfit() + previousSackCompostionsList[k].calculateTotalProfit() > maxProfit) {
								bestComposition[j] = previousSackCompostionsList[k].getItemList();
								bestComposition[j].addJobConfiguration(currentItem);
								maxProfit = currentItem.getProfit() + previousSackCompostionsList[k].getTotalProfit();
							}
						}
					}
					profitArray[i][j] = maxProfit;
				}

				//not enough space in the sack
				else {
					profitArray[i][j] = profitArray[i - 1][j];
				}
			}
		}
		for (int j = 0; j < numberResources + 1; j++) previousSackCompostionsList[j] = bestComposition[j];
	}
	
	cout << endl << profitArray[numberItems][numberResources];
	cout << endl << previousSackCompostionsList[numberResources].getTotalProfit() << endl;

	for (int a = 0; a < numberItems + 1; a++)
	{
		for (int b = 0; b < numberResources + 1; b++)
		{
			cout << profitArray[a][b] << " ";
		}
		cout << endl;
	}
	return 0;
}

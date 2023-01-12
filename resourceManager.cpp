#include "resourceManager.h"


/**
* Default builder for ResourceManager
*/
ResourceManager::ResourceManager() {

}

bool compareByTask(JobConfiguration a, JobConfiguration b) {
	return a.getTask() < b.getTask();
}

/**
* ResourceManager builder 
*/
ResourceManager::ResourceManager(int numberOfResources, std::unordered_map<int, JobConfiguration> mapItems) {
	this->numberResources = numberOfResources;
	this->mapItems = mapItems;
	this->numberItems = mapItems.size();
	profitArray = new int* [this->numberItems + 1];
	for (int i = 0; i < this->numberItems + 1; i++) {
		this->profitArray[i] = new int[numberResources + 1];
	}
	for (auto item : mapItems) {
		this->itemsSortedByTask.push_back(item.second);
	}

	sort(this->itemsSortedByTask.begin(), this->itemsSortedByTask.end(), compareByTask);
	cout << "Initialisation complete" << endl;
}


/**
* Solve the MCKP according to parameters of the object Resource Manager
*/
SackComposition ResourceManager::solveMckp() {

	std::vector<JobConfiguration> emptyVector = {};
	SackComposition bestComposition = SackComposition(emptyVector);

	cout << "Solving starting ..." << endl;
	for (int i = 0; i < numberItems + 1; i++) {
		for (int j = 0; j < numberResources + 1; j++) { 
			//cout << "step number i = " << i << " number j = " << j << endl;
			
			if (i == 0 || j == 0) profitArray[i][j] = 0;

			else {
				JobConfiguration currentItem = itemsSortedByTask[i-1];
				int previousTask = itemsSortedByTask[i-1].getTask() - 1;
				
				//cout << "item number : " << currentItem.getId() << " weighs " << currentItem.getResources() << endl;
				if (j >= currentItem.getResources()) {
					int maxProfit = max(profitArray[i - 1][j], currentItem.getProfit());
					int k = j - currentItem.getResources();
					for (int l = 1; l < i; l++) {
						if (currentItem.getProfit() + profitArray[l][k] > maxProfit && itemsSortedByTask[l-1].getTask() == previousTask) {
							maxProfit = currentItem.getProfit() + profitArray[l][k];
						}
					}
					profitArray[i][j] = maxProfit;
				}

				else {
					profitArray[i][j] = profitArray[i - 1][j];
				}
			}
		}
	}
	//Now get the best composition : 
	int i = numberItems;
	int j = numberResources;
	int previousTask = itemsSortedByTask[i - 1].getTask();
	while (i > 1 && j > 0) {
		JobConfiguration inspectedJobConfiguration = itemsSortedByTask[i - 1];
		if (profitArray[i - 1][j] != profitArray[i][j] && inspectedJobConfiguration.getTask() <= previousTask) {
			previousTask = inspectedJobConfiguration.getTask() - 1;
			bestComposition.addJobConfiguration(inspectedJobConfiguration);
			j = j - itemsSortedByTask[i-1].getResources();
		}
		i--;
	}

	cout << endl << profitArray[numberItems][numberResources] << endl;

	for (int a = 0; a < numberItems + 1; a++)
	{
		for (int b = 0; b < numberResources + 1; b++)
		{
			cout << profitArray[a][b] << " ";
		}
		cout << endl;
	}
	cout << "profit of best composition = " << bestComposition.calculateTotalProfit();
	return bestComposition;
}

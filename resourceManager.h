#pragma once
#include "Task.h"
#include "jobconfiguration.h"
#include <vector>
#include <vector>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include "jobconfiguration.h"
#include "SackComposition.h"
#include "map"
#include "algorithm"

using namespace std;
/** 
* @brief The class of the MCKP solver 
*/
class ResourceManager
{
public:
	ResourceManager();
	ResourceManager(int numberOfResources, unordered_map<int, JobConfiguration> mapItems);
	SackComposition solveMckp();
	int** getProfitArray() { return profitArray; };
private:
	vector<Task> listOfTask;
	int numberItems;
	int numberResources;
	vector <JobConfiguration> itemsSortedByTask;
	unordered_map<int, JobConfiguration> mapItems;
	int** profitArray;

};


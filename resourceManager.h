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


/** 
* @brief The class of the MCKP solver 
*/
class ResourceManager
{
public:
	ResourceManager();
	ResourceManager(int numberOfResources, std:: unordered_map<int, JobConfiguration> mapItems);
	SackComposition solveMckp();
	int** getProfitArray() { return profitArray; };
private:
	std::vector<Task> listOfTask;
	int numberItems;
	int numberResources;
	std::vector <JobConfiguration> itemsSortedByTask;
	std::unordered_map<int, JobConfiguration> mapItems;
	int** profitArray;

};


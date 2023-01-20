#pragma once
#include "jobconfiguration.h"
#include <vector>
#include <vector>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <ppl.h>
#include "jobconfiguration.h"
#include "SackComposition.h"
#include "map"
#include "algorithm"


/** 
* @brief The class of the MCKP solver 
*/
class ResourceManagerDP
{
public:
	ResourceManagerDP();
	~ResourceManagerDP();
	ResourceManagerDP(int numberOfResources, std:: unordered_map<int, JobConfiguration> mapItems);
	SackComposition solveMckp();
	SackComposition solveMckpConcurrently();
	int** getProfitArray() { return profitArray; };
	void printProfitArray();
private:
	int numberItems;
	int numberResources;
	std::vector <JobConfiguration> itemsSortedByTask;
	std::unordered_map<int, JobConfiguration> mapItems;
	int** profitArray;

};


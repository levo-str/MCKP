#pragma once

#include <vector>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <ppl.h>
#include <limits>
#include "algorithm"

#include "Job.h"
#include "jobconfiguration.h"
#include "jobconfiguration.h"
#include "sackcomposition.h"
#include "ResourceManager.h"

class Node; //forward declaration for reciprocal dependency

/* 
* Solving class using the branch and bound algorithm
*/
class ResourceManagerBB : private ResourceManager
{
public:
	ResourceManagerBB();
	~ResourceManagerBB();
	ResourceManagerBB(int numberOfResources, std::unordered_map<int, JobConfiguration> mapItems);
	SackComposition solveMckp();
	SackComposition solveMckpConcurrently();
	

private:
	int numberItems;
	std::vector<JobConfiguration> itemsSortedByRatio;
	int nextIndex(int currentIndex);
	int calculateProfit(Node node);
	int calculateBound(std::vector<JobConfiguration> currentComposition, std::unordered_map<int,int> maxRatioItemIndexByTask, std::unordered_set<int> setsAlreadyPresent);
};

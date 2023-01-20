#pragma once
#include <unordered_map>
#include "jobconfiguration.h"
#include "sackcomposition.h"

class ProblemGenerator;
/**
* Base class for MCKP solver
*/
class ResourceManager
{
public:
	virtual SackComposition solveMckp() { return SackComposition(); };
	virtual SackComposition solveMckpConcurrently(){ return SackComposition(); };
	ResourceManager() {};
	ResourceManager(int numberOfResources, std::unordered_map<int, JobConfiguration> mapItems);
	ResourceManager(ProblemGenerator problem);

protected : 
	int numberItems;
	int numberResources;
	std::unordered_map<int, JobConfiguration> mapItems;
};

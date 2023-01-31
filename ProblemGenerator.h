#pragma once~
#include "jobconfiguration.h"
#include "Job.h"
#include <unordered_map>
#include <vector>
#include "ResourceManager.h"
#include "SolutionGenerator.h"

/**
* Link class between MCKP and shrinking malleable jobs.
*/
class ProblemGenerator
{
public:
	ProblemGenerator();
	ProblemGenerator(int numberOfNodesNeeded, vector<Job> jobList);
private:
	int numberOfNodes;
	std::unordered_map<int, JobConfiguration> mapItems;
	friend class ResourceManager;
	friend class SolutionGenerator;
};

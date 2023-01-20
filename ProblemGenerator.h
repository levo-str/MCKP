#pragma once~
#include "jobconfiguration.h"
#include "Job.h"
#include "ResourceManager.h"
#include <unordered_map>
#include <vector>


class ProblemGenerator
{
public:
	ProblemGenerator();
	ProblemGenerator(int NumberOfNodesAvailable, vector<Job> jobList);
private:
	int numberOfNodes;
	std::unordered_map<int, JobConfiguration> mapItems;
	friend class ResourceManager;
};

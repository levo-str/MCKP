#pragma once
#include<vector>
#include "Job.h"
#include "sackcomposition.h"
#include "ResourceManagerType.h"
#include "ResourceManager.h"

/**
* Main class to solve the malleable job shrinking problem
*/
class SolutionGenerator
{
public:
	SolutionGenerator();
	SolutionGenerator(const int& numberOfNodesNeeded, const vector<Job>& jobList, ResourceManagerType solverType);
	SackComposition serialSolve();
	SackComposition parallelSolve();

private:
	ResourceManager solver;
};

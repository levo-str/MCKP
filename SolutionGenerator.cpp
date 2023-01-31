#include "SolutionGenerator.h"
#include "ResourceManagerBB.h"
#include "resourceManagerDP.h"
#include "ProblemGenerator.h"

SolutionGenerator::SolutionGenerator() {

}

/**
* Builder to generate the MCKP solver corresponding to the malleable jobs shrinking problem.
* @args
* [numberOfNodesNeeded] number of nodes requirequuired by the new pending job.
* [jobList] List of the jobs already running.
* [solverType] algorithm to use to solve the MCKP.
*/
SolutionGenerator::SolutionGenerator(const int& numberOfNodesNeeded, const vector<Job>& jobList, ResourceManagerType solverType) {
	ProblemGenerator problem = ProblemGenerator(numberOfNodesNeeded,jobList);
	switch (solverType)
	{
	case DynamicProgramming:
		solver = ResourceManagerDP(problem.numberOfNodes, problem.mapItems);
	case BranchAndBound:
		solver = ResourceManagerBB(problem.numberOfNodes, problem.mapItems);
	default:
		throw("unsupported solver type");
		break;
	}
}
/**
* Solve the problem using serial solving
*/
SackComposition SolutionGenerator::serialSolve() {
	return solver.solveMckp();
}

SackComposition SolutionGenerator::parallelSolve() {
	return solver.solveMckpConcurrently();
}

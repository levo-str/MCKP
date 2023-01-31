#include "ProblemGenerator.h"

ProblemGenerator::ProblemGenerator() {

}

/**
* Builder to generate the MCKP items corresponding to the malleable jobs shrinking problem.
* @args
* [numberOfNodesNeeded] number of nodes requirequuired by the new pending job.
* [jobList] List of the jobs already running.
*/
ProblemGenerator::ProblemGenerator(int numberOfNodesNeeded, vector<Job> jobList) {
	this->numberOfNodes = numberOfNodesNeeded;
	for (Job job : jobList) {
		for (JobConfiguration jobConfiguration : job.generateJobConfigurations()) {
			mapItems[jobConfiguration.getId()] = jobConfiguration;
		}
	}
}

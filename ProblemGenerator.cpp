#include "ProblemGenerator.h"

ProblemGenerator::ProblemGenerator() {

}

ProblemGenerator::ProblemGenerator(int NumberOfNodesAvailable, vector<Job> jobList) {
	this->numberOfNodes = NumberOfNodesAvailable;
	for (Job job : jobList) {
		for (JobConfiguration jobConfiguration : job.generateJobConfigurations()) {
			mapItems[jobConfiguration.getId()] = jobConfiguration;
		}
	}
}

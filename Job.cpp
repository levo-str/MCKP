#include "Job.h"

atomic_uint32_t Job::current_task_number = 1; // added

Job::Job(int minResources, int currentResource, std::function<int(int)> func) : taskNumber(current_task_number++) {
	this->minResources = minResources;
	this->currentResources = currentResources;
	this->costFunction = func;
};

vector<JobConfiguration> Job::generateJobConfigurations() {
	vector<JobConfiguration> jobConfigurations;
	for (int i = 0; i <= currentResources - minResources; i++) {
		int profit = -costFunction(i);
		jobConfigurations.push_back(JobConfiguration(currentResources - i, profit, taskNumber));
	}
	return jobConfigurations;
};

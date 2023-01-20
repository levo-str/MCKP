#pragma once
#include <atomic>
#include <functional>
#include "jobconfiguration.h"
#include <vector>

using namespace std;

class Job
{
public:
	Job();
	Job(int minResources, int currentResource, std::function<int(int)> func);
	vector<JobConfiguration> generateJobConfigurations();

private:
	static atomic_uint32_t current_task_number; // added
	uint32_t taskNumber;
	int currentResources;
	int minResources;
	std::function<int(int)> costFunction;
};

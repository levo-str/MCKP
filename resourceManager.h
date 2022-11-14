#pragma once
#include "Task.h"
#include "jobconfiguration.h"
#include <vector>

using namespace std;

class ResourceManager
{
public:
	ResourceManager();
	vector<JobConfiguration> solveMckp();
private:
	int resourcesAvailable;
	vector<Task> listOfTask;
};


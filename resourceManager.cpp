#include "ResourceManager.h"
#include "ProblemGenerator.h"

ResourceManager::ResourceManager(int numberOfResources, std::unordered_map<int, JobConfiguration> mapItems) {
	this->numberResources = numberOfResources;
	this->mapItems = mapItems;
}

ResourceManager::ResourceManager(ProblemGenerator problem) {
	ResourceManager(problem.numberOfNodes, problem.mapItems); 
}

#include "Jobconfiguration.h"
#include <atomic> //std::atomic_uint32_t
#include <iostream>
#include <fstream>


atomic_uint32_t JobConfiguration::current_id = 1; // added

JobConfiguration::JobConfiguration() {

}

JobConfiguration::JobConfiguration(int r, int p, int t): id(current_id++) {
	resources = r;
	profit = p;
	task = t;
}

int JobConfiguration::getId() {
	return id;
}

int JobConfiguration:: getResources() {
	return resources;
}

int JobConfiguration::getProfit() {
	return profit;
}

int JobConfiguration::getTask() {
	return task;
}

JobConfiguration JobConfiguration::setId(int id) {
	this->id = id;
	return *this;
}

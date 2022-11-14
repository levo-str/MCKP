#pragma once
#include <atomic>

using namespace std;

class Task
{
public:
	Task();
	Task(int maxResource, int costFunction());
private:
	static atomic_uint32_t current_id; // added
	uint32_t id;
	int maxResource;
	int costFunction();
};

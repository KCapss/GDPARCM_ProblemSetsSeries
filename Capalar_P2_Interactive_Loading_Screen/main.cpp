#include <iostream>
#include <time.h>

#include "BaseRunner.h"
int main() {
	srand(time(0));

	BaseRunner runner;
	runner.run();
}
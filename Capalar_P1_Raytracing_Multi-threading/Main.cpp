#include "BaseRaytracing.h"


int main() {
	/*const auto processor_count = std::thread::hardware_concurrency();
	std::cout << "Thread Count: " << processor_count << std::endl;*/

	BaseRaytracing raytracing;
	raytracing.run();

	std::cout << "Done Main Thred" << std::endl;
	return 0;
}

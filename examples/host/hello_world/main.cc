
#include <iostream>

int main() {
	std::cout << "Hello world!\n";
#ifdef SPECIAL_MESSAGE
	std::cout << SPECIAL_MESSAGE << "\n";
#endif
	return 0;
}

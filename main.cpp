#include "RainbowSix.h"

int main(int argv, char *arg[]) {

	// argv[0] is the name of the exe
	if (argv > 1) {

		// hide the console
		if (arg[0] == "-s" or arg[0] == "-silent") {

			ShowWindow(GetConsoleWindow(), SW_HIDE);

		}

	}

	RainbowSix rainbowSix;
	rainbowSix.start();
	std::cin.get();
	return 0;

}
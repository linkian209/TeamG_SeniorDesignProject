#include <iostream>
#include "PWMManager.hpp"

using namespace std;

int main()
{
	cout << "Getting Singleton..." << endl;
	PWMMgr();
	cout << "Done!" << endl;

	return 0;
}

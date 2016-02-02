#include <iostream>
#include "../inc/PWMManager.h"

using namespace std;

int main()
{
	cout << "Getting Singleton..." << endl;
	getPWMMgr();
	cout << "Done!" << endl;

	return 0;
}

#include <iostream>
#include "PWMManager.hpp"
#include "BluetoothManager.hpp"

using namespace std;

int main()
{
	cout << "Getting Singleton..." << endl;
	PWMMgr().test();
	cout << "Done!" << endl;

	return 0;
}

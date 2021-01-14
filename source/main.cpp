#include <iostream>
using namespace std;

//Galaxy Includes:
#include "GameEngine.h"



int main()
{
	GameEngine engine;
	Object test(&engine);

	test.Talk();
	cout<<"hello world";
	return 0;
}
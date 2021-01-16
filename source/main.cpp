#include <iostream>
using namespace std;

//Galaxy Includes:
#include "GameEngine.h"


int main()
{
	GameEngine engine;
	Object test( &engine );

	test.Talk();
	return 0;
}
#include "Engine.h"

int main()
{
	// seed the pseudo number generator
	srand(static_cast<unsigned int>(time(0))); 

	Engine engine; // create engine object

	engine.run(); // run it

	return 0;

}
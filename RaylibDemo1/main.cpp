#include <raylib.h>
#include <cmath>
#include "BallBounce.h"
#include "MoveSquare.h"
#include "Particles.h"

int main()
{
	/*MoveSquare mover({ 600, 1100 }, 50, 50);
	mover.Main()*/;

	Particles particles;
	particles.Main();

	return 0;
}


#include <raylib.h>
#include <cmath>
#include "BallBounce.h"
#include "MoveSquare.h"

int main()
{
	/*MoveSquare mover({ 600, 1100 }, 50, 50);
	mover.Main()*/;

	BallBounce ballBounce;

	ballBounce.Main();

	return 0;
}


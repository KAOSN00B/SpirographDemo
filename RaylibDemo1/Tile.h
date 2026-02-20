#pragma once
#include <raylib.h>
#include <string>
using namespace std;

enum State
{
	Hidden,
	Flipped,
	Matched
};
struct Tile
{
	int number;
	int x = 0;
	int y = 0;
	int wh = 0; //width and height



	Tile(int x, int y, int wh, int num)
	{
		this->x = x;
		this->y = y;
		this->wh = wh;
		this->number = num;

	}

	State state = State::Hidden;
	void Update()
	{
		int fontSize = 80;
		int textY = y + wh / 2 - fontSize / 2;
		string text;
		int textWidth;
		int textX;
		Color rectColor;
		Color textColor;

		switch (state)
		{
		case Hidden:
			rectColor = BLUE;
			textColor = BLACK;
			text = "?";  // keep string alive
			textWidth = MeasureText(text.c_str(), fontSize);
			textX = x + wh / 2 - textWidth / 2;
			
			break;

		case Flipped:
			break;
		case Matched:
			break;

		default:
			break;
		}
		DrawRectangle(x, y, wh, wh, rectColor);
		DrawText(text.c_str(), textX, textY, fontSize, textColor);

		//DrawRectangle(x, y, wh, wh, BLUE);
		//std::string text = std::to_string(number);  // keep string alive
		//const char* cs = text.c_str();

		//int textWidth = MeasureText(cs, fontSize);
		//int textX = x + wh / 2 - textWidth / 2;
		//DrawText(cs, textX, textY, fontSize, BLACK);

		


		
	}

};
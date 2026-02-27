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
	Rectangle rect;


	Tile(int x, int y, int wh, int num)
	{
		this->x = x;
		this->y = y;
		this->wh = wh;
		this->number = num;
		rect = Rectangle{ (float)x, (float)y, (float)wh, (float)wh } ;
	}
	
	State state = State::Hidden;

	Rectangle GetRec()
	{
		return Rectangle(rect);
	}
	void Update()
	{
		int fontSize = 80;
		int textY = y + wh / 2 - fontSize / 2;
		string text;
		int textWidth;
		int textX;
		Color rectColor = WHITE;
		Color textColor = BLACK;

		switch (state)
		{
		case Hidden:
			rectColor = BLUE;
			text = "?";  // keep string alive
			textWidth = MeasureText(text.c_str(), fontSize);
			textX = x + wh / 2 - textWidth / 2;
			
			break;

		case Flipped:
			rectColor = RED;
			text = to_string(number);  // keep string alive
			textWidth = MeasureText(text.c_str(), fontSize);
			textX = x + wh / 2 - textWidth / 2;
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
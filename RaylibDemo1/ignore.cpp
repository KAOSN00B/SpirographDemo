
for (Circle& c : circles)
{

	c.cen.x += c.vel.x;
	c.cen.y += c.vel.y;


	if (c.cen.x <= radius || c.cen.x >= widthHieght - radius)
	{
		c.vel.x *= -1;
		c.vel.x += (float)GetRandomValue(-10, 10) / 50.0f;
	}

	if (c.cen.y <= radius || c.cen.y >= widthHieght - radius)
	{
		c.vel.y *= -1;
		c.vel.y += (float)GetRandomValue(-10, 10) / 50.0f;
	}

	DrawCircle(c.cen.x, c.cen.y, radius, c.color);
}


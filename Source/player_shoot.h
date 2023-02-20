#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class player_shoot // pociski gracza
{
public:
	int x;
	int y;
	int x1;
	int y1;
	int speed;
	int default_y;
	bool shoot;
	bool check;
	ALLEGRO_BITMAP* player_bullet;
	ALLEGRO_BITMAP* bullet_bitmap;
	player_shoot();
	~player_shoot();
	void draw(ALLEGRO_BITMAP* player_model, int player_x, int player_y);
};
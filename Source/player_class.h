#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class player_class // statek gracza
{
public:
	ALLEGRO_BITMAP* player_model;
	int x;
	int y;
	int vector_x;
	int vector_y;
	int speed;
	player_class();
	~player_class();
	void draw();
};

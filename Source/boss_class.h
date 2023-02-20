#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "collision.h"

struct bullet
{
	double x;
	double y;
};

class boss_class
{
	ALLEGRO_BITMAP* boss_model;
	ALLEGRO_BITMAP* boss_bullet1;
	ALLEGRO_BITMAP* boss_bullet2;
	bullet b[5][2];
	int x;
	int y;
	int hp;
	bool check;
public:
	boss_class();
	~boss_class();
	void boss_collision(ALLEGRO_BITMAP* player_model, int player_x, int player_y, ALLEGRO_BITMAP* bullet_model, int bullet_x, int bullet_y, int bullet_x1, int bullet_y1, bool* exit);
	void draw(int* wave, int* score, ALLEGRO_FONT* font);
};

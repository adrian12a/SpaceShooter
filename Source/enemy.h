#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "collision.h"

struct enemy_pos
{
	int x;
	int y;
	int y_bullet;
	bool alive;
};

class enemy
{
public:
	ALLEGRO_BITMAP* enemy_model;
	ALLEGRO_BITMAP* enemy_model2;
	ALLEGRO_BITMAP* enemy_bitmap1;
	ALLEGRO_BITMAP* enemy_bitmap2;
	ALLEGRO_BITMAP* enemy_bitmap3;
	ALLEGRO_BITMAP* enemy_bitmap4;
	ALLEGRO_BITMAP* enemy_bullet;
	enemy_pos en[5][3];
	int speed;
	int bullet_speed;
	int wave;
	int score;
	int direction;
	int timer;
	enemy();
	~enemy();
	void enemy_collision(ALLEGRO_BITMAP* player_model, int player_x, int player_y, ALLEGRO_BITMAP* bullet_model, int bullet_x, int bullet_y, int bullet_x1, int bullet_y1, bool* exit);
	int draw(ALLEGRO_FONT* font);
	void init();
	void clear_wave();
};

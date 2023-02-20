#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class bonus_class
{
	int x;
	int y;
	int wave_temp;
	int random;
	bool draw_flag;
	ALLEGRO_BITMAP* bonus;
	ALLEGRO_BITMAP* bonus1;
	ALLEGRO_BITMAP* bonus2;
	ALLEGRO_BITMAP* bonus3;
	ALLEGRO_BITMAP* bonus4;
	ALLEGRO_BITMAP* bonus5;
	ALLEGRO_BITMAP* bonus_bullet1;
	ALLEGRO_BITMAP* bonus_bullet2;
public:
	bonus_class();
	~bonus_class();
	void draw(int wave, int* score, bool* exit, ALLEGRO_BITMAP* player_model, int player_x, int player_y, ALLEGRO_BITMAP** bullet_model, int bullet_x, int bullet_y, int bullet_x1, int bullet_y1);
};

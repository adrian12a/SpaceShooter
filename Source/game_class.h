#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include "player_class.h"
#include "player_shoot.h"
#include "enemy.h"

class game_class // gra
{
	ALLEGRO_TIMER* timer;
	ALLEGRO_BITMAP* background;
public:
	game_class(); // konstruktor
	~game_class(); // destruktor
	int main(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, ALLEGRO_FONT* big_font, ALLEGRO_FONT* small_font); // glowna funkcja gry
};

#include "player_shoot.h"
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace std;

player_shoot::player_shoot() // konstruktor
{
	bullet_bitmap = al_load_bitmap("player_bullet.png"); // wczytanie bitmapy do pamieci
	al_convert_mask_to_alpha(bullet_bitmap, al_map_rgb(255, 0, 255)); // ustawienie przezroczystosci
	player_bullet = bullet_bitmap;
	default_y = 0 - al_get_bitmap_height(player_bullet);
	x = 0 - al_get_bitmap_width(player_bullet);
	y = default_y;
	x1 = 0 - al_get_bitmap_width(player_bullet);
	y1 = default_y; // poczatkowe pozycje pociskow poza obszarem okna
	shoot = false;
	check = false;
	speed = 15;
}

player_shoot::~player_shoot() // destrukotor - zwalnianie pamieci
{
	al_destroy_bitmap(bullet_bitmap);
}

void player_shoot::draw(ALLEGRO_BITMAP* player_model, int player_x, int player_y) // wyswietlenie pociskow
{
	if (shoot == true) // strzal gdy wcisnieto SPACE
	{
		if (y < default_y)
		{
			y = 720;
			x = player_x;
		}
		if (y == 360)
		{
			y1 = 720;
			x1 = player_x;
		}
		y -= speed;
		y1 -= speed;
		check = true;
	}
	if (check == true)
	{
		if (shoot == false && (y1 > default_y || y > default_y) && (y1 != 720 && y != 720)) // strzal gdy nie wcisnieto SPACE, ale pociski jeszcze nie opuscily obszaru gry
		{
			y -= speed;
			y1 -= speed;
		}
		if (shoot == false && y1 < default_y && y < default_y) // brak strzalu, reset pozycji pociskow
		{
			y = 720;
			x = player_x;
			y1 = 720;
			x1 = player_x;
		}
		if (y < player_y) // wyswietlanie pociskow
			al_draw_bitmap(player_bullet, x + (al_get_bitmap_width(player_model) / 2) - (al_get_bitmap_width(player_bullet) / 2), y, 0);
		else
			x = player_x;
		if (y1 < player_y)
			al_draw_bitmap(player_bullet, x1 + (al_get_bitmap_width(player_model) / 2) - (al_get_bitmap_width(player_bullet) / 2), y1, 0);
		else
			x1 = player_x;
	}
}
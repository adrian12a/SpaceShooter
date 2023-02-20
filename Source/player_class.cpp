#include "player_class.h"
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace std;

player_class::player_class()
{
	x = 640;
	y = 620;
	vector_x = 0;
	vector_y = 0;
	speed = 15;
	player_model = al_load_bitmap("player_model.png"); // wczytanie bitmapy do pamieci
	al_convert_mask_to_alpha(player_model, al_map_rgb(255, 0, 255)); // ustawienie przezroczystosci
}

player_class::~player_class()
{
	al_destroy_bitmap(player_model); // zwlanianie pamiêci
}

void player_class::draw() // wyswietlenie modelu gracza
{
	x += vector_x;
	y += vector_y;
	if (x < 0 - al_get_bitmap_width(player_model)) // zmiana pozycji gracza, gdy wyleci poza ekran na druga strone ekranu
		x = 1280;
	if (x > 1280 + al_get_bitmap_width(player_model))
		x = 0;
	if (y < 0 - al_get_bitmap_height(player_model))
		y = 720;
	if (y > 720 + al_get_bitmap_height(player_model))
		y = 0;
	al_draw_bitmap(player_model, x, y, 0);
}
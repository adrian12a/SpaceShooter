#include "bonus_class.h"
#include "collision.h"
#include <iostream>
#include <ctime>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace std;

bonus_class::bonus_class() // konstruktor
{
	random = 0;
	draw_flag = false;
	bonus1 = al_load_bitmap("bonus1.png"); // wczytanie bitmap do pamieci
	bonus2 = al_load_bitmap("bonus2.png");
	bonus3 = al_load_bitmap("bonus3.png");
	bonus4 = al_load_bitmap("bonus4.png");
	bonus5 = al_load_bitmap("bonus5.png");
	bonus_bullet1 = al_load_bitmap("bonus_bullet1.png");
	bonus_bullet2 = al_load_bitmap("bonus_bullet2.png");
	al_convert_mask_to_alpha(bonus1, al_map_rgb(255, 0, 255)); // ustawienie przezroczystosci
	al_convert_mask_to_alpha(bonus2, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(bonus3, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(bonus4, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(bonus5, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(bonus_bullet1, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(bonus_bullet2, al_map_rgb(255, 0, 255));
	bonus = bonus1; // ustawienie poczatkowej bitmapy bonusu - bonus1
	srand(time(0)); // ustawienie dla funkcji rand() sposobu losowania danych
	wave_temp = 0;
	x = -400; // poczatkowa wartosc x - wartosc ujemna oznacza, ze bonus znajduje sie poza obszarem okna
	y = -400; // poczatkowa wartosc y - wartosc ujemna oznacza, ze bonus znajduje sie poza obszarem okna
}

bonus_class::~bonus_class() // destruktor - zwalnianie pamieci
{
	al_destroy_bitmap(bonus1);
	al_destroy_bitmap(bonus2);
	al_destroy_bitmap(bonus3);
	al_destroy_bitmap(bonus4);
	al_destroy_bitmap(bonus5);
	al_destroy_bitmap(bonus_bullet1);
	al_destroy_bitmap(bonus_bullet2);
}

void bonus_class::draw(int wave, int* score, bool* exit, ALLEGRO_BITMAP* player_model, int player_x, int player_y, ALLEGRO_BITMAP** bullet_model, int bullet_x, int bullet_y, int bullet_x1, int bullet_y1) // wyswietlanie bonusow
{
	if (wave_temp != wave)  // losowanie bonusu
	{
		wave_temp = wave;
		random = rand() % 6;
		if (random == 1)
			bonus = bonus1;
		if (random == 2)
			bonus = bonus2;
		if (random == 3)
			bonus = bonus3;
		if (random == 4)
			bonus = bonus4;
		if (random == 5)
			bonus = bonus5;
		x = 50 + rand() % 600;
		y = -100;
		draw_flag = true;
	}
	if (y < 720 + al_get_bitmap_height(bonus)) // poruszanie sie bonusu w dol ekranu
		y += 5;
	if (collision(player_model, player_x, player_y, bonus, x, y) || collision(*bullet_model, bullet_x, bullet_y, bonus, x, y) || collision(*bullet_model, bullet_x1, bullet_y1, bonus, x, y)) // kolizje bonusu z graczem i pociskami gracza
	{
		if (draw_flag) // efekt dzialania bonusu
		{
			if (random == 1)
				*bullet_model = bonus_bullet1;
			if (random == 2)
				*bullet_model = bonus_bullet2;
			if (random == 3)
				*score += 100;
			if (random == 4)
				*score *= 2;
			if (random == 5)
				*exit = true;
			draw_flag = false;
		}
	}
	if (draw_flag) // wyswietlanie bonusu
		al_draw_bitmap(bonus, x, y, 0);
}
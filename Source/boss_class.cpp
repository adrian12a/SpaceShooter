#include "boss_class.h"
#include <iostream>
#include <ctime>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

boss_class::boss_class() // konstruktor
{
	srand(time(0)); // ustawienie dla funkcji rand() sposobu losowania danych
	boss_model = al_load_bitmap("boss_model.png"); // wczytanie bitmap do pamieci
	boss_bullet1 = al_load_bitmap("boss_bullet1.png");
	boss_bullet2 = al_load_bitmap("boss_bullet2.png");
	al_convert_mask_to_alpha(boss_model, al_map_rgb(255, 0, 255)); // ustawienie przezroczystosci
	al_convert_mask_to_alpha(boss_bullet1, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(boss_bullet2, al_map_rgb(255, 0, 255));
	for (int i = 0; i < 5; i++)
	{
		b[i][0] = { -400,-400 };
		b[i][1] = { -400,-400 };
	}
	x = 360;
	y = 20;
	hp = 10000;
	check = false;
}

boss_class::~boss_class() // destruktor - zwalnianie pamieci
{
	al_destroy_bitmap(boss_model);
	al_destroy_bitmap(boss_bullet1);
	al_destroy_bitmap(boss_bullet2);
}

void boss_class::boss_collision(ALLEGRO_BITMAP* player_model, int player_x, int player_y, ALLEGRO_BITMAP* bullet_model, int bullet_x, int bullet_y, int bullet_x1, int bullet_y1, bool* exit) // kolizje
{
	if (collision(bullet_model, bullet_x, bullet_y, boss_model, x, y) || collision(bullet_model, bullet_x1, bullet_y1, boss_model, x, y)) // zmniejszenie zdrowia bossa po trafieniu pociskiem
		hp = hp - 10;
	if (collision(player_model, player_x, player_y, boss_model, x, y)) // sprawdzenie kolizji bossa z graczem
		*exit = true;

	for (int i = 0; i < 5; i++) // sprawdzenie kolizji gracza z pociskami bossa
	{
		if (collision(player_model, player_x, player_y, boss_bullet1, b[i][0].x, b[i][0].y) || collision(player_model, player_x, player_y, boss_bullet2, b[i][1].x, b[i][1].y))
			*exit = true;
	}
}

void boss_class::draw(int* wave, int* score, ALLEGRO_FONT* font) // wyswietlenie bossa
{
	if (hp > 0)
	{
		if (check == false) // poruszanie sie po osi x w prawo bossa
		{
			x -= 2;
			if (x < 100)
				check = true;
		}
		if (check == true) // poruszanie sie po osi x w lewo bossa
		{
			x += 2;
			if (x > 1180)
				check = false;
		}
		for (int i = 0; i < 5; i++) // poruszanie sie pociskow bossa
			for (int j = 0; j < 2; j++)
			{
				if (b[i][j].y > 1000)
				{
					b[i][j].y = y;
					b[i][j].x = rand() % 1000;
				}
				if (b[i][j].x > 1200)
					b[i][j].x = -200;
				if (b[i][j].x < -200)
					b[i][j].x = 1200;
				b[0][0].x -= 0.5;
				b[1][0].x += 0.5;
				b[2][0].x -= 0.5;
				b[3][0].x += 0.5;
				b[4][0].x -= 0.5;
				b[i][0].y += 1;
				b[i][1].y += 2;
			}
		for (int i = 0; i < 5; i++) // wyswietlanie bitmap i napisow
		{
			al_draw_bitmap(boss_bullet1, b[i][0].x, b[i][0].y, 0);
			al_draw_bitmap(boss_bullet2, b[i][1].x, b[i][1].y, 0);
		}
		al_draw_bitmap(boss_model, x, y, 0);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 20, 0, "Wynik: %d", *score);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 40, 0, "Fala: %d", *wave);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 60, 0, "Boss HP: %d", hp);
	}
	else // zabicie bossa
	{
		*score += 1000;
		*wave += 1;
	}
}
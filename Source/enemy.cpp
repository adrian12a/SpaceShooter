#include "enemy.h"
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

using namespace std;

enemy::enemy() // kontruktor
{
	speed = 12;
	bullet_speed = 5;
	wave = 0;
	score = 0;
	timer = 0;
	direction = 1;
	for (int i = 0; i < 5; i++)
	{
		en[i][0] = { i * 150,100,100,false };
		en[i][1] = { i * 150,200,200,false };
		en[i][2] = { i * 150,300,300,false };
	}
	enemy_bitmap1 = al_load_bitmap("enemy_bitmap1.png"); // wczytanie bitmap
	enemy_bitmap2 = al_load_bitmap("enemy_bitmap2.png");
	enemy_bitmap3 = al_load_bitmap("enemy_bitmap3.png");
	enemy_bitmap4 = al_load_bitmap("enemy_bitmap4.png");
	enemy_bullet = al_load_bitmap("enemy_bullet.png");
	enemy_model = enemy_bitmap1;
	enemy_model2 = enemy_bitmap3;
	al_convert_mask_to_alpha(enemy_bitmap1, al_map_rgb(255, 0, 255)); // ustawienie przezroczystosci
	al_convert_mask_to_alpha(enemy_bitmap2, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(enemy_bitmap3, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(enemy_bitmap4, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(enemy_bullet, al_map_rgb(255, 0, 255));
}

enemy::~enemy() // destruktor - zwlanianie pamiêci
{
	al_destroy_bitmap(enemy_bullet);
	al_destroy_bitmap(enemy_bitmap1);
	al_destroy_bitmap(enemy_bitmap2);
	al_destroy_bitmap(enemy_bitmap3);
	al_destroy_bitmap(enemy_bitmap4);
}

void enemy::enemy_collision(ALLEGRO_BITMAP* player_model, int player_x, int player_y, ALLEGRO_BITMAP* bullet_model, int bullet_x, int bullet_y, int bullet_x1, int bullet_y1, bool* exit) // kolizje
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 3; j++)
		{
			if (en[i][j].alive)
			{
				if (collision(player_model, player_x, player_y, enemy_bullet, en[i][j].x, en[i][j].y_bullet)) // kolizja gracza z pociskiem wroga
					*exit = true;
				if (j == 0)
				{
					if (collision(player_model, player_x, player_y, enemy_model, en[i][j].x, en[i][j].y)) // kolizja gracza z wrogiem typu 1
						*exit = true;
				}
				else
				{
					if (collision(player_model, player_x, player_y, enemy_model2, en[i][j].x, en[i][j].y)) // kolizja gracza z wrogiem typu 2
						*exit = true;
				}
			}
			if (j == 0)
			{
				if (collision(bullet_model, bullet_x, bullet_y, enemy_model, en[i][j].x, en[i][j].y) || collision(bullet_model, bullet_x1, bullet_y1, enemy_model, en[i][j].x, en[i][j].y)) // kolizja wroga typu 1 z pociskiem gracza
					en[i][j].alive = false;
			}
			else
			{
				if (collision(bullet_model, bullet_x, bullet_y, enemy_model2, en[i][j].x, en[i][j].y) || collision(bullet_model, bullet_x1, bullet_y1, enemy_model2, en[i][j].x, en[i][j].y)) // kolizja wroga typu 2 z pociskiem gracza
					en[i][j].alive = false;
			}
		}
}

void enemy::init() // inicjalizacja wrogow w poszczegolnych falach
{
	if (en[0][0].x >= 1480 || en[4][0].x <= -200)
	{
		wave++;
		if (wave != 1)
			score += 100;
		if (wave >= 1)
		{
			en[0][0].alive = true;
			en[1][0].alive = true;
			en[2][0].alive = true;
		}
		if (wave >= 2)
		{
			en[3][0].alive = true;
			en[4][0].alive = true;
		}
		if (wave >= 3)
		{
			for (int i = 0; i < 5; i++)
				en[i][1].alive = true;
		}
		if (wave >= 4)
		{
			for (int i = 0; i < 5; i++)
				en[i][2].alive = true;
		}
	}
}

void enemy::clear_wave() // sprawdzenie czy gracz pokonal wszystkich wrogow w fali
{
	int check = 0;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 3; j++)
			if (en[i][j].alive)
				check++;
	if (check == 0)
		init();
}

int enemy::draw(ALLEGRO_FONT* font) // wyswietlenie wrogow
{
	clear_wave();
	timer++;
	if (timer == 144) // animacje wrogow
	{
		timer = 0;
		if (enemy_model == enemy_bitmap1)
		{
			enemy_model = enemy_bitmap2;
			enemy_model2 = enemy_bitmap4;
		}
		else
		{
			enemy_model = enemy_bitmap1;
			enemy_model2 = enemy_bitmap3;
		}
	}
	if (direction == 0) // poruszanie sie wrogow po osi x w lewo
	{
		if (en[0][0].x >= 1480)
			direction = 1;
	}
	else // poruszanie sie wrogow po osi x w prawo
	{
		if (en[4][0].x <= -200)
			direction = 0;
	}
	if (en[0][0].y_bullet == 750) // reset pozycji pociskow po opuszczenie obszaru gry
	{
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 3; j++)
				en[i][j].y_bullet = en[i][j].y;
	}
	for (int i = 0; i < 5; i++) // wyswietlenie pociskow i wrogow
		for (int j = 0; j < 3; j++)
		{
			if (en[i][j].alive)
			{
				al_draw_bitmap(enemy_bullet, en[i][j].x + al_get_bitmap_width(enemy_model) / 2 - al_get_bitmap_width(enemy_bullet) / 2, en[i][j].y_bullet, 0);
				if (j == 0)
					al_draw_bitmap(enemy_model, en[i][j].x, en[i][j].y, 0);
				else
					al_draw_bitmap(enemy_model2, en[i][j].x, en[i][j].y, 0);
			}
			if (direction == 0) // poruszanie sie pociskow i wrogow
				en[i][j].x += speed;
			else
				en[i][j].x -= speed;
			en[i][j].y_bullet += bullet_speed;
		}
	al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 20, 0, "Wynik: %d", score); // wyswietlenie tekstu
	al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 40, 0, "Fala: %d", wave);
	return score; // zwrocenie wyniku gracza
}
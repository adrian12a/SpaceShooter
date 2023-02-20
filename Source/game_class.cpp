#include "game_class.h"
#include "bonus_class.h"
#include "boss_class.h"
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

using namespace std;

game_class::game_class() // konstruktor
{
	timer = al_create_timer(1.0 / 60.0); // wskaznik timera
	background = al_load_bitmap("game_background.png"); // wczytanie bitmapy do pamieci
}

game_class::~game_class() // destruktor -zwalnianie pamieci
{
	al_destroy_timer(timer);
	al_destroy_bitmap(background);
}

int game_class::main(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, ALLEGRO_FONT* big_font, ALLEGRO_FONT* small_font) // glowna funkcja gry
{
	bool exit = false;
	bool exit_loop = false;
	player_class player;
	player_shoot bullet;
	enemy enemies;
	bonus_class bonus;
	boss_class boss;
	player.x = 640;
	player.y = 620;
	al_clear_to_color(al_map_rgb(0, 0, 0)); // wyczyszczenie aktualnego bufora ekranu
	al_flip_display(); // wyswietlenie aktualnego bufora na ekran
	al_register_event_source(queue, al_get_timer_event_source(timer)); // wprowadzeine rejestrowania obrazu przez kolejke
	al_start_timer(timer); // start timera
	al_flush_event_queue(queue); // wyczyszczenie kolejki
	while (!exit_loop)
	{
		al_wait_for_event(queue, &event); // oczekiwanie na wcisniecie przycisku
		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER: // aktywny timer
		{
			al_clear_to_color(al_map_rgb(0, 0, 0)); // wyczyszczenie aktualnego bufora ekranu
			if (exit == true)
			{
				al_draw_bitmap(background, 0, 0, 0);
				al_draw_textf(big_font, al_map_rgb(255, 255, 255), 480, 200, 0, "Wynik: %d", enemies.score); // tworzenie napisu
				al_draw_textf(big_font, al_map_rgb(255, 255, 255), 160, 400, 0, "Nacisnij Enter, aby powrocic do menu"); // tworzenie napisu
			}
			else
			{
				al_draw_bitmap(background, 0, 0, 0); // wyswietlenie tla
				bullet.draw(player.player_model, player.x, player.y); // wyswietlenie pociskow gracza
				if (enemies.wave != 5)
				{
					enemies.draw(small_font); // wyswietlenie przeciwnikow
					enemies.enemy_collision(player.player_model, player.x, player.y, bullet.player_bullet, bullet.x, bullet.y, bullet.x1, bullet.y1, &exit); // kolizje z wrogami
				}
				else
				{
					boss.draw(&enemies.wave, &enemies.score, small_font); // wyswietlanie bossa
					boss.boss_collision(player.player_model, player.x, player.y, bullet.player_bullet, bullet.x, bullet.y, bullet.x1, bullet.y1, &exit); // kolizje z bossem
				}
				player.draw(); // wyswietlenie statku gracza
				bonus.draw(enemies.wave, &enemies.score, &exit, player.player_model, player.x, player.y, &bullet.player_bullet, bullet.x, bullet.y, bullet.x1, bullet.y1); // wyswietlenie bonusow
			}
			al_flip_display(); // wyswietlenie aktualnego bufora na ekran
			break;
		}
		case ALLEGRO_EVENT_KEY_DOWN:
		{
			if (event.keyboard.keycode == ALLEGRO_KEY_UP) // wcisniety przycisk strzalka w gore
				player.vector_y -= player.speed;
			if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) // wcisniety przycisk strzalka w dol
				player.vector_y += player.speed;
			if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) // wcisniety przycisk strzalka w prawo
				player.vector_x += player.speed;
			if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) // wcisniety przycisk strzalka w lewo
				player.vector_x -= player.speed;
			if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) // wcisniety przycisk spacja
				bullet.shoot = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) // wcisniety przycisk escape
				exit = true;
			if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && exit == true) // wcisniety przycisk escape
				exit_loop = true;
			break;
		}
		case ALLEGRO_EVENT_KEY_UP:
		{
			if (event.keyboard.keycode == ALLEGRO_KEY_UP) // niewcisniety przycisk strzalka w gore
				player.vector_y += player.speed;
			if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) // niewcisniety przycisk strzalka w dol
				player.vector_y -= player.speed;
			if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) // niewcisniety przycisk strzalka w prawo
				player.vector_x -= player.speed;
			if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) // niewcisniety przycisk strzalka w lewo
				player.vector_x += player.speed;
			if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) // niewcisniety przycisk spacja
				bullet.shoot = false;
			break;
		}
		}
	}
	al_stop_timer(timer);
	return enemies.score;
}
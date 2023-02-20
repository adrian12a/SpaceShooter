#include "menu_class.h"
#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace std;

menu_class::menu_class() // konstruktor klasy
{
	menu_a = al_load_bitmap("menu_a.png"); // wczytywanie bitmapy menu 1 do pamieci
	menu_b = al_load_bitmap("menu_b.png"); // wczytywanie bitmapy menu 2 do pamieci
	menu_c = al_load_bitmap("menu_c.png"); // wczytywanie bitmapy menu 3 do pamieci
	menu_d = al_load_bitmap("menu_d.png"); // wczytywanie bitmapy menu 4 do pamieci
	menu_e = al_load_bitmap("menu_e.png"); // wczytywanie bitmapy menu 5 do pamieci
	help = al_load_bitmap("help.png"); // wczytywanie bitmapy menu 5 do pamieci
	v.push_back(menu_a); // wczytywanie bitmapy menu 1 do kontenera
	v.push_back(menu_b); // wczytywanie bitmapy menu 2 do kontenera
	v.push_back(menu_c); // wczytywanie bitmapy menu 3 do kontenera
	v.push_back(menu_d); // wczytywanie bitmapy menu 4 do kontenera
	v.push_back(menu_e); // wczytywanie bitmapy menu 5 do kontenera
	i = -1;
};

menu_class::~menu_class() // destruktor klasy
{
	al_destroy_bitmap(menu_a); // zwlanianie pamiêci
	al_destroy_bitmap(menu_b); // zwlanianie pamiêci
	al_destroy_bitmap(menu_c); // zwlanianie pamiêci
	al_destroy_bitmap(menu_d); // zwlanianie pamiêci
	al_destroy_bitmap(menu_e); // zwlanianie pamiêci
	al_destroy_bitmap(help); // zwlanianie pamiêci
};

void menu_class::redraw(ALLEGRO_BITMAP* bitmap) // wyswietlanie na ekran obrazu
{
	al_clear_to_color(al_map_rgb(0, 0, 0)); // wyczyszczenie aktualnego bufora ekranu
	al_draw_bitmap(bitmap, 0, 0, 0);  // wyswietlenie bitmapy "menu" na bufor ekranu
	al_flip_display(); // wyswietlenie aktualnego bufora na ekran
}

void menu_class::menu_up() // przejscie w gore w menu
{
	if (i != -2)
	{
		if (i == -1)
			i = 0;
		else
		{
			if (i == 0)
				i = 4;
			else
				i--;
		}
		redraw(v[i]);
	}
}

void menu_class::menu_down() // przejscie w dol w menu
{
	if (i != -2)
	{
		if (i == -1)
			i = 0;
		else
		{
			if (i == 4)
				i = 0;
			else
				i++;
		}
		redraw(v[i]);
	}
}

void menu_class::menu_start(bool* exit, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, ALLEGRO_FONT* big_font, ALLEGRO_FONT* small_font) // wybranie opcji w menu
{
	int score = 0;
	if (i == 0) // uruchomienie gry
	{
		i = -2;
		rank.insert_name(queue, event, big_font);
		score = game.main(queue, event, big_font, small_font);
		rank.insert_score(score);
		i = -1;
	}
	if (i == 1) // uruchomienie rankingu
	{
		i = -2;
		rank.view_rank(big_font);
	}
	if (i == 2) // zapisanie rankingu do pliku
	{
		i = -2;
		rank.save_rank(big_font);
	}
	if (i == 3) // wyswietlenie pomocy
	{
		i = -2;
		redraw(help);
	}
	if (i == 4) // wylaczenie programu
		*exit = true;
}
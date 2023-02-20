#include "ranking.h"
#include <iostream>
#include <fstream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

using namespace std;

ranking::ranking() // konstruktor
{
	rank_bitmap = al_load_bitmap("ranking.png"); // wczytanie bitmap do pamieci
	insert_name_bitmap = al_load_bitmap("insert_name.png");
	y = 200;
	for (int i = 0; i < 5; i++)
	{
		score[i] = 0;
		nick[i] = "brak nazwy";
	}
}

ranking::~ranking() // destruktor - zwalnianie pamieci
{
	al_destroy_bitmap(rank_bitmap);
	al_destroy_bitmap(insert_name_bitmap);
};

void ranking::sort_rank() // sortowanie rankingu
{
	for (int i = 0; i < 5; i++)
		for (int j = 1; j < 5 - i; j++)
			if (score[j - 1] < score[j])
			{
				swap(score[j - 1], score[j]);
				swap(nick[j - 1], nick[j]);
			}
}

void ranking::insert_name(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, ALLEGRO_FONT* font) // ekran wyboru nazwy gracza
{
	bool exit = false;
	char input;
	nick_player.clear();
	while (!exit)
	{
		al_clear_to_color(al_map_rgb(0, 0, 0)); // wyczyszczenie aktualnego bufora ekranu
		al_wait_for_event(queue, &event); // czekanie na wcisniecie przycisku
		if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && nick_player.size() != 0) // przejscie do gry po wcisnieciu ENTER
			exit = true;
		if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && nick_player.size() != 0) // kasowanie znakow po wcisnieciu BACKSPACE
			nick_player.resize(nick_player.size() - 1);
		input = event.keyboard.keycode + 96; // pobranie znaku od uzytkownika
		if (input > 96 && input < 123 && nick_player.size() < 15) // zapisanie nazwy gracza
		{
			if (nick_player.size() != 0)
			{
				if (input != nick_player.back())
					nick_player = nick_player + string(1, input);
			}
			else
				nick_player = nick_player + string(1, input);
		}
		al_draw_bitmap(insert_name_bitmap, 0, 0, 0); // wyswietlenie tla
		al_draw_textf(font, al_map_rgb(255, 255, 255), 260, 360, 0, "Wprowadz swoja nazwe: %s", nick_player.c_str()); // wyswietlenie napisu z nazwa gracza
		al_flip_display(); // wyswietlenie aktualnego bufora na ekran
	}
}

void ranking::insert_score(int score_player_from_game) // wprowadzenie nowego wyniku do rankingu
{
	score_player = score_player_from_game;
	if (score_player > score[4])
	{
		nick[4] = nick_player;
		score[4] = score_player;
		sort_rank();
	}
}

void ranking::view_rank(ALLEGRO_FONT* font) // ekran wyswietlenia rankingu
{
	y = 200;
	al_clear_to_color(al_map_rgb(0, 0, 0)); // wyczyszczenie aktualnego bufora ekranu
	al_draw_bitmap(rank_bitmap, 0, 0, 0); // wyswietlenie tla
	for (int i = 0; i < 5; i++)
	{
		al_draw_textf(font, al_map_rgb(173, 253, 245), 380, y, 0, "%d.", i + 1);// tworzenie napisu - indeks miejsca w rankingu
		al_draw_textf(font, al_map_rgb(173, 253, 245), 480, y, 0, "%s", nick[i].c_str());// tworzenie napisu - nazwa gracza
		al_draw_textf(font, al_map_rgb(173, 253, 245), 880, y, 0, "%d", score[i]);// tworzenie napisu - wynik
		y += 50;// wartosc y dla nastepnej pozycji w rankingu
	}
	al_flip_display(); // wyswietlenie aktualnego bufora na ekran
}

void ranking::save_rank(ALLEGRO_FONT* font) // zapisanie rankingu do pliku
{
	ofstream file("ranking.txt");
	file << "Miejsce" << "        " << "Wynik" << "        " << "Nazwa gracza" << endl;
	for (int i = 0; i < 5; i++)
	{
		if (score[i] == 0)
			file << i + 1 << "              " << score[i] << "            " << nick[i] << endl;
		if (score[i] < 1000 && score[i] > 0)
			file << i + 1 << "              " << score[i] << "          " << nick[i] << endl;
		if (score[i] >= 1000)
			file << i + 1 << "              " << score[i] << "         " << nick[i] << endl;
	}
	al_clear_to_color(al_map_rgb(0, 0, 0)); // wyczyszczenie aktualnego bufora ekranu
	al_draw_bitmap(insert_name_bitmap, 0, 0, 0); // wyswietlenie tla
	al_draw_textf(font, al_map_rgb(173, 253, 245), 140, 360, 0, "Zapisano ranking do pliku ranking.txt"); // tworzenie napisu
	al_draw_textf(font, al_map_rgb(173, 253, 245), 140, 400, 0, "Nacisnij ESC, aby powrocic do menu"); // tworzenie napisu
	al_flip_display(); // wyswietlenie aktualnego bufora na ekran
}
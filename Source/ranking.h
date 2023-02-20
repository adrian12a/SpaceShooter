#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

class ranking // ranking
{
	ALLEGRO_BITMAP* rank_bitmap;
	ALLEGRO_BITMAP* insert_name_bitmap;
	std::string nick[5];
	int score[5];
	int y;
	std::string nick_player;
	int score_player;
public:
	ranking(); // konstruktor
	~ranking(); // destruktor
	void sort_rank(); // sortowanie rankingu
	void insert_name(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, ALLEGRO_FONT* font); // ekran wyboru nazwy gracza
	void insert_score(int score_player_from_game); // wprowadzenie nowego wyniku do rankingu
	void view_rank(ALLEGRO_FONT* font); // ekran wyswietlenia rankingu
	void save_rank(ALLEGRO_FONT* font); // zapisanie rankingu do pliku
};
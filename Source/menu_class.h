#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "ranking.h"
#include "game_class.h"

class menu_class // menu
{
	ALLEGRO_BITMAP* menu_a; // bitmapa opcji 1 w menu
	ALLEGRO_BITMAP* menu_b; // bitmapa opcji 2 w menu
	ALLEGRO_BITMAP* menu_c; // bitmapa opcji 3 w menu
	ALLEGRO_BITMAP* menu_d; // bitmapa opcji 4 w menu
	ALLEGRO_BITMAP* menu_e; // bitmapa opcji 5 w menu
	ALLEGRO_BITMAP* help; // bitmapa pomocy
	std::vector <ALLEGRO_BITMAP*> v; // kontener bitmap
	ranking rank; // obiekt rankingu
	game_class game; // obiekt gry
public:
	int i; // zmienna przechowujaca aktualnie wybrana opcje menu
	menu_class(); // konstruktor klasy
	~menu_class(); // destruktor klasy
	void redraw(ALLEGRO_BITMAP* bitmap); // wyswietlanie na ekran obrazu
	void menu_up(); // przejscie w gore w menu
	void menu_down(); // przejscie w dol w menu
	void menu_start(bool* exit, ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, ALLEGRO_FONT* big_font, ALLEGRO_FONT* small_font); // wybranie opcji w menu
};
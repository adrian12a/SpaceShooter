#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "menu_class.h"

using namespace std;

int main()
{
	al_init(); // wprowadzenie biblioteki allegro
	al_init_image_addon(); // wprowadzenie dodatku obslugujacego obrazy
	al_install_keyboard(); // wprowadzenie obslugi klawiatury
	al_init_font_addon(); // wprowadzenie dodatku obslugujacego czcionki
	al_init_ttf_addon(); // wprowadzenie dodatku obslugujacego czcionki ttf
	ALLEGRO_DISPLAY* display = al_create_display(1280, 720); // wskaznik okna z gra
	al_set_window_title(display, "Space Invaders"); // ustawianie nazwy okna
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); // wskaznik kolejki
	ALLEGRO_BITMAP* menu_bitmap = al_load_bitmap("menu.png"); // wczytywanie bitmapy menu do pamieci
	al_register_event_source(queue, al_get_keyboard_event_source()); // wprowadzenie rejestrowania klawiatury przez kolejke
	al_register_event_source(queue, al_get_display_event_source(display)); // wprowadzenie rejestrowania obrazu przez kolejke
	ALLEGRO_FONT* big_font = al_load_ttf_font("ocr.ttf", 45, 0);// wskaznik na czcionke
	ALLEGRO_FONT* small_font = al_load_ttf_font("ocr.ttf", 15, 0);// wskaznik na czcionke

	ALLEGRO_EVENT event; // utworzenie eventu
	bool exit = false; // zmienna sprawadzajaca czy nalezy zakonczyc gre
	menu_class menu; // tworzenie obiektu menu
	menu.redraw(menu_bitmap); // wyswietlenie ekranu glownego menu
	while (!exit)
	{
		al_wait_for_event(queue, &event); // oczekiwanie na wcisniecie przycisku

		switch (event.type)
		{
		case ALLEGRO_EVENT_KEY_DOWN:
			if (event.keyboard.keycode == ALLEGRO_KEY_UP) // wcisniety przycisk strzalka w gore
			{
				menu.menu_up();
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) // wcisniety przycisk strzalka w dol
			{
				menu.menu_down();
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) // wcisniety przycisk enter
			{
				menu.menu_start(&exit, queue, event, big_font, small_font);
				if (menu.i == -1)
					menu.redraw(menu_bitmap); // wyswietlenie ekranu glownego menu
			}
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) // wcisniety przycisk escape
			{
				if (menu.i == -2)
				{
					menu.redraw(menu_bitmap); // wyswietlenie ekranu glownego menu
					menu.i = -1;
				}
				else
					exit = true;
			}
		}
	}

	al_destroy_display(display); // zwalnianie pamieci
	al_destroy_bitmap(menu_bitmap); // zwlanianie pamiêci
	al_destroy_event_queue(queue); // zwalnianie pamieci
	al_destroy_font(big_font);
	al_destroy_font(small_font);
	return 0;
}
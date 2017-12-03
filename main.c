
/*
main.c
------

Par Ekalawen, pour l'ENSEEIHT et plus précisément pour la Geek Week

Création : 25 février 2017
*/

#include "includes.h"

int main ()
{
	SDL_Surface *ecran = NULL ; // l'écran
    Input in; // les inputs
    memset(&in, 0, sizeof(in));
	int t_avt, t_act, t_debut ;
	int continuer = true ;
	char buf[5000] ;

	// l'initialisation
	SDL_Init(SDL_INIT_VIDEO) ;
	TTF_Init() ;
	SDL_WM_SetCaption("GreedHouse Bus !", NULL) ;
	SDL_WM_SetIcon(IMG_Load("images/bus_icone.png"), NULL) ;
	SDL_putenv("SDL_VIDEO_CENTERED=center") ; // je pense que ça centre la fenêtre
	srand(time(NULL)) ;
	SDL_EnableUNICODE(1) ;
	// init de l'écran
	ecran = SDL_SetVideoMode(SIZE_WINDOWS_WIDTH, SIZE_WINDOWS_HIGH, 32,
			SDL_HWSURFACE | SDL_DOUBLEBUF ) ; // on peut rajouter SDL_FULLSCREEN

	// créer la map
	Blocs *b ;
	b = initBlocs() ;
	Map *m = creerMap("images/pink_city_L1.png", b->nb_blocs, b->tailles_blocs,
			b->blocs, ecran) ;

	// créer le bus
	Bus *bus = creerBus("images/bus_vue_dessus_vert_80.png", POS_INI_BUS_X, POS_INI_BUS_Y) ;

	// créer les passagers
	Passagers *psg = initPassagers() ;

	t_debut = SDL_GetTicks() ;
	t_act = t_debut ;
	while (!in.quit && continuer)
	{
		// récupérer les évènements
        updateEvents(&in);

		// faire apparaître les passagers
		ajouterPassager(psg, m, bus) ;
		
		// déplacer le bus
		if(in.key[SDLK_z]) {
			if(polygoneInPolygone(bus->poly, m->ligneL1)) {
				deplacerBus(m, bus, bus->v_lin*2, 0) ;
			} else {
				deplacerBus(m, bus, bus->v_lin, 0) ;
			}
		}
		if(in.key[SDLK_s]) {
			if(polygoneInPolygone(bus->poly, m->ligneL1)) {
				deplacerBus(m, bus, -bus->v_lin, 0) ;
			} else {
				deplacerBus(m, bus, -bus->v_lin / 2, 0) ;
			}
		}
		if(in.key[SDLK_q]) {
			deplacerBus(m, bus, 0, bus->v_rot) ;
		}
		if(in.key[SDLK_d]) {
			deplacerBus(m, bus, 0, -bus->v_rot) ;
		}
		deplacerPassagers(psg, m, bus) ;
		recupererPassagersBus(bus, psg) ;
		ramenerPassagers(m, bus) ;
		
		// récupérer les passagers
		
		// quand je clique, affiche la position de la souris sur la map 
		if(in.button[SDL_BUTTON_LEFT]) {
			in.button[SDL_BUTTON_LEFT] = 0 ;
			printf("%d %d\n", in.mouseX + (int)m->standpoint->x,
				   in.mouseY + (int)m->standpoint->y) ;
		}
	
		// afficher le tout
		majStandpointMap(m, bus) ;
		afficherMap(ecran, m) ;
		afficherPassagers(ecran, m, psg) ;
		afficherBus(ecran, m, bus) ;
		// actualiser l'écran
		SDL_Flip(ecran) ;

		// on gère les FPS
		t_avt = t_act ;
		t_act = SDL_GetTicks() ;
		sprintf(buf, "Il reste %d secondes !\n", (TEMPS_JEU - t_act + t_debut) / 1000) ;
		changerTexte(m->texte_temps_jeu, buf) ;
		sprintf(buf, "Vous avez convertit %d voitures !\n", m->passagers_recuperes) ;
		changerTexte(m->texte_convertit, buf) ;
		if(t_act - t_avt < 1000 / FPS)
			SDL_Delay(1000/FPS - (t_act - t_avt)) ;
		if(t_act - t_debut > TEMPS_JEU)
			continuer = false ;
	}
	if(!continuer) {
		/*
		sprintf(buf, "FELICITATION !!! Vous avez réussi à convertir %d chauffeur polluants ! Vous avez grandement réduit l'empreinte carbonne de cette Toulouse ! C'est peut-être un record !", m->passagers_recuperes) ;
		changerTexte(m->texte_convertit, buf) ;
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)) ;
		Pos *pos = malloc(sizeof(Pos)) ;
		pos->x = m->w / 2 - m->texte_convertit->surface->w / 2 ;
		pos->y = m->h / 2 - m->texte_convertit->surface->h / 2 ;
		SDL_Blit(m->texte_convertit->surface, NULL, ecran, pos) ;
		SDL_Flip(ecran) ;
		*/

		printf("\n\nCONGRATULAION !!!You succed in convert %d polluting cars !\nYou participated a lot to raduce the carbon footprint of the great ligne LA of the amazing Pink City of Toulouse !`\n\n", m->passagers_recuperes) ;
		//SDL_Delay(10000) ;
	}

	// on quitte proprement
	SDL_EnableUNICODE(0) ;
	TTF_Quit() ;
	SDL_Quit() ;
	return EXIT_SUCCESS ;
}





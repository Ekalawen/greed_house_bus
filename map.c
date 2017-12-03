
#include "includes.h"

Map* creerMap(char *nom_fond_ecran,
			  int nb_poly,
			  int *tailles_polys,
			  Point ***sommets_polygones,
			  SDL_Surface *ecran) {
	// initialisation
	FILE *F ;
	int i, j, nb;
	Sint16 *vx, *vy ;
	double *vxd, *vyd, x, y ;
	Point **t = malloc(sizeof(Point) * 38) ;
	Pos *taille_poly, *pos = malloc(sizeof(Pos)) ;
	Map *m = malloc(sizeof(Map)) ;

	// le point de vue
	m->standpoint = malloc(sizeof(Pos)) ;
	m->standpoint->x = POS_DEPART_X ;
	m->standpoint->y = POS_DEPART_Y ;
	m->standpoint->w = SIZE_WINDOWS_WIDTH ;
	m->standpoint->h = SIZE_WINDOWS_HIGH ;

	// l'image de fond
	m->fond = IMG_Load(nom_fond_ecran) ;
	// on multiplie la taille du fond, sans la tourner, et en lissant les bords
	m->fond = rotozoomSurface(m->fond, 0, ZOOM_MAP, 1) ;
	
	// taille de la map
	m->w = m->fond->w ;
	m->h = m->fond->h ;

	// les polygones
	m->nb_poly = nb_poly ;
	m->poly = malloc(sizeof(Polygone) * nb_poly) ;
	for(i = 0 ; i < nb_poly ; i++) {
		m->poly[i] = creerPolygone(tailles_polys[i], sommets_polygones[i]) ;
	}

	// les surfaces des polygones
	m->surf_poly = malloc(sizeof(SDL_Surface) * nb_poly) ;
	for(i = 0 ; i < nb_poly ; i++) {
		// initialiser leurs surfaces
		taille_poly = getPositionPoly(m->poly[i]) ;
		m->surf_poly[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, taille_poly->w, taille_poly->h, 32, 0, 0, 0, 0) ;

		// dessiner les polygones
		// on récupère les valeurs en x et en y
		vx = malloc(sizeof(Sint16) * m->poly[i]->n) ;
		vy = malloc(sizeof(Sint16) * m->poly[i]->n) ;
		vxd = getVxPoly(m->poly[i]) ;
		vyd = getVyPoly(m->poly[i]) ;
		for(j = 0 ; j < m->poly[i]->n ; j++){
			// on décale de manière à afficher dans la surface
			vxd[j] -= taille_poly->x ;
			vyd[j] -= taille_poly->y ;
			// on passe en Sint16 (ça c'était grave casse-couille !)
			vx[j] = vxd[j];
			vy[j] = vyd[j];
		}

		// on imprime le polygone
		filledPolygonRGBA(m->surf_poly[i], vx, vy, m->poly[i]->n, 255, 100, 100, 255) ;

		// on rend tous le non-polygone totalement transparent
		SDL_SetColorKey(m->surf_poly[i], SDL_SRCCOLORKEY, SDL_MapRGB(m->surf_poly[i]->format, 0, 0, 0)) ;

		// on rend partiellement transparent le reste
		SDL_SetAlpha(m->surf_poly[i], SDL_SRCALPHA, 175) ;
	}

	// les checkpoints
	t[0] = creerPointXY(3787 - 300, 1526 - 300) ;
	t[1] = creerPointXY(3787 + 300, 1526 - 300) ;
	t[2] = creerPointXY(3787 + 300, 1526 + 300) ;
	t[3] = creerPointXY(3787 - 300, 1526 + 300) ;
	m->checkpoint[0] = creerPolygone(4, t) ;
	t[0] = creerPointXY(6994 - 300, 3490 - 300) ;
	t[1] = creerPointXY(6994 + 300, 3490 - 300) ;
	t[2] = creerPointXY(6994 + 300, 3490 + 300) ;
	t[3] = creerPointXY(6994 - 300, 3490 + 300) ;
	m->checkpoint[1] = creerPolygone(4, t) ;
	m->image_checkpoint = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 600, 32, 0, 0, 0, 0) ;
	SDL_FillRect(m->image_checkpoint, NULL, SDL_MapRGB(ecran->format, 0, 255, 0)) ;
	SDL_SetAlpha(m->image_checkpoint, SDL_SRCALPHA, 100) ;
	m->passagers_recuperes = 0 ;

	// la ligne L1
	F = fopen("map/ligne.txt", "r") ;
	if(F == NULL)
		printf("Echec du chargement du fichier de la ligne L1 !\n") ;
	fscanf(F, "%d", &nb) ;
	for(i = 0 ; i < nb ; i++) {
		fscanf(F, "%lf %lf", &x, &y) ;
		t[i] = creerPointXY(x, y) ;
	}
	m->ligneL1 = creerPolygone(nb, t) ;
	pos = getPositionPoly(m->ligneL1) ;
	m->image_ligneL1 = SDL_CreateRGBSurface(SDL_HWSURFACE, pos->w, pos->h, 32, 0, 0, 0, 0) ;
	vx = malloc(sizeof(Sint16) * nb) ;
	vy = malloc(sizeof(Sint16) * nb) ;
	vxd = getVxPoly(m->ligneL1) ;
	vyd = getVyPoly(m->ligneL1) ;
	for(j = 0 ; j < nb ; j ++) {
		// on décale de manière à afficher dans la surface
		vxd[j] -= pos->x ;
		vyd[j] -= pos->y ;
		// on passe en Sint16
		vx[j] = vxd[j] ;
		vy[j] = vyd[j] ;
	}
	filledPolygonRGBA(m->image_ligneL1, vx, vy, nb, 255, 140, 0, 255) ;
	SDL_SetColorKey(m->image_ligneL1, SDL_SRCCOLORKEY, SDL_MapRGB(m->image_ligneL1->format, 0, 0, 0)) ;
	SDL_SetAlpha(m->image_ligneL1, SDL_SRCALPHA, 175) ;
	
	// le texte
	m->texte_temps_jeu = malloc(sizeof(s_texte)) ;
    inits_texte(m->texte_temps_jeu, 0, 0, 0, "Le temps restant est ...", "mermaid.ttf", 20, 0, 0, 100);

	m->texte_convertit = malloc(sizeof(s_texte)) ;
	inits_texte(m->texte_convertit, 0, 0, 0, "une chaine est si et seulement sinon vide", "mermaid.ttf", 20, 0, 0, 100) ;

	return m ;
}

Blocs* initBlocs() {
	int i, j ;
	double x, y ;
	Blocs *b = malloc(sizeof(Blocs)) ;

	// ouvrir le fichier de lecture
	FILE *F = fopen("map/blocs.txt", "r") ;
	if (F == NULL)
		fprintf(stderr, "Echec du chargement du fichier des blocs de la map !\n") ;

	// initialiser le nombre de polygones
	fscanf(F, "%d", &b->nb_blocs) ;

	// pour chaque polygone
	b->tailles_blocs = malloc(sizeof(int) * b->nb_blocs) ;
	b->blocs = malloc(sizeof(Point*) * b->nb_blocs) ;
	for(i = 0 ; i < b->nb_blocs ; i++) {
		// récupérer sa taille
		fscanf(F, "%d", &b->tailles_blocs[i]) ;
		// puis récupérer ses coordonnées
		b->blocs[i] = malloc(sizeof(Point) * b->tailles_blocs[i]) ;
		for(j = 0 ; j < b->tailles_blocs[i] ; j++) {
			fscanf(F, "%lf %lf", &x, &y) ;
			b->blocs[i][j] = creerPointXY(x, y) ;
		}
	}

	// fermer le fichier
	fclose(F) ;
	return b ;
}

void afficherMap(SDL_Surface *ecran, Map *m) {
	int i ;
	Pos *pos = malloc(sizeof(Pos)) ;
	pos->x = 0 ;
	pos->y = 0 ;
	pos->w = m->fond->w ;
	pos->h = m->fond->h ;

	// effacer l'écran actuel
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, rand()%255, 0, 0)) ;

	// afficher le fond
	SDL_Blit(m->fond, m->standpoint, ecran, pos) ;

	// afficher les polygones
	for(i = 0 ; i < m->nb_poly ; i++) {
		pos = getPositionPoly(m->poly[i]) ;
		pos->x -= m->standpoint->x ;
		pos->y -= m->standpoint->y ;
		SDL_Blit(m->surf_poly[i], NULL, ecran, pos) ;
	}

	// afficher les checkpoints
	pos = getPositionPoly(m->checkpoint[0]) ;
	pos->x -= m->standpoint->x ;
	pos->y -= m->standpoint->y ;
	SDL_Blit(m->image_checkpoint, NULL, ecran, pos) ;
	pos = getPositionPoly(m->checkpoint[1]) ;
	pos->x -= m->standpoint->x ;
	pos->y -= m->standpoint->y ;
	SDL_Blit(m->image_checkpoint, NULL, ecran, pos) ;

	// afficher la ligne L1
	pos = getPositionPoly(m->ligneL1) ;
	pos->x -= m->standpoint->x ;
	pos->y -= m->standpoint->y ;
	SDL_Blit(m->image_ligneL1, NULL, ecran, pos) ;

	// afficher le texte
	pos->x = 50 ;
	pos->y = 50 ;
	SDL_Blit(m->texte_temps_jeu->surface, NULL, ecran, pos) ;
	pos->y = 100 ;
	SDL_Blit(m->texte_convertit->surface, NULL, ecran, pos) ;
}


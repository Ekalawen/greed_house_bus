
#include "includes.h" 


bool egalDouble(double a, double b) {
	return (a > b - EPSILON) && (a < b + EPSILON) ;
}

double absd(double a) {
	if (a > 0)
		return a ;
	else
		return -a ;
}

double signe(double a) {
	if (a >= 0)
		return 1 ;
	else 
		return -1 ;
}

double max(double a, double b) {
	if (a > b)
		return a ;
	else
		return b ;
}

double min(double a, double b) {
	if (a > b)
		return b ;
	else
		return a ;
}

double maxt(double *t, int n) {
	double m = t[0] ;	
	for(int i = 1 ; i < n ; i++) {
		if (t[i] > m) { 
			m = t[i] ;
		}
	}
	return m ;
}

double mint(double *t, int n) {
	double m = t[0] ;	
	for(int i = 1 ; i < n ; i++) {
		if (t[i] < m) {
			m = t[i] ;
		}
	}
	return m ;
}

double imaxt(double *t, int n) {
	double m = t[0] ;	
	int indice = 0 ;
	for(int i = 1 ; i < n ; i++) {
		if (t[i] > m) {
			m = t[i] ;
			indice = i ;
		}
	}
	return indice ;
}

double imint(double *t, int n) {
	double m = t[0] ;	
	int indice = 0 ;
	for(int i = 1 ; i < n ; i++) {
		if (t[i] < m) {
			m = t[i] ;
			indice = i ;
		}
	}
	return indice ;
}

void trieInsertion(double *t, int n) {
	int i;
	int indice_min ;
	double tmp ;
	for(i = 0 ; i < n ; i++){
		indice_min = imint(t + i, n - i) + i;
		tmp = t[i] ;
		t[i] = t[indice_min] ;
		t[indice_min] = tmp ;
	}
}

int randint(int min, int max) {
	return rand() % (max - min + 1) + min ;
}

int entreStrict(double elem, double x1, double x2) {
	return (x1 < elem && elem < x2) || (x2 < elem && elem < x1) ;
}

int entreLarge(double elem, double x1, double x2) {
	return (x1 <= elem && elem <= x2) || (x2 <= elem && elem <= x1) ;
}

Pos* initPos(double x, double y, double w, double h) {
	Pos *p = malloc(sizeof(Pos)) ;

	p->x = x ;
	p->y = y ;
	p->w = w ;
	p->h = h ;

	return p ;
}

void SDL_Blit(SDL_Surface *surface, Pos *rect, SDL_Surface *ecran, Pos *pos) {
    SDL_Rect posRect;
    posRect.x = (int)pos->x;
    posRect.y = (int)pos->y;
    posRect.w = (int)pos->w;
    posRect.h = (int)pos->h;
    if(rect != NULL)
    {
        SDL_Rect rectangleRect;
        rectangleRect.x = (int)rect->x;
        rectangleRect.y = (int)rect->y;
        rectangleRect.w = (int)rect->w;
        rectangleRect.h = (int)rect->h;
        SDL_BlitSurface(surface, &rectangleRect, ecran, &posRect);
    }
    else
        SDL_BlitSurface(surface, NULL, ecran, &posRect);
}

void inits_texte (s_texte *t, int r, int g, int b, char message[], char police[], int taille, int x, int y, int longueur)
{
    t->couleur.r = r;
    t->couleur.g = g;
    t->couleur.b = b;
    t->pos.x = x;
    t->pos.y = y;
    t->n = longueur;
    t->curseur = 0;
    t->taille = taille;
    t->police = TTF_OpenFont(police, taille);
    if(t->police == NULL)
        fprintf(stderr, "Une police a mal été initialisé");
    t->chaine = malloc(t->n * sizeof(char));
    strcpy(t->chaine, message);
    t->surface = TTF_RenderUTF8_Blended(t->police, message, t->couleur);
    if(t->surface == NULL)
        fprintf(stderr, "Une surface de texte a été mal initialisé");
    t->pos.w = t->surface->w;
    t->pos.h = t->surface->h;
}

void changerTexte(s_texte *txt, char newTexte[])
{
    strcpy(txt->chaine, newTexte);
    SDL_FreeSurface(txt->surface);
    txt->surface = TTF_RenderUTF8_Blended(txt->police, txt->chaine, txt->couleur);
}

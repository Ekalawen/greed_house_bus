
#include "includes.h"


Bus* creerBus(char *nomImageBus, double x_ini, double y_ini) {
	// déclaration
	Point **point_bus = malloc(sizeof(Point*) * 4) ;
	Bus *bus = malloc(sizeof(Bus)) ;
	bus->pos = malloc(sizeof(Pos)) ;

	// initialisation
	
	// position initiale, le centre du bus
	bus->pos->x = x_ini ;
	bus->pos->y = y_ini ;
	bus->pos->w = LARGEUR_BUS ;
	bus->pos->h = LONGEUR_BUS ;
	// le polygone du bus, centré AUTOUR de bus->pos
	point_bus[0] = creerPointXY(bus->pos->x - bus->pos->w / 2, bus->pos->y - bus->pos->h / 2) ;
	point_bus[1] = creerPointXY(bus->pos->x + bus->pos->w / 2, bus->pos->y - bus->pos->h / 2) ;
	point_bus[2] = creerPointXY(bus->pos->x + bus->pos->w / 2, bus->pos->y + bus->pos->h / 2) ;
	point_bus[3] = creerPointXY(bus->pos->x - bus->pos->w / 2, bus->pos->y + bus->pos->h / 2) ;
	bus->poly = creerPolygone(4, point_bus) ;
	bus->rot = PI / 2 ; // on est dirigé vers le haut
	// RAPPEL : le repère est dans le sens TRIGONOMÉTRIQUE !

	// caractéristiques de bases
	bus->v_lin = VITESSE_LINEAIRE_BUS ;
	bus->v_rot = VITESSE_ROTATION_BUS ;
	bus->image = IMG_Load(nomImageBus) ;
	bus->image_originelle = IMG_Load(nomImageBus) ; 
	if(bus->image == NULL)
		printf("Echec du chargement de l'image du bus à l'adresse \n%s\n", nomImageBus) ;
	if(bus->image_originelle == NULL)
		printf("Echec du chargement de l'image_originelle du bus à l'adresse \n%s\n", nomImageBus) ;

	// le nombre de passagers
	bus->nb_passagers = 0 ;
	// récupère l'image du mini passager
	bus->image_passagers = IMG_Load("images/voiture_polluante_rouge_80.png") ;
	if(bus->image_passagers == NULL) 
		printf("Echec du chargement de l'image du passager du bus !\n") ;
	bus->image_passagers = rotozoomSurface(bus->image_passagers, 0, 1.0/4.0, 1) ;
	
	return bus ;
}

int deplacerBus(Map *m, Bus* bus, double avancee, double rotation) {
	double i ;
	double nv_pas ;
	double mv_x, mv_y ;
	double tmp_rot ;
	// rotation fullmouvement
	if(!rotationBus(m, bus, rotation)) {
		// si pas possible, faire la rotation la plus ample possible
		i = PI / 180 ; // i est échantilloné en degrés
		nv_pas = rotation - signe(rotation)*i ;
		while(signe(nv_pas) * signe(rotation) > 0 && !rotationBus(m, bus, nv_pas)) {
			i += PI / 180 ;
			nv_pas = rotation - signe(rotation)*i ;
		}
	}
	// avancée fullmouvement
	if(!avancerBus(m, bus, avancee)) {
		// si pas possible, décomposer le mouvement sur chacun des 2 axes
		RTtoXY(avancee, bus->rot, &mv_x, &mv_y) ;
		// faire l'avancée la plus ample possible pour chacun des 2 mouvements
		// selon les x, j'ai choisi x en premier de façon totalement arbitraire,
		// il faudrait peut-être faire les deux mouvements en même temps
		i = 0 ;
		nv_pas = mv_x - signe(mv_x)*i ;
		tmp_rot = bus->rot ;
		bus->rot = 0 ;
		while(signe(nv_pas) * signe(mv_x) > 0 && !avancerBus(m, bus, nv_pas)) {
			i ++ ;
			nv_pas = mv_x - signe(mv_x)*i ;
		}
		// selon les y
		i = 0 ;
		nv_pas = mv_y - signe(mv_y)*i ;
		bus->rot = PI / 2 ;
		while(signe(nv_pas) * signe(mv_y) > 0 && !avancerBus(m, bus, nv_pas)) {
			i ++ ;
			nv_pas = mv_y - signe(mv_y)*i ;
		}
		bus->rot = tmp_rot ;
	}
}	

int avancerBus(Map *m, Bus *bus, double avancee) {
	int i ;
	int collision = false ; // au début, le bus n'est pas en collision
	double rotation_indirecte = -bus->rot ;
	Point *p_tmp ;
	Polygone *next_poly ;

	// créer un polygone fictif ayant effectué l'avancée
	next_poly = creerPolygone(bus->poly->n, getSommetsPoly(bus->poly)) ;
	translaterPolygoneRT(next_poly, avancee, rotation_indirecte) ;

	// si l'avancée n'entre pas en collision avec le décord
	for(i = 0 ; i < m->nb_poly ; i++) {
		if(polygoneInPolygone(next_poly, m->poly[i])) {
			 printf("COLLISION ! avec le polygone %d !\n", i);
			collision = true ;
		}
	}
	// alors faire avancer le bus
	if(!collision) {
		// on translate son polynome
		translaterPolygoneRT(bus->poly, avancee, rotation_indirecte) ;
		// on translate sa position
		p_tmp = creerPointXY(bus->pos->x, bus->pos->y) ;
		translaterPointRT(p_tmp, avancee, rotation_indirecte) ;
		bus->pos->x = p_tmp->x ;
		bus->pos->y = p_tmp->y ;
		return true ; // SUCCESS
	// sinon ne rien faire
	} else {
		return false ; // ECHEC
	}
}

int rotationBus(Map *m, Bus *bus, double rotation) {
	int i ;
	double collision = false ; // au début, le bus n'est pas en collision
	double coef_avant, coef_arriere ;
	double x_centre, y_centre ;
	double rotation_indirecte = -rotation ;
	Point *p_tmp ;
	Point *centreDeRotation ;
	Point *centreArriere ;
	Polygone *next_poly ;

	// récupérer le centre de rotation
	// on veut un centre sur la ligne médiane avant/arrière du bus, mais plus ou
	// moins en avant en fonction de la pondération CENTRE_ROTATION_PONDERATION
	coef_avant = (bus->poly->a[0]->p1->x + bus->poly->a[1]->p1->x) / 2;
	coef_arriere = (bus->poly->a[2]->p1->x + bus->poly->a[3]->p1->x) / 2;
	x_centre = coef_avant * (1 - CENTRE_ROTATION_PONDERATION) + coef_arriere * CENTRE_ROTATION_PONDERATION ;
	coef_avant = (bus->poly->a[0]->p1->y + bus->poly->a[1]->p1->y) / 2;
	coef_arriere = (bus->poly->a[2]->p1->y + bus->poly->a[3]->p1->y) / 2;
	y_centre = coef_avant * (1 - CENTRE_ROTATION_PONDERATION) + coef_arriere * CENTRE_ROTATION_PONDERATION ;
	centreArriere = creerPointXY(x_centre, y_centre) ;

	// créer un polygone ayant effectué la rotation
	next_poly = creerPolygone(bus->poly->n, getSommetsPoly(bus->poly)) ;
	rotationPolygone(next_poly, rotation_indirecte, centreArriere) ;

	// si la rotation n'entre pas en collision avec le décord
	for(i = 0 ; i < m->nb_poly ; i++) {
		if(polygoneInPolygone(next_poly, m->poly[i])) {
			collision = true ;
		}
	}
	// alors faire la rotation pour le bus
	if(!collision) {
		// on fait tourner son polynome
		rotationPolygone(bus->poly, rotation_indirecte, centreArriere) ;
		// on récupère la nouvelle position
		p_tmp = creerPointXY(bus->pos->x, bus->pos->y) ;
		rotationPoint(p_tmp, rotation_indirecte, centreArriere) ;
		bus->pos->x = p_tmp->x ;
		bus->pos->y = p_tmp->y ;
		bus->pos->w = bus->image->w ;
		bus->pos->h = bus->image->h ;
		// on met à jour la rotation
		bus->rot += rotation ;
		return true ; // SUCCESS
	// sinon ne rien faire
	} else {
		return false ; // ECHEC
	}
}

void afficherBus(SDL_Surface *ecran, Map *m, Bus *bus) {
	int i ;
	int x, y ;
	Pos *pos = malloc(sizeof(Pos)) ;
	Pos *pos_affichage_bus = malloc(sizeof(Pos)) ;
	double rotation_rotozoom ;

	// on ajoute les passagers sur l'image
	bus->image = IMG_Load("images/bus_vue_dessus_vert_80.png") ;
	if(bus->image == NULL) 
		printf("Echec de chargement d'une image dans afficherBus !\n") ;
	for(i = 0 ; i < bus->nb_passagers ; i++) {
		x = 10 + (i%2)*30 ;
		y = 60 + (i/2)*40 ;
		pos->x = x ;
		pos->y = y ;
		pos->w = 40 ;
		pos->h = 40 ;
		SDL_Blit(bus->image_passagers, NULL, bus->image, pos) ;
	}

	// on recalcul la rotation de l'image
	// on fait tourner l'image
	// rotozoom est en sens directe (trigo !) et son unité est le degré
	// rotozoom fait tourner l'image autour de son centre
	rotation_rotozoom = (bus->rot - PI/2)*180/PI ;
	bus->image = rotozoomSurface(bus->image, rotation_rotozoom, 1, 1) ;
	bus->pos->w = bus->image->w ;
	bus->pos->h = bus->image->h ;

	// on affiche le rectangle de contact
	Sint16 tx[] = {bus->poly->a[0]->p1->x,
				   bus->poly->a[1]->p1->x,
				   bus->poly->a[2]->p1->x,
				   bus->poly->a[3]->p1->x} ;
	Sint16 ty[] = {bus->poly->a[0]->p1->y,
				   bus->poly->a[1]->p1->y,
				   bus->poly->a[2]->p1->y,
				   bus->poly->a[3]->p1->y} ;
	for(int i = 0 ; i < 4 ; i++ ) {
		tx[i] -= bus->pos->x - bus->pos->w / 2 ;
		ty[i] -= bus->pos->y - bus->pos->h / 2 ;
	}
	polygonRGBA(bus->image, tx, ty, 4, 0, 255, 0, 255) ;
	
	// je rappelle que bus->pos est la position du centre du bus !!
	pos_affichage_bus->x = bus->pos->x - (bus->pos->w / 2) - m->standpoint->x ;
	pos_affichage_bus->y = bus->pos->y - (bus->pos->h / 2) - m->standpoint->y ;
	pos_affichage_bus->w = bus->pos->w ;
	pos_affichage_bus->h = bus->pos->h ;
	SDL_Blit(bus->image, NULL, ecran, pos_affichage_bus) ;
}

void majStandpointMap(Map *m, Bus *bus) {
	// on centre le standpoint sur le centre du bus
	m->standpoint->x = bus->pos->x - m->standpoint->w / 2 ;
	m->standpoint->y = bus->pos->y - m->standpoint->h / 2 ;
}


#include "includes.h" 


Passagers* initPassagers() {
	Passagers *psg = malloc(sizeof(Passagers)) ;
	if(psg == NULL)
		printf("psg == NULL\n") ;
	psg->nb = 0 ;
	psg->nb_max = NB_MAX_PASSAGERS ;
	psg->image = malloc(sizeof(SDL_Surface*) * NB_MAX_PASSAGERS) ;
	if(psg->image == NULL)
		printf("psg->image == NULL\n") ;
	psg->pos = malloc(sizeof(Pos*) * NB_MAX_PASSAGERS) ;
	if(psg->pos == NULL)
		printf("psg->pos == NULL\n") ;
	psg->poly = malloc(sizeof(Polygone*) * NB_MAX_PASSAGERS) ;
	if(psg->poly == NULL)
		printf("psg->poly == NULL\n") ;
	psg->rotation = malloc(sizeof(double) * NB_MAX_PASSAGERS) ;
	if(psg->rotation == NULL)
		printf("psg->rotation == NULL\n") ;
	psg->vitesse = malloc(sizeof(double) * NB_MAX_PASSAGERS) ;
	if(psg->vitesse == NULL)
		printf("psg->vitesse == NULL\n") ;

	return psg ;
}

void ajouterPassager(Passagers *psg, Map *m, Bus *bus) {
	int i, j, n ;
	int compteur ;
	int x, y ;
	int collision = true ; 
	Point **point_passager = malloc(sizeof(Point*) * 4) ;
	if(point_passager == NULL)
		printf("point_passager == NULL\n") ;
	// si un peut rajouter un passager
	if(psg->nb < psg->nb_max) {
		// incrémenter leur nombre
		n = psg->nb ;
		psg->nb ++ ;

		// lui choisir une image aléatoire
		// pour le moment on a qu'une seule image
		psg->image[n] = IMG_Load("images/voiture_polluante_rouge_80.png") ; 
		if(psg->image[n] == NULL)
			printf("Erreur de chargement de l'image d'une voiture polluante !\n") ;
		psg->pos[n] = malloc(sizeof(Pos)) ;
		psg->pos[n]->w = psg->image[n]->w ;
		psg->pos[n]->h = psg->image[n]->h ;

		// trouver une zone libre de la map
		compteur = 0 ;
		while(collision && compteur < 10) {
			compteur ++ ;
			// position aléatoire de la map
			x = randint(0, m->w) ;
			y = randint(0, m->h) ;
			// initialiser son poly
			psg->pos[n]->x = (double)x ;
			psg->pos[n]->y = (double)y ;
			point_passager[0] = creerPointXY(psg->pos[n]->x - psg->pos[n]->w / 2, psg->pos[n]->y - psg->pos[n]->h / 2) ;
			point_passager[1] = creerPointXY(psg->pos[n]->x + psg->pos[n]->w / 2, psg->pos[n]->y - psg->pos[n]->h / 2) ;
			point_passager[2] = creerPointXY(psg->pos[n]->x + psg->pos[n]->w / 2, psg->pos[n]->y + psg->pos[n]->h / 2) ;
			point_passager[3] = creerPointXY(psg->pos[n]->x - psg->pos[n]->w / 2, psg->pos[n]->y + psg->pos[n]->h / 2) ;
			psg->poly[n] = creerPolygone(4, point_passager) ;
			collision = false ;
			// il ne faut pas que la position soit en contacte avec un polygone
			for(i = 0 ; i < m->nb_poly ; i ++) {
				if(polygoneInPolygone(m->poly[i], psg->poly[n])) {
					// printf("collision avec le poly %d\n", i) ;
					collision = true ;
				}
			}
			// il ne faut pas que la position soit en collision avec un autre passager
			for(i = 0 ; i < n ; i++) {
				if(polygoneInPolygone(psg->poly[i], psg->poly[n])) {
					collision = true ;
				}
			}
			// il ne faut pas que la position soit en collision avec le bus
			if(polygoneInPolygone(bus->poly, psg->poly[n])) {
				collision = true ;
			}
		}
		if(compteur == 10000) {
			printf("Manque de place pour le nouveau passager !\n") ;
		} else {
		// lui trouver une vitesse initiale aléatoire
		psg->vitesse[n] = (double)randint(VITESSE_MIN_PASSAGER, VITESSE_MAX_PASSAGER) ;

		// lui trouver une rotation initiale aléatoire
		psg->rotation[n] = (double)randint(0, (int)PI*10) / 10 ;
		}
	// si on a pas pu rajouter de passager
	} else {
		//printf("On ne peut plus rajouter de passagers !\n") ;
	}
}

void deplacerPassagers(Passagers *psg, Map *m, Bus *bus) {
	int i, j, k ;
	double new_rot1, new_rot2 ;
	double mv_x, mv_y ;
	double nv_pas ;
	double tmp_rot ;

	// pour chaque passagers 
	for(i = 0 ; i < psg->nb ; i++) {
		// on les fait avancer
		if(!avancerPassager(m, bus, psg, i, psg->vitesse[i])) {
			// si pas possible, décomposer le mouvement sur chacun des 2 axes
			RTtoXY(psg->vitesse[i], psg->rotation[i], &mv_x, &mv_y) ;
			// faire l'avancée la plus ample possible pour chacun des 2 mouvements
			// selon les x, j'ai choisi x en premier de façon totalement arbitraire,
			// il faudrait peut-être faire les deux mouvements en même temps
			k = 0 ;
			nv_pas = mv_x - signe(mv_x)*i ;
			tmp_rot = psg->rotation[i] ;
			psg->rotation[i] = 0 ;
			while(signe(nv_pas) * signe(mv_x) > 0 && !avancerPassager(m, bus, psg, i, nv_pas)) {
				k ++ ;
				nv_pas = mv_x - signe(mv_x)*k ;
			}
			// selon les y
			k = 0 ;
			nv_pas = mv_y - signe(mv_y)*k ;
			psg->rotation[i] = PI / 2 ;
			while(signe(nv_pas) * signe(mv_y) > 0 && !avancerPassager(m, bus, psg, i, nv_pas)) {
				k ++ ;
				nv_pas = mv_y - signe(mv_y)*k ;
			}
			psg->rotation[i] = tmp_rot ;

			// comme il y a eus collision, il faut changer de vecteur directeur!
			// on aura ainsi l'impression que les passager rebondissent
			new_rot1 = psg->rotation[i] + PI + PI/4 ;
			new_rot2 = psg->rotation[i] + PI - PI/4 ;
			psg->rotation[i] = (double)randint((int)min(new_rot1, new_rot2)*10,
					(int)max(new_rot1, new_rot2)) / 10 ;
		}
	}
}

int avancerPassager(Map *m, Bus *bus, Passagers *psg, int num, double avancee) {
	int i ;
	int collision = false ; // au début, le passager n'est pas en collision
	double rotation_indirecte = psg->rotation[num] ;
	Point *p_tmp ;
	Polygone *next_poly ;

	// créer un polygone fictif ayant effectué l'avancée
	next_poly = creerPolygone(psg->poly[num]->n, getSommetsPoly(psg->poly[num])) ;
	translaterPolygoneRT(next_poly, avancee, rotation_indirecte) ;

	// si l'avancée n'entre pas en collision avec le décord
	for(i = 0 ; i < m->nb_poly ; i++) {
		if(polygoneInPolygone(next_poly, m->poly[i])) {
			collision = true ;
		}
	}
	// si l'avancée n'entre pas en collision avec les autres passagers
	for(i = 0 ; i < psg->nb ; i++) {
		if(i != num) {
			if(polygoneInPolygone(next_poly, psg->poly[i])) {
				collision = true ;
			}
		}
	}
	// si l'avancée n'entre pas en collision avec le bus
	if(polygoneInPolygone(next_poly, bus->poly)) {
		collision = true ;
	}

	// alors faire avancer le bus
	if(!collision) {
		// on translate son polynome
		translaterPolygoneRT(psg->poly[num], avancee, rotation_indirecte) ;
		// on translate sa position
		p_tmp = creerPointXY(psg->pos[num]->x, psg->pos[num]->y) ;
		translaterPointRT(p_tmp, avancee, rotation_indirecte) ;
		psg->pos[num]->x = p_tmp->x ;
		psg->pos[num]->y = p_tmp->y ;
		return true ; // SUCCESS
	// sinon ne rien faire
	} else {
		return false ; // ECHEC
	}
}

void recupererPassagersBus(Bus *bus, Passagers *psg) {
	int i ;
	for(i = 0 ; i < psg->nb ; i++) {
		if(polygoneInPolygone(bus->poly, psg->poly[i])) {
			// supprimer le passager
			psg->image[i] = psg->image[psg->nb-1] ;
			psg->pos[i] = psg->pos[psg->nb-1] ;
			psg->poly[i] = psg->poly[psg->nb-1] ;
			psg->rotation[i] = psg->rotation[psg->nb-1] ;
			psg->vitesse[i] = psg->vitesse[psg->nb-1] ;
			psg->nb -- ;

			// incrémenter le compteur de passager du bus
			bus->nb_passagers ++ ;
		}
	}
}

void afficherPassagers(SDL_Surface *ecran, Map *m, Passagers *psg) {
	int i, j ;
	Pos *pos_affichage_passager = malloc(sizeof(Pos)) ;
	Sint16 tx[4], ty[4] ;

	// pour chaque passager, l'afficher proprement
	for(i = 0 ; i < psg->nb ; i++) {
		// on affiche le rectangle de contact
		tx[0] = psg->poly[i]->a[0]->p1->x ;
		tx[1] = psg->poly[i]->a[1]->p1->x - 1 ;
		tx[2] = psg->poly[i]->a[2]->p1->x - 1 ;
		tx[3] = psg->poly[i]->a[3]->p1->x ;
		ty[0] = psg->poly[i]->a[0]->p1->y ;
		ty[1] = psg->poly[i]->a[1]->p1->y ;
		ty[2] = psg->poly[i]->a[2]->p1->y - 1 ;
		ty[3] = psg->poly[i]->a[3]->p1->y - 1 ;
		for(int j = 0 ; j < 4 ; j++ ) {
			tx[j] -= psg->pos[i]->x - psg->pos[i]->w / 2 ;
			ty[j] -= psg->pos[i]->y - psg->pos[i]->h / 2 ;
		}
		polygonRGBA(psg->image[i], tx, ty, 4, 255, 0, 0, 255) ;
		
		// je rappelle que psg->pos[i] est la position du centre du passager !!
		pos_affichage_passager->x = psg->pos[i]->x - (psg->pos[i]->w / 2) - m->standpoint->x ;
		pos_affichage_passager->y = psg->pos[i]->y - (psg->pos[i]->h / 2) - m->standpoint->y ;
		pos_affichage_passager->w = psg->pos[i]->w ;
		pos_affichage_passager->h = psg->pos[i]->h ;
		SDL_Blit(psg->image[i], NULL, ecran, pos_affichage_passager) ;
	}
}

void ramenerPassagers(Map *m, Bus *bus) {
	// vérifier la collision avec les checkpoints
	if(polygoneInPolygone(bus->poly, m->checkpoint[0]) || polygoneInPolygone(bus->poly, m->checkpoint[1])) {
		// augmenter le nombre de passagers de la map
		m->passagers_recuperes += bus->nb_passagers ;

		// vider le bus
		bus->nb_passagers = 0 ;
	}
}

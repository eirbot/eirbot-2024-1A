#include <stdio.h>

float compt_long(int n1, int n2)
{
	float r = 1, resolution = 1;
	float lambda = resolution * r/2 * (n1 + n2);
	return lambda ;
}

float compt_rot(int n1, int n2)
{
	float r = 1, d = 1, resolution = 1;
	float rot = resolution * r/(2*d) * (n1 - n2);
	return rot ;
}

float consigne_moteur_from_longueur(float distance)
{}

float consigne_moteur_from_rotation(float angle_rotation)
{}

void consigne_moteur_gauche(float consigne)
{}

void consigne_moteur_droite(float consigne)
{}

void avancer(float consigne_distance)
{
	float distance = consigne_distance;
	float consigne_moteur_avancer = consigne_moteur_from_longueur(consigne_distance); //fonction qui prend en argument la distance que doit parcourir le robot et renvoie l'angle (ou nombre de pas) que doit faire les moteur avec l'hypothese teta_gauche = teta_droite
	consigne_moteur_gauche(consigne_moteur_avancer); //fonction qui prend en argument l'angle que doit faire le moteur gauche et instruit le moteur 
	consigne_moteur_droite(consigne_moteur_avancer); //pareil pour le moteur droit
}

void rotation(float consigne_rotation)
{
	float angle_rotation = consigne_rotation;
	float consigne_moteur_tourner = consigne_moteur_from_rotation(angle_rotation); //fonction qui prend en argument l'angle de rotation du robot et renvoie l'angle (ou nombre de pas) que doit faire les moteur avec l'hypothese teta_gauche = -+teta_droite
		if (angle_rotation < 0)
		{
			consigne_moteur_gauche(-1*consigne_moteur_tourner); //fonction qui prend en argument l'angle que doit faire le moteur gauche et instruit le moteur 
			consigne_moteur_droite(consigne_moteur_tourner); //pareil pour le moteur droit
		}
		else 
		{
			consigne_moteur_gauche(consigne_moteur_tourner); //fonction qui prend en argument l'angle que doit faire le moteur gauche et instruit le moteur 
			consigne_moteur_droite(-1*consigne_moteur_tourner); //pareil pour le moteur droit
		}
}

void command(char * avancer_ou_tourner[], float consigne_distance_ou_rotation)
{
	if (avancer_ou_tourner = "avance")
	{
		avancer(consigne_distance_ou_rotation);
	}
	else 
	{
		rotation(consigne_distance_ou_rotation);
	}
}


int main(){}
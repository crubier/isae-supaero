/*************************************************************************************************
 Fichier description_helico.h
 Ce fichier contient l'initialisation de toutes les variables globales caract�risant
 l'h�licopt�re, c'est-�-dire :
 - les caract�ristiques m�caniques :	- dimensions des �l�ments et positions relatives
										entre les �l�ments
 - les caract�ristiques physiques :	- masses des �l�ments
									- caract�risation des h�lices
									- caract�risation des moteurs
									- caract�risation des forces de frottement
 - les param�tres des r�gulateurs PID
*************************************************************************************************/

#define PI	3.141592654

/*************************************************************************************************
 Caract�ristiques m�caniques et masses des �l�ments de l'h�licopt�re
 Notations :
 - inclinaison des barres par rapport � l'horizontal : alpha
 - masse des �l�ments : m_
 - dimensions m�caniques des �l�ments:
			- parall�l�pip�de :	- L_ (longueur = dimension selon l'axe y)
								- l_ (largeur = dimension selon axe x)
								- h_ (hauteur = dimension selon axe z)
			- cylindre :		- L_ (hauteur du cylindre)
								- r_ (rayon)
 - position du centre de masse selon l'axe z d'un �l�ment : z_
 Remarque1 :- cette distance est mesur�e par � la position verticale (axe z) de l'intersection
			  des barres (si celles-ci sont � l'horizontal : alpha = 0), avec z > 0 si le CM
			  de l'�l�ment consid�r� est au-dessus de l'intersection des barres
 Remarque2 :- si l'angle alpha != 0, les nouvelles positions des centres de masse sont d�duites
			  des positions z, il est donc important de bien d�finir les valeur des z_
*************************************************************************************************/

//***** Inclinaison des barres
int alpha = 0;			// [�]

//***** Electronics (e)
double me = 0.040;		// [kg]
double Le = 0.054;		// [m]
double le = 0.039;		// [m]
double he = 0.028;		// [m]
double ze = 0.020;		// [m]

//***** Electronics holder (h)
double mh = 0.010;		// [kg]
double Lh = 0.054;		// [m]
double lh = 0.039;		// [m]
double hh = 0.002;		// [m]
double zh = 0.005;		// [m]

//***** Supply (s)
double ms = 0.064;		// [kg]
double Ls = 0.095;		// [m]
double ls = 0.065;		// [m]
double hs = 0.005;		// [m]
double zs = -0.0065;	// [m]

//***** Motor (m)
double mm = 0.017;		// [kg]
double Lm = 0.024;		// [m]
double rm = 0.0085;		// [m]
double zm = -0.012;		// [m]
double dm = 0.200;		// [m]		position des moteurs (selon x et y) par rapport �
						//			l'intersection des barres
double Im = 0;			// [kgm2]	inertie du moteur

//***** Bar (b)
double mb = 0.030;		// [kg]
double Lb = 0.450;		// [m]
double zb = 0.000;		// [m]

//***** Gear box (g)
double mg = 0.005;		// [kg]
double zg = 0.005;		// [m]

//***** Propeller (p)
double mp = 0.007;		// [kg]
// Propeller as a cylinder (or disc)
double Lp = 0.285;		// [m]		diam�tre
double hp = 0.002;		// [m]		hauteur
// Propeller as a parallelepiped
double lp = 0.030;		// [m]		Lp = longeur, lp = largeur d'une pale
double zp = 0.010;		// [m]
double ea = 0.0126;		// [m]		entraxe moteur-h�lice


						
/*************************************************************************************************
 Caract�ristiques physiques de l'h�licopt�re
 - Caract�risation des h�lices :	- b[i] : coefficients de portance [N s2]
									- d[i] : coefficients de train�e [Nm s2]
 - Caract�risation des moteurs :	- vmax : vitesse max [rad/s]
									- amax : acc�l�ration max (positive et n�gative) [rad/s2]
									- r    : rapport de r�duction
 - Caract�risation des forces de frottement : - coefficients de frottements : kx,ky,kz
   (les forces de frottement lin�aires sont mod�lis�es comme �tant proportionnelles aux
    vitesses lin�raires au carr� : Ffrot = k * v * v avec v = vitesse lin�aire)
 - Rapport de r�duction : r
 *************************************************************************************************/
double b[4] = {0.000009 ,	0.0000087 ,	0.0000085,	0.0000093	};	// [N s2]
double d[4] = {0.0000002,	0.00000018,	0.0000002,	0.00000023	};	// [Nm s2]
double vmax = 1800;		// [rad/s]
double amax = 25000;	// [rad/s2]
double kx = 0.8;
double ky = 0.8;
double kz = 0.2;
double r = 5;



/*************************************************************************************************
 Param�tres des 4 r�gulateurs PID : - PID1 [0] : contr�le de l'altitude
									- PID2 [1] : contr�le du roulis (phi) (ou tangage)
									- PID3 [2] : contr�le du tangage (theta) (ou roulis)
									- PID4 [3] : contr�le du lacet (psi)
 - Kp[i] : param�tre multipliant l'ecart e (consigne-mesure)
 - Td[i] : param�tre multipliant la vitesse
 - Ti[i] : param�tre multipliant le terme d'int�gration des �carts
 - U0[i] : commande a priori (force g�n�ralis�e [N ou Nm])
 - zd    : altitude d�sir�e (consigne)
 - phid,thetad,psid : orientation d�sir�e (consigne)
*************************************************************************************************/
double Kp[4] = {5.0,	1.0		, 0.5	,0.01	};
double Td[4] = {0.2,	0.2		, 0.2	,5.0	};
double Ti[4] = {0.002,	0.01	, 0.02	,0.1	};
double U0[4] = {2.8449,	0.0		, 0.0	,0.0	};
double zd = 0.5;		// [m]
double phid = 0;		// [rad]
double thetad = 0;		// [rad]
double psid = 0;		// [rad]
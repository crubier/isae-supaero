/*************************************************************************************************
 Fichier variables.h
 Ce fichier contient toutes les variables globales associ�es aux calculs de la simulation
 (r�sultats de calculs interm�diaires pour une meilleure lecture)
 - simulation :				- temps et communication
 - description m�canique :	- quelques dimensions
 - description physique :	- vitesses,acc�l�ration,masses,centre de masse, moments d'inertie
 - r�gulateur :				- entr�es et sorties
 - position et orientation de l'h�licopt�re
 - forces g�n�ralis�es appliqu�es � l'h�licopt�re
**************************************************************************************************



/*************************************************************************************************
 Variables associ�es � la simulation
 - gps1			: d�claration du GPS de l'h�licopt�re
 - Dt			: pas de temps de la simulation [s]
 - time			: variable temps [s]
 - answer		: caract�re pour la communication avec l'utilisateur
 - i			: compteur de boucle
*************************************************************************************************/	// Divers
DeviceTag gps1;
double Dt = 0.032;	// [s]
double time = 0;	// [s]
char answer;
int i;


/*************************************************************************************************
 Variables associ�es � la description m�canique de l'h�licopt�re :
 - L		: demi longeur d'une barre
 - rp		: rayon d'une h�lice
 - dp		: position des h�lices (selon x et y) par rapport � l'intersection des barres
 - alphar	: angle alpha exprim� en radians
*************************************************************************************************/
double L;			// [m]
double rp;			// [m] rayon d'une h�lice
double dp;			// [m] position d'une h�lice (position du moteur + entraxe)
double alphar;		// [rad]



/*************************************************************************************************
 Variables associ�es � la description physique de l'h�licopt�re
 - vp[i]	: vitesse angulaire des h�lices [rad/s]
 - vpu[i]	: vitesse angulaire des h�lices demand�e par le r�gulateur
 - a		: acc�l�ration angulaire demand�e par le r�gulateur
 - limit	: une limite physique a-t-elle �t� atteint ? (oui => limit = 1)
 - c[i]		: d[i]/b[i] = rapport entre les coefficients des h�lices
			  c[4] = c[0] + ... + c[3]
 - m		: masse totale [kg]
 - zcm		: position du centre de masse (selon axe z) par rapport � l'intersection des barres
 - dz_		: position relative de chaque �l�ment par rapport au centre de masse
 - Ixx_		: moment d'inertie de chaque �l�ment par rapport � l'axe x (h�licopt�re)
 - Iyy_		: moment d'inertie de chaque �l�ment par rapport � l'axe y (h�licopt�re)
 - Izz_		: moment d'inertie de chaque �l�ment par rapport � l'axe z (h�licopt�re)
 - Ixx,Iyy,Izz : moments d'inertie de l'h�licopt�re
 - Ipr		: moment d'inertie rotorique de l'h�lice + moment d'inertie du rotor rapport�
			  � l'h�lice
 *************************************************************************************************/
double vp[4];	// [rad/s]
double vpu[4];	// [rad/s]
double a;		// [rad/s2]
int limit = 0;	// [boolean]
double c[5];	// [m]
double m;		// [kg]		
double zcm;		// [m]
double dze;		// [m]
double dzh;		// [m]
double dzs;		// [m]
double dzm;		// [m]
double dzb;		// [m]
double dzp;		// [m]
double dzg;		// [m]
double Ixxe;	// [kgm2]
double Ixxh;	// [kgm2]
double Ixxs;	// [kgm2]
double Ixxm1;	// [kgm2]
double Ixxm2;	// [kgm2]
double Ixxb1;	// [kgm2]
double Ixxb2;	// [kgm2]
double Ixxp1;	// [kgm2]
double Ixxp2;	// [kgm2]
double Iyye;	// [kgm2]
double Iyyh;	// [kgm2]
double Iyys;	// [kgm2]
double Iyym1;	// [kgm2]
double Iyym2;	// [kgm2]
double Iyyb1;	// [kgm2]
double Iyyb2;	// [kgm2]
double Iyyp1;	// [kgm2]
double Iyyp2;	// [kgm2]
double Izze;	// [kgm2]
double Izzh;	// [kgm2]
double Izzs;	// [kgm2]
double Izzm1;	// [kgm2]
double Izzm2;	// [kgm2]
double Izzb1;	// [kgm2]
double Izzb2;	// [kgm2]
double Izzp1;	// [kgm2]
double Izzp2;	// [kgm2]
double Ixx;		// [kgm2]
double Iyy;		// [kgm2]
double Izz;		// [kgm2]
double Ipr;		// [kgm2]



/*************************************************************************************************
 Variables associ�es aux calculs des r�gulateurs PID
 - ei[i]	: variable int�gration des �carts
 - U[i]		: variable de sortie (force g�n�ralis�e [N ou Nm])
*************************************************************************************************/
double ei[4];
double ei2[4];
double U[4];		// U[0] : [N], U[1]-U[3] : [Nm]



/*************************************************************************************************
 Variables associ�es � la position et � l'orientation de l'h�licopt�re
 - x,y,z	: [1] = position actuelle du CM de l'h�licopt�re (r�f�rentiel terrestre)
			: [0] = position pr�c�dente du CM de l'h�licopt�re (r�f�rentiel terrestre)
 - dx,dy,dz	: vitesse actuelle du CM de l'h�licopt�re (r�f�rentielle terrestre)
 - phi,theta,psi : [1] = orientation actuelle de l'h�licopt�re (angle d'Euler)
				 : [0] = orientation actuelle de l'h�licopt�re (angle d'Euler)
 - dphi,dtheta,dpsi : vitesse angulaire de l'h�licopt�re (angle d'Euler)
 - PosMatrix : matrice de position fournie par le GPS de Webots
 - MW11,...,MW33 : variables pour l'extraction des �l�ments de la matrice de rotation
   (r�f�rentiel terrestre -> r�f�rentiel du robot)
*************************************************************************************************/
double x[2],y[2],z[2];
double dx,dy,dz;
double phi[2],theta[2],psi[2];
double dphi,dtheta,dpsi;
const float *PosMatrix;
float MW11, MW12, MW13,            // Rotation Matrix: tranform vector 
	  MW21, MW22, MW23,            // expressed in WEBOTS earth ref 
	  MW31, MW32, MW33;            // in a vector expressed W. body ref. 



/*************************************************************************************************
 Variables associ�es � l'expression des forces g�n�ralis�es appliqu�es � l'h�licopt�re 
 exprim�es par rapport au r�f�rentiel de l'h�licopt�re
 - tgphi,tgtheta			: moment gyroscopiques
 - v1,v2,v3					: vitesses associ�es au calcul des moments gyroscopiques
 - ffrotx, ffroty, ffrotz	: forces de frottement avec l'air
 - fx,fy,fz,tx,ty,tz		: forces r�sultantes totales
 - beta						: pour cr�er perturbation harmonique
*************************************************************************************************/
double tgphi, tgtheta;			// [Nm]
double v1,v2,v3;				// [rad/s]
double ffrotx,ffroty,ffrotz;	// [N]
double fx,fy,fz,tx,ty,tz;		// f : [N], t [Nm]
double beta = 0;
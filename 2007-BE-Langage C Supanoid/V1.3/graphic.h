#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include "key.h"

/**
 * ATTENTION : les coordonn�es graphiques en informatique ont toujours leur
 * origine dans le coin sup�rieur gauche.
 * L'axe des abscisses est croissant vers la droite.
 * L'axes des ordonn�es est par contre croissant vers le bas.
 * Toutes les coordonn�es et les distances (largeur, hauteur, x, y, ...) sont 
 * donn�es en pixels. Tout d�pend donc de la r�solution de l'�cran. Une r�solution
 * de 1024 x 768 veut donc dire qu'il y a 1024 pixels de largeur � l'�cran et 768
 * pixels en hauteur.
 */

#define TRUE 1
#define FALSE 0

typedef int BOOLEAN;

typedef enum { WHITE, BLACK, RED, BLUE, GREEN, YELLOW, CYAN, GRAY, MAGENTA, ORANGE, PINK } COLOR;

typedef enum { PLAIN, BOLD, ITALIC } STYLE;

/**
 * M�thode de cr�ation de la fen�tre dans laquelle dessiner.
 * Cette m�thode doit �tre appel�e en 1er pour pouvoir utiliser toutes
 * les autres fonctions.
 * width : largeur de la fen�tre.
 * height : hauteur de la fen�tre.
 */
void start(int width, int height);

/**
 * M�thode � appeler � la fin du programme. Elle permet d'attendre
 * la fermeture de la fen�tre pour arr�ter le programme courant (sinon
 * la fen�tre se fermerait automatiquement)
 */
void finish();

/**
 * Bloque l'ex�cution du programme pendant le temps indiqu� en param�tre.
 * Cette m�thode est � appeler par exemple si on veut redessiner le contenu
 * de la fen�tre toutes les 20 ms, en lui passant 20 comme argument.
 * millis : temps d'attente en millisecondes.
 */
void sleepAWhile(long millis);

/**
 * Sp�cifie la couleur de 1er plan. C'est la couleur utilis�e par les
 * m�thode draw... et fill...
 * color : la couleur de 1er plan.
 * cf. l'�num�ration COLOR pour la liste des couleurs disponibles.
 */
void setForegroundColor(COLOR color);

/**
 * Sp�cifie la couleur d'arri�re-plan. C'est la couleur utilis�e par la
 * m�thode clearRect pour "effacer" le rectangle sp�cifi� (le rectangle est
 * en fait rempli avec cette couleur).
 * color : la couleur d'arri�re-plan.
 * cf. l'�num�ration COLOR pour la liste des couleurs disponibles. */
void setBackgroundColor(COLOR color);

/**
 * "Efface" le rectangle sp�cifi� avec la couleur d'arri�re-plan.
 * x : abscisse du coin sup�rieur gauche du rectangle.
 * y : ordonn�e du coin sup�rieur gauche du rectangle.
 * width : largeur du rectangle.
 * height : hauteur du rectangle.
 */
void clearRect(int x, int y, int width, int height);

/**
 * Dessine un arc de cercle.
 * x : abscisse du coin sup�rieur gauche du rectangle circonscrit.
 * y : ordonn�e du coin sup�rieur gauche du rectangle circonscrit.
 * width : largeur du rectangle circonscrit.
 * height : hauteur du rectangle circonscrit.
 * startAngle : angle de d�part de l'arc de cercle (en degr�s). Un angle de 0
 * correspond � l'axe des abscisses. Un angle positif suit le sens trigonom�trique.
 * endAngle : longueur angulaire de l'arc (� partir de l'angle de d�part).
 */
void drawArc(int x, int y, int width, int height, int startAngle, int arcAngle);

/**
 * Dessine une image.
 * filepath : chemin de l'image (.jpg, .gif, .png, ...) en relatif (par rapport
 * au r�pertoire de lancement de l'application) ou en absolu ("c:\...." ou "/home..").
 * ATTENTION : sous Windows, il est possible (et pr�f�rable) d'utiliser "/" 
 * au lieu de "\" pour sp�cifier le chemin d'un fichier (p.ex. : "toto/titi/image.jpg").
 * Ceci a l'avantage de ne pas �tre oblig� de modifier le code lors de la compilation
 * sous un autre syst�me d'exploitation.
 * x : abscisse du coin sup�rieur gauche de l'image.
 * y : ordonn�e du coin sup�rieur gauche de l'image.
 */
void drawImage(const char *filepath, int x, int y);

/**
 * Dessine une ligne.
 * x1 : abscisse du 1er point.
 * y1 : ordonn�e du 1er point.
 * x2 : abscisse du 2�me point.
 * y2 : ordonn�e du 2�me point.
 */
void drawLine(int x1, int y1, int x2, int y2);  

/**
 * Dessine un ovale inscrit dans le rectangle sp�cifi�.
 * x : abscisse du coin sup�rieur gauche du rectangle circonscrit.
 * y : ordonn�e du coin sup�rieur gauche du rectangle circonscrit.
 * width : largeur du rectangle circonscrit.
 * height : hauteur du rectangle circonscrit.
 */
void drawOval(int x, int y, int width, int height);

/**
 * Dessine un polygone.
 * Chaque point est reli� au suivant par un segment ainsi que le dernier 
 * point avec le premier s'ils sont diff�rents.
 * xPoints : tableau des abscisses des points.
 * yPoints : tableau des ordonn�es des points.
 * nPoints : nombre total de points.
 */
void drawPolygon(int *xPoints, int *yPoints, int nPoints);

/**
 * Dessine une s�quence de points reli�s.
 * Chaque point est reli� au suivant par un segment. 
 * xPoints : tableau des abscisses des points.
 * yPoints : tableau des ordonn�es des points.
 * nPoints : nombre total de points.
 */
void drawPolyline(int *xPoints, int *yPoints, int nPoints);

/**
 * Dessine un rectangle.
 * x : abscisse du coin sup�rieur gauche du rectangle.
 * y : ordonn�e du coin sup�rieur gauche du rectangle.
 * width : largeur du rectangle.
 * height : hauteur du rectangle.
 */
void drawRect(int x, int y, int width, int height);

/**
 * Dessine un rectangle surlign� en 3D.
 * x : abscisse du coin sup�rieur gauche du rectangle.
 * y : ordonn�e du coin sup�rieur gauche du rectangle.
 * width : largeur du rectangle.
 * height : hauteur du rectangle.
 * raised : un boole�n sp�cifiant si le rectangle doit appara�tre sur�lev�
 * ou abaiss�.
 */
void draw3DRect(int x, int y, int width, int height, BOOLEAN raised);

/**
 * Dessine un rectangle dont les coins sont arrondis.
 * x : abscisse du coin sup�rieur gauche du rectangle circonscrit.
 * y : ordonn�e du coin sup�rieur gauche du rectangle circonscrit.
 * width : largeur du rectangle circonscrit.
 * height : hauteur du rectangle circonscrit.
 * arcWidth : largeur du rectangle cirsconscrit � l'arc utilis� pour arrondir les angles.
 * arcHeight : hauteur du rectangle cirsconscrit � l'arc utilis� pour arrondir les angles.
 */
void drawRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight);

/**
 * Dessine un texte � l'�cran.
 * text : le texte � afficher.
 * x : l'abscisse de la 1�re lettre du texte.
 * y : l'ordonn�e du texte.
 * cf. setFontSize et setFontStyle.
 */
void drawText(const char *text, int x, int y);

/**
 * Sp�cifie la taille de la police � utiliser par la m�thode drawText.
 * size : taille de la police utilis�e pour afficher du texte (la taille
 * par d�faut doit �tre 12).
 * cf. drawText.
 */
void setFontSize(float size);

/**
 * Sp�cifie le style de la police � utiliser par la m�thode drawText.
 * style : style � appliquer � la police (BOLD = gras, ITALIC = italique,
 * PLAIN = normal).
 * cf. l'�num�ration STYLE.
 */
void setFontStyle(STYLE style);

/**
 * Dessine et remplit un arc de cercle (comme une part de g�teau).
 * x : abscisse du coin sup�rieur gauche du rectangle circonscrit.
 * y : ordonn�e du coin sup�rieur gauche du rectangle circonscrit.
 * width : largeur du rectangle circonscrit.
 * height : hauteur du rectangle circonscrit.
 * startAngle : angle de d�part de l'arc de cercle (en degr�s). Un angle de 0
 * correspond � l'axe des abscisses. Un angle positif suit le sens trigonom�trique.
 * endAngle : longueur angulaire de l'arc (� partir de l'angle de d�part).
 */
void fillArc(int x, int y, int width, int height, int startAngle, int arcAngle);

/**
 * Dessine et remplit un ovale inscrit dans le rectangle sp�cifi�.
 * x : abscisse du coin sup�rieur gauche du rectangle circonscrit.
 * y : ordonn�e du coin sup�rieur gauche du rectangle circonscrit.
 * width : largeur du rectangle circonscrit.
 * height : hauteur du rectangle circonscrit.
 */
void fillOval(int x, int y, int width, int height);

/**
 * Dessine et remplit un polygone.
 * Chaque point est reli� au suivant par un segment ainsi que le dernier 
 * point avec le premier s'ils sont diff�rents.
 * xPoints : tableau des abscisses des points.
 * yPoints : tableau des ordonn�es des points.
 * nPoints : nombre total de points.
 */
void fillPolygon(int *xPoints, int *yPoints, int nPoints);

/**
 * Dessine et remplit un rectangle.
 * x : abscisse du coin sup�rieur gauche du rectangle.
 * y : ordonn�e du coin sup�rieur gauche du rectangle.
 * width : largeur du rectangle.
 * height : hauteur du rectangle.
 */
void fillRect(int x, int y, int width, int height);

/**
 * Dessine et remplit un rectangle dont les coins sont arrondis.
 * x : abscisse du coin sup�rieur gauche du rectangle circonscrit.
 * y : ordonn�e du coin sup�rieur gauche du rectangle circonscrit.
 * width : largeur du rectangle circonscrit.
 * height : hauteur du rectangle circonscrit.
 * arcWidth : largeur du rectangle cirsconscrit � l'arc utilis� pour arrondir les angles.
 * arcHeight : hauteur du rectangle cirsconscrit � l'arc utilis� pour arrondir les angles.
 */
void fillRoundRect(int x, int y, int width, int height, int arcWidth, int arcHeight);

/**
 * Dessine et remplit un rectangle surlign� en 3D.
 * x : abscisse du coin sup�rieur gauche du rectangle.
 * y : ordonn�e du coin sup�rieur gauche du rectangle.
 * width : largeur du rectangle.
 * height : hauteur du rectangle.
 * raised : un boole�n sp�cifiant si le rectangle doit appara�tre sur�lev�
 * ou abaiss�.
 */
void fill3DRect(int x, int y, int width, int height, BOOLEAN raised);

/**
 * Affiche le graphique dans la fen�tre.
 * Toutes les figures dessin�es avec les m�thodes ci-dessus (drawRect, drawArc, fillRect, 
 * fillOval, etc...) n'apparaissent dans la fen�tre qu'une fois que paint() a �t�
 * appel�.
 */
void paint();

/**
 * "Enregistre" la touche du clavier pass�e en param�tre.
 * Cette m�thode doit �tre appel�e au d�but du programme (avant d'utiliser
 * la m�thode "getLastKeyPressed") en passant en param�tre la touche du
 * clavier que l'on veut �couter.
 * Par exemple : registerKeyPressed(VK_LEFT); va "�couter" la touche fl�che
 * gauche du clavier.
 * key : code de la touche du clavier (cf. key.h pour la liste des codes)
 * cf. getLastKeyPressed
 */
void registerKeyPressed(int key);

/**
 * Renvoie la touche du clavier press�e ou -1 si aucune touche n'est press�e.
 * Seule les touches qui auront �t� enregistr�e avec la m�thode registerKeyPressed
 * sont �cout�es.
 * Exemple : Voici le code d'une application qui permet de faire bouger un ballon
 * vers le haut ou vers le bas en fonction de l'appui des touches Fl�che Haut et Bas.
 * 
 * #include "graphic.h"
 * #include "key.h"
 * 
 * int main() {
 *   int y = 400;                     // ordonn�e du ballon (haut du ballon)
 *   int fini = 0;                    // valeur bool�enne initialis�e � FAUX
 * 
 *   start(800, 800);                 // cr�ation d'une fen�tre 800 x 800
 *   setBackgroundColor(BLACK);       // couleur de fond = NOIR
 *   setForegroundColor(RED);         // couleur de 1er plan = ROUGE
 *   clearRect(0, 0, 800, 800);       // la fen�tre est painte enti�rement en noir 
 *
 *   registerKeyPressed(VK_UP);       // Enregistrement de la touche Fl�che Haut
 *   registerKeyPressed(VK_DOWN);     // Enregistrement de la touche Fl�che Bas
 * 
 *   fillOval(400, y, 40, 40);        // Dessin du ballon de diam�tre 40, � l'abscisse
 *                                    // 400 et � l'ordonn�e y (angle gauche-haut)
 * 
 *   while (!fini) {                  // boucle infinie
 *     switch (getLastKeyPressed()) { // R�cup�ration de la touche press�e en cours
 *       case -1:                     // aucune touche press�e
 *         break;                     // On ne fait rien 
 *       case VK_UP:                  // Si la touche press�e est la fl�che Haut
 *         y--;                       // On d�cr�mente y, le ballon ira vers le haut
 *         break;
 *       case VK_DOWN:                // Si la touche press�e est la fl�che Bas
 *         y++;                       // On incr�mente y, le ballon ira vers le bas
 *         break;
 *       case VK_ESCAPE:              // par d�faut la touche "escape" est toujours �cout�e
 *         fini = 1;                  // sortira de la boucle � la prochaine it�ration
 *         break;
 *     }
 *     clearRect(0, 0, 800, 800);     // On efface la fen�tre (toute en noir donc)
 *     fillOval(400, y, 40, 40);      // On redessine le ballon � sa nouvelle position
 *     paint();                       // On affiche le r�sultat
 *     sleepAWhile(5);                // On patiente 5 ms, ce qui fera un affichage
 *                                    // de 200 images/s, ce qui est largement suffisant
 *   }
 *   finish();                       // Cette m�thode doit toujours �tre appel�e en fin de programme
 * }
 */
int getLastKeyPressed();

/**
 * "Enregistre" le son pass� en param�tre.
 * Cette m�thode doit �tre appel�e avant d'appeler "playSound).
 * Ce son doit �tre un fichier de type "wav" (avec l'extension ".wav").
 * filepath : chemin du fichier son en relatif (par rapport au r�pertoire de 
 * lancement de l'application) ou en absolu ("c:\...." ou "/home..").
 * ATTENTION : sous Windows, il est possible (et pr�f�rable) d'utiliser "/" 
 * au lieu de "\" pour sp�cifier le chemin d'un fichier (p.ex. : "toto/titi/son.wav").
 * Ceci a l'avantage de ne pas �tre oblig� de modifier le code lors de la compilation
 * sous un autre syst�me d'exploitation.
 * L'enregistrement des fichiers sons est obligatoire pour pouvoir ensuite jouer le son
 */
void registerSound(char *filepath);

/**
 * Joue le son pr�alablement enregistr� (le chemin du fichier doit �tre le
 * m�me que lors de l'appel � registrerSound).
 */
void playSound(char *filepath);

void setClip(int x, int y, int width, int height);

void addClip(int x, int y, int width, int height);


#endif

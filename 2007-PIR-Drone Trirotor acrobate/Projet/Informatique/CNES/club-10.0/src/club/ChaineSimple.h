///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//       Marmottes
//
//$Application
//       Club
//
//$Nom
//>       ChaineSimple.h
//
//$Resume
//       fichier d'en-t�te de la classe ChaineSimple
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class ChaineSimple              
//>       inline ChaineSimple operator +()
//
//$Historique
//       $Log: ChaineSimple.h,v $
//       Revision 1.18  2002/11/29 10:49:16  club
//       DM-ID 12 Correction de l'ordre des d�clarations (public, protected, private)
//
//       Revision 1.17  2001/06/22 05:39:41  club
//       remplacement de l'inclusion de cwctype par l'inclusion de cctype
//
//       Revision 1.16  2000/10/25 09:31:43  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 1.15  2000/10/24 14:18:14  club
//       mise � jour des includes et ajout des tests de configuration.
//
//       Revision 1.14  2000/10/24 08:31:21  club
//       modification des includes du standard C : utilisation de cNAME au lieu
//       de NAME.h (pour permettre la compilation avec Sun Workshop 5.0)
//
//       Revision 1.13  2000/09/11 12:18:50  club
//       Mise � jour des include et suppression des tests sur variable de
//       configuration de ClubConfig.h qui n'est pas install�.
//
//       Revision 1.12  2000/08/30 14:09:34  club
//       Utilisation des variables de configuration pour tester les include.
//       Utilisation de l'espace de nommage std.
//
//       Revision 1.11  2000/08/25 07:09:07  club
//       Ajout du constructeur de ChaineSimple � partir d'un string STL.
//       Ajout de l'op�rateur de conversion implicite d'une ChaineSimple en string.
//
//       Revision 1.10  2000/07/03 08:54:19  club
//       Ajout du copyright CNES
//
//       Revision 1.9.2.1  2000/03/30 14:46:54  club
//       ajout du copyright CNES
//
//       Revision 1.9  1998/10/19 06:39:44  club
//       ajout des op�rateurs + entre ChaineSimple, const char *, et char
//       dans tous les sens
//
//       Revision 1.8  1998/07/27 10:14:00  club
//       passage � une configuration de type GNU (fichier ClubConfig.h g�n�r�)
//
//       Revision 1.7  1998/06/25 06:40:29  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.6  1998/04/26 13:02:19  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.5  1998/01/22 08:27:02  luc
//       am�lioration de l'en-t�te de classe
//
//       Revision 1.4  1997/08/21 16:34:01  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 1.3  1997/03/25 14:45:25  luc
//       ajout d'une m�thode vFormate prenant un argument de type va_list
//       changement des r�gles de nommage
//       
//       Revision 1.2  1997/03/19 14:41:07  luc
//       renommage de la biblioth�que util_c++ en club
//       d�placement du destructeur vers le fichier .cc
//       
//       Revision 1.1  1997/03/16 18:10:09  luc
//       Initial revision
//
//$Version
//       $Id: ChaineSimple.h,v 1.18 2002/11/29 10:49:16 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_ChaineSimple_h
#define __club_ChaineSimple_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <cstdarg>
#include <cstdio>
#include <cctype>

#include <string>

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ChaineSimple
//
//$Resume
//       classe cha�ne de caract�res
//
//$Description
//       gestion tr�s simplifi�e d'une cha�ne de caract�res (seules
//       les allocations m�moires et les tests == et != sont g�r�es,
//       pour le reste l'utilisateur pourra s'appuyer sur les
//       fonctions C classiques index, strchr, ...)
//
//$Usage
//>     construction : 
//          sans argument, � partir d'une taille initiale, d'une
//          cha�ne (m�me vide ou pointeur nul) �ventuellement limit�e
//          par une longueur utile, d'un caract�re et d'un nombre de
//          r�p�titions, d'un string, par copie et affectation
//>     utilisation  : 
//>       void reinitialise          () 
//         r�initialise une cha�ne comme si elle venait d'�tre
//         construite
//>       void formate               () 
//          �crit dans l'instance avec un format C
//>       void vFormate              () 
//          �crit dans l'instance avec un format C
//>       void modifieCaractere      () 
//          modifie le caract�re d'index i (i est limit� par taille (),
//          pas par longueur ())
//>       void elimineBlancsFinaux   () 
//          enl�ve les derniers blancs de la cha�ne
//>       void elimineBlancsInitiaux () 
//          enl�ve les premiers blancs de la cha�ne
//>       ChaineSimple& operator +=  () 
//          ajoute une cha�ne � la fin de l'instance
//>       ChaineSimple operator()    () 
//          extrait une sous-cha�ne par des pointeurs ou des index sur
//          ses premier et dernier caract�res (les index d�butent � 0)
//>       ChaineSimple& operator =   () 
//          affectation
//>       operator const char*       () 
//         conversion en const char *
//>       operator string            () 
//         conversion en string
//>       void recadre               () 
//          enl�ve les premiers et les derniers blancs de la cha�ne
//>       int taille                 () 
//          retourne la taille du tableau allou� pour la cha�ne
//>       int longueur               () 
//          retourne la longueur courante de la cha�ne
//>       const char *premier        () 
//          retourne un pointeur sur le premier caract�re de la cha�ne
//>       const char *dernier        () 
//          retourne un pointeur sur le dernier caract�re de la cha�ne
//>       int operator ==            () 
//          teste l'�galit� de deux cha�nes
//>       int operator !=            () 
//
//$Auteur
//       L. Maisonobe CNES
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class ChaineSimple
{ 

  public :

  // constructeurs et affectations
  ChaineSimple (int taille = -1) { alloueChaine (taille); }

  ChaineSimple (const char *chaine);
  ChaineSimple (const char *chaine, int longueur);
  ChaineSimple (char caractere, int repetitions);
  ChaineSimple (const ChaineSimple& c);
  ChaineSimple (const string& c);

  ChaineSimple& operator = (const ChaineSimple& c)
  { reinitialise (c); return *this; }

  ChaineSimple& operator = (const char *chaine)
  { reinitialise (chaine); return *this; }

  // destructeur
  ~ChaineSimple ();

  // conversions
  operator const char* () const { return chaine_; }
  operator string      () const { return string (chaine_); }

  // modifications
  void          reinitialise          (const ChaineSimple& c);
  void          reinitialise          (const char *chaine);
  void          reinitialise          (const char *chaine, int longueur);
  void          reinitialise          (char caractere, int repetitions);

  void          formate               (const char *format ...);
  void          vFormate              (const char *format, va_list ap);

  void          modifieCaractere      (int i, char c);

  void          elimineBlancsFinaux   ();
  void          elimineBlancsInitiaux ();
  void          recadre               ()
                { elimineBlancsFinaux (); elimineBlancsInitiaux (); }

  ChaineSimple& operator +=           (const ChaineSimple& c);
  ChaineSimple& operator +=           (const char         *chaine);
  ChaineSimple& operator +=           (char                c);

  // acc�s aux �l�ments internes
  int          taille   () const { return taille_;   }
  int          longueur () const { return longueur_; }

  const char  *premier  () const { return chaine_;   }
  const char  *dernier  () const { return chaine_ + longueur_ - 1; }

  ChaineSimple operator () (const char *debut, const char *fin) const;
  ChaineSimple operator () (int         debut, int         fin) const;

  // tests
  int operator == (const char         *chaine) const;
  int operator == (const ChaineSimple& chaine) const;
  int operator != (const char         *chaine) const;
  int operator != (const ChaineSimple& chaine) const;

  private:

  int    taille_;
  int    longueur_;
  char  *chaine_;

  // allocation d'une cha�ne d'au moins taille caract�res
  // (si la taille est inf�rieure � une valeur limite, on utilise la limite)
  void alloueChaine (int taille);
  void etendChaine  (int taille);

};

inline ChaineSimple operator + (const ChaineSimple& c1, const ChaineSimple& c2)
{ ChaineSimple c3 (c1); c3 += c2; return c3; }

inline ChaineSimple operator + (const ChaineSimple& c1, const char *c2)
{ ChaineSimple c3 (c1); c3 += c2; return c3; }

inline ChaineSimple operator + (const ChaineSimple& c1, char c2)
{ ChaineSimple c3 (c1); c3 += c2; return c3; }

inline ChaineSimple operator + (const char *c1, const ChaineSimple& c2)
{ ChaineSimple c3 (c1); c3 += c2; return c3; }

inline ChaineSimple operator + (char c1, const ChaineSimple& c2)
{ ChaineSimple c3 (c1, 1); c3 += c2; return c3; }

#endif

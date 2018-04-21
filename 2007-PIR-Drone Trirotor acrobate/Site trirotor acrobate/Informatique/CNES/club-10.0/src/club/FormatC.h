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
//>       FormatC.h
//
//$Resume
//       fichier d'en-t�te de la classe FormatC
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class FormatC
//
//$Historique
//       $Log: FormatC.h,v $
//       Revision 1.6  2000/10/25 09:31:43  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 1.5  2000/10/24 14:18:14  club
//       mise � jour des includes et ajout des tests de configuration.
//
//       Revision 1.4  2000/09/11 12:18:50  club
//       Mise � jour des include et suppression des tests sur variable de
//       configuration de ClubConfig.h qui n'est pas install�.
//
//       Revision 1.3  2000/09/07 07:46:43  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 1.2  2000/08/25 07:09:41  club
//       Ajout du copyright CNES.
//
//       Revision 1.1  2000/08/25 07:00:44  club
//       Cr�ation de cette classe qui permet de g�rer les formats du C.
//
//$Version
//       $Id: FormatC.h,v 1.6 2000/10/25 09:31:43 club Exp $
//
//$Auteur
//       O. Queyrut  CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_FormatC_h
#define __club_FormatC_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <cstdarg>
#include <string>

#include "club/ClubErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class FormatC
//$Resume
//       classe g�rant les formats d'�criture du langage C
//
//$Description
//       classe de gestion des formats d'�criture du langage C. Cette classe
//       permet d'analyser les arguments attendus par un format C afin de
//       tester la compatibilit� de deux formats (ce m�canisme est utilis�
//       pour la traduction) et afin d'utiliser le format.
//
//$Usage
//>     construction : 
//          sans argument, par une cha�ne de caract�res, par copie
//>     utilisation  : 
//>       FormatC& operator =              () 
//          affectation
//>       void analyse                     () 
//          analyse la cha�ne format et stocke les arguments attendus
//>       int compatible                   () 
//          teste si l'instance est compatible avec le format f
//>       int nbArgs                       () 
//          retourne le nombre d'arguments attendus
//>       int typeArg                      () 
//          retourne le type attendu pour l'argument i
//>       const string& chaine             () 
//          retourne la cha�ne du format
//>       void ajouteArg                   () protegee - 
//>       const char* specificateurSuivant () protegee - 
//
//$Auteur
//       O. Queyrut  CSSI
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////


class FormatC
{ 
public :
  
  enum { ENTIER, REEL, CHAINE, CARACTERE, INCONNU, ERREUR };

  // constructeurs et affectation
  FormatC () : tailleTableType_ (0), nbArgs_ (0), type_ (0), chaine_ ("")
  {}

  FormatC (const string& format)
    : tailleTableType_ (0), nbArgs_ (0), type_ (0)
  { analyse (format); }

  FormatC (const FormatC& f);
  FormatC& operator = (const FormatC& f);

  // destructeur
  ~FormatC ();

  // traitement du format
  void    analyse    (const string& format);

  va_list applique   (va_list ap, string *ptrChaine) const;

  int     compatible (const FormatC& f) const;

  // acc�s aux �l�ments canoniques
  const string& chaine  ()      const { return chaine_; }
  int           nbArgs  ()      const { return nbArgs_; }
  int           typeArg (int i) const;

private :
  int     tailleTableType_;
  int     nbArgs_;
  int    *type_;
  string  chaine_;

  void ajouteArg  (int type);
  const char* specificateurSuivant (const char* mobile) const;
};

#endif

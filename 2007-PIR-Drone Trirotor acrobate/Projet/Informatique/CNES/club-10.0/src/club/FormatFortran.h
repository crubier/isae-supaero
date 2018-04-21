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
//>       FormatFortran.h
//
//$Resume
//       fichier d'en-t�te de la classe FormatFortran
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class FormatFortran
//
//$Historique
//       $Log: FormatFortran.h,v $
//       Revision 1.11  2000/10/25 09:31:43  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 1.10  2000/10/24 14:18:14  club
//       mise � jour des includes et ajout des tests de configuration.
//
//       Revision 1.9  2000/09/11 12:18:50  club
//       Mise � jour des include et suppression des tests sur variable de
//       configuration de ClubConfig.h qui n'est pas install�.
//
//       Revision 1.8  2000/09/07 07:46:43  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 1.7  2000/07/03 08:54:19  club
//       Ajout du copyright CNES
//
//       Revision 1.6.2.1  2000/03/30 14:46:54  club
//       ajout du copyright CNES
//
//       Revision 1.6  1999/07/06 15:24:16  club
//       Changement des signatures pour gestion des erreurs
//       par m�canisme d'exception
//
//       Revision 1.5  1998/06/25 06:42:02  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.4  1998/04/26 13:02:25  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.3  1998/01/22 08:30:00  luc
//       ajout d'un en-t�te de classe
//
//       Revision 1.2  1997/08/28 20:18:33  luc
//       modification de la signature de applique pour r�pondre aux besoins
//       des interfaces fortran tradecrch_ et tradecrfd_
//
//       Revision 1.1  1997/08/27 20:57:13  luc
//       Initial revision
//
//$Version
//       $Id: FormatFortran.h,v 1.11 2000/10/25 09:31:43 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut  CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_FormatFortran_h
#define __club_FormatFortran_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <cstdarg>
#include <string>

#include "club/ClubErreurs.h"
#include "club/AnalyseurLexical.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class FormatFortran
//$Resume
//       classe g�rant les formats d'�criture du langage fortran
//
//$Description
//       classe de gestion des formats d'�criture du langage fortran
//       cette classe permet d'analyser les arguments attendus par un
//       format fortran afin de tester la compatibilit� de deux
//       formats (ce m�canisme est utilis� pour la traduction) et afin
//       d'utiliser le format.
//
//$Usage
//>     construction : 
//          sans argument, par une cha�ne de caract�res, par copie
//>     utilisation  : 
//>       FormatFortran& operator =  () 
//          affectation
//>       void analyse               () 
//          analyse la cha�ne format et stocke les arguments attendus
//>       va_list applique           () 
//          applique le format � une s�rie d'arguments r�cup�r�s dans
//          un va_list
//>       int compatible             () 
//          teste si l'instance est compatible avec le format f
//>       int nbArgs                 () 
//          retourne le nombre d'arguments attendus
//>       int typeArg                () 
//          retourne le type attendu pour l'argument i
//>       void ajoutePart            () protegee - 
//>       int modificateurs          () protegee - 
//>       int terme                  () protegee - 
//>       int specificateur          () protegee - 
//>       int liste                  () protegee - 
//>       const string& chaine       () 
//          retourne la cha�ne du format
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut  CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class FormatFortran
{ 
public :
  
  enum { ENTIER, REEL, CHAINE_ARG, BOOLEEN, CHAINE_FIXE, ERREUR };

  // constructeurs et affectation
  FormatFortran ()
    : tailleTableParts_ (0), nombreParts_ (0), type_ (0), formatC_ (0),
      chaine_ ("")
  {}

  FormatFortran (const string& format)
    throw (ClubErreurs)
    : tailleTableParts_ (0), nombreParts_ (0), type_ (0), formatC_ (0)
  { analyse (format); }

  FormatFortran (const FormatFortran& f);
  FormatFortran& operator = (const FormatFortran& f);

  // destructeur
 ~FormatFortran ();

  // traitement du format
  void    analyse    (const string& format)
    throw (ClubErreurs);

  va_list applique   (va_list ap, int nbLong, long int tabLong [],
                      string *ptrChaine) const;

  int     compatible (const FormatFortran& f) const;

  // acc�s aux �l�ments canoniques
  const string&       chaine  ()      const { return chaine_; }
  int                 nbArgs  ()      const;
  int                 typeArg (int i) const;

private :
  int           tailleTableParts_;
  int           nombreParts_;
  int          *type_;
  string       *formatC_;

  string        chaine_;

  void ajoutePart  (int type, const string& format);

  int modificateurs (AnalyseurLexical *al, int *ptrTaille, int *ptrPrecision);
  int terme         (AnalyseurLexical *al);
  int specificateur (AnalyseurLexical *al);
  int liste         (AnalyseurLexical *al);
  
};

#endif

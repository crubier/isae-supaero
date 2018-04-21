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
//>       OptionReel.h
//
//$Resume
//       fichier d'en-t�te de la classe OptionReel
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class OptionReel
//
//$Historique
//       $Log: OptionReel.h,v $
//       Revision 3.11  2003/07/17 12:38:28  club
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 3.10  2002/12/09 15:56:40  club
//       DM-ID 12 Mise en conformit� des constructeurs/destructeurs avec la norme qualit�
//
//       Revision 3.9  2000/09/07 07:41:45  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 3.8  2000/07/03 08:48:31  club
//       Ajout du copyright CNES.
//
//       Revision 3.7.2.1  2000/03/30 14:46:56  club
//       ajout du copyright CNES
//
//       Revision 3.7  1999/07/06 15:24:17  club
//       Changement des signatures pour gestion des erreurs
//       par m�canisme d'exception
//
//       Revision 3.6  1998/07/27 10:14:10  club
//       passage � une configuration de type GNU (fichier ClubConfig.h g�n�r�)
//
//       Revision 3.5  1998/06/25 06:42:51  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//       �limination de la m�thode estValide
//
//       Revision 3.4  1998/01/22 08:33:02  luc
//       am�lioration de l'en-t�te de classe
//
//       Revision 3.3  1997/08/21 16:35:44  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 3.2  1997/03/25 15:01:38  luc
//       changement des r�gles de nommage
//       
//       Revision 3.1  1997/03/19 14:44:50  luc
//       utilisation de la classe ChaineSimple
//       correction du destructeur virtuel
//       renommage de la biblioth�que util_c++ en club
//       passage de SCCS � RCS
//       
//       Revision 2.2  1996/09/25 10:55:33  luc
//       ajout d'un "cast" explicite pour le compilateur (idiot) version 3 de Sun
//       
//       Revision 2.1  1996/07/15 17:18:16  luc
//       �limination de la d�pendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour enti�re et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant g�n�rer des erreurs
//       
//       Revision 1.2  1994/11/09 15:00:04  mercator
//       elimination des directives #pragma
//       
//       Revision 1.1  1994/07/27 11:55:33  luc
//       Initial revision
//
//$Version
//       $Id: OptionReel.h,v 3.11 2003/07/17 12:38:28 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_OptionReel_h
#define __club_OptionReel_h

#include "club/OptionTableauReels.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class OptionReel
//
//$Resume
//       classe des options prenant des arguments r�els
//
//$Description
//       gestion d'une option de la ligne de commande a argument
//       r�el. Cette classe d�rive de OptionTabReels
//
//$Usage
//>     construction : 
//          � partir du code de l'option (sans le '-') et des drapeaux
//          g�n�raux (nombres limites d'occurrences, presence d'une
//          valeur par defaut).
//>     utilisation  : 
//>       OptionReel& operator = () 
//          affectation
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class OptionReel : public OptionTableauReels
{ public :

  // constructeurs
  OptionReel (const char *code,
              int occurrencesMin, int occurrencesMax, int valueeParDefaut,
              double valeur = 0,
              double limiteInf = -1.0e30, double limiteSup = 1.0e30)
    throw (ClubErreurs)
    : OptionTableauReels (code, occurrencesMin, occurrencesMax,
                          valueeParDefaut, 1, &valeur, limiteInf, limiteSup)
    {}

  OptionReel (const string& code,
              int occurrencesMin, int occurrencesMax, int valueeParDefaut,
              double valeur = 0,
              double limiteInf = -1.0e30, double limiteSup = 1.0e30)
    throw (ClubErreurs)
    : OptionTableauReels (code, occurrencesMin, occurrencesMax,
                          valueeParDefaut, 1, &valeur, limiteInf, limiteSup)
      {}

  // copie constructeur et affectation
  OptionReel             (const OptionReel& opt)
    : OptionTableauReels (opt)
  {}

  OptionReel& operator = (const OptionReel& opt);

  // destructeur virtuel
  virtual ~OptionReel () {}

protected :
  OptionReel ()
    throw (ClubErreurs)
    : OptionTableauReels ("", 0, 0, 0, 1, 0, -1.0e30, 1.0e30)
  {}

};

#endif

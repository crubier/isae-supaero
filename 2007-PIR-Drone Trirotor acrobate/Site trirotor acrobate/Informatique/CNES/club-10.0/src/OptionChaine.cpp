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
//>       OptionChaine.cpp
//
//$Resume
//       fichier d'implantation de la classe OptionChaine
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       class OptionChaine
//>         operator =()    
//
//$Historique
//       $Log: OptionChaine.cpp,v $
//       Revision 3.7  2003/02/03 13:43:39  club
//       DM-ID 17 Mise � jour de l'extension du fichier dans le bandeau
//
//       Revision 3.6  2000/07/03 08:57:20  club
//       Ajout du copyright CNES
//
//       Revision 3.5.2.1  2000/03/30 14:46:49  club
//       ajout du copyright CNES
//
//       Revision 3.5  1999/07/07 07:55:16  club
//       Passage a une gestion d'erreurs par exceptions
//
//       Revision 3.4  1998/06/21 15:58:31  luc
//       modification du format de l'en-t�te
//       �limination de la cha�ne statique RCS
//       �limination de la fonction estValide
//
//       Revision 3.3  1997/08/21 16:44:03  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 3.2  1997/03/25 15:04:47  luc
//       changement des r�gles de nommage
//       
//       Revision 3.1  1997/03/19 15:18:13  luc
//       utilisation de la classe ChaineSimple
//       renommage de la classe UtilErreurs en ClubErreurs
//       renommage de la biblioth�que util_c++ en club
//       passage de SCCS � RCS
//       
//       Revision 2.1  1996/07/15 17:17:21  luc
//       �limination de la d�pendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour enti�re et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant g�n�rer des erreurs
//       
//       Revision 1.4  1995/07/12 15:03:40  mercator
//       ajout de signatures pour aider le compilateur SUN a comprendre ...
//       
//       Revision 1.3  1994/11/09 15:01:51  mercator
//       elimination des directives #pragma
//       
//       Revision 1.2  1994/08/10 15:48:06  mercator
//       correction d'une erreur de surcharge de constructeur
//       
//       Revision 1.1  1994/07/27 12:05:52  luc
//       Initial revision
//
//$Version
//       $Id: OptionChaine.cpp,v 3.7 2003/02/03 13:43:39 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "club/OptionChaine.h"

OptionChaine& OptionChaine::operator = (const OptionChaine& opt)
{ if (this != &opt)      // protection contre x = x
    this->OptionTableauChaines::operator = ((const OptionTableauChaines) opt);

  return *this;

}

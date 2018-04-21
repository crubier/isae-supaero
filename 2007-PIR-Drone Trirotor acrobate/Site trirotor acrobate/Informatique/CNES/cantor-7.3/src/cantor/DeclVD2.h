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
//       Cantor
//
//$Nom
//>       DeclVD2.h
//
//$Resume
//       fichier d'en-t�te des template <ValeurDerivee2>
//
//$Description
//       Module de d�claration des types
//
//$Contenu
//>       typedef Vecteur3<ValeurDerivee2> VecVD2
//>       typedef Rotation<ValeurDerivee2> RotVD2
//>       typedef Polynome<ValeurDerivee2> PolVD2
//
//$Historique
//       $Log: DeclVD2.h,v $
//       Revision 1.7  2000/08/09 14:36:44  cantor
//       R�union de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.6.4.1  2000/03/30 15:36:09  cantor
//       ajout du copyright CNES
//
//       Revision 1.6  1998/06/24 10:17:46  luc
//       modification du format de l'en-t�te
//       �limination de la variable statique RCS
//
//       Revision 1.5  1997/07/06 10:26:16  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 1.4  1997/03/26 06:39:42  luc
//       changement des conventions de nommage
//       
//       Revision 1.3  1997/03/24 09:22:14  luc
//       passage de SCCS � RCS
//       
//       Revision 1.2  1994/11/26 15:14:56  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:57:06  luc
//       Initial revision
//
//$Version
//       $Id: DeclVD2.h,v 1.7 2000/08/09 14:36:44 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_DeclVD2_h
#define __cantor_DeclVD2_h

// ce fichier d�clare les classes composites bas�es sur le type ValeurDerivee2

#include "cantor/ValeurDerivee2.h"

#include "cantor/Vecteur3.h"
#include "cantor/Rotation.h"
#include "cantor/Polynome.h"

// renommage des types composites
typedef Vecteur3<ValeurDerivee2> VecVD2;
typedef Rotation<ValeurDerivee2> RotVD2;
typedef Polynome<ValeurDerivee2> PolVD2;

#endif

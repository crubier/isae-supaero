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
//>       DeclDBLVD2.h
//
//$Resume
//       fichier d'en-t�te des templates <double> et <ValeurDerivee2>
//
//$Description
//       Module de regroupement des inclusions
//
//$Contenu
//
//$Historique
//       $Log: DeclDBLVD2.h,v $
//       Revision 1.8  2000/08/09 14:36:43  cantor
//       R�union de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.7.4.1  2000/03/30 15:36:09  cantor
//       ajout du copyright CNES
//
//       Revision 1.7  1998/06/24 10:17:02  luc
//       modification du format de l'en-t�te
//       �limination de la variable statique RCS
//
//       Revision 1.6  1997/07/06 10:26:00  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 1.5  1997/03/26 06:39:40  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 09:22:12  luc
//       passage de SCCS � RCS
//       
//       Revision 1.3  1996/07/16 11:54:45  luc
//       suppression de l'inclusion du fichier des op�rateurs de rotation
//       (il n'y a plus d'op�rateur de rotation apr�s la suppression du ==)
//       
//       Revision 1.2  1994/11/26 15:14:37  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 14:57:03  luc
//       Initial revision
//
//$Version
//       $Id: DeclDBLVD2.h,v 1.8 2000/08/09 14:36:43 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_DeclDBLVD2_h
#define __cantor_DeclDBLVD2_h

// ce fichier regroupe les conversions et combinaisons d'op�rateurs
// entre scalaires et classes composites bas�es sur les types suivants:
//          double
//          ValeurDerivee2

// d�clarations des types
#include "cantor/DeclDBL.h"
#include "cantor/DeclVD2.h"


// d�claration et d�finition de toutes les op�rations entre
// scalaires, vecteurs, rotations et polyn�mes des deux types de base.

// remarque: les fichiers situ�s dans le r�pertoire "conversions"
// sont �crits avec le principe th�orique suivant:
// si le type B est une "restriction" du type A (par exemple A est une
// d�riv�e et B est un r�el simple), alors une op�ration entre un A et un B
// donnera un A, le B ayant �t� "compl�t�" par des 0.
// (ceci n'est bien sur pas vrai pour une op�ration du type B += A, dans
//  ce cas on restreint le type A pour r�aliser l'op�ration).
// sous ces m�mes hypoth�ses, une comparaison entre un A et un B (<, <=, ...)
// sera r�alis�e entre une restriction du A et le B original.

// Dans la pratique, le calcul n'est pas fait en cr�ant un A avec des 0,
// mais par des formules adapt�es � chaque cas, pour des raisons d'efficacit�.

// Ce principe est l'extension naturelle des formules donnant la d�riv�e
// d'une op�ration arithm�tique entre une d�riv�e et un r�el, consid�r�
// comme une fonction constante.

#include "cantor/conversions/ConvDBLVD2.h"
#include "cantor/conversions/CombScalDBLVD2.h"
#include "cantor/conversions/CombVecDBLVD2.h"
#include "cantor/conversions/CombPolDBLVD2.h"

#endif

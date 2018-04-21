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
//>       Variation1.h
//
//$Resume
//       fichier d'en-t�te de la classe Variation1
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class Variation1
//
//$Historique
//       $Log: Variation1.h,v $
//       Revision 1.13  2002/12/10 15:38:21  cantor
//       DM-ID 12 Ajout d'un destructeur pour pr�venir celui cr�� par le compilateur
//
//       Revision 1.12  2002/12/02 13:49:28  cantor
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.11  2000/08/09 14:36:45  cantor
//       R�union de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.10.4.1  2000/03/30 15:36:11  cantor
//       ajout du copyright CNES
//
//       Revision 1.10  1998/06/24 16:28:09  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.9  1998/04/26 15:24:14  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.8  1998/04/14 18:23:22  luc
//       suppression de la m�thode estValide
//
//       Revision 1.7  1998/01/22 10:45:47  luc
//       mise en coh�rence de listes d'initialisation de constructeurs
//       et de l'ordre des attributs dans la classe
//       am�lioration de l'en-t�te de classe
//
//       Revision 1.6  1997/07/06 10:36:51  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 1.5  1997/03/26 06:39:52  luc
//       changement des conventions de nommage
//       
//       Revision 1.4  1997/03/24 09:22:22  luc
//       passage de SCCS � RCS
//       
//       Revision 1.3  1996/07/16 10:56:16  luc
//       �limination de la d�pendance aux tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en cantor_erreurs.h
//       
//       Revision 1.2  1994/11/26 15:16:05  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 15:02:48  luc
//       Initial revision
//
//$Version
//       $Id: Variation1.h,v 1.13 2002/12/10 15:38:21 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Variation1_h
#define __cantor_Variation1_h

#include "cantor/ValeurDerivee1.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Variation1
//
//$Resume
//       mod�lisation de la variation d'une fonction scalaire en un point
//
//$Description
//       mod�lisation de la variation d'une fonction scalaire en un point
//
//$Usage
//>     construction : 
//          sans argument, � partir d'un couple (x, y)
//>     utilisation  : 
//>       Variation1& operator =  () 
//          affectation
//>       int sens                () 
//          retourne le sens de variation
//>       int croissante          () 
//          teste si la fonction est croissante
//>       int decroissante        () 
//          teste si la fonction est d�croissante
//>       int sensValide          () 
//          teste si le sens de variation est valide (c'est � dire non
//          forc�)
//>       double x                () 
//          retourne une copie de l'abscisse de calcul
//>       const ValeurDerivee1& y () 
//          retourne une r�f�rence constante sur la valeur de la
//          fonction
//>       void reinitialise       () 
//          r�initialise l'instance avec les caract�ristiques d'un
//          nouveau point
//>       void simuleCroissante   () 
//          force le sens de variation
//>       void simuleDecroissante () 
//          force le sens de variation
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Variation1
{ 

public :

  // constructeurs
  Variation1 () : sens_ (+1), sensValide_ (0), x_ (0), y_ (0) {}

  Variation1 (double x, const ValeurDerivee1& y)
    : sensValide_ (1), x_ (x), y_ (y)
  { sens_ = (y_.f1 () >= 0.0) ? +1 : -1; }

  // copie constructeur et affectation
  Variation1 (const Variation1& v)
    : sens_ (v.sens_), sensValide_ (v.sensValide_), x_ (v.x_), y_ (v.y_)
  {}

  Variation1& operator = (const Variation1& v);

  // destructeur
  ~Variation1 () {}

  // fonctions d'acc�s aux �l�ments canoniques
  int                   sens         () const { return sens_;               }
  int                   croissante   () const { return (sens_ > 0) ? 1 : 0; }
  int                   decroissante () const { return (sens_ > 0) ? 0 : 1; }
  int                   sensValide   () const { return sensValide_;         }
  double                x            () const { return x_;                  }
  const ValeurDerivee1& y            () const { return y_;                  }

  // fonctions de mise � jour de l'ensemble des attributs
  void              reinitialise (double x, const ValeurDerivee1& y)
  { x_ = x; y_ = y; sens_ = (y_.f1 () >= 0.0) ? +1 : -1; sensValide_ = 1; }

  // fonctions de mise � jour du sens de variation
  void              simuleCroissante   () { sens_ = +1; sensValide_ = 0; }
  void              simuleDecroissante () { sens_ = -1; sensValide_ = 0; }

private :

  int              sens_;
  int              sensValide_;
  double           x_;
  ValeurDerivee1   y_;

};

#endif

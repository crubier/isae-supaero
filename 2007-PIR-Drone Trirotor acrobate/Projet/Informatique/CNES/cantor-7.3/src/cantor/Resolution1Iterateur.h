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
//>       Resolution1Iterateur.h
//
//$Resume
//       fichier d'en-t�te de la classe Resolution1Iterateur
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class Resolution1Iterateur
//
//$Historique
//       $Log: Resolution1Iterateur.h,v $
//       Revision 1.15  2002/12/10 15:09:28  cantor
//       DM-ID 12 Ajout d'un destructeur, d'un operateur d'assignation et d'un constructeur par recopie pour pr�venir ceux cr��s par le compilateur
//
//       Revision 1.14  2002/12/02 13:39:55  cantor
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.13  2001/06/05 15:29:50  cantor
//       suppression d'un argument inutilis�
//
//       Revision 1.12  2000/08/09 14:36:44  cantor
//       R�union de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.11.4.1  2000/03/30 15:36:10  cantor
//       ajout du copyright CNES
//
//       Revision 1.11  1998/07/29 11:50:11  cantor
//       �limination de float.h
//
//       Revision 1.10  1998/06/24 15:21:33  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.9  1998/04/26 15:24:03  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.8  1998/01/22 10:41:50  luc
//       am�lioration de l'en-t�te de classe
//
//       Revision 1.7  1997/07/06 10:31:15  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 1.6  1997/03/26 06:39:48  luc
//       changement des conventions de nommage
//       
//       Revision 1.5  1997/03/24 09:22:17  luc
//       passage de SCCS � RCS
//       
//       Revision 1.4  1996/07/16 10:43:40  luc
//       prise en compte du renommage de erreurs.h en cantor_erreurs.h
//       
//       Revision 1.3  1994/12/12 15:14:41  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.2  1994/11/26 15:15:28  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.1  1994/07/27 15:02:42  luc
//       Initial revision
//
//$Version
//       $Id: Resolution1Iterateur.h,v 1.15 2002/12/10 15:09:28 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Resolution1Iterateur_h
#define __cantor_Resolution1Iterateur_h

#include "cantor/Util.h"
#include "cantor/CantorErreurs.h"
#include "cantor/Resolution1.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Resolution1Iterateur
//
//$Resume
//       it�rateur sur tous les z�ros d'une fonction
//
//$Description
//       it�rateur sur tous les z�ros d'une fonction
//       � l'int�rieur d'un intervalle
//
//$Usage
//>     construction : 
//          � partir de la fonction, d'un pointeur sur un argument,
//          des bornes de l'intervalle, d'un pas (ou d'un nombre
//          d'intervalle) de s�paration des extremums locaux et de
//          seuils de convergence en x et y.
//>     utilisation  : 
//>       void reinitialise             () 
//          r�initialise la recherche
//>       double zeroSuivant            () 
//         retourne une copie de l'abscisse du z�ro suivant (ou un
//         nombre tr�s sup�rieur � la borne sup de l'intervalle de
//         recherche s'il n'y a plus de z�ro)
//>       double convergenceX           () 
//          retourne une copie du seuil de convergence en x
//>       double convergenceY           () 
//          retourne une copie du seuil de convergence en y
//>       ValeurDerivee1 evalueFonction () 
//          retourne la valeur de la fonction en x
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Resolution1Iterateur
{ 

public :

  // constructeurs
  Resolution1Iterateur (TypeFoncVD1 f, void* arg, double a, double b,
                        double pas, double convergenceX, double convergenceY);
  Resolution1Iterateur (TypeFoncVD1 f, void* arg, double a, double b,
                        int n, double convergenceX, double convergenceY);

  // fonctions d'acc�s aux �l�ments
  double         convergenceX  ()         const { return convergenceX_; }
  double         convergenceY  ()         const { return convergenceY_; }

  // calcul de la valeur de la fonction en x
  ValeurDerivee1 evalueFonction (double x) const { return (*f_) (x, arg_); }

  // extraction des z�ros successifs
  void           reinitialise   ();
  double         zeroSuivant    ();

  // destructeur
  ~Resolution1Iterateur () {}

protected :

  // constructeur par d�faut
  Resolution1Iterateur () {}

  // constructeur par copie
  Resolution1Iterateur (const Resolution1Iterateur & other)
  {
    convergenceX_ = other.convergenceX_;
    convergenceY_ = other.convergenceY_;
    tMin_         = other.tMin_;
    tMax_         = other.tMax_;
    pas_          = other.pas_;
    min_          = other.min_;
    max_          =  other.max_;
    precedente_   =  other.precedente_;
    f_            =  other.f_;
    arg_          =  other.arg_;
  }

  // operateur d'assignation
  Resolution1Iterateur & operator = (const Resolution1Iterateur & other)
  {
    if ( this != &other )
    {
      convergenceX_ = other.convergenceX_;
      convergenceY_ = other.convergenceY_;
      tMin_         = other.tMin_;
      tMax_         = other.tMax_;
      pas_          = other.pas_;
      min_          = other.min_;
      max_          =  other.max_;
      precedente_   =  other.precedente_;
      f_            =  other.f_;
      arg_          =  other.arg_;
    }
    return *this;
  }

private :

  double      convergenceX_;
  double      convergenceY_;

  double      tMin_;
  double      tMax_;
  double      pas_;

  Variation1  min_;
  Variation1  max_;
  Variation1  precedente_;

  TypeFoncVD1 f_;
  void*       arg_;

};

#endif

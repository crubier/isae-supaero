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
//       Marmottes
//
//$Nom
//>       FamilleProlongementPi.cpp
//$Resume
//       fichier d'implantation de la classe FamilleProlongementPi
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       class FamilleProlongementPi
//>         FamilleProlongementPi()  
//>         operator =()             
//>         copie()                  
//>         inertielCanonique()      
//$Historique
//       $Log: FamilleProlongementPi.cpp,v $
//       Revision 1.3  2003/02/04 16:26:31  marmottes
//       DM-ID 17 Mise � jour de l'extension du fichier dans le bandeau
//
//       Revision 1.2  2000/03/30 17:01:18  luc
//       ajout du copyright CNES
//
//       Revision 1.1  1999/07/29 12:07:30  filaire
//       Creation de la classe
//       Solutions qui traitent les singularites
//
//
//$Version
//       $Id: FamilleProlongementPi.cpp,v 1.3 2003/02/04 16:26:31 marmottes Exp $
//
//$Auteur
//       G. Filaire CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/FamilleProlongementPi.h"

FamilleProlongementPi::FamilleProlongementPi ()
  : FamilleAbstraite () 
{}

FamilleProlongementPi::FamilleProlongementPi (const Intervalle& plages,
                                              const VecVD1& u1, const VecVD1& u2,
                                              double signe,
                                              double sinMu2, double cosMu2)
  : FamilleAbstraite (plages), u1_ (u1), u2_ (u2), signe_ (signe),
    sinMu_2_ (sinMu2), cosMu_2_ (cosMu2) 
{}

FamilleProlongementPi::FamilleProlongementPi (const FamilleProlongementPi& f)
  : FamilleAbstraite (f), u1_ (f.u1_), u2_ (f.u2_), signe_ (f.signe_),
    sinMu_2_ (f.sinMu_2_), cosMu_2_ (f.cosMu_2_) 
{}

FamilleProlongementPi& FamilleProlongementPi::operator = (const FamilleProlongementPi& f)
{ 
  if (&f != this)     // protection contre x = x
  { 
    FamilleAbstraite::operator = (f);
    u1_      = f.u1_;
    u2_      = f.u2_;
    signe_   = f.signe_;
    sinMu_2_ = f.sinMu_2_;
    cosMu_2_ = f.cosMu_2_;
  }
  return *this;
}

FamilleAbstraite * FamilleProlongementPi::copie () const
{
  return new FamilleProlongementPi (*this);
}

RotVD1 FamilleProlongementPi::inertielCanonique (const ValeurDerivee1& t) const
{ 
  // constitution du mod�le
  // d�termination de l'angle de la rotation autour de v : theta (param�tre libre)
  ValeurDerivee1 theta = transforme (t);

  // �quations du vecteur V1
  ValeurDerivee1 v1X = 0;
  ValeurDerivee1 v1Y = - sin(theta);
  ValeurDerivee1 v1Z = cos(theta);
  VecVD1 v1 = VecVD1 (v1X, v1Y, v1Z);
 
  // R�solution
  ValeurDerivee1 phi = M_PI - asin (tan(0.5 * (M_PI-theta)) / (sinMu_2_ / cosMu_2_));
  if(signe_ < 0.0)
  {
    phi = asin (tan(0.5 * (M_PI-theta)) / (sinMu_2_ / cosMu_2_));
  }

  // �quations du vecteur V2
  ValeurDerivee1 v2X = sinMu_2_ * cos(phi);
  ValeurDerivee1 v2Y = sinMu_2_ * sin(phi);
  ValeurDerivee1 v2Z = cosMu_2_;
  VecVD1 v2 = VecVD1 (v2X, v2Y, v2Z);

  // rotation qui passe de l'inertiel au canonique
  return RotVD1 (u1_, u2_, v1, v2);

}

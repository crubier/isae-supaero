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
//>       FamilleGenerale.h
//
//$Resume
//       fichier d'en-t�te de la classe FamilleGenerale
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class FamilleGenerale
//
//$Historique
//       $Log: FamilleGenerale.h,v $
//       Revision 1.3  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 1.2  1999/11/02 07:19:20  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.1  1999/07/29 12:12:57  filaire
//       Creation de la classe
//       Traite le cas general
//
//
//$Version
//       $Id: FamilleGenerale.h,v 1.3 2000/03/30 17:01:22 luc Exp $
//
//$Auteur
//       G. Filaire CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_FamilleGenerale_h
#define __marmottes_FamilleGenerale_h

#include "cantor/DeclDBLVD1.h"
#include "marmottes/FamilleAbstraite.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class FamilleGenerale
//$Resume
//       mod�le g�om�trique d'attitude (cas g�n�ral)
//
//$Description
//       Cette classe implante un mod�le d'attitude � un degr�  de
//       libert� tel qu'aucun cas particulier d'alignement ne soit rencontr�
//
//$Usage
//>     construction : 
//          sans argument, � partir des caract�ristiques compl�tes du mod�le,
//          par copie
//>     utilisation  : 
//>       FamilleGenerale& operator =      ()
//          affectation 
//>       virtual FamilleAbstraite * copie () 
//          retourne une copie de la famille allou�e en m�moire
//>       RotVD1 inertielCanonique         () 
//          retourne la rotation qui passe du rep�re inertiel au rep�re canonique
//          pour une famille et une valeur du degr� de libert� donn�es
//$<>
///////////////////////////////////////////////////////////////////////////////

class FamilleGenerale : public FamilleAbstraite
{ 
  public :

  // constructeurs
  FamilleGenerale ();
  FamilleGenerale (const Intervalle& plages,
                   const VecVD1& u1, const VecVD1& u2,
                   double signe,
                   double sinMu1, double cosMu1,
                   double sinMu2, double cosMu2,
                   double sinGamma, double cosGamma,
                   double cosAlpha_1_2);
  FamilleGenerale (const FamilleGenerale& f);

  // op�rateur d'affectation
  FamilleGenerale& operator = (const FamilleGenerale& f);

  // op�rateur de copie
  virtual FamilleAbstraite * copie () const;

  // destructeur
  virtual ~FamilleGenerale() {} 
  
  // m�thode qui retourne la rotation de passage du rep�re inertiel au rep�re canonique
  virtual RotVD1 inertielCanonique (const ValeurDerivee1& t) const;

  private :

  VecVD1 u1_;
  VecVD1 u2_;
  double signe_;
  double sinMu_1_;
  double sinMu_2_;
  double cosMu_2_;
  double sinGammaCosMu1_;
  double cosGammaSinMu1_;
  double sinGammaSinMu1_;
  double cosGammaCosMu1_;
  double partieConstante_;
  double cosMu2SinGammaSinMu1_;

};

#endif

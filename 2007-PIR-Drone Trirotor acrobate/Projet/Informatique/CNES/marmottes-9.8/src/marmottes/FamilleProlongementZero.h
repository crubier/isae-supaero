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
//>       FamilleProlongementZero.h
//
//$Resume
//       fichier d'en-t�te de la classe FamilleProlongementZero
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class FamilleProlongementZero
//
//$Historique
//       $Log: FamilleProlongementZero.h,v $
//       Revision 1.3  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 1.2  1999/11/02 07:19:21  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.1  1999/07/29 12:12:07  filaire
//       Creation de la classe
//       Solutions qui traitent les singularites
//
//
//$Version
//       $Id: FamilleProlongementZero.h,v 1.3 2000/03/30 17:01:22 luc Exp $
//
//$Auteur
//       G. Filaire CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_FamilleProlongementZero_h
#define __marmottes_FamilleProlongementZero_h

#include "cantor/DeclDBLVD1.h"
#include "marmottes/FamilleAbstraite.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class FamilleProlongementZero
//$Resume
//       mod�le g�om�trique d'attitude (cas particuler d'alignement)
//
//$Description
//       Cette classe implante un mod�le d'attitude � un degr� de
//       libert� tel que theta rencontre 0 et que Mu1=Gamma=Pi/2
//
//$Usage
//>     construction : 
//          sans argument, � partir des caract�ristiques compl�tes du mod�le,
//          par copie
//>     utilisation  : 
//>       FamilleProlongementZero& operator = ()
//          affectation 
//>       virtual FamilleAbstraite * copie    ()
//          retourne une copie de la famille allou�e en m�moire
//>       RotVD1 inertielCanonique            () 
//          retourne la rotation qui passe du rep�re inertiel au rep�re Canonique
//          pour une famille et une valeur du degr� de libert� donn�es
//$<>
///////////////////////////////////////////////////////////////////////////////

class FamilleProlongementZero : public FamilleAbstraite
{ 
  public :

  // constructeurs
  FamilleProlongementZero ();
  FamilleProlongementZero (const Intervalle& plages,
                           const VecVD1& u1, const VecVD1& u2,
                           double signe,
                           double sinMu2, double cosMu2);
  FamilleProlongementZero (const FamilleProlongementZero& f);

  // op�rateur d'affectation
  FamilleProlongementZero& operator = (const FamilleProlongementZero& f);

  // op�rateur de copie
  virtual FamilleAbstraite * copie() const ;

  // destructeur
  virtual ~FamilleProlongementZero() {}

  // m�thode qui retourne la rotation de passage du rep�re inertiel au rep�re canonique
  virtual RotVD1 inertielCanonique (const ValeurDerivee1& t) const;

  private :

  VecVD1 u1_;
  VecVD1 u2_;
  double signe_;
  double sinMu_2_;
  double cosMu_2_;

};

#endif

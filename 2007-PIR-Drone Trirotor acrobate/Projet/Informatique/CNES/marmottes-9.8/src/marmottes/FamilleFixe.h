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
//>       FamilleFixe.h
//
//$Resume
//       fichier d'en-t�te de la classe FamilleFixe
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class FamilleFixe
//
//$Historique
//       $Log: FamilleFixe.h,v $
//       Revision 1.4  2002/01/17 09:34:40  marmottes
//       (class FamilleFixe): remplacement de l'attribut v1_ par axe_, passage explicite de v1 et de axe dans le constructeur (FA 0007)
//
//       Revision 1.3  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 1.2  1999/11/02 07:19:20  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.1  1999/07/29 12:12:35  filaire
//       Creation de la classe
//       Remplace en partie la classe ModeleGeomV1Fixe
//
//
//$Version
//       $Id: FamilleFixe.h,v 1.4 2002/01/17 09:34:40 marmottes Exp $
//
//$Auteur
//       G. Filaire CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_FamilleFixe_h
#define __marmottes_FamilleFixe_h

#include "cantor/DeclVD1.h"
#include "marmottes/FamilleAbstraite.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class FamilleFixe
//$Resume
//       mod�le g�om�trique d'attitude � un vecteur fig�
//
//$Description
//       Cette classe implante un mod�le d'attitude � un degr� de
//       libert� tel qu'un vecteur particulier de l'espace ait une
//       direction constante quelle que soit la valeur du degr� de
//       libert�.
//
//$Usage
//>     construction : 
//          sans argument, � partir des caract�ristiques compl�tes du mod�le,
//          par copie
//>     utilisation  : 
//>       FamilleFixe& operator =            ()
//          affectation 
//>       virtual FamilleAbstraite * copie   ()
//          retourne une copie de la famille allou�e en m�moire
//>       RotVD1 inertielCanonique           () 
//          retourne la rotation de passage du rep�re inertiel au 
//          rep�re canonique mod�lis�s pour une valeur
//          du degr� de libert� donn�e
//>       const VecVD1& vecteur              () 
//          retourne le premier vecteur (repere inertiel)
//>       const RotVD1& rotation             () 
//          retourne la rotation constante qui permet d'amener 
//          le vecteur fixe � sa place dans le rep�re canonique
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class FamilleFixe : public FamilleAbstraite
{
  public :

  // constructeurs
  FamilleFixe ();
  FamilleFixe (const Intervalle& plages,
               const VecVD1& u1, const VecVD1& u2,
               const VecVD1& v1, const VecVD1& ref,
               const VecVD1& axe);
  FamilleFixe (const FamilleFixe& f);

  // op�rateur d'affectation
  FamilleFixe& operator = (const FamilleFixe& f);

  // op�rateur de copie 
  virtual FamilleAbstraite * copie() const ;

  // destructeur
  virtual ~FamilleFixe () {}

  // retourne la rotation de passage du rep�re inertiel au rep�re canonique
  virtual RotVD1 inertielCanonique (const ValeurDerivee1& t) const ;

  private:

  VecVD1 axe_; // axe de rotation dans le rep�re canonique
               // (le vecteur fixe vaut +/- cet axe)

  RotVD1 r_;   // rotation constante amenant le vecteur fixe
               // � sa place dans le rep�re canonique

};

#endif

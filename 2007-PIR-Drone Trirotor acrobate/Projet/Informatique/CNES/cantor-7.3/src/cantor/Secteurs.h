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
//>       Secteurs.h
//
//$Resume
//       fichier d'en-t�te de la classe Secteurs
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class Secteurs
//
//$Historique
//       $Log: Secteurs.h,v $
//       Revision 1.5  2002/12/10 15:35:45  cantor
//       DM-ID 12 Ajout d'un destructeur pour pr�venir celui cr�� par le compilateur
//
//       Revision 1.4  2002/12/02 13:48:32  cantor
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.3  2002/09/03 15:22:48  cantor
//       renommage de la m�thode vecteurs en diedre (FA15)
//
//       Revision 1.2  2001/06/12 12:48:21  cantor
//       utilisation du type bool pour les valeurs de retour des pr�dicats
//
//       Revision 1.1  2001/06/05 15:23:14  cantor
//       version initiale
//
//$Version
//       $Id: Secteurs.h,v 1.5 2002/12/10 15:35:45 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Secteurs_h
#define __cantor_Secteurs_h

#include "cantor/MathPi.h"
#include "cantor/DeclVD1.h"
#include "cantor/Creneau.h"
#include "cantor/Cone.h"
#include "cantor/CantorErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Secteurs
//
//$Resume
//       mod�lisation des secteurs visibles d'un c�ne projet� sur la sph�re unit�
//
//$Description
//       mod�lisation des secteurs visibles d'un c�ne projet�
//       sur la sph�re unit�
//
//$Usage
//>     construction : 
//          sans argument, � partir d'un c�ne, � partir d'un c�ne
//          d'un vecteur et d'un cr�neau, par copie
//>     utilisation  : 
//>       Secteurs& operator =    () 
//          affectation
//>       void intersection       () 
//          limite la partie visible du c�ne
//>       bool diedreContient     () 
//          teste si un vecteur est dans l'un des di�dres
//>       void vecteurs           () 
//          rempli les vecteurs de d�finition du i-�me secteur.
//>       void modifieReference   () 
//          change le vecteur de r�f�rence
//>       void tourne             () 
//          tourne l'ensemble des vecteurs selon la rotation donn�e
//>       int nombre              () 
//          retourne le nombre de secteurs visibles.
//>       bool vide               () 
//          indique si le c�ne est compl�tement vide.
//>       bool nonVide            () 
//          indique si le c�ne est partiellement visible.
//>       const Cone& cone        () 
//          retourne le c�ne de base.
//>       double angle            () 
//          retourne le demi-angle d'ouverture du c�ne.
//>       const VecDBL& reference () 
//          retourne le vecteur de r�f�rence � partir duquel sont
//          compt�s les angles d�crivant les portions visibles
//>       const Creneau& creneau  () 
//          retourne les portions angulaires visibles
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Secteurs
{

public :

  // constructeurs
  Secteurs ();
  Secteurs (const Cone& base);
  Secteurs (const Cone& base, const VecDBL& reference, const Creneau& visible)
    throw (CantorErreurs);
  Secteurs (const Secteurs& s)
    : base_ (s.base_), x_ (s.x_), y_ (s.y_), zNonNorme_ (s.zNonNorme_),
      visible_ (s.visible_)
  {}

  Secteurs& operator = (const Secteurs& s);

  // destructeur
  ~Secteurs () {}

  void           intersection (const Cone& c);
  int            nombre       () const { return   visible_.nombre ();  }
  bool           vide         () const { return   visible_.vide   ();  }
  bool           nonVide      () const { return !(visible_.vide   ()); }
  bool           diedreContient (const VecDBL& u) const
                 { return visible_.contient (atan2 (u | y_, u | x_)); }


  const Cone&    cone         () const { return   base_;               }
  double         angle        () const { return   base_.angle     ();  }
  const VecDBL&  reference    () const { return   x_;                  }
  const Creneau& creneau      () const { return   visible_;            }
  void           diedre       (int i,
                               VecDBL *ptrAxe,
                               VecDBL *ptrPlanDebut, VecDBL *ptrPlanFin,
                               double *ptrBalayage)  const;

  void           modifieReference (const VecDBL& reference);
  void           tourne           (const RotDBL& r);

private :

  Cone     base_;
  VecDBL   x_;
  VecDBL   y_;
  VecDBL   zNonNorme_;
  Creneau  visible_;

};

#endif

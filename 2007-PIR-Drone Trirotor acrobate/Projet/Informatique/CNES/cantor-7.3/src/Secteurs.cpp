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
//>       Secteurs.cpp
//
//$Resume
//       fichier d'implantation de la classe Secteurs
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       class Secteurs      
//>         Secteurs()        
//>         operator =()      
//>         intersection()    
//>         diedre()        
//>         modifieReference()
//>         tourne()          
//$Historique
//       $Log: Secteurs.cpp,v $
//       Revision 1.5  2003/02/04 09:30:07  cantor
//       DM-ID 17 Mise � jour du nom du fichier dans le bandeau suite � la modification des extensions.
//
//       Revision 1.4  2002/09/03 15:06:48  cantor
//       modification de la m�thode 'vecteur' en m�thode 'diedre' (FA15)
//
//       Revision 1.3  2002/01/17 08:41:34  cantor
//       correction d'une erreur d'�chelle conduisant les vecteurs d�but et fin � ne pas �tre norm�s pour des c�nes de demi ouverture diff�rente de PI/2
//
//       Revision 1.2  2001/06/08 13:00:15  cantor
//       ajout d'un recalage entre -PI et PI des angles
//       dans le constructeur par vecteur et cr�neau
//
//       Revision 1.1  2001/06/05 15:42:11  cantor
//       initial version
//
//$Version
//       $Id: Secteurs.cpp,v 1.5 2003/02/04 09:30:07 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Secteurs.h"
#include "cantor/Util.h"

Secteurs::Secteurs ()
  : visible_ (-M_PI, M_PI)
{ zNonNorme_  = base_.axe ();
  x_          = zNonNorme_.orthogonal ();
  y_          = zNonNorme_ ^ x_;

  // raccourcissement de z
  zNonNorme_ *= base_.cosinus ();

}

Secteurs& Secteurs::operator = (const Secteurs& s)
{ if (&s != this)     // protection contre x = x
  { base_      = s.base_;
    x_         = s.x_;
    y_         = s.y_;
    zNonNorme_ = s.zNonNorme_;
    visible_   = s.visible_;
  }

  return *this;
  
}

Secteurs::Secteurs (const Cone& base)
  : base_ (base), visible_ (-M_PI, M_PI)
{ // constitution d'une base orthonorm�e
  zNonNorme_  = base_.axe ();
  x_          = zNonNorme_.orthogonal ();
  y_          = zNonNorme_ ^ x_;

  // raccourcissement de z
  zNonNorme_ *= base_.cosinus ();

}

Secteurs::Secteurs (const Cone& base, const VecDBL& reference,
                    const Creneau& visible)
  throw (CantorErreurs)
  : base_ (base)
{ // constitution d'une base orthonorm�e
  zNonNorme_  = base_.axe ();
  x_          = reference - (reference | zNonNorme_) * zNonNorme_;
  x_.normalise ();
  y_          = zNonNorme_ ^ x_;

  // raccourcissement de z
  zNonNorme_ *= base_.cosinus ();

  // recalage des intervalles entre -PI et PI
  for (int i = 0; i < visible.nombre (); ++i)
  {
    Intervalle original = visible [i];
    double inf = recaleAngle (original.inf (), 0.0);
    double sup = original.sup () + inf - original.inf ();
    if (sup > M_PI)
    { // l'intervalle se projette dans [-PI; PI] en deux tron�ons
      visible_ += Intervalle (inf, M_PI);
      visible_ += Intervalle (-M_PI, sup - (M_PI + M_PI));
    }
    else
      visible_ += Intervalle (inf, sup);
  }

}

void Secteurs::intersection (const Cone& c)
{ // calcul des vecteurs d�limitant la partie visible des secteurs
  VecDBL debVis;
  VecDBL finVis;

  try
  {
    base_.intersection (c, &debVis, &finVis);
  }
  catch (CantorErreurs ce)
  { // le c�ne de base est soit enti�rement cach�, soit enti�rement visible
    ce.correction ();

    if ((base_.angle () >= c.angle ())
        ||
        (c.axe ().angleAvecVecteur (base_.axe ()) > c.angle ()))
    { // tout le c�ne de base est cach�
      visible_.nettoie ();
    }

    return;

  }

  // projection dans le plan normal � l'axe
  debVis -= zNonNorme_;
  finVis -= zNonNorme_;

  // transformation du secteur de plan en intervalle d'angles
  double thetaDeb = atan2 ((debVis | y_), (debVis | x_));
  double thetaFin = atan2 ((finVis | y_), (finVis | x_));

  // intersection de cet intervalle avec le partitionnement en secteurs
  if (thetaDeb <= thetaFin)
  { // l'intervalle est d'une pi�ce dans [-PI; PI]
    visible_ *= Intervalle (thetaDeb, thetaFin);
  }
  else
  { // l'intervalle se projette dans [-PI; PI] en deux tron�ons

    // cr�ation d'un cr�neau comprenant les deux tron�ons
    Creneau deuxTroncons (Intervalle (-M_PI, thetaFin));
            deuxTroncons += Intervalle (thetaDeb, M_PI);

    // intersection du cr�neau courant avec les deux tron�ons
    visible_ = visible_ * deuxTroncons;

  }

}

void Secteurs::diedre (int i, VecDBL *ptrAxe,
                       VecDBL *ptrPlanDebut, VecDBL *ptrPlanFin,
                       double *ptrBalayage)  const
{ // remplissage de l'axe
  *ptrAxe = base_.axe ();

  // r�cuperation du i-�me intervalle angulaire
  Intervalle inter = visible_ [i];

  // calcul de vecteurs dans les plans m�ridiens d�but et fin
  // (ce ne sont PAS les vecteurs d�but et fin de l'arc lui-m�me)
  double inf    = inter.inf ();
  double sup    = inter.sup ();
  *ptrPlanDebut = cos (inf) * x_ + sin (inf) * y_;
  *ptrPlanFin   = cos (sup) * x_ + sin (sup) * y_;

  *ptrBalayage = sup - inf;

}

void Secteurs::modifieReference (const VecDBL& reference)
{ // modification du vecteur de r�f�rence

  // azimut du nouveau vecteur de r�f�rence
  double delta = atan2 (reference | y_, reference | x_);
  if (delta < 0.0)
    delta += M_PI + M_PI;

  // cr�ation d'un cr�neau �tendu en raboutant deux copies
  // dont l'une est d�cal�e de 2pi
  Creneau etendu (visible_);
  etendu.decale (M_PI + M_PI);
  etendu += visible_;

  // calage sur la nouvelle origine
  etendu.decale (-delta);

  // limitation entre -pi et pi
  visible_ = etendu * Intervalle (-M_PI, M_PI);

  // recalage des vecteurs
  double cos_delta = cos (delta);
  double sin_delta = sin (delta);
  VecDBL u =  cos_delta * x_ + sin_delta * y_;
  y_       = -sin_delta * x_ + cos_delta * y_;
  x_       = u;

}

void Secteurs::tourne (const RotDBL& r)
{ // rotation de l'ensemble des secteurs
  base_      = Cone (r (base_.axe ()), base_.angle ());
  x_         = r (x_);
  y_         = r (y_);
  zNonNorme_ = r (zNonNorme_);
}

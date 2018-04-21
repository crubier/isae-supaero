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
//>       Arc.cpp
//
//$Resume
//       fichier d'implantation de la classe Arc
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       class Arc           
//>         initVecteurs()    
//>         Arc()             
//>         operator =()      
//>         proche()        
//>         distance()        
//>         diedreContient()  
//>         partage()         
//>         intersection()    
//>         appliqueRotation()
//>         recouvre()        
//>         balaye()        
//
//$Historique
//       $Log: Arc.cpp,v $
//       Revision 2.18  2003/02/04 09:24:14  cantor
//       DM-ID 17 Mise � jour du nom du fichier dans le bandeau suite � la modification des extensions.
//
//       Revision 2.17  2002/09/03 14:58:08  cantor
//       ajout de nouvelles m�thodes, modification (FA15)
//
//       Revision 2.16  2002/09/02 09:17:59  cantor
//       correction mineure d'une faute de frappe
//
//       Revision 2.15  2002/02/04 09:19:29  cantor
//       correction des tests d'intersections de c�nes dans les cas limites
//
//       Revision 2.14  2001/09/18 16:08:38  cantor
//       ajout de la m�thode Arc::proche
//
//       Revision 2.13  2001/08/23 15:08:52  cantor
//       autorisation de la construction d'arcs avec des balayages n�gatifs
//
//       Revision 2.12  2001/06/05 15:48:55  cantor
//       remont�e d'exception g�n�r�es par les classes sous-jacentes
//
//       Revision 2.11  2000/11/10 15:48:39  cantor
//       correction d'erreurs diverses dans les calculs d'intersections d'arcs
//       pour les cas d�g�n�r�s
//
//       Revision 2.10  2000/10/18 15:59:20  cantor
//       correction sur le traitement des cas extr�mes dans les calculs
//       d'intersection d'arcs.
//
//       Revision 2.9  2000/08/09 14:36:41  cantor
//       R�union de la branche 5.2.2 dans le tronc principal.
//
//       Revision 2.8.4.2  2000/07/31 15:56:35  cantor
//       s�paration des cas d�g�n�r�s de s�paration autour du d�but et autour
//       de la fin de l'arc. L'arc nul produit est bien proche du point de
//       coupure (auparavant l'arc d�g�n�r� �tait syst�matiquement le second,
//       m�me si le point de partage �tait au d�but).
//
//       Revision 2.8.4.1  2000/03/30 15:36:04  cantor
//       ajout du copyright CNES
//
//       Revision 2.8  1998/06/24 10:06:58  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 2.7  1998/04/26 15:23:40  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.6  1998/04/18 19:07:02  luc
//       �limination de la m�thode estValide
//
//       Revision 2.5  1997/07/08 13:01:21  luc
//       ajout d'un en-t�te de fichier
//       ajout d'une m�thode de test des recouvrements
//       modification des epsilons
//       s�paration en deux fichiers Arc.cc et ArcIterateur.cc
//
//       Revision 2.4  1997/03/26 06:54:27  luc
//       changement des conventions de nommage
//       
//       Revision 2.3  1997/03/24 09:32:36  luc
//       passage de SCCS � RCS
//       
//       Revision 2.2  1996/08/06 17:15:40  luc
//       ajout d'un constructeur
//       
//       Revision 2.1  1996/07/24 10:54:24  luc
//       refonte de la classe
//       (ajout des m�thodes distance, diedreContient, partage, intersection,
//       appliqueRotation, - unaire)
//       
//       Revision 1.4  1995/01/25 16:14:41  mercator
//       ajout de const devant les arguments reference des constructeurs
//       
//       Revision 1.3  1994/11/26 15:16:25  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.2  1994/08/11 13:59:50  mercator
//       ajout de qualificatifs const dans la signature de initvecteurs
//       
//       Revision 1.1  1994/07/27 14:53:15  luc
//       Initial revision
//
//$Version
//       $Id: Arc.cpp,v 2.18 2003/02/04 09:24:14 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/MathPi.h"
#include "cantor/Arc.h"


// Les calculs sur les arcs ne sont r�alisables que dans certaines
// plages (les c�nes trop fins par exemples ne permettent pas des
// calculs pr�cis). Il est donc n�cessaire de g�rer certains
// seuils. Ceci est �galement vrai pour les calculs sur les champs
// (voir la classe Champ). La classe Champ s'appuyant sur la classe
// Arc, il est n�cessaire que les epsilons de Champ soient au moins
// l�g�rement sup�rieurs � ceux de Arc. Il a �t� d�cid� de prendre
// 4.85e-6 pour Champ, ce qui repr�sente une seconde d'arc (ou son
// sinus, � ce niveau la distinction n'est pas perceptible) et de
// prendre 3.16e-6 pour Arc, ce qui repr�sente la racine de 1.0e-11
// (qui est utilis� dans des soustractions de nombres aux alentours de
// 1.0).
const double ArcEpsilon  = 3.16e-6;
const double ArcEpsilon2 = ArcEpsilon * ArcEpsilon;

Arc::Arc (const VecDBL& debut, const VecDBL& fin)
  throw (CantorErreurs)
{
  VecDBL axe = debut ^ fin;
  if (axe.norme () < ArcEpsilon)
    initVecteurs (debut.orthogonal (), 0.5 * M_PI, debut, fin);
  else
    initVecteurs (debut ^ fin, 0.5 * M_PI, debut, fin);
}

void Arc::initVecteurs (const VecDBL& axe, double alpha,
                        const VecDBL& debut, const VecDBL& fin)
  throw (CantorErreurs)
{ // ajustement des vecteurs sur la sph�re unit�
  axe_ = axe   / axe.norme   ();
  deb_ = debut / debut.norme ();
  fin_ = fin   / fin.norme   ();

  if (alpha < 0.0)
    alpha = 0.0;
  else if (alpha > M_PI)
    alpha = M_PI;
  cos_   = cos (alpha);
  sin_   = sin (alpha);
  angle_ = alpha;

  // ajustement de l'�cartement des vecteurs
  w_ = axe_ * cos_;

  double scal = axe_ | deb_;
  double s = sqrt (1.0 - scal * scal);
  if (s < ArcEpsilon2)
    throw CantorErreurs(CantorErreurs::alignement_axe_extremite);
  deb_ = w_ + (deb_ - scal * axe_) * (sin_ / s);

  scal = axe_ | fin_;
  s = sqrt (1.0 - scal * scal);
  if (s < ArcEpsilon2)
    throw CantorErreurs(CantorErreurs::alignement_axe_extremite);
  fin_ = w_ + (fin_ - scal * axe_) * (sin_ / s);

  // calcul du rep�re canonique (orthogonal non norm�) de l'arc
  u_ = deb_ - w_;
  v_ = axe_ ^ u_;

  // calcul de l'angle de balayage autour de l'axe (entre 0 et 2PI)
  if (sin_ < ArcEpsilon)
    balayage_ = 0.0;
  else
    balayage_ = M_PI + atan2 (-(fin_ | v_), -(fin_ | u_));

}

Arc::Arc (const VecDBL& axe, double angle)
  throw (CantorErreurs)
{ // calcul d'un vecteur d�but arbitraire, pour faire un tour
  VecDBL debut = axe.orthogonal ();

  // mise en place des vecteurs
  initVecteurs (axe, angle, debut, debut);
  balayage_ = M_PI + M_PI;

}

Arc::Arc (const Cone& c)
  throw (CantorErreurs)
{ // calcul d'un vecteur d�but arbitraire, pour faire un tour
  VecDBL debut = c.axe ().orthogonal ();

  // mise en place des vecteurs
  initVecteurs (c.axe (), c.angle (), debut, debut);
  balayage_ = M_PI + M_PI;

}

Arc::Arc (const VecDBL& axe, double angle,
          const VecDBL& debut, double balayage)
  throw (CantorErreurs)
{ // on commence par initialiser les vecteurs
  // de fa�on � faire un quart de tour
  if (balayage < 0.0)
    initVecteurs (-axe, M_PI - angle, debut, debut ^ axe);
  else
    initVecteurs (axe, angle, debut, axe ^ debut);

  // correction de la fin selon l'angle de balayage d�sir�
  balayage_ = fabs (balayage);
  fin_      = intermediaire (balayage_);

}

Arc& Arc::operator = (const Arc& a)
{ if (this != &a)       // protection contre x = x
  { axe_      = a.axe_;
    cos_      = a.cos_;
    sin_      = a.sin_;
    angle_    = a.angle_;
    deb_      = a.deb_;
    fin_      = a.fin_;
    u_        = a.u_;
    v_        = a.v_;
    w_        = a.w_;
    balayage_ = a.balayage_;
  }

  return *this;

}

VecDBL Arc::proche (const VecDBL& p) const
{ // calcul du point le plus proche d'un point donn�

  // coordonn�es dans le plan normal du vecteur test�
  double x  = p | u_;
  double y  = p | v_;
  double r2 = x * x + y * y;

  if (r2 > ArcEpsilon2)
  { // le point est raisonnablement �loign� de l'axe
    if (M_PI + atan2 (-y, -x) <= balayage_)
    { // le point test� est dans le di�dre couvert par l'arc
      // c'est sa projection sur le c�ne qui d�termine sa distance � l'arc
      double r = sqrt (r2);
      return u_ * (x / r) + v_ * (y / r) + w_;
    }
  }

  // c'est une des extr�mit�s de l'axe qui d�termine la distance
  double d1 = p.angleAvecVecteur (deb_);
  double d2 = p.angleAvecVecteur (fin_);

  return (d1 < d2) ? deb_ : fin_;

}

double Arc::distance (const VecDBL& p) const
{ // �valuation de la distance � l'arc d'un point quelconque

  // coordonn�es dans le plan normal du vecteur test�
  double x  = p | u_;
  double y  = p | v_;
  double r2 = x * x + y * y;

  if (r2 > ArcEpsilon2)
  { // le point est raisonnablement �loign� de l'axe
    if (M_PI + atan2 (-y, -x) <= balayage_)
    { // le point test� est dans le di�dre couvert par l'arc
      // c'est sa projection sur le c�ne qui d�termine sa distance � l'arc
      double r = sqrt (r2);
      return p.angleAvecVecteur (u_ * (x / r) + v_ * (y / r) + w_);
    }
  }

  // c'est une des extr�mit�s de l'axe qui d�termine la distance
  double d1 = p.angleAvecVecteur (deb_);
  double d2 = p.angleAvecVecteur (fin_);

  return (d1 < d2) ? d1 : d2;

}

bool Arc::diedreContient (const VecDBL& p) const
{ // test d'appartenance d'un point au di�dre d�fini par l'arc

  // coordonn�es du vecteur test� dans le plan normal � l'axe de l'arc
  double x = p | u_;
  double y = p | v_;

  if (x * x + y * y > ArcEpsilon2)
  { // le point est raisonnablement �loign� de l'axe
    double alpha = M_PI + atan2 (-y, -x);
    return ((alpha < (balayage_ + 1.1 * ArcEpsilon))
            ||
            (alpha > (M_PI + M_PI - 1.1 * ArcEpsilon))) ? 1 : 0;
  }
  else
    return 1;

}

void Arc::partage (const VecDBL& p, Arc *ptrAv, Arc *ptrAp) const
{ // d�coupage de l'arc de part et d'autre d'un point

  // coordonn�es du vecteur test� dans le plan normal � l'axe de l'arc
  double x = p | u_;
  double y = p | v_;

  // sauvegarde des param�tres de construction de l'instance
  // (au cas o� l'un des pointeurs corresponde au pointeur this)
  VecDBL axe      = axe_;
  double angle    = angle_;
  VecDBL debut    = deb_;
  VecDBL fin      = fin_;
  double balayage = balayage_;

  double alpha = (x * x + y * y > ArcEpsilon2) ?
                 M_PI + atan2 (-y, -x) : 0.5 * balayage_;
  VecDBL interm = cos (alpha) * u_ + sin (alpha) * v_ + w_;
  if ((alpha < 0.0) || (interm.angleAvecVecteur (debut) <= ArcEpsilon))
  { // le point est hors du di�dre (ou trop pr�s du d�but)

    // le premier est d�g�n�r� en un arc nul
    // (en faisant attention de bien avoir un balayage nul et pas de 2PI)
    ptrAv->initVecteurs (axe, angle, debut, debut);
    ptrAv->balayage_ = 0.0;

    // le deuxi�me sous-arc est sous-arc est une copie de l'arc complet
    ptrAp->initVecteurs (axe, angle, debut, fin);
    ptrAp->balayage_ = balayage;

  }
  else
  {
    if ((alpha > balayage_) || (interm.angleAvecVecteur (fin) <= ArcEpsilon))
    { // le point est hors du di�dre (ou trop pr�s de la fin)

      // le premier sous-arc est une copie de l'arc complet
      ptrAv->initVecteurs (axe, angle, debut, fin);
      ptrAv->balayage_ = balayage;

      // le deuxi�me sous-arc est d�g�n�r� en un arc nul
      // (en faisant attention de bien avoir un balayage nul et pas de 2PI)
      ptrAp->initVecteurs (axe, angle, fin, fin);
      ptrAp->balayage_ = 0.0;

    }
    else
    { // cas standard : il existe un point interm�diaire entre les sous-arcs
      VecDBL interm = cos (alpha) * u_ + sin (alpha) * v_ + w_;

      ptrAv->initVecteurs (axe, angle, debut, interm);
      ptrAp->initVecteurs (axe, angle, interm, fin);
    }
  }

}

void Arc::intersection (const VecDBL& a, double cosinus,
                        int *ptrNbInt, VecDBL *ptrV1, VecDBL *ptrV2) const
{ // calcul de l'intersection d'un arc et d'un c�ne
  *ptrNbInt = 0;

  double cMoinsWA = cosinus - (w_ | a);

  // traitement des cas particuliers
  if ((axe_ ^ a).norme () < ArcEpsilon2)
  { // l'arc et le c�ne sont coaxiaux

    if ((cMoinsWA * cMoinsWA) < (ArcEpsilon2 * sin_ * sin_))
    { // l'arc et le c�ne sont superpos�s
      // on consid�re les extr�mit�s de l'arc comme des points d'intersection
      *ptrNbInt = 2;
      *ptrV1    = deb_;
      *ptrV2    = fin_;
    }

    return;

  }

  // pr�paration de la r�solution de l'�quation du second degr�
  double       ua = u_ | a;
  double       va = v_ | a;
  double plus     = ua * ua + va * va;
  double delta2   = plus - cMoinsWA * cMoinsWA;

  if (delta2 >= 0.0)
  { // l'�quation est r�soluble : il y a des intersections
    double racine = sqrt (delta2);
    double      x = (cMoinsWA * ua - racine * va) / plus;
    double      y = (cMoinsWA * va + racine * ua) / plus;
    double alpha1 = M_PI + atan2 (-y, -x);
    VecDBL v1     = x * u_ + y * v_ + w_;
    if ((alpha1 < balayage_)
        || (v1.angleAvecVecteur (deb_) < ArcEpsilon)
        || (v1.angleAvecVecteur (fin_) < ArcEpsilon))
    { // le premier point d'intersection des c�nes appartient bien � l'arc
      (*ptrNbInt)++;
      *ptrV1 = v1;
    }

    x = (cMoinsWA * ua + racine * va) / plus;
    y = (cMoinsWA * va - racine * ua) / plus;
    double alpha2 = M_PI + atan2 (-y, -x);
    VecDBL v2 = x * u_ + y * v_ + w_;
    if ((alpha2 < balayage_)
        || (v2.angleAvecVecteur (deb_) < ArcEpsilon)
        || (v2.angleAvecVecteur (fin_) < ArcEpsilon))
    { // le second point d'intersection des c�nes appartient bien � l'arc
      if ((*ptrNbInt)++)
      { // il y avait d�j� un point d'intersection dans l'arc
        if (alpha1 <= alpha2)
          *ptrV2 = v2;
        else
        {
          *ptrV1 = v2;
          *ptrV2 = v1;
        }
      }
      else
        *ptrV1 = v2;
    }
  }

}

void Arc::intersection (const Arc& a,
                        int *ptrNbInt, VecDBL *ptrV1, VecDBL *ptrV2) const
{ // calcul de l'intersection de deux arcs
  *ptrNbInt = 0;

  double cMoinsWA = a.cos_ - (w_ | a.axe_);

  // traitement des cas particuliers
  if ((axe_ ^ a.axe ()).norme () < ArcEpsilon2)
  { // les deux arcs sont coaxiaux

    if ((cMoinsWA * cMoinsWA) < (ArcEpsilon2 * sin_ * sin_))
    { // les deux arcs sont superpos�s

      // calcul des angles du second arc dans le rep�re du premier
      bool memeSens  = ((axe_ | a.axe_) > 0.0);
      VecDBL v1     = memeSens ? a.deb_ : a.fin_;
      double alpha1 = M_PI + atan2 (-(v1 | v_), -(v1 | u_));
      VecDBL v2     = memeSens ? a.fin_ : a.deb_;
      double alpha2 = alpha1 + a.balayage_;

      // si les arcs ont une partie commune
      // ses extr�mit�s seront consid�r�es commes les points d'intersection
      if ((alpha1 < balayage_) || (v1.angleAvecVecteur (fin_) < ArcEpsilon))
      { // l'arc commence avant la fin de l'instance
        *ptrNbInt = 2;

        if ((alpha2 > M_PI + M_PI)
            || (v2.angleAvecVecteur (deb_) < ArcEpsilon))
         { // l'arc sort de l'instance puis revient en recouvrir le d�but
           *ptrV1 = (alpha2 > M_PI + M_PI) ? v2 : deb_;
           *ptrV2 = (alpha1 < balayage_) ? v1 : fin_;
         }
         else
         { // l'arc se termine soit avant soit apr�s la fin de l'instance
           *ptrV1 = (alpha1 < balayage_) ? v1 : fin_;
           *ptrV2 = (alpha2 < balayage_) ? v2 : fin_;
         }

      }
      else
      { // l'arc commence apr�s la fin de l'instance
        alpha2 -= M_PI + M_PI;

        if ((alpha2 > 0)
            || (v2.angleAvecVecteur (deb_) < ArcEpsilon))
        { // l'arc revient recouvrir le d�but ou toute l'instance
          *ptrNbInt = 2;
          *ptrV1    = deb_;
          *ptrV2    = (alpha2 < balayage_) ? v2 : fin_;
        }

      }

      return;
    }

  }

  // pr�paration de la r�solution de l'�quation du second degr�
  double       ua = u_ | a.axe_;
  double       va = v_ | a.axe_;
  double plus     = ua * ua + va * va;
  double delta2   = plus - cMoinsWA * cMoinsWA;

  if (delta2 >= 0.0)
  { // l'�quation est r�soluble : il y a des intersections
    double racine = sqrt (delta2);
    double      x = (cMoinsWA * ua - racine * va) / plus;
    double      y = (cMoinsWA * va + racine * ua) / plus;
    double alpha1 = M_PI + atan2 (-y, -x);
    VecDBL v1     = x * u_ + y * v_ + w_;
    if ((alpha1 < balayage_)
        || (v1.angleAvecVecteur (deb_) < ArcEpsilon)
        || (v1.angleAvecVecteur (fin_) < ArcEpsilon))
    { // le premier point d'intersection des c�nes appartient bien � l'arc
      (*ptrNbInt)++;
      *ptrV1 = v1;
    }

    x = (cMoinsWA * ua + racine * va) / plus;
    y = (cMoinsWA * va - racine * ua) / plus;
    VecDBL v2     = x * u_ + y * v_ + w_;
    double alpha2 = M_PI + atan2 (-y, -x);
    if ((alpha2 < balayage_)
        || (v2.angleAvecVecteur (deb_) < ArcEpsilon)
        || (v2.angleAvecVecteur (fin_) < ArcEpsilon))
    { // le second point d'intersection des c�nes appartient bien � l'arc
      if ((*ptrNbInt)++)
      { // il y avait d�j� un point d'intersection dans l'arc
        if (alpha1 <= alpha2)
          *ptrV2 = v2;
        else
        {
          *ptrV1 = v2;
          *ptrV2 = v1;
        }
      }
      else
        *ptrV1 = v2;
    }
  }

  // prise en compte des limitations de l'autre arc
  if ((*ptrNbInt == 2) && (! a.diedreContient (*ptrV2)))
    (*ptrNbInt)--;
  if (*ptrNbInt && (! a.diedreContient (*ptrV1)))
  { (*ptrNbInt)--;
    if (*ptrNbInt)
      *ptrV1 = *ptrV2;
  }

}

void Arc::appliqueRotation (const RotDBL& r)
{ // transformation de l'instance par rotation
  axe_ = r (axe_);
  deb_ = r (deb_);
  fin_ = r (fin_);
  u_   = r (u_);
  v_   = r (v_);
  w_   = r (w_);
}

bool Arc::recouvre (const Arc& a, double epsilon) const
{ // indique si tous les points de a sont � moins de epsilon de l'instance

  if (distance (a.deb_) > epsilon)
    return 0;

  // il y a au moins un point proche, tous les autres points de a sont
  // proches si a ne traverse jamais les arcs f1, f2, ... constituant
  // une fronti�re construite � la distance epsilon de l'instance (en
  // tenant compte de la marge ArcEpsilon interne � la classe)
  epsilon += ArcEpsilon;
  int    nbInt;
  VecDBL v1, v2;

  if (angle_ - epsilon > 0.0)
  { // il y a une fronti�re int�rieure (entre l'arc et l'axe de l'instance)
    Arc f1 (axe_, angle_ - epsilon, deb_, fin_);
    f1.intersection (a, &nbInt, &v1, &v2);
    if (nbInt)
      return 0;
  }

  if (angle_ + epsilon < M_PI)
  { // il y a une fronti�re ext�rieure (au del� de l'arc de l'instance)
    Arc f2 (axe_, angle_ + epsilon, deb_, fin_);
    f2.intersection (a, &nbInt, &v1, &v2);
    if (nbInt)
      return 0;
  }

  if ((angle_ - epsilon <= 0.0) || (angle_ + epsilon >= M_PI))
    return 1; // pour des arcs aussi petits, on ne cherche pas plus loin ...

  // fronti�res aux extr�mit�s de l'instance (deux demi-c�nes)
  Arc f3 (deb_, epsilon, axe_, (cos_ + cos_) * deb_ - axe_);
  Arc f4 (fin_, epsilon, (cos_ + cos_) * fin_ - axe_, axe_);

  VecDBL va, vb;
  f3.intersection (f4, &nbInt, &va, &vb);
  if (nbInt == 2)
  { // l'instance fait presque un tour, les deux bouts se rejoignent
    // les fronti�res f3 et f4 ne doivent pas �tres test�es en totalit�
    Arc f3a (deb_, epsilon, f3.deb_, va);
    f3a.intersection (a, &nbInt, &v1, &v2);
    if (nbInt)
      return 0;

    Arc f3b (deb_, epsilon, vb, f3.fin_);
    f3b.intersection (a, &nbInt, &v1, &v2);
    if (nbInt)
      return 0;

    Arc f4a (fin_, epsilon, f4.deb_, vb);
    f4a.intersection (a, &nbInt, &v1, &v2);
    if (nbInt)
      return 0;

    Arc f4b (fin_, epsilon, va, f4.fin_);
    f4b.intersection (a, &nbInt, &v1, &v2);
    if (nbInt)
      return 0;

  }
  else
  { // les fronti�res f3 et f4 ne se perturbent pas mutuellement
    f3.intersection (a, &nbInt, &v1, &v2);
    if (nbInt)
      return 0;
    f4.intersection (a, &nbInt, &v1, &v2);
    if (nbInt)
      return 0;
  }

  // l'arc a ne s'est jamais �loign� de l'instance : il est recouvert
  return 1;

}

bool Arc::balaye (const VecDBL& point,
                  const VecDBL& axe, double balayage) const
  throw (CantorErreurs)
{
  double mu = point.angleAvecVecteur (axe);

  int nbInt;
  VecDBL p1, p2;
  intersection (axe, cos (mu), &nbInt, &p1, &p2);

  if (nbInt > 0)
  {
    // le point p1 d�crit cette trajectoire pendant le balayage
    Arc trajetP1 (axe, mu, p1, balayage);
    if (trajetP1.distance (point) < ArcEpsilon)
      return true;
  }

  if (nbInt > 1)
  {
    // le point p2 d�crit cette trajectoire pendant le balayage
    Arc trajetP1 (axe, mu, p2, balayage);
    if (trajetP1.distance (point) < ArcEpsilon)
      return true;
  }

  return false;

}

Arc Arc::operator - () const
{
  if (sin_ < ArcEpsilon)
  { // c'est un arc d�g�n�r�
    return Arc (-axe_, M_PI - angle_, axe_.orthogonal (), 0.0);
  }
  else
    return Arc (-axe_, M_PI - angle_, fin_, balayage_);
}

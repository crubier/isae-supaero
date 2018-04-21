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
//>       Resolution2Iterateur.cpp
//
//$Resume
//       fichier d'implantation de la classe Resolution2Iterateur
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       static CodeConvergence2 ConvergenceXOuY()
//>       static double VariationEstimee()         
//>       static CodeConvergence2 TousPositifs()   
//>       static CodeConvergence2 TousNegatifs()   
//>       class Resolution2Iterateur               
//>         Resolution2Iterateur()                 
//>         reinitialise()                         
//>         zeroSuivant()                          
//
//$Historique
//       $Log: Resolution2Iterateur.cpp,v $
//       Revision 1.23  2003/02/04 09:29:58  cantor
//       DM-ID 17 Mise � jour du nom du fichier dans le bandeau suite � la modification des extensions.
//
//       Revision 1.22  2001/06/05 15:43:01  cantor
//       suppression d'un argument inutilis�
//
//       Revision 1.21  2000/08/09 14:36:42  cantor
//       R�union de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.20.2.1  2000/03/30 15:36:06  cantor
//       ajout du copyright CNES
//
//       Revision 1.20  1999/08/05 09:55:08  cantor
//       modification r�sultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 1.19.2.1  1999/04/26 10:38:18  cantor
//       �limination d'�valuations inutiles dans les convergences d'extremums
//
//       Revision 1.19  1998/10/05 13:31:12  cantor
//       utilisation de la constante cantorEpsilon de cantor/Util.h
//
//       Revision 1.18  1998/10/05 12:40:58  cantor
//       remplacement de la constante DBL_EPSILON par 1.0e-15
//       (pour �viter les probl�mes de non-portabilit�)
//
//       Revision 1.17  1998/07/29 11:37:39  cantor
//       �limination de float.h
//
//       Revision 1.16  1998/06/24 10:11:18  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.15  1998/04/26 15:24:07  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.14  1998/01/22 10:37:32  luc
//       mise en coh�rence de listes d'initialisation de constructeurs
//       et de l'ordre des attributs dans la classe
//
//       Revision 1.13  1997/09/10 08:52:48  luc
//       reconnaissance correcte des z�ros en fin d'intervalle
//
//       Revision 1.12  1997/07/06 10:39:21  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 1.11  1997/03/26 06:54:35  luc
//       changement des conventions de nommage
//       
//       Revision 1.10  1997/03/24 09:32:44  luc
//       passage de SCCS � RCS
//       
//       Revision 1.9  1996/07/16 10:51:05  luc
//       �limination de la d�pendance aux tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en cantor_erreurs.h
//       
//       Revision 1.8  1995/06/26 16:31:31  mercator
//       encapsulation de la verification d'inversion de pas
//       dans des directives de compilation conditionnelles
//       (la verification confond discontinuite et inversions: a utiliser avec precautions)
//       
//       Revision 1.7  1995/01/30 07:58:21  mercator
//       correction d'un test de convergence (seul le point inf etait teste)
//       
//       Revision 1.6  1995/01/26 16:20:36  mercator
//       correction d'un probleme lorsque l'un des points de dichotomie tombe
//       exactement sur un des zeros de la fonction (il n'etait pas detecte)
//       
//       Revision 1.5  1994/12/12 15:14:43  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.4  1994/11/26 15:17:30  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.3  1994/11/09 16:03:52  mercator
//       remplacement de la fonction "lance" par "erreur"
//       
//       Revision 1.2  1994/08/03 05:53:57  mercator
//       correction d'une erreur empechant la detection des zeros
//       pres de la fin de l'intervalle de recherche
//       modification du choix du point de convergence des extremums
//       
//       Revision 1.1  1994/07/27 14:53:34  luc
//       Initial revision
//
//$Version
//       $Id: Resolution2Iterateur.cpp,v 1.23 2003/02/04 09:29:58 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Util.h"
#include "cantor/CantorErreurs.h"
#include "cantor/Resolution2Iterateur.h"

static CodeConvergence2 ConvergenceXOuY (const Variation2& inf,
                                         const Variation2& sup,
                                         void* donnee)
{ // indicateur de convergence vers un z�ro

  // r�cup�ration du pointeur sur l'instance de Resolution2Iterateur
  Resolution2Iterateur* iter = (Resolution2Iterateur*) donnee;

  double dx    = fabs (sup.x () - inf.x ());
  double y_inf = fabs (inf.y ().f0 ());
  double y_sup = fabs (sup.y ().f0 ());

  if ((dx >= iter->convergenceX ())
      &&
      (y_inf >= iter->convergenceY ()) && (y_sup >= iter->convergenceY ()))
    return CONV2_AUCUNE;
  else
    return (y_inf <= y_sup) ? CONV2_INF : CONV2_SUP;

}

static double VariationEstimee (double ta, const ValeurDerivee2& fa,
                                double tb, const ValeurDerivee2& fb)
{ // estimation de la variation de la fonction sur l'intervalle

  if (((fa.f0 () <= 0.0) && (fb.f0 () >= 0.0))
      ||
      ((fa.f0 () >= 0.0) && (fb.f0 () <= 0.0)))
  { // la fonction change de signe, la variation relative est infinie
    return 1.0e10;
  }

  // calcul de l'intersection des mod�les lin�aires en a et b
  double y_inters = (fb.f1 () * (fa.f0 () - ta * fa.f1 ())
                   - fa.f1 () * (fb.f0 () - tb * fb.f1 ())
                    ) / (fb.f1 () - fa.f1 ());

  // estimation de l'�cart maximal
  double ecart     = max (fabs (y_inters - fa.f0 ()),
                          fabs (y_inters - fb.f0 ()));
  double reference = min (fabs (fa.f0 ()), fabs (fb.f0 ()));

  // variation relative de la valeur de la fonction (estimation)
  return ecart / max (reference, cantorEpsilon);

}

static CodeConvergence2 TousPositifs (const Variation2& inf,
                                      const Variation2& sup,
                                      void*)
{ // indicateur de convergence vers un maximum local
  // on s'arr�te soit quand tout l'intervalle est positif
  // soit quand la variation relative devient trop faible
  if (((inf.y ().f0 () <= 0.0) || (sup.y ().f0 () <= 0.0))
      &&
      (VariationEstimee (inf.x (), inf.y (), sup.x (), sup.y ()) >= 1.0e-9))
    return CONV2_AUCUNE;
  else
    return CONV2_SUP; // le sup est plus proche du tron�on suivant

}

static CodeConvergence2 TousNegatifs (const Variation2& inf,
                                      const Variation2& sup,
                                      void*)
{ // indicateur de convergence vers un minimum local
  // on s'arr�te soit quand tout l'intervalle est n�gatif
  // soit quand la variation relative devient trop faible
  if (((inf.y ().f0 () >= 0.0) || (sup.y ().f0 () >= 0.0))
      &&
      (VariationEstimee (inf.x (), inf.y (), sup.x (), sup.y ()) >= 1.0e-9))
    return CONV2_AUCUNE;
  else
    return CONV2_SUP; // le sup est plus proche du tron�on suivant

}

Resolution2Iterateur::Resolution2Iterateur (TypeFoncVD2 f, void* arg,
                                            double a, double b,
                                            double pas,
                                            double convergenceX,
                                            double convergenceY)
  : convergenceX_ (convergenceX), convergenceY_ (convergenceY),
    pas_ (pas), f_ (f), arg_ (arg)
{ if (a <= b)
  { tMin_ = a;
    tMax_ = b;
  }
  else
  { tMin_ = b;
    tMax_ = a;
  }

  reinitialise ();

}

Resolution2Iterateur::Resolution2Iterateur (TypeFoncVD2 f, void* arg,
                                            double a, double b,
                                            int n,
                                            double convergenceX,
                                            double convergenceY)
  : convergenceX_ (convergenceX), convergenceY_ (convergenceY),
    f_ (f), arg_ (arg)
{ if (a <= b)
  { tMin_ = a;
    tMax_ = b;
    pas_  = (b - a) / n;
  }
  else
  { tMin_ = b;
    tMax_ = a;
    pas_  = (a - b) / n;
  }

  reinitialise ();

}

void Resolution2Iterateur::reinitialise ()
{ precedente_ = Variation2 (tMin_, evalueFonction (tMin_));
  if (precedente_.croissante ())
    min_ = precedente_;
  else
    max_ = precedente_;

}

double Resolution2Iterateur::zeroSuivant ()
{ // it�ration sur les z�ros de la fonction
  int    dernier = 0;
  double t;

  // v�rification de d�passement de l'intervalle sp�cifi� � la construction
  if (precedente_.x () > tMax_)
    return precedente_.x ();

  while (1)
  { // boucle de parcours de l'intervalle

    if (precedente_.x () + pas_ > tMax_)
    { // r�duction du pas a l'approche de la fin de l'intervalle
      pas_ = tMax_ - precedente_.x ();

      // il ne faut pas que le pas devienne nul !...
      const double eps = 2.0 * cantorEpsilon
                             * max (1.0, fabs (precedente_.x ()));
      if (pas_ < eps)
        pas_ = eps;

      dernier = 1;

    }

    // progression dans l'intervalle
    t = precedente_.x () + pas_;
    if (t > tMax_)
    { // on a d�pass� la fin de l'intervalle, on se positionne loin par s�curit�
      precedente_ = Variation2 (tMin_ + 1.0e6 * (tMax_ - tMin_),
                                ValeurDerivee2 (0.0, 0.0));
      return precedente_.x ();
    }

    // calcul de la fonction et de ses d�riv�es au point courant
    Variation2 courante (t, evalueFonction (t));

    if (courante.sens () == precedente_.sens ())
    { // a priori, on reste dans le domaine de monotonie

      if (precedente_.croissante ())
      { // la fonction cro�t normalement

        if (courante.y ().f0 () <= 0.0)
        { // on se rapproche de l'axe des abscisses par dessous

          if (dernier && (courante.y ().f0 () >= -convergenceY_))
          { // le point courant peut �tre consid�r� comme un z�ro
            precedente_ = courante;
            min_        = courante;

            return courante.x ();

          }

          // on peut rapprocher le min sans perdre de z�ro
          min_ = courante;

        }
        else if (min_.y ().f0 () <= 0.0)
        { // on vient de franchir un z�ro
          double t0 = NewtonSecante (f_, arg_, ConvergenceXOuY, (void *) this,
                                     min_, courante
                                    ).x ();

          // pr�paration de la recherche suivante
          precedente_ = courante;
          min_        = courante;

          return t0;

        }
      }
      else
      { // la fonction d�cro�t normalement
        if (courante.y ().f0 () >= 0.0)
        { // on se rapproche de l'axe des abscisses par dessus

          if (dernier && (courante.y ().f0 () <= convergenceY_))
          { // le point courant peut �tre consid�r� comme un z�ro
            precedente_ = courante;
            min_        = courante;

            return courante.x ();

          }

          // on peut rapprocher le max sans perdre de z�ro
          max_ = courante;
        }
        else if (max_.y ().f0 () >= 0.0)
        { // on vient de franchir un z�ro
          double t0 = NewtonSecante (f_, arg_, ConvergenceXOuY, (void *) this,
                                     max_, courante
                                    ).x ();

          // pr�paration de la recherche suivante
          precedente_ = courante;
          max_        = courante;

          return t0;

        }
      }
    }
    else
    { // il y a un extremum dans [precedente_.x (); courante.x ()]
      int reinitialiser_min = 0;
      int reinitialiser_max = 0;

      if (precedente_.croissante ())
      { // on approche d'un maximum local

        if ((precedente_.y ().f0 () <= 0.0) || (courante.y ().f0 () <= 0.0))
        { // on ne peut pas garantir que tout l'intervalle soit de signe constant
          max_     = ExtremumNewSec (f_, arg_, TousPositifs, (void *) 0,
                                     precedente_, courante);
          max_.simuleDecroissante ();  // le tron�on suivant descendra
          courante = max_;             // le tron�on suivant partira du max
        }
        else
        { // on sait d'embl�e que tout l'intervalle est positif
          max_              = precedente_;
          reinitialiser_max = 1; // d�marrage d�croissant du tron�on suivant
        }
      }
      else
      { // on approche d'un minimum local

        if ((precedente_.y ().f0 () >= 0.0) || (courante.y ().f0 () >= 0.0))
        { // on ne peut pas garantir que tout l'intervalle soit de signe constant
          min_     = ExtremumNewSec (f_, arg_, TousNegatifs, (void *) 0, 
                                     precedente_, courante);
          min_.simuleCroissante ();    // le tron�on suivant montera
          courante = min_;             // le tron�on suivant partira du min
        }
        else
        { // on sait d'embl�e que tout l'intervalle est n�gatif
          min_              = precedente_;
          reinitialiser_min = 1; // d�marrage croissant du tron�on suivant
        }
      }

      if ((min_.y ().f0 () <= 0.0) && (max_.y ().f0 () >= 0.0))
      { // recherche d'un z�ro dans l'intervalle monotone identifi�
        double t0 = NewtonSecante (f_, arg_, ConvergenceXOuY, (void *) this,
                                   min_, max_
                                  ).x ();

        // pr�paration de la recherche sur le tron�on suivant
        precedente_ = courante;
        if (reinitialiser_min)
          min_ = courante;
        else if (reinitialiser_max)
          max_ = courante;

        // retour du z�ro identifi�
        return t0;

      }

      // pr�paration de la recherche sur le tron�on suivant
      if (reinitialiser_min)
        min_ = courante;
      else if (reinitialiser_max)
        max_ = courante;

    }

    // passage au point suivant
    precedente_ = courante;

  }
}

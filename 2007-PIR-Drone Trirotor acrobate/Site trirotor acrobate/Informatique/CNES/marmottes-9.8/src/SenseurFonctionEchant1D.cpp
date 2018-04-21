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
//>       SenseurFonctionEchant1D.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurFonctionEchant1D
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       class SenseurFonctionEchant1D 
//>         SenseurFonctionEchant1D()   
//>         fonction()       
//
//$Historique
//       $Log: SenseurFonctionEchant1D.cpp,v $
//       Revision 1.5  2003/02/27 16:41:36  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.4  2003/02/04 16:40:09  marmottes
//       DM-ID 17 Mise � jour de l'extension du fichier dans le bandeau
//
//       Revision 1.3  2001/07/17 15:38:23  luc
//       ajout du vecteur observ� pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.2  2001/03/26 11:17:42  luc
//       mise � jour r�sultant de la mod�lisation des inhibitions
//       dans la classe SenseurOptique
//
//       Revision 1.1  2000/11/16 18:22:01  luc
//       version initiale
//
//$Version
//       $Id: SenseurFonctionEchant1D.cpp,v 1.5 2003/02/27 16:41:36 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <utility>

#include "cantor/MathPi.h"

#include "marmottes/SenseurFonctionEchant1D.h"

SenseurFonctionEchant1D::SenseurFonctionEchant1D (const string& nom,
                                                  const RotDBL& repere,
                                                  const VecDBL& axeCalage,
                                                  double precision,
                                                  codeCible code,
                                                  const StationCible *ptrStation,
                                                  const VecDBL& observe,
                                                  Parcelle* ptrChampDeVue,
                                                  Parcelle *ptrChampInhibitionSoleil,
                                                  Parcelle *ptrChampInhibitionLune,
                                                  Parcelle *ptrChampInhibitionCentral,
                                                  double margeEclipseSoleil,
                                                  double margeEclipseLune,
                                                  double seuilPhaseLune,
                                                  const VecDBL& axe,
                                                  const VecDBL& origine,
                                                  int nbEchantillons,
                                                  double *angles,
                                                  double *valeurs)
  throw (CantorErreurs, MarmottesErreurs)
  : SenseurFonction (nom, repere, axeCalage, precision,
                     code, ptrStation, observe, ptrChampDeVue,
                     ptrChampInhibitionSoleil, ptrChampInhibitionLune,
                     ptrChampInhibitionCentral,
                     margeEclipseSoleil, margeEclipseLune, seuilPhaseLune,
                     axe, origine)
{

  if (nbEchantillons < 1)
    throw MarmottesErreurs (MarmottesErreurs::echantillon_vide, nom.c_str ());

  for (int i = 0; i < nbEchantillons; ++i)
  {
    if ((angles [i] < 0) || (angles [i] > M_PI))
      throw MarmottesErreurs (MarmottesErreurs::echantillon_rejete,
                              degres (angles [i]), valeurs [i], nom.c_str ());

    echantillon_.insert ( map<double, double>::value_type (angles [i], valeurs [i]));

  }

}

SenseurFonctionEchant1D& SenseurFonctionEchant1D::operator = (const SenseurFonctionEchant1D& s)
{ if (&s != this)    // protection contre x = x
  {
    SenseurFonction::operator = (s);
    echantillon_ = s.echantillon_;
  }

  return *this;

}

double SenseurFonctionEchant1D::fonction (double azimut,
                                          double depointage) const
  throw (MarmottesErreurs)
{

  // extraction des angles et valeurs d'�chantillonnage
  map<double, double>::const_iterator i = echantillon_.upper_bound (depointage);
  if (i == echantillon_.end ())
  {
    // le d�pointage courant est au del� de tous les points d'�chantillonnage
    return (--i)->second;
  }

  if (i == echantillon_.begin ())
  {
    // le d�pointage courant est en de�� de tous les points d'�chantillonnage
    return i->second;
  }

  // le d�pointage est entre le point courant et le pr�c�dent
  double theta2 = i->first;
  double val2   = i->second;

  --i;

  double theta1 = i->first;
  double val1   = i->second;

  // interpolation lin�aire sur l'�chantillon
  return ((depointage - theta1) * val2 + (theta2 - depointage) * val1)
       / (theta2 - theta1);

}

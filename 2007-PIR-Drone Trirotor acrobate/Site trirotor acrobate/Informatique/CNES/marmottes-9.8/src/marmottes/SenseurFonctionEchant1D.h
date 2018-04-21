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
//>       SenseurFonctionEchant1D.h
//
//$Resume
//       fichier d'en-t�te de la classe SenseurFonctionEchant1D
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class SenseurFonctionEchant1D
//
//$Historique
//       $Log: SenseurFonctionEchant1D.h,v $
//       Revision 1.5  2003/02/27 16:13:45  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.4  2002/12/11 17:17:50  marmottes
//       DM-ID 12 Ajout d'un constructeur par d�faut (prot�g�) pour pr�venir celui construit par le compilateur.
//
//       Revision 1.3  2001/07/17 15:32:50  luc
//       ajout du vecteur observ� pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.2  2001/03/26 11:13:07  luc
//        mise � jour r�sultant de la mod�lisation des inhibitions dans la
//       classe SenseurOptique
//
//       Revision 1.1  2000/11/16 18:20:18  luc
//       version initiale
//
//$Version
//       $Id: SenseurFonctionEchant1D.h,v 1.5 2003/02/27 16:13:45 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurFonctionEchant1D_h
#define __marmottes_SenseurFonctionEchant1D_h

#include <map>

#include "marmottes/SenseurFonction.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurFonctionEchant1D
//$Resume
//       mod�lisation d'un pseudo-senseur plaquant un �chantillonnage radial
//       sur la sph�re unit�
//
//$Description
//       mod�lisation d'un senseur plaquant un �chantillonnage radial
//       sur la sph�re unit�. L'utilisation principale d'un tel senseur
//       est de repr�senter des gains d'antenne.
//
//$Usage
//>     construction : 
//          � partir du nom, du rep�re satellite, de l'axe de calage,
//          de la pr�cision et des points d'�chantillonnage
//          par copie
//>     utilisation  : 
//>       SenseurFonctionEchant1D& operator = () 
//          affectation
//>       virtual Senseur* copie              () 
//          op�rateur de copie virtuel
//>       virtual double fonction          () 
//          �value la fonction �chantillonn�e
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurFonctionEchant1D : public SenseurFonction
{
public:

  // constructeurs
  SenseurFonctionEchant1D (const string& nom, const RotDBL& repere,
                           const VecDBL& axeCalage, double precision,
                           codeCible code, const StationCible *ptrStation,
                           const VecDBL& observe,
                           Parcelle* ptrChampDeVue,
                           Parcelle *ptrChampInhibitionSoleil,
                           Parcelle *ptrChampInhibitionLune,
                           Parcelle *ptrChampInhibitionCentral,
                           double margeEclipseSoleil, double margeEclipseLune,
                           double seuilPhaseLune,
                           const VecDBL& axe, const VecDBL& origine,
                           int nbEchantillons, double *angles, double *valeurs)
    throw (CantorErreurs, MarmottesErreurs);

  SenseurFonctionEchant1D (const SenseurFonctionEchant1D& s)
    : SenseurFonction (s), echantillon_ (s.echantillon_)
  {}

  SenseurFonctionEchant1D& operator = (const SenseurFonctionEchant1D& s);

  virtual Senseur* copie () const
  { return new SenseurFonctionEchant1D (*this); }

  // destructeur
  virtual ~SenseurFonctionEchant1D () {}

  // fonction sinus cardinal plaqu�e sur la sph�re
  virtual double fonction (double azimut, double depointage) const
    throw (MarmottesErreurs);

protected :

  // constructeur par defaut : ne doit JAMAIS �tre utilis�
  SenseurFonctionEchant1D () {}

private:

  map<double, double> echantillon_;

};

#endif

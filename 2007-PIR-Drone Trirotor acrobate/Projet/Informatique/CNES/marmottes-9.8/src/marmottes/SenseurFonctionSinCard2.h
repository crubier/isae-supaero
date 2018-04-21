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
//>       SenseurFonctionSinCard2.h
//
//$Resume
//       fichier d'en-t�te de la classe SenseurFonctionSinCard2
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class SenseurFonctionSinCard2
//
//$Historique
//       $Log: SenseurFonctionSinCard2.h,v $
//       Revision 1.7  2003/02/27 16:13:21  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.6  2002/12/11 17:18:58  marmottes
//       DM-ID 12 Ajout d'un constructeur par d�faut (prot�g�) pour pr�venir celui construit par le compilateur.
//
//       Revision 1.5  2002/12/02 17:06:35  marmottes
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.4  2001/07/17 15:33:02  luc
//       ajout du vecteur observ� pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.3  2001/03/26 11:13:32  luc
//        mise � jour r�sultant de la mod�lisation des inhibitions dans la
//       classe SenseurOptique
//
//       Revision 1.2  2000/09/13 10:59:00  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.1  2000/06/07 14:06:03  luc
//       version initiale
//
//$Version
//       $Id: SenseurFonctionSinCard2.h,v 1.7 2003/02/27 16:13:21 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurFonctionSinCard2_h
#define __marmottes_SenseurFonctionSinCard2_h

#include "marmottes/SenseurFonction.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurFonctionSinCard2
//
//$Resume
//       mod�lisation d'un pseudo-senseur plaquant la fonction sin(x)/x
//       sur la sph�re unit�
//
//$Description
//       mod�lisation d'un senseur plaquant la fonction sin(x)/x
//       sur la sph�re unit�. L'utilisation principale d'un tel senseur
//       est de repr�senter des gains d'antenne.
//
//$Usage
//>     construction : 
//          � partir du nom, du rep�re satellite, de l'axe de calage,
//          de la pr�cision, du maximum et de l'angle pour un gain de -3dB
//          par copie
//>     utilisation  : 
//>       SenseurFonctionSinCard2& operator =        () 
//          affectation
//>       virtual double fonction          () 
//          �value la fonction sinus cardinal
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurFonctionSinCard2 : public SenseurFonction
{

public :

  // constructeurs
  SenseurFonctionSinCard2 (const string& nom, const RotDBL& repere,
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
                           double maximum, double angle3dB)
    throw (CantorErreurs);

  SenseurFonctionSinCard2 (const SenseurFonctionSinCard2& s)
    : SenseurFonction (s),
      maximum_ (s.maximum_), angle3dB_ (s.angle3dB_)
  {}

  SenseurFonctionSinCard2& operator = (const SenseurFonctionSinCard2& s);

  virtual Senseur* copie () const { return new SenseurFonctionSinCard2 (*this); }

  // destructeur
  virtual ~SenseurFonctionSinCard2 () {}

  // fonction sinus cardinal plaqu�e sur la sph�re
  virtual double fonction (double azimut, double depointage) const
    throw (MarmottesErreurs);

protected :

  // constructeur par defaut : ne doit JAMAIS �tre utilis�
  SenseurFonctionSinCard2 () {}

private :

  double maximum_;
  double angle3dB_;

};

#endif

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
//>       SenseurLimbe.h
//
//$Resume
//       fichier d'en-t�te de la classe SenseurLimbe
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class SenseurLimbe
//
//$Historique
//       $Log: SenseurLimbe.h,v $
//       Revision 1.6  2003/02/27 16:12:51  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.5  2002/12/11 17:18:58  marmottes
//       DM-ID 12 Ajout d'un constructeur par d�faut (prot�g�) pour pr�venir celui construit par le compilateur.
//
//       Revision 1.4  2002/01/17 09:39:05  marmottes
//       correction de sp�cifications throw (FA 0003)
//
//       Revision 1.3  2001/07/17 15:22:17  luc
//       �limination des arguments code et station inutilis�s
//       �limination de la m�thode filtreSecteurs
//       (implant�e enti�rement dans la classe de base)
//
//       Revision 1.2  2001/04/04 12:07:57  luc
//       renommage de SenseurHorizon en SenseurLimbe
//       �limination de la sp�cialisation de la m�thode controlable
//       ajout d'une sp�cialisation de la m�thode ecartFrontiere
//
//       Revision 1.1  2001/03/26 11:10:48  luc
//       version initiale
//
//$Version
//       $Id: SenseurLimbe.h,v 1.6 2003/02/27 16:12:51 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2001 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurLimbe_h
#define __marmottes_SenseurLimbe_h

#include "marmottes/SenseurDiedre.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurLimbe
//
//$Resume
//       mod�lisation d'un cas particulier des senseurs di�dres, les senseurs limbe.
//
//$Description
//       mod�lisation d'un cas particulier des senseurs di�dres,
//       les senseurs limbe.
//
//$Usage
//>     construction : 
//          � partir du nom, du rep�re satellite, de l'axe de calage
//          et de la pr�cision, par copie
//          La classe �tant abstraite, les constructeurs sont appel�s
//          par les constructeurs des classes d�riv�es.
//>     utilisation  : 
//>       SenseurLimbe& operator =              () 
//          affectation
//>       virtual int controlable               () 
//          indique si le senseur serait capable de contr�ler
//          l'attitude de l'�tat donn�
//>       virtual Senseur* copie                () 
//          retourne une copie du senseur allou�e en m�moire
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurLimbe : public SenseurDiedre
{

  public :

  // constructeurs
  SenseurLimbe (const string& nom,
                const RotDBL& repere, const VecDBL& axeCalage,
                double precision,
                Parcelle *ptrChampDeVue,
                Parcelle *ptrChampInhibitionSoleil,
                Parcelle *ptrChampInhibitionLune,
                Parcelle *ptrChampInhibitionCentral,
                double margeEclipseSoleil, double margeEclipseLune,
                double seuilPhaseLune,
                const VecDBL& referenceZero, const VecDBL& axeSensible);

  SenseurLimbe (const SenseurLimbe& s);

  SenseurLimbe& operator = (const SenseurLimbe& s);

  // destructeur
  virtual ~SenseurLimbe () {}

  virtual Senseur* copie () const { return new SenseurLimbe (*this); }

  protected :

  virtual void ecartFrontiere (const Etat& etat,
                               double *ptrEcartFrontiere,
                               bool *ptrAmplitudeSignificative) const
    throw (CantorErreurs);

  // constructeur par defaut : ne doit JAMAIS �tre utilis�
  SenseurLimbe () {}

};

#endif

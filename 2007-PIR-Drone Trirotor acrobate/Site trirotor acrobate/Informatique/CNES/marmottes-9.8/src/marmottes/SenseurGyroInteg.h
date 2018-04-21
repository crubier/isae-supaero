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
//>       SenseurGyroInteg.h
//
//$Resume
//       fichier d'en-t�te de la classe SenseurGyroInteg
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class SenseurGyroInteg
//
//$Historique
//       $Log: SenseurGyroInteg.h,v $
//       Revision 1.10  2003/10/08 09:40:09  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 1.9  2002/12/11 17:18:58  marmottes
//       DM-ID 12 Ajout d'un constructeur par d�faut (prot�g�) pour pr�venir celui construit par le compilateur.
//
//       Revision 1.8  2002/01/17 09:39:05  marmottes
//       correction de sp�cifications throw (FA 0003)
//
//       Revision 1.7  2000/10/02 12:22:17  luc
//       remplacement d'attributs entiers en bool�ens
//
//       Revision 1.6  2000/09/13 10:41:08  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.5  2000/03/30 17:01:24  luc
//       ajout du copyright CNES
//
//       Revision 1.4  1999/11/02 07:19:23  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.3  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines m�thodes (correction des oublis
//       apr�s le passage aux exceptions)
//
//       Revision 1.2  1999/08/06 13:32:20  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 1.1  1998/07/15 12:33:48  luc
//       support pour les gyros integrateurs
//
//$Version
//       $Id: SenseurGyroInteg.h,v 1.10 2003/10/08 09:40:09 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurGyroInteg_h
#define __marmottes_SenseurGyroInteg_h

#include "cantor/DeclDBLVD1.h"

#include "marmottes/Etat.h"
#include "marmottes/SenseurCinematique.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurGyroInteg
//
//$Resume
//       mod�lisation d'un gyroscope int�grateur
//
//$Description
//       mod�lisation d'un senseur cin�matique
//
//$Usage
//>     construction : 
//          � partir du nom, du rep�re satellite, de l'axe de calage
//          et de la pr�cision, par copie
//          La classe �tant abstraite, les constructeurs sont appel�s
//          par les constructeurs des classes d�riv�es.
//>     utilisation  : 
//>       SenseurGyroInteg& operator =     () 
//          affectation
//>       virtual int modeliseConsigne     () 
//          permet de stocker un mod�le de la consigne que doit
//          respecter un senseur contr�lant l'attitude du satellite
//          dans l'�tat courant ATTENTION: dans cet �tat, l'attitude
//          ne doit pas �tre utilis�e, elle ne sera initialis�e
//          correctement qu'� la fin de la r�solution ayant utilis� ce
//          mod�le!
//>       virtual double mesure            () 
//          retourne la mesure que donnerait le senseur dans l'�tat donn�
//>       virtual ValeurDerivee1 foncEcart () 
//          calcule la fonction d'�cart du senseur par rapport � sa
//          consigne � la date donn�e et dans l'attitude donn�e en
//          tenant compte de l'�tat pr�c�dent.
//>       virtual int initialiseGyro       () 
//          initialise l'angle d'un gyro int�grateur
//>       virtual int prendEtatEnCompte    () 
//          prise en compte d'un �tat de r�solution
//          (pour les gyros int�grateurs)
//>       virtual Senseur* copie           () 
//          retourne une copie du senseur allou�e en m�moire
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurGyroInteg : public SenseurCinematique
{
public :

  // constructeurs
  SenseurGyroInteg (const string& nom, const RotDBL& repere,
                    const VecDBL& axeCalage, double precision,
                    const VecDBL& axeSensible)
    : SenseurCinematique (nom, repere, axeCalage, precision, axeSensible),
      t0_ (0.0), alpha0_ (0.0), initialise_ (false)
  {}
  SenseurGyroInteg (const SenseurGyroInteg& s)
    : SenseurCinematique (s),
      t0_ (s.t0_), alpha0_ (s.alpha0_), initialise_ (s.initialise_)
  {}

  SenseurGyroInteg& operator = (const SenseurGyroInteg& s);

  // destructeur
  virtual ~SenseurGyroInteg () {}

  virtual Senseur* copie () const { return new SenseurGyroInteg (*this); }

  // fonctions de resolution de l'attitude
  virtual void           modeliseConsigne (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);

  virtual double         mesure           (const Etat& etat)
    throw (MarmottesErreurs);

  virtual ValeurDerivee1 foncEcart        (const Etat& etatPrecedent,
                                           const Etat& etatResolution,
                                           const RotVD1& attitude,
                                           const VecVD1& spin);

  // initialisation d'un gyro int�grateur
  virtual void initialiseGyro (double date, double angle)
    throw (MarmottesErreurs);

  // prise en compte des �tats apr�s r�solution d'attitude
  virtual void prendEtatEnCompte (const Etat& etat);

protected :

  // constructeur par defaut : ne doit JAMAIS �tre utilis�
  SenseurGyroInteg () {}

private :

  double t0_;
  double alpha0_;
  bool   initialise_;

};

#endif

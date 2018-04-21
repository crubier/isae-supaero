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
//>       SenseurGyroInteg.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurGyroInteg
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       class SenseurGyroInteg
//>         operator =()        
//>         modeliseConsigne()  
//>         mesure()            
//>         foncEcart()         
//>         initialiseGyro()    
//>         prendEtatEnCompte() 
//
//$Historique
//       $Log: SenseurGyroInteg.cpp,v $
//       Revision 1.9  2003/10/08 09:39:41  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 1.8  2003/02/04 16:41:24  marmottes
//       DM-ID 17 Mise � jour de l'extension du fichier dans le bandeau
//
//       Revision 1.7  2002/01/17 09:22:08  marmottes
//       (modeliseConsigne): correction d'une erreur d'unit�s - ccorrection de sp�cifications throw
//
//       Revision 1.6  2000/10/02 13:15:32  luc
//       remplacement d'attributs entiers en bool�ens
//
//       Revision 1.5  2000/03/30 17:01:20  luc
//       ajout du copyright CNES
//
//       Revision 1.4  1999/08/20 07:37:28  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des m�thodes "throw"
//
//       Revision 1.3  1999/08/06 13:32:16  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 1.2  1999/04/26 11:38:42  luc
//       remplacement de abs par fabs
//
//       Revision 1.1  1998/07/15 12:50:01  luc
//       support pour les gyros integrateurs
//
//$Version
//       $Id: SenseurGyroInteg.cpp,v 1.9 2003/10/08 09:39:41 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurGyroInteg.h"

SenseurGyroInteg& SenseurGyroInteg::operator = (const SenseurGyroInteg& s)
{ if (&s != this)    // protection contre x = x
  { SenseurCinematique::operator = (s);
    t0_         = s.t0_;
    alpha0_     = s.alpha0_;
    initialise_ = s.initialise_;
  }

  return *this;

}


void SenseurGyroInteg::modeliseConsigne (const Etat& etat, double valeur)
  throw (CantorErreurs, MarmottesErreurs)
{ 
  // mod�lisation d'une consigne d'angle int�gr�
  if (! initialise_)
  { // le senseur s'auto-initialise � 0 lors de la premi�re utilisation
    t0_         = etat.date ();
    alpha0_     = 0.0;
    initialise_ = true;
  }

  if (fabs (etat.date () - t0_) < 1.0e-8)
  { // la date de r�f�rence est trop proche de la date de mod�lisation
    // on la d�cale en fonction du spin courant
    double omega = SenseurCinematique::mesure (etat);
    t0_     -= 2.0e-8;
    alpha0_ -= 2.0e-8 * omega;
  }

  // l'angle de r�f�rence est stock� en unit� de mesure, l'argument
  // valeur est quant � lui exprim� en unit� de consigne et
  // SenseurCinematique::modeliseConsigne attend �galement sa vitesse
  // angulaire en unit� de consigne, il faut donc ramener l'angle de
  // r�f�rence dans cette m�me unit� de consigne pour calculer la
  // vitesse angulaire � partir de l'angle int�gr�
  double alphaRad = conversionMesures   () ? radians (alpha0_) : alpha0_;
  double alpha    = conversionConsignes () ? degres (alphaRad) : alphaRad;

  double dt = 86400.0 * (etat.date () - t0_);
  SenseurCinematique::modeliseConsigne (etat, (valeur - alpha) / dt );

  // la valeur m�moris�e par la classe de base
  // doit l'�tre dans l'unit� de mesure
  double valeurRad = conversionConsignes () ? radians (valeur) : valeur;
  if (conversionMesures ())
    Senseur::modeliseConsigne (etat, degres (valeurRad));
  else
    Senseur::modeliseConsigne (etat, valeurRad);

}


double SenseurGyroInteg::mesure (const Etat& etat)
  throw (MarmottesErreurs)
{ 
  if (! initialise_)
  { // le senseur s'auto-initialise � 0 lors de la premi�re utilisation
    t0_         = etat.date ();
    alpha0_     = 0.0;
    initialise_ = true;
  }

  double dt    = 86400.0 * (etat.date () - t0_);
  double omega = SenseurCinematique::mesure (etat);

  // la conversion �ventuelle degr�s/radians est d�j� prise
  // en compte par alpha0_ et par SenseurCinematique::mesure
  return alpha0_ + dt * omega;

}


ValeurDerivee1 SenseurGyroInteg::foncEcart (const Etat& etatPrecedent,
                                            const Etat& etatResolution,
                                            const RotVD1& attitude,
                                            const VecVD1& spin)
{ return SenseurCinematique::foncEcart (etatPrecedent, etatResolution,
                                        attitude, spin)
       * (etatResolution.date () - t0_) * 86400.0;
}


void SenseurGyroInteg::initialiseGyro (double date, double angle)
  throw (MarmottesErreurs)
{ // initialisation d'un gyro int�grateur

  // l'angle de r�f�rence doit �tre donn� dans l'unit� de mesure,
  // il est �galement stock� dans cette unit�
  t0_         = date;
  alpha0_     = angle;
  initialise_ = true;

}


void SenseurGyroInteg::prendEtatEnCompte (const Etat& etat)
{ // prise en compte des �tats apr�s r�solution d'attitude
  if (! initialise_)
  { // le senseur s'auto-initialise � 0 lors de la premi�re utilisation
    t0_         = etat.date ();
    alpha0_     = 0.0;
    initialise_ = true;
  }
  else
  { // on propage la r�f�rence selon le dernier pas
    alpha0_ = mesure (etat);
    t0_     = etat.date ();
  }
}

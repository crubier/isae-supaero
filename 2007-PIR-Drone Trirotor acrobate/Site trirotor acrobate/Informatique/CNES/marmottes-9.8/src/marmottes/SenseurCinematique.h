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
//>       SenseurCinematique.h
//
//$Resume
//       fichier d'en-t�te de la classe SenseurCinematique
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class SenseurCinematique
//
//$Historique
//       $Log: SenseurCinematique.h,v $
//       Revision 2.20  2003/10/08 09:40:09  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 2.19  2002/12/11 17:13:26  marmottes
//       DM-ID 12 Ajout d'un constructeur par d�faut (prot�g�) pour pr�venir celui construit par le compilateur.
//
//       Revision 2.18  2002/12/02 17:04:43  marmottes
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 2.17  2002/02/27 14:09:09  marmottes
//       suppression de la description de la r�vision ins�r�e manuellement
//       et mise � jour du copyright CNES
//
//       Revision 2.16  2002/02/22 09:50:55  marmottes
//       Introduction des m�thodes SenseurCinematique::initialiseDerive et SenseurCinematique::derive (DM 0002)
//
//       Revision 2.15  2002/01/17 09:39:05  marmottes
//       correction de sp�cifications throw (FA 0003)
//
//       Revision 2.14  2001/06/06 07:46:51  luc
//       r�cup�ration des exceptions Cantor
//
//       Revision 2.13  2000/09/13 10:16:28  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 2.12  2000/03/30 17:01:23  luc
//       ajout du copyright CNES
//
//       Revision 2.11  1999/11/02 07:19:22  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 2.10  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines m�thodes (correction des oublis
//       apr�s le passage aux exceptions)
//
//       Revision 2.9  1999/08/06 13:32:19  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 2.8  1998/06/25 06:14:20  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 2.7  1998/04/26 18:25:31  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.6  1998/02/04 08:45:18  luc
//       mise en place d'un en-t�te de classe au format AMIGAU
//
//       Revision 2.5  1997/09/23 09:26:20  luc
//       ajout d'une gestion des unit�s de consigne et de mesure
//       interne au senseur
//
//       Revision 2.4  1997/08/20 09:51:10  luc
//       ajout d'un en-t�te de fichier
//       �limination de l'attribut omega_ (redondant avec la valeur de consigne de base)
//
//       Revision 2.3  1997/04/27 19:33:45  luc
//       inversion des codes de retour
//       changement des r�gles de nommage
//       passage de SCCS � RCS
//       
//       Revision 2.2  1996/09/11 17:44:52  luc
//       ajout du nom du senseur dans l'instance
//       
//       Revision 2.1  1996/07/31 17:22:16  luc
//       ajout d'une possibilit� de modifier le rep�re senseur � l'ex�cution
//       
//       Revision 1.4  1996/06/04 12:44:02  luc
//       correction de la non-prise en compte du rep�re senseur
//       
//       Revision 1.3  1995/01/30 09:43:29  mercator
//       ajout de l'initialisation de pointeurs d'erreur en sortie
//       ajout d'initialisations des cibles de senseurs geometriques
//       
//       Revision 1.2  1995/01/27 16:59:49  mercator
//       propagation du spin dans tous les calculs depuis la modelisation
//       jusqu'a la sauvegarde de la solution finale dans l'etat
//       
//       Revision 1.1  1994/12/23 11:00:14  luc
//       Initial revision
//
//$Version
//       $Id: SenseurCinematique.h,v 2.20 2003/10/08 09:40:09 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurCinematique_h
#define __marmottes_SenseurCinematique_h

#include "cantor/DeclDBLVD1.h"
#include "cantor/CantorErreurs.h"

#include "marmottes/Etat.h"
#include "marmottes/Senseur.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurCinematique
//
//$Resume
//       mod�lisation d'un senseur cin�matique
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
//>       SenseurCinematique& operator =   () 
//          affectation
//>       virtual void respecterMesures    () 
//          force le senseur � respecter les unit�s de mesures dans
//          ses sorties
//>       virtual void convertirMesures    () 
//          force le senseur � convertir les unit�s de mesures dans
//          ses sortie
//>       virtual void nouveauRepere       () 
//          tourne le senseur pour l'aligner sur le rep�re donn�
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
//>       virtual Senseur* copie           () 
//          retourne une copie du senseur allou�e en m�moire
//>       const VecDBL& sensible           () 
//          retourne l'axe sensible du senseur
//>       double omega                     () 
//          retourne la consigne courante du senseur
//>       double derive                    () 
//          retourne la derive courante du senseur
//>       virtual int methode              () 
//          retourne un identificateur qui permet de regrouper les
//          senseurs de m�me principe g�n�ral (g�om�trique ou
//          cin�matique).
//>       virtual int controlable          () 
//          indique si le senseur serait capable de contr�ler
//          l'attitude de l'�tat donn�
//>       virtual void initialiseDerive    ()
//          initialise la d�rive du senseur
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurCinematique : public Senseur
{ 

public :

  // constructeurs
  SenseurCinematique (const string& nom, const RotDBL& repere,
                      const VecDBL& axeCalage, double precision,
                      const VecDBL& axeSensible)
    throw (CantorErreurs)
    : Senseur (nom, repere, axeCalage, radians (precision)),
      sensible_ ((-repere) (axeSensible)), omega_ (0.0), derive_(0.0)
  {
    sensible_.normalise ();
    sensibleVD1_ = VecDBLVD1 (sensible_);
  }
  SenseurCinematique (const SenseurCinematique& s)
    : Senseur (s), sensible_ (s.sensible_), sensibleVD1_ (s.sensibleVD1_),
      omega_ (0.0), derive_(0.0)
  {}

  SenseurCinematique& operator = (const SenseurCinematique& s);

  // destructeur
  virtual ~SenseurCinematique () {}

  virtual void respecterMesures ();
  virtual void convertirMesures ();

  virtual Senseur* copie () const { return new SenseurCinematique (*this); }

  // r�orientation du senseur
  virtual void  nouveauRepere (const RotDBL& nouveau);

  // fonctions d'acces aux elements internes
  const VecDBL& sensible () const { return sensible_; }

  double        omega    () const { return omega_; }

  double        derive   () const { return derive_; }

  // fonctions de resolution de l'attitude
  virtual int            methode            () const
                                            { return integrationSpin; }

  virtual void           modeliseConsigne   (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);

  virtual double         mesure             (const Etat& etat)
    throw (MarmottesErreurs);

  virtual int            controlable        (const Etat& etat) 
    throw (CantorErreurs, MarmottesErreurs)
                                            { return 1; }

  virtual ValeurDerivee1 foncEcart          (const Etat& etatPrecedent,
                                             const Etat& etatResolution,
                                             const RotVD1& attitude,
                                             const VecVD1& spin);

  // fonction d'initialisation de la d�rive d'un senseur cin�matique
  virtual void           initialiseDerive   (double derive)
    throw (MarmottesErreurs);

protected :

  // constructeur par defaut : ne doit JAMAIS �tre utilis�
  SenseurCinematique () {}

private :

  VecDBL sensible_;
  VecVD1 sensibleVD1_;

  double omega_;
  double derive_;

};

#endif

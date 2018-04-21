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
//>       SenseurAlpha.h
//
//$Resume
//       fichier d'en-t�te de la classe SenseurAlpha
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class SenseurAlpha
//
//$Historique
//       $Log: SenseurAlpha.h,v $
//       Revision 1.16  2003/10/08 09:40:09  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 1.15  2002/12/11 17:11:50  marmottes
//       DM-ID 12 Ajout d'un constructeur par d�faut (prot�g�) pour pr�venir celui construit par le compilateur.
//
//       Revision 1.14  2002/12/02 17:03:58  marmottes
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.13  2002/01/17 09:38:03  marmottes
//       correction de sp�cifications throw (FA 0003)
//
//       Revision 1.12  2000/09/13 10:04:11  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.11  2000/03/30 17:01:23  luc
//       ajout du copyright CNES
//
//       Revision 1.10  1999/11/02 07:19:22  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.9  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines m�thodes (correction des oublis
//       apr�s le passage aux exceptions)
//
//       Revision 1.8  1999/08/06 13:32:18  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 1.7  1998/09/14 11:53:36  luc
//       �limination de caract�res de contr�le parasites
//       devant certains accents de l'en-t�te
//
//       Revision 1.6  1998/06/25 06:13:06  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.5  1998/04/26 18:25:27  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.4  1998/02/06 17:33:32  luc
//       ajout d'une sp�cialisation de foncEcart de sorte que
//       la valeur produite soit bien un �cart entre mesure et consigne
//       (dans le cas contraire, des probl�mes se posent pour des
//       pseudo-senseurs utilisant une cible tr�s proche de l'axe sensible)
//
//       Revision 1.3  1998/02/04 08:42:38  luc
//       mise en place d'un en-t�te de classe au format AMIGAU
//
//       Revision 1.2  1997/09/23 09:25:40  luc
//       ajout d'une gestion des unit�s de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/08/20 09:50:16  luc
//       Initial revision
//
//$Version
//       $Id: SenseurAlpha.h,v 1.16 2003/10/08 09:40:09 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurAlpha_h
#define __marmottes_SenseurAlpha_h

#include "marmottes/SenseurGeometrique.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurAlpha
//
//$Resume
//       mod�lisation d'un pseudo-senseur d'ascension droite
//
//$Description
//       mod�lisation d'un pseudo-senseur d'ascension droite
//
//$Usage
//>     construction : 
//          � partir du nom, du rep�re satellite, de l'axe de calage
//          et de la pr�cision, par copie
//          La classe �tant abstraite, les constructeurs sont appel�s
//          par les constructeurs des classes d�riv�es.
//>     utilisation  : 
//>       SenseurAlpha& operator =         () 
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
//>       virtual int controlable          () 
//          indique si le senseur serait capable de contr�ler
//          l'attitude de l'�tat donn�
//>       virtual Senseur* copie           () 
//          retourne une copie du senseur allou�e en m�moire
//>       virtual typeGeom typeGeometrique () 
//          retourne le type de senseur g�om�trique (pseudoSenseur)
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurAlpha : public SenseurGeometrique
{ 

public :

  // constructeurs
  SenseurAlpha (const string& nom,
                const RotDBL& repere, const VecDBL& axeCalage,
                double precision, const VecDBL& observe);
  SenseurAlpha (const SenseurAlpha& s)
    : SenseurGeometrique (s),
      observe_ (s.observe_), alphaConsigne_ (s.alphaConsigne_)
  {}

  SenseurAlpha& operator = (const SenseurAlpha& s);

  // destructeur
  virtual ~SenseurAlpha () {}

  virtual void respecterMesures ();
  virtual void convertirMesures ();

  virtual int      controlable     (const Etat& etat)
    throw (MarmottesErreurs)
                                   { return 1; }

  virtual Senseur* copie           () const
                                   { return new SenseurAlpha (*this); }

  virtual typeGeom typeGeometrique () const { return pseudoSenseur; }

  // r�orientation du senseur
  virtual void  nouveauRepere (const RotDBL& nouveau);

  // fonctions de r�solution de l'attitude
  virtual void    modeliseConsigne (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);
  virtual double  mesure           (const Etat& etat)
    throw (MarmottesErreurs);
  virtual ValeurDerivee1 foncEcart (const Etat& etatPrecedent,
                                    const Etat& etatResolution,
                                    const RotVD1& attitude,
                                    const VecVD1& spin
                                   );

protected :

  // constructeur par defaut : ne doit JAMAIS �tre utilis�
  SenseurAlpha () {}

private :

  VecDBL observe_;
  double alphaConsigne_;

  void    initialiseCible (double alpha);

};

#endif

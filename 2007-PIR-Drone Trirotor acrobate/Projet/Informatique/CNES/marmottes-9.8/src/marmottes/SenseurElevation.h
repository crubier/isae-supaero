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
//>       SenseurElevation.h
//
//$Resume
//       fichier d'en-t�te de la classe SenseurElevation
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class SenseurElevation
//
//$Historique
//       $Log: SenseurElevation.h,v $
//       Revision 1.16  2003/02/27 16:15:30  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.15  2002/12/11 17:16:17  marmottes
//       DM-ID 12 Ajout d'un constructeur par d�faut (prot�g�) pour pr�venir celui construit par le compilateur.
//
//       Revision 1.14  2002/01/17 09:39:05  marmottes
//       correction de sp�cifications throw (FA 0003)
//
//       Revision 1.13  2001/07/17 15:32:18  luc
//       ajout du vecteur observ� pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.12  2001/03/26 11:12:46  luc
//        mise � jour r�sultant de la mod�lisation des inhibitions dans la
//       classe SenseurOptique
//
//       Revision 1.11  2000/09/13 10:22:29  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.10  2000/03/30 17:01:24  luc
//       ajout du copyright CNES
//
//       Revision 1.9  1999/11/02 07:19:22  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.8  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines m�thodes (correction des oublis
//       apr�s le passage aux exceptions)
//
//       Revision 1.7  1999/08/06 13:32:19  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 1.6  1998/06/25 06:15:15  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.5  1998/02/04 08:49:37  luc
//       mise en place d'un en-t�te de classe au format AMIGAU
//
//       Revision 1.4  1997/11/27 07:08:32  luc
//       remplacement de la notion d'astre par la notion de cible
//       ajout du param�trage des cibles de type stations sol
//
//       Revision 1.3  1997/09/23 09:26:48  luc
//       ajout d'une gestion des unit�s de consigne et de mesure
//       interne au senseur
//
//       Revision 1.2  1997/09/01 10:31:12  luc
//       correction de la valeur de consigne scalaire m�moris�e
//
//       Revision 1.1  1997/08/20 09:51:39  luc
//       Initial revision
//
//$Version
//       $Id: SenseurElevation.h,v 1.16 2003/02/27 16:15:30 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurElevation_h
#define __marmottes_SenseurElevation_h

#include "marmottes/SenseurVecteur.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurElevation
//
//$Resume
//       mod�lisation d'un senseur mesurant des angles entre vecteur et plan.
//
//$Description
//       mod�lisation d'un senseur g�om�trique mesurant des
//       angles entre un vecteur et un plan.
//
//$Usage
//>     construction : 
//          � partir du nom, du rep�re satellite, de l'axe de calage
//          et de la pr�cision, par copie
//          La classe �tant abstraite, les constructeurs sont appel�s
//          par les constructeurs des classes d�riv�es.
//>     utilisation  : 
//>       SenseurElevation& operator = () 
//          affectation
//>       virtual int modeliseConsigne () 
//          permet de stocker un mod�le de la consigne que doit
//          respecter un senseur contr�lant l'attitude du satellite
//          dans l'�tat courant ATTENTION: dans cet �tat, l'attitude
//          ne doit pas �tre utilis�e, elle ne sera initialis�e
//          correctement qu'� la fin de la r�solution ayant utilis� ce
//          mod�le!
//>       virtual double mesure        () 
//          retourne la mesure que donnerait le senseur dans l'�tat donn�
//>       virtual Senseur* copie       () 
//          retourne une copie du senseur allou�e en m�moire
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class SenseurElevation : public SenseurVecteur
{ public :

  // constructeurs
  SenseurElevation (const string& nom, const RotDBL& repere,
                    const VecDBL& axeCalage, double precision,
                    codeCible code, const StationCible *ptrStation,
                    const VecDBL& observe,
                    Parcelle* ptrChampDeVue,
                    Parcelle *ptrChampInhibitionSoleil,
                    Parcelle *ptrChampInhibitionLune,
                    Parcelle *ptrChampInhibitionCentral,
                    double margeEclipseSoleil, double margeEclipseLune,
                    double seuilPhaseLune, const VecDBL& reference)
    throw (MarmottesErreurs)
    : SenseurVecteur (nom, repere, axeCalage, precision,
                      code, ptrStation, observe, ptrChampDeVue,
                      ptrChampInhibitionSoleil, ptrChampInhibitionLune,
                      ptrChampInhibitionCentral,
                      margeEclipseSoleil, margeEclipseLune,
                      seuilPhaseLune, reference)
  {}
  SenseurElevation (const SenseurElevation& s)
    : SenseurVecteur (s)
  {}

  SenseurElevation& operator = (const SenseurElevation& s);

  // destructeur
  virtual ~SenseurElevation () {}

  virtual Senseur* copie () const { return new SenseurElevation (*this); }

  // fonctions de r�solution de l'attitude
  virtual void    modeliseConsigne (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);
  virtual double  mesure           (const Etat& etat)
    throw (MarmottesErreurs);

protected :

  // constructeur par defaut : ne doit JAMAIS �tre utilis�
  SenseurElevation () {}

};

#endif

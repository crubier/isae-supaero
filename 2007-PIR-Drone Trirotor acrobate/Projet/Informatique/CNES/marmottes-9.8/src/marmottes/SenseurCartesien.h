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
//>       SenseurCartesien.h
//
//$Resume
//       fichier d'en-t�te de la classe SenseurCartesien
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class SenseurCartesien
//
//$Historique
//       $Log: SenseurCartesien.h,v $
//       Revision 1.14  2003/02/27 16:16:04  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.13  2002/12/11 17:12:57  marmottes
//       DM-ID 12 Ajout d'un constructeur par d�faut (prot�g�) pour pr�venir celui construit par le compilateur.
//
//       Revision 1.12  2002/01/17 09:38:03  marmottes
//       correction de sp�cifications throw (FA 0003)
//
//       Revision 1.11  2001/07/17 15:30:32  luc
//       ajout du vecteur observ� pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.10  2001/03/26 11:12:26  luc
//        mise � jour r�sultant de la mod�lisation des inhibitions dans la
//       classe SenseurOptique
//
//       Revision 1.9  2000/09/13 10:09:02  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.8  2000/03/30 17:01:23  luc
//       ajout du copyright CNES
//
//       Revision 1.7  1999/11/02 07:19:22  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.6  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines m�thodes (correction des oublis
//       apr�s le passage aux exceptions)
//
//       Revision 1.5  1999/08/06 13:32:19  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 1.4  1998/06/25 06:14:10  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.3  1997/11/27 07:07:50  luc
//       remplacement de la notion d'astre par la notion de cible
//       ajout du param�trage des cibles de type stations sol
//
//       Revision 1.2  1997/09/23 09:25:57  luc
//       ajout d'une gestion des unit�s de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/09/15 13:48:39  luc
//       Initial revision
//
//$Version
//       $Id: SenseurCartesien.h,v 1.14 2003/02/27 16:16:04 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurCartesien_h
#define __marmottes_SenseurCartesien_h

#include "marmottes/SenseurVecteur.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurCartesien
//
//$Resume
//       mod�lisation d'un senseur mesurant une coordonn�e cart�sienne
//
//$Description
//       Cette classe concr�te mod�lise un senseur mesurant la projection
//       de la cible sur un axe de r�f�rence.
//
//$Usage
//>     construction : 
//          � partir du nom, du rep�re satellite, de l'axe de calage
//          et de la pr�cision, par copie
//          La classe �tant abstraite, les constructeurs sont appel�s
//          par les constructeurs des classes d�riv�es.
//>     utilisation  : 
//>       SenseurCartesien& operator =  () 
//          affectation
//>       virtual void respecterMesures () 
//          force le senseur � respecter les unit�s de mesures dans
//          ses sorties
//>       virtual void convertirMesures () 
//          force le senseur � convertir les unit�s de mesures dans
//          ses sortie
//>       virtual int modeliseConsigne  () 
//          permet de stocker un mod�le de la consigne que doit
//          respecter un senseur contr�lant l'attitude du satellite
//          dans l'�tat courant ATTENTION: dans cet �tat, l'attitude
//          ne doit pas �tre utilis�e, elle ne sera initialis�e
//          correctement qu'� la fin de la r�solution ayant utilis� ce
//          mod�le!
//>       virtual double mesure         () 
//          retourne la mesure que donnerait le senseur dans l'�tat donn�
//>       virtual Senseur* copie        () 
//          retourne une copie du senseur allou�e en m�moire
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


class SenseurCartesien : public SenseurVecteur
{ public :

  // constructeurs
  SenseurCartesien (const string& nom, const RotDBL& repere,
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
    : SenseurVecteur (nom, repere, axeCalage,
                      degres (precision), // <-- pour compenser la conversion
                                          // inverse de la classe de base :-(
                      code, ptrStation, observe, ptrChampDeVue,
                      ptrChampInhibitionSoleil, ptrChampInhibitionLune,
                      ptrChampInhibitionCentral,
                      margeEclipseSoleil, margeEclipseLune, seuilPhaseLune,
                      reference)
  {}
  SenseurCartesien (const SenseurCartesien& s)
    : SenseurVecteur (s)
  {}

  SenseurCartesien& operator = (const SenseurCartesien& s);

  // destructeur
  virtual ~SenseurCartesien () {}

  virtual void respecterMesures ();
  virtual void convertirMesures ();

  virtual Senseur* copie () const { return new SenseurCartesien (*this); }

  // fonctions de r�solution de l'attitude
  virtual void    modeliseConsigne (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);
  virtual double  mesure           (const Etat& etat)
    throw (MarmottesErreurs);

protected :

  // constructeur par defaut : ne doit JAMAIS �tre utilis�
  SenseurCartesien () {}

};

#endif

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
//>       SenseurDiedre.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurDiedre
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       class SenseurDiedre 
//>         SenseurDiedre()   
//>         operator =()      
//>         respecterMesures()
//>         convertirMesures()
//>         nouveauRepere()   
//>         modeliseConsigne()
//>         mesure()          
//>         foncEcart()       
//
//$Historique
//       $Log: SenseurDiedre.cpp,v $
//       Revision 1.18  2003/10/08 09:39:41  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 1.17  2003/02/27 16:40:58  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 1.16  2003/02/04 16:39:23  marmottes
//       DM-ID 17 Mise � jour de l'extension du fichier dans le bandeau
//
//       Revision 1.15  2002/01/17 09:27:32  marmottes
//       correction de sp�cifications throw
//
//       Revision 1.14  2001/07/17 15:39:14  luc
//       ajout du vecteur observ� pour la cible vitesse-sol-apparente
//       lancement d'une exception par le constructeur
//
//       Revision 1.13  2001/03/26 11:17:14  luc
//       mise � jour r�sultant de la mod�lisation des inhibitions
//       dans la classe SenseurOptique
//
//       Revision 1.12  2000/09/13 10:21:17  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.11  2000/03/30 17:01:20  luc
//       ajout du copyright CNES
//
//       Revision 1.10  1999/12/13 08:02:08  luc
//       recalage de la mesure � moins d'un demi-tour de la valeur de consigne
//
//       Revision 1.9  1999/08/20 07:37:28  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des m�thodes "throw"
//
//       Revision 1.8  1999/08/06 13:32:15  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 1.7  1999/04/20 16:03:38  luc
//       mise au propre du filtrage des secteurs de consigne par les champs de vue
//
//       Revision 1.6  1998/06/24 20:04:36  luc
//       �limination des variables statiques RCS
//       modification du format des en-t�tes
//
//       Revision 1.5  1998/04/26 19:44:58  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.4  1998/02/04 17:49:32  luc
//       ajout d'une sp�cialisation de foncEcart de sorte que
//       la valeur produite soit bien un �cart entre mesure et consigne
//       (dans le cas contraire, des probl�mes se posent pour des
//       pseudo-senseurs utilisant une cible tr�s proche de l'axe sensible)
//
//       Revision 1.3  1997/11/27 06:56:47  luc
//       remplacement de la notion d'astre par la notion de cible
//       ajout du param�trage des cibles de type stations sol
//
//       Revision 1.2  1997/09/23 09:29:46  luc
//       ajout d'une gestion des unit�s de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/08/20 09:23:54  luc
//       Initial revision
//
//
//$Version
//       $Id: SenseurDiedre.cpp,v 1.18 2003/10/08 09:39:41 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurDiedre.h"

SenseurDiedre::SenseurDiedre (const string& nom, const RotDBL& repere,
                              const VecDBL& axeCalage, double precision,
                              codeCible code, const StationCible *ptrStation,
                              const VecDBL& observe,
                              Parcelle* ptrChampDeVue,
                              Parcelle *ptrChampInhibitionSoleil,
                              Parcelle *ptrChampInhibitionLune,
                              Parcelle *ptrChampInhibitionCentral,
                              double margeEclipseSoleil,
                              double margeEclipseLune,
                              double seuilPhaseLune,
                              const VecDBL& referenceZero,
                              const VecDBL& axeSensible)
  : SenseurOptique (nom, repere, axeCalage, radians (precision),
                    code, ptrStation, observe, ptrChampDeVue,
                    ptrChampInhibitionSoleil, ptrChampInhibitionLune,
                    ptrChampInhibitionCentral,
                    margeEclipseSoleil, margeEclipseLune, seuilPhaseLune)
{ RotDBL sensSat = -repere;

  // calcul des vecteurs de base des mesures en rep�re satellite
  normalPlan0_  = axeSensible ^ referenceZero;
  normalPlan0_  = sensSat (normalPlan0_);
  dansPlan0_    = normalPlan0_ ^ sensSat (axeSensible);

  // normalisation des vecteurs
  normalPlan0_.normalise ();
  dansPlan0_.normalise   ();

}

SenseurDiedre& SenseurDiedre::operator = (const SenseurDiedre& s)
{ if (&s != this)    // protection contre x = x
  { SenseurOptique::operator = (s);
    normalPlan0_ = s.normalPlan0_;
    dansPlan0_   = s.dansPlan0_;
  }

  return *this;

}

void SenseurDiedre::respecterMesures ()
{ // m�morisation du besoin de fournir des mesures en radians

  if (conversionMesures ())
    reinitialisePrecision (radians (precision ())); // jusque l� on �tait en degr�s

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::respecterMesures ();

}

void SenseurDiedre::convertirMesures ()
{ // m�morisation du besoin de fournir des mesures en degr�s

  if (! conversionMesures ())
    reinitialisePrecision (degres (precision ())); // jusque l� on �tait en radians

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::convertirMesures ();

}

void SenseurDiedre::nouveauRepere (const RotDBL& nouveau)
{ // r�orientation du senseur
  RotDBL decalage ((-nouveau) (repere ()));
  dansPlan0_   = decalage (dansPlan0_);
  normalPlan0_ = decalage (normalPlan0_);

  // appel de la fonction de la classe de base
  SenseurOptique::nouveauRepere (nouveau);

}

void SenseurDiedre::modeliseConsigne (const Etat& etat, double valeur)
  throw (CantorErreurs, MarmottesErreurs)
{ 
  if (conversionConsignes ())
    valeur = radians (valeur);  // la consigne �tait en degr�s

  // la valeur m�moris�e doit l'�tre dans l'unit� de mesure
  if (conversionMesures ())
    Senseur::modeliseConsigne (etat, degres (valeur));
  else
    Senseur::modeliseConsigne (etat, valeur);

  // initialisation de la direction de la cible du senseur
  initialiseCible (etat);

  // une consigne de senseur di�dre est un demi-plan
  // (= c�ne d'ouverture PI/2, dont on ne prend qu'une moiti�)
  VecDBL axe        = cos (valeur) * normalPlan0_ - sin (valeur) * dansPlan0_;
  secteursConsigne_ = Secteurs (Cone (axe, 0.5 * M_PI),
                                dansPlan0_ ^ normalPlan0_,
                                Creneau (0.0, M_PI));
  filtreSecteurs ();

  // on fait la conversion en ValeurDerivee1 une fois pour toutes
  axeVD1_ = VecDBLVD1 (axe);

}

double SenseurDiedre::mesure (const Etat& etat)
  throw (MarmottesErreurs)
{ 

  // initialisation de la direction de la cible du senseur
  initialiseCible (etat);

  VecDBL v = etat.attitude () (cible_);
  double m = atan2 (v | normalPlan0_, v | dansPlan0_);
  if (conversionMesures ())
  {
    m  = degres (m);      // la mesure doit �tre en degr�s
    m -= 360.0 * floor ((m - valeurConsigne () + 180.0) / 360.0);
  }
  else
    m -= (M_PI + M_PI) * floor ((m - valeurConsigne () + M_PI) / (M_PI + M_PI));

  return m;

}

ValeurDerivee1 SenseurDiedre::foncEcart (const Etat& etatPrecedent,
                                         const Etat& etatResolution,
                                         const RotVD1& attitude,
                                         const VecVD1& spin)
{

  if (code_ == codeVitesseSolApparente)
  { // il faut r�initialiser la cible, qui d�pend de l'attitude
    reinitVitesseSolApparente (etatResolution, attitude);
  }

  VecVD1 v = attitude (cibleVD1_);
  ValeurDerivee1 m = atan2 (v | normalPlan0_, v | dansPlan0_);
  if (conversionMesures ())
  {
    // la fonction degres () ne fonctionne qu'avec des doubles
    ValeurDerivee1 d = m * (180.0 / M_PI) - valeurConsigne ();
    return d - 360.0 * floor ((d.f0 () + 180.0) / 360.0);
  }
  else
  {
    ValeurDerivee1 d = m - valeurConsigne ();
    return d - (M_PI + M_PI) * floor ((d.f0 () + M_PI) / (M_PI + M_PI));
  }

}

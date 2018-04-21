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
//>       SenseurAlpha.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurAlpha
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       class SenseurAlpha  
//>         initialiseCible() 
//>         SenseurAlpha()    
//>         operator =()      
//>         respecterMesures()
//>         convertirMesures()
//>         nouveauRepere()   
//>         modeliseConsigne()
//>         mesure()          
//>         foncEcart()       
//
//$Historique
//       $Log: SenseurAlpha.cpp,v $
//       Revision 1.12  2003/10/08 09:39:41  marmottes
//       FA 0029, 0030, 0031
//       DM 0025, 0026, 0028
//
//       Revision 1.11  2003/02/04 16:37:23  marmottes
//       DM-ID 17 Mise � jour de l'extension du fichier dans le bandeau
//
//       Revision 1.10  2002/01/17 09:26:19  marmottes
//       correction de sp�cifications throw
//
//       Revision 1.9  2000/09/13 10:06:29  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.8  2000/03/30 17:01:20  luc
//       ajout du copyright CNES
//
//       Revision 1.7  1999/08/20 07:37:28  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des m�thodes "throw"
//
//       Revision 1.6  1999/08/06 13:32:15  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 1.5  1998/06/24 20:02:54  luc
//       �limination des variables statiques RCS
//       modification du format des en-t�tes
//
//       Revision 1.4  1998/04/26 20:00:18  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.3  1998/02/06 17:33:14  luc
//       ajout d'une sp�cialisation de foncEcart de sorte que
//       la valeur produite soit bien un �cart entre mesure et consigne
//       (dans le cas contraire, des probl�mes se posent pour des
//       pseudo-senseurs utilisant une cible tr�s proche de l'axe sensible)
//
//       Revision 1.2  1997/09/23 09:29:08  luc
//       ajout d'une gestion des unit�s de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/08/20 09:23:07  luc
//       Initial revision
//
//$Version
//       $Id: SenseurAlpha.cpp,v 1.12 2003/10/08 09:39:41 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurAlpha.h"

void SenseurAlpha::initialiseCible (double alpha)
{ // sauvegarde de la derni�re valeur de consigne en ascension droite
  alphaConsigne_ = alpha;

  // initialisation de la direction de pointage cible du senseur
  cible_ = VecDBL (sin (alpha), -cos (alpha), 0.0);

  // on fait la conversion en d�veloppement limit� une fois pour toutes
  cibleVD1_ = VecDBLVD1 (cible_);

}

SenseurAlpha::SenseurAlpha (const string& nom, const RotDBL& repere,
                            const VecDBL& axeCalage, double precision,
                            const VecDBL& observe)
  : SenseurGeometrique (nom, repere, axeCalage, radians (precision))
{ // calcul du vecteur observ� en rep�re satellite
  observe_       = (-repere) (observe);

  // consigne par d�faut: alpha = 0
  initialiseCible (0.0);

}

SenseurAlpha& SenseurAlpha::operator = (const SenseurAlpha& s)
{ if (&s != this)    // protection contre x = x
  { SenseurGeometrique::operator = (s);
    observe_       = s.observe_;
    alphaConsigne_ = s.alphaConsigne_;
  }

  return *this;

}

void SenseurAlpha::respecterMesures ()
{ // m�morisation du besoin de fournir des mesures en radians

  if (conversionMesures ())
    reinitialisePrecision (radians (precision ())); // jusque l� on �tait en degr�s

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::respecterMesures ();

}

void SenseurAlpha::convertirMesures ()
{ // m�morisation du besoin de fournir des mesures en degr�s

  if (! conversionMesures ())
    reinitialisePrecision (degres (precision ())); // jusque l� on �tait en radians

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::convertirMesures ();

}

void SenseurAlpha::nouveauRepere (const RotDBL& nouveau)
{ // r�orientation du senseur
  RotDBL decalage ((-nouveau) (repere ()));
  observe_ = decalage (observe_);

  // appel de la fonction de la classe de base
  SenseurGeometrique::nouveauRepere (nouveau);

}

void SenseurAlpha::modeliseConsigne (const Etat& etat, double valeur)
  throw (CantorErreurs, MarmottesErreurs)
{ 
  if (conversionConsignes ())
    valeur = radians (valeur);  // la consigne �tait en degr�s

  // la valeur m�moris�e doit l'�tre dans l'unit� de mesure
  if (conversionMesures ())
    Senseur::modeliseConsigne (etat, degres (valeur));
  else
    Senseur::modeliseConsigne (etat, valeur);

  initialiseCible (valeur);

  // une consigne d'ascension droite est un plan (= c�ne d'ouverture PI/2)
  secteursConsigne_ = Secteurs (Cone (observe_, 0.5 * M_PI));

  // on fait la conversion en d�veloppement limit� une fois pour toutes
  axeVD1_ = VecDBLVD1 (observe_);

}

double SenseurAlpha::mesure (const Etat& etat)
  throw (MarmottesErreurs)
{ 
  // projection de l'axe observ� dans le rep�re inertiel
  VecDBL obsInl ((-(etat.attitude ())) (observe_));

  // calcul de l'ascension droite
  double alpha = atan2 (obsInl.y (), obsInl.x ());

  // placement de la discontinuit� loin de la valeur de consigne
  double m = recaleAngle (alpha, alphaConsigne_);
  if (conversionMesures ())
    m = degres (m);  // la mesure doit �tre en degr�s

  return m;

}

ValeurDerivee1 SenseurAlpha::foncEcart (const Etat& etatPrecedent,
                                        const Etat& etatResolution,
                                        const RotVD1& attitude,
                                        const VecVD1& spin)
{ VecVD1 obsInl = (-attitude) (axeVD1_);
  ValeurDerivee1 alpha = atan2 (obsInl.y (), obsInl.x ());

  // placement de la discontinuit� loin de la valeur de consigne
  int            k = (int) floor ((alpha.f0 () + M_PI - alphaConsigne_) / (M_PI + M_PI));
  ValeurDerivee1 m = alpha - k * (M_PI + M_PI);
  if (conversionMesures ())
    m *= 180.0 / M_PI; // la fonction degres () ne fonctionne qu'avec des doubles

  return m - valeurConsigne ();

}

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
//>       SenseurDelta.cpp
//
//$Resume
//       fichier d'implantation de la classe SenseurDelta
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       class SenseurDelta  
//>         operator =()      
//>         respecterMesures()
//>         convertirMesures()
//>         nouveauRepere()   
//>         modeliseConsigne()
//>         mesure()          
//
//$Historique
//       $Log: SenseurDelta.cpp,v $
//       Revision 1.10  2003/02/04 16:39:08  marmottes
//       DM-ID 17 Mise � jour de l'extension du fichier dans le bandeau
//
//       Revision 1.9  2002/01/17 09:27:32  marmottes
//       correction de sp�cifications throw
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
//       Revision 1.5  1998/09/14 11:50:38  luc
//       v�rification de la consigne g�n�r�e
//
//       Revision 1.4  1998/06/24 20:04:15  luc
//       �limination des variables statiques RCS
//       modification du format des en-t�tes
//
//       Revision 1.3  1998/04/26 19:43:20  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.2  1997/09/23 09:29:39  luc
//       ajout d'une gestion des unit�s de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/08/20 09:23:12  luc
//       Initial revision
//
//$Version
//       $Id: SenseurDelta.cpp,v 1.10 2003/02/04 16:39:08 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/SenseurDelta.h"

SenseurDelta& SenseurDelta::operator = (const SenseurDelta& s)
{ if (&s != this)    // protection contre x = x
  { SenseurGeometrique::operator = (s);
    observe_       = s.observe_;
  }

  return *this;

}

void SenseurDelta::respecterMesures ()
{ // m�morisation du besoin de fournir des mesures en radians

  if (conversionMesures ())
    reinitialisePrecision (radians (precision ())); // jusque l� on �tait en degr�s

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::respecterMesures ();

}

void SenseurDelta::convertirMesures ()
{ // m�morisation du besoin de fournir des mesures en degr�s

  if (! conversionMesures ())
    reinitialisePrecision (degres (precision ())); // jusque l� on �tait en radians

  // appel de la fonction de la classe INITIALE, qui ne fait presque rien
  Senseur::convertirMesures ();

}

void SenseurDelta::nouveauRepere (const RotDBL& nouveau)
{ // r�orientation du senseur
  RotDBL decalage ((-nouveau) (repere ()));
  observe_ = decalage (observe_);

  // appel de la fonction de la classe de base
  SenseurGeometrique::nouveauRepere (nouveau);

}

void SenseurDelta::modeliseConsigne (const Etat& etat, double valeur)
  throw (CantorErreurs, MarmottesErreurs)
{ 
  if (conversionConsignes ())
    valeur = radians (valeur);  // la consigne �tait en degr�s

  // la valeur m�moris�e doit l'�tre dans l'unit� de mesure
  if (conversionMesures ())
    Senseur::modeliseConsigne (etat, degres (valeur));
  else
    Senseur::modeliseConsigne (etat, valeur);

  // la cible pointe toujours vers le p�le
  cible_    = VecDBL    (0.0, 0.0, 1.0);
  cibleVD1_ = VecDBLVD1 (cible_);

  // d�clinaison fix�e => distance du p�le fix�e
  secteursConsigne_ = Secteurs (Cone (observe_, 0.5 * M_PI - valeur));

  // on fait la conversion en d�veloppement limit� une fois pour toutes
  axeVD1_ = VecDBLVD1 (observe_);

  // retour normal � la fonction appelante
  verifieConsigne ();

}

double SenseurDelta::mesure (const Etat& etat)
  throw (MarmottesErreurs)
{
  // projection de l'axe observ� dans le rep�re inertiel
  RotDBL satInl = -(etat.attitude ());
  VecDBL obsInl (satInl (observe_));

  double m = asin (obsInl.z ());
  if (conversionMesures ())
    m = degres (m);      // la mesure doit �tre en degr�s

  return m;

}

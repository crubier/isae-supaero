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
//>       Senseur.cpp
//
//$Resume
//       fichier d'implantation de la classe Senseur
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       class Senseur       
//>         operator =()      
//>         respecterMesures()
//>         convertirMesures()
//>         nouveauRepere()   
//>         criteresControlabilite()   
//>         calage()          
//>         modeliseConsigne()
//
//$Historique
//       $Log: Senseur.cpp,v $
//       Revision 2.14  2003/02/04 16:37:05  marmottes
//       DM-ID 17 Mise � jour de l'extension du fichier dans le bandeau
//
//       Revision 2.13  2002/01/17 09:26:19  marmottes
//       correction de sp�cifications throw
//
//       Revision 2.12  2001/04/04 12:24:53  luc
//       ajout de la m�thode criteresControlabilite
//
//       Revision 2.11  2000/10/02 13:16:29  luc
//       remplacement d'attributs entiers en bool�ens
//
//       Revision 2.10  2000/03/30 17:01:20  luc
//       ajout du copyright CNES
//
//       Revision 2.9  1999/08/20 07:37:28  filaire
//       Correction de certaines erreurs dues au passage aux exceptions
//       Changement de signatures des m�thodes "throw"
//
//       Revision 2.8  1999/08/06 13:32:15  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 2.7  1998/06/24 20:02:34  luc
//       �limination des variables statiques RCS
//       modification du format des en-t�tes
//
//       Revision 2.6  1998/04/26 18:25:26  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.5  1997/09/23 09:29:01  luc
//       ajout d'une gestion des unit�s de consigne et de mesure
//       interne au senseur
//
//       Revision 2.4  1997/08/20 08:41:58  luc
//       ajout d'un en-t�te de fichier
//       utilisation de ChaineSimple
//       d�placement de constructeurs dans le .h (simplifi�s gr�ce � ChaineSimple)
//       implantation d'une version g�n�rique de la m�thode modeliseConsigne
//
//       Revision 2.3  1997/04/27 19:36:34  luc
//       inversion des codes de retour
//       changement des r�gles de nommage
//       passage de SCCS � RCS
//       
//       Revision 2.2  1996/09/11 17:43:04  luc
//       ajout du nom du senseur dans l'instance
//       
//       Revision 2.1  1996/07/31 17:21:34  luc
//       ajout d'une possibilit� de modifier le rep�re senseur � l'ex�cution
//       
//       Revision 1.1  1994/12/23 11:00:13  luc
//       Initial revision
//
//$Version
//       $Id: Senseur.cpp,v 2.14 2003/02/04 16:37:05 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "marmottes/Senseur.h"

Senseur& Senseur::operator = (const Senseur& s)
{ if (&s != this)    // protection contre x = x
  { nom_                = s.nom_;
    repereBase_         = s.repereBase_;
    repere_             = s.repere_;
    axeCalage_          = s.axeCalage_;
    precision_          = s.precision_;
    convertirConsignes_ = s.convertirConsignes_;
    convertirMesures_   = s.convertirMesures_;
    valeurConsigne_     = s.valeurConsigne_;
  }

  return *this;

}


void Senseur::respecterMesures ()
{ // implantation de la m�thode virtuelle dans la classe de base

  // ATTENTION : bien que cette m�thode soit implant�e, elle est virtuelle pure
  // les classes d�riv�es DOIVENT fournir �galement une implantation
  // qui peut �ventuellement faire appel � cette implantation de base
  convertirMesures_ = false;

}


void Senseur::convertirMesures ()
{ // implantation de la m�thode virtuelle dans la classe de base

  // ATTENTION : bien que cette m�thode soit implant�e, elle est virtuelle pure
  // les classes d�riv�es DOIVENT fournir �galement une implantation
  // qui peut �ventuellement faire appel � cette implantation de base
  convertirMesures_ = true;

}


void Senseur::nouveauRepere (const RotDBL& nouveau)
{ // rotation du senseur

  // les coordonn�es de axeCalage_ sont (et restent en permanence)
  // exprim�es dans le rep�re de base : on ne les touche donc pas

  // modification du rep�re courant
  repere_ = nouveau;

}


void Senseur::criteresControlabilite (const Etat& etat,
                                      codeAstre *ptrInhibant,
                                      codeAstre *ptrEclipsant,
                                      double    *ptrEcartFrontiere,
                                      bool      *ptrAmplitudeSignificative)
  throw (MarmottesErreurs, CantorErreurs)
{ // calcul des crit�res de contr�labilit�

  // l'impl�mentation par d�faut consiste � dire que tout est parfait
  *ptrInhibant               = nonSignificatif;
  *ptrEclipsant              = nonSignificatif;
  *ptrEcartFrontiere         = +1.0;
  *ptrAmplitudeSignificative = false;

}

void Senseur::calage (double c)
  throw (MarmottesErreurs)
{ // rotation du senseur autour d'un axe de calage pr�vu

  if (axeCalage_.norme () < 0.5)
    throw MarmottesErreurs (MarmottesErreurs::calage_interdit);

  // remise � z�ro du rep�re
  nouveauRepere (repereBase_);

  // prise en compte du calage
  nouveauRepere (RotDBL (axeCalage_, -c) (repereBase_));

}

void Senseur::modeliseConsigne (const Etat&, double valeur)
  throw (CantorErreurs, MarmottesErreurs)
{ // implantation de la m�thode virtuelle dans la classe de base

  // ATTENTION : bien que cette m�thode soit implant�e, elle est virtuelle pure
  // les classes d�riv�es DOIVENT fournir �galement une implantation
  // qui peut �ventuellement faire appel � cette implantation de base
  valeurConsigne_ = valeur;

}

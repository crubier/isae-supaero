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
//>       Famille.h
//$Resume
//       fichier d'en-t�te de la classe Famille
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class Famille
//$Historique
//       $Log: Famille.h,v $
//       Revision 1.4  2000/03/30 17:01:21  luc
//       ajout du copyright CNES
//
//       Revision 1.3  1999/11/02 07:19:20  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.2  1999/10/15 11:48:35  luc
//       ajout d'un bool�en dans le constructeur par pointeur
//       de fa�on � d�terminer si l'instance peut prendre la
//       responsabilit� de la d�sallocation m�moire ou si elle
//       doit se faire sa propre copie
//
//       Revision 1.1  1999/07/29 12:10:24  filaire
//       Creation de la classe
//       Sert d'interface a la classe FamilleAbstraite
//
//
//$Version
//       $Id: Famille.h,v 1.4 2000/03/30 17:01:21 luc Exp $
//
//$Auteur
//       G. Filaire CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_Famille_h
#define __marmottes_Famille_h

#include "FamilleAbstraite.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Famille
//$Resume
//       mod�le g�om�trique d'attitude
//
//$Description
//       Cette classe repr�sente une famille de solutions. Elle permet de g�rer 
//       des familles de solutions comme s'il s'agissait d'objets r�els alors 
//       que C++ ne permet que de tra�ter des pointeurs sur la classe de base 
//       abstraite.
//
//$Usage
//>     construction : 
//          sans argument, par copie, par un pointeur sur une
//          FamilleAbstraite et indicateur de copie (si la copie n'est
//          pas requise, l'instance prend directement le pointeur et
//          devient responsable de sa d�sallocation, il faut donc
//          qu'il s'agisse de m�moire allou�e par un new)
//>     utilisation  : 
//>       Famille& operator =              () 
//          affectation
//>       RotVD1 inertielCanonique         () 
//          retourne la rotation qui passe du rep�re inertiel au rep�re canonique
//          pour une famille et une valeur du degr� de libert� donn�es
//$<>
///////////////////////////////////////////////////////////////////////////////

class Famille
{ 
  public :

  // constructeurs
  Famille ();
  Famille (const Famille& f);
  Famille (FamilleAbstraite* ptr, bool copieRequise);

  // op�rateur d'affectation
  Famille& operator = (const Famille& f);

  // destructeur
  virtual ~Famille ();

  // m�thode qui retourne la rotation de passage du rep�re inertiel au rep�re canonique
  RotVD1 inertielCanonique (const ValeurDerivee1& t) const;

  private :

  //pointeur de FamilleAbstraite
  FamilleAbstraite *  ptrFamille_; 

};

#endif

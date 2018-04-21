///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//        Bibam
//$Application
//        Club
//$Nom
//>       IterateurBase.h
//$Resume
//       fichier d'en-t�te de la classe IterateurBase
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class IterateurBase
//$Historique
//       $Log: IterateurBase.h,v $
//       Revision 1.4  2002/12/09 15:54:03  club
//       DM-ID 12 Mise en conformit� des constructeurs/destructeurs avec la norme qualit�
//
//       Revision 1.3  2000/10/24 14:18:14  club
//       mise � jour des includes et ajout des tests de configuration.
//
//       Revision 1.2  2000/07/03 08:49:05  club
//       Ajout du copyright CNES
//
//       Revision 1.1.2.2  2000/04/04 07:08:08  club
//       d�placement du copyright
//
//       Revision 1.1.2.1  2000/03/30 14:46:55  club
//       ajout du copyright CNES
//
//       Revision 1.1  1999/03/15 15:04:06  club
//       version initiale
//
//$Version
//       $Id: IterateurBase.h,v 1.4 2002/12/09 15:54:03 club Exp $
//
//$Auteur
//        P-A.Cros CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_IterateurBase_h
#define club_IterateurBase_h

#include "club/ClubErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class IterateurBase
//$Resume
//       classe abstraite de d�finition de l'interface minimale d'un it�rateur
//       sur une structure de donn�es, l'unit� de parcours (�l�ment) est propre 
//       a chaque classe d�riv�e de cet it�rateur (caract�re, champ,...)
//$Description
//       classe de base m�morisant la notion d'�tat de l'it�rateur
//       et les op�rations indispensables a un objet it�rateur
//       
//$Usage
//>     construction :
//          prot�g�e car seuls les classes d�riv�es peuvent instancier
//          un it�rateur de base
//>     utilisation  : 
//>       virtual void premier   () 
//          positionne l'it�rateur sur le premier �l�ment de la structure
//          de donn�es
//>       virtual void dernier   () 
//          positionne l'it�rateur sur le dernier �l�ment de la structure
//          de donn�es
//>       virtual void allerSur  ()
//          positionne l'it�rateur sur l'�l�ment i de la structure
//          de donn�es
//>       virtual int termine    ()
//          indique que l'it�rateur est a la fin de la structure
//          de donn�es
//>       virtual int nombreIterations
//          renvoie le nombre d'�l�ments de la structure de donn�es
//>       virtual int operator++ ()
//          positionne l'it�rateur sur l'�l�ment suivant de la structure
//          de donn�es
//>       virtual int operator-- ()
//          positionne l'it�rateur sur l'�l�ment suivant de la structure
//          de donn�es
//>       void controleEtat()
//          retourne vrai si l'�tat de l'it�rateur est conforme � l'�tat du 
//          tampon
//$Auteur
//        P-A.Cros
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////


class IterateurBase {

public:

  // positionnement du pointeur :
  virtual void premier          ()           throw(ClubErreurs) = 0;
  virtual void dernier          ()           throw(ClubErreurs) = 0;
  virtual void allerSur         (int index ) throw(ClubErreurs) = 0;

  // indicateur d'etat de l'iterateur :
  virtual int  termine          ()  const                       = 0;

  // mecanisme d'iteration :
  virtual int  nombreIterations ()  const    throw(ClubErreurs) = 0;
  virtual int  operator++(int)               throw(ClubErreurs) = 0;
  virtual int  operator--(int)               throw(ClubErreurs) = 0;

protected :
  // variable permettant de controler l'etat de l'iterateur. 
  unsigned long etat_; 

  // protection des constructeurs pour eviter toute instanciation.
  IterateurBase() : etat_ (0) {}
  IterateurBase (const IterateurBase & other)
  {
    etat_ = other.etat_;
  }
  virtual IterateurBase & IterateurBase::operator = (const IterateurBase & other)
  {
    if (this != &other)
      etat_ = other.etat_;
    return *this;
  }

  // destructeur
  virtual ~IterateurBase () {}

  // etat de l'iterateur :
  virtual void  controleEtat() const throw(ClubErreurs) = 0;

};


#endif

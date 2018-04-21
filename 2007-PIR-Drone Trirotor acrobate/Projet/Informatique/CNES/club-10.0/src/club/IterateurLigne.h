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
//>       IterateurLigne.h
//$Resume
//       fichier d'en-t�te de la classe IterateurLigne
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class IterateurLigne
//$Historique
//       $Log: IterateurLigne.h,v $
//       Revision 1.6  2003/07/17 12:38:28  club
//       Mise a jour suite aux patchs du 17/07/003
//
//       Revision 1.5  2002/12/09 15:55:17  club
//       DM-ID 12 Mise en conformit� des constructeurs/destructeurs avec la norme qualit�
//
//       Revision 1.4  2000/10/24 14:18:15  club
//       mise � jour des includes et ajout des tests de configuration.
//
//       Revision 1.3  2000/07/03 08:49:05  club
//       Ajout du copyright CNES
//
//       Revision 1.2.2.2  2000/04/04 07:08:09  club
//       d�placement du copyright
//
//       Revision 1.2.2.1  2000/03/30 14:46:55  club
//       ajout du copyright CNES
//
//       Revision 1.2  1999/07/06 15:24:16  club
//       Changement des signatures pour gestion des erreurs
//       par m�canisme d'exception
//
//       Revision 1.1  1999/03/15 15:06:06  club
//       version initiale
//
//$Version
//       $Id: IterateurLigne.h,v 1.6 2003/07/17 12:38:28 club Exp $
//
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//        G. Lajon  CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_IterateurLigne_h
#define club_IterateurLigne_h

#include "club/IterateurAscii.h"
#include "club/ClubErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class IterateurLigne
//$Resume
//        classe it�rateur qui parcourt ligne � ligne un tampon ascii
//
//$Description
//        la classe h�rite de mani�re virtuelle de la classe
//        IterateurAscii, ce qui permet lors d'une d�rivation multiple
//        de cette classe de partager les m�thodes et attributs de la classe
//        IterateurAscii ( sinon une instance par classe de base dans le cas
//        d'un h�ritage multiple ).
//$Usage
//>     construction :
//          avec r�f�rence ou avec pointeur sur un tampon ascii
//>     utilisation : 
//>       void premier                () 
//          positionne l'it�rateur sur la premi�re ligne du tampon
//>       void dernier                () 
//          positionne l'it�rateur sur la derni�re ligne du tampon
//>       void allerSur               () 
//          positionne l'it�rateur sur la ligne l du tampon
//>       int termine                 ()
//          indique que l'it�rateur est a la fin du tampon
//>       int nombreIterations        ()
//          renvoie le nombre de lignes du tampon
//>       int operator++              () 
//          positionne l'it�rateur sur la ligne suivante du tampon
//>       int operator--              () 
//          positionne l'it�rateur sur la ligne pr�c�dente du tampon
//>       int longueurElement         () 
//          renvoie la longueur de la ligne
//>       const char* valeur          () 
//          renvoie la valeur de la ligne courante 
//>       void synchronize            () 
//          si direction = 1 synchronise la position de l'it�rateur 
//          sur la position r�elle dans le tampon (it�rateur alt�r� 
//          lors d'une modification du tampon)
//          si direction = 0 (par defaut)
//          synchronise l'�tat du tampon (position courante du curseur) 
//          sur la position courante de l'it�rateur (m�morisation avant
//          alt�ration du tampon)  
//>       void actualise              () 
//          r�initialise l'it�rateur sur le d�but du tampon
//>       void actualiseEtat          () protegee - 
//          remet l'it�rateur en conformit� avec l'�tat courant du tampon
//>       void rechercheLigne           () protegee - 
//          recherche de la ligne i
//>       int compteLignes            () protegee - 
//          retourne le nombre de lignes a partir d'une position donnee
//          jusqu'� la fin de tampon 
//$Auteur
//        P-A.Cros
//        G. Lajon   CSSI
//        Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////




class IterateurLigne : public virtual IterateurAscii {


public :

  // constructeurs :
  IterateurLigne( const TamponAscii& tampon, int compterLignes = 1 ) 
    throw(ClubErreurs);
  IterateurLigne( TamponAscii* tampon, int compterLignes = 1 ) 
    throw(ClubErreurs);

  // destructeur
  ~IterateurLigne () {}

  void                premier          () throw(ClubErreurs);
  void                dernier          () throw(ClubErreurs);
  virtual void        allerSur         (int index)  throw(ClubErreurs);

  int                 termine          () const;

  int                 nombreIterations ()  const throw(ClubErreurs);
  int                 operator++       (int) throw(ClubErreurs);
  int                 operator--       (int)  throw(ClubErreurs);

  int                 longueurElement  (int avecFin = 0) const 
    throw(ClubErreurs);
  const char*         valeur           ()  const throw(ClubErreurs);

  void                synchronize      (int direction = 0)  throw(ClubErreurs);
  void                actualise        ();

protected :
  char* debutLigne_;
  int   numLigne_; 
  int   nombreLignes_;

  void                actualiseEtat          ();

  void                rechercheLigne         (int l) throw(ClubErreurs);
  int                 compteLignes           (const char* mobile) const;

  // autres constructeurs
  IterateurLigne () 
  {
    debutLigne_   = NULL;
    numLigne_     = 0;
    nombreLignes_ = 0;
  }
  IterateurLigne (const IterateurLigne & other)
  {
    debutLigne_   = other.debutLigne_;
    numLigne_     = other.numLigne_;
    nombreLignes_ = other.nombreLignes_;
  }
  IterateurLigne & operator = (const IterateurLigne & other)
  {
    if (this != &other)
    {
      debutLigne_   = other.debutLigne_;
      numLigne_     = other.numLigne_;
      nombreLignes_ = other.nombreLignes_;
    }
    return *this;
  }

};


#endif

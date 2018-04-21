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
//       Cantor
//
//$Nom
//>       StatistiqueEchantillon.h
//
//$Resume
//       fichier d'en-t�te de la classe StatistiqueEchantillon
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class StatistiqueEchantillon
//
//$Historique
//       $Log: StatistiqueEchantillon.h,v $
//       Revision 1.5  2002/12/10 15:36:31  cantor
//       DM-ID 12 Ajout d'un destructeur pour pr�venir celui cr�� par le compilateur
//
//       Revision 1.4  2002/12/02 13:48:49  cantor
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.3  2000/08/09 14:36:45  cantor
//       R�union de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.2.4.1  2000/03/30 15:36:11  cantor
//       ajout du copyright CNES
//
//       Revision 1.2  1998/06/24 15:28:53  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.1  1998/05/12 12:58:37  luc
//       Initial revision
//
//$Version
//       $Id: StatistiqueEchantillon.h,v 1.5 2002/12/10 15:36:31 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __StatistiqueEchantillon_h
#define __StatistiqueEchantillon_h

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class StatistiqueEchantillon
//
//$Resume
//       classe g�rant un �chantillon statistique
//
//$Description
//       Cette classe concr�te permet de constituer un �chantillon
//       statistique et d'en extraire les caract�ristiques
//
//$Usage
//>     construction : 
//          sans argument, par copie
//>     utilisation  : 
//>       StatistiqueEchantillon& operator =        () 
//          affectation
//>       const StatistiqueEchantillon& operator += () 
//          ajoute un point a l'�chantillon.
//>       double ecartType                          () 
//          retourne l'�cart type de la loi suivie par l'�chantillon
//>       int nbPoints                              () 
//          retourne le nombre de points de l'�chantillon
//>       double min                                () 
//          retourne la valeur minimale rencontr�e sur l'�chantillon
//>       double max                                () 
//          retourne la valeur maximale rencontr�e sur l'�chantillon
//>       double moyenne                            () 
//          retourne la valeur moyenne de l'�chantillon
//
//$Version
//       $Id: StatistiqueEchantillon.h,v 1.5 2002/12/10 15:36:31 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////
class StatistiqueEchantillon
{ 

public :

  // constructeurs
  StatistiqueEchantillon ();
  StatistiqueEchantillon (const StatistiqueEchantillon& s);
  StatistiqueEchantillon& operator = (const StatistiqueEchantillon& s);

  // destructeur
  ~StatistiqueEchantillon () {}

  // enrichissement de l'�chantillon
  const StatistiqueEchantillon& operator += (double x);
  const StatistiqueEchantillon& operator += (const StatistiqueEchantillon& s);

  // statistiques
  int    nbPoints  () const { return s1_;  }
  double min       () const { return min_; }
  double max       () const { return max_; }

  double moyenne   () const
  { return (s1_ > 0) ? (sX_ / s1_) : 0.0;  }

  double ecartType () const;

private :

  int                  s1_;
  double               min_;
  double               max_;
  double               sX_;
  double               sX2_;

};

#endif

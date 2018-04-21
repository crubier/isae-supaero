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
//>       MoindreCarreLineaire.h
//
//$Resume
//       fichier d'en-t�te de la classe MoindreCarreLineaire
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class MoindreCarreLineaire
//>       void factLDLt()            
//>       void resoudLDLt()         
//
//$Historique
//       $Log: MoindreCarreLineaire.h,v $
//       Revision 1.10  2002/12/02 13:39:09  cantor
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.9  2001/06/05 15:19:24  cantor
//       passage au m�canisme des exceptions pour la gestion des erreurs
//       (ceci induit des modifications de signatures)
//
//       Revision 1.8  2000/08/09 14:36:44  cantor
//       R�union de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.7.4.1  2000/03/30 15:36:10  cantor
//       ajout du copyright CNES
//
//       Revision 1.7  1998/06/24 16:45:00  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.6  1998/04/26 15:23:58  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.5  1998/01/22 10:40:21  luc
//       am�lioration de l'en-t�te de classe
//
//       Revision 1.4  1997/09/10 06:56:23  luc
//       correction des caract�res RCS
//
//       Revision 1.3  1997/07/06 10:30:22  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 1.2  1997/03/26 06:39:45  luc
//       changement des conventions de nommage
//       
//       Revision 1.1  1997/03/24 08:37:10  luc
//       Initial revision
//
//$Version
//       $Id: MoindreCarreLineaire.h,v 1.10 2002/12/02 13:39:09 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_MoindreCarreLineaire_h
#define __cantor_MoindreCarreLineaire_h

#include "cantor/CantorErreurs.h"

// fonctions de r�solution en place d'un syst�me lin�aire sym�trique
void factLDLt   (double *m, int n, double seuil) throw (CantorErreurs);
void resoudLDLt (const double *m, int n, double x []);

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class MoindreCarreLineaire
//$Resume
//       R�solution d'un probl�me de moindres carr�s lin�aire
//
//$Description
//       R�solution au sens des moindres carr�s pond�r�s d'un mod�le
//       lin�aire de dimension n : rk = a1 rk,1 + ... + an rk,n des
//       r�sidus de mesures d'un syst�me rk = mk - mthk connaissant
//       les mesures r�lles mk et th�oriques mthk et les coefficients
//       de lin�arit� rk,i. Cette classe peut �tre utilis�e pour
//       r�soudre une it�ration d'un probl�me g�n�ral d'ajustement au
//       sens des moindre carr�s (les fki sont alors les d�riv�es
//       partielles des mesures autour de la valeur courante du
//       vecteur d'�tat).
//
//$Usage
//>     construction : 
//          sans argument, � partir de la dimension, par copie
//>     utilisation  : 
//>       MoindreCarreLineaire& operator = () 
//          affectation
//>       void ajouteResidu                () 
//          ajoute un r�sidu pond�r� dans l'�chantillon de r�f�rence
//>       void oteResidu                   () 
//          ote un r�sidu pond�r� dans l'�chantillon de r�f�rence
//>       void oteTousResidus              () 
//          vide l'�chantillon de r�f�rence
//>       void ajuste                      () 
//          r�alise l'ajustement des coefficients au sens des moindres
//          carr�s
//>       void coefficients                () 
//          copie les coefficients du mod�le dans le tableau fourni en
//          argument
//>       double erreurQuadratique         () 
//          retourne l'erreur quadratique (somme des rk au carr�)
//>       void operator()                  () 
//          calcule le r�sidu lin�aire obtenu apr�s ajustement
//>       int nbResidus                    () 
//          retourne le nombre de r�sidus de l'�chantillon
//>       bool estAjuste                   () 
//          indique si le mod�le a �t� ajust�
//>       int dimension                    () 
//          retourne la dimension de l'espace vectoriel d'ajustement
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class MoindreCarreLineaire
{

public :

  // constructeurs
  MoindreCarreLineaire ()
    : dimension_ (0), nbResidus_ (0), sommeRk2_ (0.0), vecSommeRkFk_ (0),
      matSommeFkFk_ (0), estAjuste_ (false), ai_ (0), errQuad_ (0.0)
  {}

  MoindreCarreLineaire (int dimension)
    : nbResidus_ (0), estAjuste_ (false), errQuad_ (0.0)
  { alloueTableaux (dimension); }

  // copie constructeur et affectation
  MoindreCarreLineaire (const MoindreCarreLineaire& m);
  MoindreCarreLineaire& operator = (const MoindreCarreLineaire& m);

  // destructeur
  ~MoindreCarreLineaire () { libereTableaux (); }

  // enregistrement de l'�chantillon de points de r�f�rences
  void ajouteResidu     (double rk, double fki [], double wk = 1.0);
  void oteResidu        (double rk, double fki [], double wk = 1.0);
  void oteTousResidus   ();
  int  nbResidus        () const { return nbResidus_; }

  // ajustement par combinaison lin�aire des fonctions de base
  void ajuste (double seuil = 1.0e-10)
    throw (CantorErreurs);

  bool estAjuste () const { return estAjuste_; }

  void coefficients (double ai []) const
    throw (CantorErreurs);

  double erreurQuadratique () const
    throw (CantorErreurs);

  void operator () (double *ptrFk, double fki []) const
    throw (CantorErreurs);

  // acc�s aux �l�ments internes
  int dimension         () const { return dimension_; }

private :

  int               dimension_;      // dimension du mod�le lin�aire

  // attributs de gestion de l'�chantillon de points du moindres carr�s
  int               nbResidus_;      // taille de l'�chantillon
  double            sommeRk2_;       // scalaire pour le calcul de l'erreur
  double           *vecSommeRkFk_;   // second membre des moindres carr�s
  double           *matSommeFkFk_;   // matrice des moindres carr�s

  // attributs de gestion de l'ajustement
  bool              estAjuste_;
  double           *ai_;
  double            errQuad_;

  void alloueTableaux (int dimension);
  void libereTableaux ();

};

#endif

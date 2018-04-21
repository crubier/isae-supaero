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
//>       Creneau.h
//
//$Resume
//       fichier d'en-t�te de la classe Creneau
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class Creneau              
//>       ostream& operator <<()     
//>       inline Creneau operator +()
//>       inline Creneau operator *()
//
//$Historique
//       $Log: Creneau.h,v $
//       Revision 1.20  2002/12/02 13:33:33  cantor
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.19  2002/09/03 15:20:22  cantor
//       surcharge de l'op�rateur '-', correction de 'throw' (FA15)
//
//       Revision 1.18  2001/06/12 12:50:50  cantor
//       utilisation du type bool pour les valeurs de retour des pr�dicats
//
//       Revision 1.17  2001/06/05 15:31:16  cantor
//       passage au m�canisme des exceptions pour la gestion des erreurs,
//       utilisation du type bool pour les pr�dicats
//
//       Revision 1.16  2000/10/24 16:22:18  cantor
//       modification des includes : suppression de .h dans le nom du fichier
//
//       Revision 1.15  2000/08/09 14:36:43  cantor
//       R�union de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.14.2.1  2000/03/30 15:36:08  cantor
//       ajout du copyright CNES
//
//       Revision 1.14  1999/08/05 09:55:57  cantor
//       modification r�sultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 1.13.2.1  1999/04/26 13:51:45  cantor
//       ajout de la m�thode decale
//
//       Revision 1.13  1998/07/29 11:47:05  cantor
//       �limination de float.h
//
//       Revision 1.12  1998/06/24 10:36:16  luc
//       modification du format de l'en-t�te
//       �limination de la variable statique RCS
//
//       Revision 1.11  1998/04/26 15:23:49  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.10  1998/04/06 20:08:16  luc
//       ajout de l'op�rateur *= entre cr�neaux, en s'appuyant sur l'op�rateur *
//
//       Revision 1.9  1998/01/22 10:39:27  luc
//       am�lioration de l'en-t�te de classe
//
//       Revision 1.8  1997/07/06 10:24:38  luc
//       ajout d'un en-t�te de fichier
//       remplacement des size_t par des int
//
//       Revision 1.7  1997/03/26 06:39:39  luc
//       changement des conventions de nommage
//       
//       Revision 1.6  1997/03/24 09:22:10  luc
//       passage de SCCS � RCS
//       
//       Revision 1.5  1996/07/16 10:27:54  luc
//       �limination de la d�pendance aux tools.h++ (Rogue Wave)
//       (les intervalles sont d�sormais conserv�s dans un tableau g�r� par l'instance)
//       
//       Revision 1.4  1994/12/12 15:14:34  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.3  1994/11/26 15:14:18  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.2  1994/08/11 14:56:00  mercator
//       elimination d'un qualificatif const excedentaire
//       
//       Revision 1.1  1994/07/27 14:57:00  luc
//       Initial revision
//
//$Version
//       $Id: Creneau.h,v 1.20 2002/12/02 13:33:33 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Creneau_h
#define __cantor_Creneau_h

#include <iostream>

#include "cantor/CantorErreurs.h"
#include "cantor/Intervalle.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Creneau
//$Resume
//       mod�lisation de r�union d'intervalles disjoints
//
//$Description
//       mod�lisation de r�union d'intervalles disjoints
//
//$Usage
//>     construction : 
//          � partir d'un intervalle, des bornes d'un intervalle
//>     utilisation  : 
//>       Creneau& operator =           () 
//          affectation
//>       double inf                    () 
//          retourne une copie de la borne inf du premier intervalle
//>       double sup                    () 
//          retourne une copie de la borne sup du dernier intervalle
//>       const Intervalle& operator [] () 
//          retourne une copie de l'intervalle d'indice i (indices
//          variant de 0 a n-1)
//>       bool vide                     () 
//          teste si le cr�neau est vide
//>       bool contient                 () 2 signatures - 
//          teste si le cr�neau contient un r�el ou un intervalle
//>       bool rencontre                () 
//          teste si le cr�neau rencontre un intervalle
//>       bool disjoint                 () 
//          teste si le cr�neau ne rencontre pas un intervalle
//>       void decale                   () 
//          d�cale tous les intervalles du cr�neau
//>       Creneau& operator +=          () 2 signatures - 
//          retourne une r�f�rence � l'instance apres l'avoir modifi�e
//          par r�union avec un intervalle ou un cr�neau
//>       Creneau& operator -=          () 2 signatures - 
//          retourne une r�f�rence � l'instance apres l'avoir modifi�e
//          par disjonction avec un intervalle ou un cr�neau
//>       Creneau& operator *=          () 2 signatures - 
//          retourne une r�f�rence � l'instance apres l'avoir modifi�e
//          par intersection avec un intervalle ou un cr�neau
//>       friend Creneau operator *     () 
//          retourne le Creneau intersection de l'instance et d'un
//          autre Creneau
//>       void nettoie                  () 
//          vide le creneau de ses intervalles
//>       int nombre                    () 
//          retourne une copie du nombre d'intervalles
//>       bool connexe                  () 
//          teste si le cr�neau est connexe
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Creneau
{ 
  public :

  // constructeurs
  Creneau ()
    : tailleTable_ (0), nbIntervalles_ (0), table_ (0)
  {}
  Creneau (const Intervalle& i);
  Creneau (const Intervalle& i1, const Intervalle& i2);
  Creneau (double a, double b);

  // copie constructeur et affectation
  Creneau (const Creneau& c);
  Creneau& operator = (const Creneau& c);

  // destructeur
  ~Creneau () { if (tailleTable_) delete [] table_; }

  // fonctions de gestion
  void        nettoie     ()     { nbIntervalles_ = 0; }

  // fonctions d'acc�s aux �l�ments canoniques
  double      inf         () const throw (CantorErreurs);
  double      sup         () const throw (CantorErreurs);
  int         nombre      () const { return nbIntervalles_; }
  const Intervalle& operator [] (int i) const throw (CantorErreurs);

  // fonctions de tests
  bool        connexe     ()      const { return nbIntervalles_ == 1; }
  bool        vide        ()      const;

  bool        contient    (double x)            const;
  bool        contient    (const Intervalle& i) const;
  bool        rencontre   (const Intervalle& i) const;
  bool        disjoint    (const Intervalle& i) const;

  // fonctions de modification
  void        decale      (double delta);

  // op�rations avec des intervalles ('+': r�union, '-': disjonction, '*': intersection)
  Creneau&    operator +=   (const Intervalle& i);
  Creneau&    operator -=   (const Intervalle& i);
  Creneau&    operator *=   (const Intervalle& i);

  // op�rations entre cr�neaux ('+': r�union, '-': disjonction, '*': intersection)
  Creneau&    operator +=   (const Creneau& c);
  Creneau&    operator -=   (const Creneau& c);
  Creneau&    operator *=   (const Creneau& c)
                            { *this = *this * c ; return *this; }

  friend Creneau operator * (const Creneau& c, const Creneau& c2);

private :

  int         tailleTable_;
  int         nbIntervalles_;
  Intervalle *table_;

  void etendTable ();

};

// les op�rations suivantes doivent �tre utilis�es avec pr�cautions
// elle peuvent �tre co�teuses en raison de la variable temporaire copi�e
// (la copie �tant faite au cours du passage de param�tres)
inline Creneau operator + (Creneau c, const Intervalle& i)
{ return c += i; }

inline Creneau operator - (Creneau c, const Intervalle& i)
{ return c -= i; }

inline Creneau operator * (Creneau c, const Intervalle& i)
{ return c *= i; }

inline Creneau operator + (Creneau c1, const Creneau& c2)
{ return c1 += c2; }

inline Creneau operator - (Creneau c1, const Creneau& c2)
{ return c1 -= c2; }

ostream& operator << (ostream& s, const Creneau& c);

#endif

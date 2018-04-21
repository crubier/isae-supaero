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
//>       Polynome.h
//
//$Resume
//       fichier d'en-t�te de la classe Polynome
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class Polynome                                    
//>       template <class T> ostream& operator <<()         
//>       template <class T> inline Polynome<T> operator +()
//>       template <class T> inline Polynome<T> operator -()
//>       template <class T> inline Polynome<T> operator *()
//
//$Historique
//       $Log: Polynome.h,v $
//       Revision 1.20  2003/02/04 15:31:49  cantor
//       DM-ID 18 Mise en conformit� avec la norme C++
//
//       Revision 1.19  2002/12/10 15:07:34  cantor
//       DM-ID 12 Ajout d'un destructeur pour pr�venir celui cr�� par le compilateur
//
//       Revision 1.18  2002/12/02 13:39:30  cantor
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.17  2001/06/05 15:28:41  cantor
//       passage au m�canisme des exceptions pour la gestion des erreurs
//
//       Revision 1.16  2000/10/24 16:22:18  cantor
//       modification des includes : suppression de .h dans le nom du fichier
//
//       Revision 1.15  2000/08/09 14:36:44  cantor
//       R�union de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.14.4.1  2000/03/30 15:36:10  cantor
//       ajout du copyright CNES
//
//       Revision 1.14  1998/07/29 11:49:39  cantor
//       �limination de float.h
//
//       Revision 1.13  1998/06/24 12:02:15  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.12  1998/04/26 15:24:01  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.11  1998/04/19 18:22:34  luc
//       �limination de la m�thode estValide
//
//       Revision 1.10  1998/01/22 10:41:36  luc
//       am�lioration de l'en-t�te de classe
//
//       Revision 1.9  1997/07/06 10:30:52  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 1.8  1997/04/03 19:36:26  luc
//       modification de commentaires
//       
//       Revision 1.7  1997/03/26 06:39:46  luc
//       changement des conventions de nommage
//       
//       Revision 1.6  1997/03/24 08:55:40  luc
//       s�paration des instructions du type "return p += q" en "p += q ; return p;"
//       pour �viter les probl�mes de variables temporaires sous Linux
//       passage de SCCS � RCS
//       
//       Revision 1.5  1996/07/16 10:36:12  luc
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       prise en compte du renommage de erreurs.h en cantor_erreurs.h
//       
//       Revision 1.4  1994/12/12 15:14:37  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.3  1994/11/26 15:15:15  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.2  1994/11/09 16:14:48  mercator
//       transformation de certains operateurs en operateurs membres
//       elimination de l'inclusion du source en fin de fichier
//       
//       Revision 1.1  1994/07/27 14:57:09  luc
//       Initial revision
//
//$Version
//       $Id: Polynome.h,v 1.20 2003/02/04 15:31:49 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Polynome_h
#define __cantor_Polynome_h

#include <iostream>

#ifdef HAVE_SSTREAM
#include <sstream>
#endif

#include "club/ClubErreurs.h"
#include "cantor/Util.h"
#include "cantor/CantorErreurs.h"

const int polynome_max_degre = 10;

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Polynome
//$Resume
//       mod�lisation de polyn�mes
//
//$Description
//       mod�lisation de polyn�mes
//
//$Usage
//>     construction : 
//          � partir du degr� et des cofficients, � partir des seuls
//          premiers coefficients (jusqu'au degr� 5), par copie
//>     utilisation  : 
//>       Polynome<T>& operator =  () 
//          affectation
//>       T coeff                  () 
//          retourne une copie du coefficient du mon�me dont le degr�
//          est fourni en argument
//>       T operator()             () 
//          retourne une copie de la valeur du polyn�me en x
//>       Polynome<T> operator()   () 
//          retourne la composition de l'instance avec un autre
//          polyn�me
//>       T derivee                () 
//          retourne une copie de la valeur de la d�riv�e du
//          polyn�me en x
//>       Polynome<T> derivee      () 
//          retourne une copie du polyn�me d�riv�e de l'instance
//>       Polynome<T> integrale    () 
//          retourne une copie du polyn�me int�grale de l'instance qui
//          prend a valeur y au point x (arguments par d�faut: y = 0,
//          x = 0)
//>       Polynome<T>& operator += () 
//          retourne une r�f�rence � l'instance apr�s l'avoir modifi�e
//          par addition d'un scalaire ou d'un polyn�me
//>       Polynome<T>& operator -= () 
//          retourne une r�f�rence � l'instance apr�s l'avoir modifi�e
//          par soustraction d'un scalaire ou d'un polyn�me
//>       Polynome<T>& operator *= () 
//          retourne une r�f�rence � l'instance apr�s l'avoir modifi�e
//          par multiplication par un scalaire ou un polyn�me
//>       Polynome<T> operator -   () 
//          retourne la diff�rence de l'instance et d'un scalaire ou
//          d'un polyn�me
//>       Polynome<T>& operator /= () 
//          retourne une r�f�rence � l'instance apr�s l'avoir modifi�e
//          par addition d'un polyn�me
//>       void zeros               () 
//          initialise l'entier point� par pn avec le nombre de z�ros
//          r�els du polyn�me, le tableau z avec les valeurs des
//          z�ros, et le tableau o avec l'ordre de multiplicit� des
//          z�ros. Tous les calculs sont faits par des m�thodes
//          analytiques directes.
//>       int degre                () 
//          retourne une copie du degr�
//>       Polynome<T> operator +   () 
//          retourne la somme de l'instance et d'un scalaire ou d'un
//          polyn�me
//>       Polynome<T> operator *   () 
//          retourne le produit de l'instance et d'un scalaire ou d'un
//          polyn�me
//>       Polynome<T> operator /   () 
//          retourne le quotient de l'instance et d'un kscalaire
//>       bool zerosCalculables     () 
//          indique si les z�ros sont calculables analytiquement
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

template <class T> class Polynome
{
  public :

  // constructeurs
  Polynome ()            : degre_ (-1) {}
  Polynome (int degre, const T coeff []) throw (CantorErreurs);

  Polynome (const T& a0)
    : degre_ (0)
  { coeff_ [0] = a0;
    ajusteDegre ();
  }

  Polynome (const T& a0, const T& a1)
    : degre_ (1)
  { coeff_ [0] = a0; coeff_ [1] = a1;
    ajusteDegre ();
  }

  Polynome (const T& a0, const T& a1, const T& a2)
    : degre_ (2)
  { coeff_ [0] = a0; coeff_ [1] = a1; coeff_ [2] = a2;
    ajusteDegre ();
  }

  Polynome (const T& a0, const T& a1, const T& a2,
            const T& a3)
    : degre_ (3)
  { coeff_ [0] = a0; coeff_ [1] = a1; coeff_ [2] = a2;
    coeff_ [3] = a3;
    ajusteDegre ();
  }

  Polynome (const T& a0, const T& a1, const T& a2,
            const T& a3, const T& a4)
    : degre_ (4)
  { coeff_ [0] = a0; coeff_ [1] = a1; coeff_ [2] = a2;
    coeff_ [3] = a3; coeff_ [4] = a4;
    ajusteDegre ();
  }

  Polynome (const T& a0, const T& a1, const T& a2,
            const T& a3, const T& a4, const T& a5)
    : degre_ (5)
  { coeff_ [0] = a0; coeff_ [1] = a1; coeff_ [2] = a2;
    coeff_ [3] = a3; coeff_ [4] = a4; coeff_ [5] = a5;
    ajusteDegre ();
  }

  // copie constructeur et affectation
  Polynome                 (const Polynome<T>& p);
  Polynome<T>& operator =  (const Polynome<T>& p);

  // fonctions d'acc�s aux �l�ments canoniques
  int         degre        ()                     const { return degre_; }
  T           coeff        (int i) const throw (CantorErreurs);

  // calcul de la valeur en x
  T           operator ()  (const T& x) const throw (CantorErreurs);

  // composition de polyn�mes
  Polynome<T> operator ()  (const Polynome<T>& x) const throw (CantorErreurs);

  // calcul de la d�riv�e en x
  T           derivee      (const T& x) const throw (CantorErreurs);

  // construction d'un polyn�me d�riv�e
  Polynome<T> derivee      () const throw (CantorErreurs);

  // construction d'un polyn�me int�grale
  Polynome<T> integrale    (const T& y = T (0.0), const T& x = T (0.0)) const
    throw (CantorErreurs);

  // op�rateurs sur les polyn�mes
  Polynome<T>& operator += (const Polynome<T>& p);
  Polynome<T>& operator -= (const Polynome<T>& p);
  Polynome<T>& operator *= (const Polynome<T>& p)
    throw (CantorErreurs);
  Polynome<T>  operator -  ()                     const;
  Polynome<T>  operator +  (const Polynome<T>& q) const
  { Polynome<T> p = *this; p += q; return p; }

  Polynome<T>  operator -  (const Polynome<T>& q) const
  { Polynome<T> p = *this; p -= q; return p; }

  Polynome<T>  operator *  (const Polynome<T>& q) const
    throw (CantorErreurs)
  { Polynome<T> p = *this; p *= q; return p; }


  Polynome<T>& operator += (const T& c);
  Polynome<T>& operator -= (const T& c);
  Polynome<T>& operator *= (const T& c);
  Polynome<T>& operator /= (const T& c);
  Polynome<T>  operator +  (const T& c)           const
  { Polynome<T> p = *this; p += c; return p; }

  Polynome<T>  operator -  (const T& c)           const
  { Polynome<T> p = *this; p -= c; return p; }

  Polynome<T>  operator *  (const T& c)           const
  { Polynome<T> p = *this; p *= c; return p; }

  Polynome<T>  operator /  (const T& c)           const
  { Polynome<T> p = *this; p /= c; return p; }


  // recherche des z�ros
  bool  zerosCalculables () const { return degre_ < 5; }
  void zeros (int* n, T z [], int o []) const throw (CantorErreurs);

  // destructeur
  ~Polynome () {}

private :

  int degre_;
  T   coeff_ [polynome_max_degre + 1];

  void affecter    (const Polynome<T>& p);
  void ajusteDegre ();

};

template <class T> ostream& operator << (ostream& s, const Polynome<T>& p);

template <class T> inline Polynome<T> operator + (const T& c, Polynome<T> p)
{ p += c; return p; }

template <class T> inline Polynome<T> operator - (const T& c, Polynome<T> p)
{ p -= c; p = -p; return p; }

template <class T> inline Polynome<T> operator * (const T& c, Polynome<T> p)
{ p *= c; return p; }


#endif

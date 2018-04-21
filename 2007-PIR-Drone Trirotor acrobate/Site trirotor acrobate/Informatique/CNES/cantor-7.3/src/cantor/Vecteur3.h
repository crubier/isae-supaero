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
//>       Vecteur3.h
//
//$Resume
//       fichier d'en-t�te de la classe Vecteur3
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class Vecteur3                                      
//>       template <class T> inline ostream& operator <<()    
//>       template <class T> inline Vecteur3<T> operator *()  
//>       template <class T> inline T angle()                 
//>       inline Vecteur3<T> vecteurOrthogonalNorme()         
//>       template <class T> inline Vecteur3<T> vecteurNorme()
//
//$Historique
//       $Log: Vecteur3.h,v $
//       Revision 1.22  2002/12/10 15:39:44  cantor
//       DM-ID 12 Ajout d'un destructeur pour pr�venir celui cr�� par le compilateur
//
//       Revision 1.21  2002/12/02 13:50:00  cantor
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.20  2001/06/05 15:18:10  cantor
//       passage au m�canisme des exceptions pour la gestion des erreurs
//
//       Revision 1.19  2000/10/24 16:22:19  cantor
//       modification des includes : suppression de .h dans le nom du fichier
//
//       Revision 1.18  2000/08/09 14:36:45  cantor
//       R�union de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.17.2.1  2000/03/30 15:36:12  cantor
//       ajout du copyright CNES
//
//       Revision 1.17  1999/06/28 14:47:02  cantor
//       modification de l'op�rateur externe * : l'argument Vecteur3<T> est
//       pass� par r�f�rence constante plut�t que par valeur
//
//       Revision 1.16  1998/07/29 11:50:58  cantor
//       �limination de float.h
//
//       Revision 1.15  1998/06/24 16:35:41  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.14  1998/04/26 15:34:36  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.13  1998/01/22 10:46:18  luc
//       am�lioration de l'en-t�te de classe
//
//       Revision 1.12  1997/07/06 10:37:17  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 1.11  1997/03/26 06:39:54  luc
//       changement des conventions de nommage
//       
//       Revision 1.10  1997/03/24 09:22:24  luc
//       passage de SCCS � RCS
//       
//       Revision 1.9  1996/07/16 12:03:37  luc
//       suppression de l'op�rateur == (il n'avait pas de raison d'�tre intrins�que,
//       il n'�tait pr�sent jusqu'ici qu'� cause des tools.h++)
//       
//       Revision 1.8  1996/05/29 17:38:13  luc
//       utilisation d'un fichier d'inclusion garantissant la d�finition de M_PI
//       m�me si la compilation a �t� faite avec l'option -ansi.
//       
//       Revision 1.7  1994/12/22 16:19:41  mercator
//       utilisation de retours de references constantes pour optimiser la vitesse
//       
//       Revision 1.6  1994/12/12 15:14:50  mercator
//       generalisation a toute la biliotheque de l'argument CantorErreurs* optionnel
//       
//       Revision 1.5  1994/11/26 15:16:18  mercator
//       remplacement du pragma ident par une variable statique
//       
//       Revision 1.4  1994/11/14 07:03:44  mercator
//       correction d'une erreur dans la fonction en ligne vecteurNorme
//       
//       Revision 1.3  1994/11/09 16:08:33  mercator
//       ajout de l'operateur de sortie
//       elimination de l'inclusion du source en fin de fichier
//       
//       Revision 1.2  1994/08/11 15:10:41  mercator
//       transformation de fonctions globales en fonctions membres
//       ou en fonctions sans template, pour pallier a un probleme temporaire
//       de compilateur (g++ 2.6.0)
//       
//       Revision 1.1  1994/07/27 14:57:20  luc
//       Initial revision
//
//$Version
//       $Id: Vecteur3.h,v 1.22 2002/12/10 15:39:44 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_Vecteur3_h
#define __cantor_Vecteur3_h

#include <iostream>
#include "cantor/MathPi.h"
#include "cantor/CantorErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Vecteur3
//
//$Resume
//       calculs vectoriels en dimension 3
//
//$Description
//       calculs vectoriels en dimension 3
//
//$Usage
//>     construction : 
//          � partir des coordonn�es polaires (alpha,delta), radians
//          � partir des coordonn�es cart�siennes (x, y, z)
//>     utilisation  : 
//>       Vecteur3<T>& operator =  () 
//          affectation
//>       int estNorme             () 
//          indique si le vecteur est norm�
//>       int estNul               () 
//          indique si le vecteur est nul
//>       void normalise           () 
//          normalise le vecteur
//>       void orthonormalise      () 
//          transforme l'instance en un vecteur norm� orthogonal � ce
//          qu'il �tait
//>       T angleAvecVecteur       () 
//          retourne l'angle entre l'instance et un autre vecteur
//>       Vecteur3<T> orthogonal   () 
//          retourne un vecteur norm� orthogonal � l'instance
//>       Vecteur3<T>& operator ^= () 
//          remplace l'instance par son produit vectoriel avec un
//          vecteur
//>       const T& x               () 
//          retourne l'abscisse
//>       const T& y               () 
//          retourne l'ordonn�e
//>       const T& z               () 
//          retourne la cote
//>       T norme                  () 
//          retourne la norme
//>       T alpha                  () 
//          retourne l'azimut
//>       T delta                  () 
//          retourne l'�l�vation
//>       Vecteur3<T>& operator -= () 
//          retourne une r�f�rence sur l'instance apr�s lui avoir
//          soustrait un autre vecteur
//>       Vecteur3<T>& operator += () 
//          retourne une r�f�rence sur l'instance apr�s lui avoir
//          ajout� un autre vecteur
//>       Vecteur3<T> operator -   () 
//          soustrait un vecteur � l'instance
//>       Vecteur3<T> operator +   () 
//          ajoute un vecteur � l'instance
//>       Vecteur3<T> operator ^   () 
//          calcule le produit vectoriel de l'instance et d'un autre
//          vecteur
//>       T operator |             () 
//          calcule le produit scalaire de l'instance et d'un autre
//          vecteur
//>       Vecteur3<T>& operator *= () 
//          retourne une r�f�rence sur l'instance apr�s l'avoir
//          multipli�e par un scalaire
//>       Vecteur3<T>& operator /= () 
//          retourne une r�f�rence sur l'instance apr�s l'avoir
//          divis�e par un scalaire
//>       Vecteur3<T> operator *   () 
//          calcule le produit de l'instance par un scalaire
//>       Vecteur3<T> operator /   () 
//          calcule le quotient de l'instance par un scalaire
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

template <class T> class Vecteur3
{

public :

  // constructeurs
  Vecteur3   ()                 : x_ (0), y_ (0), z_ (0) {}
  Vecteur3   (T alpha, T delta) { z_ = cos (delta);
                                  x_ = cos (alpha) * z_;
                                  y_ = sin (alpha) * z_;
                                  z_ = sin (delta);
                                 }
  Vecteur3   (T x, T y, T z)    : x_ (x), y_ (y), z_ (z) {}

  // copie-constructeur et affectation
  Vecteur3   (const Vecteur3<T>& u) : x_ (u.x_), y_ (u.y_), z_ (u.z_) {}

  Vecteur3<T>& operator = (const Vecteur3<T>& u);

  // fonctions d'acc�s aux coordonn�es
  const T&     x              () const { return x_; }
  const T&     y              () const { return y_; }
  const T&     z              () const { return z_; }
  T            norme          () const { return sqrt (x_*x_ + y_*y_ + z_*z_); }
  T            alpha          () const { return atan2 (y_, x_); }
  T            delta          () const { return asin (z_ / norme ()); }

  // tests du vecteur courant
  int          estNorme       () const;
  int          estNul         () const;

  // transformations du vecteur courant
  void         normalise      () throw (CantorErreurs);
  void         orthonormalise () throw (CantorErreurs);

  T            angleAvecVecteur (const Vecteur3<T>& u) const;

  // creation d'un vecteur norm� orthogonal au vecteur courant
  // (il existe une infinit� d'autres solutions)
  Vecteur3<T>  orthogonal     () const throw (CantorErreurs);

  // op�rations arithm�tiques entre Vecteur3<T>
  Vecteur3<T>& operator -=    (const Vecteur3<T>& u)
  { x_ -= u.x_; y_ -= u.y_; z_ -= u.z_; return *this; }

  Vecteur3<T>& operator +=    (const Vecteur3<T>& u)
  { x_ += u.x_; y_ += u.y_; z_ += u.z_; return *this; }

  Vecteur3<T>  operator -     () const
  { return Vecteur3<T> (-x_, -y_, -z_); }

  Vecteur3<T>  operator -     (const Vecteur3<T>& v) const
  { Vecteur3<T> u = *this; return u -= v; }

  Vecteur3<T>  operator +     (const Vecteur3<T>& v) const
  { Vecteur3<T> u = *this; return u += v; }

  // produit vectoriel
  Vecteur3<T>& operator ^=    (const Vecteur3<T>& u);

  Vecteur3<T>  operator ^     (const Vecteur3<T>& v) const
  { Vecteur3<T> u = *this; return u ^= v; }

  // produit scalaire
  T            operator |     (const Vecteur3<T>& v) const
  { return x_ * v.x_ + y_ * v.y_ + z_ * v.z_; }

  // op�rations arithm�tiques avec le patron T
  Vecteur3<T>& operator *=    (const T& t)
  { x_ *= t; y_ *= t; z_ *= t; return *this; }

  Vecteur3<T>& operator /=    (const T& t)
  { x_ /= t; y_ /= t; z_ /= t; return *this; }

  Vecteur3<T>  operator *     (const T& t)           const
  { Vecteur3<T> u = *this; return u *= t; }

  Vecteur3<T>  operator /     (const T& t)           const
  { Vecteur3<T> u = *this; return u /= t; }

  // destructeur
  ~Vecteur3 () {}

private :

  T x_;
  T y_;
  T z_;

};

// op�rateur de sortie
template <class T> inline ostream& operator << (ostream& s,
                                                const Vecteur3<T>& u)
{ return s << '{' << u.x () << ' ' << u.y () << ' ' << u.z () << '}'; }

// multiplication du patron T par un Vecteur3<T>
template <class T> inline Vecteur3<T> operator *  (const T& t, 
                                                   const Vecteur3<T>& u)
{ return (u * t); }


// les fonctions suivantes sont une alternative permettant d'�crire
// xxx (u, v)  au lieu de u.xxx (v)
// le choix d'une interface ou de l'autre est une question de go�t ...
template <class T> inline T angle (const Vecteur3<T>& u,
                                   const Vecteur3<T>& v)
{ return u.angleAvecVecteur (v); }

template <class T>
inline Vecteur3<T> vecteurOrthogonalNorme (const Vecteur3<T>& u)
  throw (CantorErreurs)
{ return u.orthogonal (); }

// attention: passage par valeur, u est modifi� dans la fonction
template <class T> inline Vecteur3<T> vecteurNorme (Vecteur3<T> u)
  throw (CantorErreurs)
{ u.normalise (); return u; }


#endif

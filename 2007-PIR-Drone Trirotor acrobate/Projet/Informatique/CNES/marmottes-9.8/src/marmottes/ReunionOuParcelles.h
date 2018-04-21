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
//>       ReunionOuParcelles.h
//
//$Resume
//       fichier d'en-t�te de la classe ReunionOuParcelles
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class ReunionOuParcelles
//
//$Historique
//       $Log: ReunionOuParcelles.h,v $
//       Revision 1.13  2002/12/11 17:10:17  marmottes
//       DM-ID 12 Ajout d'un constructeur par d�faut (prot�g�) pour pr�venir celui construit par le compilateur.
//
//       Revision 1.12  2002/04/17 16:15:32  marmottes
//       Corrections de throw
//
//       Revision 1.11  2002/01/17 09:38:03  marmottes
//       correction de sp�cifications throw (FA 0003)
//
//       Revision 1.10  2001/06/22 07:03:37  luc
//       utilisation du type bool pour les pr�dicats
//
//       Revision 1.9  2001/04/04 12:19:58  luc
//       ajout de la m�thode ecartFrontiere
//
//       Revision 1.8  2000/11/13 09:02:33  luc
//       remplacement de la classe Champ par la classe Field
//
//       Revision 1.7.2.1  2000/07/07 11:26:45  luc
//       remplacement de TypeFoncConstChamp par Champ::TypeFoncConstChamp
//       dans les signatures des diff�rentes m�thodes applique
//
//       Revision 1.7  2000/03/30 17:01:23  luc
//       ajout du copyright CNES
//
//       Revision 1.6  1999/11/02 07:19:22  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.5  1998/06/25 06:07:07  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.4  1998/06/09 20:16:18  luc
//       suppression d'une directive de d�rivation virtual inutile
//
//       Revision 1.3  1998/04/26 18:25:23  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.2  1998/02/04 08:39:56  luc
//       mise en place d'un en-t�te de classe au format AMIGAU
//
//       Revision 1.1  1997/08/20 09:48:46  luc
//       Initial revision
//
//$Version
//       $Id: ReunionOuParcelles.h,v 1.13 2002/12/11 17:10:17 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_ReunionOuParcelles_h
#define __marmottes_ReunionOuParcelles_h

#include "marmottes/Parcelle.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ReunionOuParcelles
//
//$Resume
//       mod�lisation de r�unions de parcelles sur la sph�re unit�
//
//$Description
//       mod�lisation de la r�union de deux parcelles
//       sur la sph�re unit�, de fa�on � voir un horizon d�s qu'il
//       est visible dans au moins l'une des deux parcelles.
//
//$Usage
//>     construction : 
//          � partir de deux parcelles
//>     utilisation  : 
//>       virtual Parcelle* copie       () 
//          retourne une copie de la parcelle allou�e en m�moire
//>       virtual bool inclus           () 
//          teste si un vecteur est dans la parcelle
//>       virtual double ecartFrontiere () 
//          calcule la distance d'un point � la fronti�re
//>       virtual bool visible          () 
//          teste si un c�ne est visible � travers la parcelle
//>       virtual Secteurs visible      () 
//          filtre les parties visibles de secteurs � traver la parcelle
//>       virtual void appliqueRotation () 
//          remplace l'instance par son image � travers une rotation
//>       virtual void integreRotation  () 
//          remplace l'instance par la train�e qu'elle laisse lorsqu'on
//          la d�place par rotation
//>       virtual void appliqueMarge    () 
//          d�forme l'instance par ajout d'une marge
//          (soustraction si m < 0)
//>       virtual void applique         () 
//          applique la fonction f � tous les champs de la parcelle, en
//          lui passant le pointeur anonyme d
//>       virtual void rechercheChamp   () 
//          recherche dans la structure r�cursive un champ diff�rent de
//          celui dont l'adresse est fournie
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class ReunionOuParcelles : public Parcelle
{

public :

  // constructeurs
  ReunionOuParcelles  (Parcelle* p1, Parcelle* p2)
    : p1_ (p1), p2_ (p2)
  {}
  virtual Parcelle* copie        ()                                 const;

  // destructeur
  ~ReunionOuParcelles () { if (p1_) delete p1_; if (p2_) delete p2_; }

  // fonctions de test
  virtual bool     inclus         (const VecDBL& u)   const;
  virtual double   ecartFrontiere (const VecDBL& u)   const;
  virtual bool     visible        (const Cone& c)     const
    throw (CantorErreurs);
  virtual Secteurs visible        (const Secteurs& s) const
    throw (CantorErreurs);

  // fonctions de modification de l'instance
  virtual void appliqueRotation  (const RotDBL& r);
  virtual void integreRotation   (const VecDBL& axe, double angle)
    throw (CantorErreurs, MarmottesErreurs);
  virtual void appliqueMarge     (double m)
    throw (CantorErreurs, MarmottesErreurs);
  virtual void applique          (Field::TypeFuncConstField *f, void *d) const;
  virtual void applique          (Field::TypeFuncField      *f, void *d);

  // fonctions de parcours de la fronti�re d'un champ
  virtual void rechercheChamp (Field **adressePtr);

private:

  // constructeur par defaut : ne doit JAMAIS �tre utilis�
  ReunionOuParcelles () {}

  Parcelle* p1_;
  Parcelle* p2_;

  // la copie n'est autoris�e que par pointeur et allocation (m�thode copie ())
  // le constructeur par copie et l'affectation sont donc priv�s
  ReunionOuParcelles (const ReunionOuParcelles& p) {}
  ReunionOuParcelles& operator = (const ReunionOuParcelles& p)
  { return *this; }

};

#endif

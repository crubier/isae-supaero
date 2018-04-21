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
//>       ParcelleElementaire.h
//
//$Resume
//       fichier d'en-t�te de la classe ParcelleElementaire
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class ParcelleElementaire
//
//$Historique
//       $Log: ParcelleElementaire.h,v $
//       Revision 1.13  2002/12/11 17:08:23  marmottes
//       DM-ID 12 Ajout d'un constructeur par d�faut (prot�g�) pour pr�venir celui construit par le compilateur.
//
//       Revision 1.12  2002/04/17 16:14:59  marmottes
//       Corrections de throw
//
//       Revision 1.11  2002/01/17 09:38:03  marmottes
//       correction de sp�cifications throw (FA 0003)
//
//       Revision 1.10  2001/06/22 07:06:36  luc
//       utilisation du type bool pour les pr�dicats
//       utilisation d'un axe et d'un angle pour sp�cifier l'int�gration le
//       long d'une rotation
//
//       Revision 1.9  2001/04/04 12:19:58  luc
//       ajout de la m�thode ecartFrontiere
//
//       Revision 1.8  2000/11/13 09:02:05  luc
//       remplacement de la classe Champ par la classe Field
//
//       Revision 1.7.2.1  2000/07/07 11:26:46  luc
//       remplacement de TypeFoncConstChamp par Champ::TypeFoncConstChamp
//       dans les signatures des diff�rentes m�thodes applique
//
//       Revision 1.7  2000/03/30 17:01:23  luc
//       ajout du copyright CNES
//
//       Revision 1.6  1999/11/02 07:19:21  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.5  1998/06/25 06:05:40  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.4  1998/06/09 20:15:40  luc
//       suppression d'une directive de d�rivation virtual inutile
//
//       Revision 1.3  1998/04/26 18:25:16  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.2  1998/02/04 08:37:53  luc
//       mise en place d'un en-t�te de classe au format AMIGAU
//
//       Revision 1.1  1997/08/20 09:37:47  luc
//       Initial revision
//
//$Version
//       $Id: ParcelleElementaire.h,v 1.13 2002/12/11 17:08:23 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_ParcelleElementaire_h
#define __marmottes_ParcelleElementaire_h

#include "marmottes/Parcelle.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ParcelleElementaire
//
//$Resume
//       mod�lisation de parcelles simples sur la sph�re unit�
//
//$Description
//       mod�lisation de la parcelle la plus simple sur la sph�re
//       unit� : un champ sans comportement particulier au
//       regard des visibilit�s d'horizon
//
//$Usage
//>     construction : 
//          � partir d'un champ de la sph�re unit�
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

class ParcelleElementaire : public Parcelle
{

public:

  // constructeurs
  ParcelleElementaire  (const Field& f) : f_ (f) {}
  virtual Parcelle* copie        ()                                 const;

  // destructeur
 ~ParcelleElementaire  () {}

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

  // constructeur par d�faut : il ne doit JAMAIS �tre appell�
  // car il n'y a pas de sens a construire une parcelle
  // sans arguments
  ParcelleElementaire () {}
  
  // la copie n'est autoris�e que par pointeur et allocation (m�thode copie ())
  // le constructeur par copie et l'affectation sont donc priv�s
  ParcelleElementaire (const ParcelleElementaire& p) {}
  ParcelleElementaire& operator = (const ParcelleElementaire& p)
  { return *this; }

  Field f_;

};

#endif

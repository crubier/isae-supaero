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
//>       Parcelle.h
//
//$Resume
//       fichier d'en-t�te de la classe Parcelle
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class Parcelle
//
//$Historique
//       $Log: Parcelle.h,v $
//       Revision 2.15  2002/04/17 16:14:45  marmottes
//       Corrections de throw
//
//       Revision 2.14  2002/01/17 09:38:03  marmottes
//       correction de sp�cifications throw (FA 0003)
//
//       Revision 2.13  2001/06/22 07:06:17  luc
//       utilisation du type bool pour les pr�dicats
//       utilisation d'un axe et d'un angle pour sp�cifier l'int�gration le
//       long d'une rotation
//
//       Revision 2.12  2001/06/06 07:48:50  luc
//       prise en compte du d�placement de la classe Field vers Cantor
//
//       Revision 2.11  2001/04/04 12:19:58  luc
//       ajout de la m�thode ecartFrontiere
//
//       Revision 2.10  2000/11/13 09:01:31  luc
//       remplacement de la classe Champ par la classe Field,
//       modification de la signature de la m�thode pointSuivant
//
//       Revision 2.9.2.1  2000/07/07 11:26:45  luc
//       remplacement de TypeFoncConstChamp par Champ::TypeFoncConstChamp
//       dans les signatures des diff�rentes m�thodes applique
//
//       Revision 2.9  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 2.8  1999/11/02 07:19:21  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 2.7  1998/06/25 06:05:23  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 2.6  1998/04/26 20:12:30  luc
//       d�placement de Champ et Secteurs vers la biblioth�que marmottes
//
//       Revision 2.5  1998/04/26 18:25:15  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.4  1998/02/04 08:36:22  luc
//       mise en place d'un en-t�te de classe au format AMIGAU
//
//       Revision 2.3  1997/08/20 09:37:36  luc
//       ajout d'un en-t�te de fichier
//       r�organisation du code � raison d'une seule classe par fichier
//
//       Revision 2.2  1997/04/27 19:33:28  luc
//       inversion des codes de retour
//       changement des r�gles de nommage
//       passage de SCCS � RCS
//       
//       Revision 2.1  1996/07/31 17:17:55  luc
//       refonte compl�te pour remplacer les Connexes par des Mosa�ques
//       
//       Revision 1.1  1994/12/23 11:00:08  luc
//       Initial revision
//
//$Version
//       $Id: Parcelle.h,v 2.15 2002/04/17 16:14:45 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_Parcelle_h
#define __marmottes_Parcelle_h

#include "cantor/DeclDBL.h"
#include "cantor/Cone.h"
#include "cantor/Field.h"

#include "marmottes/MarmottesErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Parcelle
//$Resume
//       classe abstraite de mod�lisation de parcelles sur la sph�re unit�
//
//$Description
//       mod�lisation de parcelles sur la sph�re unit�, avec une notion
//       logique par dessus la notion g�om�trique de la classe Champ
//       de la biblioth�que CANTOR : la visibilit� d'un horizon (la terre)
//       s'exprime sous forme de combinaisons logiques de la visibilit�
//       dans des parcelles (ou des champs) sous-jacents.
//
//$Usage
//>     construction : 
//          sans objet (classe abstraite)
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
//>       void initParcours             () 
//          initialise le parcours de la frontiere de la parcelle avec
//          une tol�rance donn�e
//>       bool pointSuivant             () 
//          calcule le point suivant dans le parcours de la fronti�re
//          de la parcelle, et retourne un indicateur de validit� et un
//          indicateur de dernier point pour les parcelles �l�mentaires
//>       void arreteParcours           () 
//          arr�te le parcours de la fronti�re de la parcelle
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Parcelle
{

public :

  // constructeurs
  Parcelle () : courant_ (0) {}
  virtual Parcelle* copie () const = 0;

  // destructeur
  virtual ~Parcelle () { arreteParcours (); }

  // fonctions de test
  virtual bool     inclus         (const VecDBL& u)   const = 0;
  virtual double   ecartFrontiere (const VecDBL& u)   const = 0;
  virtual bool     visible        (const Cone& c)     const
    throw (CantorErreurs) = 0;
  virtual Secteurs visible        (const Secteurs& s) const
    throw (CantorErreurs) = 0;

  // fonctions de modification de l'instance
  virtual void appliqueRotation  (const RotDBL& r) = 0;
  virtual void integreRotation   (const VecDBL& axe, double angle)
    throw (CantorErreurs, MarmottesErreurs) = 0;
  virtual void appliqueMarge     (double m)
    throw (CantorErreurs, MarmottesErreurs) = 0;
  virtual void applique          (Field::TypeFuncConstField *f,
                                  void *d) const = 0;
  virtual void applique          (Field::TypeFuncField      *f,
                                  void *d) = 0;

  // fonctions de parcours de la fronti�re d'un champ
  virtual void rechercheChamp    (Field **adressePtr) = 0;
  void         initParcours      (double tolerance = 1.0e-4);
  bool         pointSuivant      (VecDBL* u, bool* dernier);
  void         arreteParcours    ();

private:

  Field  *courant_;
  double  tolerance_;

  bool champSuivant ();

  // la copie n'est autoris�e que par pointeur et allocation (m�thode copie ())
  // le constructeur par copie et l'affectation sont donc priv�s
  Parcelle (const Parcelle& p) {}
  Parcelle& operator = (const Parcelle& p) { return *this; }

};

#endif

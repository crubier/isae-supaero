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
//>       Modele.h
//
//$Resume
//       fichier d'en-t�te de la classe Modele
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class Modele
//
//$Historique
//       $Log: Modele.h,v $
//       Revision 1.12  2002/12/02 17:03:08  marmottes
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.11  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 1.10  1999/11/02 07:19:21  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.9  1999/07/29 12:15:17  filaire
//       Modification de la signature de la fonction prendConsignesEnCompte
//
//       Revision 1.9  1999/07/02 07:03:07  geraldine
//       modification de la signature de prendConsignesEnCompte
//       utilisation des exceptions
//
//       Revision 1.8  1998/06/25 06:03:07  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.7  1998/04/26 20:11:56  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.6  1998/02/04 09:20:54  luc
//       ajout d'un destructeur virtuel
//
//       Revision 1.5  1998/02/04 08:26:31  luc
//       mise en place d'un en-t�te de classe au format AMIGAU
//
//       Revision 1.4  1997/08/20 09:35:36  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 1.3  1997/04/27 19:33:11  luc
//       inversion des codes de retour
//       changement des r�gles de nommage
//       passage de SCCS � RCS
//       
//       Revision 1.2  1995/01/27 16:59:37  mercator
//       propagation du spin dans tous les calculs depuis la modelisation
//       jusqu'a la sauvegarde de la solution finale dans l'etat
//       
//       Revision 1.1  1994/12/23 11:00:06  luc
//       Initial revision
//
//$Version
//       $Id: Modele.h,v 1.12 2002/12/02 17:03:08 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_Modele_h
#define __marmottes_Modele_h

#include "cantor/DeclVD1.h"

#include "marmottes/Senseur.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Modele
//
//$Resume
//       classe abstraite d'un mod�le d'attitude � un degr� de libert�
//
//$Description
//       mod�lisation de fonction d'attitude � un degr� de libert�
//       respectant deux consignes identiques.
//
//$Usage
//>     construction : 
//         sans objet (classe abstraite)
//>     utilisation  : 
//>       virtual void prendConsignesEnCompte() 
//          initialise le mod�le � partir des consignes courantes des
//          senseurs concern�s
//>       virtual int familles               () 
//          retourne le nombre de familles d'attitude disjointes mod�lis�es
//>       virtual void attitude              () 
//          retourne l'attitude et le spin mod�lis�s pour une famille
//          et une valeur du degr� de libert� donn�es
//>       Modele& operator =                 () 
//          affectation
//>       const Senseur* senseur1            () 
//          retourne un pointeur sur le premier senseur du mod�le
//>       const Senseur* senseur2            () 
//          retourne un pointeur sur le second senseur du mod�le
//>       void miseAJourSenseurs             () 
//          modifie les senseurs du mod�le
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class Modele
{

  public :

  // constructeurs
  Modele () : senseur1_ (0), senseur2_ (0) {}
  Modele (const Modele& m) : senseur1_ (m.senseur1_), senseur2_ (m.senseur2_)
  {}
  Modele& operator = (const Modele& m)
  { if (&m != this)
    { senseur1_ = m.senseur1_; senseur2_ = m.senseur2_; }
    return *this;
  }

  virtual ~Modele () {}

  // fonctions d'acc�s aux �l�ments internes
  const Senseur* senseur1 () const { return senseur1_; }
  const Senseur* senseur2 () const { return senseur2_; }

  // fonctions de mise � jour du mod�le
  void           miseAJourSenseurs (Senseur* s1, Senseur* s2)
                                   { senseur1_ = s1; senseur2_ = s2; }
  virtual void   prendConsignesEnCompte () = 0;

  // fonctions de mod�lisation d'attitude
  virtual int    familles () const = 0;
  virtual void   attitude (const Etat& etatPrecedent, double date,
                           const ValeurDerivee1& t, int famille,
                           RotVD1* ptrAttitude, VecVD1* ptrSpin) const = 0;
private :

  Senseur* senseur1_;
  Senseur* senseur2_;


};

#endif

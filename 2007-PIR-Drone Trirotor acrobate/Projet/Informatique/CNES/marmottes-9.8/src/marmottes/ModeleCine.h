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
//>       ModeleCine.h
//
//$Resume
//       fichier d'en-t�te de la classe ModeleCine
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class ModeleCine
//
//$Historique
//       $Log: ModeleCine.h,v $
//       Revision 1.15  2002/12/02 17:03:26  marmottes
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.14  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 1.13  1999/11/02 07:19:21  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.12  1999/08/06 13:32:17  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 1.11  1999/07/29 12:15:17  filaire
//       Modification de la signature de la fonction prendConsignesEnCompte
//
//       Revision 1.11  1999/07/02 07:29:08  geraldine
//       modification de la signature de prendConsignesEnCompte
//       utilisation des exceptions
//
//       Revision 1.10  1998/06/25 06:03:33  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.9  1998/04/26 18:25:08  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.8  1998/02/19 16:19:25  luc
//       d�placement d'un constructeur inline dans le .cc
//       pour contourner un probl�me d'optimiseur avec g++ 2.8.0
//
//       Revision 1.7  1998/02/04 09:21:14  luc
//       ajout d'un destructeur virtuel
//
//       Revision 1.6  1998/02/04 08:30:06  luc
//       mise en place d'un en-t�te de classe au format AMIGAU
//
//       Revision 1.5  1997/08/20 09:35:51  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 1.4  1997/04/27 19:33:16  luc
//       inversion des codes de retour
//       changement des r�gles de nommage
//       passage de SCCS � RCS
//       
//       Revision 1.3  1996/07/31 18:11:03  luc
//       prise en compte du renommage de erreurs.h en marmottes_erreurs.h
//       
//       Revision 1.2  1995/01/27 16:59:39  mercator
//       propagation du spin dans tous les calculs depuis la modelisation
//       jusqu'a la sauvegarde de la solution finale dans l'etat
//       
//       Revision 1.1  1994/12/23 11:00:07  luc
//       Initial revision
//
//$Version
//       $Id: ModeleCine.h,v 1.15 2002/12/02 17:03:26 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_ModeleCine_h
#define __marmottes_ModeleCine_h

#include "cantor/DeclVD1.h"

#include "marmottes/Modele.h"
#include "marmottes/MarmottesErreurs.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ModeleCine
//
//$Resume
//       mod�le d'attitude pour deux consignes cin�matiques
//
//$Description
//       mod�lisation de fonction d'attitude a un degr� de libert�
//       respectant deux consignes cin�matiques
//
//$Usage
//>     construction : 
//          sans argument, par copie
//>     utilisation  : 
//>       ModeleCine& operator =             () 
//          affectation
//>       int miseAJourOmegaMax              () 
//          met � jour le param�tre de r�glage omegaMax de la mod�lisation
//>       virtual void prendConsignesEnCompte() 
//          initialise le mod�le � partir des consignes courantes des
//          senseurs concern�s
//>       virtual void attitude              () 
//          retourne l'attitude et le spin mod�lis�s pour une famille
//          et une valeur du degr� de libert� donn�es
//>       virtual int familles               () 
//          retourne le nombre de familles d'attitude disjointes mod�lis�es
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class ModeleCine : public Modele
{ 

  public :

  // constructeur
  ModeleCine ();
  ModeleCine (const ModeleCine& m)
   : Modele (m), u_ (m.u_), v_ (m.v_),
     thetaMax_ (m.thetaMax_), omegaMax_ (m.omegaMax_)
  {}
  ModeleCine& operator = (const ModeleCine& m);

  virtual ~ModeleCine () {}

  void           miseAJourOmegaMax (double omega)
    throw (MarmottesErreurs);

  virtual void   prendConsignesEnCompte () 
    throw (MarmottesErreurs);

  // fonctions de mod�lisation d'attitude
  virtual int    familles () const { return 1; }
  virtual void   attitude (const Etat& etatPrecedent, double date,
                           const ValeurDerivee1& t, int famille,
                           RotVD1* ptrAtt, VecVD1* ptrSpin) const;

  private :

  VecVD1 u_;
  VecVD1 v_;
  double thetaMax_;
  double omegaMax_;

};


#endif

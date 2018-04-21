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
//>       ArcIterateur.h
//
//$Resume
//       fichier d'en-t�te de la classe ArcIterateur
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class ArcIterateur
//
//$Historique
//       $Log: ArcIterateur.h,v $
//       Revision 1.8  2002/12/10 14:52:05  cantor
//       DM-ID 12 Ajout d'un destructeur et d'un constructeur pour pr�venir ceux cr�es par le compilateur
//
//       Revision 1.7  2002/12/02 13:32:19  cantor
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.6  2000/08/09 14:36:43  cantor
//       R�union de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.5.4.1  2000/03/30 15:36:08  cantor
//       ajout du copyright CNES
//
//       Revision 1.5  1998/06/24 16:43:54  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.4  1998/04/26 15:23:41  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.3  1998/04/18 19:08:08  luc
//       �limination de la m�thode estValide
//
//       Revision 1.2  1998/01/22 10:38:23  luc
//       am�lioration de l'en-t�te de classe
//
//       Revision 1.1  1997/07/08 10:14:34  luc
//       Initial revision
//
//
//$Version
//       $Id: ArcIterateur.h,v 1.8 2002/12/10 14:52:05 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __cantor_ArcIterateur_h
#define __cantor_ArcIterateur_h

#include "cantor/Arc.h"


///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ArcIterateur
//$Resume
//       it�rateur sur la classe Arc
//
//$Description
//       it�rateur sur un arc de cercle trac� sur la sph�re
//       (parcours de l'arc point � point)
//
//$Usage
//>     construction : 
//          � partir d'une r�f�rence � un arc et d'une tol�rance ou
//          par copie (l'etat est ind�fini juste apr�s la
//          construction, il faut appeler l'op�rateur ())
//>     utilisation  : 
//>       ArcIterateur& operator = () 
//          affectation
//>       VecDBL point             () 
//          retourne une copie du point courant (si on n'a pas encore
//          appel� (), le point de d�but est renvoy�, et sera
//          EGALEMENT renvoy� apr�s le premier appel, si on a fini le
//          parcours, le point de fin est renvoy�, alors qu'il a DEJA
//          �t� envoy� par les appels pr�c�dents).
//>       int nbSegments           () 
//          retourne le nombre de segments que l'it�rateur d�crit.
//>       int nbPoints             () 
//          retourne le nombre de points que l'it�rateur d�crit.
//>       void reinitialise        () 
//          remet l'it�rateur en d�but d'arc.
//>       int suivant              () 
//          d�place le pointeur courant et retourne un indicateur de
//          validit�.
//>       int operator()           () 
//          d�place le pointeur courant et retourne un indicateur de
//          validit�.
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class ArcIterateur
{ 
  public :

  // constructeurs
  ArcIterateur (const Arc& a, double tolerance = 1.0e-4);
  ArcIterateur (const ArcIterateur& i)
    : arc_ (i.arc_), pas_ (i.pas_), indice_ (i.indice_),
      segments_ (i.segments_)
  {}

  ArcIterateur& operator = (const ArcIterateur& i);

  // destructeur
  ~ArcIterateur () {}

  // fonctions d'acc�s
  int    nbSegments   () const { return segments_;     }
  int    nbPoints     () const { return segments_ + 1; }

  // fonctions d'it�ration (on peut it�rer segments_+1 fois)
  void   reinitialise () { indice_ = 0;                   }
  int    suivant      () { return indice_++ <= segments_; }
  int    operator ()  () { return suivant ();             }

  // calcul du point courant
  VecDBL point        () const;

  protected :

  // constructeur par d�faut
  ArcIterateur () {}

  private :

  const Arc*        arc_;
  double            pas_;
  int               indice_;
  int               segments_;

};

#endif

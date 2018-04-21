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
//>       SectionDoree.cpp
//
//$Resume
//       fichier d'implantation de l'algorithme de la section dor�e
//
//$Description
//       Module de d�finition de la fonction
//
//$Contenu
//>       void SectionDoree()            
//
//$Historique
//       $Log: SectionDoree.cpp,v $
//       Revision 1.7  2003/02/04 09:30:17  cantor
//       DM-ID 17 Mise � jour du nom du fichier dans le bandeau suite � la modification des extensions.
//
//       Revision 1.6  2000/08/09 14:36:42  cantor
//       R�union de la branche 5.2.2 dans le tronc principal.
//
//       Revision 1.5.2.1  2000/03/30 15:36:07  cantor
//       ajout du copyright CNES
//
//       Revision 1.5  1999/08/05 09:55:08  cantor
//       modification r�sultant du merge entre les versions
//       release-5-0-1 et pre-5-2
//
//       Revision 1.4.2.1  1999/04/26 09:41:10  cantor
//       remplacement de abs par fabs
//
//       Revision 1.4  1998/07/29 11:41:51  cantor
//       �limination de float.h
//
//       Revision 1.3  1998/06/24 10:11:26  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.2  1998/06/22 08:26:03  luc
//       correction de valeurs par d�faut inutiles
//       (d�j� d�finies dans le .h)
//
//       Revision 1.1  1998/05/13 09:26:05  luc
//       Initial revision
//
//$Version
//       $Id: SectionDoree.cpp,v 1.7 2003/02/04 09:30:17 cantor Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "cantor/Util.h"
#include "cantor/SectionDoree.h"


void SectionDoree (double fonc (double x, void *), void *arg,
                   double eps, double xa, double xb,
                   double *ptrXMin, double *ptrFMin)
{ // recherche du minimum d'une fonction par un algorithme de section
  // dor�e il s'agit l� d'une m�thode de r�duction d'intervalle simple
  // ne faisant qu'une hypoth�se de fonction unimodale sur l'intervalle ouvert
  // (la fonction n'a pas besoin d'�tre continue sur l'intervalle, elle peut
  //  m�me ne pas �tre d�finie aux bornes)
  const double phi = 0.5 * (sqrt (5.0) - 1.0);

  // points de test interm�diaires : x1 et x2
  double longueur = xb - xa;
  double delta    = longueur * (1.0 - phi);

  double x1 = xa + delta;
  double f1 = fonc (x1, arg);

  double x2 = xb - delta;
  double f2 = fonc (x2, arg);

  while (fabs (longueur) > 2.0 * eps / phi)
  { // boucle de r�duction de l'intervalle
    delta    *= phi;
    longueur *= phi;

    if (f1 <= f2)
    { // le minimum est entre xa et x2
      xb = x2;

      x2 = x1;
      f2 = f1;

      x1 = xa + delta;
      f1 = fonc (x1, arg);

    }
    else
    { // le minimum est entre x1 et xb
      xa = x1;

      x1 = x2;
      f1 = f2;

      x2 = xb - delta;
      f2 = fonc (x2, arg);

    }
  }

  // on a converg�, on �value le point milieu, pour garantir que
  // le dernier appel � f (et donc les �ventuelles derni�res mises �
  // jour de arg) correspondent bien au minimum estim�
  double xMin = (f1 < f2) ? (0.5 * (xa + x2)) : (0.5 * (x1 + xb));
  double fMin = fonc (xMin, arg);

  if (ptrXMin)
    *ptrXMin = xMin;
  if (ptrFMin)
    *ptrFMin = fMin;

}

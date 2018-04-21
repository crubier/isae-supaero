////////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Type
//       DEF
//
//$Projet
//        Bibam
//$Application
//        Club
//$Nom
//
//$Resume
//       fichier d'implantation de la classe XXXX
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//
//$Historique
//       $Log: prgm_Arc1.cpp,v $
//       Revision 1.1  2002/02/04 13:09:19  cantor
//       cr�ation de test
//
//       Revision 1.9  2001/03/22 09:53:34  cantor
//       suppression d'un avertissement de g++
//
//       Revision 1.8  2001/03/14 15:24:01  cantor
//       suppression d'une fuite de m�moire
//
//       Revision 1.7  2000/10/24 16:26:42  cantor
//       utilisation des tests de configuration � l'aide des variables d�finies
//       dans CantorConfigNoInstall.h pour les includes du standard C ou C++.
//
//$Version
//       $Id: prgm_Arc1.cpp,v 1.1 2002/02/04 13:09:19 cantor Exp $
//$Auteur
//        P-A.Cros  CSSI
//        M. Julien CSSI 
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <CantorConfigNoInstall.h>

#ifdef HAVE_IOSTREAM
#include <iostream>
#endif

#include "club/ClubErreurs.h"
#include "cantor/Util.h"
#include "cantor/Arc.h"
#include "cantor/ArcIterateur.h"

static void proprietesArc (int i, const Arc& a)
{ VecDBL  avantDeb = a.intermediaire (-0.01 * a.balayage ());
  VecDBL  apresDeb = a.intermediaire ( 0.01 * a.balayage ());
  VecDBL  avantFin = a.intermediaire ( 0.99 * a.balayage ());
  VecDBL  apresFin = a.intermediaire ( 1.01 * a.balayage ());

cout << "# Arc " << i << "\n# balayage : " << degres (a.balayage ())
       << "\n# longueur : " << degres (a.longueur ())
       << "\n# intermediaire (-0.01 alpha) : "
       << (a.diedreContient (avantDeb) ? "inclus" : "hors")
       << ", distance = " << degres (a.distance (avantDeb))
       << "\n# intermediaire ( 0.01 alpha) : "
       << (a.diedreContient (apresDeb) ? "inclus" : "hors")
       << ", distance = " << degres (a.distance (apresDeb))
       << "\n# intermediaire ( 0.99 alpha) : "
       << (a.diedreContient (avantFin) ? "inclus" : "hors")
       << ", distance = " << degres (a.distance (avantFin))
       << "\n# intermediaire ( 1.01 alpha) : "
       << (a.diedreContient (apresFin) ? "inclus" : "hors")
       << ", distance = " << degres (a.distance (apresFin))
       << "\n";
}

int main ()
{ ClubAllocHandler h; // utilis� uniquement pour ses constructeur/destructeur

#ifdef HAVE_EXCEPTIONS
  try
  {
#endif

    // construction de divers arcs
    Arc* tab [7];
    tab [0] = new Arc (VecDBL (0.0, 0.0, 12345.0));
    tab [1] = new Arc (VecDBL (0.0, 12.0, 0.0), 0.3);
    tab [2] = new Arc (VecDBL (1.0, 1.0, 0.0),
                       VecDBL (0.0, 1.0, 1.0)
                      );
    tab [3] = new Arc (VecDBL (1.0, 0.0, 0.0),
                       VecDBL (1.0, 1.0, 0.0),
                       VecDBL (0.0, 1.0, 1.0)
                      );
    tab [4] = new Arc (VecDBL (1.0, 0.0, 0.0), 0.4,
                       VecDBL (1.0, 1.0, 0.0),
                       VecDBL (0.0, 1.0, 1.0)
                      );
    tab [5] = new Arc (VecDBL (0.0, 0.8, 0.6), 0.5);
    tab [6] = new Arc (tab [5]->axe (), tab [5]->angle ()- 3e-6,
                       tab [5]->intermediaire (6.2),
                       tab [5]->intermediaire (0.1));

    cout.setf (ios::fixed);
    cout.setf (ios::showpoint);

    for (int i = 0; i < 7; i++)
    { // boucle sur tous les arcs
      proprietesArc (i, *tab[i]);

      int nbInt;
      VecDBL v1, v2;
      tab [i]->intersection (*tab[5], &nbInt, &v1, &v2);
      cout << "# " << nbInt << " intersection" << (nbInt > 1 ? "s" : "")
           << " avec l'arc 5\n";
      if (nbInt)
        cout << "# (" << v1.x () << ", " << v1.y () << ", " << v1.z () << ")";
      if (nbInt == 2)
        cout << ", (" << v2.x () << ", " << v2.y () << ", " << v2.z () << ")";
      if (nbInt)
        cout << endl;

      if (tab [i]->recouvre (*tab [6], 3.04e-6))
        cout << "# recouvre l'arc 6 � 0.63 seconde d'arc pr�s\n";
      else
        cout << "# ne recouvre pas l'arc 6 � 0.63 seconde d'arc pr�s\n";

      if (tab [i]->recouvre (*tab [6], 2.96e-6))
        cout << "# recouvre l'arc 6 � 0.61 seconde d'arc pr�s\n";
      else
        cout << "# ne recouvre pas l'arc 6 � 0.61 seconde d'arc pr�s\n";

      ArcIterateur iter (*tab[i]);

      // utilisation de l'it�rateur non initialis�
      VecDBL p = iter.point ();
      cout << p.x () << ' ' << p.y () << ' ' << p.z () << '\n';
      p = iter.point ();
      cout << p.x () << ' ' << p.y () << ' ' << p.z () << '\n';

      // boucle d'affichage des points
      while (iter ())
      { p = iter.point ();
            cout << p.x () << ' ' << p.y () << ' ' << p.z () << '\n';
      }

      // utilisation de l'it�rateur en bout d'arc
      p = iter.point ();
      cout << p.x () << ' ' << p.y () << ' ' << p.z () << '\n';
      p = iter.point ();
      cout << p.x () << ' ' << p.y () << ' ' << p.z () << '\n';

      // ajout d'un caract�re '&' pour s�parer les courbes
      cout << "&\n";

    }


    for (int i = 0; i < (int) (sizeof(tab)/sizeof(Arc *)); ++i)
      delete tab [i];

#ifdef HAVE_EXCEPTIONS
  }

  catch (ClubErreurs& e)
  { e.affiche (cerr);
    return 1;
  }
#endif

  return 0;

}

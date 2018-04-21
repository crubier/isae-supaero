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
//       Club
//
//$Nom
//>       OptionTableauReels.cpp
//
//$Resume
//       fichier d'implantation de la classe OptionTabReels
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       class OptionTableauReels
//>         OptionTableauReels()  
//>         operator =()          
//>         ~OptionTableauReels() 
//>         verifier()            
//>         lireValeur()          
//>         ajouterOccurrence()   
//>         ajouterValeur()       
//
//$Historique
//       $Log: OptionTableauReels.cpp,v $
//       Revision 1.6  2003/02/03 13:47:18  club
//       DM-ID 17 Mise � jour de l'extension du fichier dans le bandeau
//
//       Revision 1.5  2000/10/24 14:21:01  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 1.4  2000/10/24 08:33:30  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 1.3  2000/09/07 08:02:10  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 1.2  2000/07/03 08:57:21  club
//       Ajout du copyright CNES
//
//       Revision 1.1.2.1  2000/03/30 14:46:51  club
//       ajout du copyright CNES
//
//       Revision 1.1  1999/07/07 08:06:06  club
//       Changement de nom des fichiers *Tab* en
//       *Tableau* pour correspondre au nom de la classe
//
//       Revision 3.7  1998/07/27 10:13:50  club
//       passage � une configuration de type GNU (fichier ClubConfig.h g�n�r�)
//
//       Revision 3.6  1998/06/21 16:00:27  luc
//       modification du format de l'en-t�te
//       �limination de la cha�ne statique RCS
//       �limination de la fonction estValide
//
//       Revision 3.5  1998/04/26 13:02:40  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.4  1997/08/21 16:44:06  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 3.3  1997/04/03 12:48:08  luc
//       inversion des codes de retour, 0 signifie d�sormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:04:19  luc
//       changement des r�gles de nommage
//       
//       Revision 3.1  1997/03/19 15:19:52  luc
//       utilisation de la classe ChaineSimple
//       renommage de la classe UtilErreurs en ClubErreurs
//       renommage de la biblioth�que util_c++ en club
//       passage de SCCS � RCS
//       
//       Revision 2.3  1996/10/04 09:47:54  luc
//       appel explicite des m�thodes de la classe de base pour
//       �viter le masquage des signatures de lireValeur invalides
//       par la seule signature valide
//       
//       Revision 2.2  1996/09/25 10:54:23  luc
//       ajout d'un "cast" explicite pour le compilateur (idiot) version 3 de Sun
//       
//       Revision 2.1  1996/07/15 17:19:30  luc
//       �limination de la d�pendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       correction d'orthographe dans les noms de fonctions (occurence -> occurrence)
//       utilisation d'une valeur de retour enti�re et d'un UtilErreurs *ptrErreur
//       pour les fonctions pouvant g�n�rer des erreurs
//       
//       Revision 1.6  1995/07/12 15:02:17  mercator
//       ajout d'un pointeur this explicite pour aider le compilateur SUN a comprendre
//       
//       Revision 1.5  1995/07/03 14:48:09  mercator
//       modification de la portee de variables de boucle for
//       
//       Revision 1.4  1995/06/26 06:38:11  mercator
//       remplacement d'un copie-constructeur par un operateur =
//       (on ne peut construire une instance de classe abstraite, meme pour initialiser
//       une instance de classe derivee concrete)
//       
//       Revision 1.3  1994/11/09 15:02:19  mercator
//       elimination des directives #pragma
//       
//       Revision 1.2  1994/08/30 12:54:26  mercator
//       remplacement de "lance" par "erreur"
//       
//       Revision 1.1  1994/07/27 12:05:57  luc
//       Initial revision
//
//$Version
//       $Id: OptionTableauReels.cpp,v 1.6 2003/02/03 13:47:18 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       G. Lajon     CSSI
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#if STDC_HEADERS
# include <cstdlib>
#endif

#include "club/OptionTableauReels.h"
#include "club/ClubErreurs.h"

OptionTableauReels::OptionTableauReels (const char *code,
                                        int occurrencesMin,
                                        int occurrencesMax,
                                        int valueeParDefaut,
                                        int valeursAttendues,
                                        const double* valeurs,
                                        double limiteInf, double limiteSup)
  throw (ClubErreurs)
  : OptionBase (code, occurrencesMin, occurrencesMax, valueeParDefaut,
                OptionBase::tableau_de_reels, valeursAttendues),
    tabValeurs_ (0), limiteInf_ (limiteInf), limiteSup_ (limiteSup)
{ 
  if (valeursAttendues == 0)
    throw ClubErreurs (ClubErreurs::nombre_arguments_nul,
                 OptionBase::code ().c_str ());

  if (valueeParDefaut)
  { 
    if (valeurs == 0)
      throw ClubErreurs(ClubErreurs::valeur_par_defaut_manquante,
                        OptionBase::code ().c_str ());
    else
    { // v�rification des valeurs par d�faut
      for (int i = 0; i < valeursAttendues; i++)
      { if ((valeurs [i] < limiteInf) || (valeurs [i] > limiteSup))
        throw ClubErreurs (ClubErreurs::option_reelle_hors_limites,
                           OptionBase::code ().c_str (),
                           limiteInf, limiteSup, valeurs [i]);
      }

      // stockage
      tabValeurs_     = new double* [1];
      tabValeurs_ [0] = new double  [valeursAttendues];
      for (int k = 0; k < valeursAttendues; k++)
        tabValeurs_ [0][k] = valeurs [k];

    }
  }

}

OptionTableauReels::OptionTableauReels (const string& code,
                                        int occurrencesMin,
                                        int occurrencesMax,
                                        int valueeParDefaut,
                                        int valeursAttendues,
                                        const double* valeurs,
                                        double limiteInf, double limiteSup)
  throw (ClubErreurs)
  : OptionBase (code, occurrencesMin, occurrencesMax, valueeParDefaut,
                OptionBase::tableau_de_reels, valeursAttendues),
    tabValeurs_ (0), limiteInf_ (limiteInf), limiteSup_ (limiteSup)
{ 
  if (valeursAttendues == 0)
    throw ClubErreurs(ClubErreurs::nombre_arguments_nul,
                      OptionBase::code ().c_str ());

  if (valueeParDefaut)
  { 
    if (valeurs == 0)
    throw ClubErreurs (ClubErreurs::valeur_par_defaut_manquante,
                       OptionBase::code ().c_str ());
    else
    { // v�rification des valeurs par d�faut
      for (int i = 0; i < valeursAttendues; i++)
      { 
        if ((valeurs [i] < limiteInf) || (valeurs [i] > limiteSup))
          throw ClubErreurs (ClubErreurs::option_reelle_hors_limites,
                             OptionBase::code ().c_str (),
                             limiteInf, limiteSup, valeurs [i]);
      }

      // stockage
      tabValeurs_     = new double* [1];
      tabValeurs_ [0] = new double  [valeursAttendues];
      for (int k = 0; k < valeursAttendues; k++)
        tabValeurs_ [0][k] = valeurs [k];

    }
  }

}

OptionTableauReels::OptionTableauReels (const OptionTableauReels& opt)
  : OptionBase (opt),
    tabValeurs_ (0), limiteInf_ (opt.limiteInf_), limiteSup_ (opt.limiteSup_)
{ // copie-constructeur

  if (opt.occurrencesPassees ())
  { // allocation d'une table d'occurrences
    tabValeurs_ = new double* [opt.occurrencesPassees ()];
    for (int i = 0; i < opt.occurrencesPassees (); i++)
    { // allocation d'une table des valeurs pour l'occurrence courante
      tabValeurs_ [i] = new double [opt.valeursAttendues ()];

      // remplissage de la table
      for (int j = 0; j < opt.valeursAttendues (); j++)
        tabValeurs_ [i][j] = opt.tabValeurs_ [i][j];

    }
  }
  else if (opt.estValueeParDefaut ())
  { // allocation d'une entr�e par d�faut
    tabValeurs_     = new double* [1];
    tabValeurs_ [0] = new double [opt.valeursAttendues ()];

    // remplissage de la table
    for (int k = 0; k < opt.valeursAttendues (); k++)
      tabValeurs_ [0][k] = opt.tabValeurs_ [0][k];

  }

}

OptionTableauReels& OptionTableauReels::operator =
                                                (const OptionTableauReels& opt)
{ if (this != &opt)      // protection contre x = x
  { this->OptionBase::operator = (opt);

    // lib�ration des tables pr�c�dentes
    if (occurrencesPassees ())
    { for (int i = 0; i < occurrencesPassees (); i++)
       delete [] tabValeurs_ [i];
      delete [] tabValeurs_;
    }
    else if (estValueeParDefaut ())
    { delete [] tabValeurs_ [0];
      delete [] tabValeurs_;
    }

    // copie effective
    if (opt.occurrencesPassees ())
    { // allocation d'une table d'occurrences
      tabValeurs_ = new double* [opt.occurrencesPassees ()];
      for (int i = 0; i < opt.occurrencesPassees (); i++)
      { // allocation d'une table des valeurs pour l'occurrence courante
        tabValeurs_ [i] = new double [opt.valeursAttendues ()];

        // remplissage de la table
        for (int j = 0; j < opt.valeursAttendues (); j++)
          tabValeurs_ [i][j] = opt.tabValeurs_ [i][j];

      }
    }
    else if (opt.estValueeParDefaut ())
    { // allocation d'une entr�e par d�faut
      tabValeurs_ = new double* [1];
      tabValeurs_ [0] = new double [opt.valeursAttendues ()];

      // remplissage de la table
      for (int k = 0; k < opt.valeursAttendues (); k++)
        tabValeurs_ [0][k] = opt.tabValeurs_ [0][k];

    }

    limiteInf_ = opt.limiteInf_;
    limiteSup_ = opt.limiteSup_;

  }

  return *this;

}

OptionTableauReels::~OptionTableauReels ()
{ if (occurrencesPassees ())
  { for (int i = 0; i < occurrencesPassees (); i++)
      delete [] tabValeurs_ [i];
    delete [] tabValeurs_;
  }
  else if (estValueeParDefaut ())
  { delete [] tabValeurs_ [0];
    delete [] tabValeurs_;
  }

}

int OptionTableauReels::verifier (string *ptrMessage) const
{ int r = OptionBase::verifier (ptrMessage);
  if (r)
    return r;

  for (int n = 0; n < occurrencesPassees (); n++)
  { for (int i = 0; i < valeursAttendues (); i++)
    { double* tableau = tabValeurs_ [n];

      if ((tableau [i] < limiteInf_) || (tableau [i] > limiteSup_))
      { ClubErreurs e (ClubErreurs::option_reelle_hors_limites,
                       code ().c_str (), limiteInf_, limiteSup_,
                       tableau [i]);
        *ptrMessage = e.why ();
        e.correction ();
        return ClubErreurs::option_reelle_hors_limites;
      }

    }
  }

  return 0;

}

void OptionTableauReels::lireValeur (int nombre, int dest [],
                                    int occurrence) const
  throw (ClubErreurs)
{ OptionBase::lireValeur (nombre, dest, occurrence); }

void OptionTableauReels::lireValeur (int nombre, double dest [],
                                    int occurrence) const
  throw (ClubErreurs)
{ if (nombre != valeursAttendues ())
    throw ClubErreurs (ClubErreurs::taille_tableau_arguments,
                       code ().c_str (), valeursAttendues ());

  if (occurrencesPassees () == 0)
  { if (! estValueeParDefaut ())
      throw ClubErreurs (ClubErreurs::valeur_par_defaut_manquante,
                         code ().c_str ());
    else
    { // en l'absence d'option, on utilise les valeurs par d�faut
      double* tableau = tabValeurs_ [0];
      for (int i = 0; i < nombre; i++)
         dest [i] = tableau [i];
    }
  }
  else
  { if ((occurrence < 1) || (occurrence > occurrencesPassees ()))
      throw ClubErreurs (ClubErreurs::occurrence_inexistante,
                         occurrence, code ().c_str (),
                         occurrencesPassees ());
    else
    { double* tableau = tabValeurs_ [occurrence - 1];
      for (int i = 0; i < nombre; i++)
         dest [i] = tableau [i];
    }

  }

}

void OptionTableauReels::lireValeur (int nombre, char *dest [],
                                    int occurrence) const
  throw (ClubErreurs)
{ OptionBase::lireValeur (nombre, dest, occurrence); }

void OptionTableauReels::lireValeur (int nombre, string dest [],
                                    int occurrence) const
  throw (ClubErreurs)
{ OptionBase::lireValeur (nombre, dest, occurrence); }

void OptionTableauReels::ajouterOccurrence ()
  throw (ClubErreurs)
{ 
  OptionBase::ajouterOccurrence ();

  if ((occurrencesPassees () != 1) || (! estValueeParDefaut ()))
  { // on doit allouer une nouvelle entr�e dans la table des occurrences
    double **nouvelleTable = new double* [occurrencesPassees ()];
    for (int i = 0; i < occurrencesPassees () - 1; i++)
      nouvelleTable [i] = tabValeurs_ [i];
    if (occurrencesPassees () != 1)
      delete [] tabValeurs_;
    tabValeurs_ = nouvelleTable;

    tabValeurs_ [occurrencesPassees () - 1] = new double [valeursAttendues ()];
    for (int j = 0; j < valeursAttendues (); j++)
      tabValeurs_ [occurrencesPassees () - 1][j] = 0.0;

  }

}

void OptionTableauReels::ajouterValeur (const char *chaine)
  throw (ClubErreurs)
{ incrementeValeursTrouvees ();

  if (valeursTrouvees () > valeursAttendues ())
    throw ClubErreurs (ClubErreurs::nombres_arguments_incompatibles,
                       code ().c_str (),
                       valeursTrouvees (), valeursAttendues ());

  tabValeurs_ [occurrencesPassees()-1][valeursTrouvees()-1] = atof (chaine);

}

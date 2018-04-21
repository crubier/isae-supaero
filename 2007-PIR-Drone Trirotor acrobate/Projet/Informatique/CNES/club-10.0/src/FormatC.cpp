////////////////////////////////////////////////////////////////////////////////
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
//>       FormatC.cpp
//
//$Resume
//       fichier d'implantation de la classe FormatC
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       class FormatC
//>         ajoutePart()     
//>         FormatC()  
//>         operator =()     
//>         ~FormatC() 
//>         analyse()        
//>         compatible()     
//>         nbArgs()         
//>         typeArg()        
//
//$Historique
//       $Log: FormatC.cpp,v $
//       Revision 1.6  2003/02/03 13:33:12  club
//       DM-ID 17 Mise � jour de l'extension du fichier dans le bandeau
//
//       Revision 1.5  2000/10/24 14:21:01  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 1.4  2000/10/24 08:33:29  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 1.3  2000/09/13 15:33:58  club
//       modification de la m�thode applique de FormatC : allocation de la chaine s
//       avec un nombre de caract�res suppos� suffisamment grand.
//
//       Revision 1.2  2000/09/07 08:08:45  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//       suppression de l'include stdlib.h, ajout de l'include stdio.h
//
//       Revision 1.1  2000/08/25 07:38:18  club
//       Initial revision.
//
//$Version
//       $Id: FormatC.cpp,v 1.6 2003/02/03 13:33:12 club Exp $
//$Auteur
//       O. Queyrut  CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#if STDC_HEADERS
# include <cstdio>
#endif

#include "club/FormatC.h"


FormatC::FormatC (const FormatC& f)
  : tailleTableType_ (0), nbArgs_ (0), type_ (0), chaine_ (f.chaine_)
{ 
  // constructeur par copie
  for (int i = 0; i < f.nbArgs_; i++)
    ajouteArg (f.type_ [i]);
}


FormatC& FormatC::operator = (const FormatC& f)
{ // affectation
  if (this != &f)    // protection contre x = x
  {
    // copie des tables
    nbArgs_ = 0;
    for (int i = 0; i < f.nbArgs_; i++)
      ajouteArg (f.type_ [i]);

    chaine_ = f.chaine_;
  }
  return *this;
}


FormatC::~FormatC ()
{ // destructeur
  if (tailleTableType_)
  { // lib�ration de la m�moire allou�e
    delete [] type_;
  }
}


void FormatC::analyse (const string& format)
{ // analyse d'un format C
  chaine_      = format;
  nbArgs_ = 0;

  const char* specificateur = specificateurSuivant (chaine_.c_str ());

  while (specificateur)
  {
    switch (*specificateur)
    { 
      case 's' :
        // sp�cificateur de cha�ne
        ajouteArg (CHAINE);
        break;
        
      case 'e' : case 'f' : case 'g' : case 'E' : case 'G' :
        // sp�cificateur de r�el
        ajouteArg (REEL);
        break;
        
      case 'c' :
        // sp�cificateur de caract�re
        ajouteArg (CARACTERE);
        break;

      case 'd' : case 'i' : case 'o' : case 'u' : case 'x' : case 'X' :
        // sp�cificateur d'entier
        ajouteArg (ENTIER);
        break;

      default :
        // sp�cificateur non reconnu
        ajouteArg (INCONNU);
        break;
    }

    // pr�paration de l'analyse du sp�cificateur suivant
    specificateur = specificateurSuivant (specificateur);
  }
}


int FormatC::compatible (const FormatC& f) const
{
  // teste la compatibilit� de deux formats au niveau des arguments attendus
  int n = nbArgs ();

  if (n != f.nbArgs ())
    return 0;

  for (int i = 0; i < n; i++)
    if (typeArg (i) != f.typeArg (i))
      return 0;

  return 1;  
}

va_list FormatC::applique (va_list ap, string* ptrChaine) const
{ // �criture d'une cha�ne selon un format analys�
  *ptrChaine = "";
  char* s = new char [4096];

  (void) vsprintf (s, chaine_.c_str (), ap);
  *ptrChaine += s;

  delete [] s;

  return ap;
}


int FormatC::typeArg (int i) const
{ // r�cup�ration du type attendu pour un argument
  if ((i < 0) || (i >= nbArgs_))
    return ERREUR;
  else
    return type_ [i];
}


void FormatC::ajouteArg (int type)
{ // ajout d'un �l�ment aux tables d'analyse de parts de format

  if (nbArgs_ == tailleTableType_)
  { // extension des tables d'analyse de parts de format
    int taille = (tailleTableType_ <= 0) ? 5 : (tailleTableType_ << 1);

    int *nouveauxTypes = new int [taille];

    for (int i = 0; i < nbArgs_; i++)
      nouveauxTypes [i] = type_ [i];

    if (tailleTableType_)
      // lib�ration des anciennes tables
      delete [] type_;

    // mise en place des nouvelles tables
    tailleTableType_ = taille;
    type_            = nouveauxTypes;
  }

  type_ [nbArgs_] = type;
  nbArgs_++;
}


const char* FormatC::specificateurSuivant (const char* mobile) const
{
  // recherche du prochain sp�cificateur de format
  while (1)
  { 
    while ((*mobile) && (*mobile != '%'))
      mobile++;

    if (*mobile == '\0')
      return 0;

    if (*++mobile != '%')
    { // le '%' est bien un indicateur de format

      // saut des options du format (drapeaux, �tendue, pr�cision, indicateur
      // de taille)
      while (isdigit(*mobile) || (*mobile == '.') || (*mobile == '-') || 
             (*mobile == '+') || (*mobile == ' ') || (*mobile == '#') ||
             (*mobile == 'h') || (*mobile == 'l') || (*mobile == 'L'))
        mobile++;

      // retour du sp�cificateur
      return mobile;
    }
  }
}

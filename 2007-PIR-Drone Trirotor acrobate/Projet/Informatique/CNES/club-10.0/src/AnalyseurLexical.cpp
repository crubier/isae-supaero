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
//>       AnalyseurLexical.cpp
//
//$Resume
//       fichier d'implantation de la classe AnalyseurLexical
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       class AnalyseurLexical  
//>         AnalyseurLexical()    
//>         operator =()          
//>         analyseReelOuEntier() 
//>         analyseEntier()       
//>         analyseChaineC()      
//>         analyseChaineFortran()
//>         redemarre()           
//>         suivant()             
//>         precedent()           
//>         retourneAEtat()     
//  
//$Historique
//       $Log: AnalyseurLexical.cpp,v $
//       Revision 1.16  2003/02/03 09:03:37  club
//       DM-ID 17 Changement de l'extension du fichier dans le bandeau
//
//       Revision 1.15  2001/06/22 05:41:50  club
//       remplacement de l'inclusion de cwctype par l'inclusion de cctype
//
//       Revision 1.14  2001/04/04 11:29:59  club
//       ajout de la reconnaissance param�trable des r�els du langage fortran
//
//       Revision 1.13  2000/10/24 14:21:00  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 1.12  2000/10/24 08:33:29  club
//       modification des include standard du C : utilisation de cNAME au lieu de
//       NAME.h (pour permettre la compilation avec le Sun Workshop 5.0)
//
//       Revision 1.11  2000/09/07 08:10:01  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//       ajout de l'include ctype.h
//
//       Revision 1.10  2000/07/03 08:57:18  club
//       Ajout du copyright CNES
//
//       Revision 1.9.2.1  2000/03/30 14:46:46  club
//       ajout du copyright CNES
//
//       Revision 1.9  1999/03/15 10:54:00  club
//       correction du masque utilis� pour la protection des caract�res lus sous
//       forme octale ou hexad�cimale
//
//       Revision 1.8  1998/11/17 12:04:18  club
//       correction de l'oubli de l'affectation de derniereChaineC_ et
//       derniereChaineFortran_ dans l'op�rateur d'affectation et le
//       constructeur par copie
//       ajout de protection sur le domaine des caract�res lus sous
//       forme octale ou hexad�cimale
//
//       Revision 1.7  1998/07/27 10:13:37  club
//       passage � une configuration de type GNU (fichier ClubConfig.h g�n�r�)
//
//       Revision 1.6  1998/06/21 15:53:01  luc
//       modification du format de l'en-t�te
//       �limination de la cha�ne statique RCS
//
//       Revision 1.5  1998/04/26 13:02:15  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.4  1997/09/11 15:36:50  luc
//       correction d'une erreur d'analyse des r�els avec exposants sign�s
//
//       Revision 1.3  1997/08/25 18:25:01  luc
//       reconnaissance des cha�nes de caract�res C et fortran
//       d�brayage possible de la reconnaissance des r�els
//       d�brayage possible de la reconnaissance des cha�nes
//       ajout des m�thodes etatCourant et retourneAEtat
//
//       Revision 1.2  1997/08/21 16:43:10  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 1.1  1997/04/08 09:53:32  luc
//       Initial revision
//
//$Version
//       $Id: AnalyseurLexical.cpp,v 1.16 2003/02/03 09:03:37 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#if STDC_HEADERS
# include <cstdlib>
# include <cctype>
#endif

#include "club/AnalyseurLexical.h"

AnalyseurLexical::AnalyseurLexical (const string& chaine)
  : chaine_ (chaine),
    blancs_ ("\t\n\v\f\r "), separateurs_ (""), operateurs_ (""),
    reconnaitReels_ (true), reconnaitReelsFortran_ (false),
    reconnaitChainesC_ (false), reconnaitChainesFortran_ (false)
{ redemarre (); }

AnalyseurLexical::AnalyseurLexical (const char *chaine)
  : chaine_ (chaine),
   blancs_ ("\t\n\v\f\r "),  separateurs_ (""), operateurs_ (""),
    reconnaitReels_ (true), reconnaitReelsFortran_ (false),
    reconnaitChainesC_ (false), reconnaitChainesFortran_ (false)
{ redemarre (); }

AnalyseurLexical::AnalyseurLexical (const char *chaine, int longueur)
  : chaine_ (chaine, longueur),
   blancs_ ("\t\n\v\f\r "),  separateurs_ (""), operateurs_ (""),
    reconnaitReels_ (true), reconnaitReelsFortran_ (false),
    reconnaitChainesC_ (false), reconnaitChainesFortran_ (false)
{ redemarre (); }

AnalyseurLexical::AnalyseurLexical (const AnalyseurLexical& a)
  : chaine_ (a.chaine_), index_ (a.index_), blancs_ (a.blancs_),
    separateurs_ (a.separateurs_), operateurs_ (a.operateurs_),
    reconnaitReels_ (a.reconnaitReels_),
    reconnaitReelsFortran_ (a.reconnaitReelsFortran_),
    reconnaitChainesC_ (a.reconnaitChainesC_),
    reconnaitChainesFortran_ (a.reconnaitChainesFortran_),
    dernierLexeme_ (a.dernierLexeme_), dernierType_ (a.dernierType_),
    dernierEntier_ (a.dernierEntier_), dernierReel_ (a.dernierReel_),
    dernierNom_ (a.dernierNom_),
    derniereChaineC_ (a.derniereChaineC_),
    derniereChaineFortran_ (a.derniereChaineFortran_),
    dernierSeparateur_ (a.dernierSeparateur_),
    derniereParenthese_ (a.derniereParenthese_),
    dernierOperateur_ (a.dernierOperateur_)
{ debut_  = chaine_.c_str () + a.debutLexeme ();
  mobile_ = chaine_.c_str () + a.apresLexeme ();
}

AnalyseurLexical& AnalyseurLexical::operator = (const AnalyseurLexical& a)
{ // affectation
  if (this != &a)     // protection contre x = x
  { chaine_                  = a.chaine_;
    debut_                   = chaine_.c_str () + a.debutLexeme ();
    mobile_                  = chaine_.c_str () + a.apresLexeme ();
    index_                   = a.index_;

    blancs_                  = a.blancs_;
    separateurs_             = a.separateurs_;
    operateurs_              = a.operateurs_;

    reconnaitReels_          = a.reconnaitReels_;
    reconnaitReelsFortran_   = a.reconnaitReelsFortran_;
    reconnaitChainesC_       = a.reconnaitChainesC_;
    reconnaitChainesFortran_ = a.reconnaitChainesFortran_;

    dernierLexeme_           = a.dernierLexeme_;
    dernierType_             = a.dernierType_;
    dernierEntier_           = a.dernierEntier_;
    dernierReel_             = a.dernierReel_;
    dernierNom_              = a.dernierNom_;
    derniereChaineC_         = a.derniereChaineC_;
    derniereChaineFortran_   = a.derniereChaineFortran_;
    dernierSeparateur_       = a.dernierSeparateur_;
    derniereParenthese_      = a.derniereParenthese_;
    dernierOperateur_        = a.dernierOperateur_;

  }

  return *this;

}

void AnalyseurLexical::analyseReelOuEntier ()
{ // tentative de reconnaissance d'un r�el (voire d'un entier)

  int dejaChiffre = isdigit(*mobile_);
  int dejaPoint   = (*mobile_++ == '.');
  while (((*mobile_ == '.') && !dejaPoint) || isdigit(*mobile_))
  { // parcours de la mantisse
    dejaChiffre = dejaChiffre || isdigit(*mobile_);
    dejaPoint   = dejaPoint   || (*mobile_ == '.');
    mobile_++;
  }

  if (!dejaChiffre)
  { // il n'y avait qu'un signe et �ventuellement un point
    dernierType_   = codeInconnu;
    dernierLexeme_ = string (debut_, 1);
    mobile_        = debut_ + 1;
    return;
  }

  // m�me si on doit s'arr�ter l�, on a d�j� reconnu un nombre
  const char *debutExposant = mobile_;
  if (((*mobile_ == 'e') || (*mobile_ == 'E'))
      || (reconnaitReelsFortran_ && ((*mobile_ == 'd') || (*mobile_ == 'D'))))
  { // analyse de l'exposant
    int indexExposant = mobile_ - debut_;
    mobile_++;

    if ((*mobile_ == '-') || (*mobile_ == '+') || isdigit(*mobile_))
    { if ((*mobile_ == '-') || (*mobile_ == '+'))
        mobile_++;

      while (isdigit(*mobile_))
        mobile_++;

      if (isdigit(*(mobile_ - 1)))
      { // l'exposant est bien form�
        dernierType_   = codeReel;
        dernierLexeme_ = string (debut_, mobile_ - debut_);
        dernierLexeme_.replace (indexExposant, 1, 1, 'e');
        dernierReel_   = atof (dernierLexeme_.c_str ());
        return;
      }

    }
  }

  // soit l'exposant n'est pas bien form� soit il n'y a pas d'exposant
  // on se contente de la mantisse d�j� d�tect�e
  mobile_        = debutExposant;
  dernierLexeme_ = string (debut_, mobile_ - debut_);
  if (dejaPoint)
  { // c'est un r�el
    dernierType_ = codeReel;
    dernierReel_ = atof (dernierLexeme_.c_str ());
  }
  else
  { // c'est un entier
    dernierType_   = codeEntier;
    dernierEntier_ = atoi (dernierLexeme_.c_str ());
  }

}

void AnalyseurLexical::analyseEntier ()
{ // tentative de reconnaissance d'un entier
  int dejaChiffre = isdigit(*mobile_++);
  while (isdigit(*mobile_))
  { // parcours des chiffres
    dejaChiffre = 1;
    mobile_++;
  }

  if (!dejaChiffre)
  { // il n'y avait qu'un signe
    dernierType_   = codeInconnu;
    dernierLexeme_ = string (debut_, 1);
    mobile_        = debut_ + 1;
  }
  else
  { // on a bien lu un entier complet
    dernierType_   = codeEntier;
    dernierLexeme_ = string (debut_, mobile_ - debut_);
    dernierEntier_ = atoi (dernierLexeme_.c_str ());
  }

}


void AnalyseurLexical::analyseChaineC ()
{ // tentative de reconnaissance d'une cha�ne au format C
  // le tron�on entre '"' peut contenir des caract�res sp�ciaux
  // ('\n', '\012', ' ', ...)
  string chaine ("");

  mobile_++;
  char  caractere;
  int   i;

  while (true)
  { // boucle sur les caract�res
    caractere = *mobile_;

    switch (caractere)
    { // identification des caract�res sp�ciaux
      case '\0' : case '\n' :
        // on a trouv� la fin de tampon (de ligne) avant la fin du champ
        dernierType_   = codeInconnu;
        dernierLexeme_ = string (debut_, 1);
        mobile_        = debut_ + 1;
        return;
        // break;

      case '"'  :
        // ce '"' marque la fin de la cha�ne
        dernierType_     = codeChaineC;
        dernierLexeme_   = chaine;
        derniereChaineC_ = chaine;
        mobile_++;
        return;
        // break;

      case '\\' :
        // interpr�tation du caract�re suivant
        mobile_++;
        switch (*mobile_)
        { case '0' : case '1' : case '2' : case '3' :
          case '4' : case '5' : case '6' : case '7' :  // code octal
            caractere = *mobile_ - '0';
            i         = 0;
            while ((i < 2) && (*(mobile_+1) >= '0') && (*(mobile_+1) <= '7'))
            { mobile_++;
              i++;
              caractere = (caractere * 8 + (*mobile_ - '0')) & 0xff;
            }
            break;

          case 'a' :
            caractere = '\a';   // alarme sonore
            break;

          case 'b' :
            caractere = '\b';   // retour en arri�re
            break;

          case 'f' :
            caractere = '\f';   // saut de page
            break;

          case 'n' :
            caractere = '\n';   // nouvelle ligne
            break;

          case 'r' :
            caractere = '\r';   // retour charriot
            break;

          case 't' :
            caractere = '\t';   // tabulation horizontale
            break;

          case 'v' :
            caractere = '\v';   // tabulation verticale
            break;

          case 'x' :  // code hexad�cimal
            caractere = '\0';
            while (isxdigit(*(mobile_ + 1)))
            { mobile_++;
              if (isdigit(*mobile_))
                caractere = (caractere * 16 + (*mobile_ - '0')) & 0xff;
              else
                caractere = (caractere * 16 + (tolower(*mobile_) - 'a' + 10)) & 0xff;
            }
            break;

          default  :  // parmi les autres il y a: '\\', '\"', ...
            caractere = *mobile_;
            break;

        }

        // copie du caract�re dans le tampon
        chaine += caractere;
        break;

      default   : // caract�re normal: 'a', ' ', ...
        // copie du caract�re dans le tampon
        chaine += caractere;
        break;

    }

    // pr�paration de l'analyse du caract�re suivant
    mobile_++;

  }
}


void AnalyseurLexical::analyseChaineFortran ()
{ // tentative de reconnaissance d'une cha�ne au format fortran
  // le seul caract�re sp�cial est le marqueur de fin de cha�ne "'"
  string chaine ("");

  mobile_++;

  while (true)
  { // boucle sur les caract�res
    if ((*mobile_ == '\0') || (*mobile_ == '\n'))
    { // on a trouv� la fin de tampon (de ligne) avant la fin de la cha�ne
      dernierType_   = codeInconnu;
      dernierLexeme_ = string (debut_, 1);
      mobile_        = debut_ + 1;
      return;
    }
    else if (*mobile_ == '\'')
    { // si le caract�re est doubl�, il est dans la cha�ne
      if (*++mobile_ != '\'')
      { // on vient de trouver le caract�re suivant la cha�ne
        dernierType_           = codeChaineFortran;
        dernierLexeme_         = chaine;
        derniereChaineFortran_ = chaine;
        return;
      }
    }

    // copie du caract�re dans le tampon
    chaine += *mobile_++;

  }
}

void AnalyseurLexical::redemarre ()
{ // reprise de l'analyse au d�but de la cha�ne courante
  debut_              = chaine_.c_str ();
  mobile_             = debut_;
  index_              = 0;

  dernierType_        = codeInconnu;
  dernierLexeme_      = "";
  dernierEntier_      = 0;
  dernierReel_        = 0.0;
  dernierNom_         = "";
  dernierSeparateur_  = '\0';
  dernierOperateur_   = '\0';
  derniereParenthese_ = '\0';

}

int AnalyseurLexical::suivant ()
{ // recherche du lex�me suivant

  // �limination des blancs initiaux
  while ((*mobile_) && strchr (blancs_.c_str (), *mobile_))
    mobile_++;

  if (*mobile_ == '\0')
  { // il n'y a plus rien
    dernierType_   = codeFin;
    dernierLexeme_ = "";
  }
  else
  { // indicateur de d�but de lex�me
    debut_ = mobile_;

    // test du caract�re
    if (strchr (separateurs_.c_str (), *mobile_))
    { // c'est un s�parateur
      dernierType_       = codeSeparateur;
      dernierLexeme_     = string (1, *mobile_);
      dernierSeparateur_ = *mobile_++;
    }
    else if (strchr (operateurs_.c_str (), *mobile_))
    { // c'est un op�rateur
      dernierType_      = codeOperateur;
      dernierLexeme_    = string (1, *mobile_);
      dernierOperateur_ = *mobile_++;
    }
    else if (strchr ("()[]{}", *mobile_))
    { // c'est un op�rateur
      dernierType_        = codeParenthese;
      dernierLexeme_      = string (1, *mobile_);
      derniereParenthese_ = *mobile_++;
    }
    else if (reconnaitReels_ && ((*mobile_ == '-') || (*mobile_ == '+')
                              || (*mobile_ == '.') || isdigit(*mobile_)))
    { // il s'agit d'un entier, d'un r�el, ou d'une erreur
      analyseReelOuEntier ();
    }
    else if ((! reconnaitReels_)
             &&
             ((*mobile_ == '-') || (*mobile_ == '+') || isdigit(*mobile_)))
    { // il s'agit d'un entier ou d'une erreur
      analyseEntier ();
    }
    else if (isalpha(*mobile_) || (*mobile_ == '_'))
    { // c'est un nom
      while (isalnum(*mobile_) || (*mobile_ == '_'))
        mobile_++;
      dernierType_   = codeNom;
      dernierLexeme_ = string (debut_, mobile_ - debut_);
      dernierNom_    = dernierLexeme_;
    }
    else if (reconnaitChainesC_ && (*mobile_ == '"'))
    { // il s'agit d'une cha�ne au format C ou d'une erreur
      analyseChaineC ();
    }
    else if (reconnaitChainesFortran_ && (*mobile_ == '\''))
    { // il s'agit d'une cha�ne au format fortran ou d'une erreur
      analyseChaineFortran ();
    }
    else
    { // on ne reconnait pas le lex�me
      dernierType_   = codeInconnu;
      dernierLexeme_ = string (1, *mobile_++);
    }

  }

  index_++;
  return dernierType_;

}

int AnalyseurLexical::precedent ()
{ // retour au lex�me pr�c�dent
  int objectif = index_ ? (index_ - 1) : 0;
  redemarre ();

  while (index_ != objectif)
    (void) suivant ();

  return dernierType_;

}

int AnalyseurLexical::retourneAEtat (int etat)
{ // retour � un lex�me donn�
  redemarre ();

  while (index_ != etat)
    (void) suivant ();

  return dernierType_;

}

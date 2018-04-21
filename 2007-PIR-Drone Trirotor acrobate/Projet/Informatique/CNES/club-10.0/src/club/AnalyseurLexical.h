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
//>       AnalyseurLexical.h
//
//$Resume
//       fichier d'en-t�te de la classe AnalyseurLexical
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class AnalyseurLexical
//
//$Historique
//       $Log: AnalyseurLexical.h,v $
//       Revision 1.14  2002/12/10 08:47:49  club
//       Modification visant � mettre le corps du destructeur dans le fichier H plut�t que dans le fichier CC.
//
//       Revision 1.13  2002/12/09 15:52:21  club
//       DM-ID 12 Mise en conformit� des constructeurs/destructeurs avec la norme qualit�
//
//       Revision 1.12  2001/04/04 11:29:11  club
//       ajout de la reconnaissance param�trable des r�els du langage fortran
//
//       Revision 1.11  2000/10/25 09:31:43  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 1.10  2000/10/24 14:18:14  club
//       mise � jour des includes et ajout des tests de configuration.
//
//       Revision 1.9  2000/09/11 12:18:50  club
//       Mise � jour des include et suppression des tests sur variable de
//       configuration de ClubConfig.h qui n'est pas install�.
//
//       Revision 1.8  2000/09/07 07:47:30  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 1.7  2000/07/03 08:54:18  club
//       Ajout du copyright CNES
//
//       Revision 1.6.2.1  2000/03/30 14:46:53  club
//       ajout du copyright CNES
//
//       Revision 1.6  1998/06/25 06:38:19  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.5  1998/04/26 13:02:13  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.4  1998/01/22 08:26:24  luc
//       am�lioration de l'en-t�te de classe
//
//       Revision 1.3  1997/08/24 13:37:18  luc
//       reconnaissance des cha�nes de caract�res C et fortran
//       d�brayage possible de la reconnaissance des r�els
//       d�brayage possible de la reconnaissance des cha�nes
//       ajout des m�thodes etatCourant et retourneAEtat
//
//       Revision 1.2  1997/08/21 16:33:46  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 1.1  1997/04/08 09:54:21  luc
//       Initial revision
//
//$Version
//       $Id: AnalyseurLexical.h,v 1.14 2002/12/10 08:47:49 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_AnalyseurLexical_h
#define __club_AnalyseurLexical_h

#include <club/ClubConfig.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#include <string>

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class AnalyseurLexical
//
//$Resume
//       classe implantant un analyseur lexical simple
//
//$Description
//       cette classe implante un analyseur lexical param�trable et
//       pouvant reconna�tre les nombres, les parenth�ses, les
//       s�parateurs, les op�rateurs, les noms et les chaines des
//       langages C et fortran.
//
//$Usage
//>     construction : 
//          sans argument, � partir d'une cha�ne initiale, par copie
//>     utilisation  : 
//>       AnalyseurLexical& operator =      () 
//          affectation
//>       void redemarre                    () 
//          reprend l'analyse de la cha�ne courante au d�but
//>       int suivant                       () 
//          passe au lex�me suivant (retourne le type)
//>       int precedent                     () 
//          revient au lex�me pr�c�dent (retourne le type)
//>       int retourneAEtat                 () 
//          remet l'instance dans un �tat m�moris� au pr�alable
//>       void initBlancs                   () 
//          r�initialise la liste des caract�res blancs (ils s�parent
//          les lex�mes mais ne sont pas des lex�mes en eux m�mes)
//>       void initSeparateurs              () 
//          r�initialise la liste des caract�res s�parateurs (ce sont
//          des lex�mes)
//>       void initOperateurs               () 
//          r�initialise la liste des caract�res op�rateurs (pas
//          d'op�rateur � plusieurs caract�res)
//>       void autoriseReels                () 
//          autorise la reconnaissance des r�els
//>       void interditReels                () 
//          interdit la reconnaissance des r�els
//>       void autoriseReelsFortran         () 
//          autorise la reconnaissance des r�els du langage fortran
//>       void interditReelsFortran         () 
//          interdit la reconnaissance des r�els du langage fortran
//>       void autoriseChainesC             () 
//          autorise la reconnaissance des cha�nes du langage C
//>       void interditChainesC             () 
//          interdit la reconnaissance des cha�nes du langage C
//>       void autoriseChainesFortran       () 
//          autorise la reconnaissance des cha�nes du langage fortran
//>       void interditChainesFortran       () 
//          interdit la reconnaissance des cha�nes du langage fortran
//>       void reinitialise                 () 
//          r�initialise l'analyseur pour la cha�ne c (sans changer
//          les listes de s�parateurs ou d'op�rateurs, mais en se
//          repla�ant au d�but)
//>       int etatCourant                   () 
//          retourne un �tat de sorte que l'on puisse y retourner par
//          la suite
//>       const string& chaine              () 
//         retourne la cha�ne compl�te en cours d'analyse
//>       const string& lexeme              () 
//          retourne le lex�me courant
//>       int debutLexeme                   () 
//          retourne l'index du premier caract�re du lex�me courant
//          dans la cha�ne
//>       int apresLexeme                   () 
//          retourne l'index du caract�re suivant le lex�me courant
//          dans la cha�ne
//>       int type                          () 
//          retourne le type du lex�me courant
//>       int entier                        () 
//          retourne le dernier entier analys�
//>       double reel                       () 
//          retourne le dernier r�el analys�
//>       const string& nom                 () 
//          retourne le dernier nom analys�
//>       const string& chaineC             () 
//          retourne la derni�re cha�ne du langage C analys�e
//>       const string& chaineFortran       () 
//          retourne la derni�re cha�ne du langage fortran analys�e
//>       char separateur                   () 
//          retourne le dernier s�parateur analys�
//>       char parenthese                   () 
//          retourne la derni�re parenth�se analys�e
//>       char operateur                    () 
//          retourne le dernier op�rateur analys�
//
//$Auteur
//       L. Maisonobe CNES
//       O. Queyrut   CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class AnalyseurLexical
{

public :

  enum { codeFin,           codeSeparateur, codeOperateur, codeParenthese,
         codeEntier,        codeReel,       codeNom,       codeChaineC,
         codeChaineFortran, codeInconnu
       };

  // constructeurs et affectations
  AnalyseurLexical (const string& chaine);
  AnalyseurLexical (const char *chaine = 0);
  AnalyseurLexical (const char *chaine, int longueur);

  AnalyseurLexical (const AnalyseurLexical& a);
  AnalyseurLexical& operator = (const AnalyseurLexical& a);

  // destructeur
  ~AnalyseurLexical () {};

  // modification de l'analyseur
  void initBlancs (const string& blancs)
  { blancs_ = blancs; redemarre (); }

  void initBlancs (const char *blancs)
  { blancs_ = blancs; redemarre (); }

  void initSeparateurs (const string& separateurs)
  { separateurs_ = separateurs; redemarre (); }

  void initSeparateurs (const char *separateurs)
  { separateurs_ = separateurs; redemarre (); }

  void initOperateurs (const string& operateurs)
  { operateurs_ = operateurs; redemarre (); }

  void initOperateurs (const char *operateurs)
  { operateurs_ = operateurs; redemarre (); }

  void autoriseReels          () { reconnaitReels_          = true;  }
  void interditReels          () { reconnaitReels_          = false; }

  void autoriseReelsFortran   () { reconnaitReelsFortran_   = true;  }
  void interditReelsFortran   () { reconnaitReelsFortran_   = false; }

  void autoriseChainesC       () { reconnaitChainesC_       = true;  }
  void interditChainesC       () { reconnaitChainesC_       = false; }

  void autoriseChainesFortran () { reconnaitChainesFortran_ = true;  }
  void interditChainesFortran () { reconnaitChainesFortran_ = false; }

  // analyse
  void reinitialise (const string& c)
  { chaine_ = c; redemarre (); }

  void reinitialise (const char *c)
  { chaine_ = c; redemarre (); }

  void reinitialise (const char *c, int longueur)
  { chaine_ = string (c, longueur); redemarre (); }

  void redemarre    ();

  int suivant       ();
  int precedent     ();

  int etatCourant   () const { return index_; }
  int retourneAEtat (int etat);

  // acc�s aux �l�ments internes
  const string& chaine        () const { return chaine_;                }
  const string& lexeme        () const { return dernierLexeme_;         }
  int           debutLexeme   () const { return debut_
                                                    - chaine_.c_str (); }
  int           apresLexeme   () const { return mobile_
                                                    - chaine_.c_str (); }
  int           type          () const { return dernierType_;           }
  int           entier        () const { return dernierEntier_;         }
  double        reel          () const { return dernierReel_;           }
  const string& nom           () const { return dernierNom_;            }
  const string& chaineC       () const { return derniereChaineC_;       }
  const string& chaineFortran () const { return derniereChaineFortran_; }
  char          separateur    () const { return dernierSeparateur_;     }
  char          parenthese    () const { return derniereParenthese_;    }
  char          operateur     () const { return dernierOperateur_;      }

private :

  string       chaine_;
  const char  *debut_;
  const char  *mobile_;
  int          index_;

  string       blancs_;
  string       separateurs_;
  string       operateurs_;

  bool         reconnaitReels_;
  bool         reconnaitReelsFortran_;
  bool         reconnaitChainesC_;
  bool         reconnaitChainesFortran_;

  string       dernierLexeme_;
  int          dernierType_;
  int          dernierEntier_;
  double       dernierReel_;
  string       dernierNom_;
  string       derniereChaineC_;
  string       derniereChaineFortran_;
  char         dernierSeparateur_;
  char         derniereParenthese_;
  char         dernierOperateur_;

  void analyseReelOuEntier  ();
  void analyseEntier        ();
  void analyseChaineC       ();
  void analyseChaineFortran ();

};

#endif

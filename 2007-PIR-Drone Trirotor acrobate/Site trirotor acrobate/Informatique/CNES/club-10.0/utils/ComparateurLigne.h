///////////////////////////////////////////////////////////////////////////////
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
//>       ComparateurLigne.h
//$Resume
//       fichier d'en-t�te de la classe ComparateurLigne
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class ComparateurLigne
//>       inline int max()      
//>       inline int min()      
//$Historique
//       $Log: ComparateurLigne.h,v $
//       Revision 1.9  2001/04/04 11:28:24  club
//       ajout de la reconnaissance des r�els du langage fortran
//
//       Revision 1.8  2001/02/16 12:24:27  club
//       remplacement de l'inclusion de map.h par l'inclusion de map
//
//       Revision 1.7  2000/10/25 10:05:15  club
//       correction du nom du chemin vers le fichier d'en-t�te ClubConfig.h
//
//       Revision 1.6  2000/10/25 09:00:38  club
//       modification du r�pertoire pour l'include ClubConfig.h
//
//       Revision 1.5  2000/10/24 14:16:04  club
//       utilisation de tests de configuration pour les includes.
//
//       Revision 1.4  2000/10/23 13:56:05  club
//       modification de l'initialisation des cha�nes nomFichierRes et nomFichierRef
//       pour coriger un bug.
//
//       Revision 1.3  2000/09/07 08:42:02  club
//       utilisation de string de la STL au lieu de ChaineSimple conform�ment
//       aux �volutions r�alis�es sur les classes de l'interface publique de club.
//
//       Revision 1.2  2000/08/03 08:32:23  club
//       utilisation d'un code de retour plut�t que la lev�e d'une exception
//       pour la fonction analyserLigne.
//
//       Revision 1.1  2000/07/26 09:48:06  club
//       Suite � la destruction du r�pertoire club/utils/club, d�placement
//       des fichiers .h dans le r�pertoire club/utils.
//
//       Revision 1.3  2000/07/26 07:30:03  club
//       modification profonde de la classe ComparateurLigne pour simplifier
//       et am�liorer la comparaison et l'analyse de deux lignes.
//       Dans la classe interne AnalyseurLexicalDifference, suppression de
//       l'attribut nbLexemes_ et modification de la m�thode fournissant
//       le nombre de lex�mes.
//
//       Revision 1.2  2000/07/07 09:50:33  club
//       ajout de la m�thode formaterMessage permettant de cr�er
//       le message de diff�rence
//
//       Revision 1.1  2000/07/03 09:26:23  club
//       cr�ation d'une classe fournissant des services pour comparer de
//       lignes d'un fichier tout en acceptant une impr�cision num�rique.
//       cette classe est utilis�e par l'utilitaire difference
//
//$Version
//       $Id: ComparateurLigne.h,v 1.9 2001/04/04 11:28:24 club Exp $
//
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_ComparateurLigne_h
#define __club_ComparateurLigne_h

#include <club/ClubConfig.h>
#include <ClubConfigNoInstall.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#ifdef HAVE_STL
#include <map>
#include <string>
#endif

#include "StatDifference.h"

#include "club/AnalyseurLexical.h"
#include "club/ClubErreurs.h"
#include "club/Traducteur.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ComparateurLigne
//$Resume
//       classe permettant de comparer une ligne d'un fichier r�sultat avec
//       une ligne d'un fichier r�f�rence
//
//$Description
//       Cette classe permet de comparer deux lignes en acceptant une
//       imprecision num�rique sur les r�els. Elle permet de formater
//       un message de diff�rence concernant la ligne et elle met � jour des
//       statistiques sur les diff�rences. Il est possible de recaler
//       les tampons si certaines lignes sont propres � un seul d'entre eux.
//       L'algorithme utilis� pour conna�tre quelles sont les lignes communes,
//       propres � un fichier ou propres � l'autre s'inspire de l'algorithme
//       "Longest Common Subsequence". Cet algorithme est fourni � l'adresse 
//       suivante valide au 24/07/2000 :
//          http://www.ics.uci.edu/~eppstein/161/960229.html
//       L'algorithme utilis� ne permet pas forc�ment d'avoir la plus longue
//       s�quence commune mais permet de facon simple de s'en approcher voire
//       de la trouver.
// 
//$Usage
//>     construction : 
//          � partir de deux noms de fichiers et d'une valeur indiquant la 
//          pr�cision num�rique souhait�e
//>     utilisation  : 
//>       void initialiser           () 
//          apr�s la cr�ation de l'instance, cette m�thode permet d'initialiser
//          les analyseurs lexicaux avec des chaines de caract�res fournies
//          en param�tres.
//>       int analyserLigne          ()
//          permet de comparer les deux lignes et si n�cessaire de repositionner
//          les analyseurs lexicaux si certains lex�mes ne sont que dans une
//          des deux lignes. Retourne le nombre de diff�rences entre
//          les deux lignes.
//>       bool comparerLigne         ()
//          compare la ligne res avec la ligne ref. Retourne true si les lignes
//          sont �gales, false sinon. 
//
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


class ComparateurLigne
{

public :

  // constructeur
  ComparateurLigne (const string& fichierRes, const string& fichierRef, 
                    double precision)
    : nomFichierRes_ (fichierRes.c_str ()), nomFichierRef_ (fichierRef.c_str ()),
      alres_ (" "), alref_ (" "), precision_ (precision)
  {
    alres_.autoriseReelsFortran ();
    alref_.autoriseReelsFortran ();
  }

  // initialise le comparateur de lignes avec les lignes cres et cref.
  void initialiser (const string& cres, int numLigneRes,
                    const string& cref, int numLigneRef);

  // comparaisons des lex�mes de alres_ et alref_ par une m�thode gloutonne
  int analyserLigne (StatDifference& stats);

  // fonction permettant de comparer la ligne de alres_ avec celle de alref_
  // Retourne true si les lignes sont �gales, false sinon.
  bool comparerLigne ();

  // retourne la chaine messageDiff_
  const string& messageDiff () const
  { return messageDiff_; }

private :

  // calcul les positions dans le fichier res et ref des deux premiers 
  // lex�mes �gaux en favorisant des positions proches. C'est � dire que
  // si les 1er et 2�me lex�mes de res sont �gaux au 3�me lex�me de ref,
  // la fonction retournera numeroRes = 2 et numeroRef = 3.
  void lexemesSuivantsIdentiques (int& numeroRes, int& numeroRef);

  // m�thode permettant de formater le message de diff�rence
  void formaterMessage (int index, double diff);

  // compare les lex�mes courants en acceptant une diff�rence num�rique
  // Retourne :
  //  - 0 : si les lex�mes sont �gaux
  //  - 1 : si les lex�mes sont des chaines de caract�res diff�rentes
  //  - 2 : si les lex�mes sont deux entiers diff�rents
  //  - 3 : si les lex�mes sont des valeurs num�riques diff�rentes
  int comparerLexeme (double& diff);

  // classe d�riv�e de AnalyseurLexical ajoutant la notion de
  // valeur num�rique (englobe entier et reel) et fournissant le nombre
  // de lex�mes analys�s
  class AnalyseurLexicalDifference : public AnalyseurLexical
  {
    double derniereValeurNumerique_;
    
  public :
    
    // constructeur
    AnalyseurLexicalDifference (const string& c) : 
      AnalyseurLexical (c)
    {};
    
    // mise a jour
    void majValeurNumerique (double x) { derniereValeurNumerique_ = x; }
    
    // lecture
    int nbLexemes ()
    {
      redemarre ();
      int nbLexemes = 0;
      while (suivant () != codeFin)
        nbLexemes++;
      return nbLexemes; 
    }

    double valeurNumerique () const { return derniereValeurNumerique_; }    
  };

  // noms du fichier r�sultat et du fichier r�f�rence que l'on compare
  string nomFichierRes_;
  string nomFichierRef_;

  // analyseurs lexicaux pour comparer la ligne du fichier res par rapport
  // � celle du fichier ref
  AnalyseurLexicalDifference alres_;
  AnalyseurLexicalDifference alref_;

  // chaines contenant le texte de toute la ligne � analyser
  string ligneRes_;
  string ligneRef_;

  // num�ro de la ligne analys�e dans le fichier
  int numeroLigneRes_;
  int numeroLigneRef_;

  // pr�cision des calculs souhait�e
  double precision_;

  // message de diff�rence sur la ligne
  string messageDiff_;
};

// calcule le maximum de deux entiers
inline int max (int i, int j) { return ((i<j) ? j : i); }

// calcule le minimum de deux entiers
inline int min (int i, int j) { return ((i<j) ? i : j); }

#endif

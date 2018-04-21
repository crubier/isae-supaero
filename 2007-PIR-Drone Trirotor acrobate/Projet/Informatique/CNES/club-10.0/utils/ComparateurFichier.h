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
//>       ComparateurFichier.h
//$Resume
//       fichier d'en-t�te de la classe ComparateurFichier
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class ComparateurFichier
//$Historique
//       $Log: ComparateurFichier.h,v $
//       Revision 1.7  2000/10/25 10:05:15  club
//       correction du nom du chemin vers le fichier d'en-t�te ClubConfig.h
//
//       Revision 1.6  2000/10/25 09:00:38  club
//       modification du r�pertoire pour l'include ClubConfig.h
//
//       Revision 1.5  2000/10/24 14:16:04  club
//       utilisation de tests de configuration pour les includes.
//
//       Revision 1.4  2000/09/07 08:42:02  club
//       utilisation de string de la STL au lieu de ChaineSimple conform�ment
//       aux �volutions r�alis�es sur les classes de l'interface publique de club.
//
//       Revision 1.3  2000/08/04 09:45:46  club
//       calcul et affichage du d�calage maximal rencontr�.
//
//       Revision 1.2  2000/07/28 13:07:14  club
//       modification de la signature du constructeur pour permettre la prise
//       en compte de l'option pour ignorer des lignes du fichier de r�f�rence.
//
//       Revision 1.1  2000/07/26 09:48:06  club
//       Suite � la destruction du r�pertoire club/utils/club, d�placement
//       des fichiers .h dans le r�pertoire club/utils.
//
//       Revision 1.3  2000/07/26 07:30:56  club
//       modification profonde de la classe pour permettre l'implantation
//       de l'algorithme "Longest Common Subsequence" dans l'analyse des
//       fichiers : ajout de l'attribut tabLCS_, modification du constructeur,
//       cr�ation d'un destructeur et suppression de la m�thode repositionner ...
//
//       Revision 1.2  2000/07/07 09:51:20  club
//       suppression de lam�thode initialise et de l'attribut lignesDifferentes_.
//       Remplacement de leur utilit� algorithmique dans le repositionnement
//       par numPremieresLignesEgales.
//
//       Revision 1.1  2000/07/03 09:27:36  club
//       cr�ation d'une classe permettant de comparer deux fichiers tout en
//       acceptant une impr�cision num�rique.
//       cette classe est utilis� par l'utilitaire difference
//
//$Version
//       $Id: ComparateurFichier.h,v 1.7 2000/10/25 10:05:15 club Exp $
//
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


#ifndef __club_ComparateurFichier_h
#define __club_ComparateurFichier_h

#include <club/ClubConfig.h>
#include <ClubConfigNoInstall.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#ifdef HAVE_STL
#include <string>
#endif

#include "StatDifference.h"
#include "ComparateurLigne.h"

#include "club/ClubErreurs.h"
#include "club/TamponTexte.h"
#include "club/Traducteur.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class ComparateurFichier
//$Resume
//       classe permettant de comparer un fichier r�sultat avec
//       un fichier r�f�rence
//
//$Description
//       Cette classe permet de comparer deux fichiers en acceptant une
//       imprecision num�rique sur les r�els. Elle permet de formater
//       un message de diff�rence concernant chaque ligne et elle met � jour 
//       des statistiques sur les diff�rences. Il est possible de recaler
//       les tampons si certaines lignes sont propres � un seul d'entre eux.
//       L'algorithme utilis� pour conna�tre quelles sont les lignes communes,
//       propres � un fichier ou propres � l'autre est appel� "Longest Common
//       Subsequence". Cet algorithme est fourni � l'adresse suivante valide 
//       au 24/07/2000 :
//          http://www.ics.uci.edu/~eppstein/161/960229.html
//
//$Usage
//>     construction : 
//          � partir de deux noms de fichiers, d'une valeur indiquant la 
//          pr�cision num�rique souhait�e, du d�calage maximal tol�r� et 
//          du nombre de lignes au d�but et � la fin du fichier res qu'il faut
//          ignorer. Le constructeur cr�e des tampons texte contenant 
//          le texte des fichiers
//>     utilisation : 
//>       void analyserFichier     () 
//          analyse les deux fichiers ligne par ligne et permet si n�cessaire
//          de sauter des lignes propres � un seul des deux fichiers.
//>       int decalageRencontreMax ()
//          retourne la valeur maximale du d�calage rencontr� 
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////



class ComparateurFichier
{
public :

  // constructeur
  ComparateurFichier (const string& fichierRes, const string& fichierRef, 
                      double precision, int decalageMax, int suppLignesResDebut, 
                      int suppLignesResFin, int suppLignesRefDebut, 
                      int suppLignesRefFin) throw (ClubErreurs, bad_alloc);
  
  // destructeur
  ~ComparateurFichier ();

  // comparaisons des tampons tamponRes_ et tamponRef_
  void analyserFichier (StatDifference& stats) throw (ClubErreurs);

  int decalageRencontreMax () const { return decalageRencontreMax_; }

private :

  void analyserLignesEgalesDebut (int& debutRes, const int finRes, 
                                  int& debutRef, const int finRef,
                                  StatDifference& stats);

  void analyserLignesEgalesFin (const int debutRes, int& finRes, 
                                const int debutRef, int& finRef,
                                StatDifference& stats);

  // cette m�thode priv�e permet de remplir le tableau tabLCS_ par l'algorithme 
  // "Longest Common Subsequent" de complexit� O(nbLignesRes*nbLignesRef)
  void initialiser (const int debutRes, const int finRes, 
                    const int debutRef, const int finRef);

  // noms du fichier r�sultat et du fichier r�f�rence que l'on compare
  string nomFichierRes_;
  string nomFichierRef_;

  // tampon texte contenant le texte du fichier resultat
  TamponTexte tamponRes_;
  // tampon texte contenant le texte du fichier r�f�rence
  TamponTexte tamponRef_;

  // pr�cision des calculs souhait�e (pour la comparaison des valeurs num�riques)
  double precision_;

  // valeur du d�calage maximal tol�r� pour le repositionnement des analyseurs
  int decalageMax_;
  int decalageRencontreMax_;

  // nombre de lignes � ne pas analyser au d�but et � la fin du tampon r�sultat
  int suppLignesResDebut_;
  int suppLignesResFin_;

  // nombre de lignes � ne pas analyser au d�but et � la fin du tampon r�f�rence
  int suppLignesRefDebut_;
  int suppLignesRefFin_;

  // tableau de taille � 2 dimensions utilis�s pour stock�s les r�sultats 
  // du calcul de la "Longest Common Subsequence"
  int** tabLCS_;
};

#endif

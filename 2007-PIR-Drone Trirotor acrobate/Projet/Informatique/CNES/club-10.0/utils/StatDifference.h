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
//>       StatDifference.h
//$Resume
//       fichier d'en-t�te de la classe StatDifference
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class StatDifference
//$Historique
//       $Log: StatDifference.h,v $
//       Revision 1.8  2001/02/16 12:23:56  club
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
//       Revision 1.4  2000/08/04 09:45:46  club
//       calcul et affichage du d�calage maximal rencontr�.
//
//       Revision 1.3  2000/08/03 08:34:29  club
//       modification de la m�thode majMessagesAffiches :
//       dans le cas o� nbMessagesMax = 0, affectation de 0 � messagesAffiches_ [0]
//       et messagesAffiches_ [1].
//       Modification du constructeur : affectation de 0 � messagesAffiches_ [0].
//
//       Revision 1.2  2000/07/28 13:03:56  club
//       Modification de la signature de afficherSynthese : on passe en
//       argument de la fonction la valeur du seuil max tol�r�.
//
//       Revision 1.1  2000/07/26 09:48:06  club
//       Suite � la destruction du r�pertoire club/utils/club, d�placement
//       des fichiers .h dans le r�pertoire club/utils.
//
//       Revision 1.4  2000/07/26 07:28:14  club
//       ajout des attributs nbErrNonAccepteesNumeriques_, afficherMessages_
//       et afficherSynthese_ permettant de fournir les services aux nouvelles
//       options de la ligne de commande (rsynth, rmess).
//       Cr�ation des accesseurs � ces attributs
//
//       Revision 1.3  2000/07/07 09:49:54  club
//       cr�ation des fonctions permettant de calculer les statistiques
//       sur les diff�rences num�riques.
//       modification de l'attribut nbMessagesDiffMax_  en un tableau � deux
//       �l�ments qui indiquent l'intervalle des messages � afficher
//
//       Revision 1.2  2000/07/06 07:31:19  club
//       modification de l'attribut nbMessagesDiffMax_ (repr�sentant le
//       nombre maximal de messages de diff�rence � afficher) en un tableau
//       � deux �l�ments qui indiquent respectivement le num�ro du premier
//       et le num�ro du dernier message � afficher
//
//       Revision 1.1  2000/07/03 09:28:23  club
//       cr�ation d'une classe permettant de g�rer toutes les statistiques
//       n�cessaires � l'utilitaire difference
//
//$Version
//       $Id: StatDifference.h,v 1.8 2001/02/16 12:23:56 club Exp $
//
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////


#ifndef __club_StatDifference_h
#define __club_StatDifference_h

#include <club/ClubConfig.h>
#include <ClubConfigNoInstall.h>

#if CLUB_HAVE_NAMESPACES
using namespace std;
#endif

#ifdef HAVE_STL
#include <map>
#endif

#include "club/ClubErreurs.h"
#include "club/Traducteur.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class StatDifference
//$Resume
//      classe g�rant toutes les statistiques utiles � l'utilitaire difference
//
//$Description
//      Cette classe fournit des m�thodes permettant de g�rer les statistiques
//      de difference (valeur de l'erreur num�rique max, ...). Elle permet
//      �galement de compter le nombre de messages de diff�rences affich�s et
//      d'afficher des statistiques sur les diff�rences num�riques rencontr�es.
//
//$Usage
//>     construction : 
//        sans argument
//>     utilisation  : 
//>       bool traiterDifference              () 
//          permet d'afficher un message de diff�rence si le num�ro de ce
//          message appartient � l'intervalle des messages � afficher.
//>       void afficherSynthese               () 
//          affiche la synth�se statistique de l'analyse des fichiers
//>       void majAfficherMessages            () 
//          met � jour le bool�en indiquant si l'utilisateur souhaite afficher
//          les messages de diff�rence
//>       void majAfficherSynthese            () 
//          met � jour le bool�en indiquant si l'utilisateur souhaite afficher
//          la synth�se de l'analyse
//>       void majMessagesAffiches            () 2 signatures - 
//          met � jour l'intervalle des num�ros de messages de diff�rences 
//          � afficher
//>       void majNbErrAcceptees              () 
//          met � jour le nombre d'erreurs accept�es
//>       void majNbErrNonAcceptees           () 
//          met � jour le nombre d'erreurs non accept�es
//>       void majNbErrNonAccepteesNumeriques () 
//          met � jour le nombre d'erreurs num�riques non accept�es
//>       void majDifferencesNumeriques       () 
//          met � jour le tableau contenant les valeurs des diff�rences
//          num�riques
//>       int nbErrNonAcceptees               () 
//          retourne le nombre d'erreurs non accept�es
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//$<>
///////////////////////////////////////////////////////////////////////////////


class StatDifference
{
public :

  StatDifference () : nbErrNonAcceptees_ (0), nbErrNonAccepteesNumeriques_ (0),
                      nbErrAcceptees_ (0), nbMessagesDiffFini_ (false), 
                      nbErrAffichees_ (0), nbDifferencesNumeriques_ (0), 
                      afficherMessages_ (true), afficherSynthese_ (true)
  {
    messagesAffiches_ [0] = 0;
    messagesAffiches_ [1] = 0;
  };
  
  // mise a jour 

  void majAfficherMessages (const bool x) { afficherMessages_ = x; }
  void majAfficherSynthese (const bool x) { afficherSynthese_ = x; }

  void majMessagesAffiches (const int nbMessagesMax) 
  { 
    nbMessagesDiffFini_ = true;

    if (nbMessagesMax > 0)
    {
      messagesAffiches_ [0] = 1;
      messagesAffiches_ [1] = nbMessagesMax;
    }
    else
    {
      messagesAffiches_ [0] = 0;
      messagesAffiches_ [1] = 0;
    }
  }

  void majMessagesAffiches (const int nbMessagesMin, const int nbMessagesMax) 
  { 
    nbMessagesDiffFini_ = true;
    messagesAffiches_ [0] = nbMessagesMin;
    messagesAffiches_ [1] = nbMessagesMax;
  }

  void majNbErrAcceptees () { nbErrAcceptees_++; }
  void majNbErrNonAcceptees () { nbErrNonAcceptees_++; }
  void majNbErrNonAccepteesNumeriques () { nbErrNonAccepteesNumeriques_++; }

  void majDifferencesNumeriques (const double diff)
  {
    nbDifferencesNumeriques_++;
    differencesNumeriques_ [nbDifferencesNumeriques_] = diff;
  }

  // lecture
  int nbErrNonAcceptees () const { return nbErrNonAcceptees_; }

  // fonction permettant :
  //   - d'incr�menter le nombre de messages affich�s, 
  //   - d'autoriser l'affichage de message si le num�ro du message appartient
  //     � l'intervalle messagesAffiches_
  bool traiterDifference ();

  // fonction permettant d'afficher les r�sultats finaux
  void afficherSynthese (const double precision, const int decalage);

private :

  void calculerStat (double& errMinRelative, double& errMaxRelative,
                     double& moyenne);

  int nbErrNonAcceptees_;
  int nbErrNonAccepteesNumeriques_;
  int nbErrAcceptees_;

  int messagesAffiches_ [2];
  bool nbMessagesDiffFini_;
  int nbErrAffichees_;

  map<int,double> differencesNumeriques_;
  int nbDifferencesNumeriques_;

  bool afficherMessages_;
  bool afficherSynthese_;
};

#endif

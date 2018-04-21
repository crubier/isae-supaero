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
//>       ComparateurFichier.cpp
//$Resume
//       fichier d'implantation de la classe ComparateurFichier
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       inline const char* trad()
//>       class ComparateurFichier   
//>         ComparateurFichier()
//>         ~ComparateurFichier()
//>         initialiser()
//>         analyserLignesEgalesDebut()
//>         analyserLignesEgalesFin()
//>         analyserFichier()        
//$Historique
//       $Log: ComparateurFichier.cpp,v $
//       Revision 1.10  2003/02/03 14:45:56  club
//       DM-ID 17 Mise � jour de l'extensions du fichier dans le bandeau
//
//       Revision 1.9  2001/02/16 12:25:20  club
//       ajout d'un typedef pour aider le compilateur SUN
//
//       Revision 1.8  2000/09/07 08:42:02  club
//       utilisation de string de la STL au lieu de ChaineSimple conform�ment
//       aux �volutions r�alis�es sur les classes de l'interface publique de club.
//
//       Revision 1.7  2000/08/04 09:45:45  club
//       calcul et affichage du d�calage maximal rencontr�.
//
//       Revision 1.6  2000/08/03 08:33:04  club
//       suppression du catch permettant de r�cup�rer le message de diff�rence
//       (s'il y en a une). Utilisation � la place d'un test sur la valeur de retour
//       de la fonction analyserLigne.
//
//       Revision 1.5  2000/07/28 13:06:05  club
//       Mise en place de l'option permettant de sauter les lignes du fichier
//       de r�f�rence dans le traitement et le constructeur.
//
//       Revision 1.4  2000/07/26 09:49:13  club
//       Modification des #include suite au d�placement des fichiers .h dans
//       le r�pertoire club/utils.
//
//       Revision 1.3  2000/07/26 07:34:53  club
//       modification profonde des m�thodes de la classe pour mettre
//       en place l'algorithme de "Longest Common Subsequence".
//
//       Revision 1.2  2000/07/07 12:12:16  club
//       am�lioration de l'algorithme de la fonction permettant de se repositionner.
//       suppression de la fonction initialise ().
//
//       Revision 1.1  2000/07/03 09:38:36  club
//       cr�ation de cette classe permettant de comparer deux fichiers tout en
//       acceptant une impr�cision num�rique
//
//$Version
//       $Id: ComparateurFichier.cpp,v 1.10 2003/02/03 14:45:56 club Exp $
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "ComparateurFichier.h"


// permet de traduire les messages de diff�rence
inline const char* trad (const char* s) { return TraduitFormatCVersExterne (s); }

// constructeur
ComparateurFichier::ComparateurFichier (const string& fichierRes, 
                                        const string& fichierRef, 
                                        double precision, int decalageMax,
                                        int suppLignesResDebut, int suppLignesResFin,
                                        int suppLignesRefDebut, int suppLignesRefFin) 
  throw (ClubErreurs, bad_alloc) : nomFichierRes_ (fichierRes), nomFichierRef_ (fichierRef),
                                   tamponRes_ (0), tamponRef_ (0), precision_ (precision), 
                                   decalageMax_ (decalageMax), decalageRencontreMax_ (0)
{
  // initialisation des tampons texte avec les lignes des fichiers res ou ref
  tamponRes_.lit (nomFichierRes_.c_str (), 0);
  tamponRef_.lit (nomFichierRef_.c_str (), 0);

  int nbLignesRes = tamponRes_.nombreLignes ();
  if (nbLignesRes < (suppLignesResDebut+suppLignesResFin))
  {
    char message[1024];
    (void) sprintf (message, trad ("le nombre de lignes a ignorer (%d) est superieur "
                                   "au nombre total de lignes (%d) du fichier %s"),
                    suppLignesResDebut+suppLignesResFin,
                    nbLignesRes, nomFichierRes_.c_str ());
    throw ClubErreurs (ClubErreurs::message_simple, message);
  }

  int nbLignesRef = tamponRef_.nombreLignes ();
  if (nbLignesRef < (suppLignesRefDebut+suppLignesRefFin))
  {
    char message[1024];
    (void) sprintf (message, trad ("le nombre de lignes a ignorer (%d) est superieur "
                                   "au nombre total de lignes (%d) du fichier %s"),
                    suppLignesRefDebut+suppLignesRefFin,
                    nbLignesRef, nomFichierRef_.c_str ());
    throw ClubErreurs (ClubErreurs::message_simple, message);
  }

  suppLignesResDebut_ = suppLignesResDebut;
  suppLignesResFin_ = suppLignesResFin;
  suppLignesRefDebut_ = suppLignesRefDebut;
  suppLignesRefFin_ = suppLignesRefFin;

  typedef int *intPtr;
  tabLCS_ = new intPtr [decalageMax_+2];
  for (int i=0 ; i<decalageMax_+2 ; i++)
    tabLCS_[i] = new (int [decalageMax_+2]);
};


// destructeur
ComparateurFichier::~ComparateurFichier ()
{
  for (int i=0 ; i<decalageMax_+1 ; i++)
    delete tabLCS_[i];
  delete tabLCS_;
}


// initialisation du tableau tabLCS_ � partir des lignes debutRes et debutRef
// Cette m�thode utilise l'algorithme de "Longest Common Subsequence" d�crit
// � l'adresse http://www.ics.uci.edu/~eppstein/161/960229.html (cette r�f�rence
// est valide au 24/07/2000). Cette m�thode calcule la s�quence commune la plus
// longue sur un nombre r�duit de lignes (au maximum decalageMax_) pour �viter
// des places m�moires trop importantes et un temps de calcul trop grand.

void ComparateurFichier::initialiser (const int debutRes, const int finRes, 
                                      const int debutRef, const int finRef)
{
  ComparateurLigne cmpLigne (nomFichierRes_, nomFichierRef_, precision_);

  int maxRes = min (finRes, decalageMax_+debutRes);
  int maxRef = min (finRef, decalageMax_+debutRef);

  for (int i=debutRes ; i<= maxRes+1 ; i++)
    tabLCS_ [i-debutRes][maxRef-debutRef+1] = 0;
  for (int i=debutRef ; i<= maxRef+1 ; i++)
    tabLCS_ [maxRes-debutRes+1][i-debutRef] = 0;

  for (int i=maxRes ; i>=debutRes ; i--)
  {
    for (int j=maxRef ; j>=debutRef ; j--)
    {
      cmpLigne.initialiser (tamponRes_.ligne (i), 0, tamponRef_.ligne (j), 0);

      if (cmpLigne.comparerLigne ())
        tabLCS_[i-debutRes][j-debutRef] = 1 + tabLCS_[i+1-debutRes][j+1-debutRef];
      else
        tabLCS_[i-debutRes][j-debutRef] = max (tabLCS_[i+1-debutRes][j-debutRef], 
                                               tabLCS_[i-debutRes][j+1-debutRef]);
    }
  }
}


// analyse de toutes les premi�res lignes �gales. Modifie debutRes et debutRef.
void ComparateurFichier::analyserLignesEgalesDebut (int& debutRes, const int finRes, 
                                                    int& debutRef, const int finRef,
                                                    StatDifference& stats)
{
  ComparateurLigne cmpLigne (nomFichierRes_, nomFichierRef_, precision_);

  while ((debutRes <= finRes) && (debutRef <= finRef))
  {
    // initialisation du comparateur de lignes avec la premi�re ligne
    // de chaque tampon
    cmpLigne.initialiser (tamponRes_.ligne (debutRes), debutRes, 
                           tamponRef_.ligne (debutRef), debutRef);
    if (cmpLigne.comparerLigne ())
    {
      // les lignes sont identiques
      // on analyse les lignes pour mettre � jour les statistiques
      cmpLigne.analyserLigne (stats);
      
      // on incr�mente le num�ro de la premi�re ligne de chaque tampon
      debutRes++; debutRef++;
    }
    else
      break;
  }
}

// analyse de toutes les derni�res lignes �gales. Modifie finRes et finRef.
void ComparateurFichier::analyserLignesEgalesFin (const int debutRes, int& finRes, 
                                                  const int debutRef, int& finRef,
                                                  StatDifference& stats)
{
  ComparateurLigne cmpLigne (nomFichierRes_, nomFichierRef_, precision_);

  while ((debutRes <= finRes) && (debutRef <= finRef))
  {
    // initialisation du comparateur de lignes avec la derni�re ligne
    // de chaque tampon
    cmpLigne.initialiser (tamponRes_.ligne (finRes), finRes, 
                           tamponRef_.ligne (finRef), finRef);
    if (cmpLigne.comparerLigne ())
    {
      // les lignes sont identiques
      // on analyse les lignes pour mettre � jour les statistiques
      cmpLigne.analyserLigne (stats);

      // on d�cr�mente le num�ro de la derni�re ligne de chaque tampon
      finRes--; finRef--;
    }
    else
      break;
  }
}


// analyse des deux fichiers
void ComparateurFichier::analyserFichier (StatDifference& stats) throw (ClubErreurs)
{
  char messageDiff[1024];
  ComparateurLigne cmpLigne (nomFichierRes_, nomFichierRef_, precision_);

  // num�ros des premi�res lignes de chaque tampon
  int debutRes = suppLignesResDebut_+1;
  int debutRef = suppLignesRefDebut_+1;
  // num�ros des derni�res lignes de chaque tampon
  int finRes = tamponRes_.nombreLignes () - suppLignesResFin_;
  int finRef = tamponRef_.nombreLignes () - suppLignesRefFin_;
  // indices indiquant le nombre de lignes du tampon res et ref qui ont
  // �t� d�cal�es.
  int indiceRes = 0;
  int indiceRef = 0;
  // num�ro de la premi�re ligne res et ref utilis� pour le calcul de tabLCS_.
  int iRes = 0;
  int iRef = 0;

  int decalage = 0;

  bool recalculerTabLCS = true;

  // analyse des premi�res et derni�res lignes communes aux deux tampons 
  analyserLignesEgalesDebut (debutRes, finRes, debutRef, finRef, stats);
  analyserLignesEgalesFin (debutRes, finRes, debutRef, finRef, stats);

  // tant qu'un des deux tampons n'est pas �puis�
  while ((debutRes <= finRes) && (debutRef <= finRef))
  {
    // calcul de TabLCS_
    if (recalculerTabLCS)
    {
      // calcul de tabLCS_ � partir de debutRes et debutRef
      initialiser (debutRes, finRes, debutRef, finRef);
      iRes = debutRes;
      iRef = debutRef;

      // si aucunes lignes sont �gales
      if (tabLCS_[0][0] == 0)
      {
        // si on n'est pas proche de la fin d'un des deux tampons texte
        if ((debutRes+decalageMax_<finRes) && (debutRef+decalageMax_<finRef))
        {
          decalageRencontreMax_ = decalageMax_;

          char message[1024];
          (void) sprintf (message, trad ("les fichiers sont trop differents : "
                                         "plus de %d lignes separent deux lignes egales"),
                          decalageMax_);
          throw ClubErreurs (ClubErreurs::message_simple, message);
        }
        else
        {
          while ((debutRes <= finRes) && (debutRef <= finRef))
          {
            // comparer les lignes debutRes-indiceRes et debutRef-indiceRef
            cmpLigne.initialiser (tamponRes_.ligne (debutRes), debutRes, 
                                  tamponRef_.ligne (debutRef), debutRef);
            if (cmpLigne.analyserLigne (stats) != 0)
            {
              // affichage du message de diff�rence concernant les deux lignes
              if (stats.traiterDifference ())
                cerr << cmpLigne.messageDiff () << endl << endl;
            }
            debutRes++;
            debutRef++;
            decalage++;
          }

          break;
        }
      }
      recalculerTabLCS = false;
    }

    // initialisation du comparateur de lignes avec la premi�re ligne
    // de chaque tampon
    cmpLigne.initialiser (tamponRes_.ligne (debutRes), debutRes, 
                          tamponRef_.ligne (debutRef), debutRef);
    if (cmpLigne.comparerLigne ())
    {
      // si on a d�cal� le tamponRes, affichage d'un message de diff�rence 
      if (indiceRes > 0)
      {
        if (decalageRencontreMax_ < decalage)
          decalageRencontreMax_ = decalage;

        // mise � jour des statistiques
        stats.majNbErrNonAcceptees ();
        
        // affichage du message
        if (stats.traiterDifference ())
        {
          // formation du message
          (void) sprintf (messageDiff, trad ("les lignes suivantes sont en plus dans %s:"),
                          nomFichierRes_.c_str ());
          cerr << messageDiff << endl;
          
          // toutes les lignes suivantes ne sont que dans le fichier res
          for (int n = debutRes-indiceRes; n < debutRes; n++)
          {
            (void) sprintf (messageDiff, "%s,%d : %s", nomFichierRes_.c_str (), n,
                            tamponRes_.ligne (n));
            cerr << messageDiff << endl;
          }
          cerr << endl;
        }
      }
      
      // si on a d�cal� le tamponRef, affichage d'un message de diff�rence 
      if (indiceRef > 0)
      {
        if (decalageRencontreMax_ < decalage)
          decalageRencontreMax_ = decalage;

        // mise � jour des statistiques
        stats.majNbErrNonAcceptees ();

        // affichage du message
        if (stats.traiterDifference ())
        {
          // formation du message
          (void) sprintf (messageDiff, trad ("les lignes suivantes manquent dans %s,%d:"),
                          nomFichierRes_.c_str (), debutRes);
          cerr << messageDiff << endl;
          
          // toutes les lignes suivantes ne sont que dans le fichier ref
          for (int n = debutRef-indiceRef; n < debutRef; n++)
          {
            (void) sprintf (messageDiff, "%s,%d : %s", nomFichierRef_.c_str (), n,
                            tamponRef_.ligne (n));
            cerr << messageDiff << endl;
          }
          cerr << endl;
        }
      }
      
      indiceRes = 0;
      indiceRef = 0;
      decalage = 0;
      
      analyserLignesEgalesDebut (debutRes, finRes, debutRef, finRef, stats);

      recalculerTabLCS = true;
    }
    
    else 
    {
      if (tabLCS_ [debutRes-iRes+1][debutRef-iRef] > tabLCS_ [debutRes-iRes][debutRef-iRef+1])
      {
        // d�calage du tamponRes
        debutRes++;
        indiceRes++;
        decalage++;
      }
      
      else
      {
        // d�calage du tamponRef
        debutRef++;
        indiceRef++;
        decalage++;
      }

      // si les deux tampons ont �t� d�cal�s, affichage d'un message de diff�rence
      // entre une ligne de tamponRes et une ligne de tamponRef
      while ((indiceRes > 0) && (indiceRef > 0))
      {
        // comparer les lignes debutRes-indiceRes et debutRef-indiceRef
        cmpLigne.initialiser (tamponRes_.ligne (debutRes-indiceRes), debutRes-indiceRes, 
                              tamponRef_.ligne (debutRef-indiceRef), debutRef-indiceRef);

        // comparaison des lignes et mise � jour des statistiques
        if (cmpLigne.analyserLigne (stats) != 0)
        {
          // affichage du message de diff�rence concernant les deux lignes
          if (stats.traiterDifference ())
            cerr << cmpLigne.messageDiff () << endl << endl;
        }

        indiceRes--;
        indiceRef--;
        decalage--;
      }
    }
  }

  // au moins un des deux fichiers est arriv� au bout
  // s'il reste des lignes dans le fichier r�sultat, on affiche un message
  // de diff�rence
  if (debutRes <= finRes)
  {
    //  mise � jour des statistiques
    stats.majNbErrNonAcceptees ();

    // toutes les lignes qui suivent sont en plus
    if (stats.traiterDifference ())
    {
      // formation du message
      (void) sprintf (messageDiff, trad ("les lignes suivantes sont en plus dans %s:"),
                      nomFichierRes_.c_str ());
      cerr << messageDiff << endl;

      while (debutRes <= finRes)
      {
        (void) sprintf (messageDiff, "%s,%d : %s", nomFichierRes_.c_str (), debutRes,
                        tamponRes_.ligne (debutRes));
        cerr << messageDiff << endl;
        debutRes++;
        decalage++;
      }
      cerr << endl;
    }
    
    if (decalage > decalageRencontreMax_)
      decalageRencontreMax_ = decalage;
  }

  // s'il reste des lignes dans le fichier r�f�rence, on affiche un message
  // de diff�rence
  else if (debutRef <= finRef)
  {
    stats.majNbErrNonAcceptees ();

    // toutes les lignes qui suivent sont en plus
    if (stats.traiterDifference ())
    {
      // formation du message
      (void) sprintf (messageDiff, trad ("les lignes suivantes manquent dans %s,%d:"),
                      nomFichierRes_.c_str (),debutRes);
      cerr << messageDiff << endl;

      while (debutRef <= finRef)
      {
        (void) sprintf (messageDiff, "%s,%d : %s", nomFichierRef_.c_str (), debutRef,
                        tamponRef_.ligne (debutRef));
        cerr << messageDiff << endl;        
        debutRef++;
        decalage++;
      }
      cerr << endl;
    }    
    
    if (decalage > decalageRencontreMax_)
      decalageRencontreMax_ = decalage;
  }
}

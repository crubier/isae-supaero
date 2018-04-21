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
//>       difference.cpp
//$Resume
//       fichier d'implantation de l'utilitaire difference
//
//$Description
//       l'utilitaire difference permet de r�pertorier les diff�rences entre
//       deux fichiers tout en acceptant une impr�cision num�rique d�e par 
//       exemple � un changement de plateforme. D'autre part, le but de cet
//       utilitaire est de produire des messages plus explicites que ceux de
//       la fonction syst�me diff, et d'offrir des m�canismes de traduction
//       de ces messages.
//
//$Contenu
//>       inline const char* trad()
//>       void analyserArguments() 
//>       int main()               
//$Historique
//       $Log: difference.cpp,v $
//       Revision 1.13  2003/02/03 14:45:25  club
//       DM-ID 17 Mise � jour de l'extensions du fichier dans le bandeau
//
//       Revision 1.12  2000/10/18 17:22:06  club
//       la valeur minimale de l'option shift passe � 0.
//
//       Revision 1.11  2000/09/07 08:42:03  club
//       utilisation de string de la STL au lieu de ChaineSimple conform�ment
//       aux �volutions r�alis�es sur les classes de l'interface publique de club.
//
//       Revision 1.10  2000/08/04 09:45:46  club
//       calcul et affichage du d�calage maximal rencontr�.
//
//       Revision 1.9  2000/08/03 08:35:11  club
//       protection contre l'utilisation de l'option -ee avec une premi�re
//       valeur sup�rieure � la seconde.
//
//       Revision 1.8  2000/07/28 13:01:49  club
//       Am�lioration des valeurs par d�faut et limites des options de la ligne
//       de commande. G�n�ralisation de l'option permettant d'ignorer des lignes
//       au fichier de r�f�rence.
//
//       Revision 1.7  2000/07/26 09:49:13  club
//       Modification des #include suite au d�placement des fichiers .h dans
//       le r�pertoire club/utils.
//
//       Revision 1.6  2000/07/26 07:33:39  club
//       ajout d'options pour la ligne de commande.
//       modification du main suite aux changements d'interface des classes
//       ComparateurFichier et StatDifference.
//
//       Revision 1.5  2000/07/07 12:13:21  club
//       ajout de l'option -ee indiquant l'intervalle de valeurs que doivent
//       respecter les num�ros des messages de diff�rence pour �tre affich�s.
//       suppression de l'affichage de la synth�se et utilisation de la m�thode
//       afficherSynthese de la classe StatDifference.
//
//       Revision 1.4  2000/07/06 07:31:56  club
//       ajout de l'option -ee dans la ligne de commande
//
//       Revision 1.3  2000/07/03 09:44:46  club
//       modification compl�te de l'utilitaire difference :
//       suppression des appels aux fonctions syst�me
//       utilisation des services des classes ComparateurFichier et StatDifference
//
//       Revision 1.2  1999/10/12 12:05:26  club
//       am�lioration de la syntaxe et inclusion de club/difference.h
//
//       Revision 1.1  1999/10/11 09:29:23  club
//       initial revision
//
//$Version
//       $Id: difference.cpp,v 1.13 2003/02/03 14:45:25 club Exp $
//$Auteur
//       O. Queyrut CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "difference.h"


inline const char* trad (const char* s) { return TraduitFormatCVersExterne (s); }



void analyserArguments (int nombreArguments, char** arguments,
                        double* precision, int* decalageMax,
                        int* numLignesResDebut, int* numLignesResFin,
                        int* numLignesRefDebut, int* numLignesRefFin,
                        StatDifference& stats,
                        string *ptrFichierRes,
                        string *ptrFichierRef) throw (ClubErreurs)
{
  // analyse des arguments de la ligne de commande
  OptionsAppli analyseur (arguments[0]);

  // valeur du d�calage maximal accept�
  // option shift: z�ro ou une occurence, valeur par d�faut 100
  analyseur.ajouterOption (OptionEntier ("shift", 0, 1, avecValeurDefaut, 
                                         1000, 0, 5000));

  // lignes du d�but du fichier res � ne pas analyser
  // option rfres : z�ro ou une occurence, avec valeur par d�faut 0
  analyseur.ajouterOption (OptionEntier ("rfres", 0, 1, avecValeurDefaut, 0));
  
  // lignes de fin du fichier res � ne pas analyser
  // option rlres : z�ro ou une occurence, avec valeur par d�faut 0
  analyseur.ajouterOption (OptionEntier ("rlres", 0, 1, avecValeurDefaut, 0));

  // lignes du d�but du fichier ref � ne pas analyser
  // option rfref : z�ro ou une occurence, avec valeur par d�faut 0
  analyseur.ajouterOption (OptionEntier ("rfref", 0, 1, avecValeurDefaut, 0));
  
  // lignes de fin du fichier ref � ne pas analyser
  // option rlref : z�ro ou une occurence, avec valeur par d�faut 0
  analyseur.ajouterOption (OptionEntier ("rlref", 0, 1, avecValeurDefaut, 0));

  // suppression de l'affichage de la synthese
  // option rsynth : z�ro ou une occurence, avec valeur par d�faut
  analyseur.ajouterOption (OptionSansValeur ("rsynth", 0, 1));

  // suppression de l'affichage des messages de difference
  // option rmess : z�ro ou une occurence, avec valeur par d�faut
  analyseur.ajouterOption (OptionSansValeur ("rmess", 0, 1));

  // pr�cision
  // option p: z�ro ou une occurence, valeur par d�faut=0.00001
  analyseur.ajouterOption (OptionReel ("p", 0, 1, avecValeurDefaut, 0.00001, 
                                       0.0));

  // nombre maximum de messages de differences � afficher
  // option e: z�ro ou une occurence, pas de valeur par d�faut
  analyseur.ajouterOption (OptionEntier ("e", 0, 1, sansValeurDefaut));

  // num�ro des messages de diff�rence � afficher
  // option ee : z�ro ou une occurence, pas de valeur par d�faut
  analyseur.ajouterOption (OptionTableauEntiers ("ee", 0, 1, sansValeurDefaut,
                                                 2, (int *) 0, 1));

  // fichier r�f�rence
  // option ref: une occurence, pas de valeur par d�faut
  analyseur.ajouterOption (OptionChaine ("ref", 1, 1, sansValeurDefaut, "", 4096));

  // fichier r�sultat
  // option res: une occurence, pas de valeur par d�faut
  analyseur.ajouterOption (OptionChaine ("res", 1, 1, sansValeurDefaut, "", 4096));

  // analyse de la ligne
  analyseur.initialiser (nombreArguments, arguments);
  analyseur.garantirComplet ();

  // r�cup�ration des donn�es
  analyseur.lireValeur ("p", precision);
  analyseur.lireValeur ("shift", decalageMax);
  analyseur.lireValeur ("rfres", numLignesResDebut);
  analyseur.lireValeur ("rlres", numLignesResFin);
  analyseur.lireValeur ("rfref", numLignesRefDebut);
  analyseur.lireValeur ("rlref", numLignesRefFin);
  
  if (analyseur.occurrencesPassees ("rsynth") == 1)
    stats.majAfficherSynthese (false);

  if (analyseur.occurrencesPassees ("rmess") == 1)
    stats.majAfficherMessages (false);

  if ((analyseur.occurrencesPassees ("e") == 1) && 
      (analyseur.occurrencesPassees ("ee") == 1))
  {
    char tampon [1024];
    (void) sprintf (tampon, "options -e et -ee incompatibles");
    ClubErreurs::erreur (0, ClubErreurs::message_simple, tampon);
  }

  if (analyseur.occurrencesPassees ("e") == 1)
  {
    // l'utilisateur a pr�cis� un nombre maximal d'erreurs � afficher, 
    // on en tient compte
    int nbMessagesDiffMax;
    analyseur.lireValeur ("e", &nbMessagesDiffMax);
    stats.majMessagesAffiches (nbMessagesDiffMax);
  }

  else if (analyseur.occurrencesPassees ("ee") == 1)
  {
    // l'utilisateur a pr�cis� un intervalle de num�ros d'erreurs � afficher, 
    // on en tient compte
    int tableau [2];
    analyseur.lireValeur ("ee", 2, tableau);
    if (tableau [0] <= tableau [1])
      stats.majMessagesAffiches (tableau [0], tableau [1]);
    else
      stats.majMessagesAffiches (tableau [1], tableau [0]);
  }

  analyseur.lireValeur ("ref", ptrFichierRef);
  analyseur.lireValeur ("res", ptrFichierRes);
}


int main (int argc, char **argv)
{ 
  // les messages utilisent le domaine de traduction "club"
  InitDomaineClub ();
  BaseErreurs::initErreurs (0, 0, 1, 0);

  // buffer de formatage du message
  char tampon[1024];

  // recup�ration de la ligne de commande et analyse de celle-ci pour 
  // r�cup�rer le nom des fichiers dont on veut la diff�rence et la valeur de 
  // toutes les autres options

  double precision;
  int decalageMax;
  int numLignesResDebut;
  int numLignesResFin;
  int numLignesRefDebut;
  int numLignesRefFin;

  // variables pour les statistiques
  StatDifference stats; 

  string fichierRes;
  string fichierRef;

  try
  {
    analyserArguments (argc, argv, &precision, &decalageMax, &numLignesResDebut,
                       &numLignesResFin, &numLignesRefDebut, &numLignesRefFin, 
                       stats, &fichierRes, &fichierRef);
  }
  catch (ClubErreurs &ce)
  {
    cerr << ce.why () << endl;
    ce.correction ();
    return 2;
  }

  // v�rification que les fichiers de la ligne de commande existent bien
  if (access (fichierRes.c_str (), F_OK) == -1)
  {
    (void) sprintf (tampon, trad ("fichier %s inconnu"), fichierRes.c_str ());
    cerr << tampon << endl;
    return 2;
  }

  if (access (fichierRef.c_str (), F_OK) == -1)
  {
    (void) sprintf (tampon, trad ("fichier %s inconnu"), fichierRef.c_str ());
    cerr << tampon << endl;
    return 2;
  }

  try
  {
    // creation d'une instance de la classe ComparateurFichier pour 
    // realiser l'analyse des fichiers
    ComparateurFichier cmpFichier (fichierRes, fichierRef, precision, decalageMax,
                                   numLignesResDebut, numLignesResFin,
                                   numLignesRefDebut, numLignesRefFin);

    // analyse des fichiers ligne par ligne avec si necessaire saut de lignes
    // si certaines sont en plus dans un fichier
    // Cet appel permet egalement de mettre a jour les statistiques
    try
    {
      cmpFichier.analyserFichier (stats);
      
      // on retourne le resultat
      stats.afficherSynthese (precision, cmpFichier.decalageRencontreMax ());
      
      if (stats.nbErrNonAcceptees () != 0)
        return 1;
      else
        return 0;
    }
    catch (ClubErreurs& ce)
    {
      // les fichiers sont trop differents
      cerr << ce.why () << endl;
      ce.correction ();
      return 1;
    }
  }
  catch (bad_alloc l)
  {
    char message[1024];
    (void) sprintf (message, trad ("Analyse impossible : la place memoire necessaire pour le calcul "
                                   "d'un decalage de %d lignes est trop importante"), 
                    decalageMax);
    cerr << message << endl;
    return 2;
  }
  catch (ClubErreurs& ce)
  {
    // impossibilite de creer le tampon
    cerr << ce.why () << endl;
    ce.correction ();
    return 2;
  }
}

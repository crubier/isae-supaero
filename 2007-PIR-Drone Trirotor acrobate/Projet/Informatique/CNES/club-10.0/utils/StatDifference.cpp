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
//       fichier d'implantation de la classe StatDifference
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       inline const char* trad()
//>       class StatDifference
//>         traiterDifference()           
//>         calculerStat()
//>         afficherSynthese()
//$Historique
//       $Log: StatDifference.cpp,v $
//       Revision 1.10  2000/09/07 08:42:03  club
//       utilisation de string de la STL au lieu de ChaineSimple conform�ment
//       aux �volutions r�alis�es sur les classes de l'interface publique de club.
//
//       Revision 1.9  2000/08/04 09:45:46  club
//       calcul et affichage du d�calage maximal rencontr�.
//
//       Revision 1.8  2000/08/03 08:33:46  club
//       modification des cha�nes max et min en maximum et minimum.
//
//       Revision 1.7  2000/07/28 13:03:00  club
//       Ajout de la valeur du seuil max tol�r� dans la synth�se.
//
//       Revision 1.6  2000/07/26 12:19:17  club
//       Modification du test permettant d'affecter une valeur � minMessage.
//
//       Revision 1.5  2000/07/26 09:49:13  club
//       Modification des #include suite au d�placement des fichiers .h dans
//       le r�pertoire club/utils.
//
//       Revision 1.4  2000/07/26 07:34:25  club
//       modification des m�thodes de la classe pour fournir de nouvelles
//       options � l'utilisateur (ne pas afficher les messages par exemple)
//       et pour am�liorer les informations fournies dans la synth�se
//       (num�ros des messages affich�s, moyenne des erreurs num�riques ...).
//
//       Revision 1.3  2000/07/07 12:08:06  club
//       cr�ation des m�thodes permettant de calculer et d'afficher des
//       statistiques sur les diff�rences num�riques rencontr�es.
//       modification de l'attribut nbMessagesDiffMax_ en un tableau � deux
//       �l�ments qui indiquent l'intervalle des messages � afficher.
//
//       Revision 1.2  2000/07/06 07:31:19  club
//       modification de l'attribut nbMessagesDiffMax_ (repr�sentant le
//       nombre maximal de messages de diff�rence � afficher) en un tableau
//       � deux �l�ments qui indiquent respectivement le num�ro du premier
//       et le num�ro du dernier message � afficher
//
//       Revision 1.1  2000/07/03 09:36:58  club
//       cr�ation de cette classe permettant de g�rer les statistiques de difference
//
//$Version
//       $Id: StatDifference.cpp,v 1.10 2000/09/07 08:42:03 club Exp $
//$Auteur
//       O. Queyrut CSSI 
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


#include "StatDifference.h"


// permet de traduire les messages de diff�rence
inline const char* trad (const char* s) { return TraduitFormatCVersExterne (s); }


bool StatDifference::traiterDifference ()
{
  nbErrAffichees_++;

  if (afficherMessages_ == false)
    return false;

  if ((!nbMessagesDiffFini_) ||
      (nbErrAffichees_ >= messagesAffiches_ [0]) &&
      (nbErrAffichees_ <= messagesAffiches_ [1]))
  {
    return true;
  }

  return false;
}


void StatDifference::calculerStat (double& errMinRelative, double& errMaxRelative, 
                                   double& moyenne)
{
  if (nbDifferencesNumeriques_ > 0)
  {
    errMinRelative = differencesNumeriques_ [1];
    errMaxRelative = differencesNumeriques_ [1];
    double total = differencesNumeriques_ [1];

    for (int i=2;i<=nbDifferencesNumeriques_;i++)
    {
      if (differencesNumeriques_[i] < errMinRelative)
        errMinRelative = differencesNumeriques_ [i];
      
      if (differencesNumeriques_[i] > errMaxRelative)
        errMaxRelative =  differencesNumeriques_ [i];

      total += differencesNumeriques_ [i];
    }
    
    moyenne = total / nbDifferencesNumeriques_;
  }
  else
  {
    errMinRelative = 0;
    errMaxRelative = 0;
    moyenne = 0;
  }  
}


void StatDifference::afficherSynthese (const double precision, const int decalage)
{
  if (afficherSynthese_ == false)
    return;

  char* tampon = new char [1024];

  double errMaxRelative;
  double errMinRelative;
  double moyenne;

  calculerStat (errMinRelative, errMaxRelative, moyenne);

  int minMessage = 0;
  int maxMessage = 0;

  if ((! nbMessagesDiffFini_) && (nbErrAffichees_ > 0))
  {
    minMessage = 1;
    maxMessage = nbErrAffichees_;    
  }
  else if (nbErrAffichees_ < messagesAffiches_ [0])
  {
    minMessage = 0;
    maxMessage = 0;
  }
  else if (nbErrAffichees_ <= messagesAffiches_ [1])
  {
    minMessage = messagesAffiches_ [0];
    maxMessage = nbErrAffichees_;
  }
  else
  {
    minMessage = messagesAffiches_ [0];
    maxMessage = messagesAffiches_ [1];
  }


  // on retourne le resultat

  (void) sprintf (tampon, trad ("nombre de messages de difference      : %d"),
                  nbErrAffichees_);
  cout << tampon << endl;

  if (afficherMessages_)
  {
    (void) sprintf (tampon, trad ("numeros des messages affiches         : %d a %d"),
                    minMessage, maxMessage, nbErrAffichees_);
    cout << tampon << endl;
  }

  (void) sprintf (tampon, trad ("nombre d'erreurs non acceptees        : %d\n"
                                "\t%d erreur(s) numerique(s)\n"
                                "\t%d erreur(s) lexicale(s)"),
                  nbErrNonAcceptees_, nbErrNonAccepteesNumeriques_,
                  nbErrNonAcceptees_ - nbErrNonAccepteesNumeriques_);
  cout << tampon << endl;

  (void) sprintf (tampon, trad ("nombre d'erreurs numeriques acceptees : %d"),
                  nbErrAcceptees_);
  cout << tampon << endl;

  (void) sprintf (tampon, trad ("decalage maximal rencontre            : %d"),
                  decalage);
  cout << tampon << endl;

  (void) sprintf (tampon, trad ("seuil de tolerance numerique          : %12.6e"),
                  precision);
  cout << tampon << endl;

  (void) sprintf (tampon, trad ("erreur numerique minimale             : %12.6e"),
                  errMinRelative);
  cout << tampon << endl;

  (void) sprintf (tampon, trad ("erreur numerique maximale             : %12.6e"),
                  errMaxRelative);
  cout << tampon << endl;

  (void) sprintf (tampon, trad ("moyenne des erreurs numeriques        : %12.6e"),
                  moyenne);
  cout << tampon << endl;
}

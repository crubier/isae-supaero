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
//>       ComparateurLigne.cpp
//$Resume
//       fichier d'implantation de la classe ComparateurLigne
//
//$Description
//       Module de d�finition de la classe
//
//$Contenu
//>       inline const char* trad()
//>       class ComparateurLigne   
//>         initialiser()           
//>         analyserLigne()
//>         lexemesSuivantsIdentiques()        
//>         comparerLigne()
//>         formaterMessage()
//>         comparerLexeme()       
//$Historique
//       $Log: ComparateurLigne.cpp,v $
//       Revision 1.11  2003/02/03 14:46:11  club
//       DM-ID 17 Mise � jour de l'extensions du fichier dans le bandeau
//
//       Revision 1.10  2001/06/22 05:38:50  club
//       inclusion de cmath
//
//       Revision 1.9  2001/05/03 13:22:38  club
//       �limination d'une violation m�moire lors de l'affichage des
//       diff�rences entres lignes tr�s longues (merci � Ole Kristian
//       Kverneland)
//
//       Revision 1.8  2000/09/11 13:19:07  club
//       suppression des blancs au d�but des cha�nes � analyser.
//
//       Revision 1.7  2000/09/07 08:42:02  club
//       utilisation de string de la STL au lieu de ChaineSimple conform�ment
//       aux �volutions r�alis�es sur les classes de l'interface publique de club.
//
//       Revision 1.6  2000/08/03 08:32:23  club
//       utilisation d'un code de retour plut�t que la lev�e d'une exception
//       pour la fonction analyserLigne.
//
//       Revision 1.5  2000/07/28 13:04:28  club
//       am�lioration de la forme des messages de diff�rence
//
//       Revision 1.4  2000/07/26 09:49:13  club
//       Modification des #include suite au d�placement des fichiers .h dans
//       le r�pertoire club/utils.
//
//       Revision 1.3  2000/07/26 07:36:32  club
//       modification importante de la classe pour am�liorer le recalage
//       des analyseurs lexicaux lorsque certains lex�mes sont propres
//       � un seul d'entre eux. Am�lioration des algorithmes pour diminuer
//       leur complexit� et donc le temps de calcul.
//
//       Revision 1.2  2000/07/07 12:09:34  club
//       cr�ation d'une m�thode permettant de formater le message de diff�rence.
//       suppression du formatage du message de la fonction comparerLigne.
//
//       Revision 1.1  2000/07/03 09:37:51  club
//       cr�ation de cette classe permettant de comparer deux lignes d'un fichier
//       tout en acceptant une impr�cision num�rique sur les r�els
//
//$Version
//       $Id: ComparateurLigne.cpp,v 1.11 2003/02/03 14:46:11 club Exp $
//$Auteur
//        O. Queyrut CSSI
//        Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include "ComparateurLigne.h"


// permet de traduire les messages de diff�rence
inline const char* trad (const char* s) { return TraduitFormatCVersExterne (s); }


// initialisation du comparateur de lignes
void ComparateurLigne::initialiser (const string& cres, int numLigneRes,
                                    const string& cref, int numLigneRef)
{
  // enregistrement des lignes � comparer (utile pour la formation des messages)
  ligneRes_ = cres;
  ligneRef_ = cref;

  // suppression des blancs initiaux
  int pos = ligneRes_.find_first_not_of ("\n\t\v\b\r ");
  ligneRes_.erase (0, pos);

  pos = ligneRef_.find_first_not_of ("\n\t\v\b\r ");
  ligneRef_.erase (0, pos);

  // enregistrement des num�ros des lignes (utile pour la formation des messages)
  numeroLigneRes_ = numLigneRes;
  numeroLigneRef_ = numLigneRef;

  // reinitialisation des analyseurs lexicaux avec les chaines cres et cref
  alres_.reinitialise (ligneRes_);
  alref_.reinitialise (ligneRef_);
}


int ComparateurLigne::analyserLigne (StatDifference& stats)
{
  int nbErreursDansLigne = 0;
  int pos = 0;
  string chaine;

  string chres, chref;
  char *tampon = 0;

  // on se replace sur le premier lex�me
  alres_.redemarre (); alres_.suivant ();
  alref_.redemarre (); alref_.suivant ();

  // analyse lex�me par lex�me jusqu'� arriver � la fin d'une ligne
  while ((alres_.type () != AnalyseurLexical::codeFin) && 
         (alref_.type () != AnalyseurLexical::codeFin))
  {
    // comparaison du premier lex�me de alres_ avec le premier lex�me de alref_
    double diff = 0;
    int estDifferent = comparerLexeme (diff);

    if (estDifferent == 0) 
    {
      // les lex�mes sont identiques

      if (diff > 0)
      {
        // l'�galit� des deux lex�mes est � diff pr�s. On met � jour les statistiques
        stats.majDifferencesNumeriques (diff);
        stats.majNbErrAcceptees ();
      }
      
      // les deux lex�mes ont �t� analys�s, on les supprime de
      // respectivement alres_ et alref_
      chres = alres_.chaine ().substr (alres_.lexeme ().size (), 
                                       alres_.chaine ().size ());
      pos = chres.find_first_not_of ("\n\t\v\b\r ");
      chres.erase (0, pos);
      alres_.reinitialise (chres);
      alres_.suivant ();

      chref = alref_.chaine ().substr (alref_.lexeme ().size (), 
                                       alref_.chaine ().size ());
      pos = chref.find_first_not_of ("\n\t\v\b\r ");
      chref.erase (0, pos);
      alref_.reinitialise (chref);
      alref_.suivant ();
    }
    else
    {
      // les lex�mes sont diff�rents
      chaine = "";

      // recherche des deux lex�mes suivants identiques
      int indiceRes, indiceRef;
      lexemesSuivantsIdentiques (indiceRes, indiceRef);

      alres_.redemarre (); alres_.suivant ();
      alref_.redemarre (); alref_.suivant ();
      int i = 1;
      int j = 1;

      while ((i < indiceRes) && (j < indiceRef))
      {
        nbErreursDansLigne++;
        // deux lex�mes suivants sont diff�rents
        estDifferent = comparerLexeme (diff);

        // mise � jour des statistiques
        stats.majNbErrNonAcceptees ();
        if (estDifferent == 3)
        {
          // si les deux lex�mes sont des valeurs num�riques diff�rentes,
          // il faut mettre � jour l'erreur max relative
          stats.majNbErrNonAccepteesNumeriques ();
          stats.majDifferencesNumeriques (diff);
        }

        // formation du message
        formaterMessage (estDifferent, diff);
        
        // les deux lex�mes ont �t� analys�s, on les supprime de 
        // respectivement alres_ et alref_
        chres = alres_.chaine ().substr (alres_.lexeme ().size (),
                                         alres_.chaine ().size ());
        pos = chres.find_first_not_of ("\n\t\v\b\r ");
        chres.erase (0, pos);
        alres_.reinitialise (chres);
        alres_.suivant ();
        
        chref = alref_.chaine ().substr (alref_.lexeme ().size (), 
                                         alref_.chaine ().size ());
        pos = chref.find_first_not_of ("\n\t\v\b\r ");
        chref.erase (0, pos);
        alref_.reinitialise (chref);
        alref_.suivant ();

        i++;
        j++;
      }

      int lexemesEnPlus = 0;

      while (i < indiceRes)
      {
        lexemesEnPlus = 1;
        chaine += " ";
        chaine += alres_.lexeme ();
        
        // suppression du lex�me dans alres_
        string chres = alres_.chaine ().substr (alres_.lexeme ().size (), 
                                                alres_.chaine ().size ());
        pos = chres.find_first_not_of ("\n\t\v\b\r ");
        chres.erase (0, pos);
        alres_.reinitialise (chres);
        alres_.suivant ();
        i++;
      }
      
      while (j < indiceRef)
      {
        lexemesEnPlus = -1;
        chaine += " ";
        chaine += alref_.lexeme ();

        // suppression du lex�me de alref_
        string chref = alref_.chaine ().substr (alref_.lexeme ().size (), 
                                                alref_.chaine ().size ());
        pos = chref.find_first_not_of ("\n\t\v\b\r ");
        chref.erase (0, pos);
        alref_.reinitialise (chref);
        alref_.suivant ();
        j++;
      }

      switch (lexemesEnPlus)
      {
        case 0 : // pas de repositionnement � effectuer
          break;

        case 1 : // lex�mes en plus dans alres_
          nbErreursDansLigne++;

          pos = chaine.find_first_not_of ("\n\t\v\b\r ");
          chaine.erase (0, pos);

          // mise � jour des statistiques
          stats.majNbErrNonAcceptees ();

          // formation du message
          tampon = new char [strlen (trad ("la chaine \"%s\" est en"
                                           " plus :\n%s,%d : %s\n"
                                           "%s,%d : %s"))
                            + chaine.size ()
                            + nomFichierRes_.size ()
                            + ligneRes_.size ()
                            + nomFichierRef_.size ()
                            + ligneRef_.size ()
                            + 100];
          (void) sprintf (tampon, trad ("la chaine \"%s\" est en plus :\n%s,%d : %s\n%s,%d : %s"),
                          chaine.c_str (),
                          nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str (),
                          nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());
          messageDiff_ = tampon;
          delete[] tampon;
          break;

        case -1 : // lex�mes en moins dans alres_
          nbErreursDansLigne++;

          pos = chaine.find_first_not_of ("\n\t\v\b\r ");
          chaine.erase (0, pos);

          // mise � jour des statistiques
          stats.majNbErrNonAcceptees ();

          // formation du message
          tampon = new char [strlen (trad ("la chaine \"%s\" manque :\n"
                                           "%s,%d : %s\n%s,%d : %s"))
                            + chaine.size ()
                            + nomFichierRes_.size ()
                            + ligneRes_.size ()
                            + nomFichierRef_.size ()
                            + ligneRef_.size ()
                            + 100];
          (void) sprintf (tampon, trad ("la chaine \"%s\" manque :\n%s,%d : %s\n%s,%d : %s"),
                          chaine.c_str (), 
                          nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str (),
                          nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());
          messageDiff_ = tampon;
          delete[] tampon;
          break;

        default :
          // ce cas ne se produit pas
          break;
      }
    }
  
    // alres_ et alref_ ont �t� r�initialis�s avec une chaine ne comportant 
    // plus les lex�mes analys�s. Les deux analyseurs sont positionner sur 
    // leur premier lex�me

  } // fin de la boucle sur les lex�mes

  // on teste pour savoir si on est bien au bout de la ligne pour
  // les deux analyseurs lexicaux

  if (alres_.type () != AnalyseurLexical::codeFin)
  {
    // une erreur suppl�mentaire dans la ligne
    nbErreursDansLigne++;
    stats.majNbErrNonAcceptees ();
    
    // il reste des lex�mes dans le tampon r�sultat
    chaine = alres_.chaine ().substr (alref_.chaine ().size (), 
                                      alres_.chaine ().size ());
    
    tampon = new char [strlen (trad ("la chaine \"%s\" est en plus :\n"
                                     "%s,%d : %s\n%s,%d : %s"))
                      + chaine.size ()
                      + nomFichierRes_.size ()
                      + ligneRes_.size ()
                      + nomFichierRef_.size ()
                      + ligneRef_.size ()
                      + 100];
    (void) sprintf (tampon, trad ("la chaine \"%s\" est en plus :\n%s,%d : %s\n%s,%d : %s"),
                    chaine.c_str (), 
                    nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str (),
                    nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());
    messageDiff_ = tampon;
    delete[] tampon;
  }
  
  else if (alref_.type () != AnalyseurLexical::codeFin)
  {
    // une erreur suppl�mentaire dans la ligne
    nbErreursDansLigne++;
    stats.majNbErrNonAcceptees ();

    // il reste des lex�mes dans le tampon r�f�rence
    chaine = alref_.chaine ().substr (alres_.chaine ().size (), 
                                      alref_.chaine ().size ());
    tampon = new char [strlen (trad ("la chaine \"%s\" manque :\n"
                                     "%s,%d : %s\n%s,%d : %s"))
                      + chaine.size ()
                      + nomFichierRes_.size ()
                      + ligneRes_.size ()
                      + nomFichierRef_.size ()
                      + ligneRef_.size ()
                      + 100];
    (void) sprintf (tampon, trad ("la chaine \"%s\" manque :\n%s,%d : %s\n%s,%d : %s"),
                    chaine.c_str (), 
                    nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str (),
                    nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());
    messageDiff_ = tampon;
    delete[] tampon;
  }

  if (nbErreursDansLigne > 1)
  {
      // plusieurs erreurs dans la ligne, on formate un message
      // concernant toute la ligne
    tampon = new char [strlen (trad ("%d differences dans les lignes:\n"
                                     "%s,%d : %s\n%s,%d : %s"))
                      + nomFichierRes_.size ()
                      + ligneRes_.size ()
                      + nomFichierRef_.size ()
                      + ligneRef_.size ()
                      + 100];
    (void) sprintf (tampon, trad ("%d differences dans les lignes:\n"
                                  "%s,%d : %s\n%s,%d : %s"),
                    nbErreursDansLigne,
                    nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str (),
                    nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());
    messageDiff_ = tampon;
    delete[] tampon;
  }

  return nbErreursDansLigne;
}



// cette fonction permet de trouver les premiers lex�mes de res et ref qui soient �gaux
// et qui v�rifient :
// - numeroRes et numeroRef doivent �tre le plus proches possible
// - numeroRes et numeroRef doivent �tre minimaux
// Ainsi si les lex�mes 3 de res est �gal au lex�me 1 et 3 de ref et
// si le lex�me 1 de res est �gal au lex�me 5 de ref, la fonction retournera : 
// numeroRes = 3 et numeroRef = 3
//
//               ---->
//        a   b   a   z   c
//       -------------------
//    c  |0   0   0 | 0   1|
//       |          |      |
// |  y  |0   0   0 | 0   0|
// |     |          |      |
// |  a  |1   0   1 | 0   0|
// v     |-----------      |
//    v  |0   0   0   0   0|
//       |                 |
//    w  |0   0   0   0   0|
//       -------------------
//
// En d'autres termes, on cherche le plus petit carr� de c�t� max(numeroRes, numeroRef)
// o� numeroRes et numeroRef sont les positions de deux lex�mes �gaux. On prend ensuite
// les lex�mes �gaux les plus proches du coin inf�rieur droit de ce carr�.
// 

void ComparateurLigne::lexemesSuivantsIdentiques (int& numeroRes, int& numeroRef)
{
  double diff;

  int i = 1;
  int j = 1;

  numeroRes = alres_.nbLexemes ()+1;
  numeroRef = alref_.nbLexemes ()+1;

  alres_.redemarre ();
  alres_.suivant ();

  // on parcourt la ligne res lex�me par lex�me
  while ((alres_.type () != AnalyseurLexical::codeFin) && 
         (i <= max (numeroRes, numeroRef)))
  {
    alref_.redemarre ();
    alref_.suivant ();
    j = 1;

    // on parcourt la ligne ref lex�me par lex�me
    while ((alref_.type () != AnalyseurLexical::codeFin) && 
           (j <= max (numeroRes, numeroRef)))
    {
      // si � i et j, les lex�mes sont �gaux, on stocke ces valeurs dans numeroRes 
      // et numeroRef.
      if (comparerLexeme (diff) == 0)
      {
        numeroRes = i;
        numeroRef = j;
      }
      j++;
      alref_.suivant ();
    }
    i++;
    alres_.suivant ();
  }
}


// m�thode publique permettant de comparer les deux lignes
bool ComparateurLigne::comparerLigne ()
{
  double diff = 0;
  int i=0;

  alres_.redemarre ();
  alref_.redemarre ();
  alres_.suivant ();
  alref_.suivant ();

  // dans chaque ligne, on analyse lex�me par lex�me
  while ((alres_.type () != AnalyseurLexical::codeFin) && 
         (alref_.type () != AnalyseurLexical::codeFin))
  {
    // comparaison des lex�mes courants
    if (comparerLexeme (diff) != 0)
      return false;

    i++;

    alres_.suivant ();
    alref_.suivant ();
  }

  if ((alres_.type () != AnalyseurLexical::codeFin) ||
      (alref_.type () != AnalyseurLexical::codeFin))
    return false;

  return true;
}


// m�thode priv�e permettant de formater le message de diff�rence
void ComparateurLigne::formaterMessage (int index, double diff)
{

  char *tampon = 0;

  switch (index)
  {
    case 0 : 
      // lex�mes identiques (strictement ou relativement)
      break;
    case 1 :
      // chaines de caract�res diff�rentes
      tampon = new char [strlen (trad ("chaines \"%s\" et \"%s\" differentes "
                                       "dans les lignes :\n"
                                       "%s,%d : %s\n%s,%d : %s"))
                        + alres_.lexeme ().size ()
                        + alref_.lexeme ().size ()
                        + nomFichierRes_.size ()
                        + ligneRes_.size ()
                        + nomFichierRef_.size ()
                        + ligneRef_.size ()
                        + 100];
      (void) sprintf (tampon, trad ("chaines \"%s\" et \"%s\" differentes "
                                    "dans les lignes :\n%s,%d : %s\n%s,%d : %s"),
                      alres_.lexeme ().c_str (), alref_.lexeme ().c_str (),
                      nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str (),
                      nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());

      messageDiff_ = tampon;
      delete[] tampon;
      break;
    case 2 :
      // entiers diff�rents
      tampon = new char [strlen (trad ("entiers %d et %d differents dans les "
                                       "lignes :\n%s,%d : %s\n%s,%d : %s"))
                        + nomFichierRes_.size ()
                        + ligneRes_.size ()
                        + nomFichierRef_.size ()
                        + ligneRef_.size ()
                        + 100];
      (void) sprintf (tampon, trad ("entiers %d et %d differents dans les "
                                    "lignes :\n%s,%d : %s\n%s,%d : %s"),
                      alres_.entier (), alref_.entier (), 
                      nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str(), 
                      nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());

      messageDiff_ = tampon;
      delete[] tampon;
      break;
    case 3 :
      // valeurs num�riques diff�rentes
      tampon = new char [strlen (trad ("difference relative (%12.6e) entre"
                                       " les reels %f et %f superieure"
                                       " au seuil (%12.6e):\n"
                                       "%s,%d : %s\n%s,%d : %s"))
                        + nomFichierRes_.size ()
                        + ligneRes_.size ()
                        + nomFichierRef_.size ()
                        + ligneRef_.size ()
                        + 100];
      (void) sprintf (tampon, trad ("difference relative (%12.6e) entre les reels %f et %f "
                                    "superieure au seuil (%12.6e):\n%s,%d : %s\n%s,%d : %s"),
                      diff, alres_.valeurNumerique (), 
                      alref_.valeurNumerique (), precision_,
                      nomFichierRes_.c_str (), numeroLigneRes_, ligneRes_.c_str (),
                      nomFichierRef_.c_str (), numeroLigneRef_, ligneRef_.c_str ());

      messageDiff_ = tampon;
      delete[] tampon;
      break;
    default :
      // ce cas ne se produit pas 
      break;
  }
}

// m�thode priv�e permettant de comparer deux lex�mes tout en acceptant une impr�cision
// num�rique
int ComparateurLigne::comparerLexeme (double& diff)
{
  int typeRes = alres_.type ();
  int typeRef = alref_.type ();

  diff = 0;

  // on consid�re d'abord les cas o� les lex�mes sont de types autres
  // que codeEntier et autres que codeReel
    
  if (((typeRes != AnalyseurLexical::codeReel) && (typeRes != AnalyseurLexical::codeEntier)) || 
      ((typeRef != AnalyseurLexical::codeReel) && (typeRef != AnalyseurLexical::codeEntier)))
  {
    // Au moins un des deux lex�mes n'est pas un entier ou un reel, on analyse donc leur
    // formes brutes et ils doivent �tre identiques.
    
    if (alres_.lexeme () != alref_.lexeme ())
      return 1;
  }

  // les deux lex�mes sont de type num�rique
  else if ((typeRes == typeRef) && (typeRes == AnalyseurLexical::codeEntier))
  {
    // les deux lex�mes sont entiers, ils doivent �tre strictement �gaux
    if (alres_.entier () != alref_.entier ())
      return 2;
  }

  else
  {
    // un des deux lex�mes est de type codeReel. Les deux lex�mes doivent
    // etre compar�s de facon relative
    
    double valeurRes = (double) ((typeRes == AnalyseurLexical::codeReel)? 
                                 alres_.reel () : alres_.entier ());
    double valeurRef = (double) ((typeRef == AnalyseurLexical::codeReel)? 
                                 alref_.reel () : alref_.entier ());
    diff = fabs (valeurRes - valeurRef) / (1+fabs (valeurRef));

    alres_.majValeurNumerique (valeurRes);
    alref_.majValeurNumerique (valeurRef);

    if (diff != 0)
    {      
      if (diff < precision_)
      {
        // l'erreur est accept�e
        return 0;
      }
      else
        // l'erreur est trop importante
        return 3;
    }
  }
  return 0;
}

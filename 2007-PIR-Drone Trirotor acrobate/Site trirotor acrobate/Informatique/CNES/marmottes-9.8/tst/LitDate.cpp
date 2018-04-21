#include "club/AnalyseurLexical.h"

static double date1950 (int j, int m, int a,
                        int h, int mn, int sec, int ms)
{ // construction � partir des �l�ments calendaires
  int nonBis = (a & 3) || ((a % 100 == 0) && ((a / 100) & 3));
  int      s = (a - 1201) / 100;

  // formule valable � partir du 15/10/1582 (calendrier gr�gorien)
  return double ((1461 * (a - 1581)) >> 2) + (s >> 2) - s
                 + ((m * 489) >> 4) - ((m > 2) ? (nonBis ? 32 : 31) : 30)
                 + j - 134772
       + double (((h * 60 + mn) * 60 + sec) * 1000 + ms) / 86400000.0;

}

double LitDate (const char *chaine)
{ // lecture d'une date dans une cha�ne avec un format variable
  AnalyseurLexical al (chaine);

  // on commence par tenter un format calendaire
  al.initSeparateurs (":/-");
  int n [7];
  for (int j = 0; j < 7; j++)
    n [j] = 0;
  int nbEntiers = 0;
  int ok = 1;

  (void) al.suivant ();
  while (ok && (al.type () == AnalyseurLexical::codeEntier))
  { // boucle sur les entiers du format
    n [nbEntiers++] = al.entier ();
    ok = (nbEntiers <= 7);

    if (al.suivant () != AnalyseurLexical::codeSeparateur)
    { // les s�parateurs sont optionnels entre ann�e et heure ou � la fin
      ok = ok
        && (((nbEntiers == 3) && (al.type () == AnalyseurLexical::codeEntier))
         || (al.type () == AnalyseurLexical::codeFin));
    }
    else
      (void) al.suivant ();

  }
  ok = ok
    && ((nbEntiers == 3) || (nbEntiers == 6) || (nbEntiers == 7))
     && (al.type () == AnalyseurLexical::codeFin);

  if (ok)
  { // un format calendaire a �t� reconnu

    if (n [0] > 999)
    { // la date est au format ISO 8601 (ann�e en premier)
      // on la ram�ne dans l'ordre fran�ais
      int tmp = n [0];
      n [0]   = n [2];
      n [2]   = tmp;
    }

    // correction de l'ann�e si elle n'est que sur deux chiffres
    if (n [2] < 50)
      n [2] += 2000;   // ann�es 2000 � 2049, not�es 00 � 49
    else if (n [2] < 100)
      n [2] += 1900;   // ann�es 1950 � 1999, not�es 50 � 99

    return date1950 (n [0], n [1], n [2], n [3], n [4], n [5], n [6]);

  }
  else
  { // le format calendaire ne convenait pas, on essaie un simple r�el
    al.initSeparateurs ("");
    if ((al.suivant () == AnalyseurLexical::codeReel)
        &&
        (al.suivant () == AnalyseurLexical::codeFin))
      return al.reel ();
    else
      return 0.0;
  }

}

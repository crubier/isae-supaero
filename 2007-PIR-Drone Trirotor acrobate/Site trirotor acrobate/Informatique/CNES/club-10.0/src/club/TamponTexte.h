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
//>       TamponTexte.h
//$Resume
//       fichier d'en-t�te de la classe TamponTexte
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class TamponTexte            
//>       inline ostream& operator <<()
//$Historique
//       $Log: TamponTexte.h,v $
//       Revision 3.15  2003/10/22 12:54:39  club
//       DM 0029
//
//       Revision 3.14  2000/10/25 09:31:44  club
//       modification des include du standard C++ : suppression de ".h" dans le nom
//       du fichier inclus.
//
//       Revision 3.13  2000/09/07 07:42:15  club
//       utilisation de la classe string de la STL au lieu de ChaineSimple.
//
//       Revision 3.12  2000/07/03 08:53:50  club
//       Ajout du copyright CNES
//
//       Revision 3.11.2.1  2000/03/30 14:46:59  club
//       ajout du copyright CNES
//
//       Revision 3.11  1999/07/06 15:24:17  club
//       Changement des signatures pour gestion des erreurs
//       par m�canisme d'exception
//
//       Revision 3.10  1999/03/15 15:09:18  club
//       modification totale de TamponTexte, qui repose sur la hi�rarchie de TamponAscii
//       et des it�rateurs, sans changement de l'interface utilisateur
//       TamponTexte bloquent les exceptions des objets utilis�s et conserve en
//       interface le syst�me d'erreur ClubErreur
//
//       Revision 3.9  1998/07/27 10:14:14  club
//       passage � une configuration de type GNU (fichier ClubConfig.h g�n�r�)
//
//       Revision 3.8  1998/06/25 06:48:33  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//       �limination de la m�thode estValide
//
//       Revision 3.7  1998/04/26 13:02:48  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.6  1998/01/22 08:30:24  luc
//       am�lioration de l'en-t�te de classe
//
//       Revision 3.5  1997/08/24 13:37:40  luc
//       reconnaissance des cha�nes de caract�res du fortran
//       utilisation de la classe AnalyseurLexical
//       traitement en bloc des commentaires
//       dans le cas de l'interpr�tation des guillemets
//       (sinon, on confond les apostrophes dans les commentaires
//       avec les sp�cificateurs de cha�nes fortran)
//
//       Revision 3.4  1997/08/21 16:36:28  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 3.3  1997/04/03 12:50:54  luc
//       inversion des codes de retour, 0 signifie d�sormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:03:48  luc
//       changement des r�gles de nommage
//       
//       Revision 3.1  1997/03/19 14:50:50  luc
//       utilisation de la classe ChaineSimple
//       renommage de la biblioth�que util_c++ en club
//       passage de SCCS � RCS
//       
//       Revision 2.1  1996/07/15 17:30:47  luc
//       �limination de la d�pendance au tools.h++ (Rogue Wave)
//       prise en compte du renommage de erreurs.h en util_erreurs.h
//       
//       Revision 1.8  1995/07/12 14:58:06  mercator
//       ajout de signatures pour aider le compilateur SUN a comprendre ...
//       
//       Revision 1.7  1995/07/07 14:02:51  mercator
//       transformation de toutes les fonctions de lecture en fonctions "const"
//       (on estime licite de modifier des attributs d'optimisation invisibles
//       de l'exterieur dans des fonctions "const")
//       
//       Revision 1.6  1994/12/13 07:55:20  mercator
//       ajout d'une interface en FILE* a la construction et a la lecture
//       
//       Revision 1.5  1994/12/09 13:54:59  mercator
//       ajout d'une possibilite de mettre hors-circuit l'interpretation des '"'
//       
//       Revision 1.4  1994/11/09 15:00:45  mercator
//       elimination des directives #pragma
//       
//       Revision 1.3  1994/09/30 07:17:20  mercator
//       transformation des routines d'insertion dans les lignes
//       ajout de tests de validite des numeros de champs et lignes
//       elimination de tests redondants entre appelants et appeles
//       
//       Revision 1.2  1994/09/28 16:17:51  mercator
//       ajout d'une possibilite de personnalisation des separateurs
//       ajout de pointeurs d'erreur optionnels dans les signatures des methodes
//       
//       Revision 1.1  1994/07/27 11:55:30  luc
//       Initial revision
//
//$Version
//       $Id: TamponTexte.h,v 3.15 2003/10/22 12:54:39 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef club_TamponTexte_h
#define club_TamponTexte_h

#include <iostream>
#include <fstream>

#include "club/ClubErreurs.h"
#include "club/TamponAscii.h"
#include "club/IterateurCaractere.h"
#include "club/IterateurChamp.h"
#include "club/IterateurLigne.h"
#include "club/IterateurChampLigne.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class TamponTexte
//$Resume
//       classe de gestion de texte en m�moire (image d'un fichier ou non)
//
//$Description
//       acc�s aux �l�ments internes (lignes, champs) d'un texte
//       pouvant comporter des lignes blanches, des commentaires, des
//       cha�nes de caract�res comportant des caract�res blancs ou
//       sp�ciaux du langage C (\n, \012, ...)  (les caract�res -ou le
//       champ complet- sont alors inclus entre '"')
//
//$Usage
//>     construction : 
//          sans argument, ou � partir d'un fichier, ou du nom du
//          fichier, par copie, avec �ventuelle suppression de
//          l'interpr�tation des commentaires
//>     utilisation  : 
//>       TamponTexte& operator =              () 
//          affectation
//>       void lit                             () 2 signatures - 
//          relit le fichier donn� en argument. Si le nom est vide
//          (c'est la valeur par d�faut) utilise le nom conserv� dans
//          l'instance.
//>       void ecrit                           () 
//          stocke dans le fichier dont le nom est donn� en
//          argument. Si ce nom est vide (c'est la valeur par defaut)
//          utilise le nom conserv� dans l'instance. 
//>       void elimineCommentaires             () 
//          �limine les caract�res qui vont d'un caract�re marqueur de
//          commentaire � la fin de la ligne (sauf si le marqueur est
//          dans une cha�ne entre '"'). 
//>       void elimineBlancs                   () 
//          �limine les caract�res blancs de d�but et de fin de ligne
//          (pour une ligne enti�rement blanche, le '\n' est �galement
//          �limin�). 
//>       void initCarCommentaires            () 
//          utilise les caract�res de str comme marqueurs de
//          commentaires. Si str est la cha�ne vide ou le pointeur
//          nul, cette fonction r�initialise � la valeur par d�faut
//          qui est "#".
//>       void ajouteCarCommentaires          () 
//          ajoute les caract�res de str � la liste des caract�res
//          marqueurs de commentaires.
//>       const string& carCommentaires       () 
//          retourne la liste des caract�res marqueurs de
//          commentaires.
//>       void initSeparateurs                () 
//          utilise les caract�res de str comme caract�res s�parateurs
//          de champs. Si str est la cha�ne vide ou le pointeur nul,
//          cette fonction r�initialise � la valeur par d�faut qui est
//          "\t\n\v\f\r ".
//>       void ajouteSeparateurs              () 
//          ajoute les caract�res de str � la liste des caract�res
//          s�parateurs.
//>       const string& separateurs           () 
//          retourne la liste des caract�res s�parateurs.
//>       const char* nom                     () 
//          retourne le nom du fichier
//>       int estVide                         () 
//          teste si l'instance est vide
//>       const char* total                   () 
//          retourne un pointeur sur le tampon constant contenant les
//          donn�es (totalit� du fichier)
//>       int longueur                        () 
//          retourne la longueur du tampon (sans le '\0' final)
//>       int insereAAdresse                  () 
//          insere la chaine pointee par p a l'adresse donnee par ad
//          (si ad est avant le debut, on insere au debut, si ad est
//          apres la fin, on ajoute a la fin).
//>       int insereAuDebut                   () 
//          insere la cha�ne point�e par p avant le d�but du
//          fichier. 
//>       void ajouteALaFin                    () 
//          ajoute la cha�ne point�e par p apr�s la fin du
//          fichier. 
//>       void elimineZone                     () 
//          elimine la zone s'etendant de l'adresse d a l'adresse f.
//>       void elimineTout                     () 
//          vide le tampon complet. 
//>       void remplaceTout                    ()
//          remplace le tampon complet par la chaine pointee par p.
//>       int nombreLignes                    () 
//          retourne le nombre de lignes, ou -1 en cas de probl�me.
//>       const char* ligne                   () 
//          retourne la ligne num�ro l du fichier (lignes num�rot�es a
//          partir de 1)
//>       void insereDebutLigne                () 
//          ins�re une cha�ne en d�but de ligne l. 
//>       void insereFinLigne                  () 
//          ins�re une cha�ne en fin de ligne l. 
//>       void elimineLigne                    () 
//          �limine la ligne l. 
//>       void remplaceLigne                   () 
//          remplace la ligne l par la cha�ne point�e
//          (les s�parateurs de champ sont g�r�s par l'instance,
//          il est inutile de les mettre dans p). 
//>       int nombreChampsLigne               () 
//          retourne le nombre de champs de la ligne num�ro l, ou -1
//          en cas de probl�me (lignes num�rot�es � partir de 1)
//>       const char* champLigne              () 
//          retourne le champ num�ro c de la ligne num�ro l (lignes
//          num�rot�es � partir de 1, champs num�rot�s � partir de 1)
//>       void insereAvantChampLigne           () 
//          ins�re la cha�ne point�e par p avant le champ c de la
//          ligne l.
//>       void ajouteApresChampLigne           () 
//          ajoute la cha�ne point�e par p apr�s le champ c de la
//          ligne l. 
//>       void elimineChampLigne               () 
//          �limine le champ c de la ligne l. 
//>       void remplaceChampLigne              () 
//          remplace le champ c de la ligne l par la cha�ne point�e
//          par p (les s�parateurs de champ sont g�r�s par l'instance,
//          il est inutile de les mettre dans p). 
//>       int nombreChamps                    () 
//          retourne le nombre de champs total du fichier, ou -1 en
//          cas de probl�me.
//>       const char* champ                   () 
//          retourne le champ num�ro c du fichier (champs num�rot�s a
//          partir de 1)
//>       void insereAvantChamp                () 
//          ins�re la cha�ne point�e par p avant le champ c. 
//>       void ajouteApresChamp                () 
//          ajoute la cha�ne point�e par p apr�s le champ c. 
//>       void elimineChamp                    () 
//          �limine le champ c (ne fait rien si c n'est pas
//          valide). 
//>       void remplaceChamp                   () 
//          remplace le champ c par la cha�ne point�e par p (les
//          s�parateurs de champ existants sont conserv�s,il est
//          inutile de les mettre dans p).
//$Auteur
//       L. Maisonobe CNES
//       M. Julien    CSSI
//       P-A. Cros    CSSI
//       G. Lajon     CSSI
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class TamponTexte
{ 
public :

  // constructeurs
  TamponTexte (int interprete = 1) throw(ClubErreurs) : tampon_ (0)  
    {tampon_ = new TamponAscii( interprete );
    parcoursCaractere_ = new IterateurCaractere(tampon_);
    parcoursChamp_ = new IterateurChamp(tampon_,0);
    parcoursLigne_ = new IterateurLigne(tampon_,0);
    parcoursChampLigne_ = new IterateurChampLigne(tampon_,0);
    }


  TamponTexte (FILE* ptrFic,  int interprete = 1)
    throw(ClubErreurs);
  TamponTexte (const char* nom, int interprete = 1)
    throw(ClubErreurs);

  // constructeur par copie et affectation
  TamponTexte             (const TamponTexte& t)
    throw(ClubErreurs);

  TamponTexte& operator = (const TamponTexte& t)
    throw(ClubErreurs);
  
  // destructeur
  ~TamponTexte ()
    throw();

  // relecture d'un fichier
  void        lit                   (FILE* ptrFic, int interprete = 1) 
    throw(ClubErreurs);
  void        lit                   (const char* nom = 0, int interprete = 1) 
    throw(ClubErreurs);
  // sauvegarde dans un fichier
  void        ecrit                 (const char* nom = 0) const 
    throw(ClubErreurs);

  // fonctions de filtrage
  void          elimineCommentaires   () throw(ClubErreurs);
  void          elimineBlancs         () throw(ClubErreurs);
  void          initCarCommentaires   (const char* chaine) throw();
  void          ajouteCarCommentaires (const char* chaine) throw();
  const string& carCommentaires       () const throw();

  void          initSeparateurs       (const char* chaine) throw();
  void          ajouteSeparateurs     (const char* chaine) throw();
  const string& separateurs           () const throw();


  // routines d'acc�s globales
  const char* nom                   () const throw();
  int         estVide               () const throw();
  const char* total                 () const throw();
  int         longueur              () const throw();

  void        insereAAdresse        (const char* adresse, const char* chaine)
    throw(ClubErreurs);
  void        insereAuDebut         (const char* chaine) throw (ClubErreurs)
    { insereAAdresse (total(), chaine); }

  void        ajouteALaFin          (const char* chaine)
    throw(ClubErreurs);
  void        elimineZone           (char* debut, char* fin)
    throw(ClubErreurs);
  void        elimineTout           ()
    throw(ClubErreurs)
    { elimineZone ((char *)total(), (char *)total() + longueur() - 1); }

  void        remplaceTout          (const char* chaine)
    throw(ClubErreurs);

  // routines d'acc�s par lignes
  int         nombreLignes          () const throw(ClubErreurs);
  const char* ligne                 (int l) const
    throw(ClubErreurs);
  void        insereDebutLigne      (int l, const char* chaine)
    throw(ClubErreurs);
  void        insereFinLigne        (int l, const char* chaine)
    throw(ClubErreurs);
  void        elimineLigne          (int l)
    throw(ClubErreurs);
  void        remplaceLigne         (int l, const char* chaine)
    throw(ClubErreurs);

  // routines d'acc�s par champs dans les lignes
  int         nombreChampsLigne     (int l) const
    throw(ClubErreurs);
  const char* champLigne            (int c, int l) const
    throw(ClubErreurs);
  void        insereAvantChampLigne (int c, int l, const char* chaine)
    throw(ClubErreurs);
  void        ajouteApresChampLigne (int c, int l, const char* chaine)
    throw(ClubErreurs);
  void        elimineChampLigne     (int c, int l)
    throw(ClubErreurs);
  void        remplaceChampLigne    (int c, int l, const char* chaine)
    throw(ClubErreurs);

  // routines d'acc�s par champs dans l'ensemble du fichier
  int         nombreChamps          () const throw();
  const char* champ                 (int c) const
    throw(ClubErreurs);
  void        insereAvantChamp      (int c, const char* chaine)
    throw(ClubErreurs);
  void        ajouteApresChamp      (int c, const char* chaine)
    throw(ClubErreurs);
  void        elimineChamp          (int c)
    throw(ClubErreurs);
  void        remplaceChamp         (int c, const char* chaine)
    throw(ClubErreurs);
  const TamponAscii* getTampon      ();

protected :
  TamponAscii         *tampon_;
  IterateurCaractere  *parcoursCaractere_;
  IterateurChamp      *parcoursChamp_;
  IterateurLigne      *parcoursLigne_;
  IterateurChampLigne *parcoursChampLigne_;

private :

  void actualiseIterateurs();

};

inline ostream& operator << (ostream& s, TamponTexte& t)
{return s << t.getTampon(); }

#endif

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
//>       TamponPartage.h
//
//$Resume
//       fichier d'en-t�te de la classe TamponPartage
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class TamponPartage
//
//$Historique
//       $Log: TamponPartage.h,v $
//       Revision 2.11  2002/12/09 15:59:00  club
//       DM-ID 12 Mise en conformit� des constructeurs/destructeurs avec la norme qualit�
//
//       Revision 2.10  2000/07/03 08:53:22  club
//       Ajout du copyright CNES
//       �limination de la valeur nulle par d�faut du pointeur de fonction
//       correction d'une erreur de comptabilisation pour les tampons
//       initalis�s par d�faut et recopi�s
//
//       Revision 2.9.2.2  2000/03/30 14:46:58  club
//       ajout du copyright CNES
//
//       Revision 2.9.2.1  2000/03/30 10:03:06  club
//       �limination de la valeur nulle par d�faut du pointeur de fonction
//       correction d'une erreur de comptabilisation pour les
//       tampons initalis�s par d�faut et recopi�s
//
//       Revision 2.9  1999/07/06 15:24:17  club
//       Changement des signatures pour gestion des erreurs
//       par m�canisme d'exception
//
//       Revision 2.8  1999/04/12 15:22:38  club
//       ajout des attributs fonctionLiberation_ et arg_
//
//       Revision 2.7  1998/07/07 15:07:00  luc
//       correction du cas des instances r�affect�es
//       sans jamais avoir �t� initialis�es
//
//       Revision 2.6  1998/06/25 06:46:19  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//       transformation de TamponPartage::Acces de "struct" en "class"
//
//       Revision 2.5  1998/04/26 13:02:44  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 2.4  1998/01/22 08:25:49  luc
//       am�lioration de l'en-t�te de classe
//
//       Revision 2.3  1997/08/21 16:36:21  luc
//       ajout d'un en-t�te de fichier
//
//       Revision 2.2  1997/03/25 15:01:07  luc
//       changement des r�gles de nommage
//       
//       Revision 2.1  1997/03/19 14:50:32  luc
//       renommage de la biblioth�que util_c++ en club
//       passage de SCCS � RCS
//       
//       Revision 1.2  1994/11/09 15:00:40  mercator
//       elimination des directives #pragma
//       
//       Revision 1.1  1994/07/27 11:55:39  luc
//       Initial revision
//
//$Version
//       $Id: TamponPartage.h,v 2.11 2002/12/09 15:59:00 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __club_TamponPartage_h
#define __club_TamponPartage_h

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class TamponPartage
//
//$Resume
//       classe de partage d'une ressource m�moire entre instance
//
//$Description
//       m�canisme de partage d'une ressource m�moire entre plusieurs
//       instances avec lib�ration m�moire uniquement � la disparition
//       de la derni�re instance.
//
//$Usage
//>     construction : 
//          par un pointeur sur une zone de m�moire allou�e et pointeurs
//          sur la fonction de lib�ration et ses donn�es associ�es
//          (ATTENTION: c'est le destructeur de cette classe qui g�re
//          la lib�ration de cette m�moire, l'utilisateur ne doit pas
//          le faire lui-m�me, d'autre part la lib�ration est faite �
//          l'aide de la fonction enregistr�e par l'utilisateur)
//>     utilisation  : 
//>       TamponPartage& operator = () 
//          affectation
//>       int references            () 
//          retourne le nombre de r�f�rences � la m�moire allou�e
//>       void* memoire             () 
//          retourne un pointeur sur la m�moire allou�e
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

class TamponPartage
{ 
  public :

  // constructeurs
  TamponPartage ();
  TamponPartage (void* memoire,
                 void  (*f) (void *, void *), void *arg = 0);

  // copie constructeur et affectation
  TamponPartage             (const TamponPartage& t);
  TamponPartage& operator = (const TamponPartage& t);

  // destructeur
  ~TamponPartage ();

  // fonctions d'acc�s aux �l�ments internes
  int   references () const { return acces_->compteur (); }
  void* memoire    () const { return acces_->memoire  (); }

  private:
  class Acces { 
                public :
                      Acces    () : compteur_ (1), memoire_ (0) {}
                      ~Acces () {}

                void  initMemoire (void *m) { memoire_  = m; }
                int   operator ++ (int)     { return compteur_++; }
                int   operator -- (int)     { return compteur_--; }

                int   compteur    ()        { return compteur_; }
                void *memoire     ()        { return memoire_;  }

                private :
                      int   compteur_;
                      void* memoire_;

                      Acces (const Acces & other) {}
                      Acces & operator = (const Acces & other)
                      {
                         return *this;
                      }

              };

  Acces *acces_;
  void  (*fonctionLiberation_) (void *memoire, void *arg);
  void  *arg_;

};

#endif

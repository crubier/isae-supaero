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
//>       ClubVersion.cpp
//
//$Resume
//       fichier d'implantation de la fonction ClubVersion
//
//$Description
//       Module de d�finition de la fonction
//
//$Contenu
//>       const char *clubVersion()
//
//$Historique
//       $Log: ClubVersion.cpp,v $
//       Revision 4.10  2003/07/09 08:09:46  club
//       remplacement de VERSION par PACKAGE_VERSION pour compatibilit� avec autoconf 2.57 (DM 24)
//
//       Revision 4.9  2003/02/03 09:13:22  club
//       DM-ID 17 Changement de l'extension du fichier dans le bandeau
//
//       Revision 4.8  2000/10/24 14:21:00  club
//       Remplacement de l'include ClubConfig.h par ClubConfigNoInstall.h
//
//       Revision 4.7  2000/07/03 08:57:19  club
//       Ajout du copyright CNES
//
//       Revision 4.6.2.1  2000/03/30 14:46:47  club
//       ajout du copyright CNES
//
//       Revision 4.6  1998/07/29 09:58:16  club
//       utilisation de la macro mise en place par configure
//
//       Revision 4.5  1998/07/27 10:13:43  club
//       passage � une configuration de type GNU (fichier ClubConfig.h g�n�r�)
//
//       Revision 4.4  1998/07/07 15:08:13  luc
//       correction du cas des TamponPartage r�affect�s
//       sans jamais avoir �t� initialis�s
//
//       Revision 4.3  1998/07/02 15:38:19  luc
//       correction d'une erreur de construction de message d'erreur
//       (oubli de r�initialisation d'une variable statique)
//
//       Revision 4.2  1998/06/24 08:52:29  luc
//       correction d'un �crasement m�moire lors des lib�rations de cha�nes
//       modification du format des en-t�te
//       �limination des cha�nes statiques RCS
//       �limination des m�thodes XXX::estValide
//
//       Revision 4.1  1998/04/26 13:39:56  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.15  1998/01/22 08:40:09  luc
//       am�lioration des en-t�tes de classes
//       corrections des avertissements (mineurs) g�n�r�s par g++ -Wall
//       correction d'une valeur de retour dans la classe AnalyseurLexical
//       inversion des macro-d�finitions de compilation
//       conditionnelle des exceptions
//
//       Revision 3.14  1997/12/15 11:01:27  luc
//       renommage de la macro-d�finition TRACE en CLUB_TRACE
//       mise � jour de la documentation
//
//       Revision 3.13  1997/10/14 16:52:59  luc
//       acc�l�ration des routines d'allocation de ChaineSimple
//       �limination d'un #ifdef diff�renciant les versions Solaris et Linux
//       (il n'y a d�sormais plus aucune diff�rence)
//       passage par des typedef dans certaines allocations pour simplifier
//       le travail du compilateur SUN
//
//       Revision 3.12  1997/09/17 16:20:27  luc
//       correction d'une erreur d'analyse des r�els avec exposants sign�s
//       (classe AnalyseurLexical)
//       �limination de codes d'erreurs inutilis�s ou redondants
//       augmentation de la taille de la table d'indirection
//
//       Revision 3.11  1997/09/09 10:00:32  luc
//       am�liorations et corrections de messages d'erreurs
//
//       Revision 3.10  1997/09/09 09:58:48  luc
//       reconnaissance des cha�nes C et fortran (AnalyseurLexical)
//       utilisation de AnalyseurLexical dans TamponTexte
//       possibilit� d'utiliser la syntaxe fortran dans TamponTexte
//       refonte compl�te de la traduction des formats fortran
//       ajout des interfaces fortran tradecrCH et tradecrFD
//       ajout d'une protection sur les index n�gatifs dans Adressage
//
//       Revision 3.9  1997/08/21 16:53:57  luc
//       ajout d'en-t�tes de fichiers dans toute la biblioth�que
//       correction d'une erreur de calcul de longueur dans
//       ChaineSimple::ChaineSimple (const char *chaine, int longueur)
//
//       Revision 3.8  1997/07/04 16:23:46  luc
//       ajout de la d�finition de :
//       FichierStructure::FichierStructure (const ChaineSimple& nomFichier,
//                                           ClubErreurs *ptrErreur)
//       
//       Revision 3.7  1997/06/17 16:45:42  luc
//       correction d'une erreur de mise � jour de pointeur dans Adressage
//       
//       Revision 3.6  1997/04/28 14:19:42  luc
//       correction d'une longueur de copie dans ChaineSimple
//       correction d'une allocation de ChaineSimple dans les routines
//       de traduction appelables depuis le fortran
//       
//       Revision 3.5  1997/04/27 17:16:30  luc
//       adaptation de la production des erreurs syst�mes avec errno
//       allocation du tampon d'�criture de ChaineSimple::vFormate
//       uniquement au premier appel
//       
//       Revision 3.4  1997/04/11 10:42:49  luc
//       ajout de la classe AnalyseurLexical
//       correction de la m�thode OptionsAppli::initialiser
//       
//       Revision 3.3  1997/04/03 19:51:27  luc
//       inversion des codes de retour, 0 signifie d�sormais : pas d'erreur
//       
//       Revision 3.2  1997/03/25 15:17:48  luc
//       changement des r�gles de nommage
//       
//       Revision 3.1  1997/03/19 16:01:17  luc
//       utilisation de la classe ChaineSimple
//       renommage de la biblioth�que util_c++ en club
//       passage de SCCS � RCS
//       
//       Revision 2.8  1996/10/04 09:45:28  luc
//       prise en compte de l'�volution des fichiers option_tab_*
//       pour suppression d'un avertissement dans le cas d'une
//       compilation par SUN CC
//       
//       Revision 2.7  1996/09/25 10:57:50  luc
//       prise en compte de l'adaptation des classes d'options
//       aux limitation du compilateur Sun version 3 (ajout d'un "cast" explicite)
//       
//       Revision 2.6  1996/08/30 10:18:17  luc
//       prise en compte de l'ajout d'une protection dans util.h
//       
//       Revision 2.5  1996/08/05 16:35:51  luc
//       prise en compte du passage de traducteur.cc en version 2.3
//       (introduction des '/' dans les formats fortran)
//       
//       Revision 2.4  1996/08/01 12:15:29  luc
//       prise en compte de l'�volution de adressage.cc (correction de bug)
//       
//       Revision 2.3  1996/07/26 18:51:03  luc
//       prise en compte du passage de options_appli.cc en version 2.2
//       pour correction d'une erreur de fin de cha�ne de caract�res
//       
//       Revision 2.2  1996/07/18 14:17:18  luc
//       prise en compte du passage de traducteur.cc en version 2.2
//       
//       Revision 2.1  1996/07/15 17:42:28  luc
//       archivage de l'�tat des fichiers composant la version 2.1 de libutil_c++.a
//       
//       Revision 1.1  1996/07/15 17:00:18  luc
//       Initial revision
//
//$Version
//       $Id: ClubVersion.cpp,v 4.10 2003/07/09 08:09:46 club Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include <ClubConfigNoInstall.h>

#include "club/ClubVersion.h"

const char *clubVersion ()
{ return PACKAGE_VERSION; }

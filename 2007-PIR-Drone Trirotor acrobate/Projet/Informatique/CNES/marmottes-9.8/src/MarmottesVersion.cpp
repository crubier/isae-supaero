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
//       Marmottes
//
//$Nom
//>       MarmottesVersion.cpp
//
//$Resume
//       fichier d'implantation de la fonction MarmottesVersion
//
//$Description
//       Module de d�finition de la fonction
//
//$Contenu
//>       const char *marmottesVersion()
//
//$Historique
//       $Log: MarmottesVersion.cpp,v $
//       Revision 6.8  2003/07/09 12:52:15  marmottes
//       remplacement de VERSION par PACKAGE_VERSION pour compatibilit� avec autoconf 2.57 (DM 24)
//
//       Revision 6.7  2003/02/04 16:30:12  marmottes
//       DM-ID 17 Mise � jour de l'extension du fichier dans le bandeau
//
//       Revision 6.6  2000/11/13 10:04:16  luc
//       changement du nom du fichier d'inclusion
//
//       Revision 6.5  2000/03/30 17:01:19  luc
//       ajout du copyright CNES
//
//       Revision 6.4  1998/07/31 08:42:21  luc
//       utilisation de la macro d�finie par configure
//
//       Revision 6.3  1998/06/25 06:30:53  luc
//       modification du format des en-t�tes
//       �limination des variables statiques RCS
//
//       Revision 6.2  1998/06/02 15:39:57  hotbird
//       correction d'un bug de compilation
//       (instanciation explicite)
//
//       Revision 6.1  1998/05/17 18:41:58  luc
//       inversion de la convention de nommage des attributs
//       �limination des classes ListeSenseurs, SenseurDiedreTan
//       s�paration des interfaces C et fortran dans leurs fichiers
//       partage de la m�me table de simulateurs entre C et fortran
//       ajout des longueurs de messages dans l'interface C
//       ajout d'une possibilit� de changer les unit�s position/vitesse
//       �limination des messages d'erreur inutilis�s
//
//       Revision 5.8  1998/04/26 18:28:32  luc
//       ajout d'une gestion d'unit�s de position et de vitesse variables
//       reformatage de cerains messages d'erreur
//
//       Revision 5.7  1998/03/24 18:43:47  luc
//       correction de signatures de fonctions extern "C" dans Marmottes.h
//
//       Revision 5.6  1998/02/19 17:45:14  luc
//       contournement d'un bug d'optimiseur en ne d�clarant
//       plus inline quelques constructeurs complexes
//
//       Revision 5.5  1998/02/06 17:47:22  luc
//       correction d'un bug de tri des solutions math�matiques et physiques
//       dans le cas des senseurs di�dres et des senseurs d'ascension droite
//       �largissement d'un crit�re de rejet de solutions
//
//       Revision 5.4  1998/02/04 09:50:21  luc
//       correction d'un bug de z�ros non trouv�s dans la r�solution num�rique
//       correction d'un bug dans les mesures de senseurs d'�l�vation
//       mise au format AMIGAU des en-t�tes de classes
//       correction d'avertissements mineurs d�tect�s par l'option -Wall
//
//       Revision 5.3  1997/12/01 14:02:06  luc
//       suppression des inhibitions de senseurs terre par la lune
//       et le soleil lors des �clipses
//       remplacement de la notion d'astre par la notion de cible
//       ajout d'une cible de type station sol
//       ajout de fichiers d'exemple pour les senseurs
//
//       Revision 5.2  1997/09/23 09:36:24  luc
//       refonte des senseurs de Cardan, d�sormais tous d�riv�s
//       de SenseurGeometrique et utilisables en contr�le
//       ajout d'une cible pour la direction le long de la trace
//       (SenseurOptique et d�riv�s)
//       ajout de la possibilit� de g�rer les unit�
//       dans chaque instance de senseur
//
//       Revision 5.1  1997/09/17 15:32:12  luc
//       �clatement des fichiers (une classe par fichier)
//       ajout de fonctions inhibant la r�solution rapide par extrapolation
//       ajout de fonctions de r�initialisation de simulateur d�j� cr��
//       refonte de la m�thode de filtrage des solutions parasites
//       correction d'une erreur d'initialisation de ModeleGeom (_nombreDomaines)
//       limitation de la copie au seul mod�le actif (ResolveurAttitude)
//       correction du message cible_inconnue (une partie n'�tait pas traduite)
//       r�organisation des Makefiles
//       remplacement de ModeleGeomMono et ModeleGeomAlig par ModeleGeomV1Fixe
//       for�age de la composante scalaire du quaternion � des valeurs positives
//       ajout des senseurs roulis, tangage, lacet
//       ajout du senseur de tangente d'angle di�dre
//       ajout du senseur cart�sien
//       ajout d'une cible terre-soleil (soleil sans parallaxe)
//       pr�paration de l'utilisation de secteurs pour les consignes
//       (en pr�vision d'une r�solution plus s�lective dans une version future)
//
//       Revision 4.2  1997/04/30 08:27:32  luc
//       correction d'une mauvaise utilisation de la r�f�rence interne
//       retourn�e par TraduitVersexterne
//       
//       Revision 4.1  1997/04/27 19:42:56  luc
//       ajout des directions lune et soleil dans l'�tat
//       inversion des codes de retour
//       changement des r�gles de nommage
//       passage de SCCS � RCS
//       extraction de /SOFT_SDM
//       
//       Revision 3.7  1997/04/15 16:08:11  luc
//       correction d'une inversion dans le calcul du moment de l'orbite
//       remont�e possible des champs d'inhibition des senseurs terre
//       
//       Revision 3.6  1997/03/21 18:51:25  luc
//       passage en version 3.6 � la suite de la correction d'un bug
//       fichier affect� : etat.cc (3.1 -> 3.2)
//       
//       Revision 3.5  1997/02/13 12:30:04  luc
//       prise en compte des �volutions de lecture.cc,
//       senseur_geom.h, senseur_geom.cc, et marmottes.cc
//       suite � l'introduction de la cible "moment"
//       et � la suppression des v�rifications sur les dates trop proches
//       dans Marmottes::deuxConsignes
//       
//       Revision 3.4  1997/02/12 11:00:04  luc
//       prise en compte des �volutions de lecture.cc,
//       senseur_geom.h et senseur_geom.cc
//       � la suite de l'introduction de la cible "pseudo-soleil"
//       et de la prise en compte des �clipses par la lune
//       
//       Revision 3.3  1997/02/11 08:38:46  luc
//       prise en compte de l'�volution de marmottes.cc
//       (suppression d'une limitation sur les dates trop proches)
//       
//       Revision 3.2  1997/02/10 11:23:50  luc
//       prise en compte des �volutions de lecture.cc,
//       senseurs_geom.h et senseur_geom.cc,
//       � la suite de l'introduction de la vitesse en tant que cible observable
//       et de la gestion des �clipses de la lune et du soleil
//       
//       Revision 3.1  1997/01/28 12:50:20  luc
//       Evolution majeure :
//       gestion de la vitesse du satellite
//       initialisation du spin d�s le d�but
//       prise en compte des �volutions de etat.h, etat.cc, marmottes.h, marmottes.cc,
//       marmottes_f.h marmottes_f.cc, resolveur_attitude.cc, senseur.h,
//       et senseur_cine.h
//       
//       Revision 2.6  1996/10/18 07:54:16  luc
//       prise en compte de l'�volution de mosaique.cc (correction d'un bug)
//       et des �volutions des etat.cc et modele_geom.cc (ajout de protections)
//       
//       Revision 2.5  1996/10/07 15:46:02  luc
//       prise en compte de l'�volution de mosaique.cc
//       (correction d'une erreur d'index de boucle)
//       et de resolveur_attitude.cc
//       (ajout de conversions explicites pour �viter des avertissements)
//       
//       Revision 2.4  1996/10/03 14:37:06  luc
//       prise en compte de la modification de :
//       continuite.cc, continuite.h, modele_geom.cc
//       pour la correction du prolongement par continuit�,
//       de modele_cine.cc pour la correction des consignes en spin
//       et de lecture.cc pour la correction d'un message d'erreur
//       
//       Revision 2.3  1996/09/11 17:48:52  luc
//       prise en compte de l'ajout du nom dans Senseur (et classes d�riv�es)
//       prise en compte de la correction d'une erreur de r�f�rences multiples
//       en raison de copies inconsid�r�es de pointeurs
//       ajout des interfaces C et fortran MarmottesCopie
//       ajout des interfaces C et fortran MarmottesDeuxConsignes
//       ajout de la m�thode Marmottes:deuxConsignes
//       
//       Revision 2.2  1996/08/06 17:30:47  luc
//       prise en compte de l'utilisation du balayage dans la recherche
//       des visibilit�s d'horizon (mosaique.cc, secteurs.h, secteurs.cc)
//       
//       Revision 2.1  1996/07/31 18:13:07  luc
//       prise en compte des �volutions de fichiers dues au passage en version 2.1
//       (presque tous les fichiers ont �t� touch�s)
//       
//       Revision 1.1  1996/07/31 17:59:19  luc
//       Initial revision
//
//$Version
//       $Id: MarmottesVersion.cpp,v 6.8 2003/07/09 12:52:15 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#include "MarmottesConfigNoInstall.h"

#include "marmottes/MarmottesVersion.h"

const char *marmottesVersion ()
{ return PACKAGE_VERSION; }

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
//>       Marmottes.h
//$Resume
//       fichier d'en-t�te de la classe Marmottes
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class Marmottes
//$Historique
//       $Log: Marmottes.h,v $
//       Revision 3.34  2003/10/22 13:01:12  marmottes
//       DM 0027
//
//       Revision 3.33  2003/02/27 16:17:18  marmottes
//       DM-ID 19 Modifications pour la prise en compte des rayons des astres inhibants
//
//       Revision 3.32  2002/11/28 16:13:40  marmottes
//       Ajout de directive throw oubliees
//
//       Revision 3.31  2002/09/09 13:03:41  marmottes
//       ajout de la m�thode enregistreCorps (DM 0007)
//
//       Revision 3.30  2002/04/04 09:40:37  marmottes
//       Introduction des m�thodes accesSenseur et etat (DM 0004)
//
//       Revision 3.29  2002/02/27 14:09:09  marmottes
//       suppression de la description de la r�vision ins�r�e manuellement
//       et mise � jour du copyright CNES
//
//       Revision 3.28  2002/02/22 09:41:34  marmottes
//       Ajout de la m�thode Marmottes::initialiseDerive (DM 0002)
//
//       Revision 3.27  2002/01/17 09:38:03  marmottes
//       correction de sp�cifications throw (FA 0003)
//
//       Revision 3.26  2001/07/17 15:28:14  luc
//       lancement de CantorErreurs par toutes les fonctions
//       pouvant lire un nouveau senseur
//
//       Revision 3.25  2001/04/04 12:17:32  luc
//       ajout de la m�thode criteresControlabilite
//
//       Revision 3.24  2001/02/27 12:31:51  luc
//       ajout des m�thodes imposeAttitude et imposeSpin
//
//       Revision 3.23  2001/02/07 16:46:26  luc
//       remplacement de la classe non standard hash_map par map
//       modification des exceptions lanc�es par le constructeur
//       par copie et par l'op�rateur d'affectation
//
//       Revision 3.22  2000/10/06 09:13:20  luc
//       �limination de la s�paration entre �tats r�solu et extrapol�
//
//       Revision 3.21  2000/10/02 13:11:08  luc
//       remplacement d'attributs entiers en bool�ens
//       ajout d'un destructeur
//
//       Revision 3.20  2000/09/13 09:41:21  luc
//       remplacement de tous les ChaineSimple par des string
//       remplacement de Adressage par hash_map
//
//       Revision 3.19  2000/09/08 07:53:38  luc
//       ajout d'exceptions dans les signatures des m�thodes
//       interditExtrapolation et autoriseExtrapolation, � la suite de la mise
//       en place du m�canisme de trace d'ex�cution
//
//       Revision 3.18  2000/09/05 13:27:29  luc
//       g�n�ration d'exceptions par le m�canisme de trace d'ex�cution dans la
//       m�thode desinitialise et dans l'op�rateur d'affectation, report du
//       corps de la m�thode desinitialise dans Marmottes.cc
//
//       Revision 3.17  2000/03/30 17:01:22  luc
//       ajout du copyright CNES
//
//       Revision 3.16  1999/11/02 07:19:21  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 3.15  1999/08/25 09:41:03  filaire
//       Changement des signatures de certaines m�thodes (correction des oublis
//       apr�s le passage aux exceptions)
//
//       Revision 3.14  1999/08/06 13:32:17  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 3.13  1998/07/15 12:08:31  luc
//       ajout des m�thodes : modifieCible, initialiseGyro et modifieReference
//       ajout de la m�thode priv�e valideNouvelEtat
//
//       Revision 3.12  1998/06/25 06:02:08  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 3.11  1998/05/14 12:05:17  luc
//       int�gration des fonctionnalit�s de la classe ListeSenseurs
//       directement dans la classe Marmottes
//       transfert des fonctions d'interface C dans un fichier sp�cifique
//
//       Revision 3.10  1998/04/26 18:25:00  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 3.9  1998/04/26 18:21:01  luc
//       ajout d'une gestion d'unit�s de position et de vitesse variables
//
//       Revision 3.8  1998/03/24 18:42:27  luc
//       correction de signatures de fonctions extern "C"
//
//       Revision 3.7  1998/02/19 16:18:14  luc
//       d�placement d'un constructeur inline dans le .cc
//       pour contourner un probl�me d'optimiseur avec g++ 2.8.0
//
//       Revision 3.6  1997/09/21 19:37:15  luc
//       ajout de la possibilit� de faire g�rer les unit�s
//       par chaque instance de senseur
//
//       Revision 3.5  1997/08/20 16:50:48  luc
//       ajout d'une fonction de r�initialisation de simulateur Marmottes
//
//       Revision 3.4  1997/08/20 11:50:34  luc
//       remont�e du choix de la r�solution rapide par extrapolation
//       au niveau de l'utilisateur (r�solution rapide autoris�e par d�faut)
//
//       Revision 3.3  1997/08/20 09:33:22  luc
//       ajout d'un en-t�te de fichier
//       utilisation de ChaineSimple � la place de char *
//
//       Revision 3.2  1997/04/27 19:32:45  luc
//       inversion des codes de retour
//       changement des r�gles de nommage
//       passage de SCCS � RCS
//       
//       Revision 3.1  1997/01/28 12:40:17  luc
//       ajout de la vitesse et du spin � la cr�ation et � la r�initialisation
//       ajout de la vitesse pour les calculs d'attitude
//       ajout de qualificateurs "const"
//       
//       Revision 2.2  1996/09/11 17:30:17  luc
//       ajout de la m�thode deuxConsignes
//       transfert du constructeur par copie dans le .cc
//       ajout des interfaces C MarmottesCopie et MarmottesDeuxConsignes
//       
//       Revision 2.1  1996/07/31 16:48:50  luc
//       abandon des tools.h++ (Rogue Wave)
//       ajout des fonctions MarmottesNouveauRepere, MarmottesCalage,
//       MarmottesRepereBase, MarmottesRepere
//       (et des fonctions correspondantes de la classe Marmottes)
//       �limination de la limitation � quatre simulateurs simultan�s
//       prise en compte du renommage des erreurs.h en util_erreurs.h et marmottes_erreurs.h
//       
//       Revision 1.3  1995/07/12 12:17:35  mercator
//       propagation de la desinitialisation de l'instance aux etats inclus
//       
//       Revision 1.2  1995/07/12 12:01:49  mercator
//       ajout d'un commentaire rappelant les conventions sur les rotations
//       
//       Revision 1.1  1995/01/25 09:29:04  mercator
//       Initial revision
//
//$Version
//       $Id: Marmottes.h,v 3.34 2003/10/22 13:01:12 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_Marmottes_h
#define __marmottes_Marmottes_h

#include <string>
#include <map>

#include "club/FichierStructure.h"

#include "cantor/DeclDBL.h"

#include "marmottes/MarmottesErreurs.h"
#include "marmottes/Etat.h"
#include "marmottes/Senseur.h"
#include "marmottes/ResolveurAttitude.h"
#include "marmottes/BodyEphemC.h"
#include "marmottes/BodyEphemF.h"

//////////////////////////////////////////////////////////////////////////////
//                                RAPPEL                                    //
//                                                                          //
// La convention g�n�rale de repr�sentation de l'attitude par MARMOTTES est //
// que l'attitude transforme des vecteurs inertiels en vecteurs satellites. //
//                                                                          //
// On peut donc utiliser l'attitude MARMOTTES de la facon suivante:         //
//     Soient uIn  les coordonn�es en rep�re inertiel d'un vecteur          //
//     Soient uSat les coordonn�es en rep�re satellite du m�me vecteur      //
//     Soit   att  l'attitude                                               //
//                                                                          //
// Conversion d'un vecteur inertiel en vecteur satellite                    //
//             uSat = att (uIn)             (interface C++     de CANTOR)   //
//        AppliqueRot (att, uIn, uSat)      (interface C       de CANTOR)   //
//   call AppliqueRot (att, uIn, uSat)      (interface fortran de CANTOR)   //
//                                                                          //
// Conversion d'un vecteur satellite en vecteur inertiel                    //
//             uIn = (-att) (uSat)          (interface C++     de CANTOR)   //
//      AppliqueRotInverse (att, uSat, uIn) (interface C       de CANTOR)   //
// call AppliqueRotInverse (att, uSat, uIn) (interface fortran de CANTOR)   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class Marmottes
//
//$Resume
//       classe g�rant un simulateur d'attitude
//
//$Description
//       Cette classe concr�te est la classe de plus haut niveau de la
//       biblioth�que marmottes, elle g�re un simulateur d'attitude
//       complet, avec ses �tats pr�c�dent et courant, ses senseurs de
//       contr�le et ses senseurs de mesures. L'utilisation normale est
//       de cr�er une instance de simulateur avec une position et une
//       attitude initiale, puis � lui faire suivre pas � pas
//       l'�volution du satellite par des appels � la m�thode attitude,
//       qui est la m�thode la plus importante. De temps � autre on
//       peut changer les senseurs de contr�le par la m�thode senseurs.
//
//$Usage
//>     construction : 
//          sans argument, � partir d'un �tat initial et des senseurs
//          � utiliser, par copie
//>     utilisation  : 
//>       Marmottes& operator =          () 
//          affectation
//>       int reinitialise               () 
//          remet � jour l'ensemble de l'instance (senseurs/etat)
//>       int senseurs                   () 
//          met � jour l'instance � partir de nouveaux noms de senseurs
//          (lus dans le fichier)
//>       int nouveauRepere              () 
//          modifie le rep�re courant
//>       int calage                     () 
//          recale le senseur (s'il a un axe de calage pr�d�fini)
//>       int modifieCible               () 
//          m�morise une cible utilisateur pour un senseur optique
//>       int initialiseGyro             () 
//          initialise l'angle d'un gyro int�grateur
//>       int initialiseDerive           () 
//          initialise la d�rive d'un senseur cin�matique
//>       int modifieReference           () 
//          m�morise un rep�re de r�f�rence pour un senseur de Cardan
//>       int deuxConsignes              () 
//          calcule l'attitude v�rifiant deux consignes de mesures
//>       int attitude                   () 
//          calcule l'attitude v�rifiant trois consignes de mesures
//>       int imposeAttitude             () 
//          impose � l'instance une attitude fournie par l'utilisateur
//          (le spin en r�sulte par diff�rences finies)
//>       int imposeSpin                 () 
//          impose � l'instance un spin fourni par l'utilisateur
//          (l'attitude en r�sulte par int�gration)
//>       int repereBase                 () 
//          retourne le rep�re initial du senseur (lu dans le fichier)
//>       int repere                     () 
//          retourne le rep�re courant du senseur
//>       int mesure                     () 
//          initialise le r�el point� par m avec la mesure fournie par
//          le senseur dont le nom est fourni, dans l'�tat courant (le
//          senseur ne correspond pas forc�ment � un des senseurs
//          utilis�s pour le pilotage)
//>       int controlable                () 
//          initialise l'entier point� par c avec l'indicateur de
//          contr�labilit� du senseur dont le nom est fourni, dans
//          l'�tat courant (le senseur ne correspond pas forc�ment �
//          un des senseurs utilis�s pour le pilotage)
//>       int criteresControlabilite     () 
//          initialise les variables point�es par inhibant et eclipsant
//          avec les codes des astres inhibant et �clipsant et le r�el
//          point� par ecart avec l'�cart disponible par rapport � la
//          fronti�re du domaine de fonctionnement du senseur du senseur
//          dont le nom est fourni, dans l'�tat courant (le senseur ne
//          correspond pas forc�ment � un des senseurs utilis�s pour le
//          pilotage)
//>       int unitesPositionVitesse      () 
//          permet de sp�cifier les unit�s dans lesquelles
//          l'utilisateur va donner les position/vitesse (par d�faut
//          on consid�re km et km/s)
//>       int respecterConsignes         () 
//          indique que le senseur dont le nom est fourni ne doit pas
//          convertir les valeurs de consignes qu'on lui donnera par
//          la suite, elles seront d�j� exprim�es dans l'unit�
//          interne.
//>       int convertirConsignes         () 
//          indique que le senseur dont le nom est fourni doit
//          convertir lui-m�me les valeurs de consignes qu'on lui
//          donnera par la suite de l'unit� utilisateur � l'unit�
//          interne.
//>       int respecterMesures           () 
//          indique que le senseur dont le nom est fourni ne doit pas
//          convertir les mesures qu'il fournira par la suite �
//          l'utilisateur directement dans l'unit� interne.
//>       int convertirMesures           () 
//          indique que le senseur dont le nom est fourni doit
//          convertir les mesures qu'il fournira par la suite �
//          l'utilisateur de l'unit� interne � l'unit� utilisateur.
//>       void desinitialise             () 
//          d�sinitialise l'instance
//>       const string& nomFichier       () 
//          retourne le nom du fichier des senseurs.
//>       int estInitialise              () 
//          indique si l'instance a �t� initialis�e
//>       int wMax                       () 
//          met � jour le param�tre de r�glage correspondant � la
//          vitesse maximale de rotation du satellite utilis�e dans
//          les r�solutions avec senseurs cin�matiques.
//>       int convergence                () 
//          met � jour le param�tre de r�glage correspondant au seuil
//          de convergence des algorithmes de r�solution.
//>       int dichotomie                 () 
//          met � jour le param�tre de r�glage correspondant au nombre
//          de tranches de dichotomie pour la s�paration des extremums
//          locaux.
//>       void autoriseExtrapolation     () 
//          autorise l'utilisation de simple extrapolations pour acc�l�rer
//          les calculs (on peut �viter les r�solutions compl�tes)
//>       void interditExtrapolation     () 
//          interdit l'utilisation de simple extrapolations pour acc�l�rer
//          les calculs (on DOIT faire des r�solutions compl�tes)
//>       Senseur * accesSenseur         () 
//          r�cup�re le pointeur sur le senseur initialis� � partir de son
//          nom et de ses caract�ristiques lues dans un fichier
//>       void enregistreCorps     () 
//          donne acc�s aux fonctions utilisateurs de calculs d'�ph�m�rides 
//          par rapport au corps central (�crites en C ou en fortran)
//
//>       void lireParametres      () 
//          donne acc�s aux valeurs courantes des parametres suivants :     
//          date, position, vitesse, attitude, spin
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000-2001-2002 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////
class Marmottes
{
public :

  // constructeurs
  Marmottes ();
  Marmottes (double date, const VecDBL& position, const VecDBL& vitesse,
             const RotDBL& attitude, const VecDBL& spin,
             const string& fichier,
             const string& senseur1,
             const string& senseur2,
             const string& senseur3) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs)
  {
    reinitialise (date, position, vitesse, attitude, spin,
                  fichier, senseur1, senseur2, senseur3);
  }
  Marmottes (const Marmottes& m)
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  Marmottes& operator = (const Marmottes& m)
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

  // destructeur
  ~Marmottes ();

  // fonctions de modification des �l�ments internes
  void desinitialise   ()
    throw (MarmottesErreurs);
  void reinitialise    (double date,
                        const VecDBL& position, const VecDBL& vitesse,
                        const RotDBL& attitude, const VecDBL& spin,
                        const string& fichier,
                        const string& senseur1,
                        const string& senseur2,
                        const string& senseur3) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void senseurs        (const string& fichier,
                        const string& senseur1,
                        const string& senseur2,
                        const string& senseur3) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void nouveauRepere   (const string& fichier,
                        const string& senseur,
                        const RotDBL& nouveau) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void calage          (const string& fichier,
                        const string& senseur,
                        double c) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void modifieCible    (const string& fichier,  
                        const string& senseur,
                        const VecDBL& cible) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);  
  void initialiseGyro  (const string& fichier,  
                        const string& senseur,
                        double              date,
                        double              angle)  
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void initialiseDerive(const string& fichier,
                        const string& senseur,
                        double derive) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);  
  void modifieReference (const string& fichier,  
                         const string& senseur,
                         const RotDBL&       reference) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);  

  // fonctions de r�solution
  void deuxConsignes (double date,
                      const VecDBL& position, const VecDBL& vitesse,
                      double m1, double m2,
                      RotDBL *attitude, VecDBL *spin)
    throw (CantorErreurs, MarmottesErreurs);
  void attitude      (double date,
                      const VecDBL& position, const VecDBL& vitesse,
                      double m1, double m2, double m3,
                      RotDBL *attit, VecDBL *spin) 
    throw (CantorErreurs, MarmottesErreurs);
  void imposeAttitude (double date,
                       const VecDBL& position, const VecDBL& vitesse,
                       const RotDBL& attit) 
    throw (MarmottesErreurs);
  void imposeSpin     (double date,
                       const VecDBL& position, const VecDBL& vitesse,
                       const VecDBL& spin) 
    throw (MarmottesErreurs);

  // fonctions d'utilisation de l'attitude
  void repereBase    (const string& fichier,
                      const string& senseur, RotDBL *r) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void repere        (const string& fichier,
                      const string& senseur, RotDBL *r) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void mesure        (const string& fichier,
                      const string& senseur, double *m) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void controlable   (const string& fichier,
                      const string& senseur, int    *c) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void criteresControlabilite (const string& fichier,
                               const string& senseur,
                               Senseur::codeAstre *inhibant,
                               Senseur::codeAstre *eclipsant,
                               double *ecartFrontiere,
                               bool *amplitudeSignificative) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

  void unitesPositionVitesse (const string& unitePos,
                              const string& uniteVit)
    throw (MarmottesErreurs);

  void respecterConsignes (const string& fichier,
                           const string& senseur) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void convertirConsignes (const string& fichier,
                           const string& senseur) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void respecterMesures   (const string& fichier,
                           const string& senseur) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);
  void convertirMesures   (const string& fichier,
                           const string& senseur) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

  const string& nomFichier    () const
                { return fichier_.nomFichier (); }

  bool          estInitialise () const
                { return initialise_; }

  // r�cup�ration de l'�tat
  const Etat&   etat          () const
                { return etat_ ; }

  // fonctions de r�glage des param�tres de l'algorithme de r�solution
  void wMax (double omega) 
    throw (MarmottesErreurs);

  void convergence (double seuil) 
    throw (MarmottesErreurs);

  void dichotomie (int tranches) 
    throw (MarmottesErreurs);

  void autoriseExtrapolation () 
    throw (MarmottesErreurs);

  void interditExtrapolation () 
    throw (MarmottesErreurs);

  // r�cup�ration de pointeurs
  Senseur * accesSenseur(const string& fichier,
                         const string& senseur) 
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

  // r�cup�ration des fonctions utilisateurs de calculs d'�ph�m�rides
  void enregistreCorps (double equatorialRadius, 
                        double oblateness, double rotationVelocity,
                        double moonRadius, double sunRadius,
                        BodyEphemC::TypeFuncTsid *tsidFunc, 
                        BodyEphemC::TypeFuncPos *sunFunc, BodyEphemC::TypeFuncPos *moonFunc, 
                        BodyEphemC::TypeFuncPos *earthFunc) 
    throw (MarmottesErreurs);

  void enregistreCorps (double equatorialRadius, 
                        double oblateness, double rotationVelocity, 
                        double moonRadius, double sunRadius,
                        BodyEphemF::TypeFuncTsid *tsidFunc, 
                        BodyEphemF::TypeFuncPos *sunFunc, BodyEphemF::TypeFuncPos *moonFunc, 
                        BodyEphemF::TypeFuncPos *earthFunc) 
    throw (MarmottesErreurs);

  void lireParametres  (double *ptrDate,
                        VecDBL *ptrPosition, VecDBL *ptrVitesse, 
                        RotDBL *ptrAttitude, VecDBL *ptrSpin);

private :

  bool                 initialise_;
  bool                 extrapolationOk_;
  Etat                 etat_;

  ResolveurAttitude    solveur_;

  FichierStructure     fichier_;
  map<string, Senseur *> senseurs_;

  void      initialiseSenseurs (const string& nomFichier)
    throw (ClubErreurs, MarmottesErreurs);

  Senseur* recupParNom        (const string& nom)
    throw (ClubErreurs, CantorErreurs, MarmottesErreurs);

  void     valideNouvelEtat   (double date,
                               const VecDBL& position, const VecDBL& vitesse,
                               const RotDBL& attitude, const VecDBL& spin);

};

#endif

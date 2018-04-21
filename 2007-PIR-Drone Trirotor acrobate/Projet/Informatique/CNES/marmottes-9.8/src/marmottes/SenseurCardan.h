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
//>       SenseurCardan.h
//
//$Resume
//       fichier d'en-t�te de la classe SenseurCardan
//
//$Description
//       Module de d�claration de la classe
//
//$Contenu
//>       class SenseurCardan
//>       enum typeGenre     
//>       enum typeReference 
//
//$Historique
//       $Log: SenseurCardan.h,v $
//       Revision 1.15  2002/12/11 17:12:23  marmottes
//       DM-ID 12 Ajout d'un constructeur par d�faut (prot�g�) pour pr�venir celui construit par le compilateur.
//
//       Revision 1.14  2002/12/02 17:04:19  marmottes
//       DM-ID 12 R�organisation des fichiers H de d�claration des classes selon le principe public/protected/private.
//
//       Revision 1.13  2002/01/17 09:38:03  marmottes
//       correction de sp�cifications throw (FA 0003)
//
//       Revision 1.12  2001/01/25 16:26:20  luc
//       changement du type de refUtilInitialisee_ en bool
//
//       Revision 1.11  2000/09/13 10:04:33  luc
//       remplacement de tous les ChaineSimple par des string
//
//       Revision 1.10  2000/03/30 17:01:23  luc
//       ajout du copyright CNES
//
//       Revision 1.9  1999/11/02 07:19:22  luc
//       correction de la macro de protection contre les inclusions multiples
//
//       Revision 1.8  1999/08/25 09:41:04  filaire
//       Changement des signatures de certaines m�thodes (correction des oublis
//       apr�s le passage aux exceptions)
//
//       Revision 1.7  1999/08/06 13:32:18  filaire
//       Passage � la gestion des erreurs par les exceptions
//
//       Revision 1.6  1998/08/07 09:38:27  luc
//       ajout d'attributs s�par�s pour le rep�re d�fini par l'utilisateur
//
//       Revision 1.5  1998/07/15 12:27:32  luc
//       mod�lisation de tous les angles
//       (auparavant, le troisi�me angle n'�tait pas g�r� par cette classe)
//       support de plusieurs rep�res de r�f�rences
//       (dont un sp�cifi� par l'utilisateur)
//
//       Revision 1.4  1998/06/25 06:14:01  luc
//       modification du format des en-t�tes
//       �limination de la variable statique RCS
//
//       Revision 1.3  1998/04/26 18:25:28  luc
//       inversion de la convention de nommage des attributs
//
//       Revision 1.2  1997/09/23 09:25:46  luc
//       ajout d'une gestion des unit�s de consigne et de mesure
//       interne au senseur
//
//       Revision 1.1  1997/09/21 11:14:07  luc
//       Initial revision
//
//$Version
//       $Id: SenseurCardan.h,v 1.15 2002/12/11 17:12:23 marmottes Exp $
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////

#ifndef __marmottes_SenseurCardan_h
#define __marmottes_SenseurCardan_h

#include "marmottes/SenseurGeometrique.h"

///////////////////////////////////////////////////////////////////////////////
//$<AM-V1.0>
//
//$Nom
//>       class SenseurCardan
//
//$Resume
//       mod�lisation de tous les pseudo-senseurs d'angle de Cardan
//
//$Description
//       Cette classe concr�te regroupe tous les mod�les de senseurs
//       mesurant des angles de Cardan (ou leurs variations). Seules
//       les deux premiers angles de chaque succession de rotation sont
//       mod�lis�s par cette classe, la troisi�me rotation est toujours
//       repr�sentable directement par un senseur di�dre classique, la
//       conversion est r�alis�e d�s la lecture du senseur.
//
//$Usage
//>     construction : 
//          � partir du nom, du rep�re satellite, de l'axe de calage
//          et de la pr�cision, par copie
//          La classe �tant abstraite, les constructeurs sont appel�s
//          par les constructeurs des classes d�riv�es.
//>     utilisation  : 
//>       enum typeGenre      : 
//          identification d'une rotation dans un triplet ordonn�
//>       enum typeReference  : 
//          identification d'un rep�re de r�ference
//>       SenseurCardan& operator =        () 
//          affectation
//>       virtual void respecterMesures    () 
//          force le senseur � respecter les unit�s de mesures dans
//          ses sorties
//>       virtual void convertirMesures    () 
//          force le senseur � convertir les unit�s de mesures dans
//          ses sortie
//>       virtual double mesure            () 
//          retourne la mesure que donnerait le senseur dans l'�tat donn�
//>       virtual int modeliseConsigne     () 
//          permet de stocker un mod�le de la consigne que doit
//          respecter un senseur contr�lant l'attitude du satellite
//          dans l'�tat courant ATTENTION: dans cet �tat, l'attitude
//          ne doit pas �tre utilis�e, elle ne sera initialis�e
//          correctement qu'� la fin de la r�solution ayant utilis� ce
//          mod�le!
//>       virtual int modifieReference     () 
//          initialise l'attitude de r�f�rence d'un senseur de Cardan
//>       virtual Senseur* copie           () 
//          retourne une copie du senseur allou�e en m�moire
//>       virtual typeGeom typeGeometrique () 
//          retourne le type de senseur g�om�trique (pseudoSenseur)
//>       virtual int controlable          () 
//          indique si le senseur serait capable de contr�ler
//          l'attitude de l'�tat donn�
//
//$Auteur
//       L. Maisonobe CNES
//       Copyright (C) 2000 CNES
//
//$<>
///////////////////////////////////////////////////////////////////////////////


class SenseurCardan : public SenseurGeometrique
{

  // on doit commencer par d�clarer les �num�rations visibles de l'ext�rieur
  public :

  enum typeGenre     { GenreInconnu,
                       LRTLacet,   LRTRoulis,  LRTTangage,
                       LTRLacet,   LTRTangage, LTRRoulis,
                       RLTRoulis,  RLTLacet,   RLTTangage,
                       RTLRoulis,  RTLTangage, RTLLacet,
                       TLRTangage, TLRLacet,   TLRRoulis,
                       TRLTangage, TRLRoulis,  TRLLacet
                     };

  enum typeReference { ReferenceInconnue,
                       Geocentrique, OrbitalTNW,    OrbitalQSW,
                       Inertiel,     Topocentrique, Utilisateur
                     };

  // constructeurs
  SenseurCardan (typeGenre genre, typeReference reference,
                 const string& nom,
                 const RotDBL& repere, const VecDBL& axeCalage,
                 double precision)
    : SenseurGeometrique (nom, repere, axeCalage, radians (precision)),
      genre_ (genre), reference_ (reference),
      refUtilInitialisee_ (false), referenceUtilisateur_ (1.0, 0.0, 0.0, 0.0),
      xIn_ (1.0, 0.0, 0.0), yIn_ (0.0, 1.0, 0.0), zIn_ (0.0, 0.0, 1.0)
  {}

  SenseurCardan (const SenseurCardan& s)
    : SenseurGeometrique (s),
      genre_ (s.genre_), reference_ (s.reference_),
      refUtilInitialisee_ (s.refUtilInitialisee_),
      referenceUtilisateur_ (s.referenceUtilisateur_),
      xIn_ (s.xIn_), yIn_ (s.yIn_), zIn_ (s.zIn_)
  {}

  SenseurCardan& operator = (const SenseurCardan& s);

  // destructeur
  virtual ~SenseurCardan () {}

  virtual void respecterMesures ();
  virtual void convertirMesures ();

  virtual Senseur* copie           () const
                                   { return new SenseurCardan (*this); }

  virtual typeGeom typeGeometrique () const { return pseudoSenseur; }

  virtual double   mesure          (const Etat& etat)
    throw (MarmottesErreurs);

  virtual int      controlable     (const Etat& etat)
    throw (CantorErreurs, MarmottesErreurs)
                                   { return 1; }

  virtual void     modeliseConsigne (const Etat& etat, double valeur)
    throw (CantorErreurs, MarmottesErreurs);

  // fonction de mise � jour du rep�re de r�f�rence utilisateur
  virtual void     modifieReference (const RotDBL& reference)
    throw (MarmottesErreurs);

  protected :

  // constructeur par defaut : ne doit JAMAIS �tre utilis�
  SenseurCardan () {}

  private :

  typeGenre     genre_;
  typeReference reference_;

  bool          refUtilInitialisee_;
  RotDBL        referenceUtilisateur_;

  VecDBL        xIn_;
  VecDBL        yIn_;
  VecDBL        zIn_;

  void metAJourReference (const Etat& etat)
    throw (MarmottesErreurs);

};

#endif

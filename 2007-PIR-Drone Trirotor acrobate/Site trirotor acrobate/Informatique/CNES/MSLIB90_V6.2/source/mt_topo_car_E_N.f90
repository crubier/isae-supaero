subroutine mt_topo_car_E_N (pos_E, pos_N, code_retour, vit_E, vit_N, jacob)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Passage d'un repere TOPOcentrique Est (convention axe Ox vers l'Est) au repere topocentrique Nord associe
! ===   (convention axe Ox vers le Nord) en coordonnees CARtesiennes.
!
! Note d'utilisation:  La transformation inverse peut s'effectuer par la routine mt_topo_car_N_E
! ==================
!
! Historique:
! ==========
!   + Version 1.0 (SP 256 ed01 rev00): creation a partir de la routine MVTOPO (MVRTXY) de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mt_topo_car_E_N.h'

! Autres declarations
! -------------------
intrinsic present

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB mt_topo_car_E_N.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mt_topo_car_E_N.f90,v 1.7 2003/10/14 12:53:23 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

!-----------------------------------------------
! calcul vecteur position en repere topocentrique 
!-----------------------------------------------

pos_N(1) = pos_E(2)
pos_N(2) = -pos_E(1)
pos_N(3) = pos_E(3)

!----------------------
! calcul optionnels 
!----------------------
if (present(jacob)) then           ! calcul du jacobien 

   jacob(:,:) = 0._pm_reel

   ! calcul des derivees partielles des vecteurs position et vitesse par rapport a x,y,z,vx,vy,vz
   !
   jacob(1,2) = 1._pm_reel    !     par rapport a x 
   jacob(2,1) = -1._pm_reel   !     par rapport a y 
   jacob(3,3) = 1._pm_reel    !     par rapport a z 
   jacob(4,5) = 1._pm_reel    !     par rapport a vx 
   jacob(5,4) = -1._pm_reel   !     par rapport a vy 
   jacob(6,6) = 1._pm_reel    !     par rapport a vz 

end if


if (present(vit_N).and..not.present(vit_E)) then ! mauvais parametrage
      code_retour%valeur = pm_err_para_option
      go to 6000
else if (present(vit_E).and.present(vit_N)) then   !  calcul vecteur vitesse en repere topocentrique
      vit_N(1) =  vit_E(2)
      vit_N(2) = -vit_E(1)
      vit_N(3) =  vit_E(3)
end if
if (.not.present(vit_N).and. present(vit_E))  code_retour%valeur = pm_warn_para_option ! parametrage optionnel incoherent



6000 continue

code_retour%routine = pm_num_mt_topo_car_E_N
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine mt_topo_car_E_N

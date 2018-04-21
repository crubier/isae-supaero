subroutine mri_eclip_vrai_t1_t2 (model, jul1950_t1, jul1950_t2, mat_pass, retour)

! (C) Copyright CNES - MSLIB - 1998-2003

!************************************************************************
!
! But:  Calcul de la matrice de passage du repere ECLIPtique VRAI a T1 au repere ECLIPtique VRAI a T2.
! ===
!
! Note d'utilisation: - Routine interne
! ==================
!
! Historique:
! ==========
!   + Version 1.0 (SP 279 ed01 rev00): creation a partir de la routine MRCCVV de la MSLIB f77
!   + Version 2.0 (DE 362 ed01 rev00): suppression des commentaires sur la limitation sur les dates et des codes retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!************************************************************************


! Modules
! =======
use int_mslib_mr_nuta
use int_mslib_mri_eclip_M_eclip_V
use code_modeles_mslib ! contient toutes les valeurs possibles pour "model"

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mri_eclip_vrai_t1_t2.h'

! Autres declarations
! -------------------

real(pm_reel), dimension(3,3)  :: mat_pass1, mat_pass2  ! matrices intermediaires
type(tm_nuta)                  :: nuta                  ! nutation en longitude et en obliquite
type(tm_code_retour)           :: code_retour
integer                        :: modele_nutation       ! indicateur du modele de nutation associe a "model"

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB mri_eclip_vrai_t1_t2.f90: derniere modification V4.1 >'

intrinsic matmul, cos, sin

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mri_eclip_vrai_t1_t2.f90,v 1.8 2003/10/14 12:50:31 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
retour = pm_OK

if (model == pm_lieske_wahr) then 

   ! calcul de la matrice de passage du repere ecliptique vrai a t1 au repere ecliptique vrai a t2
   ! avec le modele de precession de Lieske et le modele de nutation de Wahr (epoque de base : J2000)

   modele_nutation = pm_wahr


   ! ===========================
   ! nutation en longitude a t1
   ! ===========================

   call mr_nuta (modele_nutation, jul1950_t1, nuta, code_retour)
   ! pas de test de retour car il ne peut etre que nul (controles deja effectues)

   ! ===================
   ! matrice de nutation
   ! ===================

   mat_pass1(1,1) = cos( nuta%long )
   mat_pass1(1,2) = sin( nuta%long )
   mat_pass1(1,3) = 0._pm_reel

   mat_pass1(2,1) =-sin( nuta%long )
   mat_pass1(2,2) = cos( nuta%long )
   mat_pass1(2,3) = 0._pm_reel

   mat_pass1(3,1) = 0._pm_reel
   mat_pass1(3,2) = 0._pm_reel
   mat_pass1(3,3) = 1._pm_reel


   ! ===============================================================
   ! calcul de la matrice de passage du repere ecliptique moyen a t1
   ! au repere  ecliptique vrai a t2
   ! ===============================================================

   call mri_eclip_M_eclip_V (model, jul1950_t1, jul1950_t2, mat_pass2, retour)
   ! pas de test de retour car il ne peut etre que nul (controles deja effectues)


   ! =================
   ! produit matriciel
   ! =================

   mat_pass(:,:) = matmul(mat_pass2(:,:), mat_pass1(:,:))

else    !    modele inconnu

   retour = pm_err_ind_model

end if

6000 continue

end subroutine mri_eclip_vrai_t1_t2

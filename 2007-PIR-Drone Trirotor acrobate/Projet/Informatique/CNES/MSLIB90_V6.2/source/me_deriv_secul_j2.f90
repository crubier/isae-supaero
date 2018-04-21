subroutine me_deriv_secul_j2( mu, r_equa, c20, a, e, i, deriv_pom, deriv_gom, deriv_M, code_retour)

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But:  DERIVes SECULaires des elements kepleriens dus au J2.
! ===
!
! Note d'utilisation:  Applicable aux orbites elliptiques uniquement, e dans [0,1[
! ==================
!
! Historique:
! ==========
!   + Version 1.0 (SP 246 ed01 rev00): creation a partir de la routine MEKED0 de la MSLIB f77
!   + Version 3.1 (DE globale 439 ed01 rev00) : ajout des champs %biblio et %message pour le code retour
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!
!************************************************************************


! Modules
! =======
use test_mslib

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use numero_routine_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_me_deriv_secul_j2.h'

! Autres declarations
! -------------------

real(pm_reel)   ::   rcosi,rmm,rtet,rg2
real(pm_reel)   ::   rc1,rc2
real(pm_reel)   ::   rtet2,rcosi2
real(pm_reel)   ::   eps100         ! constante de test pour les reels

intrinsic epsilon, cos, sqrt


character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
                     '@(#) Fichier MSLIB me_deriv_secul_j2.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: me_deriv_secul_j2.f90,v 1.7 2003/10/14 12:46:53 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
code_retour%valeur = pm_OK

! initialisation constante de test
! ................................

eps100 = 100._pm_reel * epsilon(1._pm_reel)

! Controle des donnees
! --------------------

if (mu < 0._pm_reel) then   ! constante de la gravitation negative
   code_retour%valeur= pm_err_mu_negatif
   go to 6000
end if

if (a <= eps100) then
   if (a < 0._pm_reel) then        ! demi-grand axe < 0.
      code_retour%valeur= pm_err_a_negatif
      go to 6000
   else                    ! demi-grand axe = 0.
      code_retour%valeur= pm_err_a_nul
      go to 6000
   end if
end if

if ( e < 0._pm_reel.or.e > ( 1._pm_reel - pm_eps_parab) ) then     ! orbite non elliptique
   code_retour%valeur = pm_err_e_non_ellip
   go to 6000
end if

! initialisations
! ---------------

deriv_pom = 0._pm_reel
deriv_gom = 0._pm_reel
deriv_M   = 0._pm_reel


! calculs intermediaires
! ----------------------

rcosi = cos  ( i )
rmm   = sqrt ( mu / a**3 )
rtet  = sqrt ( 1._pm_reel - e**2 )
rtet2 = rtet * rtet
rcosi2 = rcosi * rcosi

rc1   = -3._pm_reel*rmm*c20*r_equa*r_equa
rc2   =  2._pm_reel*a*a*rtet2
rg2   =  rc1 / rc2

! calcul des derives seculaires des elements kepleriens
!  ----------------------------------------------------

rc1   = rg2 * (5._pm_reel*rcosi2 - 1._pm_reel)
rc2   = 2._pm_reel*rtet2
deriv_pom = rc1 / rc2        ! derive seculaire de l'argument du perigee

rc1   = -rg2*rcosi
rc2   = rtet2
deriv_gom = rc1 / rc2        ! derive seculaire de la longitude du noeud ascendant

rc1   = rg2 * (3._pm_reel*rcosi2 - 1._pm_reel)
rc2   = 2._pm_reel*rtet
deriv_M   = rmm + rc1 / rc2  ! derive seculaire de l'anomalie moyenne


6000 continue

code_retour%routine = pm_num_me_deriv_secul_j2
code_retour%biblio = pm_mslib90
if (code_retour%valeur /= pm_OK) code_retour%message = ' '

end subroutine me_deriv_secul_j2

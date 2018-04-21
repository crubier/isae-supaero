
module valeur_code_retour_mslib

! (C) Copyright CNES - MSLIB - 1997-2005

!************************************************************************
!
! But:  Definition des valeurs (numeriques) des codes retour. 
! ===
!
! Note d'utilisation:  toute routine ou module utilisant parametre_mslib connait implicitement ce module.
! ==================
!
! Historique:
! ==========
!   + Version 0.1 (SP 175 ed01 rev00): creation
!   + Version 0.1.1 (DE globale 182 ed01 rev00): modification regle de marquage pour info_utilisateur
!   + Version 1.0 (sans DE): ajout de nouveaux codes retour
!   + Version 2.0 (sans DE): ajout de nouveaux codes retour
!   + Version 3.0 (sans DE): ajout de nouveaux codes retour
!   + Version 3.2 (sans DE) : ajout d'une nouvelle plage
!   + Version 4.0 (sans DE) : modif de la ligne rcs_id, et ajout de nouveaux codes retour
!   + Version 4.1 (sans DE) : ajout de nouveaux codes retour
!   + Version 5.0 (sans DE) : ajout de nouveaux codes retour
!   + Version 6.0 (sans DE): ajout de nouveaux codes retour
!   + Version 6.2 (sans DE): ajout de nouveaux codes retour
!************************************************************************

use longueur_chaine_mslib

implicit none

!************************************************************************

!.............
! Cas nominal
!.............

integer,parameter :: pm_OK = 0

!.................................................
! Probleme sur la valeur d'une constante physique [ +/- 1001 , +/- 1099 ]
!.................................................

integer,parameter :: pm_err_mu_negatif         = -1001
integer,parameter :: pm_err_mu_nul             = -1002
integer,parameter :: pm_err_apla_sup1          = -1003
integer,parameter :: pm_err_apla_negatif       = -1004
integer,parameter :: pm_err_cn0_nul            = -1005

!..........................................................
! Probleme sur la valeur du demi grand-axe de la conique: a [ +/- 1101 , +/- 1199 ]
!..........................................................

integer,parameter :: pm_err_a_negatif         = -1101
integer,parameter :: pm_err_a_nul             = -1102
integer,parameter :: pm_err_a_infini          = -1103

!............................................
! Probleme sur la valeur de l'excentricite e [ +/- 1201 , +/- 1299 ]
!............................................
integer,parameter :: pm_warn_e_circul_i_equa  = +1201
integer,parameter :: pm_warn_e_grand_eck_hech = +1202
integer,parameter :: pm_warn_e_faible_brouwer = +1203
integer,parameter :: pm_warn_e_circul         = +1204
integer,parameter :: pm_warn_e_parab          = +1206

integer,parameter :: pm_err_e_negatif         = -1201
integer,parameter :: pm_err_e_circul          = -1202
integer,parameter :: pm_err_e_grand_brouwer   = -1204
integer,parameter :: pm_err_e_parab           = -1205
integer,parameter :: pm_err_e_non_ellip       = -1208
integer,parameter :: pm_err_e_hyperb          = -1209
integer,parameter :: pm_err_e_grand_eck_hech  = -1210
integer,parameter :: pm_err_e_faible_brouwer  = -1211
integer,parameter :: pm_err_e_faible          = -1212
integer,parameter :: pm_err_jac_non_calc_e_circul = -1213
integer,parameter :: pm_err_anom_v_incompatible_e = -1214

!.................................................................................
! Probleme sur la valeur de l'inclinaison i ou sur le vecteur inclinaison (ix,iy) [ +/- 1301 , +/- 1399 ]
!.................................................................................

integer,parameter :: pm_warn_i_faible_brouwer = +1303
integer,parameter :: pm_warn_i_equa           = +1302

integer,parameter :: pm_err_i_negatif         = -1301
integer,parameter :: pm_err_i_equa            = -1302
integer,parameter :: pm_err_i_critique        = -1304
integer,parameter :: pm_err_i_sup_pi          = -1305
integer,parameter :: pm_err_ix_iy_sup2        = -1306
integer,parameter :: pm_err_i_equa_retro      = -1307
integer,parameter :: pm_err_jac_non_calc_i_equa = -1308

!............................................
! Probleme sur une date, une duree, un temps [ +/- 1401 , +/- 1499 ]
!............................................

integer,parameter :: pm_err_an_inf1950       = -1401
integer,parameter :: pm_err_mois_interval    = -1402
integer,parameter :: pm_err_jour_interval    = -1403
integer,parameter :: pm_err_jul1950_negatif  = -1404
integer,parameter :: pm_err_duree_negatif    = -1405
integer,parameter :: pm_err_sec_interval_jour= -1406
integer,parameter :: pm_err_heure_interval   = -1407
integer,parameter :: pm_err_min_interval     = -1408
integer,parameter :: pm_err_sec_interval_min = -1409
integer,parameter :: pm_err_an_sup2099       = -1412
integer,parameter :: pm_err_jul1950_sup2099  = -1413

!...........................................
! Probleme sur la position et/ou la vitesse [ +/- 1501 , +/- 1599 ]
!...........................................

integer,parameter :: pm_warn_pos_Oz_topo                 = +1504
integer,parameter :: pm_warn_alt_negatif                 = +1506
integer,parameter :: pm_warn_pos_Oz_ref                  = +1507

integer,parameter :: pm_err_pos_nul                      = -1501
integer,parameter :: pm_err_vit_nul                      = -1502
integer,parameter :: pm_err_pos_vit_colineaire           = -1503
integer,parameter :: pm_err_pos_Oz_topo                  = -1504
integer,parameter :: pm_err_pos_orig_topo                = -1505
integer,parameter :: pm_err_alt_sup1000km                = -1507
integer,parameter :: pm_err_orig_topo_centre_terre       = -1508
integer,parameter :: pm_err_pos_Oz_ref                   = -1509
integer,parameter :: pm_err_jac_non_calc_poles           = -1510
integer,parameter :: pm_err_jac_non_calc_alt_neg         = -1511
integer,parameter :: pm_err_meme_planete                 = -1512

!................................................
! Probleme sur la valeur d'une variable physique [ +/- 1601 , +/- 1699 ]
!................................................


!.................................................
! Probleme de codage dans le code de l'utilisateur [ +/- 1801 , +/- 1898 ]
!.................................................

integer,parameter :: pm_warn_para_option            = +1801
integer,parameter :: pm_warn_conv_identite          = +1802

integer,parameter :: pm_err_para_option             = -1801
integer,parameter :: pm_err_ind_nuta                = -1802
integer,parameter :: pm_err_ind_prec                = -1803
integer,parameter :: pm_err_ind_model               = -1804
integer,parameter :: pm_err_ind_trsf                = -1805
integer,parameter :: pm_err_val_code_retour_inconnu = -1806
integer,parameter :: pm_err_numero_routine_inconnu  = -1807
integer,parameter :: pm_err_ind_rep                 = -1808
integer,parameter :: pm_err_planete                 = -1809
integer,parameter :: pm_err_clef_rot                = -1810
integer,parameter :: pm_err_type_anom               = -1811

!.................................................
! Probleme de codage dans le code MSLIB [ - 1899 ]
!.................................................

integer,parameter :: pm_err_valid = -1899

!.................................................................
! Probleme de convergence dans des routines de mecanique spatiale [ +/- 1901 , +/- 1998 ]
!.................................................................

integer,parameter :: pm_err_conv_car_geod      = -1901
integer,parameter :: pm_err_conv_kepler_ellip  = -1902
integer,parameter :: pm_err_conv_kepler_hyperb = -1903
integer,parameter :: pm_err_conv_kepler_gene   = -1904
integer,parameter :: pm_err_conv_brouwer       = -1905
integer,parameter :: pm_err_conv_eck_hech      = -1906
integer,parameter :: pm_err_conv_lyddane       = -1907


!.................................................................
! Probleme ayant une cause non identifiee a ce jour dans une routine de mecanique spatiale [- 1999]
!.................................................................

integer,parameter :: pm_err_cni = -1999


!............................................................
! Probleme mathematique [ +/- 2001 , +/- 2999 ]
!............................................................

integer,parameter :: pm_warn_angle1_ou_3_indef = +2001

integer,parameter :: pm_err_vect_nul           = -2001
integer,parameter :: pm_err_eps_negatif        = -2002
integer,parameter :: pm_err_eps_nul            = -2003
integer,parameter :: pm_err_axe_rot_nul        = -2004
integer,parameter :: pm_err_quat_nul           = -2005
integer,parameter :: pm_err_axe_rot_indef      = -2006
integer,parameter :: pm_err_mat_non_rot        = -2007


!................................................................................................................

character(len=pm_longueur_info_utilisateur),private :: info_utilisateur = &
                  '@(#) Fichier MSLIB valeur_code_retour_mslib.f90: derniere modification V6.2 >'

!................................................................................................................

character(len=pm_longueur_rcs_id), private :: rcs_id = &
        ' $Id: valeur_code_retour_mslib.f90,v 1.29 2005/02/28 07:52:11 mslibdev Exp $ '

end module valeur_code_retour_mslib


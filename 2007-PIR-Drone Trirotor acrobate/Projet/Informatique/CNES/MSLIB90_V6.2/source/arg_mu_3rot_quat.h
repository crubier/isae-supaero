
! Justification de l'utilisation de la directive include (cf MOD(3) de la MPM f90):
! (en fevrier 98) il n'est pas possible de mettre des modules procedures dans une bibliotheque;
! il faut faire des modules interfaces explicites. Aussi pour eviter de dupliquer du code, et
! etre sur de la coherence des declarations entre la routine et son module interface, 
! nous utilisons un include pour la declaration des arguments d'appel.

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
! Arguments d'appel de la routine mu_3rot_quat

integer, intent(in)                      :: def_3rot   ! definition et ordre d'enchainement des trois rotations
real(pm_reel), intent(in)                :: angle1     ! valeur de l'angle associe a la premiere rotation
real(pm_reel), intent(in)                :: angle2     ! valeur de l'angle associe a la deuxieme rotation
real(pm_reel), intent(in)                :: angle3     ! valeur de l'angle associe a la troisieme rotation
type(tm_quat), intent(out)               :: quat       ! quaternion
type(tm_code_retour), intent(out)                    ::  code_retour


! identificateur rcs propre a cet include
character(len=pm_longueur_rcs_id) :: &
h_rcs_id =' $Id: arg_mu_3rot_quat.h,v 1.1 2003/10/27 11:04:49 msatv2 Exp $ '

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


subroutine mvi_car_kep_ellip (pos_car,vit_car,moment_cinetique,norme_vect_pos,norme_vect_vit,&
                              un_sur_a,e,pos_fois_vit,mu,kep,retour,jacob)

! (C) Copyright CNES - MSLIB - 1998

!************************************************************************
!
! But: passage des positions vitesses en coordonnees CARtesiennes aux parametres KEPleriens osculateurs, et a la 
! ===  jacobienne (optionnel), dans le cas ELLIPtique. 
!
!
! Note d'utilisation: - Routine interne.
! ==================  - L'appelant doit tester que :
!                           1) l'orbite est elliptique non circulaire : e dans ]0,1[
!                           2) la constante de la gravitation est > 0 (strictement)
!                           3) la norme du vecteur position est non nulle
!                           4) 1/a > 0 (strictement)
!
!
! Historique:
! ==========
!   + Version 1.0 (SP 227 ed01 rev00): creation a partir de la routine MVELCO de la MSLIB f77
!   + Version 4.1 (DE globale 482 ed01 rev00): Corrections qualite
!
!************************************************************************


! Modules
! =======
use test_mslib

use int_mslib_mu_angle2

use precision_mslib
use type_mslib
use valeur_code_retour_mslib
use longueur_chaine_mslib


! Declarations
! ============
implicit none

include 'arg_mvi_car_kep_ellip.h'

! Autres declarations
! -------------------

real(pm_reel), dimension(6)  ::  dadx,dedx,danedx,didx
real(pm_reel), dimension(6)  ::  domdx,dgodx,dmdx

real(pm_reel), dimension(6)  ::  drdx,f1,dpos_fois_vit,f2
real(pm_reel), dimension(6)  ::  dpz,dqz,dcr
real(pm_reel), dimension(6)  ::  drx,dry,drz

real(pm_reel) :: a,anome,cof1,cof2,cog,cose,cosi,coso
real(pm_reel) :: coti,cqz,crz
real(pm_reel) :: dusna,dusna2,dusra,ecose,esine,gom,om,pz,qz,r
real(pm_reel) :: r2,rmua,rx,ry,sig,sine,sini,sino,unme2
real(pm_reel) :: unsna,unrmua,unsrac,v,v2,xi,xmoy
real(pm_reel) :: rec6ua,rec3sr,unsurr,unsmu,unsini
real(pm_reel) :: cosese,sinese,cof0,cosesr,sinesr,css,sss

type(tm_code_retour)  :: code_retour


intrinsic sqrt, present

character(len=pm_longueur_info_utilisateur) :: info_utilisateur = &
     '@(#) Fichier MSLIB mvi_car_kep_ellip.f90: derniere modification V4.1 >'

! Ne pas toucher a la ligne suivante
character(len=pm_longueur_rcs_id) :: rcs_id =' $Id: mvi_car_kep_ellip.f90,v 1.9 2003/10/14 12:55:14 mslibdev Exp $ '

!************************************************************************

! initialisation de la valeur du code retour
! ..........................................
retour = pm_OK

! calculs des variables intermediaires
! -----------------------------------

unsmu = 1._pm_reel/mu

r  = norme_vect_pos
r2 = r*r

unsurr = 1._pm_reel/r
v  = norme_vect_vit
v2 = v*v

a=1._pm_reel/un_sur_a       ! calcul du demi-grand axe

rmua=sqrt(mu*a)
unrmua = 1._pm_reel/rmua

ecose=r*v2*unsmu-1._pm_reel
esine=pos_fois_vit*unrmua

call mu_angle2(ecose,esine,anome,code_retour)  !calcul de l'anomalie excentrique

if (code_retour%valeur == pm_err_vect_nul) then
   retour = pm_err_cni
   go to 6000
end if

cose=ecose/e
sine=esine/e

xmoy=anome-esine ! calcul de l'anomalie moyenne



! calcul de l'inclinaison
! -----------------------

!    calculs intermediaires
unsna=sqrt(a*unsmu)
unme2=1._pm_reel-e*e
unsrac=1._pm_reel/sqrt(unme2)
rec6ua = vit_car(3)*unsna
rec3sr = pos_car(3)*unsurr

pz=cose*rec3sr-sine*rec6ua      !  sin(inclinaison)*sin(petit omega)
cqz=sine*rec3sr+(cose-e)*rec6ua
qz=unsrac*cqz                   !  sin(inclinaison)*cos(petit omega)
crz=unrmua*unsrac

cosi=crz*moment_cinetique(3)    !  cos(inclinaison)
sini=sqrt(pz*pz+qz*qz)          !  sin(inclinaison)

if (sini <  pm_eps_equa) then   ! orbite equatoriale
   retour = pm_err_i_equa
   go to 6000
end if

unsini = 1._pm_reel/sini
coti=cosi*unsini

call mu_angle2(cosi, sini, xi, code_retour)!    calcul de l'inclinaison par appel a muangl
                                           !    (resultat dans [0,pi] car sin(inclinaison) > 0)
if (code_retour%valeur == pm_err_vect_nul) then
   retour = pm_err_cni
   go to 6000
end if

sino=pz*unsini
coso=qz*unsini
call mu_angle2(coso,sino,om,code_retour)   ! calcul de l'argument du perigee
if (code_retour%valeur == pm_err_vect_nul) then
   retour = pm_err_cni
   go to 6000
end if

rx=crz*moment_cinetique(1)
ry=crz*moment_cinetique(2)

sig=rx*unsini
cog=-ry*unsini
call mu_angle2(cog,sig,gom,code_retour)  ! calcul de l'ascension droite du noeud ascendant
if (code_retour%valeur == pm_err_vect_nul) then
   retour = pm_err_cni
   go to 6000
end if

! affectation des parametres osculateurs
kep%a = a
kep%e = e
kep%i = xi
kep%pom = om
kep%gom = gom
kep%M = xmoy


if (present(jacob)) then   ! calcul du jacobien de la transformation

   drdx  (1:3) = pos_car(:)*unsurr
   drdx  (4:6) = 0._pm_reel


   cof0 = 2._pm_reel*a*a
   cof1 = cof0/(r2*r)
   cof2 = cof0*unsmu

   dadx(1:3)=cof1*pos_car(:)   !     derivees du demi-grand axe a
   dadx(4:6)=cof2*vit_car(:)   !

   cof1=v2*unsmu*unsurr
   cof2=2._pm_reel*r*unsmu

   f1(1:3)=cof1*pos_car(:)
   f1(4:6)=cof2*vit_car(:)

   dpos_fois_vit(1:3)=vit_car(:)
   dpos_fois_vit(4:6)=pos_car(:)

   cof0 = 0.5_pm_reel*pos_fois_vit*un_sur_a

   f2(:)=(dpos_fois_vit(:)-cof0*dadx(:))*unrmua



   cosese = cose/e
   sinese = sine/e
   dedx(:) = cose*f1(:) + sine*f2(:)      ! derivees de l'excentricite 
   danedx(:)= cosese*f2(:) - sinese*f1(: )! derivees de l'anomalie excentrique

   dusna=0.5_pm_reel*unrmua
   dusra=e*unsrac/unme2
   dusna2=-dusna*un_sur_a

   cosesr = cose*unsurr
   sinesr = sine*unsurr

   dpz(:)=danedx(:)*(-sine*rec3sr-cose*rec6ua)+drdx(:)*(-cosesr*rec3sr)+dadx(:)*(-sine*dusna*vit_car(3))
   dqz(:)=dusra*dedx(:)*cqz+unsrac*(danedx(:)*(cose*rec3sr-sine*rec6ua)+drdx(:)*(-sinesr*rec3sr) &
          +dadx(:)*(cose-e)*dusna*vit_car(3)+dedx(:)*(-rec6ua))
   dcr(:)=dusna2*dadx(:)*unsrac+unrmua*dusra*dedx(:)
   drz(:)=dcr(:)*moment_cinetique(3)


   dpz(3)=dpz(3)+cosesr
   dpz(6)=dpz(6)-sine*unsna
   dqz(3)=dqz(3)+unsrac*sinesr
   dqz(6)=dqz(6)+unsrac*(cose-e)*unsna
   drz(1)=drz(1)+vit_car(2)*crz
   drz(2)=drz(2)-vit_car(1)*crz
   drz(4)=drz(4)-pos_car(2)*crz
   drz(5)=drz(5)+pos_car(1)*crz

   didx(:)=coti*(pz*dpz(:)+qz*dqz(:))-sini*drz(:)      !     derivees de l'inclinaison

   css = coso*unsini
   sss = sino*unsini
   domdx(:)= css*dpz(:)-sss*dqz(:)   !     derivees de l'argument du perigee

   drx(:)=dcr(:)*moment_cinetique(1)
   dry(:)=dcr(:)*moment_cinetique(2)

   drx(2)=drx(2)+vit_car(3)*crz
   dry(3)=dry(3)+vit_car(1)*crz
   drx(3)=drx(3)-vit_car(2)*crz
   dry(1)=dry(1)-vit_car(3)*crz
   drx(5)=drx(5)-pos_car(3)*crz
   dry(6)=dry(6)-pos_car(1)*crz
   drx(6)=drx(6)+pos_car(2)*crz
   dry(4)=dry(4)+pos_car(3)*crz

   css = cog*unsini
   sss = sig*unsini
   dgodx(:)= css*drx(:)+sss*dry(:)   !     derivees de l'ascension droite

   cof0 = 1._pm_reel - ecose
   dmdx(:)=danedx(:)*cof0 -sine*dedx(:)   !     derivees de l'anomalie moyenne

   ! affectation de la jacobienne de la transformation
   ! -------------------------------------------------

   jacob(1,:)=dadx(:)
   jacob(2,:)=dedx(:)
   jacob(3,:)=didx(:)
   jacob(4,:)=domdx(:)
   jacob(5,:)=dgodx(:)
   jacob(6,:)=dmdx(:)

end if

6000 continue

end subroutine mvi_car_kep_ellip

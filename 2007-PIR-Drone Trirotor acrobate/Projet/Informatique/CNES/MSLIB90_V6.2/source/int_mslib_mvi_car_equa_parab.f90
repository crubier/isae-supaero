module int_mslib_mvi_car_equa_parab

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine mvi_car_equa_parab( pos_car, vit_car, rrxv, norme_vect_pos, norme_moment_cinetique, excentricite ,&
                                    parametre, rscal, mu, equa, retour, jacob )

       use type_mslib
       use precision_mslib

       include 'arg_mvi_car_equa_parab.h'

     end subroutine mvi_car_equa_parab
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_mvi_car_equa_parab.f90,v 1.2 2003/05/06 15:50:44 mslibatv Exp $ '

end module int_mslib_mvi_car_equa_parab

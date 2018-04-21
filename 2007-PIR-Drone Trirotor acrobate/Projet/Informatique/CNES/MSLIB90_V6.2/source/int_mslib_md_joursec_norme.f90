module int_mslib_md_joursec_norme

  use longueur_chaine_mslib     ! definition des longueurs de chaines de caracteres

  implicit none

  public

  interface
     subroutine md_joursec_norme(joursec, joursec_norme, code_retour )

       use type_mslib
       use precision_mslib

       include 'arg_md_joursec_norme.h'

     end subroutine md_joursec_norme
  end interface

  character(len=pm_longueur_rcs_id), private :: &
  rcs_id =' $Id: int_mslib_md_joursec_norme.f90,v 1.2 2003/05/06 15:50:31 mslibatv Exp $ '

end module int_mslib_md_joursec_norme

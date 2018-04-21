#ifndef __cantor_CombRotVD1VD2_h
#define __cantor_CombRotVD1VD2_h

static char rcsid_CombRotVD1VD2_h [] = "$Id: CombRotVD1VD2.h,v 1.2 1997/03/26 06:38:08 luc Exp $";

// ce paquetage r�alise les combinaisons d'op�randes
// entre les types rotations suivants:
//            class ValeurDerivee1
//            class ValeurDerivee2
//

// il ne doit �tre utilis� que par le fichier "cantor/DeclVD1VD2.h",
// dont il n'est s�par� que pour des raisons de clart�

// combinaisons
inline int    operator == (const RotVD2& r, const RotVD1& q)
{ return RotVD2VD1 (r) == q; }


inline int    operator == (const RotVD1& r, const RotVD2& q)
{ return r == RotVD2VD1 (q); }

#endif

/* $IdPath$
 * Floating point number functions header file.
 *
 *  Copyright (C) 2001  Peter Johnson
 *
 *  This file is part of YASM.
 *
 *  YASM is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  YASM is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef YASM_FLOATNUM_H
#define YASM_FLOATNUM_H

typedef struct floatnum_s {
    unsigned char extval[10];	    /* float stored in extended precision */
} floatnum;

floatnum *floatnum_new(char *str);
unsigned long floatnum_get_int(floatnum *flt);
unsigned char *floatnum_get_single(unsigned char *ptr, floatnum *flt);
unsigned char *floatnum_get_double(unsigned char *ptr, floatnum *flt);
unsigned char *floatnum_get_extended(unsigned char *ptr, floatnum *flt);

void floatnum_print(floatnum *flt);

#endif

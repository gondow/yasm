/* $IdPath$
 * Symbol table handling header file
 *
 *  Copyright (C) 2001  Michael Urman, Peter Johnson
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
#ifndef YASM_SYMREC_H
#define YASM_SYMREC_H

/* DEFINED is set with EXTERN and COMMON below */
typedef enum {
    SYM_NOSTATUS = 0,
    SYM_USED = 1 << 0,		/* for using variables before definition */
    SYM_DEFINED = 1 << 1,	/* once it's been defined in the file */
    SYM_VALUED = 1 << 2		/* once its value has been determined */
} SymStatus;

/* EXTERN and COMMON are mutually exclusive */
typedef enum {
    SYM_LOCAL = 0,		/* default, local only */
    SYM_GLOBAL = 1 << 0,	/* if it's declared GLOBAL */
    SYM_COMMON = 1 << 1,	/* if it's declared COMMON */
    SYM_EXTERN = 1 << 2		/* if it's declared EXTERN */
} SymVisibility;

typedef enum {
    SYM_UNKNOWN,		/* for unknown type (COMMON/EXTERN) */
    SYM_CONSTANT_INT,		/* for EQU defined symbols (integers) */
    SYM_CONSTANT_FLOAT,		/*  (floating point) */
    SYM_LABEL			/* for labels */
} SymType;

typedef struct symrec_s {
    char *name;
    SymType type;
    SymStatus status;
    SymVisibility visibility;
    char *filename;		/* file and line */
    unsigned long line;		/*  symbol was first declared or used on */
    union {
	unsigned long int_val;	/* integer constant */
	struct floatnum_s *flt;	/* floating point constant */
	struct label_s {	/* bytecode immediately preceding a label */
	    struct section_s *sect;
	    struct bytecode_s *bc;
	} label;
    } value;
} symrec;

symrec *symrec_use(const char *name);
symrec *symrec_define_constant_int(const char *name, unsigned long int_val);
symrec *symrec_define_constant_float(const char *name, struct floatnum_s *flt);
symrec *symrec_define_label(const char *name, struct section_s *sect,
			    struct bytecode_s *precbc);
symrec *symrec_declare(const char *name, SymVisibility vis);

/* Get the numeric 32-bit value of a symbol if possible.
 * Return value is IF POSSIBLE, not the value.
 * If resolve_label is true, tries to get offset of labels, otherwise it
 * returns not possible.
 */
int symrec_get_int_value(const symrec *sym, unsigned long *ret_val,
			 int resolve_label);

void symrec_foreach(int (*func) (const char *name, symrec *rec));

#endif

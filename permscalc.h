/*
 * Copyright (c) 2022 2bllw8
 * SPDX-License-Identifier: GPL-3.0-only
 */

#ifndef PERMSCALC_H
#define PERMSCALC_H

typedef enum {
	PERMISSION_TYPE_UNKNOWN,
	PERMISSION_TYPE_NUMERIC,
	PERMISSION_TYPE_SYMBOLIC,
	PERMISSION_TYPE_SYMBOLIC_WITH_D,
	PERMISSION_TYPE_SYMBOLIC_WITH_D_AND_EXTRA,
} permission_t;

permission_t identify_type(const char *str);
char *symbolic_to_numeric(const char *str);
char *symbolic_with_d_to_numeric(const char *str);
char *symbolic_with_d_and_extra_to_numeric(const char *str);
char *numeric_to_symbolic(const char *numeric);
#endif

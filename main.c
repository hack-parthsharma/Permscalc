/*
 * Copyright (c) 2022 2bllw8
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "permscalc.h"

#include <stddef.h>
#include <stdio.h>

int parse(const char *input)
{
	char *output;
	switch (identify_type(input)) {
	case PERMISSION_TYPE_NUMERIC:
		output = numeric_to_symbolic(input);
		break;
	case PERMISSION_TYPE_SYMBOLIC:
		output = symbolic_to_numeric(input);
		break;
	case PERMISSION_TYPE_SYMBOLIC_WITH_D:
		output = symbolic_with_d_to_numeric(input);
		break;
	case PERMISSION_TYPE_SYMBOLIC_WITH_D_AND_EXTRA:
		output = symbolic_with_d_and_extra_to_numeric(input);
		break;
	case PERMISSION_TYPE_UNKNOWN:
	default:
		fprintf(stderr, "%s: invalid permissions value\n", input);
		return 0;
	}
	fprintf(stdout, "%s\n", output);
	return 1;
}

int main(int argc, char **argv)
{
	if (argc == 1) {
		char *line = 0;
		size_t len = 0, line_len = 0;
		while ((line_len = getline(&line, &len, stdin)) != -1) {
			line[line_len - 1] = 0;
			if (!parse((const char*) line)) {
				return 1;
			}
		}
	} else {
		size_t i = 1;
		while (i < argc) {
			if (!parse((const char *) argv[i++])) {
				return 1;
			}
		}
	}

	return 0;
}

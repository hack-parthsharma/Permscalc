/*
 * Copyright (c) 2022 2bllw8
 * SPDX-License-Identifier: GPL-3.0-only
 */

#include "permscalc.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	// Parser

	assert(PERMISSION_TYPE_NUMERIC == identify_type("777"));
	assert(PERMISSION_TYPE_NUMERIC == identify_type("000"));
	assert(PERMISSION_TYPE_NUMERIC == identify_type("444"));
	assert(PERMISSION_TYPE_NUMERIC == identify_type("222"));
	assert(PERMISSION_TYPE_NUMERIC == identify_type("111"));
	assert(PERMISSION_TYPE_NUMERIC == identify_type("653"));
	assert(PERMISSION_TYPE_SYMBOLIC == identify_type("rwxrwxrwx"));
	assert(PERMISSION_TYPE_SYMBOLIC == identify_type("---------"));
	assert(PERMISSION_TYPE_SYMBOLIC == identify_type("r--r--r--"));
	assert(PERMISSION_TYPE_SYMBOLIC == identify_type("-w--w--w-"));
	assert(PERMISSION_TYPE_SYMBOLIC == identify_type("--x--x--x"));
	assert(PERMISSION_TYPE_SYMBOLIC == identify_type("rw-r-x-wx"));
	assert(PERMISSION_TYPE_SYMBOLIC_WITH_D == identify_type("-rw-r--r--"));
	assert(PERMISSION_TYPE_SYMBOLIC_WITH_D == identify_type("-rw-r--r--"));
	assert(PERMISSION_TYPE_SYMBOLIC_WITH_D == identify_type("drw-r--r--"));
	assert(PERMISSION_TYPE_SYMBOLIC_WITH_D_AND_EXTRA ==
	       identify_type("-rw-r--r--@"));
	assert(PERMISSION_TYPE_SYMBOLIC_WITH_D_AND_EXTRA ==
	       identify_type("drwxrw---x@"));
	assert(PERMISSION_TYPE_SYMBOLIC_WITH_D_AND_EXTRA ==
	       identify_type("---x-w--wx+"));

	assert(PERMISSION_TYPE_UNKNOWN == identify_type("rwxwxrwx"));
	assert(PERMISSION_TYPE_UNKNOWN == identify_type("rxwrwxrwx"));
	assert(PERMISSION_TYPE_UNKNOWN == identify_type("rw-r-x-wa"));
	assert(PERMISSION_TYPE_UNKNOWN == identify_type("888"));
	assert(PERMISSION_TYPE_UNKNOWN == identify_type("0123"));
	assert(PERMISSION_TYPE_UNKNOWN == identify_type(""));

	// Numeric to symbolic

	assert(strcmp("rwxrwxrwx", numeric_to_symbolic("777")) == 0);
	assert(strcmp("---------", numeric_to_symbolic("000")) == 0);
	assert(strcmp("r--r--r--", numeric_to_symbolic("444")) == 0);
	assert(strcmp("-w--w--w-", numeric_to_symbolic("222")) == 0);
	assert(strcmp("--x--x--x", numeric_to_symbolic("111")) == 0);
	assert(strcmp("rw-r-x-wx", numeric_to_symbolic("653")) == 0);

	// Symbolic to numeric

	assert(strcmp("777", symbolic_to_numeric("rwxrwxrwx")) == 0);
	assert(strcmp("000", symbolic_to_numeric("---------")) == 0);
	assert(strcmp("444", symbolic_to_numeric("r--r--r--")) == 0);
	assert(strcmp("222", symbolic_to_numeric("-w--w--w-")) == 0);
	assert(strcmp("111", symbolic_to_numeric("--x--x--x")) == 0);
	assert(strcmp("653", symbolic_to_numeric("rw-r-x-wx")) == 0);

	assert(strcmp("644", symbolic_with_d_to_numeric("-rw-r--r--")) == 0);
	assert(strcmp("644", symbolic_with_d_to_numeric("drw-r--r--")) == 0);

	assert(strcmp("644", symbolic_with_d_and_extra_to_numeric(
				     "-rw-r--r--@")) == 0);
	assert(strcmp("761", symbolic_with_d_and_extra_to_numeric(
				     "drwxrw---x@")) == 0);
	assert(strcmp("123", symbolic_with_d_and_extra_to_numeric(
				     "---x-w--wx+")) == 0);

	// Double conversion should preserve the value (minus the "extras")

	assert(strcmp("rw-r-x-wx", numeric_to_symbolic(symbolic_to_numeric(
					   "rw-r-x-wx"))) == 0);
	assert(strcmp("---------", numeric_to_symbolic(symbolic_to_numeric(
					   "---------"))) == 0);
	assert(strcmp("r--r--r--", numeric_to_symbolic(symbolic_to_numeric(
					   "r--r--r--"))) == 0);
	assert(strcmp("-w--w--w-", numeric_to_symbolic(symbolic_to_numeric(
					   "-w--w--w-"))) == 0);
	assert(strcmp("--x--x--x", numeric_to_symbolic(symbolic_to_numeric(
					   "--x--x--x"))) == 0);
	assert(strcmp("rw-r-x-wx", numeric_to_symbolic(symbolic_to_numeric(
					   "rw-r-x-wx"))) == 0);

	assert(strcmp("777", symbolic_to_numeric(numeric_to_symbolic("777"))) ==
	       0);
	assert(strcmp("000", symbolic_to_numeric(numeric_to_symbolic("000"))) ==
	       0);
	assert(strcmp("444", symbolic_to_numeric(numeric_to_symbolic("444"))) ==
	       0);
	assert(strcmp("222", symbolic_to_numeric(numeric_to_symbolic("222"))) ==
	       0);
	assert(strcmp("111", symbolic_to_numeric(numeric_to_symbolic("111"))) ==
	       0);
	assert(strcmp("653", symbolic_to_numeric(numeric_to_symbolic("653"))) ==
	       0);
}

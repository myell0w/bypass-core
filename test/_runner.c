#include <stdlib.h>
#include <getopt.h>
#include "sut_test.h"
#include ""

int
main(int argc, char *argv[])
{
	sut_suite_t *suite;
	int ch;
	const char *filter = NULL;

	suite = sut_suite_new("");


	// Interpreting arguments

	struct option longopts[] = {
		{ "nofork", no_argument,       NULL, 'n' },
		{ "filter", required_argument, NULL, 'f' },
		{ NULL,     0,                 NULL,  0  }
	};

	while ((ch = getopt_long(argc, (char *const *) argv, "nf:", longopts, NULL)) != -1) {
		switch (ch) {
			case 'n':
				sut_suite_set_fork(suite, false);
				break;
			case 'f':
				filter = optarg;
				break;
			default:
				break;
		}
	}

	argc -= optind;
	argv += optind;

	// Preparing and running tests

	sut_suite_run(suite, filter);
	sut_suite_free(suite);

	return 0;
}

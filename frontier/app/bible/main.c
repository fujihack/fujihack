#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <sys.h>
#include <bmp.h>

#include "biblec.h"

int main() {
    struct BiblecTranslation bt;

    if (biblec_parse(&bt, "sd/web.i")) {
        printf("Error loading WEB translation\n");
    }

	struct BiblecReader reader;
	int tryReader = biblec_new(
		&reader,
		&bt,
		"Heb",
		4,
		12,
		13
	);

    while (biblec_next(&reader)) {
        puts(reader.result);
    }

    return 0;
}

#include <stdio.h>
#include "translation_fork.h"

int main() {
	char *out, *out2, *out3, *out4;

	out = translation_fork("Hello i am cool", 15, 1);
	out2 = translation_fork("[Josh] is very cool.  Don't you think?", 38, 1);
	
	g_print("%s\n", out);
	g_print("%s\n", out2);

	free(out);
	free(out2);
	
	return 0;
}


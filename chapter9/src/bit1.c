#include <stdio.h>

int main() {
	char a = 0;

	a = 0;
	fprintf(stdout, "%x\n", a);
	a = -1;
	fprintf(stdout, "%x\n\n", a);

	/* ビット反転 */
	a = ~0;
	fprintf(stdout, "%x\n", a);
	a = ~1;
	fprintf(stdout, "%x\n", a);
	a = ~-1;
	fprintf(stdout, "%x\n", a);

	return 0;
}
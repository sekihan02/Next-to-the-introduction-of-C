/* print2 */
/* Split, fileを出力する */

#include <stdio.h>
#include "func.h"

/* funcfile */
/* 引数　：なし */
/* 戻り値：なし */
void funcfile() {
	fprintf(stdout, "Split, file.\n");
}

int main()
{
	funchello();
	funcfile();
	return 0;
}

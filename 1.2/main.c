#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "header.h"

int main(int argc, char * argv[])
{
	int ViisViimast, *pViisViimast = &ViisViimast, konstant = 7, *pkonstant = &konstant;
	if (sisestus(argc, argv, pViisViimast, pkonstant))
	{
		return 1;
	}
	printf("Viieks viimaseks numbriks loeti: %d\n", ViisViimast);
	printf("Teguriks loeti: %d\n", konstant);
	FILE * F;
	F = fopen("t6ev22rtustabel.txt", "w");
	tootlus(ViisViimast, konstant, F);
	fclose(F);
	FILE * MDNK, * MKNK;
	MDNK = fopen("mdnk.txt", "w");
	MKNK = fopen("mknk.txt", "w");
	if (valjastus())
		return 1;
	if (mccluskey(MDNK, MKNK))
	{
		return 1;
	}
	fclose(MDNK);
	fclose(MKNK);
	return 0;
}

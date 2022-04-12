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
	int tulemus = mccluskey(MDNK, MKNK);
	if (tulemus == 2)
	{
		return 1;	// MDNK LOOMINE EBA6NNESTUS
	}
	if (tulemus == 3)
	{
		return 2;	// MKNK LOOMINE EBA6NNESTUS
	}
	fclose(MDNK);
	fclose(MKNK);
	return 0;
}

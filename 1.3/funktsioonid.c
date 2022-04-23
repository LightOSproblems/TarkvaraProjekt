int s6nearvuks(char string[], int pikkus, int tudengikood)
{
	int i = 0, j = 0, kaal = 1, error = 0, arv = 0;
	i = pikkus-1;
	//printf("{");
		while (i > -1)
		{
			//printf("%c", string[i]);
			if (!isdigit(string[i]))
			{
				error = 1;
			}
			j++;
			if (j <= 5)
			{
				arv += (string[i] - 48)*kaal;
			}
			kaal *= 10;
			i--;
		}
		//printf("}");
		if (error == 1 || (tudengikood == 1 && pikkus < 5))
		{
			return 1;
		}
	return arv;
}

int sisestus(int len, char argv[], int *pViisViimast, int * pkonstant)
{
	char teststring[50];
	*pViisViimast = s6nearvuks(argv, len, 1);
	if (s6nearvuks(argv, len, 1) == 1)
	{
		printf("Sobimatu parameeter: '");
		for (int i = 0; i < len; i++)
		{
			printf("%c", argv[i]);
		}
		printf("'\n");
		return 1;
	}
	return 0;
}

void tootlus(int ViisViimast, int konstant, FILE *F)
{
	int sisend = ViisViimast;
	int m22ramatuspiirkond[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int yhtedepiirkond[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	printf("Vahetulemused:\n");
	while (sisend < 0x1000000)  // 0x1000000 ehk esimene 7-kohaline 16ndarv
	{
		sisend *= konstant;
		printf("%X\n", sisend);
	}
	printf("Esimese sammu resultaat: %X\n", sisend);
	unsigned long long int pikksisend = sisend;
	int hex[7];
	int hex2[9];
	int i, j22k;
	for (i = 6; i > -1; i--)
	{
		j22k = sisend%16;
		hex[i] = j22k;
		m22ramatuspiirkond[hex[i]] = 1;
		sisend /= 16;
	}
	printf("\nVahetulemused:\n");
	while(pikksisend < 0x100000000) // 0x100000000 ehk esimene 9-kohaline 16ndarv
	{
		pikksisend *= konstant;
		printf("%llX\n", pikksisend);
	}
	printf("Teise sammu resultaat: %llX\n\n", pikksisend);
	i = 0;
	for (i = 8; i > -1; i--)
	{
		j22k = pikksisend%16;
		hex2[i] = j22k;
		if (m22ramatuspiirkond[hex2[i]] == 0)
		{
			yhtedepiirkond[hex2[i]] = 1;	// vaid juhul kui see juba m22ramatuspiirkonda ei kuulu
		}
		//printf("j22k on: %d\n", hex2[i]);
		pikksisend /= 16;
	}
	i = 0;
	for (i = 0; i < 16; i++)
	{
		if (yhtedepiirkond[i])
		{
			fprintf(F, "%d\t 1\n", i);
		}
		else if (m22ramatuspiirkond[i])
		{
			fprintf(F, "%d\t -\n", i);
		}
		else
		{
			fprintf(F, "%d\t 0\n", i);
		}
	}
	fprintf(F, "\n");
	printf("T6ev22rtustabel edukalt tekstifaili salvestatud!\n");
	rewind(F);
}

int valjastus()
{
	FILE *F;
	F = fopen("t6ev22rtustabel.txt", "r");
	if (F == NULL)	//kui faili ei leita siis v2ljastatakse veateade ja funktsioon l6petab too
	{
		printf("Viga! Andmefaili ei leitud!");
		return 1;
	}
	int i = 0, vektorid[16];
	char v22rtused[16];
	printf("OSALISELT M22RATUD 4-MUUTUJA FUNKTSIOONI T6EV22RTUSTABEL:\n");
	for (i = 0; i < 16; i++)
	{
		fscanf(F, "%d %c", &vektorid[i], &v22rtused[i]);
		printf("Vektor 10ndkujul: %d\t Funktsiooni v22rtus: %c\n", vektorid[i], v22rtused[i]);
	}
	fclose(F);
	/*
	printf("\nFunktsioon esitatud Karnaugh' kaardina:\n\n\t");
	printf("    |\tx3x4\n\t    |\t00\t01\t11\t10\n\t---------------------------------------");
	printf("\n\t    |\t    |\t    |\t    |\t    |\n");
	printf("  x1x2\t00  |");
	*/
	i = 0;
	char v22rtus;
	for (i = 0; i < 8; i++)
	{
		if (i == 2 || i == 6)
		{
			v22rtus = v22rtused[i + 1];
		}
		else if (i == 3 || i == 7)
		{
			v22rtus = v22rtused[i - 1];
		}
		else
		{
			v22rtus = v22rtused[i];
		}
		//printf("\t%c   |", v22rtus);
		if (i == 3)
		{
		//	printf("\n\t    |\t    |\t    |\t    |\t    |\n");
		//	printf("\t01  |");
		}
	}
	//printf("\n\t    |\t    |\t    |\t    |\t    |\n");
	//printf("\t11  |");
	i = 12;
	for (i = 12; i < 16; i++)
	{
		if (i == 14)
		{
			v22rtus = v22rtused[i + 1];
		}
		else if (i == 15)
		{
			v22rtus = v22rtused[i - 1];
		}
		else
		{
			v22rtus = v22rtused[i];
		}
		//printf("\t%c   |", v22rtus);
	}
	i = 8;
	//printf("\n\t    |\t    |\t    |\t    |\t    |\n");
	//printf("\t10  |");
	for (i = 8; i < 12; i++)
	{
		if (i == 10)
		{
			v22rtus = v22rtused[i + 1];
		}
		else if (i == 11)
		{
			v22rtus = v22rtused[i - 1];
		}
		else
		{
			v22rtus = v22rtused[i];
		}
		//printf("\t%c   |", v22rtus);
	}
	//printf("\n\t    |\t    |\t    |\t    |\t    |\n");
	//printf("\t---------------------------------------\n");
	return 0;
}

int kleepija(char a[], char b[], char kleebe[])	// kahendvektorite kokkukleepimiseks; tagastab 1 kui vektorid ei kleepu ja 2 kui vektorid on identsed
{
	int muutusi = 0;
	for (int i = 0; i < 4; i++)
	{
		if (a[i] == b[i])
		{
			kleebe[i] = a[i];
		}
		else if (a[i] != b[i])
		{
			muutusi++;
			kleebe[i] = '-';
		}
	}
	if (muutusi > 1)
		return 1;
	else if (muutusi == 0)
		return 2;
	return 0;
}

int elementmassiivis(int a, int b[], int pikkus)	// kui element LEIDUB massiivis, tagastab funktsioon v22rtuse 0
{
	int olemas = 0;
	for (int i = 0; i < pikkus; i++)
	{
		if (a == b[i])
		{
			olemas = 1;
			return 0;
		}
	}
	return 1;
}

int elementpaariteises(int a, int b[][2], int pikkus)	// kui element LEIDUB massiivis, tagastab funktsioon v22rtuse 0
{
	int olemas = 0;
	for (int i = 0; i < pikkus; i++)
	{
		if (a == b[i][1])
		{
			olemas = 1;
			return 0;
		}
	}
	return 1;
}

int paarmassiiviteises(int a, int b, int c[][4], int pikkus)	// kui paar LEIDUB massiivis, tagastab funktsioon v22rtuse 0
{
	int olemas = 0;
	for (int i = 0; i < pikkus; i++)
	{
		if (a == c[i][2] && b == c[i][3])
		{
			olemas = 1;
			return 0;
		}
	}
	return 1;
}

int nelikmassiiviteises(int a, int b, int c, int d, int e[][8], int pikkus)	// kui paar LEIDUB massiivis, tagastab funktsioon v22rtuse 0
{
	int olemas = 0;
	for (int i = 0; i < pikkus; i++)
	{
		if (a == e[i][4] && b == e[i][5] && c == e[i][6] && d == e[i][7])
		{
			olemas = 1;
			return 0;
		}
	}
	return 1;
}

int mccluskey(FILE * MDNK, FILE * MKNK)
{
	int indeks0[] = {0}, indeks1[] = {1, 2, 4, 8}, indeks2[] = {3, 5, 6, 9, 10, 12}, indeks3[] = {7, 11, 13, 14}, indeks4[] = {15};
	int yhtedepiirkond[16], nullidepiirkond[16], rangeyhtedepiirkond[16], rangenullidepiirkond[16];
	char tegeliktabel[16];
	char vektorids6nedena[][4] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
	FILE *TABEL;
	TABEL = fopen("t6ev22rtustabel.txt", "r");
	if (TABEL == NULL)	//kui faili ei leita siis v2ljastatakse veateade ja funktsioon l6petab too
	{
		printf("Viga! Andmefaili ei leitud!");
		return 1;
	}
	int vektor, yhtsuurus = 0, nulsuurus = 0, rangeyhtsuurus = 0, rangenulsuurus = 0;
	char kleebe[4], kleebe2[4], kleebe3[4], kleebe4[4], kleebe5[4], kleebe6[4], kleebe7[4], element;
	for (int i = 0; i < 16; i++)
	{
		fscanf(TABEL, "%d %c", &vektor, &element);
		tegeliktabel[i] = element;
		if (element == '1')
		{
			rangeyhtedepiirkond[rangeyhtsuurus] = vektor;
			rangeyhtsuurus++;
		}
		if (element == '0')
		{
			rangenullidepiirkond[rangenulsuurus] = vektor;
			rangenulsuurus++;
		}
		if (element == '1' || element == '-')
		{
			yhtedepiirkond[yhtsuurus] = vektor;
			yhtsuurus++;
		}
		if (element == '0' || element == '-')
		{
			nullidepiirkond[nulsuurus] = vektor;
			nulsuurus++;
		}
	}
	int punkte = 0;
	for (int i = 0; i < 16; i++)	// kontrollime ega me ei saanud mingi ime l2bi konstant-1 funktsiooni
	{
		if (!elementmassiivis(i, yhtedepiirkond, yhtsuurus))
		{
			punkte++;
		}
	}
	//printf("Vektoreid laiendatud 1-piirkonnas: %d\n", punkte);
	if (punkte == 16)
	{
		printf("Konstant-1 funktsioonil MDNK ega MKNK ei ole!");
		return 0;
	}
	int paarid1[64][2], paarid2[64][4], paarid3[64][8];	// kleebitud vektorite paarid kymnendesituses
	int kleepumatudesimesed[16], kleepumatudteised[16][2], kleepumatudkolmandad[16][4];	// kleepumatud vektorid kymnendesituses - nad on ise lihtimplikandid
	char kleepumatuds6nedena1[64][4], kleepumatuds6nedena2[64][4], kleepumatuds6nedena3[64][4];
	int kleepumatuidesimesi = 0, kleepumatuidteisi = 0, kleepumatuidkolmandaid = 0;	// kleepumatute vektorite hulk igas etapis indeksidena kasutamiseks
	int esimesipaare = 0, teisipaare = 0, kolmandaidpaare = 0;	// kleepimisel saadud paaride arvud
	int kleepumatuesimene = 1, kleepumatuteine = 1, kleepumatukolmas = 1;
	char paarids6nedena1[64][4], paarids6nedena2[64][4], paarids6nedena3[64][4];	// kleebitud vektorid s6nekujul (nt "01-0")
	int rangevektor = 0;
	char implikandipuhver[64][4], lihtimplikandid[64][4];
	int implikantepuhvris = 0;
	int lihtimplikante = 0;
	int kordumatu = 1;
	int ei = 1, t2is = 0;
	int elemente = 0, katvad[64];
	int rangeidlihtimplikante;
	char rangedlihtimplikandid[64][4];
	int kaetud = 0;
	int katteid = 0;
	int valituid = 0;
	int viimanekatja = 0;
	int korduvimplikant = 0;
	int valitud[256];
	int suurimaidkatteid = 0;
	int suurimvalimata = 0;
	int rangekattuvus = 0;
	int implikandidkattuvusega[256][2];	// esimene element on implikandi indeks, teine element n2itab kui palju vastav lihtimplikant katab
	int katab = 0;
	int puhver[2];
	int d;
	int kordub, rist = 0, kattuvusm22r = 0;
	if (yhtsuurus == 16)
	{
		printf("Konstant-1 funktsioonil puudub MDNK.\n");
		return 2;
	}
	if (nulsuurus == 16)
	{
		printf("Konstant-0 funktsioonil puudub MKNK.\n");
		return 3;
	}
	// ########### MDNK KLEEPIMINE ###########
	if (rangeyhtsuurus > 0) // OSALISELT M22RATUD FUNKTSIOONIL LEIDUB MDNK AINULT SIIS, KUI TA YHTEDEPIIRKOND POLE TYHI HULK
	{
		for (int i = 0; i < 15; i++)	// esimene kleepimine
		{
			for (int j = i + 1; j < 16; j++)
			{
				if (kleepija(vektorids6nedena[i], vektorids6nedena[j], kleebe) == 0 && !elementmassiivis(i, yhtedepiirkond, yhtsuurus) && !elementmassiivis(j, yhtedepiirkond, yhtsuurus))
				{
					paarid1[esimesipaare][0] = i;
					paarid1[esimesipaare][1] = j;
					for (int h = 0; h < 4; h++)
					{
						paarids6nedena1[esimesipaare][h] = kleebe[h];
					}
					esimesipaare++;
				}
			}
		}
		for (int i = 0; i < 16; i++)	// esimeste kleepumatute otsimine
		{
			kleepumatuesimene = 1;
			for (int j = i + 1; j < 16; j++)
			{
				if (kleepija(vektorids6nedena[i], vektorids6nedena[j], kleebe) == 0 && !elementmassiivis(i, yhtedepiirkond, yhtsuurus) && !elementmassiivis(j, yhtedepiirkond, yhtsuurus))
				{
					kleepumatuesimene = 0;	// vektor i on kasv6i kordki kleebitav, seega muudame v22rtuse 0-ks
				}
			}
			if (kleepumatuesimene && !elementmassiivis(i, yhtedepiirkond, yhtsuurus) && elementpaariteises(i, paarid1, esimesipaare))	// kui vektor i ei kleepunud yhegi teisega, siis loeme ta lihtimplikandiks
			{
				kleepumatudesimesed[kleepumatuidesimesi] = i;
				kleepumatuidesimesi++;
			}
		}
		/*
		printf("Esimesed paarid:\n");
		for (int i = 0; i < esimesipaare; i++)
		{
			printf("%d\t-\t%d\t\t\t\t", paarid1[i][0], paarid1[i][1]);
			for (int j = 0; j < 4; j++)
			{
				printf("%c", paarids6nedena1[i][j]);
			}
			printf("\n");
		}

		printf("Esimesed kleepumatud (%d tk.):\n", kleepumatuidesimesi);
		for (int i = 0; i < kleepumatuidesimesi; i++)
		{
			printf("%d\t\t\t\t\t\t%c%c%c%c", kleepumatudesimesed[i], vektorids6nedena[kleepumatudesimesed[i]][0], vektorids6nedena[kleepumatudesimesed[i]][1], vektorids6nedena[kleepumatudesimesed[i]][2], vektorids6nedena[kleepumatudesimesed[i]][3]);
			printf("\n");
		}
		*/
		//printf("%d\n", elementmassiivis(12, paarid1[1], esimesipaare));
		//printf("%d", elementpaariteises(12, paarid1, esimesipaare));
		for (int i = 0; i < esimesipaare - 1; i++)	// teine kleepimine
		{
			for (int j = i + 1; j < esimesipaare; j++)
			{
				if (kleepija(paarids6nedena1[i], paarids6nedena1[j], kleebe) == 0)
				{
					paarid2[teisipaare][0] = paarid1[i][0];
					paarid2[teisipaare][1] = paarid1[i][1];
					paarid2[teisipaare][2] = paarid1[j][0];
					paarid2[teisipaare][3] = paarid1[j][1];
					for (int h = 0; h < 4; h++)
					{
						paarids6nedena2[teisipaare][h] = kleebe[h];
					}
					teisipaare++;
				}
			}
		}
		for (int i = 0; i < esimesipaare; i++)	// teiste kleepumatute otsimine
		{
			kleepumatuteine = 1;
			for (int j = i + 1; j < esimesipaare; j++)
			{
				if (kleepija(paarids6nedena1[i], paarids6nedena1[j], kleebe) == 0)
				{
					kleepumatuteine = 0; // paar i on kasv6i kordki kleebitav, seega muudame v22rtuse 0-ks
				}
			}
			//printf("kontroll: %d\tpaar:%d-%d\n", paarmassiiviteises(paarid1[i][0], paarid1[i][1], paarid2, esimesipaare), paarid1[i][0], paarid1[i][1]);
			if (kleepumatuteine && paarmassiiviteises(paarid1[i][0], paarid1[i][1], paarid2, esimesipaare))	// kui paar i ei kleepunud yhegi teisega, siis loeme ta lihtimplikandiks
			{
				kleepumatudteised[kleepumatuidteisi][0] = paarid1[i][0];
				kleepumatudteised[kleepumatuidteisi][1] = paarid1[i][1];
				kleepija(vektorids6nedena[paarid1[i][0]], vektorids6nedena[paarid1[i][1]], kleebe);
				kleepumatuds6nedena2[kleepumatuidteisi][0] = kleebe[0];
				kleepumatuds6nedena2[kleepumatuidteisi][1] = kleebe[1];
				kleepumatuds6nedena2[kleepumatuidteisi][2] = kleebe[2];
				kleepumatuds6nedena2[kleepumatuidteisi][3] = kleebe[3];
				//printf("kleepumatud teised: %d-%d\n", kleepumatudteised[kleepumatuidteisi][0], kleepumatudteised[kleepumatuidteisi][1]);
				kleepumatuidteisi++;
			}
		}
		/*
		printf("\nTeised paarid:\n");
		for (int i = 0; i < teisipaare; i++)
		{
			printf("%d-%d\t;\t%d-%d\t\t\t\t", paarid2[i][0], paarid2[i][1], paarid2[i][2], paarid2[i][3]);
			for (int j = 0; j < 4; j++)
			{
				printf("%c", paarids6nedena2[i][j]);
			}
			printf("\n");
		}
		printf("Teised kleepumatud (%d tk.):\n", kleepumatuidteisi);
		for (int i = 0; i < kleepumatuidteisi; i++)
		{
			printf("%d-%d\t\t\t\t", kleepumatudteised[i][0], kleepumatudteised[i][1]);
			printf("\n");
		}
		*/
		for (int i = 0; i < teisipaare - 1; i++)	// kolmas kleepimine
		{
			for (int j = i + 1; j < teisipaare; j++)
			{
				//printf("Paar1: %c%c%c%c Paar2: %c%c%c%c\n", paarids6nedena2[i][0], paarids6nedena2[i][1], paarids6nedena2[i][2], paarids6nedena2[i][3], paarids6nedena2[j][0], paarids6nedena2[j][1], paarids6nedena2[j][2], paarids6nedena2[j][3]);
				//printf("%d\n", kleepija(paarids6nedena2[i], paarids6nedena2[j], kleebe));
				if (kleepija(paarids6nedena2[i], paarids6nedena2[j], kleebe) == 0)
				{
					paarid3[kolmandaidpaare][0] = paarid2[i][0];
					paarid3[kolmandaidpaare][1] = paarid2[i][1];
					paarid3[kolmandaidpaare][2] = paarid2[i][2];
					paarid3[kolmandaidpaare][3] = paarid2[i][3];
					paarid3[kolmandaidpaare][4] = paarid2[j][0];
					paarid3[kolmandaidpaare][5] = paarid2[j][1];
					paarid3[kolmandaidpaare][6] = paarid2[j][2];
					paarid3[kolmandaidpaare][7] = paarid2[j][3];
					/*
					kleepija(vektorids6nedena[paarid2[i][0]], vektorids6nedena[paarid2[i][1]], kleebe);
					kleepija(vektorids6nedena[paarid2[i][2]], vektorids6nedena[paarid2[i][3]], kleebe2);
					kleepija(kleebe, kleebe2, kleebe3);
					kleepija(vektorids6nedena[paarid2[j][0]], vektorids6nedena[paarid2[j][1]], kleebe4);
					kleepija(vektorids6nedena[paarid2[j][2]], vektorids6nedena[paarid2[j][3]], kleebe5);
					kleepija(kleebe4, kleebe5, kleebe6);
					kleepija(kleebe3, kleebe6, kleebe7);
					*/
					for (int h = 0; h < 4; h++)
					{
						paarids6nedena3[kolmandaidpaare][h] = kleebe[h];
					}
					kolmandaidpaare++;
				}
			}
		}
		for (int i = 0; i < teisipaare; i++)	// kolmandate kleepumatute otsimine
		{
			kleepumatukolmas = 1;
			for (int j = i + 1; j < teisipaare; j++)
			{
				//printf("Paar1: %c%c%c%c Paar2: %c%c%c%c\n", paarids6nedena2[i][0], paarids6nedena2[i][1], paarids6nedena2[i][2], paarids6nedena2[i][3], paarids6nedena2[j][0], paarids6nedena2[j][1], paarids6nedena2[j][2], paarids6nedena2[j][3]);
				//printf("%d\n", kleepija(paarids6nedena2[i], paarids6nedena2[j], kleebe));
				if (kleepija(paarids6nedena2[i], paarids6nedena2[j], kleebe) == 0)
				{
					kleepumatukolmas = 0;
				}
			}
			if (kleepumatukolmas && nelikmassiiviteises(paarid2[i][0], paarid2[i][1], paarid2[i][2], paarid2[i][3], paarid3, teisipaare))	// kui nelik i ei kleepunud yhegi teisega, siis loeme ta lihtimplikandiks
			{
				kleepumatudkolmandad[kleepumatuidkolmandaid][0] = paarid2[i][0];
				kleepumatudkolmandad[kleepumatuidkolmandaid][1] = paarid2[i][1];
				kleepumatudkolmandad[kleepumatuidkolmandaid][2] = paarid2[i][2];
				kleepumatudkolmandad[kleepumatuidkolmandaid][3] = paarid2[i][3];
				kleepija(vektorids6nedena[paarid2[i][0]], vektorids6nedena[paarid2[i][1]], kleebe);
				kleepija(vektorids6nedena[paarid2[i][2]], vektorids6nedena[paarid2[i][3]], kleebe2);
				kleepija(kleebe, kleebe2, kleebe3);
				kleepumatuds6nedena3[kleepumatuidkolmandaid][0] = kleebe3[0];
				kleepumatuds6nedena3[kleepumatuidkolmandaid][1] = kleebe3[1];
				kleepumatuds6nedena3[kleepumatuidkolmandaid][2] = kleebe3[2];
				kleepumatuds6nedena3[kleepumatuidkolmandaid][3] = kleebe3[3];
				//printf("kleepumatud kolmandad: %d-%d-%d-%d\n", kleepumatudkolmandad[kleepumatuidkolmandaid][0], kleepumatudkolmandad[kleepumatuidkolmandaid][1], kleepumatudkolmandad[kleepumatuidkolmandaid][2], kleepumatudkolmandad[kleepumatuidkolmandaid][3]);
				kleepumatuidkolmandaid++;
			}
		}
		/*
		printf("\nKolmandad paarid: \n");
		for (int i = 0; i < kolmandaidpaare; i++)
		{
			printf("%d-%d-%d-%d   \t;\t%d-%d-%d-%d\t\t", paarid3[i][0], paarid3[i][1], paarid3[i][2], paarid3[i][3], paarid3[i][4], paarid3[i][5], paarid3[i][6], paarid3[i][7]);
			for (int j = 0; j < 4; j++)
			{
				printf("%c", paarids6nedena3[i][j]);
			}
			printf("\n");
		}
		printf("Kolmandad kleepumatud: (%d tk.)\n", kleepumatuidkolmandaid);
		for (int i = 0; i < kleepumatuidkolmandaid; i++)
		{
			printf("%d-%d-%d-%d\n", kleepumatudkolmandad[i][0], kleepumatudkolmandad[i][1], kleepumatudkolmandad[i][2], kleepumatudkolmandad[i][3]);
		}
		printf("\n");
		*/
		// ########### MDNK LIHTIMPLIKANDID ###########
		rangevektor = 0;
		implikantepuhvris = 0;
		for (int i = 0; i < kleepumatuidesimesi; i++)
		{
			kleepumatuds6nedena1[i][0] = vektorids6nedena[kleepumatudesimesed[i]][0];
			kleepumatuds6nedena1[i][1] = vektorids6nedena[kleepumatudesimesed[i]][1];
			kleepumatuds6nedena1[i][2] = vektorids6nedena[kleepumatudesimesed[i]][2];
			kleepumatuds6nedena1[i][3] = vektorids6nedena[kleepumatudesimesed[i]][3];
			//printf("%c%c%c%c\n", kleepumatuds6nedena1[i][0], kleepumatuds6nedena1[i][1], kleepumatuds6nedena1[i][2], kleepumatuds6nedena1[i][3]);
		}
		for (int i = 0; i < kleepumatuidesimesi; i++)
		{
			implikandipuhver[implikantepuhvris][0] = kleepumatuds6nedena1[i][0];
			implikandipuhver[implikantepuhvris][1] = kleepumatuds6nedena1[i][1];
			implikandipuhver[implikantepuhvris][2] = kleepumatuds6nedena1[i][2];
			implikandipuhver[implikantepuhvris][3] = kleepumatuds6nedena1[i][3];
			implikantepuhvris++;
			//printf("%c%c%c%c\n", implikandipuhver[i][0], implikandipuhver[i][1], implikandipuhver[i][2], implikandipuhver[i][3]);
		}
		for (int i = 0; i < kleepumatuidteisi; i++)
		{
			implikandipuhver[implikantepuhvris][0] = kleepumatuds6nedena2[i][0];
			implikandipuhver[implikantepuhvris][1] = kleepumatuds6nedena2[i][1];
			implikandipuhver[implikantepuhvris][2] = kleepumatuds6nedena2[i][2];
			implikandipuhver[implikantepuhvris][3] = kleepumatuds6nedena2[i][3];
			implikantepuhvris++;
			//printf("%c%c%c%c\n", implikandipuhver[implikantepuhvris-1][0], implikandipuhver[implikantepuhvris-1][1], implikandipuhver[implikantepuhvris-1][2], implikandipuhver[implikantepuhvris-1][3]);
		}
		for (int i = 0; i < kleepumatuidkolmandaid; i++)
		{
			implikandipuhver[implikantepuhvris][0] = kleepumatuds6nedena3[i][0];
			implikandipuhver[implikantepuhvris][1] = kleepumatuds6nedena3[i][1];
			implikandipuhver[implikantepuhvris][2] = kleepumatuds6nedena3[i][2];
			implikandipuhver[implikantepuhvris][3] = kleepumatuds6nedena3[i][3];
			implikantepuhvris++;
			//printf("%c%c%c%c\n", implikandipuhver[implikantepuhvris-1][0], implikandipuhver[implikantepuhvris-1][1], implikandipuhver[implikantepuhvris-1][2], implikandipuhver[implikantepuhvris-1][3]);
		}
		for (int i = 0; i < kolmandaidpaare; i++)
		{
			implikandipuhver[implikantepuhvris][0] = paarids6nedena3[i][0];
			implikandipuhver[implikantepuhvris][1] = paarids6nedena3[i][1];
			implikandipuhver[implikantepuhvris][2] = paarids6nedena3[i][2];
			implikandipuhver[implikantepuhvris][3] = paarids6nedena3[i][3];
			implikantepuhvris++;
			//printf("%c%c%c%c\n", implikandipuhver[implikantepuhvris-1][0], implikandipuhver[implikantepuhvris-1][1], implikandipuhver[implikantepuhvris-1][2], implikandipuhver[implikantepuhvris-1][3]);
		}
		lihtimplikante = 0;
		kordumatu = 1;
		for (int i = 0; i < implikantepuhvris; i++)
		{
			kordumatu = 1;
			for (int j = 0; j < lihtimplikante; j++)
			{
				//printf("%c%c%c%c|||%c%c%c%c|||\n", implikandipuhver[i][0], implikandipuhver[i][1], implikandipuhver[i][2], implikandipuhver[i][3], lihtimplikandid[lihtimplikante-1][0], lihtimplikandid[lihtimplikante-1][1], lihtimplikandid[lihtimplikante-1][2], lihtimplikandid[lihtimplikante-1][3]);
				if(implikandipuhver[i][0] == lihtimplikandid[j][0] && implikandipuhver[i][1] == lihtimplikandid[j][1] && implikandipuhver[i][2] == lihtimplikandid[j][2] && implikandipuhver[i][3] == lihtimplikandid[j][3])
				{
					//printf("korduv\n");
					kordumatu = 0;
				}
			}
			if (kordumatu)
			{
				lihtimplikandid[lihtimplikante][0] = implikandipuhver[i][0];
				lihtimplikandid[lihtimplikante][1] = implikandipuhver[i][1];
				lihtimplikandid[lihtimplikante][2] = implikandipuhver[i][2];
				lihtimplikandid[lihtimplikante][3] = implikandipuhver[i][3];
				//printf("%c%c%c%c\n", lihtimplikandid[lihtimplikante][0], lihtimplikandid[lihtimplikante][1], lihtimplikandid[lihtimplikante][2], lihtimplikandid[lihtimplikante][3]);
				lihtimplikante++;
			}
		}
		/*
		for (int i = 0; i < lihtimplikante; i++)
		{
			printf("%c%c%c%c\n", lihtimplikandid[i][0], lihtimplikandid[i][1], lihtimplikandid[i][2], lihtimplikandid[i][3]);
		}
		*/
		// ########### MDNK MINIMAALNE RANGE KATE ###########
		ei = 1;
		t2is = 0;
		elemente = 0;
		for (int i = 0; i < lihtimplikante; i++)
		{
			t2is = 0;
			for (int j = 0; j < rangeyhtsuurus; j++)
			{
				ei = 1;
				for (int k = 0; k < 4; k++)
				{
					//printf("%c;%c",lihtimplikandid[i][k], vektorids6nedena[rangeyhtedepiirkond[i]][k]);
					if (lihtimplikandid[i][k] != '-' && lihtimplikandid[i][k] != vektorids6nedena[rangeyhtedepiirkond[j]][k])
					{
						//printf("%c;%c",lihtimplikandid[i][k], vektorids6nedena[rangeyhtedepiirkond[j]][k]);
						ei = 0;
					}
				}
				if (ei)
				{
					t2is++;
				}
			}
			if (t2is)
			{
				katvad[elemente] = i;
				//printf("t2is (%d)\n", i);
				elemente++;
			}
		}
		rangeidlihtimplikante = elemente;
		for (int i = 0; i < rangeidlihtimplikante; i++)
		{
			rangedlihtimplikandid[i][0] = lihtimplikandid[katvad[i]][0];
			rangedlihtimplikandid[i][1] = lihtimplikandid[katvad[i]][1];
			rangedlihtimplikandid[i][2] = lihtimplikandid[katvad[i]][2];
			rangedlihtimplikandid[i][3] = lihtimplikandid[katvad[i]][3];
		}
		printf("LIHTIMPLIKANDID VEKTORKUJUL (%d tk.) JA RANGE KATE: \n\n", lihtimplikante);
		printf("Lihtimp; 1-pk\t");
		for (int i = 0; i < rangeyhtsuurus; i++)
		{
			printf("%d\t", rangeyhtedepiirkond[i]);
		}
		int maatriks[rangeidlihtimplikante][rangeyhtsuurus];
		printf("\n");
		for (int i = 0; i < rangeidlihtimplikante; i++)
		{
			printf("%c%c%c%c\t\t", rangedlihtimplikandid[i][0], rangedlihtimplikandid[i][1], rangedlihtimplikandid[i][2], rangedlihtimplikandid[i][3]);
			for (int j = 0; j < rangeyhtsuurus; j++)
			{
				ei = 1;
				for (int k = 0; k < 4; k++)
				{
					//printf("%c;%c",lihtimplikandid[i][k], vektorids6nedena[rangeyhtedepiirkond[i]][k]);
					if (rangedlihtimplikandid[i][k] != '-' && rangedlihtimplikandid[i][k] != vektorids6nedena[rangeyhtedepiirkond[j]][k])
					{
						//printf("%c;%c",lihtimplikandid[i][k], vektorids6nedena[rangeyhtedepiirkond[j]][k]);
						ei = 0;
					}
				}
				if (ei)
				{
					printf("X\t");
					maatriks[i][j] = 1;
				}
				else
				{
					printf("\t");
					maatriks[i][j] = 0;
				}
			}
			printf("\n");
			printf("-----------");
			for (int z = 0; z < rangeyhtsuurus; z++)
			{
				printf("--------");
			}
			printf("\n");
		}
		// minimaalse range katte otsimine maatriksi abil
		kaetud = 0;
		katteid = 0;
		valituid = 0;
		viimanekatja = 0;
		korduvimplikant = 0;
		for (int i = 0; i < rangeyhtsuurus; i++)
		{
			katteid = 0;
			for (int j = 0; j < rangeidlihtimplikante; j++)
			{
				if (maatriks[j][i] == 1)
				{
					katteid++;
					viimanekatja = j;
				}
			}
			if (katteid == 1)	// valime kindlalt lihtimplikandi, mis on mingi vektori korral ainsaks katjaks
			{
				korduvimplikant = 0;
				for (int k = 0; k < valituid; k++)
				{
					if (valitud[k] == viimanekatja)
					{
						korduvimplikant = 1;
					}
				}
				if (!korduvimplikant)
				{
					valitud[valituid] = viimanekatja;
					valituid++;
				}
			}
		}
		//printf("V2ltimatult valitud: ");
		printf("Implikant:kattem22r\n");
		/*
		for (int i = 0; i < valituid; i++)
		{
			if (i == valituid - 1)
			{
				printf("%d\n", valitud[i]);
			}
			else
			{
				printf("%d, ", valitud[i]);
			}
		}
		if (valituid == 0)
		{
			printf("-\n");
		}
		*/
		katteid = 0;
		suurimaidkatteid = 0;
		suurimvalimata = 0;
		rangekattuvus = 0;
		katab = 0;
		for (int i = 0; i < rangeidlihtimplikante; i++)	// t2idame massivi implikantide indekside ja vastavate kattuvust iseloomustavate suurustega
		{
			katteid = 0;
			for (int j = 0; j < rangeyhtsuurus; j++)
			{
				if (maatriks[i][j] == 1)
				{
					katteid++;
				}
				implikandidkattuvusega[i][0] = i;					// implikandi indeks
				implikandidkattuvusega[i][1] = katteid;		// implikandi kattuvus
			}
		}
		for (int i = 1; i < rangeidlihtimplikante; i++)	// sorteerime t2idetud massivi kattuvuses kasvavas j2rjekorras
		{
			for (int j = 0; j < rangeidlihtimplikante - i; j++)
			{
				if (implikandidkattuvusega[j][1] > implikandidkattuvusega[j+1][1])
				{
					puhver[0] = implikandidkattuvusega[j][0];
					puhver[1] = implikandidkattuvusega[j][1];
					implikandidkattuvusega[j][0] = implikandidkattuvusega[j+1][0];
					implikandidkattuvusega[j][1] = implikandidkattuvusega[j+1][1];
					implikandidkattuvusega[j+1][0] = puhver[0];
					implikandidkattuvusega[j+1][1] = puhver[1];
				}
			}
		}
		for (int i = 0; i < rangeidlihtimplikante; i++)
		{
			printf("%d:%d\t", implikandidkattuvusega[i][0], implikandidkattuvusega[i][1]);
		}
		d = rangeidlihtimplikante - 1;
		rist = 0;
		kattuvusm22r = 0;
		printf("\n");
		while(!kaetud)	// lisame k6ige rohkem katvaid implikante seni, kuni kogu range 1-piirkond saab kaetud
		{
			kordub = 0;
			//printf("dektrementeerimata d: %d\n", d);
			for (int i = 0; i < valituid; i++)
			{
				//printf("valitud vs v6rreldav %d:%d\n", valitud[i], implikandidkattuvusega[d][0]);
				if (implikandidkattuvusega[d][0] == valitud[i])
				{
					//printf("-\n");
					kordub = 1;
				}
			}
			if (!kordub)
			{
				//printf("+\n");
				valitud[valituid] = implikandidkattuvusega[d][0];
				valituid++;
			}
			kattuvusm22r = 0;
			for (int i = 0; i < rangeyhtsuurus; i++)
			{
				rist = 0;
				for (int j = 0; j < valituid; j++)
				{
					if (maatriks[valitud[j]][i] == 1)
					{
						rist = 1;
					}
				}
				if (rist)
				{
					kattuvusm22r++;
				}
			}
			//printf("kattuvusm22r: %d\n", kattuvusm22r);
			if (kattuvusm22r == rangeyhtsuurus)
			{
				kaetud = 1;
			}
			d--;
			//printf("dektrementeeritud d: %d\n", d);
		}

		printf("MDNK (¬ on j2rgneva muutuja ivnersioon): \n");
		for (int i = 0; i < valituid; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (rangedlihtimplikandid[valitud[i]][j] == '1')
				{
					printf("x%d", j + 1);
					fprintf(MDNK, "x%d", j + 1);
				}
				if (rangedlihtimplikandid[valitud[i]][j] == '0')
				{
					printf("¬x%d", j + 1);
					fprintf(MDNK, "¬x%d", j + 1);
				}
			}
			if (i < valituid - 1)
			{
				printf(" v ");
				fprintf(MDNK, " v ");
			}
		}
		printf("\nMINIMEERITUD DISJUNKTIIVNE NORMAALKUJU EDUKALT FAILI SALVESTATUD!\n");
	}

	esimesipaare = 0;
	teisipaare = 0;
	kolmandaidpaare = 0;
	kleepumatuidesimesi = 0;
	kleepumatuidteisi = 0;
	kleepumatuidkolmandaid = 0;
	// ########### MKNK KLEEPIMINE ###########
	if (rangenulsuurus > 0) // OSALISELT M22RATUD FUNKTSIOONIL LEIDUB MKNK AINULT SIIS, KUI TA YHTEDEPIIRKOND POLE TYHI HULK
	{
		for (int i = 0; i < 15; i++)	// esimene kleepimine
		{
			for (int j = i + 1; j < 16; j++)
			{
				if (kleepija(vektorids6nedena[i], vektorids6nedena[j], kleebe) == 0 && !elementmassiivis(i, nullidepiirkond, nulsuurus) && !elementmassiivis(j, nullidepiirkond, nulsuurus))
				{
					paarid1[esimesipaare][0] = i;
					paarid1[esimesipaare][1] = j;
					for (int h = 0; h < 4; h++)
					{
						paarids6nedena1[esimesipaare][h] = kleebe[h];
					}
					esimesipaare++;
				}
			}
		}
		for (int i = 0; i < 16; i++)	// esimeste kleepumatute otsimine
		{
			kleepumatuesimene = 1;
			for (int j = i + 1; j < 16; j++)
			{
				if (kleepija(vektorids6nedena[i], vektorids6nedena[j], kleebe) == 0 && !elementmassiivis(i, nullidepiirkond, nulsuurus) && !elementmassiivis(j, nullidepiirkond, nulsuurus))
				{
					kleepumatuesimene = 0;	// vektor i on kasv6i kordki kleebitav, seega muudame v22rtuse 0-ks
				}
			}
			if (kleepumatuesimene && !elementmassiivis(i, nullidepiirkond, nulsuurus) && elementpaariteises(i, paarid1, esimesipaare))	// kui vektor i ei kleepunud yhegi teisega, siis loeme ta lihtimplikandiks
			{
				kleepumatudesimesed[kleepumatuidesimesi] = i;
				kleepumatuidesimesi++;
			}
		}
		/*
		printf("Esimesed paarid:\n");
		for (int i = 0; i < esimesipaare; i++)
		{
			printf("%d\t-\t%d\t\t\t\t", paarid1[i][0], paarid1[i][1]);
			for (int j = 0; j < 4; j++)
			{
				printf("%c", paarids6nedena1[i][j]);
			}
			printf("\n");
		}

		printf("Esimesed kleepumatud (%d tk.):\n", kleepumatuidesimesi);
		for (int i = 0; i < kleepumatuidesimesi; i++)
		{
			printf("%d\t\t\t\t\t\t%c%c%c%c", kleepumatudesimesed[i], vektorids6nedena[kleepumatudesimesed[i]][0], vektorids6nedena[kleepumatudesimesed[i]][1], vektorids6nedena[kleepumatudesimesed[i]][2], vektorids6nedena[kleepumatudesimesed[i]][3]);
			printf("\n");
		}
		*/
		//printf("%d\n", elementmassiivis(12, paarid1[1], esimesipaare));
		//printf("%d", elementpaariteises(12, paarid1, esimesipaare));
		for (int i = 0; i < esimesipaare - 1; i++)	// teine kleepimine
		{
			for (int j = i + 1; j < esimesipaare; j++)
			{
				if (kleepija(paarids6nedena1[i], paarids6nedena1[j], kleebe) == 0)
				{
					paarid2[teisipaare][0] = paarid1[i][0];
					paarid2[teisipaare][1] = paarid1[i][1];
					paarid2[teisipaare][2] = paarid1[j][0];
					paarid2[teisipaare][3] = paarid1[j][1];
					for (int h = 0; h < 4; h++)
					{
						paarids6nedena2[teisipaare][h] = kleebe[h];
					}
					teisipaare++;
				}
			}
		}
		for (int i = 0; i < esimesipaare; i++)	// teiste kleepumatute otsimine
		{
			kleepumatuteine = 1;
			for (int j = i + 1; j < esimesipaare; j++)
			{
				if (kleepija(paarids6nedena1[i], paarids6nedena1[j], kleebe) == 0)
				{
					kleepumatuteine = 0; // paar i on kasv6i kordki kleebitav, seega muudame v22rtuse 0-ks
				}
			}
			//printf("kontroll: %d\tpaar:%d-%d\n", paarmassiiviteises(paarid1[i][0], paarid1[i][1], paarid2, esimesipaare), paarid1[i][0], paarid1[i][1]);
			if (kleepumatuteine && paarmassiiviteises(paarid1[i][0], paarid1[i][1], paarid2, esimesipaare))	// kui paar i ei kleepunud yhegi teisega, siis loeme ta lihtimplikandiks
			{
				kleepumatudteised[kleepumatuidteisi][0] = paarid1[i][0];
				kleepumatudteised[kleepumatuidteisi][1] = paarid1[i][1];
				kleepija(vektorids6nedena[paarid1[i][0]], vektorids6nedena[paarid1[i][1]], kleebe);
				kleepumatuds6nedena2[kleepumatuidteisi][0] = kleebe[0];
				kleepumatuds6nedena2[kleepumatuidteisi][1] = kleebe[1];
				kleepumatuds6nedena2[kleepumatuidteisi][2] = kleebe[2];
				kleepumatuds6nedena2[kleepumatuidteisi][3] = kleebe[3];
				//printf("kleepumatud teised: %d-%d\n", kleepumatudteised[kleepumatuidteisi][0], kleepumatudteised[kleepumatuidteisi][1]);
				kleepumatuidteisi++;
			}
		}
		/*
		printf("\nTeised paarid:\n");
		for (int i = 0; i < teisipaare; i++)
		{
			printf("%d-%d\t;\t%d-%d\t\t\t\t", paarid2[i][0], paarid2[i][1], paarid2[i][2], paarid2[i][3]);
			for (int j = 0; j < 4; j++)
			{
				printf("%c", paarids6nedena2[i][j]);
			}
			printf("\n");
		}
		printf("Teised kleepumatud (%d tk.):\n", kleepumatuidteisi);
		for (int i = 0; i < kleepumatuidteisi; i++)
		{
			printf("%d-%d\t\t\t\t", kleepumatudteised[i][0], kleepumatudteised[i][1]);
			printf("\n");
		}
		*/
		for (int i = 0; i < teisipaare - 1; i++)	// kolmas kleepimine
		{
			for (int j = i + 1; j < teisipaare; j++)
			{
				//printf("Paar1: %c%c%c%c Paar2: %c%c%c%c\n", paarids6nedena2[i][0], paarids6nedena2[i][1], paarids6nedena2[i][2], paarids6nedena2[i][3], paarids6nedena2[j][0], paarids6nedena2[j][1], paarids6nedena2[j][2], paarids6nedena2[j][3]);
				//printf("%d\n", kleepija(paarids6nedena2[i], paarids6nedena2[j], kleebe));
				if (kleepija(paarids6nedena2[i], paarids6nedena2[j], kleebe) == 0)
				{
					paarid3[kolmandaidpaare][0] = paarid2[i][0];
					paarid3[kolmandaidpaare][1] = paarid2[i][1];
					paarid3[kolmandaidpaare][2] = paarid2[i][2];
					paarid3[kolmandaidpaare][3] = paarid2[i][3];
					paarid3[kolmandaidpaare][4] = paarid2[j][0];
					paarid3[kolmandaidpaare][5] = paarid2[j][1];
					paarid3[kolmandaidpaare][6] = paarid2[j][2];
					paarid3[kolmandaidpaare][7] = paarid2[j][3];
					/*
					kleepija(vektorids6nedena[paarid2[i][0]], vektorids6nedena[paarid2[i][1]], kleebe);
					kleepija(vektorids6nedena[paarid2[i][2]], vektorids6nedena[paarid2[i][3]], kleebe2);
					kleepija(kleebe, kleebe2, kleebe3);
					kleepija(vektorids6nedena[paarid2[j][0]], vektorids6nedena[paarid2[j][1]], kleebe4);
					kleepija(vektorids6nedena[paarid2[j][2]], vektorids6nedena[paarid2[j][3]], kleebe5);
					kleepija(kleebe4, kleebe5, kleebe6);
					kleepija(kleebe3, kleebe6, kleebe7);
					*/
					for (int h = 0; h < 4; h++)
					{
						paarids6nedena3[kolmandaidpaare][h] = kleebe[h];
					}
					kolmandaidpaare++;
				}
			}
		}
		for (int i = 0; i < teisipaare; i++)	// kolmandate kleepumatute otsimine
		{
			kleepumatukolmas = 1;
			for (int j = i + 1; j < teisipaare; j++)
			{
				//printf("Paar1: %c%c%c%c Paar2: %c%c%c%c\n", paarids6nedena2[i][0], paarids6nedena2[i][1], paarids6nedena2[i][2], paarids6nedena2[i][3], paarids6nedena2[j][0], paarids6nedena2[j][1], paarids6nedena2[j][2], paarids6nedena2[j][3]);
				//printf("%d\n", kleepija(paarids6nedena2[i], paarids6nedena2[j], kleebe));
				if (kleepija(paarids6nedena2[i], paarids6nedena2[j], kleebe) == 0)
				{
					kleepumatukolmas = 0;
				}
			}
			if (kleepumatukolmas && nelikmassiiviteises(paarid2[i][0], paarid2[i][1], paarid2[i][2], paarid2[i][3], paarid3, teisipaare))	// kui nelik i ei kleepunud yhegi teisega, siis loeme ta lihtimplikandiks
			{
				kleepumatudkolmandad[kleepumatuidkolmandaid][0] = paarid2[i][0];
				kleepumatudkolmandad[kleepumatuidkolmandaid][1] = paarid2[i][1];
				kleepumatudkolmandad[kleepumatuidkolmandaid][2] = paarid2[i][2];
				kleepumatudkolmandad[kleepumatuidkolmandaid][3] = paarid2[i][3];
				kleepija(vektorids6nedena[paarid2[i][0]], vektorids6nedena[paarid2[i][1]], kleebe);
				kleepija(vektorids6nedena[paarid2[i][2]], vektorids6nedena[paarid2[i][3]], kleebe2);
				kleepija(kleebe, kleebe2, kleebe3);
				kleepumatuds6nedena3[kleepumatuidkolmandaid][0] = kleebe3[0];
				kleepumatuds6nedena3[kleepumatuidkolmandaid][1] = kleebe3[1];
				kleepumatuds6nedena3[kleepumatuidkolmandaid][2] = kleebe3[2];
				kleepumatuds6nedena3[kleepumatuidkolmandaid][3] = kleebe3[3];
				//printf("kleepumatud kolmandad: %d-%d-%d-%d\n", kleepumatudkolmandad[kleepumatuidkolmandaid][0], kleepumatudkolmandad[kleepumatuidkolmandaid][1], kleepumatudkolmandad[kleepumatuidkolmandaid][2], kleepumatudkolmandad[kleepumatuidkolmandaid][3]);
				kleepumatuidkolmandaid++;
			}
		}
		/*
		printf("\nKolmandad paarid: \n");
		for (int i = 0; i < kolmandaidpaare; i++)
		{
			printf("%d-%d-%d-%d   \t;\t%d-%d-%d-%d\t\t", paarid3[i][0], paarid3[i][1], paarid3[i][2], paarid3[i][3], paarid3[i][4], paarid3[i][5], paarid3[i][6], paarid3[i][7]);
			for (int j = 0; j < 4; j++)
			{
				printf("%c", paarids6nedena3[i][j]);
			}
			printf("\n");
		}
		printf("Kolmandad kleepumatud: (%d tk.)\n", kleepumatuidkolmandaid);
		for (int i = 0; i < kleepumatuidkolmandaid; i++)
		{
			printf("%d-%d-%d-%d\n", kleepumatudkolmandad[i][0], kleepumatudkolmandad[i][1], kleepumatudkolmandad[i][2], kleepumatudkolmandad[i][3]);
		}
		printf("\n");
		*/
		// ########### MDNK LIHTIMPLIKANDID ###########
		rangevektor = 0;
		implikantepuhvris = 0;
		for (int i = 0; i < kleepumatuidesimesi; i++)
		{
			kleepumatuds6nedena1[i][0] = vektorids6nedena[kleepumatudesimesed[i]][0];
			kleepumatuds6nedena1[i][1] = vektorids6nedena[kleepumatudesimesed[i]][1];
			kleepumatuds6nedena1[i][2] = vektorids6nedena[kleepumatudesimesed[i]][2];
			kleepumatuds6nedena1[i][3] = vektorids6nedena[kleepumatudesimesed[i]][3];
			//printf("%c%c%c%c\n", kleepumatuds6nedena1[i][0], kleepumatuds6nedena1[i][1], kleepumatuds6nedena1[i][2], kleepumatuds6nedena1[i][3]);
		}
		for (int i = 0; i < kleepumatuidesimesi; i++)
		{
			implikandipuhver[implikantepuhvris][0] = kleepumatuds6nedena1[i][0];
			implikandipuhver[implikantepuhvris][1] = kleepumatuds6nedena1[i][1];
			implikandipuhver[implikantepuhvris][2] = kleepumatuds6nedena1[i][2];
			implikandipuhver[implikantepuhvris][3] = kleepumatuds6nedena1[i][3];
			implikantepuhvris++;
			//printf("%c%c%c%c\n", implikandipuhver[i][0], implikandipuhver[i][1], implikandipuhver[i][2], implikandipuhver[i][3]);
		}
		for (int i = 0; i < kleepumatuidteisi; i++)
		{
			implikandipuhver[implikantepuhvris][0] = kleepumatuds6nedena2[i][0];
			implikandipuhver[implikantepuhvris][1] = kleepumatuds6nedena2[i][1];
			implikandipuhver[implikantepuhvris][2] = kleepumatuds6nedena2[i][2];
			implikandipuhver[implikantepuhvris][3] = kleepumatuds6nedena2[i][3];
			implikantepuhvris++;
			//printf("%c%c%c%c\n", implikandipuhver[implikantepuhvris-1][0], implikandipuhver[implikantepuhvris-1][1], implikandipuhver[implikantepuhvris-1][2], implikandipuhver[implikantepuhvris-1][3]);
		}
		for (int i = 0; i < kleepumatuidkolmandaid; i++)
		{
			implikandipuhver[implikantepuhvris][0] = kleepumatuds6nedena3[i][0];
			implikandipuhver[implikantepuhvris][1] = kleepumatuds6nedena3[i][1];
			implikandipuhver[implikantepuhvris][2] = kleepumatuds6nedena3[i][2];
			implikandipuhver[implikantepuhvris][3] = kleepumatuds6nedena3[i][3];
			implikantepuhvris++;
			//printf("%c%c%c%c\n", implikandipuhver[implikantepuhvris-1][0], implikandipuhver[implikantepuhvris-1][1], implikandipuhver[implikantepuhvris-1][2], implikandipuhver[implikantepuhvris-1][3]);
		}
		for (int i = 0; i < kolmandaidpaare; i++)
		{
			implikandipuhver[implikantepuhvris][0] = paarids6nedena3[i][0];
			implikandipuhver[implikantepuhvris][1] = paarids6nedena3[i][1];
			implikandipuhver[implikantepuhvris][2] = paarids6nedena3[i][2];
			implikandipuhver[implikantepuhvris][3] = paarids6nedena3[i][3];
			implikantepuhvris++;
			//printf("%c%c%c%c\n", implikandipuhver[implikantepuhvris-1][0], implikandipuhver[implikantepuhvris-1][1], implikandipuhver[implikantepuhvris-1][2], implikandipuhver[implikantepuhvris-1][3]);
		}
		lihtimplikante = 0;
		kordumatu = 1;
		for (int i = 0; i < implikantepuhvris; i++)
		{
			kordumatu = 1;
			for (int j = 0; j < lihtimplikante; j++)
			{
				//printf("%c%c%c%c|||%c%c%c%c|||\n", implikandipuhver[i][0], implikandipuhver[i][1], implikandipuhver[i][2], implikandipuhver[i][3], lihtimplikandid[lihtimplikante-1][0], lihtimplikandid[lihtimplikante-1][1], lihtimplikandid[lihtimplikante-1][2], lihtimplikandid[lihtimplikante-1][3]);
				if(implikandipuhver[i][0] == lihtimplikandid[j][0] && implikandipuhver[i][1] == lihtimplikandid[j][1] && implikandipuhver[i][2] == lihtimplikandid[j][2] && implikandipuhver[i][3] == lihtimplikandid[j][3])
				{
					//printf("korduv\n");
					kordumatu = 0;
				}
			}
			if (kordumatu)
			{
				lihtimplikandid[lihtimplikante][0] = implikandipuhver[i][0];
				lihtimplikandid[lihtimplikante][1] = implikandipuhver[i][1];
				lihtimplikandid[lihtimplikante][2] = implikandipuhver[i][2];
				lihtimplikandid[lihtimplikante][3] = implikandipuhver[i][3];
				//printf("%c%c%c%c\n", lihtimplikandid[lihtimplikante][0], lihtimplikandid[lihtimplikante][1], lihtimplikandid[lihtimplikante][2], lihtimplikandid[lihtimplikante][3]);
				lihtimplikante++;
			}
		}
		/*
		for (int i = 0; i < lihtimplikante; i++)
		{
			printf("%c%c%c%c\n", lihtimplikandid[i][0], lihtimplikandid[i][1], lihtimplikandid[i][2], lihtimplikandid[i][3]);
		}
		*/
		// ########### MDNK MINIMAALNE RANGE KATE ###########
		ei = 1;
		t2is = 0;
		elemente = 0;
		for (int i = 0; i < lihtimplikante; i++)
		{
			t2is = 0;
			for (int j = 0; j < rangenulsuurus; j++)
			{
				ei = 1;
				for (int k = 0; k < 4; k++)
				{
					//printf("%c;%c",lihtimplikandid[i][k], vektorids6nedena[rangeyhtedepiirkond[i]][k]);
					if (lihtimplikandid[i][k] != '-' && lihtimplikandid[i][k] != vektorids6nedena[rangenullidepiirkond[j]][k])
					{
						//printf("%c;%c",lihtimplikandid[i][k], vektorids6nedena[rangeyhtedepiirkond[j]][k]);
						ei = 0;
					}
				}
				if (ei)
				{
					t2is++;
				}
			}
			if (t2is)
			{
				katvad[elemente] = i;
				//printf("t2is (%d)\n", i);
				elemente++;
			}
		}
		rangeidlihtimplikante = elemente;
		for (int i = 0; i < rangeidlihtimplikante; i++)
		{
			rangedlihtimplikandid[i][0] = lihtimplikandid[katvad[i]][0];
			rangedlihtimplikandid[i][1] = lihtimplikandid[katvad[i]][1];
			rangedlihtimplikandid[i][2] = lihtimplikandid[katvad[i]][2];
			rangedlihtimplikandid[i][3] = lihtimplikandid[katvad[i]][3];
		}
		printf("\nKLEEBITUD NULLID VEKTORKUJUL (%d tk.) JA RANGE KATE: \n\n", lihtimplikante);
		printf("Nullide; 1-pk\t");
		for (int i = 0; i < rangenulsuurus; i++)
		{
			printf("%d\t", rangenullidepiirkond[i]);
		}
		int maatriks2[rangeidlihtimplikante][rangenulsuurus];
		printf("\n");
		for (int i = 0; i < rangeidlihtimplikante; i++)
		{
			printf("%c%c%c%c\t\t", rangedlihtimplikandid[i][0], rangedlihtimplikandid[i][1], rangedlihtimplikandid[i][2], rangedlihtimplikandid[i][3]);
			for (int j = 0; j < rangenulsuurus; j++)
			{
				ei = 1;
				for (int k = 0; k < 4; k++)
				{
					//printf("%c;%c",lihtimplikandid[i][k], vektorids6nedena[rangeyhtedepiirkond[i]][k]);
					if (rangedlihtimplikandid[i][k] != '-' && rangedlihtimplikandid[i][k] != vektorids6nedena[rangenullidepiirkond[j]][k])
					{
						//printf("%c;%c",lihtimplikandid[i][k], vektorids6nedena[rangeyhtedepiirkond[j]][k]);
						ei = 0;
					}
				}
				if (ei)
				{
					printf("X\t");
					maatriks2[i][j] = 1;
				}
				else
				{
					printf("\t");
					maatriks2[i][j] = 0;
				}
			}
			printf("\n");
			printf("-----------");
			for (int z = 0; z < rangenulsuurus; z++)
			{
				printf("--------");
			}
			printf("\n");
		}
		// minimaalse range katte otsimine maatriksi abil
		kaetud = 0;
		katteid = 0;
		valituid = 0;
		viimanekatja = 0;
		korduvimplikant = 0;
		valitud[rangeidlihtimplikante];
		for (int i = 0; i < rangenulsuurus; i++)
		{
			katteid = 0;
			for (int j = 0; j < rangeidlihtimplikante; j++)
			{
				if (maatriks2[j][i] == 1)
				{
					katteid++;
					viimanekatja = j;
				}
			}
			if (katteid == 1)	// valime kindlalt lihtimplikandi, mis on mingi vektori korral ainsaks katjaks
			{
				korduvimplikant = 0;
				for (int k = 0; k < valituid; k++)
				{
					if (valitud[k] == viimanekatja)
					{
						korduvimplikant = 1;
					}
				}
				if (!korduvimplikant)
				{
					valitud[valituid] = viimanekatja;
					valituid++;
				}
			}
		}
		//printf("V2ltimatult valitud: ");
		printf("Kleebe:kattem22r\n");
		/*
		for (int i = 0; i < valituid; i++)
		{
			if (i == valituid - 1)
			{
				printf("%d\n", valitud[i]);
			}
			else
			{
				printf("%d, ", valitud[i]);
			}
		}
		if (valituid == 0)
		{
			printf("-\n");
		}
		*/
		katteid = 0;
		suurimaidkatteid = 0;
		suurimvalimata = 0;
		rangekattuvus = 0;
		int implikandidkattuvusega2[rangeidlihtimplikante][2];	// esimene element on implikandi indeks, teine element n2itab kui palju vastav lihtimplikant katab
		katab = 0;
		for (int i = 0; i < rangeidlihtimplikante; i++)	// t2idame massivi implikantide indekside ja vastavate kattuvust iseloomustavate suurustega
		{
			katteid = 0;
			for (int j = 0; j < rangenulsuurus; j++)
			{
				if (maatriks2[i][j] == 1)
				{
					katteid++;
				}
				implikandidkattuvusega2[i][0] = i;					// implikandi indeks
				implikandidkattuvusega2[i][1] = katteid;		// implikandi kattuvus
			}
		}
		for (int i = 1; i < rangeidlihtimplikante; i++)	// sorteerime t2idetud massivi kattuvuses kasvavas j2rjekorras
		{
			for (int j = 0; j < rangeidlihtimplikante - i; j++)
			{
				if (implikandidkattuvusega2[j][1] > implikandidkattuvusega2[j+1][1])
				{
					puhver[0] = implikandidkattuvusega2[j][0];
					puhver[1] = implikandidkattuvusega2[j][1];
					implikandidkattuvusega2[j][0] = implikandidkattuvusega2[j+1][0];
					implikandidkattuvusega2[j][1] = implikandidkattuvusega2[j+1][1];
					implikandidkattuvusega2[j+1][0] = puhver[0];
					implikandidkattuvusega2[j+1][1] = puhver[1];
				}
			}
		}
		for (int i = 0; i < rangeidlihtimplikante; i++)
		{
			printf("%d:%d\t", implikandidkattuvusega2[i][0], implikandidkattuvusega2[i][1]);
		}
		d = rangeidlihtimplikante - 1;
		rist = 0;
		kattuvusm22r = 0;
		printf("\n");
		while(!kaetud)	// lisame k6ige rohkem katvaid implikante seni, kuni kogu range 1-piirkond saab kaetud
		{
			kordub = 0;
			//printf("dektrementeerimata d: %d\n", d);
			for (int i = 0; i < valituid; i++)
			{
				//printf("valitud vs v6rreldav %d:%d\n", valitud[i], implikandidkattuvusega[d][0]);
				if (implikandidkattuvusega2[d][0] == valitud[i])
				{
					//printf("-\n");
					kordub = 1;
				}
			}
			if (!kordub)
			{
				//printf("+\n");
				valitud[valituid] = implikandidkattuvusega2[d][0];
				valituid++;
			}
			kattuvusm22r = 0;
			for (int i = 0; i < rangenulsuurus; i++)
			{
				rist = 0;
				for (int j = 0; j < valituid; j++)
				{
					if (maatriks2[valitud[j]][i] == 1)
					{
						rist = 1;
					}
				}
				if (rist)
				{
					kattuvusm22r++;
				}
			}
			//printf("kattuvusm22r: %d\n", kattuvusm22r);
			if (kattuvusm22r == rangenulsuurus)
			{
				kaetud = 1;
			}
			d--;
			//printf("dektrementeeritud d: %d\n", d);
		}

		int loend = 0, loendur = 0;
		printf("MKNK (¬ on j2rgneva muutuja ivnersioon): \n");
		for (int i = 0; i < valituid; i++)
		{
			loend = 0;
			loendur = 0;
			printf("(");
			fprintf(MKNK, "(");
			for (int j = 0; j < 4; j++)
			{
				if (rangedlihtimplikandid[valitud[i]][j] == '0' || rangedlihtimplikandid[valitud[i]][j] == '1')
				{
					loend++;
				}
			}
			for (int j = 0; j < 4; j++)
			{
				if (rangedlihtimplikandid[valitud[i]][j] == '0')
				{
					printf("x%d", j + 1);
					fprintf(MKNK, "x%d", j + 1);
					loendur++;
					if (loendur < loend)
					{
						printf(" v ");
						fprintf(MKNK, " v ");
					}
				}
				if (rangedlihtimplikandid[valitud[i]][j] == '1')
				{
					printf("¬x%d", j + 1);
					fprintf(MKNK, "¬x%d", j + 1);
					loendur++;
					if (loendur < loend)
					{
						printf(" v ");
						fprintf(MKNK, " v ");
					}
				}
			}
			printf(")");
			fprintf(MKNK, ")");
		}
		printf("\nMINIMEERITUD KONJUNKTIIVNE NORMAALKUJU EDUKALT FAILI SALVESTATUD!\n");
	}
	return 0;
}

int GenjaMin(int len, char argv[])
{
	FILE * LOGI = fopen("logifail.txt", "w");
	int ViisViimast, *pViisViimast = &ViisViimast, konstant = 7, *pkonstant = &konstant;
	if (sisestus(len, argv, pViisViimast, pkonstant))
	{
		return 1;
	}
	printf("Viieks viimaseks numbriks loeti: %d\n", ViisViimast);
	printf("Teguriks loeti: %d\n", konstant);
	FILE * F = fopen("t6ev22rtustabel.txt", "w");
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
	fclose(LOGI);
	return 0;
}

#include <string>
#include <iostream>
#include "..\include/StringHelper.h"
#include "..\include/Encoder.h"

void writeOutputFile(const String outFile,const String output)
{
	FILE* file;

	fopen_s(&file, outFile.c_str(), "w");
	if (!file)
	{
		printf("Could not open file %s for writing.\n", outFile.c_str());
		return;
	}
	fprintf_s(file, "%s", output.c_str());
	fclose(file);
}

int main()
{
	system("chcp 1250");
	char line[256];
	puts("Kérem adja meg a kódolandó szöveget(maximum 255 karakter):");
	gets_s(line, 256);

	auto toEncodeString = String(line).toUpper();
	if(toEncodeString.getLenght()==0)
	{
		puts("Nincs megadva kódolandó szöveg.");
		getchar();
		return 0;
	}
	toEncodeString.RemoveAccents();
	auto acceptableString = toEncodeString.getAcceptableString();
	if (acceptableString.getLenght() == 0)
	{
		puts("Az átalakítás után nem maradt felhasználható karakterlánc.");
		getchar();
		return 0;
	}
	puts("A formai követelmények szerint átalakított szöveg:");
	puts(acceptableString.c_str());
	
	Encoder enc = Encoder("Resource\\vtabla.dat");
	enc.Init();
	puts("Kérem adja meg a kulcsot ami 5 karakterbõl kell hogy álljon!");
	gets_s(line, 256);
	if(!enc.setKey(line))
	{
		getchar();
		return 0;
	}
	String result = enc.getEncodedString(acceptableString);
	puts(result.c_str());
	writeOutputFile("kodolt.dat", result);
	//getchar();
	/*while (true)
	{
		String toEncodeString = "Ez a próba szöveg, amit kódolunk!";
		toEncodeString = toEncodeString.toUpper();
		toEncodeString.RemoveAccents();
		String acceptableString = toEncodeString.getAcceptableString();

		Encoder enc = Encoder("Resource\\vtabla.dat");
		enc.Init();
		enc.setKey("auto");
		
		String result = enc.getEncodedString(acceptableString);
		puts(result.c_str());
		writeOutputFile("kodolt.dat", result);
	}*/
	getchar();
	return 0;
}
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
	char line[255];

	gets_s(line, 255);

	auto toEncodeString = String(line).toUpper();
	toEncodeString.RemoveAccents();
	auto acceptableString = toEncodeString.getAcceptableString();
	puts(acceptableString.c_str());
	
	Encoder enc = Encoder("Resource\\vtabla.dat");
	enc.Init();
	gets_s(line, 5);
	enc.setKey(line);
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
	return 0;
}
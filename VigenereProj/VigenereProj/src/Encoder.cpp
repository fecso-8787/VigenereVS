#include "..\include/Encoder.h"

Encoder::Encoder(String fileName)
{
	m_key = "";
	m_table = nullptr;
	m_inputFilePath = fileName;
}

Encoder::~Encoder()
{
	delete[] m_table;
}

bool Encoder::setKey(String key)
{
	bool success = true;
	if (key.getLenght() > 5 || key.getLenght()==0)
	{
		puts("A kulcsnak maximum 5 �s minimum 1 karakterb�l kell �llnia");
		success = false;
	}
	m_key = key.toUpper();
	if (isKeyContainsBadChar())
	{
		puts("Hib�san megadott kulcs.Csak az �kezetmentes bet�k az elfogadottak.");
		success = false;
	}

	
	return success;
}

const String& Encoder::getKey()const
{
	return m_key;
}

bool Encoder::isKeyContainsBadChar()
{
	for(unsigned int i=0;i<m_key.getLenght();i++)
	{
		if(!String::isAcceptedCharacter(m_key[i]))
		{
			return true;
		}
	}
	return false;
}

String Encoder::getEncodedString(const String& toEncode)
{
	unsigned short keyLength = toEncode.getLenght()+1;
	if (keyLength < m_key.getLenght())
	{
		keyLength++;
	}
	char* keyString = new char[keyLength];
	for(int i=0;i<keyLength;i++)
	{
		keyString[i] = m_key[i%(m_key.getLenght())];
	}
	keyString[keyLength - 1] = '\0';
	puts(keyString);

	char* encodedString = new char[toEncode.getLenght()+1];

	for(unsigned int i=0;i<toEncode.getLenght();i++)
	{
		int rowNo = getRowNumberByChar(toEncode.c_str()[i]);
		int columnNo = getColumnNumberByChar(keyString[i]);
		encodedString[i] = m_table[rowNo][columnNo];
	}

	encodedString[toEncode.getLenght()] = '\0';
	String result = encodedString;
	delete[] encodedString;
	delete[] keyString;
	return result;
}

int Encoder::getColumnNumberByChar(const char& input) const
{
	int result = 0;
	while(m_table[0][result]!='\0')
	{
		if (m_table[0][result] == input)
			break;
		result++;
	}
	return result;
}

int Encoder::getRowNumberByChar(const char& input) const
{
	int result = 0;
	while (m_table[result][0] != '\0')
	{
		if (m_table[result][0] == input)
			break;
		result++;
	}
	return result;
}

void Encoder::Init()
{
	FILE* file;
	char line[MAX_LINE_LEN];

	fopen_s(&file,m_inputFilePath.c_str(), "r");
	if (!file)
	{
		printf("Could not open file %s.\n",m_inputFilePath.c_str());
		return;
	}
	int lineNum = 0;
	while (fgets(line, MAX_LINE_LEN, file))
	{
		lineNum++;
	}
	rewind(file);
	m_table = new String[lineNum];
	lineNum = 0;
	while (fgets(line, MAX_LINE_LEN, file))
	{
		m_table[lineNum] = line;
		m_table[lineNum].removeAll('\n');
		lineNum++;
	}
	fclose(file);
}

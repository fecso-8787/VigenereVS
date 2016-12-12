#include "../include/StringHelper.h"

String::String()
{
	m_charArray = nullptr;
	m_length = 0;
}

String::String(const String& input)
{
	if (input.c_str())
	{
		m_length = input.getLenght()+1;
		m_charArray = new char[m_length];
		strcpy_s(m_charArray, (m_length) * sizeof(char), input.c_str());
	}
	else
	{
		m_charArray = nullptr;
		m_length = 0;
	}
}

String::String(const char * input)
{
	if (input)
	{
		m_length=static_cast<unsigned int>(strlen(input))+1;
		m_charArray = new char[m_length];
		strcpy_s(m_charArray, (m_length)*sizeof(char), input);
	}
	else
	{
		m_charArray = nullptr;
		m_length = 0;
	}
}

String::~String()
{
	if (m_charArray)
	{
		delete[] m_charArray;
		m_charArray = 0;
	}
}

const unsigned int String::getLenght() const
{
	if(m_charArray)
	return static_cast<unsigned int>(strlen(m_charArray));
	return -1;
}

String String::toUpper() const
{
	char newArray[255];
	for(unsigned int i=0;i<m_length;i++)
	{
		if((m_charArray[i]>='a' && m_charArray[i] <= 'z')||(m_charArray[i] >= 'á' && m_charArray[i] <= 'ü'))
		{
			newArray[i] = m_charArray[i] - 32;
		}
		else
		{
			newArray[i] = m_charArray[i];
		}
	}
	return String(newArray);
}

void String::RemoveAccents()
{
	char accented[] = { 'á', 'é', 'í', 'ó', 'ö', 'õ', 'ú', 'ü', 'û',
		'Á', 'É', 'Í', 'Ó', 'Ö', 'Õ', 'Ú', 'Ü', 'Û' };

	char mask[] = {'a', 'e', 'i', 'o', 'o', 'o', 'u', 'u', 'u',
		'A', 'E', 'I', 'O', 'O', 'O', 'U', 'U', 'U' };

	for(unsigned int i=0;i<m_length;i++)
	{
		for(int j=0;j<18;j++)
		{
			if(accented[j]==m_charArray[i])
			{
				m_charArray[i] = mask[j];
			}
		}
	}
}

const char* String::c_str()const
{
	return m_charArray;
}

bool String::isAcceptedCharacter(const char input)
{
	return (input >= 'A' && input <= 'Z') || input=='\0';
}

String String::getAcceptableString()const
{
	int numCharsToRemove = 0;
	for(unsigned int i=0;i<m_length;i++)
	{
		if(!isAcceptedCharacter(m_charArray[i]))
		{
			numCharsToRemove++;
		}
	}
	char newString[255];
	short index = 0;
	for (unsigned int i = 0; i < m_length; i++)
	{
		if (isAcceptedCharacter(m_charArray[i]))
		{
			newString[index] = m_charArray[i]; 
			index++;
		}
	}

	return String(newString);
}

char& String::operator[](int x)
{
	return m_charArray[x];
}

String& String::operator=(const String& str)
{
	if (this != &str)
	{
		m_length = str.getLenght()+1;
		if (m_length > 0)
		{
			delete[] m_charArray;
			m_charArray = new char[this->m_length];
			strcpy_s(m_charArray, (m_length) * sizeof(char), str.c_str());
		}
	}

	return *this;
}

void String::removeAll(const char c)
{
	char temp[255];
	int counter = 0;
	for(int i=0;i<strlen(m_charArray);i++)
	{
		if(m_charArray[i]!=c)
		{
			temp[counter] = m_charArray[i];
			counter++;
		}
	}
	if (temp[counter] != '\0')
		temp[counter] = '\0';
	if (m_charArray)
	{
		delete[] m_charArray;
	}
	m_charArray=new char[counter+1];
	strcpy_s(m_charArray, (counter + 1) * sizeof(char), temp);
	m_length = static_cast<unsigned int>(strlen(m_charArray))+1;
}

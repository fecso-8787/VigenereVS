#pragma once
#include <cstring>

class String
{
public:
	String();
	String(const String& input);
	String(const char* input);
	~String();
	const unsigned int getLenght() const;
	String toUpper()const;
	void RemoveAccents();
	const char* c_str()const;
	String getAcceptableString() const;
	char& operator[] (int x);
	String& operator=(const String& str);
	void removeAll(const char c);
private:
	char* m_charArray;
	unsigned int m_length;
	static bool isAcceptedCharacter(const char input);

};
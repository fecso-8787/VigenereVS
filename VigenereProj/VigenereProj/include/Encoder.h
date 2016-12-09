#pragma once
#include "StringHelper.h"
#include <stdio.h>
#define MAX_LINE_LEN 255

class Encoder
{
public:
	Encoder(String fileName);
	~Encoder();
	void setKey(String key);
	String getEncodedString(const String& toEncode);
	void Init();
private:
	String m_key;
	String* m_table;
	String m_inputFilePath;
	int getColumnNumberByChar(const char& input) const;
	int getRowNumberByChar(const char& input) const;
};
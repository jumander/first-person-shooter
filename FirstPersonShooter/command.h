


#pragma once



class command
{
public:
	int console(std::string scommand);
	int draw(char strline[], int State);
private:
	void write(float x, float y, float z, char *string, int size);
	
};


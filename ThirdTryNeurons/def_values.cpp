#include "def_values.h"

std::string get_string(char x)
{
	// string class has a constructor 
	// that allows us to specify size of 
	// string as first parameter and character 
	// to be filled in given size as second 
	// parameter. 
	std::string s(1, x);

	return s;
}
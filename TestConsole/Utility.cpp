#include "stdafx.h"
#include "Utility.h"


Utility::Utility()
{
}


Utility::~Utility()
{
}

bool Utility::isInRange(const int max, const int min, const int number)
{
	return (max >= number && min <= number);
}

void Utility::toLowerCase(char* str)
{
	const int DIFF = 32;
	int offset = 0;
	while (*(str+offset) != '\0') {
		if (*(str+offset) <= 90 && *(str+offset) >= 65)
			*(str + offset) += DIFF;
		offset++;
	}
	return;
}

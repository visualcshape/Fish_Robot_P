#ifndef _UTILITY_H_
#define _UTILITY_H_

class Utility
{
protected:
	Utility();
	~Utility();
public:
	static bool isInRange(const int max, const int min, const int number);

	static void toLowerCase(char* str);
};

#endif


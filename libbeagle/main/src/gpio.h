#ifndef _GPIO_H
#define _GPIO_H

#include <string>

using namespace std;

class GPIO {
private:
	bool existed;
	unsigned number;
	string path;

public:
	GPIO();
	GPIO(unsigned number);
	~GPIO();

	void direction(string direction);

	void value(string value);
	void value(unsigned value);

	string *value(string *value);
	unsigned value();

	void dump();
};

#endif

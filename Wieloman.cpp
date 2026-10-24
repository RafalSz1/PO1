#include <iostream>

struct Wielomian
{
	double* wsp;
	unsigned int stopien;
};

Wielomian analizujWielomian(const char* str);
unsigned int rozpoznajStopien(const char* str);
Wielomian alokujPamiec(unsigned int s);
Wielomian analizujJednomiany(const char* str, Wielomian* w);
const char* analizujJednomian(const char* str, Wielomian* w);

int main()
{
	Wielomian w = analizujWielomian("x^2-2x+5");
	w.Pokaz();

	return 0;
}

unsigned int rozpoznajStopien(const char* str)
{
	unsigned int maxStopien = 0;
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == 'x' || str[i] == 'X')
		{
			long st = 1;
			if (str[i + 1] == '^')
			{
				char* endPtr = NULL;
				st = strtol(&str[i + 2], &endPtr, 10); // &str[i + 2] == str + i + 2
			}
			if (st > maxStopien) maxStopien = (unsigned int) st;
		}
		i++;
	}
	return maxStopien;
}
Wielomian alokujPamiec(unsigned int s)
{
	Wielomian w;
	w.stopien = s;
	w.wsp = new double[s + 1]; // (double*) malloc((s + 1) * sizeof(double));
	return w;
}
const char* analizujJednomian(const char* str, Wielomian* w)
{
	short int znak = 1;
	double liczbaR = 0;
	int liczbaC = 0;

	if (*str == '-')
	{
		znak = -1;
		str++;
	}
	else if (*str == '+') str++;

	if (*str == 'x' || *str == 'X') liczbaR = 1;
	else liczbaR = strtod(str, (char**) &str);

	if (*str != 'x' && *str != 'X') liczbaC = 0;
	else
	{
		str++;
		if (*str == '^') liczbaC = strtol(str, (char**)&str, 10);
		else liczbaC = 1;
	}

	w->wsp[liczbaC] += znak * liczbaR;
	return str;
}
Wielomian analizujJednomiany(const char* str, Wielomian* w)
{
	while (*str != '\0') // '\0' == 0
		str = analizujJednomian(str, w);
}
Wielomian analizujWielomian(const char* str)
{
	unsigned int s = rozpoznajStopien(str);
	Wielomian w = alokujPamiec(s);

	analizujJednomiany(str, &w);

	return w;
}
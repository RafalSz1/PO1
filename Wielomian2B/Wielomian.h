#ifndef WIELOMIAN_H
#define WIELOMIAN_H

#include <iostream>

using namespace std;

struct WynikDzielenia;

class BazaWielomianu {
protected:
    unsigned int stopien;
public:
    BazaWielomianu() : stopien(0) {}
    BazaWielomianu(unsigned int st) : stopien(st) {}
    virtual ~BazaWielomianu() {}

    unsigned int GetStopien() const { return stopien; }

    virtual double& operator[](unsigned int i) = 0;
    virtual const double operator[](unsigned int i) const = 0;

    double operator()(double x) const;
    void Pokaz() const;
};

class Wielomian : public BazaWielomianu {
    double* wspolczynnik;
public:
    Wielomian();
    Wielomian(int st);
    Wielomian(int st, double* wsp);
    Wielomian(double* wsp, unsigned int liczba);
    Wielomian(const char* napis);
    Wielomian(const Wielomian& w);
    Wielomian(const BazaWielomianu& w);
    virtual ~Wielomian();

    Wielomian& operator=(const Wielomian& w);
    Wielomian& operator=(const BazaWielomianu& w);
    Wielomian& operator+=(const BazaWielomianu& w);
    Wielomian& operator-=(const BazaWielomianu& w);
    WynikDzielenia operator/=(const BazaWielomianu& w);
    Wielomian& operator*=(const BazaWielomianu& w);
    Wielomian& operator%=(const BazaWielomianu& w);

    Wielomian& operator+=(double c);
    Wielomian& operator-=(double c);
    Wielomian& operator*=(double c);
    Wielomian& operator/=(double c);

    double& operator[](unsigned int i) override;
    double const operator[](unsigned int i) const override;

    double GetWspolczynnik(unsigned int i) const {
        if (i <= stopien) {
            return wspolczynnik[i];
        }
        return 0.0;
    }
    void SetWspolczynnik(unsigned int i, double wartosc) {
        if (i <= stopien) {
            wspolczynnik[i] = wartosc;
        }
    }
    void SetStopien(unsigned int st);

    const char* PominOdstepy(const char* napis);
    unsigned int OkreslStopien(const char* napis);
    const char* AnalizujJednomian(const char* napis);
    void AnalizujJednomiany(const char* napis);
    Wielomian Pochodna(int ktora = 1);
};

class Jednomian : public BazaWielomianu {
    double wspolczynnik;
public:
    Jednomian();
    Jednomian(unsigned int st, double wsp);
    Jednomian(const Jednomian& j);
    
    double& operator[](unsigned int i) override;
    double const operator[](unsigned int i) const override;
    
    Jednomian& operator=(const Jednomian& j);
    Jednomian& operator*=(const Jednomian& j);
    Jednomian& operator*=(double c);
    Jednomian& operator/=(double c);
    
    Jednomian Pochodna(int ktora = 1) const;
};

struct WynikDzielenia {
    Wielomian iloraz;
    Wielomian reszta;
};

double* PrzydzielPamiec(int stopien);

Jednomian operator*(const Jednomian& j1, const Jednomian& j2);
Jednomian operator*(const Jednomian& j, double c);
Jednomian operator*(double c, const Jednomian& j);
Jednomian operator/(const Jednomian& j, double c);

Wielomian operator*(const BazaWielomianu& w1, const BazaWielomianu& w2);
WynikDzielenia operator/(const BazaWielomianu& w1, const BazaWielomianu& w2);
Wielomian operator+(const BazaWielomianu& w1, const BazaWielomianu& w2);
Wielomian operator-(const BazaWielomianu& w1, const BazaWielomianu& w2);
Wielomian operator%(const BazaWielomianu& w1, const BazaWielomianu& w2);

Wielomian operator*(const BazaWielomianu& w, double c);
Wielomian operator*(double c, const BazaWielomianu& w);
Wielomian operator+(const BazaWielomianu& w, double c);
Wielomian operator+(double c, const BazaWielomianu& w);
Wielomian operator-(const BazaWielomianu& w, double c);
Wielomian operator-(double c, const BazaWielomianu& w);
Wielomian operator/(const BazaWielomianu& w, double c);

ostream& operator<<(ostream& os, const BazaWielomianu& w);
istream& operator>>(istream& is, Wielomian& w);

#endif

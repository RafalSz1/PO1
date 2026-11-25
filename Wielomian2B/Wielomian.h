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
    virtual ~BazaWielomianu() {}

    unsigned int GetStopien() const { return stopien; }

    virtual double& operator[](unsigned int i);
    virtual const double operator[](unsigned int i) const;


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

    Wielomian& operator=(const BazaWielomianu&);
    Wielomian& operator+=(const BazaWielomianu&);
    Wielomian& operator-=(const BazaWielomianu&);
    WynikDzielenia operator/=(const BazaWielomianu&);
    Wielomian& operator*=(const BazaWielomianu&);
    Wielomian& operator%=(const BazaWielomianu&);

    Wielomian& operator+=(double c);
    Wielomian& operator-=(double c);
    Wielomian& operator*=(double c);
    Wielomian& operator/=(double c);

    double& operator[](unsigned int i);
    const double operator[](unsigned int i) const;

    unsigned int GetStopien() const {
        return stopien;
    }
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
    void SetStopien(unsigned int st) {
        if (st == stopien) return;

        double* nowy_wsp = new double[st + 1];
        for (unsigned int i = 0; i <= st; i++) {
            nowy_wsp[i] = (i <= stopien) ? wspolczynnik[i] : 0.0;
        }

        delete[] wspolczynnik;
        wspolczynnik = nowy_wsp;
        stopien = st;
    }
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
    Jednomian(int st, double wsp);
};

struct WynikDzielenia {
    Wielomian iloraz;
    Wielomian reszta;
};

double* PrzydzielPamiec(int stopien);

Wielomian operator*(const BazaWielomianu& w1, const BazaWielomianu& w2);
WynikDzielenia operator/(const BazaWielomianu& w1, const BazaWielomianu& w2);
Wielomian operator+(const BazaWielomianu& w1, const BazaWielomianu& w2);
Wielomian operator-(const BazaWielomianu& w1, const BazaWielomianu& w2);

Wielomian operator*(const BazaWielomianu& w, double c);
Wielomian operator*(double c, const BazaWielomianu& w);
Wielomian operator+(const BazaWielomianu& w, double c);
Wielomian operator+(double c, const BazaWielomianu& w);
Wielomian operator-(const BazaWielomianu& w, double c);
Wielomian operator-(double c, const BazaWielomianu& w);
Wielomian operator/(const BazaWielomianu& w, double c);
Wielomian operator%(const BazaWielomianu& w1, const BazaWielomianu& w2);

ostream& operator<<(ostream& os, const BazaWielomianu& w);
istream& operator>>(istream& is, BazaWielomianu& w);

#endif

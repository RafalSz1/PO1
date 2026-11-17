#ifndef WIELOMIANY_H
#define WIELOMIANY_H

#include <iostream>

using namespace std;

struct WynikDzielenia;

class Wielomian {
    double* wspolczynnik;
    unsigned int stopien;
public:
    Wielomian();
    Wielomian(int st, double* wsp);
    Wielomian(double* wsp, unsigned int liczba);
    Wielomian(const char* napis);
    Wielomian(const Wielomian& w);
    ~Wielomian();
    
    Wielomian& operator=(const Wielomian& w);
    Wielomian& operator+=(const Wielomian&);
    Wielomian& operator-=(const Wielomian&);
    WynikDzielenia operator/=(const Wielomian&);
    Wielomian& operator*=(const Wielomian& w);

    Wielomian& operator+=(double c);
    Wielomian& operator-=(double c);
    Wielomian& operator*=(double c);
    Wielomian& operator/=(double c);

    double operator()(double x);
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
    void Pokaz() const;
};

struct WynikDzielenia {
    Wielomian iloraz;
    Wielomian reszta;
};

double* PrzydzielPamiec(int stopien);

Wielomian operator*(const Wielomian& w1, const Wielomian& w2);
WynikDzielenia operator/(const Wielomian& w1, const Wielomian& w2);
Wielomian operator+(const Wielomian& w1, const Wielomian& w2);
Wielomian operator-(const Wielomian& w1, const Wielomian& w2);

Wielomian operator*(const Wielomian& w, double c);
Wielomian operator*(double c, const Wielomian& w);
Wielomian operator+(const Wielomian& w, double c);
Wielomian operator+(double c, const Wielomian& w);
Wielomian operator-(const Wielomian& w, double c);
Wielomian operator-(double c, const Wielomian& w);
Wielomian operator/(const Wielomian& w, double c);

ostream& operator<<(ostream& os, const Wielomian& w);
istream& operator>>(istream& is, Wielomian& w);

#endif

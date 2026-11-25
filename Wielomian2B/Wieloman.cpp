#include "Wielomian.h"
#include <cstring>
#include <cstdlib>

Wielomian::Wielomian() : BazaWielomianu(0) {
    wspolczynnik = new double[1];
    wspolczynnik[0] = 0.0;
}

Wielomian::Wielomian(int st) : BazaWielomianu(st) {
    wspolczynnik = new double[stopien + 1];
    for (unsigned int i = 0; i <= stopien; i++)
        wspolczynnik[i] = 0.0;
}

Wielomian::Wielomian(int st, double* wsp) : BazaWielomianu(st) {
    wspolczynnik = new double[stopien + 1];
    for (unsigned int i = 0; i <= stopien; i++)
        wspolczynnik[i] = (wsp != 0) ? wsp[i] : 0.0;
}
Wielomian::Wielomian(double* wsp, unsigned int liczba) {
    if (liczba == 0) {
        stopien = 0;
        wspolczynnik = new double[1];
        wspolczynnik[0] = 0.0;
    }
    else {
        stopien = liczba - 1;
        wspolczynnik = new double[stopien + 1];
        for (unsigned int i = 0; i <= stopien; i++)
            wspolczynnik[i] = (wsp != nullptr) ? wsp[i] : 0.0;
    }
}

Wielomian::Wielomian(const char* napis) {
    //Analizuj(napis);
    stopien = OkreslStopien(napis);
    wspolczynnik = new double[stopien + 1];
    for (unsigned int i = 0; i <= stopien; i++)
        wspolczynnik[i] = 0.0;
    AnalizujJednomiany(napis);
}

Wielomian::Wielomian(const Wielomian& w) : BazaWielomianu(w.stopien) {
    wspolczynnik = new double[stopien + 1];
    for (unsigned int i = 0; i <= stopien; i++)
        wspolczynnik[i] = w.wspolczynnik[i];
}

Wielomian::Wielomian(const BazaWielomianu& w) : BazaWielomianu(w.GetStopien()) {
    wspolczynnik = new double[stopien + 1];
    for (unsigned int i = 0; i <= stopien; i++)
        wspolczynnik[i] = w[i];
}

Wielomian::~Wielomian() {
    delete[] wspolczynnik;
}

void Wielomian::SetStopien(unsigned int st) {
    if (st == stopien) return;
    double* nowy_wsp = new double[st + 1];
    for (unsigned int i = 0; i <= st; i++) {
        nowy_wsp[i] = (i <= stopien) ? wspolczynnik[i] : 0.0;
    }
    delete[] wspolczynnik;
    wspolczynnik = nowy_wsp;
    stopien = st;
}


double& Wielomian::operator[](unsigned int i) {
    if (i > stopien) SetStopien(i);
    return wspolczynnik[i];
}

const double Wielomian::operator[](unsigned int i) const {
    if (i <= stopien) return wspolczynnik[i];
    return 0.0;
}

Wielomian& Wielomian::operator=(const Wielomian& w) {
    if (this == &w) return *this;

    delete[] wspolczynnik;
    stopien = w.stopien;
    wspolczynnik = new double[stopien + 1];
    for (unsigned int i = 0; i <= stopien; i++)
        wspolczynnik[i] = w.wspolczynnik[i];
    return *this;
}

Wielomian& Wielomian::operator=(const BazaWielomianu& w) {
    if (this == &w) return *this;

    delete[] wspolczynnik;
    stopien = w.GetStopien();
    wspolczynnik = new double[stopien + 1];
    for (unsigned int i = 0; i <= stopien; i++)
        wspolczynnik[i] = w[i];
    return *this;
}

Wielomian& Wielomian::operator+=(const BazaWielomianu& w2) {
    unsigned int st2 = w2.GetStopien();
    if (stopien < st2) {
        SetStopien(st2);
    }

    for (unsigned int i = 0; i <= st2; i++)
        wspolczynnik[i] += w2[i];

    return *this;
}

Wielomian& Wielomian::operator-=(const BazaWielomianu& w2) {
    unsigned int st2 = w2.GetStopien();
    if (stopien < st2) {
        SetStopien(st2);
    }

    for (unsigned int i = 0; i <= st2; i++)
        wspolczynnik[i] -= w2[i];

    return *this;
}

Wielomian& Wielomian::operator*=(const BazaWielomianu& w) {
    unsigned int st2 = w.GetStopien();
    unsigned int nowy_stopien = stopien + st2;
    double* nowe_wsp = new double[nowy_stopien + 1];
    for (unsigned int i = 0; i <= nowy_stopien; i++) {
        nowe_wsp[i] = 0.0;
    }

    for (unsigned int i = 0; i <= stopien; i++) {
        for (unsigned int j = 0; j <= st2; j++) {
            nowe_wsp[i + j] += wspolczynnik[i] * w[j];
        }
    }

    delete[] wspolczynnik;
    stopien = nowy_stopien;
    wspolczynnik = nowe_wsp;
    return *this;
}

Wielomian operator*(const BazaWielomianu& w1, const BazaWielomianu& w2) {
    Wielomian wynik(w1);
    wynik *= w2;
    return wynik;
}

Wielomian& Wielomian::operator*=(double c) {
    for (unsigned int i = 0; i <= stopien; i++)
        wspolczynnik[i] *= c;
    return *this;
}

Wielomian operator*(const BazaWielomianu& w, double c) {
    Wielomian wynik(w);
    wynik *= c;
    return wynik;
}

Wielomian operator*(double c, const BazaWielomianu& w) {
    return w * c;
}

WynikDzielenia Wielomian::operator/=(const BazaWielomianu& w2) {
    WynikDzielenia wynik;
    unsigned int st2 = w2.GetStopien();

    if (st2 == 0 && w2[0] == 0.0) {
        wynik.iloraz = *this;
        wynik.reszta = Wielomian();
        return wynik;
    }

    if (stopien < st2) {
        wynik.iloraz = Wielomian();
        wynik.reszta = *this;
        return wynik;
    }

    unsigned int wynik_stopien = stopien - st2;
    double* wynik_wsp = new double[wynik_stopien + 1];
    for (unsigned int i = 0; i <= wynik_stopien; i++)
        wynik_wsp[i] = 0.0;

    Wielomian reszta = *this;

    while (reszta.stopien >= st2 && !(reszta.stopien == 0 && reszta.wspolczynnik[0] == 0.0)) {
        unsigned int diff_stopien = reszta.stopien - st2;
        double wsp_ilorazu = reszta.wspolczynnik[reszta.stopien] / w2[st2];

        wynik_wsp[diff_stopien] = wsp_ilorazu;

        Jednomian jednomian(diff_stopien, wsp_ilorazu);
        reszta -= (w2 * jednomian);

        unsigned int nowy_stopien_reszty = reszta.stopien;
        while (nowy_stopien_reszty > 0 && reszta.wspolczynnik[nowy_stopien_reszty] == 0.0) {
            nowy_stopien_reszty--;
        }
        if (nowy_stopien_reszty != reszta.stopien) {
            reszta.SetStopien(nowy_stopien_reszty);
        }

        if (reszta.stopien == 0 && reszta.wspolczynnik[0] == 0.0) {
            break;
        }
    }

    delete[] wspolczynnik;
    stopien = wynik_stopien;
    wspolczynnik = wynik_wsp;

    wynik.iloraz = *this;
    wynik.reszta = reszta;

    return wynik;
}

Wielomian& Wielomian::operator/=(double c) {
    if (c != 0.0) {
        for (unsigned int i = 0; i <= stopien; i++)
            wspolczynnik[i] /= c;
    }
    return *this;
}

WynikDzielenia operator/(const BazaWielomianu& w1, const BazaWielomianu& w2) {
    Wielomian temp(w1);
    return (temp /= w2);
}

Wielomian operator/(const BazaWielomianu& w, double c) {
    Wielomian wynik(w);
    wynik /= c;
    return wynik;

}
Wielomian& Wielomian::operator%=(const BazaWielomianu& w2) {
    *this = ((*this) /= w2).reszta;
    return *this;
}

Wielomian operator%(const BazaWielomianu& w1, const BazaWielomianu& w2) {
    Wielomian temp(w1);
    WynikDzielenia wd = (temp /= w2);
    return wd.reszta;
}
Wielomian operator+(const BazaWielomianu& w1, const BazaWielomianu& w2) {
    Wielomian suma(w1);
    suma += w2;
    return suma;
}

Wielomian operator-(const BazaWielomianu& w1, const BazaWielomianu& w2) {
    Wielomian roznica(w1);
    roznica -= w2;
    return roznica;
}

Wielomian& Wielomian::operator+=(double c) {
    wspolczynnik[0] += c;
    return *this;
}

Wielomian& Wielomian::operator-=(double c) {
    wspolczynnik[0] -= c;
    return *this;
}

Wielomian operator+(const BazaWielomianu& w, double c) {
    Wielomian suma(w);
    suma += c;
    return suma;
}

Wielomian operator+(double c, const BazaWielomianu& w) {
    return w + c;
}

Wielomian operator-(const BazaWielomianu& w, double c) {
    Wielomian roznica(w);
    roznica -= c;
    return roznica;
}

Wielomian operator-(double c, const BazaWielomianu& w) {
    Wielomian wynik(w.GetStopien());
    wynik[0] = c - w[0];
    for (unsigned int i = 1; i <= w.GetStopien(); i++)
        wynik[i] = -w[i];
    return wynik;
}

ostream& operator<<(ostream& os, const BazaWielomianu& w) {
    w.Pokaz();
    return os;
}

istream& operator>>(istream& is, Wielomian& w) {
    char bufor[1024];

    is.getline(bufor, sizeof(bufor));

    if (strlen(bufor) > 0)
        w = Wielomian(bufor);
    return is;
}

// char* UsunOdstepy(const char* napis) {
//     char* napis2;
//     int y = 0, dlugosc = strlen(napis);
//     napis2 = new char [dlugosc + 1];
//     for (int i = 0; i < dlugosc; i++)
//         if (napis[i] != ' ') 
//             napis2[y++] = napis[i];
//     napis2[y] = 0;
//     return napis2;
// }

Wielomian Wielomian::Pochodna(int ktora) {
    if (ktora <= 0) return *this;

    if (stopien == 0 || ktora > stopien)
        return Wielomian();
    if (ktora > 1)
        return Pochodna().Pochodna(ktora-1);
    Wielomian wynik(stopien-1);
    for (int i = stopien; i > 0; i--)
        wynik.wspolczynnik[i-1] = wspolczynnik[i] * i;
    return wynik;
}

const char* Wielomian::PominOdstepy(const char* napis) {
    while (*napis == ' ')
        napis++;
    return napis;
}

unsigned int Wielomian::OkreslStopien(const char* napis) {
    unsigned int maksStopien = 0;
    unsigned int stopien = 0;
    int i = 0;
    while (napis[i]) {
        napis = PominOdstepy(napis);
        if (napis[i] == 'x') {
            if (napis[i + 1] == '^') {
                char* koniecNapisu;
                stopien = strtol(&napis[i + 2], &koniecNapisu, 10);
                i = koniecNapisu - napis;
            }
            else {
                stopien = 1;
                i++;
            }
            if (stopien > maksStopien)
                maksStopien = stopien;
        }
        else i++;
    }
    return maksStopien;
}
double* PrzydzielPamiec(int stopien) {
    double* tab = new double[stopien + 1];
    for (int i = 0; i <= stopien; i++)
        tab[i] = 0.0f;
    return tab;
}

const char* Wielomian::AnalizujJednomian(const char* napis) {
    napis = PominOdstepy(napis);
    if (*napis == '\0') return napis;

    int wykladnik = 0;
    int znak = 1;
    double wspolczynnik = 1.0;

    if (*napis == '-') {
        napis++;
        znak = -1;
    }
    else if (*napis == '+')
        napis++;

    napis = PominOdstepy(napis);

    if (*napis != 'x' && *napis != '\0') {
        char* koniec;
        wspolczynnik = strtod(napis, &koniec);
        napis = koniec;
    }

    napis = PominOdstepy(napis);

    if (*napis == 'x') {
        napis++;
        napis = PominOdstepy(napis);
        if (*napis == '^') {
            napis++;
            napis = PominOdstepy(napis);
            char* koniecNapisu;
            wykladnik = strtol(napis, &koniecNapisu, 10);
            napis = koniecNapisu;
        }
        else
            wykladnik = 1;
    }
    else
        wykladnik = 0;

    SetWspolczynnik(wykladnik, znak * wspolczynnik);

    return napis;

}

void Wielomian::AnalizujJednomiany(const char* napis) {
    while (*napis) {
        napis = PominOdstepy(napis);
        if (*napis == '\0') break;
        napis = AnalizujJednomian(napis);
    }
}

//Wielomian Analizuj(const char* napis) {
//    Wielomian w;
//    w.SetStopien(OkreslStopien(napis));
//    for (unsigned int i = 0; i <= w.GetStopien(); i++) {
//        w.SetWspolczynnik(i, 0.0);
//    }
//    AnalizujJednomiany(napis, &w);
//
//    return w;
//}

double BazaWielomianu::operator()(double x) const {
    if (stopien == 0) return (*this)[0];

    double wynik = (*this)[stopien];
    for (unsigned int i = stopien; i > 0; --i)
        wynik = wynik * x + (*this)[i - 1];
    return wynik;
}

void BazaWielomianu::Pokaz() const {
    bool pierwszy = true;
    bool wszystkieZerowe = true;

    for (int i = stopien; i >= 0; i--) {
        if ((*this)[i] != 0.0) {
            wszystkieZerowe = false;
            break;
        }
    }

    if (wszystkieZerowe) {
        cout << "0\n";
        return;
    }

    for (int i = stopien; i >= 0; i--) {
        double wsp = (*this)[i];

        if (wsp == 0.0) {
            continue;
        }

        if (pierwszy) {
            if (wsp < 0) {
                cout << "-";
            }
        }
        else {
            if (wsp < 0) {
                cout << " - ";
            }
            else {
                cout << " + ";
            }
        }

        double absWsp = wsp;
        if (absWsp < 0)
            absWsp = -absWsp;

        if (i == 0)
            cout << absWsp;
        else {
            if (absWsp != 1.0)
                cout << absWsp;
            cout << "x";
            if (i > 1)
                cout << "^" << i;
        }

        pierwszy = false;
    }
    cout << endl;
}

Jednomian::Jednomian() : BazaWielomianu(0), wspolczynnik(0.0) {}

Jednomian::Jednomian(unsigned int st, double wsp) : BazaWielomianu(st), wspolczynnik(wsp) {}

Jednomian::Jednomian(const Jednomian& j) : BazaWielomianu(j.stopien), wspolczynnik(j.wspolczynnik) {}

double& Jednomian::operator[](unsigned int i) {
    if (i == stopien) {
        return wspolczynnik;
    }
    if (wspolczynnik == 0.0) {
        stopien = i;
        return wspolczynnik;
    }
    static double zero = 0.0;
    zero = 0.0;
    return zero;
}
double const Jednomian::operator[](unsigned int i) const {
    return (i == stopien) ? wspolczynnik : 0.0;
}

Jednomian& Jednomian::operator=(const Jednomian& j) {
    if (this != &j) {
        stopien = j.stopien;
        wspolczynnik = j.wspolczynnik;
    }
    return *this;
}

Jednomian& Jednomian::operator*=(const Jednomian& j) {
    stopien += j.stopien;
    wspolczynnik *= j.wspolczynnik;
    return *this;
}

Jednomian& Jednomian::operator*=(double c) {
    wspolczynnik *= c;
    return *this;
}

Jednomian& Jednomian::operator/=(double c) {
    if (c != 0.0) {
        wspolczynnik /= c;
    }
    return *this;
}

Jednomian Jednomian::Pochodna(int ktora) const {
    if (ktora <= 0) return *this;
    if (stopien == 0 || ktora > stopien)
        return Jednomian();
    if (ktora > 1)
        return Pochodna(1).Pochodna(ktora - 1);

    return Jednomian(stopien - 1, wspolczynnik * stopien);
}

Jednomian operator*(const Jednomian& j1, const Jednomian& j2) {
    Jednomian wynik(j1);
    wynik *= j2;
    return wynik;
}

Jednomian operator*(const Jednomian& j, double c) {
    Jednomian wynik(j);
    wynik *= c;
    return wynik;
}

Jednomian operator*(double c, const Jednomian& j) {
    return j * c;
}

Jednomian operator/(const Jednomian& j, double c) {
    Jednomian wynik(j);
    wynik /= c;
    return wynik;
}

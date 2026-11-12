#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

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
    struct WynikDzielenia operator/=(const Wielomian&);
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

Wielomian::Wielomian() {
    stopien = 0;
    wspolczynnik = new double[1];
    wspolczynnik[0] = 0.0;
}

Wielomian::Wielomian(int st, double* wsp) {
    stopien = st;
    wspolczynnik = new double[stopien + 1];
    for (unsigned int i = 0; i <= stopien; i++) {
        wspolczynnik[i] = (wsp != 0) ? wsp[i] : 0.0;
    }
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
        for (unsigned int i = 0; i <= stopien; i++) {
            wspolczynnik[i] = (wsp != nullptr) ? wsp[i] : 0.0;
        }
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

Wielomian::Wielomian(const Wielomian& w) {
    stopien = w.stopien;
    wspolczynnik = new double[stopien + 1];
    for (unsigned int i = 0; i <= stopien; i++) {
        wspolczynnik[i] = w.wspolczynnik[i];
    }
}

Wielomian::~Wielomian() {
    delete[] wspolczynnik;
}

double Wielomian::operator()(double x) {
    if (stopien == 0) return wspolczynnik[0];

    double wynik = wspolczynnik[stopien];
    for (unsigned int i = stopien; i > 0; --i) {
        wynik = wynik * x + wspolczynnik[i - 1];
    }
    return wynik;
}

double& Wielomian::operator[](unsigned int i) {
    if (i > stopien) {
        SetStopien(i);
    }
    return wspolczynnik[i];
}

const double Wielomian::operator[](unsigned int i) const {
    if (i <= stopien && i >= 0) return wspolczynnik[i];
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
Wielomian& Wielomian::operator+=(const Wielomian& w2) {
    if (stopien < w2.stopien) {
        double* nowy_wsp = new double[w2.stopien + 1];

        for (unsigned int i = 0; i <= stopien; i++)
            nowy_wsp[i] = wspolczynnik[i];

        for (unsigned int i = stopien + 1; i <= w2.stopien; i++)
            nowy_wsp[i] = 0;

        delete[] wspolczynnik;
        wspolczynnik = nowy_wsp;
        stopien = w2.stopien;
    }

    for (unsigned int i = 0; i <= w2.stopien; i++)
        wspolczynnik[i] += w2.wspolczynnik[i];

    return *this;
}

Wielomian& Wielomian::operator-=(const Wielomian& w2) {
    if (stopien < w2.stopien) {
        double* nowy_wsp = new double[w2.stopien + 1];

        for (unsigned int i = 0; i <= stopien; i++)
            nowy_wsp[i] = wspolczynnik[i];

        for (unsigned int i = stopien + 1; i <= w2.stopien; i++)
            nowy_wsp[i] = 0;

        delete[] wspolczynnik;
        wspolczynnik = nowy_wsp;
        stopien = w2.stopien;
    }

    for (unsigned int i = 0; i <= w2.stopien; i++)
        wspolczynnik[i] -= w2.wspolczynnik[i];

    return *this;
}

Wielomian& Wielomian::operator*=(const Wielomian& w) {
    unsigned int nowy_stopien = stopien + w.stopien;
    double* nowe_wsp = new double[nowy_stopien + 1];
    for (unsigned int i = 0; i <= nowy_stopien; i++) {
        nowe_wsp[i] = 0.0;
    }

    for (unsigned int i = 0; i <= stopien; i++) {
        for (unsigned int j = 0; j <= w.stopien; j++) {
            nowe_wsp[i + j] += wspolczynnik[i] * w.wspolczynnik[j];
        }
    }

    delete[] wspolczynnik;
    stopien = nowy_stopien;
    wspolczynnik = nowe_wsp;
    return *this;
}

Wielomian operator*(const Wielomian& w1, const Wielomian& w2) {
    Wielomian wynik(w1);
    wynik *= w2;
    return wynik;
}

Wielomian& Wielomian::operator*=(double c) {
    for (unsigned int i = 0; i <= stopien; i++) {
        wspolczynnik[i] *= c;
    }
    return *this;
}

Wielomian operator*(const Wielomian& w, double c) {
    Wielomian wynik(w);
    wynik *= c;
    return wynik;
}

Wielomian operator*(double c, const Wielomian& w) {
    return w * c;
}

WynikDzielenia Wielomian::operator/=(const Wielomian& w2) {
    WynikDzielenia wynik;

    if (w2.stopien == 0 && w2.wspolczynnik[0] == 0.0) {
        wynik.iloraz = *this;
        wynik.reszta = Wielomian();
        return wynik;
    }

    if (stopien < w2.stopien) {
        wynik.iloraz = Wielomian();
        wynik.reszta = *this;
        return wynik;
    }

    unsigned int wynik_stopien = stopien - w2.stopien;
    double* wynik_wsp = new double[wynik_stopien + 1];
    for (unsigned int i = 0; i <= wynik_stopien; i++) {
        wynik_wsp[i] = 0.0;
    }

    Wielomian reszta = *this;

    while (reszta.stopien >= w2.stopien && !(reszta.stopien == 0 && reszta.wspolczynnik[0] == 0.0)) {
        unsigned int diff_stopien = reszta.stopien - w2.stopien;
        double wsp_ilorazu = reszta.wspolczynnik[reszta.stopien] / w2.wspolczynnik[w2.stopien];

        wynik_wsp[diff_stopien] = wsp_ilorazu;

        double* wsp_jedn = new double[diff_stopien + 1];
        for (unsigned int k = 0; k <= diff_stopien; k++) wsp_jedn[k] = 0.0;
        wsp_jedn[diff_stopien] = wsp_ilorazu;

        Wielomian jednomian(diff_stopien, wsp_jedn);
        delete[] wsp_jedn;

        Wielomian w2_kopia = w2;
        reszta -= (w2_kopia * jednomian);

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
        for (unsigned int i = 0; i <= stopien; i++) {
            wspolczynnik[i] /= c;
        }
    }
    return *this;
}

WynikDzielenia operator/(const Wielomian& w1, const Wielomian& w2) {
    Wielomian temp(w1);
    return (temp /= w2);
}

Wielomian operator/(const Wielomian& w, double c) {
    Wielomian wynik(w);
    wynik /= c;
    return wynik;
}

Wielomian operator+(const Wielomian& w1, const Wielomian& w2) {
    Wielomian suma(w1);
    suma += w2;
    return suma;
}

Wielomian operator-(const Wielomian& w1, const Wielomian& w2) {
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

Wielomian operator+(const Wielomian& w, double c) {
    Wielomian suma(w);
    suma += c;
    return suma;
}

Wielomian operator+(double c, const Wielomian& w) {
    return w + c;
}

Wielomian operator-(const Wielomian& w, double c) {
    Wielomian roznica(w);
    roznica -= c;
    return roznica;
}

Wielomian operator-(double c, const Wielomian& w) {
    Wielomian wynik;
    wynik.SetStopien(w.GetStopien());
    wynik.SetWspolczynnik(0, c - w.GetWspolczynnik(0));
    for (unsigned int i = 1; i <= w.GetStopien(); i++) {
        wynik.SetWspolczynnik(i, -w.GetWspolczynnik(i));
    }
    return wynik;
}

ostream& operator<<(ostream& os, const Wielomian& w) {
    w.Pokaz();
    return os;
}

istream& operator>>(istream& is, Wielomian& w) {
    char bufor[1024];

    is.getline(bufor, sizeof(bufor));

    if (strlen(bufor) > 0) {
        w = Wielomian(bufor);
        //Analizuj(w);
    }
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

const char* Wielomian::PominOdstepy(const char* napis) {
    while (*napis == ' ') {
        napis++;
    }
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
        else
            i++;
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

void Wielomian::Pokaz() const {
    bool pierwszy = true;
    bool wszystkieZerowe = true;

    for (int i = stopien; i >= 0; i--) {
        if (wspolczynnik[i] != 0.0) {
            wszystkieZerowe = false;
            break;
        }
    }

    if (wszystkieZerowe) {
        cout << "0\n";
        return;
    }

    for (int i = stopien; i >= 0; i--) {
        double wsp = wspolczynnik[i];

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

int main() {
    Wielomian w0;
    cout << "Domyslny: ";
    w0.Pokaz();

    double tab[] = { 1.0, 2.0 };
    Wielomian w1(1, tab);
    cout << "Tablica: ";
    w1.Pokaz();

    Wielomian w2("3x^2-2x+5");
    cout << "Napis: ";
    w2.Pokaz();

    Wielomian w3(w2);
    cout << "Kopiujacy: ";
    w3.Pokaz();

    Wielomian wPrzypisany;
    wPrzypisany = w2;
    cout << "Operator przypisania (=): ";
    wPrzypisany.Pokaz();

    w2 += w1;
    cout << "w2 += w1: ";
    w2.Pokaz();

    Wielomian w4 = w1 + w3;
    cout << "w1 + w3: ";
    w4.Pokaz();

    w2.Pokaz();
    w1.Pokaz();
    w2 -= w1;
    cout << "w2 -= w1: ";
    w2.Pokaz();

    w3.Pokaz();
    Wielomian w5 = w3 - w1;
    cout << "w3 - w1: ";
    w5.Pokaz();

    w5 = w5 - 5;
    w5.Pokaz();
    w5 = 5 - w5;
    w5.Pokaz();

    w5 = w5 + 5;
    w5.Pokaz();
    w5 = 5 + w5;
    w5.Pokaz();

    w5 -= 5;
    w5.Pokaz();
    w5 += 5;
    w5.Pokaz();

    w3.Pokaz();
    w5.Pokaz();

    WynikDzielenia wynik = (w5 /= w3);

    wynik.iloraz.Pokaz();
    wynik.reszta.Pokaz();
    w5.Pokaz();

    w3 *= w3;
    w3.Pokaz();

    w3 = w3 * w3;
    w3.Pokaz();

    wynik = w3 / w3;
    wynik.iloraz.Pokaz();
    wynik.reszta.Pokaz();

    w1.Pokaz();
    cout << w1(2) << endl;

    w1.Pokaz();
    cout << w1[1] << endl;
    w1[1] = 5;
    w1.Pokaz();
    cout << w1 << endl;

    cout << "Podaj wielomian: ";
    cin >> w1;
    cout << w1 << endl;

    return 0;
}

// TODO:
// Podzielić program na Wielomian.h, Wielomian.cpp, Main.cpp
// dodać np. #ifdef __WIELOMIAN_H 
// #define __WIELOMIAN_H
// #endif

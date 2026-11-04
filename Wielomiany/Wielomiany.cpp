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
    Wielomian(const char* napis);
    Wielomian(const Wielomian& w);
    ~Wielomian();
    Wielomian& operator=(const Wielomian& w);
    Wielomian& operator+=(const Wielomian&);
    Wielomian& operator-=(const Wielomian&);

    unsigned int GetStopien() {
        return stopien;
    }
    double GetWspolczynnik(unsigned int i) {
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
    void Pokaz();
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

Wielomian::Wielomian(const char* napis) {
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

Wielomian operator+(Wielomian w1, Wielomian w2) {
    w1 += w2;
    return w1;
}

Wielomian operator-(Wielomian w1, Wielomian w2) {
    w1 -= w2;
    return w1;
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

void Wielomian::Pokaz() {
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

    return 0;
}

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

unsigned int OkreslStopien(const char* napis);
void AnalizujJednomiany(const char* napis, class Wielomian* w);

class Wielomian {
    double* wspolczynnik;
    unsigned int stopien;
    public:
        Wielomian();
        Wielomian(int st, double *wsp);
        Wielomian(const char *napis);
        Wielomian(Wielomian &w);
        ~Wielomian();
        Wielomian& operator+=(const Wielomian&);
};

Wielomian::Wielomian() {
    stopien = 0;
    wspolczynnik = new double[1];
    wspolczynnik[0] = 0.0;
}

Wielomian::Wielomian(int st, double *wsp) {
    stopien = st;
    wspolczynnik = new double[stopien + 1];
    for (unsigned int i = 0; i <= stopien; i++) {
        wspolczynnik[i] = (wsp != 0) ? wsp[i] : 0.0;
    }
}

Wielomian::Wielomian(const char *napis) {
    stopien = OkreslStopien(napis);
    wspolczynnik = new double[stopien + 1];
    for (unsigned int i = 0; i <= stopien; i++)
        wspolczynnik[i] = 0.0;
    AnalizujJednomiany(napis, this);
}

Wielomian::Wielomian(Wielomian &w) {
    stopien = w.stopien;
    wspolczynnik = new double[stopien + 1];
    for (unsigned int i = 0; i <= stopien; i++) {
        wspolczynnik[i] = w.wspolczynnik[i];
    }
}

Wielomian::~Wielomian() {
    delete[] wspolczynnik;
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

const char* PominOdstepy(const char* napis) {
    while (*napis == ' ') {
        napis++;
    }
    return napis;
}

unsigned int OkreslStopien(const char* napis) {
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
    float* tab = new double[stopien + 1];
    for (int i = 0; i <= stopien; i++)
        tab[i] = 0.0f;
    return tab;
}

const char* AnalizujJednomian(const char* napis, Wielomian* w) {
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

    w->wspolczynnik[wykladnik] = znak * wspolczynnik;

    return napis;

}

void AnalizujJednomiany(const char* napis, Wielomian* w) {
    while (*napis) {
        napis = PominOdstepy(napis);
        if (*napis == '\0') break;
        napis = AnalizujJednomian(napis, w);
    }
}

Wielomian Analizuj(const char* napis) {
    Wielomian w;
    w.stopien = OkreslStopien(napis);
    delete[] w.wspolczynnik;
    w.wspolczynnik = PrzydzielPamiec(w.stopien);
    AnalizujJednomiany(napis, &w);

    return w;
}

void Pokaz(Wielomian w) {
    bool pierwszy = true;
    bool wszystkieZerowe = true;

    for (int i = w.stopien; i >= 0; i--) {
        if (w.wspolczynnik[i] != 0.0) {
            wszystkieZerowe = false;
            break;
        }
    }

    if (wszystkieZerowe) {
        cout << "0\n";
        return;
    }

    for (int i = w.stopien; i >= 0; i--) {
        double wsp = w.wspolczynnik[i];

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
    const char* napis1 = "3x^2-2x+5";
    const char* napis2 = "-3x^2";
    // Wielomian w = Analizuj(napis1);
    Wielomian w1(napis1);
    Wielomian w2(napis2);

    // Pokaz(w);
    
    return 0;
}

// TODO:
// klasa Wielomian
//  konstruktor
//  konstruktory inne
//  operatory +...

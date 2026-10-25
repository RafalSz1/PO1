#include <iostream>
#include <cstring>

using namespace std;

typedef struct {
    float *wspolczynnik;
    int stopien;
} Wielomian;

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

int OkreslStopien(const char* napis) {
    int maksStopien = 0;
    int stopien = 0;
    int i = 0;
    while (napis[i]) {
        napis = PominOdstepy(napis);
        if (napis[i] == 'x') {
            if (napis[i + 1] == '^') {
                char* koniecNapisu;
                stopien = strtol(&napis[i+2], &koniecNapisu, 10);
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
float* PrzydzielPamiec(int stopien) {
    float* tab = new float[stopien + 1];
    for (int i = 0; i <= stopien; i++)
        tab[i] = 0.0f;
    return tab;
}

const char* AnalizujJednomian(const char* napis, Wielomian* w)
{
    napis = PominOdstepy(napis);
    if (*napis == '\0') return napis;
    
    int wykladnik = 0;
    int znak = 1;
    float wspolczynnik = 1.0f;

    if (*napis == '-')
    {
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

void AnalizujJednomiany(const char* napis, Wielomian *w){
    while(*napis) {
        napis = PominOdstepy(napis);
        if (*napis == '\0') break;
        napis = AnalizujJednomian(napis, w);
    }
}

Wielomian Analizuj(const char* napis)
{
    Wielomian w;
    w.stopien = OkreslStopien(napis);
    w.wspolczynnik = PrzydzielPamiec(w.stopien);
    AnalizujJednomiany(napis, &w);
    
    return w;
}

void Pokaz(Wielomian w) {
    bool pierwszy = true;
    bool wszystkieZerowe = true;

    for (int i = w.stopien; i >= 0; i--) {
        if (w.wspolczynnik[i] != 0.0f) {
            wszystkieZerowe = false;
            break;
        }
    }

    if (wszystkieZerowe) {
        cout << "0\n";
        return;
    }

    for (int i = w.stopien; i >= 0; i--) {
        float wsp = w.wspolczynnik[i];
        
        if (wsp == 0.0f) {
            continue;
        }

        if (pierwszy) {
            if (wsp < 0) {
                cout << "-";
            }
        } else {
            if (wsp < 0) {
                cout << " - ";
            } else {
                cout << " + ";
            }
        }

        float absWsp = wsp;
        if (absWsp < 0)
            absWsp = -absWsp;

        if (i == 0)
            cout << absWsp;
        else {
            if (absWsp != 1.0f)
                cout << absWsp;
            cout << "x";
            if (i > 1)
                cout << "^" << i;
        }

        pierwszy = false;
    }
    cout << endl;
}

int main()
{
    const char* napis = "x^3-x^2+2x-7.5";
    Wielomian w = Analizuj(napis);
    Pokaz(w);
}

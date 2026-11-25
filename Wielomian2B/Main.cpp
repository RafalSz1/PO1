#include "Wielomian.h"

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

    cout << "\\=" << endl;
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

    cout << w1.Pochodna(2) << endl;

    Wielomian w6("x");
    cout << w1 % w6;
    Wielomian w7("3x^2+2");
    w7 %= w6;
    cout << w7;

    cout << "\nJednomian" << endl;

    Jednomian j0;
    Jednomian j1(2, 3.0);
    Jednomian j2(3, 2.0);
    cout << "j0 (domyslny): " << j0;
    cout << "j1: " << j1;
    cout << "j1[2] = " << j1[2] << ", j1[0] = " << j1[0] << endl;

    Jednomian jMnozenie = j1 * j2;
    Jednomian jSkalar = j1 * 4.0;
    Jednomian jDzielenie = jSkalar / 2.0;
    Jednomian jPochodna = j2.Pochodna();
    cout << "j1 * j2 (Jednomian): " << jMnozenie;
    cout << "j1 * 4 (Jednomian): " << jSkalar;
    cout << "jSkalar / 2 (Jednomian): " << jDzielenie;
    cout << "Pochodna j2 (Jednomian): " << jPochodna;

    Wielomian wSumaJ = j1 + j2;
    Wielomian wMix1 = w1 + j1;
    Wielomian wMix2 = j2 - w1;
    Wielomian wMix3 = w1 * j1;
    cout << "j1 + j2 (Wielomian): " << wSumaJ;
    cout << "w1 + j1: " << wMix1;
    cout << "j2 - w1: " << wMix2;
    cout << "w1 * j1: " << wMix3;

    wMix1 += j2;
    cout << "wMix1 += j2: " << wMix1;

    Wielomian wZJednomianu(j1);
    wZJednomianu = j2;
    cout << "Wielomian z Jednomianu: " << wZJednomianu;

    BazaWielomianu* tabBaza[2];
    tabBaza[0] = &j1;
    tabBaza[1] = &wSumaJ;

    for (int i = 0; i < 2; i++) {
        cout << "Baza[" << i << "]: " << *tabBaza[i];
        cout << "Wartosc dla x=2: " << (*tabBaza[i])(2.0) << endl;
    }

    return 0;
}

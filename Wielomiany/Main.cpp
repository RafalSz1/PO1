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

    cout << w1 % w2;

    return 0;
}

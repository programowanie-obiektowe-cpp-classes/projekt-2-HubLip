//Program prezentujący klasę Wektor3D. Operacje na wektorach 3D różnego typu, np. int i double. Należy zastosować wzorce.
#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <algorithm>
#include <stdexcept> //obsluga wyjatkow

using namespace std;
using namespace Eigen;

template <typename T>
class Wektor3D 
{
private:
    Matrix<T, 3, 1> vec3D; 
public:
    Wektor3D() { vec3D.setZero(); } //Inicjalizuje wektor na [0, 0, 0]
    Wektor3D(T x, T y, T z) : vec3D(x, y, z) {} //Przypisujemy wartosci x,y,z
    Wektor3D(Matrix<T, 3, 1> v) : vec3D(v) {} //konstruktor przyjmujacy macierz Eigen

    void print() //wyswietlanie zawartosci wektora
    { 
        cout << "Wektor 3D: ";
        cout << "[" << vec3D(0) << ", " << vec3D(1) << ", " << vec3D(2) << "]\n"; 
    }

    T get(int i) // Funkcja do pobierania i elementu wektora
    { 
        return vec3D(i);
    }

    //Okreslone operatory -> +, -, dot(), cross(), norma();
    Wektor3D operator+(Wektor3D& v)
    { 
        return Wektor3D(vec3D + v.vec3D); //zwracam Wektor ktory zawiera Eigen::Matrix jako swoje pola 
    }

    Wektor3D operator-(Wektor3D& v)
    { 
        return Wektor3D(vec3D - v.vec3D); 
    }

    Wektor3D cross(Wektor3D& v) //iloczyn wektorowy
    { 
        // Matrix<T, 3, 1> result = vec3D.cross(v.vec3D);
        return Wektor3D(vec3D.cross(v.vec3D)); // Zwracamy nowy obiekt Wektor3D z wynikiem
    }

    T dot(Wektor3D& v)
    { 
        return vec3D.dot(v.vec3D); //wykorzystanie dobrze okreslonej juz metody dot() z Eigen
    }

    T norma() //Dlugosc wektora
    {
        return vec3D.norm();
    }

};

template <typename T>
ostream& operator<<(ostream& os, Wektor3D<T>& w) 
{
    os << "[" << w.get(0) << ", " << w.get(1) << ", " << w.get(2) << "]";
    return os;
}

// Funkcja do znalezienia wektora o najwiekszej długosci
template <typename T>
Wektor3D<T> znajdzNajdluzszyWektor( vector<Wektor3D<T>>& wektory) {
    if (wektory.empty()) 
    {
        throw runtime_error("Brak wektorow!!!");
    }
    auto max = max_element(wektory.begin(), wektory.end(), [](Wektor3D<T>& a, Wektor3D<T>& b) 
    {
        return a.norma() < b.norma(); //Algorytm max_element znajduje najwiekszy element
    }); //zwracamy iterator
    return *max; //zwraca obiekt na ktory skazuje iterator
}

// Funkcja sortujaca wektory wedlug dlugosci
template <typename T>
void sortujWektory(vector<Wektor3D<T>>& v) 
{
    sort(v.begin(), v.end(), []( Wektor3D<T>& a, Wektor3D<T>& b) 
    {
        return a.norma() < b.norma(); // Porównanie norm
    });
}

void menu() {
    cout << "\nMenu:\n";
    cout << "0. Wyswietl wektory\n";
    cout << "1. Dodaj wektory\n";
    cout << "2. Odejmij wektory\n";
    cout << "3. Iloczyn skalarny wektorow\n";
    cout << "4. Iloczyn wektorowy wektorow\n";
    cout << "5. Norma wektora\n";
    cout << "6. Sortuj wektory wedlug normy\n";
    cout << "7. Znajdz najdluzszy wektor\n";
    cout << "8. Dodaj nowy wektor\n";
    cout << "9. Usun wektor\n";
    cout << "10. Wyjscie\n";
    cout << "Wybierz opcje: ";
}

template <typename T>
void executeMenuOption(int option, vector<Wektor3D<T>>& wektory) 
{
    try 
    {
        int idx1, idx2;
        Wektor3D<T> wynik;

        switch (option) 
        {
            case 0: // Wyswietl wektory
                for (int i = 0; i < wektory.size(); i++) {
                    cout << "Wektor " << i << ": " << wektory[i] << endl;
                }
                break;

            case 1: // Dodaj wektory
                cout << "Podaj indeksy wektorow do dodania (0 do " << wektory.size() - 1 << "): ";
                cin >> idx1 >> idx2;
                if (idx1 < 0 || idx1 >= wektory.size() || idx2 < 0 || idx2 >= wektory.size()) {
                    throw out_of_range("Zle indeksy!");
                } else {
                    wynik = wektory[idx1] + wektory[idx2];
                    cout << "Wynik dodawania: " << wynik << endl;
                }
                break;

            case 2: // Odejmij wektory
                cout << "Podaj indeksy wektorow do odejmowania (0 do " << wektory.size() - 1 << "): ";
                cin >> idx1 >> idx2;
                if (idx1 < 0 || idx1 >= wektory.size() || idx2 < 0 || idx2 >= wektory.size()) {
                    throw out_of_range("Zle indeksy!");
                } else {
                    wynik = wektory[idx1] - wektory[idx2];
                    cout << "Wynik odejmowania: " << wynik << endl;
                }
                break;

            case 3: // Iloczyn skalarny
                cout << "Podaj indeksy wektorow do obliczenia iloczynu skalarnego (0 do " << wektory.size() - 1 << "): ";
                cin >> idx1 >> idx2;
                if (idx1 < 0 || idx1 >= wektory.size() || idx2 < 0 || idx2 >= wektory.size()) {
                    throw out_of_range("Zle indeksy!");
                } else {
                    T dotResult = wektory[idx1].dot(wektory[idx2]);
                    cout << "Iloczyn skalarny: " << dotResult << endl;
                }
                break;

            case 4: // Iloczyn wektorowy
                cout << "Podaj indeksy wektorow do obliczenia iloczynu wektorowego (0 do " << wektory.size() - 1 << "): ";
                cin >> idx1 >> idx2;
                if (idx1 < 0 || idx1 >= wektory.size() || idx2 < 0 || idx2 >= wektory.size()) {
                    throw out_of_range("Zle indeksy!");
                } else {
                    wynik = wektory[idx1].cross(wektory[idx2]);
                    cout << "Iloczyn wektorowy: " << wynik << endl;
                }
                break;

            case 5: // Norma wektora
                cout << "Podaj indeks wektora do obliczenia normy (0 do " << wektory.size() - 1 << "): ";
                cin >> idx1;
                if (idx1 < 0 || idx1 >= wektory.size()) {
                    throw out_of_range("Zle indeksy!");
                } else {
                    T norma = wektory[idx1].norma();
                    cout << "Norma wektora: " << norma << endl;
                }
                break;

            case 6: // Sortuj wektory wedlug normy
                sort(wektory.begin(), wektory.end(), [](Wektor3D<T>& a, Wektor3D<T>& b) {
                    return a.norma() < b.norma();
                });
                cout << "Wektory posortowane wedlug normy:\n";
                for (int i = 0; i < wektory.size(); i++) {
                    cout << "Wektor " << i << ": " << wektory[i] << endl;
                }
                break;

            case 7: // Znajdz najdluzszy wektor
                if (wektory.empty()) {
                    throw out_of_range("Brak wektorow!");
                } else {
                    auto najdluzszy = *max_element(wektory.begin(), wektory.end(), [](Wektor3D<T>& a, Wektor3D<T>& b) {
                        return a.norma() < b.norma();
                    });
                    cout << "Najdluzszy wektor: " << najdluzszy << endl;
                    cout << "Norma: " << najdluzszy.norma() << endl;
                }
                break;

            case 8: // Dodaj nowy wektor
                T x, y, z;
                cout << "Podaj wspolrzedne wektora (x y z): ";
                cin >> x >> y >> z;
                wektory.emplace_back(x, y, z);
                cout << "Dodano nowy wektor: [" << x << ", " << y << ", " << z << "]" << endl;
                break;

            case 9: // Usun wektor
                cout << "Podaj indeks wektora do usuniecia (0 do " << wektory.size() - 1 << "): ";
                cin >> idx1;
                if (idx1 < 0 || idx1 >= wektory.size()) {
                    throw out_of_range("Zle indeksy!");
                } else {
                    wektory.erase(wektory.begin() + idx1);
                    cout << "Usunieto wektor o indeksie " << idx1 << endl;
                }
                break;

            case 10: // Wyjscie
                cout << "Do widzenia!" << endl;
                break;

            default:
                throw invalid_argument("Nieznana opcja!");
        }
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}


int main() 
{
    int typ;
    cout << "Wybierz typ wektora (1 - int, 2 - double): ";
    cin >> typ;

    if (typ == 1) {
        vector<Wektor3D<int>> wektory;
        int opcja = 0;
        while (opcja != 10) {
            menu();
            cin >> opcja;
            executeMenuOption(opcja, wektory);
        }
    } else if (typ == 2) {
        vector<Wektor3D<double>> wektory;
        int opcja = 0;
        while (opcja != 10) {
            menu();
            cin >> opcja;
            executeMenuOption(opcja, wektory);
        }
    } else 
    {
        cout << "Nieznany typ!" << endl;
    }
    return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using std::cout;
using std::string;
using std::vector;
using std::accumulate;
using std::istream;
using std::ostream;

class Studentas {
    string vardas;
    string pavarde;
    vector<int> pazymiai;
    int egzaminas = 0;
    double rezultatas = 0.0;

    void vidurkis() {
        if (!pazymiai.empty()) {
            double avg = std::accumulate(pazymiai.begin(), pazymiai.end(), 0.0) / pazymiai.size();
            rezultatas = avg * 0.4 + egzaminas * 0.6;
        }
        else {
            rezultatas = egzaminas * 0.6; // jei ND nėra
        }
    }

public:
    string getVardas() const {
        return vardas;
    }
    string getPavarde() const {
        return pavarde;
    }
    vector<int> getPazymiai() const {
        return pazymiai;
    }
    int getEgzaminas() const {
        return egzaminas;
    }
    double getRezultatas() const {
        return rezultatas;
    }
    // Default constructor
    Studentas() {

    }
    Studentas(string v, string p, vector<int> paz, int egzas) {
        vardas = v;
        pavarde = p;
        pazymiai = paz;
        egzaminas = egzas;
        vidurkis();
    }
    // priskyrimo-kopijavimo operatorius
    Studentas& operator=(const Studentas& other) {
        if (this == &other) return *this; 
        vardas = other.vardas;
        pavarde = other.pavarde;
        return *this;
    }
    // kopijavimo konstruktorius
    Studentas(const Studentas& other) {
        vardas = other.vardas;
        pavarde = other.pavarde;
    }
    // destruktorius
    ~Studentas() {
        vardas.clear();
        pavarde.clear();
        pazymiai.clear();
        egzaminas = 0;
        rezultatas = 0;
    };
    // operatorių perkrovimas
    // 
    friend istream& operator>>(istream& in, Studentas& s) {
        cout << "Iveskite varda ir pavarde: ";
        in >> s.vardas >> s.pavarde;

        cout << "Kiek ND pazymiu? ";
        int n = 0;
        in >> n;

        s.pazymiai.clear();
        s.pazymiai.resize(n);
        cout << "Iveskite " << n << " ND pazymius: ";
        for (int i = 0; i < n; ++i) in >> s.pazymiai[i];

        cout << "Iveskite egzamino pazymi: ";
        in >> s.egzaminas;

        s.vidurkis();
        return in;
    }

    // Isvedimas (perdengtas cout)
    friend ostream& operator<<(ostream& out, const Studentas& s) {
        out << "Vardas  " << "Pavarde  " << " Galutinis (vid.)"
            << s.vardas << " " << s.pavarde << s.rezultatas;
        return out;
    }
};

int main()
{
    Studentas st;
    std::cin >> st;   
    std::cout << st;  
}
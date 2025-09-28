#include "Studentas.h"
#include <numeric>
#include <algorithm>
#include <random>
#include <iomanip>
#include <iostream>

using std::string;
using std::vector;
using std::istream;
using std::ostream;
using std::ifstream;
using std::accumulate;
using std::sort;
using std::endl;
using std::stoi;
using std::copy;
using std::cin;
using std::cout;
using std::setw;
using std::left;
using std::right;


double Studentas::vidurkis() {
    if (!pazymiai.empty()) {
        double avg = accumulate(pazymiai.begin(), pazymiai.end(), 0.0) / pazymiai.size();
        return avg * 0.4 + egzaminas * 0.6;
    }
    else {
        return egzaminas * 0.6;
    }
}

double Studentas::mediana() {
    if (!pazymiai.empty()) {
        sort(pazymiai.begin(), pazymiai.end());
        double med = (pazymiai.size() % 2 == 0) ? (pazymiai[pazymiai.size() / 2 - 1] + pazymiai[pazymiai.size() / 2]) / 2.0 : pazymiai[pazymiai.size() / 2];
        return med * 0.4 + egzaminas * 0.6;
    }
    else {
        return egzaminas * 0.6;
    }

}
void Studentas::setModeMediana(bool m) { naudotiMediana_ = m; }

string Studentas::getVardas() const {
    return vardas;
}
string Studentas::getPavarde() const {
    return pavarde;
}
vector<int> Studentas::getPazymiai() const {
    return pazymiai;
}
int Studentas::getEgzaminas() const {
    return egzaminas;
}
double Studentas::getRezultatasV() const {
    return rezultatasV;
}
double Studentas::getRezultatasM() const {
    return rezultatasM;
}

// Default constructor
Studentas::Studentas() = default;

Studentas::Studentas(string v, string p, vector<int>paz, int egzas) {
    vardas = v;
    pavarde = p;
    pazymiai = paz;
    egzaminas = egzas;
    rezultatasV = vidurkis();
    rezultatasM = mediana();
}

// kopijavimo konstruktorius
Studentas::Studentas(const Studentas& other) {
    vardas = other.vardas;
    pavarde = other.pavarde;
    copy(other.pazymiai.begin(), other.pazymiai.end(), std::back_inserter(pazymiai));
    egzaminas = other.egzaminas;
    rezultatasV = other.rezultatasV;
    rezultatasM = other.rezultatasM;
}

//kopijavimo ir priskyrimo kontruktorius
Studentas& Studentas::operator= (const Studentas& other) {
    if (this == &other) return *this;
    else {
        vardas = other.vardas;
        pavarde = other.pavarde;
        copy(other.pazymiai.begin(), other.pazymiai.end(), std::back_inserter(pazymiai));
        egzaminas = other.egzaminas;
        rezultatasV = other.rezultatasV;
        rezultatasM = other.rezultatasM;
        return *this;
    }
}

// destruktorius
Studentas::~Studentas() {
    vardas.clear();
    pavarde.clear();
    pazymiai.clear();
    egzaminas = 0;
    rezultatasV = 0;
    rezultatasM = 0;
}

bool Studentas::comparePavarde(const Studentas& a, const Studentas& b)
{
    return a.getPavarde() < b.getPavarde();
}

// operatorių perkrovimas 
istream& operator>>(istream& in, Studentas& s) {
    in >> s.vardas >> s.pavarde;

    s.pazymiai.clear();
    string input;
    while (true) {
        in >> input;
        if (input == "x" || input == "X") break;
        s.pazymiai.push_back(stoi(input));
    }
    in >> s.egzaminas;
    s.rezultatasV = s.vidurkis();
    s.rezultatasM = s.mediana();

    return in;
}

// Isvedimas (perdengtas cout)
ostream& operator<<(ostream& out, const Studentas& s) {

    double gal = s.naudotiMediana_ ? s.rezultatasM : s.rezultatasV;

    out << left << setw(16) << s.pavarde << setw(12) << s.vardas << ' '
        << std::fixed << right << setw(15) << std::setprecision(2) << gal;

    return out;
}

// atsitiktiniu skaiciu generavimas
void Studentas::randomize(size_t n, unsigned seed) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> d(1, 10);
    pazymiai.resize(n);
    for (int& x : pazymiai) x = d(rng);
    egzaminas = d(rng);
    rezultatasV = vidurkis();
    rezultatasM = mediana();
}
bool Studentas::naudotiMediana_ = false;

#include "Studentas.h"
#include <numeric>
#include <algorithm>
#include <random>
#include <iomanip>
#include <iostream>
#include "io.h"

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

string fname = "duomenys.txt"; 


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
void Studentas::pasirinkimas() {
    int m;
    std::mt19937 rng(std::random_device{}());

    cout << "Pasirinkite\n";
    cout << "[1] Sugeneruoti 5 atsitiktiniu failus\n";
    cout << "[2] Nuskaityti duomenis is esamo failo\n";
    cout << "[3] Sugeneruoti pazymius atsitiktine tvarka\n";
    cout << "[4] Suvesti varda, pavarde ir pazymius rankiniu budu\n";
    cout << "[0] Iseiti\n> ";

    cin >> m;

    vector<Studentas> studentai;
    Studentas s;
    bool hasData = false; 

    switch (m) {
        case 1: {
            std::cout << "Generuoju 5 failus...\n";
            generate_all(rng);
            std::cout << "Baigta.\n";
        
            cout << "Ar failuose sugeneruotiems studentams paskaiciuoti galutini bala " << endl;
            cout << "ir isvesti i atskirus failus(islaike.txt), (neislaike.txt)" << endl;
            cout << "Jeigu taip, iveskite raide [T] ir spauskite enter" << endl;
            char y;
            cin >> y;
            if (y == 't' || y == 'T'){
            cout << "Rezultata [m]ediana ar [v]idurkis? ";
            char c;
            cin >> c;
            bool naudotiMediana = (c == 'm' || c == 'M');
            process_all_inputs(naudotiMediana);   // ← nuskaito visus 5 ir sukuria 2 bendrus failus
            }
            break;
        }
        case 2: {
            string fname;
            cout << "Iveskite failo pavadinima: ";
            cin >> fname;
            try {
                studentai = readStudentsFromFile(fname);
                hasData = !studentai.empty();
            }
            catch (const std::exception& e) {
                std::cerr << "Nepavyko nuskaityti failo: " << e.what() << endl;
            }
            break;
        }
        case 3: {
            string v, p;
            cout << "Iveskite varda ir pavarde: ";
            cin >> v >> p;

            cout << "Kiek pazymiu sugeneruoti (1..10)? ";
            int n; cin >> n;

            s = Studentas(v, p, {}, 0);
            s.randomize(n);
            studentai.push_back(s);      
            hasData = true;
            break;
        }
        case 4: {
            cout << "Iveskite: Vardas Pavarde Pazymius (pabaigai 'x'), tada egzamino bala\n";
            cin >> s;
            studentai.push_back(s);
            hasData = true;
            break;
        }
        case 0: {
            return;
        }
        default: {
            std::cout << "Neteisingas pasirinkimas\n";
            break;
        }
    }
    if (hasData) {
        cout << "Pasirinkite rezultata: [m]ediana arba [v]idurkis: ";
        char c;
        cin >> c;
        bool med = (c == 'm' || c == 'M');
        Studentas::setModeMediana(med);

        cout << left << setw(16) << "Pavarde" << setw(12) << "Vardas"
            << "Galutinis (" << (med ? "Med." : "Vid.") << ")\n"
            << "----------------------------------------------\n";

        std::sort(studentai.begin(), studentai.end(), Studentas::comparePavarde);
        for (const auto& st : studentai) cout << st << '\n';
    }
}
bool Studentas::naudotiMediana_ = false;

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>

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
    double rezultatasV = 0.0;
    double rezultatasM = 0.0;

    static bool naudotiMediana_;

    void vidurkis() {
        if (!pazymiai.empty()) {
            double avg = std::accumulate(pazymiai.begin(), pazymiai.end(), 0.0) / pazymiai.size();
            rezultatasV = avg * 0.4 + egzaminas * 0.6;
        }
        else {
            rezultatasV = egzaminas * 0.6;
        }
    }
    void mediana() {
        if (!pazymiai.empty()) {
            std::vector<int> t = pazymiai;
            std::sort(t.begin(), t.end());
            double med = (t.size() % 2 == 0) ? (t[t.size() / 2 - 1] + t[t.size() / 2]) / 2.0 : t[t.size() / 2];
            rezultatasM = med * 0.4 + egzaminas * 0.6;
        }
        else {
            rezultatasM = egzaminas * 0.6;
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
    double getRezultatasV() const {
        return rezultatasV;
    }
    double getRezultatasM() const {
        return rezultatasM;
    }
    static void setModeMediana(bool m) { naudotiMediana_ = m; }  
   
    static void printHeader(std::ostream& out) {
        out << std::left << std::setw(13) << "Vardas"
            << std::setw(13) << "Pavarde"
            << (naudotiMediana_ ? "Galutinis (Med.)" : "Galutinis (Vid.)") << "\n"
            << "------------------------------------------------\n";
    }

    // Default constructor
    Studentas() {

    }
    Studentas(string v, string p, vector<int>paz, int egzas) {
        vardas = v;
        pavarde = p;
        pazymiai = paz;
        egzaminas = egzas;
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
        rezultatasV = 0;
        rezultatasM = 0;
    };
    // operatorių perkrovimas 
    friend istream& operator>>(istream& in, Studentas& s) {
        cout << "Iveskite varda ir pavarde: ";
        in >> s.vardas >> s.pavarde;
        cout << "Iveskite pazymius" << std::endl;
        cout << "Baige vesti pazymius paspauskite x ir tada Enter klavisa" << std::endl;

        string input;
        while (true) {
            in >> input;
            if (input == "x") break;
            s.pazymiai.push_back(std::stoi(input));
        }
        
        cout << "Iveskite egzamino pazymi: ";
        in >> s.egzaminas;

        s.vidurkis();
        s.mediana();

        std::cout << "Spausdinti pagal mediana (m) ar vidurki (v)? ";
        char c; in >> c;
        Studentas::setModeMediana(c == 'm' || c == 'M');
        return in;
    }

    // Isvedimas (perdengtas cout)
    friend std::ostream& operator<<(std::ostream& out, const Studentas& s) {
        out << std::left << std::setw(13) 
            << s.vardas << std::setw(13) 
            << s.pavarde << std::fixed 
            << std::setprecision(2) 
            << (naudotiMediana_ ? s.rezultatasM : s.rezultatasV);
        return out;
    }
};

bool Studentas::naudotiMediana_ = false;

int main()
{
    Studentas st = Studentas();
    std::cin >> st;                 
    Studentas::printHeader(std::cout);
    std::cout << st << "\n";

}
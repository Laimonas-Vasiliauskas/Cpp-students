#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <iomanip>

using std::string;
using std::vector;
using std::accumulate;
using std::istream;
using std::ostream;
using std::sort;
using std::cin;
using std::cout;
using std::endl;
using std::stoi;
using std::copy;

class Studentas {
private:
    string vardas;
    string pavarde;
    vector<int> pazymiai;
    int egzaminas = 0;
    double rezultatasV = 0.0;
    double rezultatasM = 0.0;

    static bool naudotiMediana_;

    void vidurkis() {
        if (!pazymiai.empty()) {
            double avg = accumulate(pazymiai.begin(), pazymiai.end(), 0.0) / pazymiai.size();
            rezultatasV = avg * 0.4 + egzaminas * 0.6;
        }
        else {
            rezultatasV = egzaminas * 0.6;
        }
    }
    void mediana() {
        if (!pazymiai.empty()) {
            vector<int> t = pazymiai;
            sort(t.begin(), t.end());
            double med = (t.size() % 2 == 0) ? (t[t.size() / 2 - 1] + t[t.size() / 2]) / 2.0 : t[t.size() / 2];
            rezultatasM = med * 0.4 + egzaminas * 0.6;
        }
        else {
            rezultatasM = egzaminas * 0.6;
        }

    }
public:
    static void setModeMediana(bool m) { naudotiMediana_ = m; }

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

    // Default constructor
    Studentas() = default;

    Studentas(string v, string p, vector<int>paz, int egzas) {
        vardas = v;
        pavarde = p;
        pazymiai = paz;
        egzaminas = egzas;
        vidurkis();
        mediana();
    }
    // kopijavimo konstruktorius
    Studentas(const Studentas& other) {
        vardas = other.vardas;
        pavarde = other.pavarde;
        copy(other.pazymiai.begin(), other.pazymiai.end(), std::back_inserter(pazymiai));
        egzaminas = other.egzaminas;
    }
    //kopijavimo ir priskyrimo kontruktorius
    Studentas& operator= (const Studentas& other) {  
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
    ~Studentas() {
        vardas.clear();
        pavarde.clear();
        pazymiai.clear();
        egzaminas = 0;
        rezultatasV = 0;
        rezultatasM = 0;
    }
    // operatorių perkrovimas 
    friend istream& operator>>(istream& in, Studentas& s) {
        in >> s.vardas >> s.pavarde;

        s.pazymiai.clear();
        string input;
        while (true) {
            in >> input;
            if (input == "x" || input == "X") break;
            s.pazymiai.push_back(stoi(input));
        }
        in >> s.egzaminas;
        s.vidurkis();
        s.mediana();

        return in;
    }
    // Isvedimas (perdengtas cout)
    friend ostream& operator<<(ostream& out, const Studentas& s) {
        
        double gal = Studentas::naudotiMediana_ ? s.rezultatasM : s.rezultatasV;

        out << s.pavarde << ' ' << s.vardas << ' '
            << std::fixed << std::setprecision(2) << gal;

        return out;
    }
    // atsitiktiniu skaiciu generavimas
    void randomize(size_t n, unsigned seed = std::random_device{}()) {
        std::mt19937 rng(seed);
        std::uniform_int_distribution<int> d(1, 10);
        pazymiai.resize(n);
        for (int& x : pazymiai) x = d(rng);
        egzaminas = d(rng);
        vidurkis();
        mediana();
    }
};
bool Studentas::naudotiMediana_ = false;

int main() {
    Studentas s;

    cout << "Ar sugeneruoti pazymius atsitiktine tvarka? [T/N]: ";
    char g;
    cin >> g;

    if (g == 't' || g == 'T') {
        string v, p;
        cout << "Iveskite varda ir pavarde: ";
        cin >> v >> p;

        cout << "Kiek pazymiu sugeneruoti (1..10)? ";
        int n;
        cin >> n;

        s = Studentas(v, p, {}, 0);
        s.randomize(n);
    }
    else {
        cout << "Iveskite: Vardas Pavarde Pazymius, baige vesti pazymius iveskite raide x ir spauskite Enter, tada egzamino pazymi" << endl;
        cin >> s; 
    }

    cout << "Pasirinkite rezultata: [m]ediana arba [v]idurkis: ";
    char c;
    cin >> c;
    Studentas::setModeMediana(c == 'm' || c == 'M');

    cout << "Pavarde " << "Vardas "
        << ((c == 'm' || c == 'M') ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl;
    cout << "----------------------------------------------" << endl;
    cout << s << endl;

    return 0;
}

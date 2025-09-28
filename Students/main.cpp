#include "Studentas.h"
#include "io.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>

using std::string;
using std::vector;
using std::istream;
using std::ostream;
using std::ifstream;
using std::sort;
using std::endl;
using std::stoi;
using std::copy;
using std::cin;
using std::cout;
using std::setw;
using std::left;
using std::right;



int main() {  
    cout << "Ar nuskaityti duomenis is failo? [T/N]" << endl;
    vector<Studentas> studentai;
    char h;
    cin >> h;
    if (h == 't' || h == 'T') {
        try {
            studentai = readStudentsFromFile("kursiokai.txt");
        }
        catch (const std::exception& e) {
            std::cerr << "Nepavyko nuskaityti failo: " << e.what() << endl;
        }
    }
    else {
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
        studentai.push_back(s);
    }

    cout << "Pasirinkite rezultata: [m]ediana arba [v]idurkis: ";
    char c; 
    cin >> c;
    Studentas::setModeMediana(c == 'm' || c == 'M');
    cout << left << setw(16) << "Pavarde" << setw(12) << "Vardas"
        << setw(16) << ((c == 'm' || c == 'M') ? "Galutinis (Med.)" : "Galutinis (Vid.)") << endl;
    cout << "----------------------------------------------" << endl;

    std::sort(studentai.begin(), studentai.end(), Studentas::comparePavarde);

    for (const auto& s : studentai) {
        cout << s << endl;
    }


    return 0;
}

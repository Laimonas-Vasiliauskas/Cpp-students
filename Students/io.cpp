#include "io.h"
#include "Studentas.h"
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>

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


vector<Studentas> readStudentsFromFile(const string& kursiokai) {
    ifstream f(kursiokai);
    if (!f) { throw std::runtime_error("Nepavyko atidaryti: " + kursiokai); }

    // Praleidžiam pirmas 1 eilute
    string dump;
    getline(f, dump);

    vector<Studentas> grupe;
    string vardas, pavarde;
    int nd1, nd2, nd3, nd4, nd5, egz;

    // Paprastas skaitymas stulpeliais
    while (f >> vardas >> pavarde >> nd1 >> nd2 >> nd3 >> nd4 >> nd5 >> egz) {
        vector<int> paz = { nd1, nd2, nd3, nd4, nd5 };
        grupe.emplace_back(vardas, pavarde, paz, egz); // konstruktorius paskai?iuoja V/M
    }
    return grupe;
}
#include "io.h"
#include "Studentas.h"
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

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


vector<Studentas> readStudentsFromFile(const string& fname) {
    ifstream f(fname);
    if (!f) { 
        throw std::runtime_error("Nepavyko atidaryti: " + fname); 
    }

    string line;
    // 1 eilutė: antraštė
    if (!std::getline(f, line)) return {};
    // 2 eilutė: brūkšniai (jei yra)
    std::streampos pos = f.tellg();
    if (f.peek() == '-') std::getline(f, line); else f.seekg(pos);


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

const std::vector<List>& student_list() {
    static const std::vector<List> data = {
        {"studentai_1k.txt",      1'000},
        {"studentai_10k.txt",    10'000},
        {"studentai_100k.txt",  100'000},
        {"studentai_1m.txt",   1'000'000},
        {"studentai_10m.txt", 10'000'000}
    };
    return data;
}

void generate_file(const std::string& filename, std::uint64_t n, std::mt19937& rng) {
    std::ofstream out(filename);
    if (!out) { 
        std::cerr << "Nepavyko atidaryti: " << filename << '\n'; return; 
    }
    std::uniform_int_distribution<int> mark(1, 10);
    out << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egzaminas\n"
        << "-------------------------------------------\n";

    for (std::uint64_t i = 1; i <= n; ++i) {
        out << "Vardas" << i << ' '
            << "Pavarde" << i << ' '
            << mark(rng) << ' ' << mark(rng) << ' ' << mark(rng) << ' ' << mark(rng) << ' ' << mark(rng) << ' '<< mark(rng) << '\n';
    }
}

void generate_all(std::mt19937& rng) {
    using clock = std::chrono::steady_clock;

    auto t_all = clock::now();

    for (const auto& job : student_list()) {
        auto t0 = clock::now();
        std::cerr << "Generuoju " << job.name << " (" << job.n << ")..." << std::flush;

        generate_file(job.name, job.n, rng);

        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - t0).count();
        std::cerr << " Sugeneruota per " << ms << " ms\n";
    }

    auto total_ms = std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - t_all).count();
    std::cerr << "Uztruko generuoti failus: " << total_ms << " ms\n";
}
void process_all_inputs(bool naudotiMediana) {
    using clock = std::chrono::steady_clock;
    auto ms_since = [](clock::time_point t0) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - t0).count();
        };

    auto T_all = clock::now();

    Studentas::setModeMediana(naudotiMediana);

    std::ofstream outN("neislaike.txt"), outI("islaike.txt");
    if (!outN || !outI) {
        std::cerr << "Nepavyko atidaryti isvesties failu.\n";
        return;
    }

    auto header = [&](std::ofstream& out) {
        out << std::left << std::setw(16) << "Pavarde"
            << std::setw(12) << "Vardas"
            << "Galutinis (" << (naudotiMediana ? "Med." : "Vid.") << ")\n"
            << "----------------------------------------------\n";
        };
    header(outN);
    header(outI);

    std::size_t cntN = 0, cntI = 0;

    long long total_read_ms = 0;
    long long total_split_ms = 0;

    for (const auto& job : student_list()) {
        try {
            auto T_read = clock::now();
            auto vec = readStudentsFromFile(job.name);
            auto read_ms = ms_since(T_read);
            total_read_ms += read_ms;
            std::cerr << "[Nuskaitymas] " << job.name << ": " << vec.size()
                << " irasu per " << read_ms << " ms\n";

            auto T_split = clock::now();

            for (const auto& s : vec) {
                double gal = naudotiMediana ? s.getRezultatasM() : s.getRezultatasV();
                if (gal < 5.0) { outN << s << '\n'; ++cntN; }
                else { outI << s << '\n'; ++cntI; }
            }
            auto split_ms = ms_since(T_split);
            total_split_ms += split_ms;
        }
        catch (const std::exception& e) {
            std::cerr << "[ERR] " << job.name << ": " << e.what() << "\n";
        }
    }

    auto total_ms = ms_since(T_all);
    std::cerr << "Sukurta: neislaike.txt = " << cntN << ", islaike.txt = " << cntI << "\n";
    std::cerr << "Suvestine: Nuskaitymas = " << total_read_ms << " ms, Irasymas = " << total_split_ms << " ms, VISO=" << total_ms << " ms\n";
}
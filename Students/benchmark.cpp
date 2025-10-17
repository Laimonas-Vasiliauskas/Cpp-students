#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>

#include "Studentas.h"
#include "io.h"

using Clock = std::chrono::steady_clock;

static inline double galutinis(const Studentas& s, bool naudotiMediana) {
    return naudotiMediana ? s.getRezultatasM() : s.getRezultatasV();
}

//========== STRATEGIJA 1 ==========
template <class Container>
static void strategija1(Container& studentai, bool naudotiMediana) {
    Container vargsiukai, kietiakiai;
    std::partition_copy(studentai.begin(), studentai.end(),
        std::back_inserter(vargsiukai),
        std::back_inserter(kietiakiai),
        [&](const Studentas& s) {
            return galutinis(s, naudotiMediana) < 5.0;
        });
}

//========== STRATEGIJA 2 ==========
template <class Container>
static void strategija2(Container& studentai, bool naudotiMediana) {
    Container vargsiukai;
    auto it = std::remove_if(studentai.begin(), studentai.end(),
        [&](const Studentas& s) {
            if (galutinis(s, naudotiMediana) < 5.0) {
                vargsiukai.insert(vargsiukai.end(), s);
                return true; 
            }
            return false;
        });
    studentai.erase(it, studentai.end());
}

// Strategija 2
static void strategija2(std::list<Studentas>& studentai, bool naudotiMediana) {
    std::list<Studentas> vargsiukai;
    for (auto it = studentai.begin(); it != studentai.end(); ) {
        if (galutinis(*it, naudotiMediana) < 5.0) {
            vargsiukai.splice(vargsiukai.end(), studentai, it++);
        }
        else {
            ++it;
        }
    }
}

//kombinacija
template <class Container>
static long long bench_one(const Container& src, bool naudotiMediana, int strategija) {
    Container work = src; 
    auto t0 = Clock::now();

    if (strategija == 1) strategija1(work, naudotiMediana);
    else                 strategija2(work, naudotiMediana);

    auto t1 = Clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
}

void runBenchmark() {
    using std::cout;
    using std::cin;
    using std::string;

    string fname;
    cout << "\n=== BENCHMARK ===\n";
    cout << "Iveskite failo pavadinima (pvz. studentai_100k.txt): ";
    cin >> fname;

    char c = 'v';
    cout << "Rezultata skaiciuoti pagal [m]ediana ar [v]idurki? ";
    cin >> c;
    bool naudotiMediana = (c == 'm' || c == 'M');

    std::vector<Studentas> base = readStudentsFromFile(fname);
    std::vector<Studentas> v(base.begin(), base.end());
    std::list<Studentas>    l(base.begin(), base.end());
    std::deque<Studentas>   d(base.begin(), base.end());

    auto print = [&](const char* name,
        long long s1, long long s2) {
            cout << name
                << " | strategija1: " << s1 << " ms"
                << " | strategija2: " << s2 << " ms\n";
        };

    cout << "\n--- Rezultatai (ms) ---\n";
    print("vector", bench_one(v, naudotiMediana, 1),
        bench_one(v, naudotiMediana, 2));
    print("list  ", bench_one(l, naudotiMediana, 1),
        bench_one(l, naudotiMediana, 2));
    print("deque ", bench_one(d, naudotiMediana, 1),
        bench_one(d, naudotiMediana, 2));

    cout << "------------------------\n\n";
}

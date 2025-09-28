#pragma once
#include <string>
#include <vector>
#include <iosfwd> 
#include <random>
#include <iomanip>
#include <iostream>

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


class Studentas {
private:
    string vardas;
    string pavarde;
    vector<int> pazymiai;
    int egzaminas = 0;
    double rezultatasV = 0.0;
    double rezultatasM = 0.0;

    static bool naudotiMediana_;

    double vidurkis();
    double mediana();

public:
    static void setModeMediana(bool m);

    string getVardas() const; 
    string getPavarde() const; 
    vector<int> getPazymiai() const;
    int getEgzaminas() const; 
    double getRezultatasV() const; 
    double getRezultatasM() const;

    // Default constructor
    Studentas();

    Studentas(string v, string p, vector<int>paz, int egzas);

    // kopijavimo konstruktorius
    Studentas(const Studentas& other);

    //kopijavimo ir priskyrimo kontruktorius
    Studentas& operator= (const Studentas& other);

    // destruktorius
    ~Studentas();
    static bool comparePavarde(const Studentas& a, const Studentas& b);

    // operatorių perkrovimas 
    friend istream& operator>>(istream& in, Studentas& s);

    // Isvedimas (perdengtas cout)
    friend ostream& operator<<(ostream& out, const Studentas& s); 

    // atsitiktiniu skaiciu generavimas
    void randomize(size_t n, unsigned seed = std::random_device{}());

};
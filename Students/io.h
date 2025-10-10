#pragma once
#include <string>
#include <vector>
#include <random>
#include <cstdint>
#include "Studentas.h"

class Studentas;

std::vector<Studentas> readStudentsFromFile(const std::string& kursiokai);

struct List { std::string name; std::uint64_t n; };

const std::vector<List>& student_list();                 
void generate_file(const std::string& filename, std::uint64_t n, std::mt19937& rng);                   
void generate_all(std::mt19937& rng); 

void process_all_inputs(bool naudotiMediana);



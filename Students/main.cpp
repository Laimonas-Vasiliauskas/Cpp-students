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
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);


    Studentas st;
    st.pasirinkimas();

    return 0;
}

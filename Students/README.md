# 🎓 C++ Students – v0.2 / v1.0

Ši programa sukurta C++ kalba, siekiant įvertinti įvairių duomenų konteinerių (`std::vector`, `std::list`, `std::deque`) efektyvumą skirstant studentų duomenis į dvi kategorijas:

- **„Neislaike“** – studentai, kurių galutinis balas < 5.0
- **„Islaike“** – studentai, kurių galutinis balas ≥ 5.0

---

## ⚙️ Funkcionalumas

✅ Generuoja 5 atsitiktinius studentų failus:

> studentai_1k.txt, studentai_10k.txt, studentai_100k.txt, studentai_1m.txt, studentai_10m.txt

✅ Nuskaito duomenis iš pasirinkto failo  
✅ Suskaičiuoja galutinį pažymį pagal **vidurkį arba medianą**  
✅ Padalina studentus į „islaike“ ir „neislaike“ kategorijas  
✅ Išveda į atskirus failus:

> `islaike.txt`, `neislaike.txt`

✅ Turi **benchmark meniu**, kuris matuoja laiką, kiek užtrunka kiekviena strategija ir konteinerio tipas.

---

## 💻 Reikalavimai

- C++17 arba naujesnė versija
- CMake ≥ 3.16
- Kompiliatorius:
  - 🪟 Windows – MSVC arba MinGW
  - 🐧 Linux – GCC arba Clang

---

## 🏗️ Įdiegimas / Build

### Unix / macOS / WSL:

```bash
git clone https://github.com/<jusu_vardas>/Cpp-students.git
cd Cpp-students
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

```

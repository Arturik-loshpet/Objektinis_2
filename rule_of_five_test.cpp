#include "funkcijos.h"

#include <cassert>
#include <iostream>
#include <type_traits>
#include <sstream>

// Uzpildo studenta pastoviais duomenimis, kad testuose butu lengva lyginti rezultatus.
void uzpildytiStudenta(VectorStudent& studentas) {
    studentas.setVardas("Jonas");
    studentas.setPavarde("Jonaitis");
    studentas.pazymiai().push_back(8);
    studentas.pazymiai().push_back(9);
    studentas.setEgzaminas(10);
    studentas.setVidurkis(9.2);
    studentas.setMediana(8.5);
}

// Patikrina, ar studento duomenys sutampa su laukiamomis reiksnemis.
void patikrintiStudenta(const VectorStudent& studentas) {
    assert(studentas.vardas() == "Jonas");
    assert(studentas.pavarde() == "Jonaitis");
    assert(studentas.pazymiai().size() == 2);
    assert(studentas.pazymiai()[0] == 8);
    assert(studentas.pazymiai()[1] == 9);
    assert(studentas.egzaminas() == 10);
    assert(studentas.vidurkis() == 9.2);
    assert(studentas.mediana() == 8.5);
}

// Tikrina numatyta konstruktoriu: ar sukurtas objektas turi tuscius/pradinius laukus.
void test_default_constructor() {
    static_assert(std::is_abstract_v<Zmogus>, "Zmogus klase privalo buti abstrakti.");

    VectorStudent studentas;

    assert(studentas.vardas().empty());
    assert(studentas.pavarde().empty());
    assert(studentas.pazymiai().empty());
    assert(studentas.egzaminas() == 0);
}

// Tikrina paveldimuma ir tai, kad Studentas veikia per abstrakcios bazes sasaja.
void test_inheritance_from_zmogus() {
    VectorStudent studentas;
    studentas.setVardas("Jonas");
    studentas.setPavarde("Jonaitis");

    Zmogus& zmogus = studentas;

    assert(zmogus.vardas() == "Jonas");
    assert(zmogus.pavarde() == "Jonaitis");
    assert(zmogus.tipas() == "Studentas");
}

// Tikrina kopijavimo konstruktoriu: ar sukuriama pilna ir nepriklausoma kopija.
void test_copy_constructor() {
    VectorStudent pirmas;
    uzpildytiStudenta(pirmas);

    VectorStudent antras(pirmas);
    patikrintiStudenta(antras);

    pirmas.setVardas("Petras");
    pirmas.pazymiai().push_back(5);

    assert(antras.vardas() == "Jonas");
    assert(antras.pazymiai().size() == 2);
}

// Tikrina perkelimo konstruktoriu: ar duomenys teisingai perkeliami i nauja objekta.
void test_move_constructor() {
    VectorStudent pirmas;
    uzpildytiStudenta(pirmas);

    VectorStudent antras(std::move(pirmas));
    patikrintiStudenta(antras);
}

// Tikrina kopijavimo priskyrima: ar vienam objektui priskyrus kita, duomenys nukopijuojami teisingai.
void test_copy_assignment() {
    VectorStudent pirmas;
    VectorStudent antras;
    uzpildytiStudenta(pirmas);

    antras = pirmas;
    patikrintiStudenta(antras);

    pirmas.setPavarde("Petraitis");
    pirmas.pazymiai().clear();

    assert(antras.pavarde() == "Jonaitis");
    assert(antras.pazymiai().size() == 2);
}

// Tikrina perkelimo priskyrima: ar duomenys teisingai perkeliami jau egzistuojanciam objektui.
void test_move_assignment() {
    VectorStudent pirmas;
    VectorStudent antras;
    uzpildytiStudenta(pirmas);

    antras = std::move(pirmas);
    patikrintiStudenta(antras);
}

// Tikrina destruktoriu: objektas sukuriamas ir sunaikinamas pasibaigus bloko sričiai.
void test_destructor() {
    {
        VectorStudent studentas;
        uzpildytiStudenta(studentas);
        assert(studentas.vardas() == "Jonas");
    }
}

// Tikrina isvesties operatoriu << : ar studento duomenys isvedami laukiamu formatu.
void test_output_operator() {
    VectorStudent studentas;
    uzpildytiStudenta(studentas);
    std::ostringstream out;

    out << studentas;

    assert(out.str() == "Jonas Jonaitis 10 2 8 9");
}

// Tikrina ivesties operatoriu >> : ar duomenys teisingai nuskaitomi is srauto i objekta.
void test_input_operator() {
    VectorStudent studentas;
    std::istringstream in("Ona Onaite 9 3 10 8 7");

    in >> studentas;

    assert(studentas.vardas() == "Ona");
    assert(studentas.pavarde() == "Onaite");
    assert(studentas.egzaminas() == 9);
    assert(studentas.pazymiai().size() == 3);
    assert(studentas.pazymiai()[0] == 10);
    assert(studentas.pazymiai()[1] == 8);
    assert(studentas.pazymiai()[2] == 7);
}

int main() {
    test_default_constructor();
    test_inheritance_from_zmogus();
    test_copy_constructor();
    test_move_constructor();
    test_copy_assignment();
    test_move_assignment();
    test_destructor();
    test_output_operator();
    test_input_operator();

    std::cout << "Visi rule of five ir operatoriu testai praejo." << std::endl;
    return 0;
}

#include "funkcijos.h"
#include "test_framework.h"

#include <sstream>
#include <type_traits>

VectorStudent sukurti_studenta() {
    return VectorStudent("Jonas", "Jonaitis", {8, 9}, 10, 9.2, 8.5);
}

bool test_rule_of_five() {
    static_assert(std::is_copy_constructible_v<VectorStudent>);
    static_assert(std::is_move_constructible_v<VectorStudent>);
    static_assert(std::is_copy_assignable_v<VectorStudent>);
    static_assert(std::is_move_assignable_v<VectorStudent>);
    static_assert(std::is_destructible_v<VectorStudent>);

    VectorStudent pirmas = sukurti_studenta();

    VectorStudent kopija(pirmas);
    CHECK(kopija.vardas() == "Jonas");
    CHECK(kopija.pazymiai().size() == 2);

    VectorStudent perkeltas(std::move(pirmas));
    CHECK(perkeltas.vardas() == "Jonas");
    CHECK(pirmas.vardas().empty());

    VectorStudent priskirtas("", "", {}, 0, 0.0, 0.0);
    priskirtas = kopija;
    CHECK(priskirtas.pavarde() == "Jonaitis");

    VectorStudent perkeltas_priskiriant("", "", {}, 0, 0.0, 0.0);
    perkeltas_priskiriant = std::move(priskirtas);
    CHECK(perkeltas_priskiriant.vardas() == "Jonas");
    CHECK(priskirtas.vardas().empty());

    return true;
}

bool test_paveldimumas() {
    VectorStudent studentas = sukurti_studenta();
    Zmogus& zmogus = studentas;

    CHECK(zmogus.vardas() == "Jonas");
    CHECK(zmogus.pavarde() == "Jonaitis");
    CHECK(zmogus.tipas() == "Studentas");

    return true;
}

bool test_operatoriai() {
    VectorStudent studentas("", "", {}, 0, 0.0, 0.0);
    std::istringstream in("Ona Onaite 9 3 10 8 7");

    in >> studentas;

    CHECK(studentas.vardas() == "Ona");
    CHECK(studentas.egzaminas() == 9);
    CHECK(studentas.pazymiai().size() == 3);

    std::ostringstream out;
    out << studentas;
    CHECK(out.str() == "Ona Onaite 9 3 10 8 7");

    return true;
}

bool test_validacija() {
    CHECK(valid_name("Ona"));
    CHECK(valid_name("Ona-Marija"));
    CHECK(!valid_name("Jonas1"));
    CHECK(validation("15") == 15);
    CHECK(validation("abc") == 0);

    return true;
}

bool test_vidurkis_mediana() {
    VectorContainer studentai;
    studentai.push_back(VectorStudent("Ona", "Onaite", {8, 10, 9}, 10, 0.0, 0.0));

    vidurkis(studentai);
    mediana(studentai);

    CHECK(studentai[0].vidurkis() == 9.6);
    CHECK(studentai[0].mediana() == 9.0);

    std::list<int> pazymiai{10, 6, 8, 4};
    CHECK(skaiciuoti_mediana(pazymiai) == 7.0);

    return true;
}

int main() {
    RUN_TEST(test_rule_of_five);
    RUN_TEST(test_paveldimumas);
    RUN_TEST(test_operatoriai);
    RUN_TEST(test_validacija);
    RUN_TEST(test_vidurkis_mediana);

    return testu_rezultatas();
}

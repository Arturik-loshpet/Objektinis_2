#include "funkcijos.h"
#include "test_framework.h"

#include <sstream>
#include <type_traits>

VectorStudent studentas() {
    return VectorStudent("Jonas", "Jonaitis", {8, 9}, 10, 9.2, 8.5);
}

TEST_CASE("Rule of Five") {
    static_assert(std::is_copy_constructible_v<VectorStudent>);
    static_assert(std::is_move_constructible_v<VectorStudent>);
    static_assert(std::is_copy_assignable_v<VectorStudent>);
    static_assert(std::is_move_assignable_v<VectorStudent>);
    static_assert(std::is_destructible_v<VectorStudent>);

    VectorStudent pradinis = studentas();

    VectorStudent kopija(pradinis);
    pradinis.setVardas("Petras");
    CHECK(kopija.vardas() == "Jonas");
    CHECK(kopija.pazymiai().size() == 2);

    VectorStudent perkeltas(std::move(pradinis));
    CHECK(perkeltas.vardas() == "Petras");
    CHECK(pradinis.vardas().empty());

    VectorStudent priskirta("", "", {}, 0, 0.0, 0.0);
    priskirta = kopija;
    kopija.setPavarde("Petraitis");
    CHECK(priskirta.pavarde() == "Jonaitis");

    VectorStudent perkeltaPriskiriant("", "", {}, 0, 0.0, 0.0);
    perkeltaPriskiriant = std::move(priskirta);
    CHECK(perkeltaPriskiriant.vardas() == "Jonas");
    CHECK(priskirta.vardas().empty());
}

TEST_CASE("Studentas per Zmogus sasaja") {
    VectorStudent s = studentas();
    Zmogus& z = s;

    CHECK(z.vardas() == "Jonas");
    CHECK(z.pavarde() == "Jonaitis");
    CHECK(z.tipas() == "Studentas");
}

TEST_CASE("Ivesties ir isvesties operatoriai") {
    VectorStudent s("", "", {}, 0, 0.0, 0.0);
    std::istringstream in("Ona Onaite 9 3 10 8 7");

    in >> s;

    CHECK(s.vardas() == "Ona");
    CHECK(s.egzaminas() == 9);
    CHECK(s.pazymiai().size() == 3);

    std::ostringstream out;
    out << s;
    CHECK(out.str() == "Ona Onaite 9 3 10 8 7");
}

TEST_CASE("Validacija") {
    CHECK(valid_name("Ona"));
    CHECK(valid_name("Ona-Marija"));
    CHECK(!valid_name("Jonas1"));
    CHECK(validation("42") == 42);
    CHECK(validation("abc") == 0);
}

TEST_CASE("Vidurkis ir mediana") {
    VectorContainer studentai;
    studentai.push_back(VectorStudent("Ona", "Onaite", {8, 10, 9}, 10, 0.0, 0.0));

    vidurkis(studentai);
    mediana(studentai);

    CHECK(studentai[0].vidurkis() == 9.6);
    CHECK(studentai[0].mediana() == 9.0);

    std::list<int> pazymiai{10, 6, 8, 4};
    CHECK(skaiciuoti_mediana(pazymiai) == 7.0);
}

int main() {
    return mini_test::run_all();
}

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "funkcijos.h"
#include "doctest.h"
#include "library.h"

VectorStudent sukurti_studenta() {
    return VectorStudent("Jonas", "Jonaitis", {8, 9}, 10, 9.2, 8.5);
}

TEST_CASE("Rule of five testas"){
    VectorStudent zmogus = sukurti_studenta();
    SUBCASE("Konstruktorius"){
        CHECK(zmogus.vardas() == "Jonas");
        CHECK(zmogus.pavarde() == "Jonaitis");
        CHECK(zmogus.pazymiai() == std::vector<int>{8, 9});
        CHECK(zmogus.egzaminas() == 10);
        CHECK(zmogus.vidurkis() == doctest::Approx(9.2));
        CHECK(zmogus.mediana() == doctest::Approx(8.5));
    }
    SUBCASE("Copy"){
        VectorStudent kopija(zmogus);
        CHECK(kopija.vardas() == "Jonas");
        CHECK(kopija.pavarde() == "Jonaitis");
        CHECK(kopija.pazymiai() == std::vector<int>{8, 9});
        CHECK(kopija.egzaminas() == 10);
        CHECK(kopija.vidurkis() == doctest::Approx(9.2));
        CHECK(kopija.mediana() == doctest::Approx(8.5));
    }
    SUBCASE("Move konstruktorius"){
        VectorStudent kopija(std::move(zmogus));
        CHECK(kopija.vardas() == "Jonas");
        CHECK(kopija.pavarde() == "Jonaitis");
        CHECK(kopija.pazymiai() == std::vector<int>{8, 9});
        CHECK(kopija.egzaminas() == 10);
        CHECK(kopija.vidurkis() == doctest::Approx(9.2));
        CHECK(kopija.mediana() == doctest::Approx(8.5));
        //destruktoriaus patikra
        CHECK(zmogus.vardas().empty());
        CHECK(zmogus.pavarde().empty());
        CHECK(zmogus.pazymiai().empty());
        CHECK(zmogus.egzaminas() == 0);
        CHECK(zmogus.vidurkis() == 0.0);
        CHECK(zmogus.mediana() == 0.0);
    }
    SUBCASE("= operatorius"){
        VectorStudent dummy("A", "b", {1, 2}, 10, 4.2, 4.3);
        dummy = zmogus;
        CHECK(dummy.vardas() == "Jonas");
        CHECK(dummy.pavarde() == "Jonaitis");
        CHECK(dummy.pazymiai() == std::vector<int>{8, 9});
        CHECK(dummy.egzaminas() == 10);
        CHECK(dummy.vidurkis() == doctest::Approx(9.2));
        CHECK(dummy.mediana() == doctest::Approx(8.5));
    }
    SUBCASE("move operatorius"){
        VectorStudent dummy("A", "b", {1, 2}, 10, 4.2, 4.3);
        dummy = std::move(zmogus);
        CHECK(dummy.vardas() == "Jonas");
        CHECK(dummy.pavarde() == "Jonaitis");
        CHECK(dummy.pazymiai() == std::vector<int>{8, 9});
        CHECK(dummy.egzaminas() == 10);
        CHECK(dummy.vidurkis() == doctest::Approx(9.2));
        CHECK(dummy.mediana() == doctest::Approx(8.5));
        //destruktoriaus patikra
        CHECK(zmogus.vardas().empty());
        CHECK(zmogus.pavarde().empty());
        CHECK(zmogus.pazymiai().empty());
        CHECK(zmogus.egzaminas() == 0);
        CHECK(zmogus.vidurkis() == 0.0);
        CHECK(zmogus.mediana() == 0.0);
    }
}

TEST_CASE("Studentas paveldi Zmogus funkcionaluma"){
    VectorStudent studentas = sukurti_studenta();
    Zmogus& zmogus = studentas;

    CHECK(zmogus.vardas() == "Jonas");
    CHECK(zmogus.pavarde() == "Jonaitis");
    CHECK(zmogus.tipas() == "Studentas");

    zmogus.setVardas("Petras");
    zmogus.setPavarde("Petraitis");

    CHECK(studentas.vardas() == "Petras");
    CHECK(studentas.pavarde() == "Petraitis");
    CHECK(studentas.egzaminas() == 10);
    CHECK(studentas.pazymiai() == std::vector<int>{8, 9});
}

TEST_CASE("Skaiciavimai"){
    VectorContainer studentai = {
        VectorStudent("A", "b", {1,2,3,4}, 10, 0.0, 0.0)
    };
    SUBCASE("Vidurkis"){
        vidurkis(studentai);
        CHECK(studentai[0].vidurkis() == doctest::Approx(7));
    }
    SUBCASE("Mediana"){
        mediana(studentai);
        CHECK(studentai[0].mediana() == doctest::Approx(2.5));
    }
}


#include "funkcijos.h"

#include <iostream>
#include <sstream>
#include <type_traits>

VectorStudent sukurti_studenta() {
    return VectorStudent("Jonas", "Jonaitis", {8, 9}, 10, 9.2, 8.5);
}

bool check(bool salyga, const std::string& zinute) {
    if (!salyga) {
        std::cout << "  Klaida: " << zinute << std::endl;
        return false;
    }
    return true;
}


bool test_rule_of_five() {
    static_assert(std::is_copy_constructible_v<VectorStudent>);
    static_assert(std::is_move_constructible_v<VectorStudent>);
    static_assert(std::is_copy_assignable_v<VectorStudent>);
    static_assert(std::is_move_assignable_v<VectorStudent>);
    static_assert(std::is_destructible_v<VectorStudent>);

    VectorStudent pirmas = sukurti_studenta();

    VectorStudent kopija(pirmas);
    if (!check(kopija.vardas() == "Jonas", "kopijavimo konstruktorius nenukopijavo vardo")) return false;
    if (!check(kopija.pazymiai().size() == 2, "kopijavimo konstruktorius nenukopijavo pazymiu")) return false;

    VectorStudent perkeltas(std::move(pirmas));
    if (!check(perkeltas.vardas() == "Jonas", "perkelimo konstruktorius neperkele vardo")) return false;
    if (!check(pirmas.vardas().empty(), "senas objektas po perkelimo nebuvo isvalytas")) return false;

    VectorStudent priskirtas("", "", {}, 0, 0.0, 0.0);
    priskirtas = kopija;
    if (!check(priskirtas.pavarde() == "Jonaitis", "kopijavimo priskyrimas nenukopijavo pavardes")) return false;

    VectorStudent perkeltas_priskiriant("", "", {}, 0, 0.0, 0.0);
    perkeltas_priskiriant = std::move(priskirtas);
    if (!check(perkeltas_priskiriant.vardas() == "Jonas", "perkelimo priskyrimas neperkele vardo")) return false;
    if (!check(priskirtas.vardas().empty(), "senas objektas po perkelimo priskyrimo nebuvo isvalytas")) return false;

    return true;
}

bool test_paveldimumas() {
    VectorStudent studentas = sukurti_studenta();
    Zmogus& zmogus = studentas;

    if (!check(zmogus.vardas() == "Jonas", "neteisingas vardas per Zmogus sasaja")) return false;
    if (!check(zmogus.pavarde() == "Jonaitis", "neteisinga pavarde per Zmogus sasaja")) return false;
    if (!check(zmogus.tipas() == "Studentas", "neteisingas tipas")) return false;

    return true;
}

bool test_operatoriai() {
    VectorStudent studentas("", "", {}, 0, 0.0, 0.0);
    std::istringstream in("Ona Onaite 9 3 10 8 7");

    in >> studentas;

    if (!check(studentas.vardas() == "Ona", "operatorius >> nenuskaite vardo")) return false;
    if (!check(studentas.egzaminas() == 9, "operatorius >> nenuskaite egzamino")) return false;
    if (!check(studentas.pazymiai().size() == 3, "operatorius >> nenuskaite pazymiu")) return false;

    std::ostringstream out;
    out << studentas;
    if (!check(out.str() == "Ona Onaite 9 3 10 8 7", "operatorius << isvede neteisinga formata")) return false;

    return true;
}

bool test_validacija() {
    if (!check(valid_name("Ona"), "vardas turetu buti tinkamas")) return false;
    if (!check(valid_name("Ona-Marija"), "vardas su bruksneliu turetu buti tinkamas")) return false;
    if (!check(!valid_name("Jonas1"), "vardas su skaiciumi turetu buti netinkamas")) return false;
    if (!check(validation("15") == 15, "tekstas '15' turetu tapti skaiciumi 15")) return false;
    if (!check(validation("abc") == 0, "neteisingas skaicius turetu grazinti 0")) return false;

    return true;
}

bool test_vidurkis_mediana() {
    VectorContainer studentai;
    studentai.push_back(VectorStudent("Ona", "Onaite", {8, 10, 9}, 10, 0.0, 0.0));

    vidurkis(studentai);
    mediana(studentai);

    if (!check(studentai[0].vidurkis() == 9.6, "neteisingai apskaiciuotas vidurkis")) return false;
    if (!check(studentai[0].mediana() == 9.0, "neteisingai apskaiciuota mediana")) return false;

    std::list<int> pazymiai{10, 6, 8, 4};
    if (!check(skaiciuoti_mediana(pazymiai) == 7.0, "neteisinga list medianos reiksme")) return false;

    return true;
}

void paleisti_testa(const std::string& pavadinimas, bool (*testas)(), int& praejo, int& nepraejo) {
    std::cout << "Vykdomas testas: " << pavadinimas << std::endl;
    if (testas()) {
        ++praejo;
        std::cout << "  OK" << std::endl;
    } else {
        ++nepraejo;
        std::cout << "  NEPRAEJO" << std::endl;
    }
}

int main() {
    int praejo = 0;
    int nepraejo = 0;

    paleisti_testa("Rule of Five", test_rule_of_five, praejo, nepraejo);
    paleisti_testa("Paveldimumas", test_paveldimumas, praejo, nepraejo);
    paleisti_testa("Operatoriai", test_operatoriai, praejo, nepraejo);
    paleisti_testa("Validacija", test_validacija, praejo, nepraejo);
    paleisti_testa("Vidurkis ir mediana", test_vidurkis_mediana, praejo, nepraejo);

    std::cout << "Praejo: " << praejo << ", nepraejo: " << nepraejo << std::endl;
    return nepraejo == 0 ? 0 : 1;
}

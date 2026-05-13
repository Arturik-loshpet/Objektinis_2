#include "vector.cpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

class TestStudent {
public:
    TestStudent(const std::string& vardas,
                const std::string& pavarde,
                const MyVector<int>& pazymiai,
                int egzaminas,
                double vidurkis,
                double mediana)
        : vardas_(vardas),
          pavarde_(pavarde),
          pazymiai_(pazymiai),
          egzaminas_(egzaminas),
          vidurkis_(vidurkis),
          mediana_(mediana) {}

    TestStudent(const TestStudent& other)
        : vardas_(other.vardas_),
          pavarde_(other.pavarde_),
          pazymiai_(other.pazymiai_),
          egzaminas_(other.egzaminas_),
          vidurkis_(other.vidurkis_),
          mediana_(other.mediana_) {}

    TestStudent(TestStudent&& other)
        : vardas_(std::move(other.vardas_)),
          pavarde_(std::move(other.pavarde_)),
          pazymiai_(std::move(other.pazymiai_)),
          egzaminas_(other.egzaminas_),
          vidurkis_(other.vidurkis_),
          mediana_(other.mediana_) {
        other.vardas_.clear();
        other.pavarde_.clear();
        other.pazymiai_.clear();
        other.egzaminas_ = 0;
        other.vidurkis_ = 0.0;
        other.mediana_ = 0.0;
    }

    TestStudent& operator=(const TestStudent& other) {
        if (this != &other) {
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
            pazymiai_ = other.pazymiai_;
            egzaminas_ = other.egzaminas_;
            vidurkis_ = other.vidurkis_;
            mediana_ = other.mediana_;
        }
        return *this;
    }

    TestStudent& operator=(TestStudent&& other) {
        if (this != &other) {
            vardas_ = std::move(other.vardas_);
            pavarde_ = std::move(other.pavarde_);
            pazymiai_ = std::move(other.pazymiai_);
            egzaminas_ = other.egzaminas_;
            vidurkis_ = other.vidurkis_;
            mediana_ = other.mediana_;

            other.vardas_.clear();
            other.pavarde_.clear();
            other.pazymiai_.clear();
            other.egzaminas_ = 0;
            other.vidurkis_ = 0.0;
            other.mediana_ = 0.0;
        }
        return *this;
    }

    ~TestStudent() = default;

    const std::string& vardas() const { return vardas_; }
    const std::string& pavarde() const { return pavarde_; }
    MyVector<int>& pazymiai() { return pazymiai_; }
    const MyVector<int>& pazymiai() const { return pazymiai_; }
    int egzaminas() const { return egzaminas_; }
    double vidurkis() const { return vidurkis_; }
    double mediana() const { return mediana_; }

    void setVardas(const std::string& vardas) { vardas_ = vardas; }
    void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }
    void setEgzaminas(int egzaminas) { egzaminas_ = egzaminas; }
    void setVidurkis(double vidurkis) { vidurkis_ = vidurkis; }
    void setMediana(double mediana) { mediana_ = mediana; }

private:
    std::string vardas_;
    std::string pavarde_;
    MyVector<int> pazymiai_;
    int egzaminas_ = 0;
    double vidurkis_ = 0.0;
    double mediana_ = 0.0;
};

std::ostream& operator<<(std::ostream& out, const TestStudent& studentas) {
    out << studentas.vardas() << " "
        << studentas.pavarde() << " "
        << studentas.egzaminas() << " "
        << studentas.pazymiai().size();

    for (int pazymis : studentas.pazymiai()) {
        out << " " << pazymis;
    }

    return out;
}

std::istream& operator>>(std::istream& in, TestStudent& studentas) {
    std::string vardas;
    std::string pavarde;
    int egzaminas = 0;
    int pazymiuKiekis = 0;

    if (!(in >> vardas >> pavarde >> egzaminas >> pazymiuKiekis)) {
        return in;
    }

    studentas.setVardas(vardas);
    studentas.setPavarde(pavarde);
    studentas.setEgzaminas(egzaminas);
    studentas.pazymiai().clear();

    for (int i = 0; i < pazymiuKiekis; ++i) {
        int pazymis = 0;
        if (!(in >> pazymis)) {
            return in;
        }
        studentas.pazymiai().push_back(pazymis);
    }

    return in;
}

TestStudent tusciasStudentas() {
    return TestStudent("", "", MyVector<int>(), 0, 0.0, 0.0);
}

void uzpildytiStudenta(TestStudent& studentas) {
    studentas.setVardas("Jonas");
    studentas.setPavarde("Jonaitis");
    studentas.pazymiai().push_back(8);
    studentas.pazymiai().push_back(9);
    studentas.setEgzaminas(10);
    studentas.setVidurkis(9.2);
    studentas.setMediana(8.5);
}

void patikrintiStudenta(const TestStudent& studentas) {
    assert(studentas.vardas() == "Jonas");
    assert(studentas.pavarde() == "Jonaitis");
    assert(studentas.pazymiai().size() == 2);
    assert(studentas.pazymiai()[0] == 8);
    assert(studentas.pazymiai()[1] == 9);
    assert(studentas.egzaminas() == 10);
    assert(studentas.vidurkis() == 9.2);
    assert(studentas.mediana() == 8.5);
}

void patikrintiTusciaStudenta(const TestStudent& studentas) {
    assert(studentas.vardas().empty());
    assert(studentas.pavarde().empty());
    assert(studentas.pazymiai().empty());
    assert(studentas.egzaminas() == 0);
    assert(studentas.vidurkis() == 0.0);
    assert(studentas.mediana() == 0.0);
}

void test_empty_constructor_values() {
    TestStudent studentas = tusciasStudentas();
    patikrintiTusciaStudenta(studentas);
}

void test_copy_constructor() {
    TestStudent pirmas = tusciasStudentas();
    uzpildytiStudenta(pirmas);

    TestStudent antras(pirmas);
    patikrintiStudenta(antras);

    pirmas.setVardas("Petras");
    pirmas.pazymiai().push_back(5);

    assert(antras.vardas() == "Jonas");
    assert(antras.pazymiai().size() == 2);
}

void test_move_constructor() {
    TestStudent pirmas = tusciasStudentas();
    uzpildytiStudenta(pirmas);

    TestStudent antras(std::move(pirmas));
    patikrintiStudenta(antras);
    patikrintiTusciaStudenta(pirmas);
}

void test_copy_assignment() {
    TestStudent pirmas = tusciasStudentas();
    TestStudent antras = tusciasStudentas();
    uzpildytiStudenta(pirmas);

    antras = pirmas;
    patikrintiStudenta(antras);

    pirmas.setPavarde("Petraitis");
    pirmas.pazymiai().clear();

    assert(antras.pavarde() == "Jonaitis");
    assert(antras.pazymiai().size() == 2);
}

void test_move_assignment() {
    TestStudent pirmas = tusciasStudentas();
    TestStudent antras = tusciasStudentas();
    uzpildytiStudenta(pirmas);

    antras = std::move(pirmas);
    patikrintiStudenta(antras);
    patikrintiTusciaStudenta(pirmas);
}

void test_destructor() {
    {
        TestStudent studentas = tusciasStudentas();
        uzpildytiStudenta(studentas);
        assert(studentas.vardas() == "Jonas");
    }
}

void test_output_operator() {
    TestStudent studentas = tusciasStudentas();
    uzpildytiStudenta(studentas);
    std::ostringstream out;

    out << studentas;

    assert(out.str() == "Jonas Jonaitis 10 2 8 9");
}

void test_input_operator() {
    TestStudent studentas = tusciasStudentas();
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
    test_empty_constructor_values();
    test_copy_constructor();
    test_move_constructor();
    test_copy_assignment();
    test_move_assignment();
    test_destructor();
    test_output_operator();
    test_input_operator();

    std::cout << "Visi MyVector rule of five ir operatoriu testai praejo." << std::endl;
    return 0;
}

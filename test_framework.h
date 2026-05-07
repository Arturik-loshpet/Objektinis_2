#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <iostream>

inline int testai_praejo = 0;
inline int testai_nepraejo = 0;

#define CHECK(salyga)                                                         \
    do {                                                                      \
        if (!(salyga)) {                                                      \
            std::cout << "  Klaida eiluteje " << __LINE__                    \
                      << ": " << #salyga << std::endl;                       \
            return false;                                                     \
        }                                                                     \
    } while (0)

#define RUN_TEST(testas)                                                       \
    do {                                                                      \
        std::cout << "Vykdomas testas: " << #testas << std::endl;             \
        if (testas()) {                                                       \
            ++testai_praejo;                                                   \
            std::cout << "  OK" << std::endl;                                 \
        } else {                                                              \
            ++testai_nepraejo;                                                 \
            std::cout << "  NEPRAEJO" << std::endl;                           \
        }                                                                     \
    } while (0)

inline int testu_rezultatas() {
    std::cout << "Praejo: " << testai_praejo
              << ", nepraejo: " << testai_nepraejo << std::endl;
    return testai_nepraejo == 0 ? 0 : 1;
}

#endif

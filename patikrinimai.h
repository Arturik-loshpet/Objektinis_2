#ifndef PATIKRINIMAI_H
#define PATIKRINIMAI_H

#include "library.h"

/**
 * @brief Patikrina, ar tekstas tinkamas vardui arba pavardei.
 * @param s Tikrinamas tekstas.
 * @return true, jei tekstas netuščias ir sudarytas tik iš raidžių arba brūkšnelio; kitu atveju false.
 */
bool valid_name(const std::string& s);

/**
 * @brief Konvertuoja tekstinę įvestį į sveikąjį skaičių.
 * @param a Tekstas, kurį bandoma konvertuoti.
 * @return Gautas sveikasis skaičius arba 0, jei konvertuoti nepavyko.
 */
int validation(const std::string& a);

/**
 * @brief Saugiai nuskaito vieną tekstinę reikšmę iš standartinės įvesties.
 * @param input Kintamasis, į kurį įrašoma nuskaityta reikšmė.
 * @return true, jei nuskaitymas pavyko; false, jei įvestis nutraukta arba įvyko klaida.
 */
bool read_input(std::string& input);

/**
 * @brief Paklausia bendro pažymių kiekio generuojamiems studentams.
 * @return Teigiamas pažymių kiekis.
 */
int paz_sk();

#endif

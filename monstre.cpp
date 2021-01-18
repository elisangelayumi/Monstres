#include "monstre.hpp"

#include <iostream>

Monstre::Monstre(const std::string& nom, unsigned int degat, unsigned int magie_rouge, unsigned int magie_bleue)
  : m_nom(nom),
    m_magie_rouge(magie_rouge),
    m_magie_bleue(magie_bleue),
    m_degat(degat)
{
}

Monstre::Monstre(const Monstre& monstre)
  : m_nom(monstre.m_nom),
    m_magie_rouge(monstre.m_magie_rouge),
    m_magie_bleue(monstre.m_magie_bleue),
    m_degat(monstre.m_degat)
{
}

const std::string& Monstre::nom() const {
  return m_nom;
}

unsigned int Monstre::degat() const {
  return m_degat;
}

unsigned int Monstre::magieRouge() const {
  return m_magie_rouge;
}

unsigned int Monstre::magieBleue() const {
  return m_magie_bleue;
}

bool Monstre::operator==(const Monstre& monstre) const {
  return (m_nom == monstre.m_nom) &&
    (m_degat == monstre.m_degat) &&
    (m_magie_rouge == monstre.m_magie_rouge) &&
    (m_magie_bleue == monstre.m_magie_bleue);
}

bool Monstre::operator!=(const Monstre& monstre) const {
  return (m_nom != monstre.m_nom) ||
    (m_degat != monstre.m_degat) ||
    (m_magie_rouge != monstre.m_magie_rouge) ||
    (m_magie_bleue != monstre.m_magie_bleue);
}

bool Monstre::operator<(const Monstre& monstre) const {
  if (m_nom < monstre.m_nom)
    return true;
  if (m_nom != monstre.m_nom)
    return false;
  if (m_degat < monstre.m_degat)
    return true;
  if (m_degat != monstre.m_degat)
    return false;
  if (m_magie_rouge < monstre.m_magie_rouge)
    return true;
  if (m_magie_rouge != monstre.m_magie_rouge)
    return false;
  return m_magie_bleue < monstre.m_magie_bleue;
}

#ifndef MONSTRE
#define MONSTRE

#include <string>

class Monstre {
private:
  std::string m_nom;
  unsigned int m_magie_rouge;
  unsigned int m_magie_bleue;
  unsigned int m_degat;
public:
  Monstre(const std::string& nom, unsigned m_degat, unsigned int magie_rouge, unsigned int magie_bleue);
  Monstre(const Monstre& monstre);

  const std::string& nom() const;
  unsigned int degat() const;
  unsigned int magieRouge() const;
  unsigned int magieBleue() const;

  bool operator==(const Monstre& monstre) const;
  bool operator!=(const Monstre& monstre) const;
  bool operator<(const Monstre& monstre)  const;
};

#endif

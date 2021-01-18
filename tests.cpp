#include "jeu.hpp"

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <string>

// Retourne la somme des degats de plusieurs monstres
// Theta(n)
unsigned int degat(const std::vector<Monstre>& monstres) {
  unsigned int degat = 0;
  for (std::vector<Monstre>::const_iterator i = monstres.begin(); i != monstres.end(); i++)
    degat += i->degat();
  return degat;
}

// Affiche les monstres d'une solution de meme que les degats
// infliges par ces monstres et l'utilisation des deux magies.
// Theta(n)
void afficheSolution(const std::vector<Monstre>& monstres) {
  unsigned int magie_rouge = 0;
  unsigned int magie_bleue = 0;
  for (std::vector<Monstre>::const_iterator i = monstres.begin(); i != monstres.end(); i++) {
    std::cout << i->nom() << ", ";
    magie_rouge += i->magieRouge();
    magie_bleue += i->magieBleue();
  }
  std::cout << "(degat = " << degat(monstres) <<
    ", rouge = " << magie_rouge <<
    ", bleue = " << magie_bleue << ")" << std::endl;
}

// Retourne vrai si solution_a_tester est une solution valide a l'instance (monstres, magie_rouge, magie_bleue).
// Une solution valide n'a pas a etre optimale.
// Theta(n log n)
bool solutionValide(std::vector<Monstre> monstres,
		     unsigned int magie_rouge,
		     unsigned int magie_bleue,
		     std::vector<Monstre> solution_a_tester) {
  std::sort(monstres.begin(), monstres.end()); // Theta(n log n)
  std::sort(solution_a_tester.begin(), solution_a_tester.end()); // Theta(n log n)

  if (!std::includes(monstres.begin(), monstres.end(),
		     solution_a_tester.begin(), solution_a_tester.end())) // O(n)
    return false;

  // Theta(n)
  unsigned int rouge = 0;
  unsigned int bleue = 0;
  for (std::vector<Monstre>::const_iterator i = solution_a_tester.begin(); i != solution_a_tester.end(); i++) {
    rouge += i->magieRouge();
    bleue += i->magieBleue();
  }
  return (rouge <= magie_rouge) && (bleue <= magie_bleue);
}

// Retourne une solution optimale au probleme.
// Theta(2^n * n log n)
std::vector<Monstre> forceBrute(const std::vector<Monstre>& monstres, unsigned int magie_rouge, unsigned int magie_bleue) {
  assert(monstres.size() <= 31); // Cette fonction ne fonctionne que pour de petites instances

  std::vector<Monstre> meilleure_solution;
  // Cette bouble s'execute 2^n fois.
  for (unsigned int mask = 0; mask < (1 << monstres.size()); mask++) {
    std::vector<Monstre> solution_courante;
    // Theta(n)
    for (unsigned int j = 0; j < monstres.size(); j++) {
      if ((1 << j) & mask) {
	solution_courante.push_back(monstres[j]);
      }
    }
    // Theta(n log n)
    if (solutionValide(monstres, magie_rouge, magie_bleue, solution_courante) &&
	(degat(solution_courante) > degat(meilleure_solution))) {
      meilleure_solution.swap(solution_courante);
    }
  }
  assert(solutionValide(monstres, magie_rouge, magie_bleue, meilleure_solution));
  return meilleure_solution;
}

// Execute un test
// Theta(2^n * n log n)
bool test(const std::string& nom_du_test, const std::vector<Monstre>& monstres, unsigned int magie_rouge, unsigned int magie_bleue) {
  std::vector<Monstre> solution = programmationDynamique(monstres, magie_rouge, magie_bleue);
  std::vector<Monstre> solution_optimale = forceBrute(monstres, magie_rouge, magie_bleue);

  if (!solutionValide(monstres, magie_rouge, magie_bleue, solution) || (degat(solution) != degat(solution_optimale))) {
      std::cout << "+0 point: Le test \"" << nom_du_test << "\" a echoue" << std::endl;
      std::cout << "  Solution attendue: ";
      afficheSolution(solution_optimale);
      std::cout << "  Solution obtenue:  ";
      afficheSolution(solution);
    } else {
      std::cout << "+1 point: Le test \"" << nom_du_test << "\" a passe" << std::endl;
      std::cout << "  Solution: ";
      afficheSolution(solution);
    }

  return false;
}

// We sure as sugar are!
//   -- Applejack
bool testPouliches() {
  Monstre pouliches[5] = {Monstre("Applejack",          2, 3, 2),
			  Monstre("Pinkie Pie",         2, 2, 3),
			  Monstre("Princesse Celestia", 4, 4, 2),
			  Monstre("Rainbow Dash",       5, 2, 4),
			  Monstre("Twilight Sparkle",   6, 4, 4)};
  return test("Les pouliches",
	      std::vector<Monstre>(pouliches, pouliches + 5),
	      6,		// Magie rouge
	      6);		// Magie bleue
}

// A Caterpie may change into a Butterfree, but the heart that beats
// inside remains the same.
//    -- Brock
bool testPokemons() {
  Monstre pokemons[5] = {Monstre("Pikachu",   6, 10, 12),
			Monstre("Caterpie",   1, 1,  2),
			Monstre("Butterfree", 3, 4,  5),
			Monstre("Brock",      5, 7,  3),
			Monstre("Steelix",    2, 6,  3)};
  return test("Les Pokemons",
	      std::vector<Monstre>(pokemons, pokemons + 5),
	      15, 		// Magie rouge
	      15);		// Magie bleue
}

// He is Conan, Cimmerian, he won't cry, so I cry for him.
//    -- Subotai
bool testConanLeBarbare() {
  Monstre conan[6] = {Monstre("Conan",       15, 0, 0),
		      Monstre("Thulsa Doom", 14, 6, 2),
		      Monstre("Roi Osric",   4,  1, 5),
		      Monstre("Valeria",     10, 2, 5),
		      Monstre("Subotai",     5,  7, 4),
		      Monstre("Crom",        20, 3, 5)};
  return test("Conan le barbare",
	      std::vector<Monstre>(conan, conan + 6),
	      10,
	      10);
}

// That's the real trouble with the world. Too many people grow up.
//    -- Walt Disney
bool testDisney() {
  Monstre disney[7] = {Monstre("Mickey",             10, 2, 4),
		       Monstre("Donald",             5,  2, 5),
		       Monstre("Pluto",              1,  0, 0),
		       Monstre("Dingo",              2,  1, 1),
		       Monstre("Picsou",             6,  3, 4),
		       Monstre("Riri, Fifi, Loulou", 5,  4, 2),
		       Monstre("Mimi",               8,  5, 1)};
  return test("Disney",
	      std::vector<Monstre>(disney, disney + 7),
	      7,
	      5);
}

// Sometimes even the wisest of men and machines can be in error.
//    -- Optimus Prime
bool testTransformers() {
  Monstre transformers[17] = {Monstre("Optimus Prime", 15, 9, 3),
			      Monstre("Steeljaw",      6,  3, 4),
			      Monstre("Thunderhoof",   5,  4, 2),
			      Monstre("Megatronus",    6,  3, 3),
			      Monstre("Fracture",      3,  1, 2),
			      Monstre("Drift",         4,  2, 2),
			      Monstre("Wind Blade",    3,  2, 2),
			      Monstre("Jazz",          1,  1, 1),
			      Monstre("Bumblebee",     5,  3, 2),
			      Monstre("Grimlock",      2,  2, 2),
			      Monstre("Unicron",       6,  5, 1),
			      Monstre("Megatron",      7,  1, 5),
			      Monstre("Galvatron",     3,  0, 3),
			      Monstre("Starscream",    4,  4, 0),
			      Monstre("Skydive",       2,  1, 2),
			      Monstre("Stalker",       2,  2, 1),
			      Monstre("Targetmaster",  3,  3, 1)};
  return test("Les transformers",
	      std::vector<Monstre>(transformers, transformers + 17),
	      16,
	      14);
}

int main(void) {
  //testPouliches();
  //testPokemons();
  testConanLeBarbare();
  //testDisney();
  //testTransformers();
  return 0;
}

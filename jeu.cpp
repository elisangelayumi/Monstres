

#include "jeu.hpp"

#include <math.h>
#include "tableau.hpp"


std::vector<Monstre> programmationDynamique(const std::vector<Monstre>& monstres, unsigned int magie_rouge, unsigned int magie_bleue) {
    // Inserez votre code ici

    unsigned int dimension[3] = {static_cast<unsigned int>((monstres.size()+1)), magie_rouge+1, magie_bleue+1};

    Tableau<unsigned int> tableauDegats(std::vector<unsigned int>(dimension, dimension + 3));

    //Condition initiale : T[0,j,k]
    for (unsigned int j=0; j < magie_rouge; j++){
        for (unsigned int k=0; k < magie_bleue; k++){
            tableauDegats.at(0,j,k) = 0;
        }
    }

    //recurrence :

    for (int i =1; i<= monstres.size(); i++){
        for (int j=0; j <= magie_rouge; j++){
            for (int k=0; k <= magie_bleue; k++){

                int monstreMagieRougeRi = monstres.at(i-1).magieRouge();
                int monstreMagieBleueBi = monstres.at(i-1).magieBleue();
                int monstreDegatDi = monstres.at(i-1).degat();

                int magieRougeSolde = j - monstreMagieRougeRi;
                int magieBleuSolde = k - monstreMagieBleueBi;

                //si j-ri >= 0 ou k - bi >= 0
                if (magieRougeSolde >= 0 && magieBleuSolde >= 0 ){
                    tableauDegats.at(i,j,k) = std::max(tableauDegats.at(i-1,j,k), monstreDegatDi + tableauDegats.at(i-1, j - monstreMagieRougeRi, k - monstreMagieBleueBi));
                }
                else{ //sinon
                    tableauDegats.at(i,j,k) = tableauDegats.at(i-1,j,k) ;
                }
            }
        }
    }

    //on cherche sur le tableau quels monstres ont été choisis. Et on les ajoute dans le vector topMonstre

    std::vector<Monstre> topMonstre ; //cree le vector que la fonction va retourner
    unsigned int magieRougeDispo = magie_rouge;
    unsigned int magieBleueDispo = magie_bleue;

    for (int i = monstres.size() ; i > 0; i--){

        if (tableauDegats.at(i, magieRougeDispo, magieBleueDispo) > tableauDegats.at(i-1, magieRougeDispo, magieBleueDispo)){
            magieRougeDispo = magieRougeDispo - monstres.at(i-1).magieRouge();
            magieBleueDispo = magieBleueDispo - monstres.at(i-1).magieBleue();
            topMonstre.push_back(monstres.at(i-1));
        }
    }

    return topMonstre;
}

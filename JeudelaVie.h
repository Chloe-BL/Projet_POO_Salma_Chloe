#include "Grille.h"
#include "Regle.h"
#include "Afficheur.h"
#include "Fichier.h"

class JeuDeLaVie {
    private:
        Grille* grille; 
        Regle* regle;
        Afficheur* afficheur;
        int nombreIterations;
    public:
        // Constructeur pour initialiser la grille, la règle et l'afficheur
        JeuDeLaVie(Grille* g, Regle* r, Afficheur* a) 
    : grille(g), regle(r), afficheur(a), nombreIterations(0) {}
        // initialiser la grille a partir d'un fichier
        void initialiserGrilleDepuisFichier(const std::string& nomFichier) {
            Fichier fichier;
            std::vector<std::vector<bool>> matrice;
            if (fichier.lireMatrice(nomFichier, matrice)) {
                grille->initialiserDepuisMatrice(matrice);
            } else {
                std::cerr << "Erreur lors de la lecture du fichier : " << nomFichier << std::endl;
            }
        }
        // executer le jeu en mode console
        void executer(int iterations) {
            for (int i = 0; i < iterations; ++i) {
                afficheur->afficher(grille);
                grille->calculerGenerationSuivante();
                grille->appliquerGenerationSuivante();
            }
        }
        // mode graphique
        void executerGraphique() {
            afficheur->afficher(grille);
        }
        // appliquer genration suivante
        void appliquerGenerationSuivante() {
            grille->calculerGenerationSuivante();
            grille->appliquerGenerationSuivante();
        }
       
    // Sauvegarder la grille dans un fichier
    void sauvegarderDansFichier(const std::string& nomFichier) {
        Fichier fichier;
        std::vector<std::vector<bool>> matrice(grille->getHauteur(), std::vector<bool>(grille->getLargeur(), false));
        for (int i = 0; i < grille->getHauteur(); ++i) {
            for (int j = 0; j < grille->getLargeur(); ++j) {
                matrice[i][j] = grille->getCellule(i, j)->getEtat()->estVivante();
            }
        }
        if (!fichier.sauvegarderMatrice(nomFichier, matrice)) {
            std::cerr << "Erreur lors de la sauvegarde dans le fichier : " << nomFichier << std::endl;
        }
    }
};
#pragma once

#include <chrono>
#include <thread>

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
        int cpt;
    public:

        // Constructeur pour initialiser la grille, la règle et l'afficheur
        JeuDeLaVie(Grille* g, Regle* r, Afficheur* a) : grille(g), regle(r), afficheur(a), nombreIterations(0) {}

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


    bool estStable() {

        int H = grille->getHauteur();
        int L = grille->getLargeur();

        // Tableau d'état avant 
        std::vector<std::vector<bool>> etatAvant(H, std::vector<bool>(L));

        // Copier la grille
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < L; j++) {
                etatAvant[i][j] = grille->getCellule(i,j)->estVivante();
            }
        }

        // Calculer la génération suivante
        grille->calculerGenerationSuivante();
        grille->appliquerGenerationSuivante();

        // Comparer
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < L; j++) {
                if (etatAvant[i][j] != grille->getCellule(i,j)->estVivante()) {
                    return false;
                }
            }
        }

        return true; // identique
    }


        // executer le jeu en mode console
        void executer(int iterations) {

            for (int i = 0; i < iterations; ++i) {
                system("clear");

                cout << "\nGénération n°" << i+1 << endl;
                
                afficheur->afficher(grille);
                sauvegarderGeneration(i);

                // Vérifier stabilité APRES avoir montré la génération actuelle
                if (estStable()) {
                    cout << "La grille est stable. Arrêt à la génération " << i+1 << endl;
                    break;
                }
                this_thread::sleep_for(chrono::milliseconds(500));
            }
        }


        // mode graphique
        void executerGraphique() {
            afficheur->afficher(grille);
            return;
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

    void sauvegarderGeneration(int numero) {
        string nom = "Etats/generation_" + to_string(numero+1) + ".txt";
        cout << "Sauvegarde de : " << nom << endl;
        sauvegarderDansFichier(nom);
    }

};

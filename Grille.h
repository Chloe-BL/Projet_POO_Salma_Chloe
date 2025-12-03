#pragma once
#include <map>
#include <vector>
#include <iostream>
using namespace std;

#include "Cellule.h"

class Grille {
private:
    vector<vector<Cellule*>> cellules; // représente l'ensemble des ccellules de la grille
    int largeur;
    int hauteur;
public:
    Grille (int l, int h) : largeur(l), hauteur(h) {
    cellules = vector<vector<Cellule*>> // création de la matrice de taille hauteur (lignes) x largeur (colonnes)
              (hauteur, // matrice avec "hauteur" nbr de lignes
              vector<Cellule*> (largeur, nullptr)); // largeur = le nombre de colonnes, contenant la valeur NULL
    }
    
    int getLargeur(){
        this -> largeur = largeur;
        return largeur;
    }

    int getHauteur() {
        this -> hauteur = hauteur;
        return hauteur;
    }

    Cellule* getCellule(int i, int j) { // retourne la cellule aux coordonnées x et y 
        return this -> cellules[i][j];
    }

    void initialiserDepuisMatrice (vector<vector<bool>> matrice) { //Remplit la grille à partir du fichier d'entrée
       
        for (int i = 0; i < hauteur ; i++) {
            for (int j = 0; j < largeur; j++) {

                // matrice initiale donnée dans le fichier 
                bool etatDeLaCellule = matrice[i][j];

                if (etatDeLaCellule){
                    cellules[i][j] = new Cellule( j, i, new EtatVivant());
                }
            
                else {
                    cellules[i][j] = new Cellule( j, i, new EtatMort());
                }
            }
        }
    }

    virtual int compterVoisinsVivants(int x, int y); // retourne le nombre de voisins vivants autour d'une cellule
    virtual void calculerGenerationSuivante(); // parcourt la grille et calcule pour chaque cellules, leur prochain état (stocker dans etatSuivant)

    void appliquerGenerationSuivante() {

    }
};

class GrilleNormale : public Grille {
public:
    int compterVoisinsVivants(int i, int j) override { 

        map <Cellule*, bool> Voisins ;

        // insertion dans la liste, de l'ensemble des voisins à une cellule donnée

        // Les 3 cases du haut
        Voisins.insert({getCellule(i-1,j-1), getCellule(i-1, j-1) -> estVivante() });
        Voisins.insert({getCellule(i-1,j), getCellule(i-1, j) -> estVivante() });
        Voisins.insert({getCellule(i-1,j+1), getCellule(i-1, j+1) -> estVivante() });

        // Les 2 cases des côtés
        Voisins.insert({getCellule(i,j-1), getCellule(i, j-1) -> estVivante() });
        Voisins.insert({getCellule(i,j+1), getCellule(i, j+1) -> estVivante() });

        // Les 3 cases d'en dessous
        Voisins.insert({getCellule(i+1,j-1), getCellule(i+1, j-1) -> estVivante() });
        Voisins.insert({getCellule(i+1,j), getCellule(i+1, j) -> estVivante() });
        Voisins.insert({getCellule(i+1,j+1), getCellule(i+1, j+1) -> estVivante() });

        // Recherche du nombre de voisins vivants
        int cpt = 0;

        for (auto& l : Voisins) {
            if (l.second){
                cpt++;
            }
            else {
                cpt = cpt;
            }
        }

        return cpt;
    }

    void calculerGenerationSuivante() override { 
        
    }
};

class GrilleTorique : public Grille {
public :
    int compterVoisinsVivants(int x, int y) override {

    }

    void calculerGenerationSuivante() override {

    }
};
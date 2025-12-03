#pragma once
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

    Cellule getCellule(int x, int y) { // retourne la cellule aux coordonnées x et y 
        
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
    int compterVoisinsVivants(int x, int y) override { 

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
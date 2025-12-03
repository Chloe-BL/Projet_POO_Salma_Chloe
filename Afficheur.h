class Afficheur {
    public:
        virtual void afficher ( Grille *grille ) = 0;
        virtual ~Afficheur() {}
};
class AfficheurConsole : public Afficheur {
    public:
        void afficher ( Grille *grille ) override {
            for (int i = 0; i < grille->getHauteur(); ++i) {
                for (int j = 0; j < grille->getLargeur(); ++j) {
                    if (grille->estVivante(i, j)) {
                        std::cout << "O ";
                    } else {
                        std::cout << ". ";
                    }
                }
                std::cout << std::endl;
            }
        }
        ~AfficheurConsole() override {}
};
class AfficheurGraphique : public Afficheur {
    public:
        void afficher ( Grille *grille ) override {
        }
        ~AfficheurGraphique() override {}
}; 
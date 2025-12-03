class Regle {
public:
    virtual bool devraitEtreAppliquee(bool etatActuel,int voisinsVivants)  = 0;
    virtual ~Regle() {}
};
class RegleConway : public Regle {
public:
    bool devraitEtreAppliquee(bool etatActuel,int voisinsVivants) override {
        if (etatActuel) {
            return (voisinsVivants == 2 || voisinsVivants == 3);
        } else {
            return (voisinsVivants == 3);
        }
    }
};
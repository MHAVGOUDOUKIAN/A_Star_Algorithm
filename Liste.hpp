#ifndef LISTE_HPP_INCLUDED
#define LISTE_HPP_INCLUDED
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////                         Classe ListeMaillon                         //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Cette classe correspond au maillon que l'on place dans la liste chaînée
template <typename type>
class ListeMaillon
{
    public:
    //  Constructeurs
        ListeMaillon(type * val):m_suiv(nullptr), m_elmt(val) {}
        ListeMaillon(ListeMaillon<type> &lam):m_suiv(nullptr), m_elmt(lam.m_elmt) {}
    
    //  Setters et Getters
        ListeMaillon<type> *getSuiv(void) const { return m_suiv; }
        virtual type* getElt(void) const { return m_elmt; }
        void setSuiv( ListeMaillon<type>* suiv) { m_suiv = suiv; }
        void setElt(type * elmt) { m_elmt = elmt; }

    //  Destructeur
        virtual ~ListeMaillon() {}

    private:
        ListeMaillon<type> * m_suiv;
        type *m_elmt;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////                             Classe Liste                             /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * ------------------------------------------------------------------------------------------
 * - Cette classe Liste est principalement conçue pour contenir des instances d'objets.
 * - Les éléments de la liste sont numérotées à partir de 1.
 * - Il est déconseillé de copier 2 listes car la méthode n'est pas encore implémentée
 * 
 * ~ LIMITATONS TECHNIQUES ~
 * - Génération de Liste => A partir de 20000 élément empiler() et depiler() deviennent trop lents.
 *  => Préferez utiliser : ajouter(1, Votre_Objet) et supprimer(1, Votre_Objet).
 * - Recherche d'un indice: même si l'indice n'existe pas, la classe vous renvoie quand même un elément
 *  => comportement aléatoire ! A EVITER !
 * 
 * 
 * ~ MISE A JOUR ~
 * - empiler()/depiler() doit être mis à jour pour règler ce problème de rapidité.
 * - Pour régler les problèmes de rapidité de certaines méthodes, la liste
 * va devenir doublement chaînée.
 * 
 * R.A.S pour les autres méthodes.
 * ------------------------------------------------------------------------------------------
 **/
template <typename type>
class Liste // Cette classe correspond à la liste chaînée qui contient le premier maillon m_first qui lui permet d'accèder aux suivants
{
    public:
    //  Constructeur
        Liste();
        Liste(const bool allowing_destruction);
        Liste(const bool allowing_destruction, const std::string name);

    // Operateur
        type&  operator[](const int i){ return *this->getEltAt(i); } // Renvoie directement l'objet stocké
        //void  operator=(const type& i){ *this = i; }

    // Methodes de base
        void empiler(type *); // Ajoute "nb_element" dans un nouveau maillon de type Objet à la fin de la liste
        void ajouter(int indice, type*); // Ajoute un élément à l'emplacement 'indice' de la liste
        void depiler(void); //retire le dernier élément de la liste
        void supprimer(int indice); // supprime l'élement à l'emplacement 'indice' de la liste
        void afficher(void);

        /** 
         *  ------------------------------------------------------------------------------------------
         *  Echange la place de deux éléments de la liste.
         * 
         *  NB:  La méthode peut encore être améliorée. Actuellement elle nécessite de parcourir 2 fois la liste.
         *  Il est possible d'exécuter la méthode en parcourant 1 seule fois la liste.
         *  ------------------------------------------------------------------------------------------
         **/
        void swap(const int ind_dep, const int ind_dest); // 
        bool isEmpty(void) const { return getFirst() == nullptr; } // renvoie true si la liste est vide (m_first == nullptr), false sinon

        /** 
         *  ------------------------------------------------------------------------------------------
         *  Renvoie un pointeur vers le maillon de la liste désigné par le paramètre 'emplacement'.
         * 
         *  NB:  Le paramètre 'emplacement' doit être comprit entre 1 (pour le 1er élément de la liste) et le nombre de maillons de la liste 
         *  sinon il renvoie automatiquement un pointeur vers le dernier maillon de la liste.
         *  ------------------------------------------------------------------------------------------
         **/
        ListeMaillon<type>* getItemAt(const int emplacement); // Renvoie un pointeur sur le maillon de la liste choisis
        
        /** 
         *  ------------------------------------------------------------------------------------------
         *  Renvoie un pointeur vers l'élément contenu dans le maillon désigné par le paramètre 'emplacement'.
         * 
         *  NB:  Le paramètre 'emplacement' doit être comprit entre 1 (pour le 1er élément de la liste) et le nombre de maillons de la liste 
         *  sinon il renvoie automatiquement un pointeur vers l'élément contenu dans le dernier maillon de la liste.
         *  ------------------------------------------------------------------------------------------
         **/
        type* getEltAt(const int emplacement); // Renvoie un pointeur sur l'element du maillon de la liste choisis
        void clear(void); // Retire tous les elements de la liste    

        void setFirst(ListeMaillon<type>* ptr) { m_first = ptr; }
        void setNbMaillon(const int nb_maillon) { m_NbMaillon = nb_maillon; }
        void setDestrElt(const bool allowing_destruction) { m_destrElt = allowing_destruction; }
        void setName(std::string name) { m_nameListe = name; }

        ListeMaillon<type>* getFirst(void) const { return m_first; }
        int getNbMaillon(void) const { return m_NbMaillon; }
        bool getDestrElt(void) { return m_destrElt; }
        std::string getName(void) { return m_nameListe; }

    // Méthodes de tri
        
    //  Destructeur
        ~Liste();

    private:
        ListeMaillon<type>* m_first;
        int m_NbMaillon;
        bool m_destrElt;
        std::string m_nameListe;
};

template <typename type>
Liste<type>::Liste() : m_first(nullptr), m_NbMaillon(0), m_destrElt(true), m_nameListe("new_list") {}

template <typename type>
Liste<type>::Liste(const bool allowing_destruction) : m_first(nullptr), m_NbMaillon(0), m_destrElt(allowing_destruction), m_nameListe("new_list") {}

template <typename type>
Liste<type>::Liste(const bool allowing_destruction, const std::string name) : m_first(nullptr), m_NbMaillon(0), m_destrElt(allowing_destruction), m_nameListe(name) {}

/*template <typename type>
type operator+(const type& ob1, const type& ob2)
{
    return ob1 + ob2;
}*/

template <typename type>
void Liste<type>::empiler(type * val)
{
    ListeMaillon<type> *newMaillon = new ListeMaillon<type>(val);
    ListeMaillon<type> *tempMaillon = m_first;

    if (isEmpty()) {
            setFirst(newMaillon);
        }
    else {
        while (tempMaillon->getSuiv() != nullptr) {
            tempMaillon = tempMaillon->getSuiv();
        }
        tempMaillon->setSuiv(newMaillon);
    }
    
    m_NbMaillon ++;
    
    return;
}

template <typename type>
void Liste<type>::ajouter(int indice, type* val)
{
    if(indice < 1) { indice = 1;}
    if(indice > this->getNbMaillon()) { indice = this->getNbMaillon() + 1;}

    ListeMaillon<type> *newMaillon = new ListeMaillon<type>(val);
    ListeMaillon<type> *tempMaillon = nullptr;
    tempMaillon = m_first;
    int maillonAct = 1;

    if (isEmpty()) {
        setFirst(newMaillon);
    }
    else {
        if(indice == 1)
        {
            newMaillon->setSuiv(m_first);
            m_first = newMaillon;        
        }
        else {
            while(tempMaillon->getSuiv() != nullptr && maillonAct != indice-1) {
                tempMaillon = tempMaillon->getSuiv();
                maillonAct++;
            }
               newMaillon->setSuiv(tempMaillon->getSuiv());
            tempMaillon->setSuiv(newMaillon);
        }
    }

    m_NbMaillon ++;

    return;
}

template <typename type>
void Liste<type>::depiler(void)
{
    ListeMaillon<type> *tempMaillon = nullptr;
    tempMaillon = m_first;

    if (!isEmpty()) {
        if (m_first->getSuiv() == nullptr) {
            if(m_destrElt == true)
            {
                delete m_first->getElt();
            }
            delete m_first;
            m_first = nullptr;
        }
        else {
            while (tempMaillon->getSuiv()->getSuiv() != nullptr) {
                tempMaillon = tempMaillon->getSuiv();
            }
            if(m_destrElt == true)
            {
                delete tempMaillon->getSuiv()->getElt();
            }
            delete tempMaillon->getSuiv();
            tempMaillon->setSuiv(nullptr);
        }
        m_NbMaillon --;
    }
    else {
        std::cout << "Liste vide" << std::endl;
    }

    return;
}

template <typename type>
void Liste<type>::supprimer(int indice)
{
    ListeMaillon<type> *tempMaillon1 = nullptr;
    ListeMaillon<type> *tempMaillon2 = nullptr;
    tempMaillon1 = m_first;
    int indicetemp = 1;

    if (!isEmpty()) {
        if(indice < 1) { indice = 1;}
        if(indice > this->getNbMaillon()) { indice = this->getNbMaillon();}

        if(indice == 1) {
            tempMaillon2 = m_first->getSuiv();
            if(m_destrElt == true) {
                delete m_first->getElt();
            }
            delete m_first;
            m_first = tempMaillon2;
        }
        else {
            while (tempMaillon1->getSuiv()->getSuiv() != nullptr && indicetemp != indice-1) {
                tempMaillon1 = tempMaillon1->getSuiv();
                indicetemp++;
            }
            if(m_destrElt == true) {
                delete tempMaillon1->getSuiv()->getElt();
            }
            tempMaillon2 = tempMaillon1->getSuiv()->getSuiv();
            delete tempMaillon1->getSuiv();
            tempMaillon1->setSuiv(tempMaillon2);
        }
        m_NbMaillon --;
    }
    else {
        std::cout << "Liste vide" << std::endl;
    }

    return;
}

template<typename type>
void Liste<type>::afficher(void)
{
    std::cout << this->getName() << std::endl << "--------- (" << this->getNbMaillon() << ")" << std::endl;
    for(int i=0; i<this->getNbMaillon(); i++) {
        std::cout << *this->getEltAt(i) << " - " << i << std::endl;
    }
    std::cout << std::endl;
}

template<typename type>
void Liste<type>::swap(const int ind_dep, const int ind_dest)
{
    if(this->getNbMaillon() >= 2 && ind_dep <= this->getNbMaillon() && ind_dest <= this->getNbMaillon() && ind_dep != ind_dest)
    {
        type* EltDest = this->getEltAt(ind_dest);

        this->getItemAt(ind_dest)->setElt(this->getEltAt(ind_dep));
        this->getItemAt(ind_dep)->setElt(EltDest);
    }
}

template <typename type>
ListeMaillon<type>* Liste<type>::getItemAt(const int emplacement)
{
    ListeMaillon<type> *tempMaillon = nullptr;
    tempMaillon = m_first;
    int maillonAct = 0;

    if(emplacement >= 0 && emplacement < this->getNbMaillon()) {
        while (tempMaillon->getSuiv() != nullptr && maillonAct != emplacement) {
            tempMaillon = tempMaillon->getSuiv();
            maillonAct++;
        }
    }
    else {
        std::cout << "Error in " << this->getName() << ": Index out of bounds(" << emplacement << ")" << std::endl;
    }

    return tempMaillon;
}

template <typename type>
type* Liste<type>::getEltAt(const int emplacement)
{
    ListeMaillon<type> *tempMaillon = nullptr;
    tempMaillon = m_first;
    int maillonAct = 0;

    if(emplacement >= 0 && emplacement < this->getNbMaillon()) {
        while (tempMaillon->getSuiv() != nullptr && maillonAct != emplacement) {
            tempMaillon = tempMaillon->getSuiv();
            maillonAct++;
        }
    }
    else {
        std::cout << "Error in " << this->getName() << ": Index out of bounds(" << emplacement << ")" << std::endl;
    }
    
    return tempMaillon->getElt();
}

template <typename type>
void Liste<type>::clear(void)
{
    ListeMaillon<type> *tmp = nullptr;
    ListeMaillon<type> *toDelete = nullptr;

    if (!isEmpty()) {
        tmp = m_first->getSuiv();
        while (tmp != nullptr) {
            toDelete = tmp->getSuiv();
            if(m_destrElt == true)
            {
                delete tmp->getElt();
            }
            delete tmp;
            tmp = toDelete;
            m_NbMaillon --;
        }
        if(m_destrElt == true)
        {
            delete m_first->getElt();
        }
        delete m_first;
        m_first = nullptr;
        m_NbMaillon --;
    }
}

template <typename type>
Liste<type>::~Liste()
{ 
    clear();
}

#endif //LISTE_HPP_INCLUDED
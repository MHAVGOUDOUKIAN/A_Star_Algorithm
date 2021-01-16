#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED
#include <fstream>
#include <iostream>
#include "Displayable.hpp"
#include <vector>

class Node : public Displayable
{
    public:
        Node(const int X, const int Y);

    // Méthodes de base
        int getX(void) const { return m_X; }
        int getY(void) const { return m_Y; }
        bool isObstacle(void) const { return m_obstacle; }
        bool isVisited(void) const { return m_visited; }
        Node * getParent(void) const { return m_parent; }
        float getGlobal(void) const { return m_global; }
        float getLocal(void) const { return m_local; }
        std::vector<Node *> & getVoisins(void) { return m_voisins; }


        void setX(const int X) {  m_X = X; }
        void setY(const int Y) { m_Y = Y; }
        void setIsObstacle(const bool status) { m_obstacle = status; }
        void setIsVisited(const bool status) { m_visited = status; }
        void setParent(Node * parent) { m_parent = parent; }
        void setGlobal(const float value) { m_global = value; }
        void setLocal(const float value) { m_local = value; }

    // Méthodes dérivées
        virtual void afficher(void) const { std::cout << m_X << m_Y;} // from Displayable

    // Surcharges d'opérateurs
        friend std::ostream & operator<<(std::ostream &flot, const Node& node)
        {
            return std::cout << node.getX() << " " << node.getY();
        }

        friend std::ostream & operator<<(std::ostream &flot, Node *node)
        {
            return std::cout << node->getX() << " " << node->getY();
        }

        friend bool operator < (const Node & lhs, const Node & rhs)
        {
            return (lhs.getGlobal() < rhs.getGlobal() ? true:false);
        }

        virtual ~Node();

    private:
        int m_X, m_Y;
        bool m_obstacle, m_visited;
        Node * m_parent;
        float m_global, m_local;
        std::vector<Node *> m_voisins; // Paramètre de destruction mit à false pour éviter des conflits lors de la libération de mémoire
};

#endif // NODE_HPP_INCLUDED

#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <math.h>
#include "Liste.hpp"
#include "Node.hpp"
#include <vector>
#include <iostream>

class Engine
{
    public:
        Engine(): m_window(sf::VideoMode(1920,1080),"Ma fenetre", sf::Style::Fullscreen), m_widthMap(48), m_heightMap(27),m_vertexA(sf::Quads, 4)
        {
            m_timePerFrame = sf::seconds(1.f/120.f);
            m_timer = sf::Time::Zero;
            m_Start = nullptr;
            m_End = nullptr ;
        }

        void run(void);
        void render(void);
        void processEvents(void);
        void update(sf::Time deltaTime);
        void handleKeyInput(sf::Keyboard::Key key, bool isPressed);
        void handleMouseInput(sf::Mouse::Button mouse, bool isPressed);

        void solve_AStar(void);

        float distance(Node& a, Node& b) { return sqrtf((a.getX() - b.getX())*(a.getX() - b.getX()) + (a.getY() - b.getY())*(a.getY() - b.getY())); }
        float distance(Node* a, Node* b) { return sqrtf((a->getX() - b->getX())*(a->getX() - b->getX()) + (a->getY() - b->getY())*(a->getY() - b->getY())); }

        ~Engine() {}

    private:
        bool Escape = false;
        bool Ctrl = false, Shift = false;
        bool MouseL = false, MouseR = false;
        sf::RenderWindow m_window;
        sf::Time m_timePerFrame;
        sf::Time m_timer;
        std::vector<Node> m_nodes;
        int m_widthMap, m_heightMap;
        sf::VertexArray m_vertexA;

        Node * m_Start;
        Node * m_End;

};

#endif // ENGINE_HPP_INCLUDED

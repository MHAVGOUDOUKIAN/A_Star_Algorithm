#include "Engine.hpp"
#include "Liste.hpp"

#define TILE_SIZE 40
#define INFINI 1000000

void Engine::run(void)
{
    // Initialisation des nodes
    for(int i = 0; i < m_heightMap; i++) {
        for(int j = 0; j < m_widthMap; j++) {
            m_nodes.push_back(Node(j,i));
        }
    }

    // Assignation des voisins (Cotés et diagonales)
    for(int i = 0; i < m_heightMap; i++) {
        for(int j = 0; j < m_widthMap; j++) {
            if(i>0) { m_nodes[i * m_widthMap + j ].getVoisins().push_back(&m_nodes[(i-1) * m_widthMap + j ]); }
            if(i<m_heightMap-1) { m_nodes[i * m_widthMap + j ].getVoisins().push_back(&m_nodes[(i+1) * m_widthMap + j ]); }
            if(j>0) { m_nodes[i * m_widthMap + j ].getVoisins().push_back(&m_nodes[i * m_widthMap + (j-1) ]); }
            if(j<m_widthMap-1) { m_nodes[i * m_widthMap + j ].getVoisins().push_back(&m_nodes[i * m_widthMap + (j+1) ]); }

            
            if(i>0 && j>0) { m_nodes[i * m_widthMap + j ].getVoisins().push_back(&m_nodes[(i-1) * m_widthMap + (j-1) ]); }
            if(i<m_heightMap-1 && j>0) { m_nodes[i * m_widthMap + j ].getVoisins().push_back(&m_nodes[(i+1) * m_widthMap + (j-1) ]); }
            if(i>0 && j<m_widthMap-1) { m_nodes[i * m_widthMap + j ].getVoisins().push_back(&m_nodes[(i-1) * m_widthMap + (j+1) ]); }
            if(i<m_heightMap-1 && j<m_widthMap-1) { m_nodes[i * m_widthMap + j ].getVoisins().push_back(&m_nodes[(i+1) * m_widthMap + (j+1) ]); }
            
        }
    }

    m_Start = &m_nodes[7*m_widthMap + 1];
    m_End = &m_nodes[7*m_widthMap + 14];

    sf::Clock clock;
    sf::Clock newClock; 

    sf::Time time = sf::Time::Zero;
    int compteurFps= 0;

    while(m_window.isOpen())
    {
        processEvents();
        m_timer += clock.restart();
        time += newClock.restart();

        while (m_timer > m_timePerFrame)
        {
            processEvents();
            m_timer -= m_timePerFrame;
            update(m_timePerFrame);
            compteurFps++;
        }

        render();
    }
}

void Engine::processEvents(void)
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::KeyPressed:
                handleKeyInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                handleKeyInput(event.key.code, false);
                break;

            case sf::Event::MouseButtonPressed:
                handleMouseInput(event.mouseButton.button, true);
                break;

            case sf::Event::MouseButtonReleased:
                handleMouseInput(event.mouseButton.button, false);
                break;

            case sf::Event::Closed:
                m_window.close();
                break;
        }
    }
}

void Engine::handleKeyInput(sf::Keyboard::Key key, bool isPressed)
{
    if(key == sf::Keyboard::LControl) { this-> Ctrl = isPressed; }
    if(key == sf::Keyboard::LShift) { this-> Shift = isPressed; }
    if(key == sf::Keyboard::Escape) { this-> Escape = isPressed; }
}

void Engine::handleMouseInput(sf::Mouse::Button mouse, bool isPressed)
{
    if(mouse == sf::Mouse::Left) { this-> MouseL = isPressed; }
    if(mouse == sf::Mouse::Right) { this-> MouseR = isPressed; }
}

void Engine::update(sf::Time deltaTime)
{
    if(Escape) { m_window.close(); }

    if(MouseL || MouseR) {

        int X = sf::Mouse::getPosition().x/TILE_SIZE;
        int Y = sf::Mouse::getPosition().y/TILE_SIZE;

        if(X >= m_widthMap) { X = m_widthMap - 1; }
        if(Y >= m_heightMap) { Y = m_heightMap - 1; }


        if(MouseL)
        {
            if(Ctrl) { 
                m_Start = &m_nodes[Y * m_widthMap + X]; 
                m_nodes[Y * m_widthMap + X].setIsObstacle(false); 
            }
            else if(Shift) { 
                m_End = &m_nodes[Y * m_widthMap + X]; 
                m_nodes[Y * m_widthMap + X].setIsObstacle(false); 
            }
            else { 
                if(m_End != &m_nodes[Y * m_widthMap + X] && m_Start != &m_nodes[Y * m_widthMap + X])
                {
                    m_nodes[Y * m_widthMap + X].setIsObstacle(true); 
                }
            }

        }
        else { m_nodes[Y * m_widthMap + X ].setIsObstacle(false); }

        solve_AStar();
    }

    m_vertexA.resize(m_heightMap * m_widthMap * 4);
    int count=0;
    for(int i = 0; i < m_heightMap; i++) {
        for(int j = 0; j < m_widthMap; j++) {
            m_vertexA[count].position = sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE);
            m_vertexA[count+1].position = sf::Vector2f((j+1) * TILE_SIZE, i * TILE_SIZE);
            m_vertexA[count+2].position = sf::Vector2f((j+1) * TILE_SIZE, (i+1) * TILE_SIZE);
            m_vertexA[count+3].position = sf::Vector2f(j * TILE_SIZE, (i+1) * TILE_SIZE);

            sf::Color color;

            if(&m_nodes[i * m_widthMap + j] == m_Start) { color = sf::Color::Green; }
            else if(&m_nodes[i * m_widthMap + j] == m_End) { color = sf::Color::Red; }
            else if(m_nodes[i * m_widthMap + j].isObstacle()) { color = sf::Color::White; }
            else if(m_nodes[i * m_widthMap + j].isVisited()) { color = sf::Color::Cyan; }
            else { color = sf::Color::Blue; }

            m_vertexA[count].color = color;
            m_vertexA[count+1].color = color;
            m_vertexA[count+2].color = color;
            m_vertexA[count+3].color = color;
            count+=4;
        }
    }

    if(m_End != nullptr)
    {
        Node * p = m_End;
        if(p->getParent() != nullptr){p = p->getParent();}
        while(p->getParent() != nullptr)
        {
            m_vertexA.append(sf::Vertex(sf::Vector2f(p->getX() * TILE_SIZE, p->getY() * TILE_SIZE ),sf::Color::Yellow));
            m_vertexA.append(sf::Vertex(sf::Vector2f((p->getX()+1) * TILE_SIZE, p->getY() * TILE_SIZE ),sf::Color::Yellow));
            m_vertexA.append(sf::Vertex(sf::Vector2f((p->getX()+1) * TILE_SIZE, (p->getY()+1) * TILE_SIZE ),sf::Color::Yellow));
            m_vertexA.append(sf::Vertex(sf::Vector2f(p->getX() * TILE_SIZE, (p->getY()+1) * TILE_SIZE ),sf::Color::Yellow));

            p = p->getParent();
        }
    }
}

void Engine::solve_AStar(void)
{
    for(int i = 0; i < m_heightMap; i++) {
        for(int j = 0; j < m_widthMap; j++) {
            m_nodes[i * m_widthMap + j].setIsVisited(false);
            m_nodes[i * m_widthMap + j].setLocal(INFINI);
            m_nodes[i * m_widthMap + j].setGlobal(INFINI);
            m_nodes[i * m_widthMap + j].setParent(nullptr);
        }
    }

    Node *nodeCurrent = m_Start;
    m_Start->setLocal(0.0f);
    m_Start->setGlobal(distance(m_Start, m_End));

    Liste<Node> notTestedNode(false, "notTestedNode");
    notTestedNode.empiler(m_Start);

    while(!notTestedNode.isEmpty() && nodeCurrent != m_End)
    {
        while(!notTestedNode.isEmpty() && notTestedNode[0].isVisited())
        {
            notTestedNode.supprimer(0);
        }

        if(!notTestedNode.isEmpty())
        {
            nodeCurrent = &notTestedNode[0];
            nodeCurrent->setIsVisited(true);

            for(int i=0; i< int(nodeCurrent->getVoisins().size()); i++)
            {
                if(!nodeCurrent->getVoisins()[i]->isVisited() && !nodeCurrent->getVoisins()[i]->isObstacle())
                {
                    notTestedNode.empiler(nodeCurrent->getVoisins()[i]);
                }


                float fPossiblyLowerGoal = nodeCurrent->getLocal() + distance(nodeCurrent, nodeCurrent->getVoisins()[i]);

                if(fPossiblyLowerGoal < nodeCurrent->getVoisins()[i]->getLocal())
                {
                    nodeCurrent->getVoisins()[i]->setParent(nodeCurrent);
                    nodeCurrent->getVoisins()[i]->setLocal(fPossiblyLowerGoal);

                    nodeCurrent->getVoisins()[i]->setGlobal(nodeCurrent->getVoisins()[i]->getLocal() + distance(nodeCurrent->getVoisins()[i], m_End));
                }
            }
        }
    }
}

void Engine::render(void)
{
    m_window.clear();
    m_window.draw(m_vertexA);
    m_window.display();
}

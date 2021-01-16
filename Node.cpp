#include "Node.hpp"

Node::Node(const int X, const int Y): m_X(X), m_Y(Y), m_obstacle(false), m_visited(false), m_parent(nullptr) {}

Node::~Node() {}

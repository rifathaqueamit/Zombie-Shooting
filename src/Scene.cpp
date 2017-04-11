#include "Scene.h"

Scene::Scene()
{
    //ctor
}

Scene::~Scene()
{
    //dtor
}

int Scene::Add_Node(Node* N)
{
    Nodes.push_back(N);
    return Nodes.size() - 1;
}

int Scene::Find_Node(Node* N)
{
    for (int i = Nodes.size() - 1; i>=0; i--)
    {
        if (Nodes[i] == N)
        {
            return i;
        }
    }
    return -1;
}

bool Scene::Find_And_Delete_Node(Node* N)
{
    for (int i = Nodes.size() - 1; i>=0; i--)
    {
        if (Nodes[i] == N)
        {

            delete Nodes[i];
            Nodes.erase(Nodes.begin()+i);

            return true;
        }
    }
    return false;
}

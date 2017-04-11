#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Node.h"

class Scene
{
    public:
        Scene();
        virtual ~Scene();

        vector<Node*> Nodes;

        int Add_Node(Node* N);
        int Find_Node(Node* N);
        bool Find_And_Delete_Node(Node* N);
    protected:

    private:
};

#endif // SCENE_H

#ifndef ENGINEV2_COMPONENTS_GAMEOBJECTCOMPONENT_H_
#define ENGINEV2_COMPONENTS_GAMEOBJECTCOMPONENT_H_

#include <string>

struct Point;

#include "enginev2/components/PrimitivesStorage.h"
#include "enginev2/models/GameObject.h"

class GameObjectComponent : public PrimitivesStorage<GameObject> {
public:
    friend class GameEngine;
    friend class CollisionDetector;
    //GameObjectComponent();
    //void init(TextureLoaderComponent&);

    void loadGameObject(const std::string& textureResourcePath, const Point&);
    void loadGameObjectSprite(const std::string& textureResourcePath, const Point&, const Rectangle&);
private:
};

#endif /* ENGINEV2_COMPONENTS_GAMEOBJECTCOMPONENT_H_ */

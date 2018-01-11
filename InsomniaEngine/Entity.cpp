#include "Entity.h"

Entity::Entity() {}

Entity::Entity(float x, float y, float z) {
	pos.x = x;
	pos.y = y;
	pos.z = z;
}
Entity::~Entity() {}

//Entity::getEntity() {
//	return Entity;
//}

void Entity::draw(LPDIRECT3DDEVICE9 device) {

}
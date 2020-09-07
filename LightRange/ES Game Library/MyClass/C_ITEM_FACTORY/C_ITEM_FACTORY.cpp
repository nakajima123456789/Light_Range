#include "C_ITEM_FACTORY.h"

Object* CItemFactory::Create(std::string _type, Vector3 _position) 
{
	Object* object = CreateProduct(_type, _position);
	return object;
}

Object* ItemStationeryFactory::CreateProduct(std::string _type, Vector3 _position)
{
	if (_type == "アイテム") { return new CItemBook(_position); }
	ASSERT(FALSE && !"アイテムの名前が違う!");
}


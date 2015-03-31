#pragma once

#include <vector>
#include <array>
#include <iostream>
#include "SFML/System/Time.hpp"
#include "Component.h"

using std::string;
using std::vector;
using std::array;
using std::unique_ptr;
using std::bitset;
using std::move;
using std::cerr;
using std::endl;

namespace S2D{
#define MAX_COMPONENTS 64
	static int currentId;

	class Component;
	class EntityManager;
	
	class Entity{
		friend class EntityManager;
	private:
		int id;
		bitset<MAX_COMPONENTS> componentBitset;
		string name;

		vector<unique_ptr<Component>> components;
		//Component* componentArray[MAX_COMPONENTS];
		array<Component*, MAX_COMPONENTS> componentArray;

		Entity(string name);

	public:
		//The next 3 functions are from Vittorio Romeo. https://www.youtube.com/watch?v=QAmtgvwHInM
		template<class T>
		bool hasComponent(){
			return componentBitset[getComponentTypeID<T>()];
		}

		template<class T, typename... args>
		T& addComponent(args&&... componentArgs){
			assert(!hasComponent<T>());

			T* component(new T(forward<args>(componentArgs)...));
			unique_ptr<Component> uniqueComponentPtr{component};
			components.emplace_back(move(uniqueComponentPtr));
			size_t componentID = getComponentTypeID<T>();
			componentArray[componentID] = component;
			componentBitset[componentID] = true;

			component->setOwner(this);
			component->init();
			return *component;
		}

		template<class T>
		T& getComponent(){
			assert(hasComponent<T>());
			auto componentPtr(componentArray[getComponentTypeID<T>()]);
			return *static_cast<T*>(componentPtr);
		}

		void onStart();
		bool update(sf::Time frameTime);
		void draw(sf::RenderTarget& target);

		const int getId();
		const string getName();
	};

}

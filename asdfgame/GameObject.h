#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <string>
#include <iostream>

using namespace std;

class GameObject {
	private:
		string m_name;

	public:
		GameObject(string name);
		~GameObject();

		virtual ostream& print(ostream &stream);

		// getters
		string getName();

		// setters
		void setName(string name);
};

ostream& operator<<(ostream &stream, GameObject &gameObject);
glm::mat4 getProjMatrix();

#endif
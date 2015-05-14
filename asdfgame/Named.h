#ifndef NAMED_H
#define NAMED_H

#include <string>

using namespace std;

class Named {
	private:
		string m_name;

	public:
		Named(string name);

		// getters
		string getName();

		// setters
		void setName(string name);
};

#endif
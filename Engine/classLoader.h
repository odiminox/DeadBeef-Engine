#include "IclassBaseManager.h"

template<typename T>
class classLoader: public IclassBaseManager
{
private:

public:
	std::vector<T> vecClass;
	std::vector<int> VecId;

	void removeClass();
	void removeAllClasses();
    int classID()
	{
		static const int id = reinterpret_cast<int>(typeid(T).name());
		return id;
	}
	const char* pGetClassName()
	{
		return typeid(T).name();
	}

	void addClass()
	{
		classID();
		VecId.push_back(classID());
	}
};

//////////////////////////////////////////////////////////////////////
//Needs to be moved into new class manager away core class behaviors.
//////////////////////////////////////////////////////////////////////

//Choose which class to remove
template<typename T> void classLoader<T>::removeClass()
{
	//TO DO: add code so we can parse in a class object, the location in the vector found and then it's removed
	vecClass.erase(vecClass.begin( ) +  this->classID());
}
//Nuke the vector
template<typename T> void classLoader<T>::removeAllClasses()
{
	for(count = 0; count < VecId.size(); ++count) {
		VecId.erase(VecId.begin( ) + iterator);

		for(iterator = 0; iterator < vecClass.size(); ++count) {
			vecClass.erase(vecClass.begin( ) + iterator);
		}
	}
}
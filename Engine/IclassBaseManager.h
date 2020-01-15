static const int id;
static const char* name;

#include <vector>

class IclassBaseManager
{
private:
public:
	static std::vector<int> VecId;//Contains the ids of all the objects in the game

	virtual void addClass() = 0;
	virtual int classID() = 0;
	virtual const char* pGetClassName() = 0;
};
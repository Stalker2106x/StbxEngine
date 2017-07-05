/*!
* @file      Resolver.hh
* @brief     Resource resolving utility: get resource of given type by its name
*
*            This static class provide a resource resolver.
*            It generates the resource loaded in Data folder of name name. 
*            Its type and thereforeits path are deducted from the typename T.
*/

#ifndef RESOLVER_HH_
#define RESOLVER_HH_

#include <SFML/Graphics.hpp>

class Resolver
{
public:
	template <class T>
	static T *resolve(const std::string &name)
	{
		std::string path = "./Data/";
		T *obj = new T();

		if (std::is_same<T, sf::Font>::value)
			obj->loadFromFile(path+"font/"+name+".ttf");
		else
			return (NULL);
		return (obj);
	}

private:
};

#endif /* !RESOLVER_HH_ */
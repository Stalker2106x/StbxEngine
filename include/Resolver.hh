/*!
* @file      Resolver.hh
* @class     stb::Resolver
* @brief     Resource resolving utility: get resource of given type by its name
*
*            This static class provide a resource resolver.
*            It generates the resource loaded in Data folder of name name. 
*            Its type and thereforeits path are deducted from the typename T.
*/

#ifndef RESOLVER_HH_
#define RESOLVER_HH_

#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace stb {

	template <typename T>
	class Resolver
	{
	public:
		static T *resolve(const std::string &name, bool unique = false)
		{
			if (!unique && resources.find(name) != resources.end())
				return (resources[name]);
			std::string path = "./Data/";
			T *obj = new T();

			if (std::is_same<T, sf::Font>::value)
				obj->loadFromFile(path + "font/" + name + ".ttf");
			else if (std::is_same<T, sf::Texture>::value)
				obj->loadFromFile(path + "texture/" + name + ".png");
			else
			{
				//Engine::instance->console->output(COLOR_ERROR, "Error: Resolver: Resource of id \"" + name + "\" not found"); //Should be implemented, cannot because of cross-inc.
				return (NULL);
			}
			if (!unique)
				resources.emplace(name, obj);
			return (obj);
		}

		static std::unordered_map<std::string, T *> resources;
	};

}

#endif /* !RESOLVER_HH_ */

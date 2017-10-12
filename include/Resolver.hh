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

	class GUIScreen; //Forward

	template <typename T>
	class Resolver
	{
	public:
		static T *resolve(const std::string &name, const std::string &location = "", bool unique = false)
		{
			if (!unique && resources.count(name))
				return (resources[name]);
			std::string path = "./Data/";
			T *obj = new T();

			if (!location.empty())
			{
				obj->loadFromFile(location + name);
			}
			else
			{
				if (std::is_same<T, sf::Font>::value)
					obj->loadFromFile(path + "font/" + name + ".ttf");
				else if (std::is_same<T, sf::Texture>::value)
					obj->loadFromFile(path + "texture/" + name + ".png");
				else if (std::is_same<T, GUIScreen>::value)
					obj->loadFromFile(path + "screen/" + name + ".xml");
				else
					return (NULL); //Unhandled
			}
			if (!unique)
				resources.emplace(name, obj);
			return (obj);
		}

		static bool exists(const std::string &name)
		{
			return (resources.count(name));
		}

		static std::unordered_map<std::string, T *> resources;
	};

}

#endif /* !RESOLVER_HH_ */

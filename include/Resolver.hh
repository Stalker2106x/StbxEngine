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
	class SFResolver
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
				path = location;
			}
			if (std::is_same<T, sf::Font>::value)
			{
				if (location.empty()) path += "font/";
				obj->loadFromFile(path + name + ".ttf");
			}
			else if (std::is_same<T, sf::Texture>::value)
			{
				if (location.empty()) path += "texture/";
				obj->loadFromFile(path + name + ".png");
			}
			else
				return (NULL); //Unhandled
			if (!unique)
			{
				resources.emplace(name, obj);
			}
			return (obj);
		}

		static bool exists(const std::string &name)
		{
			return (resources.count(name));
		}

		static std::unordered_map<std::string, T *> resources;
	};

	template <typename T>
	class STBResolver
	{
	public:
		static T *resolve(const std::string &name, const std::string &location = "", const std::string &elem = "", bool unique = false)
		{
			if (!unique && resources.count(name))
				return (resources[name]);
			std::string path = "./Data/";
			T *obj = new T();

			if (!location.empty())
			{
				path = location;
			}
			if (std::is_same<T, GUIScreen>::value)
			{
				if (location.empty()) path += "screen/";
				obj->loadFromFile(path + name + ".xml", elem);
			}
			else
				return (NULL); //Unhandled
			if (!unique)
			{
				if (elem.empty())
					resources.emplace(name, obj);
				else
					resources.emplace(elem, obj);
			}
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

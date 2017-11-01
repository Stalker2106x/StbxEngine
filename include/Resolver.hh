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

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

namespace stb {

	class GUIScreen; //Forward

	template <typename T>
	class Resolver
	{
	public:
		Resolver() {};
		virtual ~Resolver();

		static void addLocation(const std::string &path)
		{
			locations.push_back((path.back() == '/' ? path : path + "/"));
		}

		static void insert(const std::string &name, T *resource)
		{
			resources.emplace(name, resource);
		}

		static bool exists(const std::string &name)
		{
			return (resources.count(name));
		}

	protected:
		static std::vector<std::string> locations;
		static std::unordered_map<std::string, T *> resources;
	};

	template <typename T>
	class SFResolver : public Resolver<T>
	{
	public:
		static T *resolve(const std::string &name, const std::string &location = "", bool unique = false)
		{
			if (!unique && resources.count(name))
				return (resources[name]);
			T *obj = new T();
			bool status = false;

			for (size_t i = 0; !status && location.empty() && i < locations.size(); i++)
			{
				if (std::is_same<T, sf::Font>::value)
				{
					status = obj->loadFromFile(locations[i] + name + ".ttf");
				}
				else if (std::is_same<T, sf::Texture>::value)
				{
					status = obj->loadFromFile(locations[i] + name + ".png");
				}
				else
					return (NULL); //Unhandled
			}
			if (!unique)
			{
				resources.emplace(name, obj);
			}
			return (obj);
		}

	};

	template <typename T>
	class STBResolver : public Resolver<T>
	{
	public:
		static T *resolve(const std::string &name, const std::string &location = "", const std::string &elem = "", bool unique = false)
		{
			if (!unique && resources.count(name))
				return (resources[name]);
			T *obj = new T();
			bool status = false;

			for (size_t i = 0; !status && location.empty() && i < locations.size(); i++)
			{
				if (std::is_same<T, GUIScreen>::value)
				{
					status = obj->loadFromFile(locations[i] + name + ".xml", elem);
				}
				else
					return (NULL); //Unhandled
			}
			if (!unique)
			{
				if (elem.empty())
					resources.emplace(name, obj);
				else
					resources.emplace(elem, obj);
			}
			return (obj);
		}
	};

}

#endif /* !RESOLVER_HH_ */

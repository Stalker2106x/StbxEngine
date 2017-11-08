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
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>

namespace stb {

	class GUIScreen; //Forward

	template <typename T>
	class Resolver
	{
	public:
		Resolver() {};
		virtual ~Resolver() {};

		static void addLocation(const std::string &path)
		{
			locations.push_back((path.back() == '/' ? path : path + '/'));
		}

		static void insert(const std::string &name, std::shared_ptr<T> resource)
		{
			resources.emplace(name, resource);
		}

		static bool exists(const std::string &name)
		{
			return (resources.count(name));
		}

	protected:
		static std::vector<std::string> locations;
		static std::map<std::string, std::shared_ptr<T>> resources;
	};

	template <typename T>
	class SFResolver : public Resolver<T>
	{
	public:
		static std::shared_ptr<T> resolve(const std::string &name, const std::string &location = "", bool unique = false)
		{
			if (!unique && resources.count(name))
				return (resources[name]);
			std::shared_ptr<T> obj = std::make_shared<T>();
			bool status = false;

			if (!location.empty())
			{
				if (!load(obj, name, location))
					return (NULL);
				return (obj);
			}
			for (size_t i = 0; !status && i < locations.size(); i++)
			{
				status = load(obj, name, locations[i]);
			}
			if (!unique)
			{
				resources.emplace(name, obj);
			}
			return (obj);
		}

		static bool load(std::shared_ptr<T> obj, const std::string &name, const std::string &location)
		{
			if (std::is_same<T, sf::Font>::value)
			{
				return (obj->loadFromFile(location + name + ".ttf"));
			}
			else if (std::is_same<T, sf::Texture>::value)
			{
				return (obj->loadFromFile(location + name + ".png"));
			}
			else
				return (false); //Unhandled
		}
	};

	template <typename T>
	class STBResolver : public Resolver<T>
	{
	public:
		static std::shared_ptr<T> resolve(const std::string &elem, const std::string &name = "", const std::string &location = "", bool unique = false)
		{
			if (!unique && resources.count(elem))
				return (resources[elem]);
			std::shared_ptr<T> obj = NULL;

			if (!location.empty())
			{
					obj = load(name, location, elem);
				return (obj);
			}
			for (size_t i = 0; obj == NULL && i < locations.size(); i++)
			{
				if (name.empty())
					obj = load(elem, locations[i], elem); //we try to retrieve it with elem name
				else
					obj = load(name, locations[i], elem);
			}
			if (!unique)
			{
				resources.emplace(elem, obj);
			}
			return (obj);
		}

		static std::shared_ptr<T> load(const std::string &name, const std::string &location, const std::string &elem = "")
		{
			if (std::is_same<T, GUIScreen>::value)
			{
				return (T::loadFromFile(location + name + ".xml", elem));
			}
			else
				return (false); //Unhandled
		}
	};

}

#endif /* !RESOLVER_HH_ */

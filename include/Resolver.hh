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
	
	enum ResolverType {
		RTexture,
		RMusic,
		RSound
	};

	inline bool file_exists(const std::string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}

	template <typename T>
	class SFResolver
	{
	public:
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

		static std::shared_ptr<T> resolve(const std::string &name, const std::string &location = "", bool unique = false)
		{
			if (!unique && exists(name))
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
	private:
		static std::vector<std::string> locations;
		static std::map<std::string, std::shared_ptr<T>> resources;
	};

	template <ResolverType>
	class PathResolver
	{
	public:
		static void addLocation(const std::string &path)
		{
			locations.push_back((path.back() == '/' ? path : path + '/'));
		}

		static void insert(const std::string &name, std::string resource)
		{
			resources.emplace(name, resource);
		}

		static bool exists(const std::string &name)
		{
			return (resources.count(name));
		}

		static const std::string &resolve(const std::string &name)
		{
			if (!unique && resources.count(elem))
				return (resources[elem]);
			for (size_t i = 0; i < locations.size(); i++)
			{
					if (file_exists(locations[i] + name))
					{
						resources.emplace(name, locations[i] + name);
						return (resources[name]);
					}
			}
			return ("");
		}

	private:
		static std::vector<std::string> locations;
	};

}

#endif /* !RESOLVER_HH_ */

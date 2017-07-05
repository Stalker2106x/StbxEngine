#ifndef RESOLVER_HH_
#define RESOLVER_HH_

#include <SFML/Graphics.hpp>

class Resolver
{
public:
	template <class T>
	static void resolve(T &resource, const std::string &name);

private:
};

#endif /* !RESOLVER_HH_ */
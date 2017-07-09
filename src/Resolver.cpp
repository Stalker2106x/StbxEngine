#include "Resolver.hh"

template <>
std::unordered_map<std::string, sf::Font *> Resolver<sf::Font>::resources = std::unordered_map<std::string, sf::Font *>();

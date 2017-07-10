#include "Resolver.hh"

template <>
std::unordered_map<std::string, sf::Font *> Resolver<sf::Font>::resources = std::unordered_map<std::string, sf::Font *>();
template <>
std::unordered_map<std::string, sf::Texture *> Resolver<sf::Texture>::resources = std::unordered_map<std::string, sf::Texture *>();

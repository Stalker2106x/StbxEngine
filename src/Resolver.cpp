#include "Resolver.hh"

using namespace stb;

template <>
std::unordered_map<std::string, sf::Font *> Resolver<sf::Font>::resources = std::unordered_map<std::string, sf::Font *>();
template <>
std::unordered_map<std::string, sf::Texture *> Resolver<sf::Texture>::resources = std::unordered_map<std::string, sf::Texture *>();
template <>
std::unordered_map<std::string, GUIScreen *> Resolver<GUIScreen>::resources = std::unordered_map<std::string, GUIScreen *>();

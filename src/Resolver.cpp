#include "Resolver.hh"

using namespace stb;

template <>
std::unordered_map<std::string, sf::Font *> SFResolver<sf::Font>::resources = std::unordered_map<std::string, sf::Font *>();
template <>
std::unordered_map<std::string, sf::Texture *> SFResolver<sf::Texture>::resources = std::unordered_map<std::string, sf::Texture *>();
template <>
std::unordered_map<std::string, GUIScreen *> STBResolver<GUIScreen>::resources = std::unordered_map<std::string, GUIScreen *>();

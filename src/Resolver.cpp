#include "Resolver.hh"

using namespace stb;

template <>
std::vector<std::string> Resolver<sf::Font>::locations = std::vector<std::string>();
template <>
std::vector<std::string> Resolver<sf::Texture>::locations = std::vector<std::string>();
template <>
std::vector<std::string> Resolver<GUIScreen>::locations = std::vector<std::string>();

template <>
std::map<std::string, sf::Font *> Resolver<sf::Font>::resources = std::map<std::string, sf::Font *>();
template <>
std::map<std::string, sf::Texture *> Resolver<sf::Texture>::resources = std::map<std::string, sf::Texture *>();
template <>
std::map<std::string, GUIScreen *> Resolver<GUIScreen>::resources = std::map<std::string, GUIScreen *>();

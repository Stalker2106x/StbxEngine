#include "Resolver.hh"

using namespace stb;

template <>
std::vector<std::string> SFResolver<sf::Font>::locations = std::vector<std::string>();
template <>
std::vector<std::string> SFResolver<sf::Texture>::locations = std::vector<std::string>();
template <>
std::vector<std::string> PathResolver<RTexture>::locations = std::vector<std::string>();
template <>
std::vector<std::string> PathResolver<RSound>::locations = std::vector<std::string>();

template <>
std::map<std::string, std::shared_ptr<sf::Font>> SFResolver<sf::Font>::resources = std::map<std::string, std::shared_ptr<sf::Font>>();
template <>
std::map<std::string, std::shared_ptr<sf::Texture>> SFResolver<sf::Texture>::resources = std::map<std::string, std::shared_ptr<sf::Texture>>();

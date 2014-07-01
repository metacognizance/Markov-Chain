#pragma once
#include "Matrix.h"
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Font.hpp>
#include "GeneralMath.h"

template <typename Identifier, typename Value>class Chain : public sf::Drawable
{
public:
	Chain();
	~Chain();

	void Increment(const unsigned int & p_amount);

	std::map<Identifier, Value> m_state;

	Matrix<Identifier, Value> m_probabilityMatrix;

	void SetPosition();

private:
	void draw(sf::RenderTarget & p_target, sf::RenderStates p_states) const;

	std::map<Identifier, sf::Vector2<float>> m_nodes;

	void GetHighest();

	Value m_high;

	sf::Texture m_texture;

	sf::Sprite m_nodeSprite;

	sf::Font m_font;
};
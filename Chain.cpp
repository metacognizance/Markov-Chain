#include "Chain.h"

template <typename Identifier, typename Value>
Chain<Identifier, Value>::Chain()
{
	m_font.loadFromFile("SourceCodePro-Regular.ttf");

	m_texture.loadFromFile("Node.png");
	m_nodeSprite.setTexture(m_texture);
}

template <typename Identifier, typename Value>
Chain<Identifier, Value>::~Chain()
{

}

template <typename Identifier, typename Value>
void Chain<Identifier, Value>::Increment(const unsigned int & p_amount)
{
	Matrix<Identifier, Value> state;

	for (auto it = m_state.begin(); it != m_state.end(); ++it)
	{
		state.SetValue(' ', it->first, ' ');
	}

	m_state.clear();

	for (int i = 0; i < p_amount; i++)
	{
		state = state * m_probabilityMatrix;
	}

	for (int i = 0; i < state.GetRows().size(); ++i)
	{
		m_state[state.GetRows()[i]] = state.GetValue(state.GetRows()[i], ' ');
	}
}

template <typename Identifier, typename Value>
void Chain<Identifier, Value>::GetHighest()
{
	m_high = 0;
	for (auto it = m_state.begin(); it != m_state.end(); ++it)
	{
		if (it->second > m_high)
		{
			m_high = it->second;
		}
	}
}

template <typename Identifier, typename Value>
void Chain<Identifier, Value>::SetPosition()
{
	m_nodes.clear();

	GetHighest();

	for (auto it = m_state.begin(); it != m_state.end(); ++it)
	{
		sf::Vector2<float> position;

		float angle = math::random(0, 360);

		angle = math::toRadians(angle);

		float radius = 310 - (310/m_high)*it->second;

		position.x = std::cos(angle)*radius + 320;
		position.y = std::sin(angle)*radius + 320;

		m_nodes[it->first] = position;
	}
}

template <typename Identifier, typename Value>
void Chain<Identifier, Value>::draw(sf::RenderTarget & p_target, sf::RenderStates p_states) const
{

}

Chain<char, float>::Chain()
{
	m_font.loadFromFile("SourceCodePro-Regular.ttf");

	m_texture.loadFromFile("Node.png");
	m_nodeSprite.setTexture(m_texture);
}

void Chain<char, float>::Increment(const unsigned int & p_amount)
{
	Matrix<char, float> state;

	for (auto it = m_state.begin(); it != m_state.end(); ++it)
	{
		state.SetValue(' ', it->first, it->second);
	}

	m_state.clear();

	std::vector<char> rows = state.GetRows(), columns = state.GetColumns();

	for (int i = 0; i < p_amount; i++)
	{
		state = state * m_probabilityMatrix;

		rows = state.GetRows(), columns = state.GetColumns();
	}

	columns = state.GetColumns();

	for (int i = 0; i < columns.size(); ++i)
	{
		m_state[columns[i]] = state.GetValue(' ', columns[i]);
	}

	SetPosition();
}

void Chain<char, float>::draw(sf::RenderTarget & p_target, sf::RenderStates p_states) const
{
	sf::VertexArray lines;
	lines.setPrimitiveType(sf::PrimitiveType::Lines);

	sf::Sprite sprite = m_nodeSprite;

	for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
	{
		sprite.setPosition(sf::Vector2<float>(it->second.x - 10, it->second.y - 10));
		p_target.draw(sprite);

		lines.append(sf::Vertex(it->second));

		for (auto iter = m_nodes.begin(); iter != m_nodes.end(); ++iter)
		{
			lines.append(sf::Vertex(iter->second));
		}
	}

	p_target.draw(lines);
}

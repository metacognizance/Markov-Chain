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
void Chain<Identifier, Value>::GetHighestIdentifier()
{
	m_highIdentifier = NULL;
	for (auto it = m_state.begin(); it != m_state.end(); ++it)
	{
		if (it->first > m_highIdentifier)
		{
			m_highIdentifier = it->first;
		}
	}
}

template <typename Identifier, typename Value>
void Chain<Identifier, Value>::SetPosition()
{
	m_nodes.clear();

	GetHighest();
	GetHighestIdentifier();

	for (auto it = m_state.begin(); it != m_state.end(); ++it)
	{
		sf::Vector2<float> position;

		float angle = (360/m_highIdentifier*(std::pow(m_state.size(), 2)))*it->first;

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
	sf::VertexArray lines;
	lines.setPrimitiveType(sf::PrimitiveType::Lines);

	sf::Sprite sprite = m_nodeSprite;

	sf::Text text;
	text.setFont(m_font);

	text.setScale(0.5f, 0.5f);

	for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
	{
		sprite.setPosition(sf::Vector2<float>(it->second.x - 10, it->second.y - 10));
		p_target.draw(sprite);

		text.setPosition(sf::Vector2<float>(it->second.x + 8, it->second.y + 8));
		text.setString(it->first);

		for (auto iter = m_nodes.begin(); iter != m_nodes.end(); ++iter)
		{
			lines.append(sf::Vertex(it->second));
			lines.append(sf::Vertex(iter->second));
		}

		p_target.draw(text);

		char* str = new char[30];
		std::sprintf(str, "%.4g", (m_state.find(it->first)->second));

		text.setPosition(sf::Vector2<float>(it->second.x - 32, it->second.y - 32));

		text.setString(str);

		p_target.draw(text);

		delete str;
	}

	p_target.draw(lines);
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

	sf::Text text;
	text.setFont(m_font);

	text.setScale(0.5f, 0.5f);

	for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
	{
		sprite.setPosition(sf::Vector2<float>(it->second.x - 10, it->second.y - 10));
		p_target.draw(sprite);

		text.setPosition(sf::Vector2<float>(it->second.x + 8, it->second.y + 8));
		text.setString(it->first);
		
		p_target.draw(text);

		char* str = new char[30];
		std::sprintf(str, "%.4g", (m_state.find(it->first)->second));

		text.setPosition(sf::Vector2<float>(it->second.x - 32, it->second.y - 32));

		text.setString(str);

		p_target.draw(text);

		delete str;
	}

	std::vector<char> probabilityMatrixRows = m_probabilityMatrix.GetRows(), probabilityMatrixColumns = m_probabilityMatrix.GetColumns();
	std::vector<std::string> combinations;

	for (int i = 0; i < probabilityMatrixRows.size()*probabilityMatrixColumns.size(); ++i)
	{
		char from = m_probabilityMatrix.GetCoord(i).m_row;
		char to = m_probabilityMatrix.GetCoord(i).m_column;

		lines.append(sf::Vertex(m_nodes.find(from)->second));
		lines.append(sf::Vertex(m_nodes.find(to)->second));

		char* first = new char[30];
		char* second = new char[30];

		std::sprintf(first, "%.4g", (m_probabilityMatrix.GetValue(from, to)));
		std::sprintf(second, "%.4g", (m_probabilityMatrix.GetValue(to, from)));

		std::string string = (std::string)first + ":" + (std::string)second;

		bool found = false;

		for (int j = 0; j < combinations.size(); ++j)
		{
			if (combinations[j] == (std::string((std::string)second + ":" + (std::string)first)))
			{
				found = true;
				break;
			}
		}

		if (!found)
		{
			text.setString(string);
			text.setPosition(sf::Vector2<float>((m_nodes.find(from)->second.x < m_nodes.find(to)->second.x ? m_nodes.find(from)->second.x:m_nodes.find(to)->second.x) + (((m_nodes.find(from)->second.x > m_nodes.find(to)->second.x) ? (m_nodes.find(from)->second.x - m_nodes.find(to)->second.x):(m_nodes.find(to)->second.x - m_nodes.find(from)->second.x))/2) - 16, (m_nodes.find(from)->second.y < m_nodes.find(to)->second.y ? m_nodes.find(from)->second.y:m_nodes.find(to)->second.y) + (((m_nodes.find(from)->second.y > m_nodes.find(to)->second.y) ? (m_nodes.find(from)->second.y - m_nodes.find(to)->second.y):(m_nodes.find(to)->second.y - m_nodes.find(from)->second.y))/2) - 16));

			p_target.draw(text);

			combinations.push_back(string);
		}

		delete first, second;
	}

	p_target.draw(lines);
}

#include "Chain.h"

template <typename Identifier, typename Value>
Chain<Identifier, Value>::Chain()
{

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

Chain<char, float>::Chain()
{

}

Chain<char, float>::~Chain()
{

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
}
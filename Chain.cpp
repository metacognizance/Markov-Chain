#include "Chain.h"

template <typename Identifier, typename Value>
Matrix<Identifier, Value>::Matrix()
{

}

template <typename Identifier, typename Value>
Matrix<Identifier, Value>::~Matrix()
{

}

template <typename Identifier, typename Value>
Value Matrix<Identifier, Value>::GetValue(const Identifier & p_row, const Identifier & p_column)
{
	return m_values[Coord(p_row, p_column)];
}

template <typename Identifier, typename Value>
void Matrix<Identifier, Value>::SetValue(const Identifier & p_row, const Identifier & p_column, const Value & p_value)
{
	m_values[Coord(p_row, p_column)] = p_value;
}

Matrix<char, int>::Matrix()
{

}

Matrix<char, int>::~Matrix()
{

}

int Matrix<char, int>::GetValue(const char & p_row, const char & p_column)
{
	Coord key = Coord(p_row, p_column);
	return m_values[key];
}

void Matrix<char, int>::SetValue(const char & p_row, const char & p_column, const int & p_int)
{
	Coord key = Coord(p_row, p_column);
	m_values[key] = p_int;
}

template <typename Identifier, typename Value>
Matrix<Identifier, Value>::Coord::Coord()
{

}

template <typename Identifier, typename Value>
Matrix<Identifier, Value>::Coord::Coord(const Identifier & p_row, const Identifier & p_column) : 
	m_row(p_row),
	m_column(p_column)
{

}

template <typename Identifier, typename Value>
Matrix<Identifier, Value>::Coord::~Coord()
{

}

template <typename Identifier, typename Value>
bool Matrix<Identifier, Value>::Coord::operator<(const Coord & p_coord) const
{
	return ((int)(m_row) != (int)(p_coord.m_row) ? ((int)(m_row) < (int)(p_coord.m_row)):((int)(m_column) < (int)(p_coord.m_column)));
}
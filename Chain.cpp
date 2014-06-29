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
Value Matrix<Identifier, Value>::GetValue(const Identifier & p_row, const Identifier & p_column) const
{
	return m_values[Coord(p_row, p_column)];
}

template <typename Identifier, typename Value>
void Matrix<Identifier, Value>::SetValue(const Identifier & p_row, const Identifier & p_column, const Value & p_value)
{
	m_values[Coord(p_row, p_column)] = p_value;
}

template <typename Identifier, typename Value>
bool Matrix<Identifier, Value>::find(const Identifier & p_identifier, const std::vector<Identifier> & p_list) const
{
	for (int i = 0; i < p_list.size(); ++i)
	{
		if (p_identifier == p_list[i])
		{
			return true;
		}
	}

	return false;
}

template <typename Identifier, typename Value>
std::vector<Identifier> Matrix<Identifier, Value>::GetRows() const
{
	std::vector<Identifier> result;

	for (auto it = m_values.begin(); it != m_values.end(); it++)
	{
		if (!find(it->first.m_row, result))
		{
			result.push_back(it->first.m_row);
		}
	}

	return result;
}

template <typename Identifier, typename Value>
std::vector<Identifier> Matrix<Identifier, Value>::GetColumns() const
{
	std::vector<Identifier> result;

	for (auto it = m_values.begin(); it != m_values.end(); it++)
	{
		if (!find(it->first.m_column, result))
		{
			result.push_back(it->first.m_column);
		}
	}

	return result;
}

Matrix<char, int>::Matrix()
{

}

Matrix<char, int>::~Matrix()
{

}

int Matrix<char, int>::GetValue(const char & p_row, const char & p_column) const
{
	Coord key = Coord(p_row, p_column);
	return m_values.find(key)->second;
}

void Matrix<char, int>::SetValue(const char & p_row, const char & p_column, const int & p_int)
{
	Coord key = Coord(p_row, p_column);
	m_values[key] = p_int;
}

Matrix<char, int> Matrix<char, int>::operator*(const Matrix<char, int> & p_matrix) const
{
	Matrix<char, int> matrix;

	std::vector<char> rows = GetRows(), columns = GetColumns();

	std::vector<char> _rows = p_matrix.GetRows(), _columns = p_matrix.GetColumns();

	for (int i = 0; i < rows.size(); ++i)
	{
		for (int j = 0; j < columns.size(); ++j)
		{
			int value = 0;

			for (int k = 0; k < _rows.size(); ++k)
			{
				value += (m_values.find(Coord(rows[i], columns[k]))->second*p_matrix.GetValue(_rows[k], _columns[j]));
			}

			matrix.SetValue(rows[i], columns[j], value);
		}
	}

	return matrix;
}

//Matrix<char, int> Matrix<char, int>::operator*=(const Matrix<char, int> & p_lhs, const Matrix<char, int> & p_rhs) const
//{
//	Matrix<char, int> matrix = p_lhs*p_rhs;
//
//	p_lhs = matrix;
//
//	return matrix;
//}


/*------------------------ Coord ------------------------*/

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
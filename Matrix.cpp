#include "Matrix.h"

//standard

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

template <typename Identifier, typename Value>
void Matrix<Identifier, Value>::Erase(const Identifier & p_row, const Identifier & p_column)
{
	
}

//int

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

	for(int i = 0; i < rows.size(); ++i)
	{
		for(int j = 0; j < _columns.size(); ++j)
		{
			matrix.m_values[Coord(rows[i], _columns[j])] = 0;

			for(int k = 0; k < columns.size(); ++k)
			{
				matrix.m_values[Coord(rows[i], _columns[j])] += GetValue(rows[i], columns[k])*p_matrix.GetValue(_rows[k], _columns[j]);
			}

		}
	}

	return matrix;
}

void Matrix<char, int>::Erase(const char & p_row, const char & p_column)
{
	if (m_values.find(Coord(p_row, p_column)) != m_values.end())
	{
		m_values.erase(Coord(p_row, p_column));
	}
}

//float

Matrix<char, float>::Matrix()
{

}

Matrix<char, float>::~Matrix()
{

}

float Matrix<char, float>::GetValue(const char & p_row, const char & p_column) const
{
	Coord key = Coord(p_row, p_column);
	return m_values.find(key)->second;
}

void Matrix<char, float>::SetValue(const char & p_row, const char & p_column, const float & p_int)
{
	Coord key = Coord(p_row, p_column);
	m_values[key] = p_int;
}


Matrix<char, float> Matrix<char, float>::operator*(const Matrix<char, float> & p_matrix) const
{
	Matrix<char, float> matrix;

	std::vector<char> rows = GetRows(), columns = GetColumns();

	std::vector<char> _rows = p_matrix.GetRows(), _columns = p_matrix.GetColumns();

	for(int i = 0; i < rows.size(); ++i)
	{
		for(int j = 0; j < _columns.size(); ++j)
		{
			matrix.m_values[Coord(rows[i], _columns[j])] = 0;

			for(int k = 0; k < columns.size(); ++k)
			{
				matrix.m_values[Coord(rows[i], _columns[j])] += GetValue(rows[i], columns[k])*p_matrix.GetValue(_rows[k], _columns[j]);
			}

		}
	}

	return matrix;
}

void Matrix<char, float>::Erase(const char & p_row, const char & p_column)
{
	if (m_values.find(Coord(p_row, p_column)) != m_values.end())
	{
		m_values.erase(Coord(p_row, p_column));
	}
}

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

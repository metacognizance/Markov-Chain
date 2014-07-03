#pragma once
#include <map>
#include <memory>
#include <vector>
#include <iostream>

template <typename Identifier, typename Value>class Matrix
{
	struct Coord
	{
		Coord();

		Coord(const Identifier & p_row, const Identifier & p_column);

		~Coord();

		Identifier m_row, m_column;

		bool operator<(const Coord & p_coord) const;
	};

public:
	Matrix();
	~Matrix();

	Value GetValue(const Identifier & p_row, const Identifier & p_column) const;

	void SetValue(const Identifier & p_row, const Identifier & p_column, const Value & p_value);

	Coord GetCoord(const int & p_index) const;

	void Erase(const Identifier & p_row, const Identifier & p_column);

	Matrix operator*(const Matrix & p_matrix) const;
	
	//Matrix operator*=(const Matrix & p_lhs, const Matrix & p_rhs) const;

	std::vector<Identifier> GetRows() const, GetColumns() const;
	
private:
	std::map<Coord, Value> m_values;

	bool find(const Identifier & p_identifier, const std::vector<Identifier> & p_list) const;
};
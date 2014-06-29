#pragma once
#include <map>
#include <memory>
#include <SFML\System\Vector2.hpp>

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

	std::map<Coord, Value> m_values;

	Value GetValue(const Identifier & p_row, const Identifier & p_column);

	void SetValue(const Identifier & p_row, const Identifier & p_column, const Value & p_value);
};
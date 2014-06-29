#pragma once
#include <map>
#include <memory>
#include <SFML\System\Vector2.hpp>

template <typename Identifier, typename Value>class Matrix
{
	struct Coord
	{
		inline Coord()
		{

		}

		inline Coord(const Identifier & p_row, const Identifier & p_column) :
			m_row(p_row),
			m_column(p_column)
		{

		}

		inline ~Coord()
		{

		}

		Identifier m_row, m_column;

		inline bool operator<(const Coord & p_coord) const
		{
			return true;
		}
	};

public:
	Matrix();
	~Matrix();

	std::map<Coord, Value> m_values;

	Value GetValue(const Identifier & p_row, const Identifier & p_column);

	void SetValue(const Identifier & p_row, const Identifier & p_column, const Value & p_value);
};
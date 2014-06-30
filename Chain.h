#pragma once
#include "Matrix.h"

template <typename Identifier, typename Value>class Chain
{
public:
	Chain();
	~Chain();

	void Increment(const unsigned int & p_amount);

	std::map<Identifier, Value> m_state;

	Matrix<Identifier, Value> m_probabilityMatrix;
};


#pragma once

#ifdef CE_OPENGL_ES

#include <fc/fixed_vector.h>
#include "Matrix.h"

CE_NAMESPACE_BEGIN

#define MATRIX_STACK_MAX_SIZE 64


class MatrixStack
{
public:
	typedef fc::fixed_vector<Matrix, MATRIX_STACK_MAX_SIZE> vec_type;

	MatrixStack()
		: m_stack(1, Matrix::Identity)
	{}

	void LoadIdentity()
	{
		m_stack.back() = Matrix::Identity;
	}

	void LoadMatrix( const Matrix& matrix )
	{
		m_stack.back() = matrix;
	}

	void MultMatrix( const Matrix& matrix )
	{
		m_stack.back() *= matrix;
	}

	void PushMatrix()
	{
		if( m_stack.capacity() == m_stack.size() )
			m_stack.reserve( m_stack.size() * 2 );

		const Matrix & top = m_stack.back();
		m_stack.push_back( top );
	}

	void PopMatrix()
	{
		if( m_stack.size() == 1 )
			LoadIdentity();

		else
			m_stack.pop_back();

	}

	size_t Depth() const
	{
		return m_stack.size();
	}

	Matrix &Top() { return m_stack.back(); }
	const Matrix &Top() const { return m_stack.back(); }

private:
	vec_type m_stack;
};



void glPushMatrix()
{
} 


void glPopMatrix()
{
} 



CE_NAMESPACE_END

#endif // CE_OPENGL_ES


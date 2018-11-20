/** @file */
//Includes
#include <initializer_list>
#include <algorithm>
#include <iostream>

#ifndef VECTOR_H
#define VECTOR_H

/**
 * @brief       Class for hosting data with different types in a vector.
 * @details     This class Vector contains methods to provide an easy storaging of data different types in a vector.
 * @author      Maximilian Bachmann <bachmann.maxim-tfe17@it.dhbw-ravensburg.de>
 * @author      Felix Bandle <bandle.felix-tfe17@it.dhbw-ravensburg.de>
 * @author      Florian Vetter <vetter.florian-tfe17@it.dhbw-ravensburg.de>
 * @version     1.2
 * @since       1.0 
 */
template<typename T>
class Vector {


private:
	T * m_elements;  //!< Pointer on the first item of a vector.
	size_t m_size;  //!< Indicates the actual size of a vector.

	size_t m_capacity = 8;  //!< Indicates the capacity of a vector.

public:

	using value_type = T;  //!< Variable for the type of the vector items.
	Vector();
	Vector(size_t size);
	Vector(std::initializer_list<value_type> lst);
	Vector(const Vector& a);
	~Vector();
	void push_back(const value_type& value);
	void push_back(value_type& value);
	void push_back_slow(const value_type& value);
	void push_back_slow(value_type& value);
	void pop_back();
	void pop_back_slow();
	void resize(size_t new_size);
    void shrink_to_fit();
	void reserve(size_t new_capacity );
	T* begin() const;
	T* end() const;
	size_t size() const;
	size_t capacity() const;
	bool empty() const;
	T& operator [] (size_t index);
	const T& operator [] (size_t index) const;
	Vector& operator = (const Vector& x);
	void clear();
	T& at(size_t pos);
};
#include "VectorImplementation.hpp"
#endif //VECTOR_H

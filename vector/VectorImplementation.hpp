/** @file */
#include "Vector.hpp"

/**
 * Constructor for an empty vector.
 * <p>
 * Creates an empty vector with the capacity 8.
 * </p>
 *
 * @param   m_size      The size of the vector is set to 0.
 * @param   m_elements  pointer on first item of a vector.
 */
template<typename T>
Vector<T>::Vector() : m_elements(new value_type[8]), m_size(0) {};

/**
 * Constructor for a vector with a specific size.
 * <p>
 * This creates an vector, which will have a specific length.
 * The length is set with the parameter "size"
 * </p>
 *
 * @param  size   Commits the size of the vector.
 */
template<typename T>
Vector<T>::Vector(size_t size):m_elements(new value_type[2*size]), m_size(size), m_capacity(2*size){
	for (size_t i = 0; i < size; ++i){
		m_elements[i] = 0;
	}
}

/**
 * Constructor for a vector with some values.
 * <p>
 * Creates a vector and saves the input data to it.
 * Therefore it gets all data with the parameter "list"
 * </p>
 *
 * @param  lst Fetches the data to be initialized when creating the vector.
 */
template<typename T>
Vector<T>::Vector(std::initializer_list<value_type> lst){
	reserve(lst.size());
	m_size = lst.size();
	size_t i = 0;
	for (auto &x : lst){
		m_elements[i++] = x;
	}
}

/**
 * copy constructor
 * <p>
 * constructs a copied vector and therefor creates a deep copy of the vector
 * </p>
 *
 * @param  Vector to copy
 */
template<typename T>
Vector<T>::Vector(const Vector& a): m_elements(new value_type[a.m_capacity]), m_size(a.m_size), m_capacity(a.m_capacity){
	for (size_t i=0; i < a.m_size; ++i){
		m_elements[i] = a.m_elements[i];
	}
}

/**
 * Destructor of vector.
 * <p>
 * Deletes the vector and sets storage free.
 * </p>
 *
 */
template<typename T>
Vector<T>::~Vector() {
	if (m_elements != nullptr){
		delete[] m_elements;
		m_elements = nullptr;
	}
}

/**
 * Adds a item at the end of the vector.
 * <p>
 * First checks for enough capacity and increases it when necessary.
 * Afterwards it adds the item at the end of the vector.
 * </p>
 *
 * @param  value  Item, that should be added.
 */
template<typename T>
void Vector<T>::push_back(const value_type& value) {
	if (m_size >= m_capacity) {
		reserve(m_capacity * 2);
	}
	m_elements[m_size++] = value;
}

/**
 * Adds a item at the end of the vector.
 * <p>
 * First checks for enough capacity and increases it when necessary.
 * Afterwards it adds the item at the end of the vector.
 * </p>
 *
 * @param  value  Item, that should be added.
 */
template<typename T>
void Vector<T>::push_back(value_type& value) {
	if (m_size >= m_capacity) {
		reserve(m_capacity * 2);
	}
	m_elements[m_size++] = value;
}

/**
 * Adds a item at the end of the vector.
 * <p>
 * capacity is always the size in the slow version
 * </p>
 *
 * @param  value  Item, that should be added.
 */
template<typename T>
void Vector<T>::push_back_slow(value_type& value) {
	m_capacity = m_size;
	reserve(m_size + 1);
	m_elements[m_size++] = value;
}

/**
 * Adds a item at the end of the vector.
 * <p>
 * Fcapacity is always the size in the slow version
 * </p>
 *
 * @param  value  Item, that should be added.
 */
template<typename T>
void Vector<T>::push_back_slow(const value_type& value) {
	m_capacity = m_size;
	reserve(m_size + 1);
	m_elements[m_size++] = value;
}

/**
 * Deletes the last item of the vector.
 *
 */
template<typename T>
void Vector<T>::pop_back() {
	if (m_size) {
		--m_size;
		if (m_size != 0 && m_size * 4 <= m_capacity) {
			m_capacity /= 2;
			reserve(m_capacity);
		}
	}
}

/**
 * Deletes the last item of the vector (capacity = size)
 *
 */
template<typename T>
void Vector<T>::pop_back_slow() {
	if (m_size > 1){
        --m_size;
		m_capacity = m_size-1;
		reserve(m_size);
	}else if (m_size){
		--m_size;
        m_capacity = 0;
		reserve(1);
	}else{
		m_capacity = 0;
		reserve(1);
	}

}

/**
 * Resizes the vector.
 * <p>
 * If the new size is bigger than the current one, it creates a second vector
 * where all items are stored plus some more storage. Afterwards the original vector
 * is deleted and the helpvector is set as the actual vector.
 * </p>
 *
 * @param  new_size  Permits the new size
 */
template<typename T>
void Vector<T>::resize(size_t new_size) {
	if (new_size < m_size){
		m_size = new_size;
	}else if (new_size > m_size){
		reserve(new_size);
		size_t old_size = m_size;
		m_size = new_size;
		for (size_t i = old_size; i < new_size; ++i){
			m_elements[i] = 0;
		}
	}
}

/**
 * Diminishes storage.
 *
 */
template<typename T>
void Vector<T>::shrink_to_fit() {
	m_capacity = m_size;
	reserve(m_capacity);
}

/**
 * Reserves storage.
 *
 * @param  n  Size of storage to be reserved.
 */
template<typename T>
void Vector<T>::reserve(size_t new_capacity ) {
	if (new_capacity < m_capacity) return;

	value_type* helper = new value_type[new_capacity];
	for (size_t i = 0; i <  m_size; ++i) {
		//element at position i of the vector gets moved to position i of the new vector
		helper[i] = m_elements[i];
	}
	if (m_elements != nullptr) {
		delete[] m_elements;
	}
	m_elements = helper;
	m_capacity = new_capacity;
}

/**
 * Returns a pointer on the first item of a vector.
 *
 * @return Pointer on the first item.
 */
template<typename T>
T* Vector<T>::begin() const {
	return m_elements;
}

/**
 * Returns a pointer on the item behind the last item of the vector.
 *
 * @return Pointer on the item behind the last item of the vector.
 */
template<typename T>
T* Vector<T>::end() const {
	return m_elements + m_size;
}

/**
 * Returns the size of a vector.
 *
 * @return Size of vector.
 */
template<typename T>
size_t Vector<T>::size() const {
	return m_size;
}

/**
 * Returns the capacity of a vector.
 *
 * @return Size of vector.
 */
template<typename T>
size_t Vector<T>::capacity() const {
	return m_capacity;
}

/**
 * Checks if the vector is empty.
 *
 * @return Bool on wether the vector is empty or not.
 */
template<typename T>
bool Vector<T>::empty() const {
	return m_size == 0;
}

/**
 * Getting access on a specific item for write and read.
 *
 * @return Returns a Pointer on the searched item.
 */
template<typename T>
T& Vector<T>::operator [] (size_t index) {
	return m_elements[index];
}

/**
 * Getting access on a specific item for read.
 *
 * @return Returns a const Pointer on the searched item.
 */
template<typename T>
const T& Vector<T>::operator [] (size_t index) const {
	return m_elements[index];
}

/**
 * custom assignment operator to make a deep copy of a Vector
 *
 * @return Returns a Pointer on the copied Vector
 */
template<typename T>
Vector<T>& Vector<T>::operator = (const Vector& x) {
	//check for self assignment
	if (this == &x) return *this;
	value_type* helper = new value_type[x.m_capacity];
	for (size_t i=0; i < x.m_size; ++i){
		helper[i] = x.m_elements[i];
	}
		
	std::swap(this->m_elements, helper);
	this->m_capacity = x.m_capacity;
	this->m_size = x.m_size;

	delete[] helper;
	return *this;
}

/**
* Clears all items of a vector.
* <p>
* The items are deleted and a second help vector is created and set as the new one.
* Afterwards it has the same size as the deleted vector, but is not filled with items.
* </p>
*
*/
template<typename T>
void Vector<T>::clear() {
	value_type* helper = new value_type[m_capacity];
	if (m_elements != nullptr) {
		delete[] m_elements;
	}
	m_elements = helper;
	m_size = 0;
}

/**
* Returns a copy of item at the wanted position.
* <p>
* Returns a copy of the item at the wanted position, when it exists. When the position is out of range, it throws an exeption.
* </p>
*
* @return Returns the value at the wanted position.
*
* @exeption std::out_of_range ("position >= Vectorsize")
*/
template<typename T>
T& Vector<T>::at(size_t pos) {
	if (!(pos < m_size)){
		throw std::out_of_range ("position >= Vectorsize");
	}
	return m_elements[pos];
}
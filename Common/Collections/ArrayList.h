#ifndef DUSK_COLLECTIONS_ARRAY_LIST_H
#define DUSK_COLLECTIONS_ARRAY_LIST_H

#include <Collections/Collections.h>
#include <Tracking/TrackedObject.h>

#include <vector>

namespace Dusk
{

namespace Collections
{

/// List of objects backed by an Array
/*!
 * Wrapper for std::vector with added functionality and standardized function
 * names. 
 */
template <class T>
class ArrayList :
	public Tracking::TrackedObject
{
public:

	typedef typename std::vector<T>::iterator
		Iterator;
	typedef typename std::vector<T>::reverse_iterator
		ReverseIterator;
	typedef typename std::vector<T>::const_iterator
		ConstIterator;
	typedef typename std::vector<T>::const_reverse_iterator
		ConstReverseIterator;

    inline ArrayList( void ) :
        m_List()
    { }

    inline ArrayList( const ArrayList& rhs ) :
        m_List(rhs.m_List)
    { }
																			   
    virtual inline ~ArrayList( void ) { Clear(); }

	virtual inline string GetClassName( void ) const { return "Array List"; }

	/// Add a new element to the list
	/*! 
	 * \param item The item to be added to the list
	 */
    inline void Add( const T& item )
        { m_List.push_back(item); }

	/// Clear the list of all elements
    inline void Clear( void ) { m_List.clear(); }

	/// Returns the element at the given index
	/*!
	 * \param index The index to get the element from
	 * \returns The element at the given index
	 */
    inline       T& At( const int& index )       { return m_List[index]; }

	/// Returns the element at the given index
	/*!
	* \param index The index to get the element from
	* \returns The element at the given index
	*/
    inline const T& At( const int& index ) const { return m_List[index]; }

	/// Returns the element at the given index
	/*!
	* \param index The index to get the element from
	* \returns The element at the given index
	*/
	inline       T& operator[]( const int& index )       { return At(index); }

	/// Returns the element at the given index
	/*!
	 * \param index The index to get the element from
	 * \returns The element at the given index
	 */
	inline const T& operator[]( const int& index ) const { return At(index); }

	// TODO: Implement Data()

	/// Returns if the given element exists within the list
	/*! 
	 * \param item The item to look for in the list
	 * \returns True if the element is in the list, False otherwise
	 */
	inline bool Contains( const T& item ) const 
		{ return (IsEmpty() ? false : 
			find(ConstBegin(), ConstEnd(), item) != ConstEnd()); }

	/// Returns if the given index exists within the list
	/*!
	 * \param index The index to check against the bounds of the list
	 * \returns True if the index is in the list, False otherwise
	 */
	inline bool HasIndex( const unsigned int& index ) const
		{ return (IsEmpty() ? false : (index >= 0 && index <= Size() - 1)); }

	/// Returns the index of a given element, or -1 if not found
	/*!
	* \param item The element to get the index of
	* \returns The index of the element, or -1 if it could not be found
	*/
	unsigned int IndexOf( const T& item ) const;

	/// Returns if the list is empty
	/*!
	* \returns True if the list is empty, False otherwise
	*/
    inline bool IsEmpty( void ) const
        { return m_List.empty(); }

	/// Returns the size of the array
	/*!
	* \returns The size of the array
	*/
    inline size_t Size( void ) const { return m_List.size(); }

	/// Resizes the internal capacity of the array
	/*!
	* Resizes the internal capacity of the array, which will remove elements if
	* the new capacity is less than the current size of the array, but will not
	* add any new elements if the capacity is larger than the current size of
	* the array.
	* \param size The new internal size of the array
	*/
	inline void Resize( const unsigned int& size ) 
		{ m_List.resize(size); }

    inline void Insert( Iterator& first, Iterator& last )
        { m_List.insert(first, last); }

    inline void Insert( ConstIterator& first,
                        ConstIterator& last ) const
        { m_List.insert(first, last); }

	inline void InsertAt( const T& item, const unsigned int& index ) 
		{ m_List.insert(Begin() + index, item); }

	inline T& Front( void ) { return m_List.front(); }
	inline T& Back ( void ) { return m_List.back(); }
	inline const T& Front( void ) const { return m_List.front(); }
	inline const T& Back ( void ) const { return m_List.back(); }

	inline T PopBack ( void ) { return m_List.pop_back(); }

	inline Iterator Remove( Iterator it ) { return m_List.erase(it); }
	inline Iterator Remove( Iterator start, Iterator end ) 
		{ return m_List.erase(start, end); }

	bool Remove( const T& item );
	bool RemoveAll( const T& item );

	/// Remove the element at the given index
	/*!
	 * \param index The index of the element to remove
	 * \returns True if the element exists and was removed, False otherwise
	 */
	inline bool RemoveAt( const unsigned int& index )
	{
		if ( ! HasIndex(index))
			return false;
		m_List.erase(Begin() + index);
		return true;
	}

	inline bool RemoveBack( void ) 
	{ 
		if (IsEmpty()) 
			return false; 
		PopBack();
		return true; 
	}

	void Fill( const T& value, const unsigned int& amount );

	template <class InputIterator>
	inline void Assign( InputIterator first, InputIterator last )
		{ m_List.assign(first, last); }

    inline Iterator Begin( void )
        { return m_List.begin(); }

    inline Iterator End( void )
        { return m_List.end(); }

    inline ReverseIterator RevBegin( void )
        { return m_List.rbegin(); }

    inline ReverseIterator RevEnd( void )
        { return m_List.rend(); }

    inline ConstIterator ConstBegin( void )
        { return m_List.cbegin(); }

    inline ConstIterator ConstEnd( void )
        { return m_List.cend(); }

    inline ConstReverseIterator ConstRevBegin( void )
        { return m_List.crbegin(); }

    inline ConstReverseIterator ConstRevEnd( void )
        { return m_List.crend(); }

	// For compatibility with range-based for loops
	
    inline Iterator begin( void )
        { return m_List.begin(); }

    inline Iterator end( void )
        { return m_List.end(); }

    inline ReverseIterator rbegin( void )
        { return m_List.rbegin(); }

    inline ReverseIterator rend( void )
        { return m_List.rend(); }

    inline ConstIterator cbegin( void ) const
        { return m_List.cbegin(); }

    inline ConstIterator cend( void ) const
        { return m_List.cend(); }

    inline ConstReverseIterator crbegin( void ) const
        { return m_List.crbegin(); }

    inline ConstReverseIterator crend( void ) const
        { return m_List.crend(); }

private:

	std::vector<T>		m_List;

}; // class ArrayList

template <class T>
unsigned int Dusk::Collections::ArrayList<T>::IndexOf(const T& item) const
{
	if (IsEmpty())
		return -1;
	auto it = find(ConstBegin(), ConstEnd(), item);
	return (it == ConstEnd() ? -1 : it - ConstBegin());
}

template <class T>
bool Dusk::Collections::ArrayList<T>::Remove(const T& item)
{
	for (auto it = Begin(); it != End(); ++it)
		if (*it == item)
		{
			Remove(it);
			return true;
		}
	return false;
}

template <class T>
bool Dusk::Collections::ArrayList<T>::RemoveAll(const T& item)
{
	bool found = false;
	for (auto it = Begin(); it != End(); ++it)
		if (*it == item)
		{
			Remove(it);
			found = true;
		}
	return found;
}

} // namespace Collections

} // namespace Dusk

#endif // DUSK_COLLECTIONS_ARRAY_LIST_H
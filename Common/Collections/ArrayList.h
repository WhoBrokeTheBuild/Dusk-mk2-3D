#ifndef DUSK_COLLECTIONS_ARRAY_LIST_H
#define DUSK_COLLECTIONS_ARRAY_LIST_H

#include <Collections/Collections.h>
#include <Tracking/ITrackedObject.h>

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
	public Tracking::ITrackedObject,
	public std::vector<T>
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

	virtual inline string GetClassName( void ) const { return "Array List"; }

	/// Add a new element to the list
	/*! 
	 * \param item The item to be added to the list
	 */
    inline void Add( const T& item )
        { push_back(item); }

	/// Clear the list of all elements
    inline void Clear( void ) { clear(); }

    inline       T& At( const int& index )       { return at(index); }
    inline const T& At( const int& index ) const { return at(index); }
	inline       T& operator[]( const int& index )       { return At(index); }
	inline const T& operator[]( const int& index ) const { return At(index); }

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
		{ return (IsEmpty() ? false : (index >= 0 && index <= GetSize() - 1)); }

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
        { return empty(); }

	/// Returns the size of the array
	/*!
	* \returns The size of the array
	*/
    inline size_t GetSize( void ) const { return size(); }

	/// Resizes the internal capacity of the array
	/*!
	* Resizes the internal capacity of the array, which will remove elements if
	* the new capacity is less than the current size of the array, but will not
	* add any new elements if the capacity is larger than the current size of
	* the array.
	* \param size The new internal size of the array
	*/
	inline void Resize( const unsigned int& size ) 
		{ resize(size); }

	inline void InsertAt( const T& item, const unsigned int& index ) 
		{ insert(Begin() + index, item); }

	inline T& Front( void ) { return front(); }
	inline T& Back ( void ) { return back(); }
	inline const T& Front( void ) const { return front(); }
	inline const T& Back ( void ) const { return back(); }

	inline T PopBack ( void ) { return pop_back(); }

	inline Iterator Remove( Iterator it ) { return erase(it); }
	inline Iterator Remove( Iterator start, Iterator end ) 
		{ return erase(start, end); }

	bool RemoveFirst( const T& item );
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
		erase(Begin() + index);
		return true;
	}

	inline bool RemoveBack( void ) 
	{ 
		if (IsEmpty()) 
			return false; 
		PopBack();
		return true; 
	}

    inline Iterator Begin( void )
        { return begin(); }

    inline Iterator End( void )
        { return end(); }

    inline ReverseIterator RevBegin( void )
        { return rbegin(); }

    inline ReverseIterator RevEnd( void )
        { return rend(); }

    inline ConstIterator ConstBegin( void )
        { return cbegin(); }

    inline ConstIterator ConstEnd( void )
        { return cend(); }

    inline ConstReverseIterator ConstRevBegin( void )
        { return crbegin(); }

    inline ConstReverseIterator ConstRevEnd( void )
        { return crend(); }

private:

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
bool Dusk::Collections::ArrayList<T>::RemoveFirst(const T& item)
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
	
	auto it = Begin();
	while (it != End()) 
	{
		if (*it == item)
		{
			it = Remove(it);
			found = true;
		}
		else
		{
			++it;
		}
	}

	return found;
}

} // namespace Collections

} // namespace Dusk

#endif // DUSK_COLLECTIONS_ARRAY_LIST_H
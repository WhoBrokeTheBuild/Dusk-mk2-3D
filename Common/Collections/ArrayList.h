#ifndef DUSK_COLLECTIONS_ARRAY_LIST_H
#define DUSK_COLLECTIONS_ARRAY_LIST_H

#include <Collections/Collections.h>

#include <vector>

namespace Dusk
{

namespace Collections
{

template <class T>
class ArrayList
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

    inline void Add( const T& item )
        { m_List.push_back(item); }

    inline void Clear( void ) { m_List.clear(); }

    inline       T& At( const int& index )       { return m_List[index]; }
    inline const T& At( const int& index ) const { return m_List[index]; }

	inline       T& operator[]( const int& index )       { return At(index); }
	inline const T& operator[]( const int& index ) const { return At(index); }

	inline bool Contains( const T& item ) const 
		{ return (IsEmpty() ? false : 
			find(ConstBegin(), ConstEnd(), item) != ConstEnd()); }

	bool HasIndex( const unsigned int& index ) const
		{ return (IsEmpty() ? false : (index >= 0 && index <= Size() - 1)); }

	bool IndexOf( const T& item ) const;

    inline bool IsEmpty( void ) const
        { return m_List.empty(); }

    inline size_t Size( void ) const { return m_List.size(); }

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

private:

	std::vector<T>		m_List;

}; // class ArrayList

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
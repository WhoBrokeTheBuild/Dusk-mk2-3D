#ifndef DUSK_COLLECTIONS_MAP_H
#define DUSK_COLLECTIONS_MAP_H

#include <Collections/Collections.h>

#include <map>

namespace Dusk
{

namespace Collections
{

template <class K, class T, typename Sort = std::less<K>>
class Map
{
public:

	typedef typename std::map<K, T>::iterator
        Iterator;
	typedef typename std::map<K, T>::reverse_iterator
        ReverseIterator;
	typedef typename std::map<K, T>::const_iterator
        ConstIterator;
	typedef typename std::map<K, T>::const_reverse_iterator
        ConstReverseIterator;

	typedef std::pair<K, T> Pair;

    inline Map( void ) :
        m_Map()
    { }

    inline Map( const Map& rhs ) :
        m_Map(rhs.m_Map)
    { }

    virtual inline ~Map( void ) { Clear(); }

    inline void Add( const K& key, const T& item )
        { m_Map.insert(Pair(key, item)); }

    inline void Clear( void ) { m_Map.clear(); }

    inline void RemoveKey( const K& key )
		{ m_Map.erase(key); }
    bool RemoveFirstValue( const T& value );
    bool RemoveAllValues( const T& value );

    inline T& At( const K& key )       { return m_Map[key]; }
    inline T& At( const K& key ) const { return m_Map[key]; }
	inline T& operator[]( const K& key )	   { return At(key); }
	inline T& operator[]( const K& key ) const { return At(key); }

    inline bool ContainsKey( const K& key )
		{ return (m_Map.find(key) != ConstEnd()); }
    bool ContainsValue( const T& value ) const;

    inline bool IsEmpty( void ) const
        { return m_Map.empty(); }

    K GetIndexOf( const T& item ) const;

    inline size_t Size( void ) const { return m_Map.size(); }

    inline Iterator Find( const K& key )
        { return m_Map.find(key); }

    inline ConstIterator Find( const K& key ) const
        { return m_Map.find(key); }

    inline void Insert( Iterator& first, Iterator& last )
        { m_Map.insert(first, last); }

    inline void Insert( ConstIterator& first,
                        ConstIterator& last ) const
        { m_Map.insert(first, last); }

    inline Iterator Begin( void )
        { return m_Map.begin(); }

    inline Iterator End( void )
        { return m_Map.end(); }

    inline ReverseIterator RevBegin( void )
        { return m_Map.rbegin(); }

    inline ReverseIterator RevEnd( void )
        { return m_Map.rend(); }

    inline ConstIterator ConstBegin( void ) const
        { return m_Map.cbegin(); }

    inline ConstIterator ConstEnd( void ) const
        { return m_Map.cend(); }

    inline ConstReverseIterator ConstRevBegin( void ) const
        { return m_Map.crbegin(); }

    inline ConstReverseIterator ConstRevEnd( void ) const
        { return m_Map.crend(); }

private:

    std::map<K, T, Sort>    m_Map;

}; // class Map<T, K, Sort>

template <class K, class T, typename Sort>
bool Dusk::Collections::Map<K, T, Sort>::RemoveFirstValue( const T& value )
{
	for (auto it = Begin(); it != End(); ++it)
    {
        if (it->second == value)
        {
			m_Map.erase(it);
            return true;
        }
	}
    return false;
}

template <class K, class T, typename Sort>
bool Dusk::Collections::Map<K, T, Sort>::RemoveAllValues(const T& value)
{
    bool found = false;
    for (auto it = Begin(); it != End(); ++it)
    {
        if (it->second == value)
        {
            m_Map.erase(it);
            found = true;
        }
	}
    return found;
}

template <class K, class T, typename Sort>
bool Dusk::Collections::Map<K, T, Sort>::ContainsValue( const T& value ) const
{
	for (auto it = ConstBegin(); it != ConstEnd(); ++it)
        if (it->second == value)
            return true;
    return false;
}

template <class K, class T, typename Sort>
K Dusk::Collections::Map<K, T, Sort>::GetIndexOf( const T& item ) const
{
	for (auto it = ConstBegin(); it != ConstEnd(); ++it)
        if (it->second == item)
            return it->first;
    return K();
}

} // namespace Collections

} // namespace Dusk

#endif // DUSK_COLLECTIONS_MAP_H

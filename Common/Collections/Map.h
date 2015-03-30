#ifndef DUSK_COLLECTIONS_MAP_H
#define DUSK_COLLECTIONS_MAP_H

#include <Collections/Collections.h>

#include <map>

using std::map;

namespace Dusk
{

namespace Collections
{

template <typename K, typename T, typename Sort = less<K>>
class Map
{
public:

    typedef typename map<K, T>::iterator
        Iterator;
    typedef typename map<K, T>::reverse_iterator
        ReverseIterator;
    typedef typename map<K, T>::const_iterator
        ConstIterator;
    typedef typename map<K, T>::const_reverse_iterator
        ConstReverseIterator;

    typedef pair<K, T> Pair;

    inline Map( void ) :
        m_Map()
    { }

    inline Map( const Map& rhs ) :
        m_Map(rhs.m_Map)
    { }

    virtual inline ~Map( void ) { clear(); }

    inline void Add( const K& key, const T& item )
        { m_Map.insert(Pair(key, item)); }

    inline void Clear( void ) { m_Map.clear(); }

    inline void RemoveKey( const K& key );
    inline void RemoveFirstValue( const T& value );
    inline void RemoveAllValues( const T& value );

    inline T& At( const K& key )       { return m_Map[key]; }
    inline T& At( const K& key ) const { return m_Map[key]; }

    bool ContainsKey( const K& key ) const
        { return (m_Map.find(key) !== ConstEnd())}
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

    inline ConstIterator ConstBegin( void )
        { return m_Map.cbegin(); }

    inline ConstIterator ConstEnd( void )
        { return m_Map.cend(); }

    inline ConstReverseIterator ConstRevBegin( void )
        { return m_Map.crbegin(); }

    inline ConstReverseIterator ConstRevEnd( void )
        { return m_Map.crend(); }

private:

    map<K, T, Sort>    m_Map;

}; // class Map<T, K, Sort>

template <class K, class T, typename Sort>
bool Dusk::Collections::Map<K, T, Sort>::removeKey( const K& key )
{
	bool removed = (m_Map.erase(key) == 1);
	updateSize();
	return removed;
}

template <class K, class T, typename Sort>
bool Arc::Map<K, T, Sort>::removeFirstValue( const T& value )
{
	for (auto it = itBegin(); it != itEnd(); ++it)
    {
        if (it->second == value)
        {
			m_Map.erase(it);
			updateSize();
            return true;
        }
	}
    return false;
}

template <class K, class T, typename Sort>
bool Arc::Map<K, T, Sort>::removeAllValues( const T& value )
{
    bool found = false;
    for (auto it = itBegin(); it != itEnd(); ++it)
    {
        if (it->second == value)
        {
            m_Map.erase(it);
            found = true;
        }
	}
	updateSize();
    return found;
}

} // namespace Collections

} // namespace Dusk

#endif // DUSK_COLLECTIONS_MAP_H

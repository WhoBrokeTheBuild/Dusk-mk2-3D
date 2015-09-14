#ifndef DUSK_COLLECTIONS_MAP_H
#define DUSK_COLLECTIONS_MAP_H

#include <Collections/Collections.h>
#include <Tracking/ITrackedObject.h>

#include <map>

namespace Dusk
{

namespace Collections
{

template <class K, class T, typename Sort = std::less<K>>
class Map :
	public Tracking::ITrackedObject,
	public std::map<K, T, Sort>
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

	virtual inline string GetClassName( void ) const { return "Map"; }

    inline void Add( const K& key, const T& item )
        { insert(Pair(key, item)); }

    inline void Clear( void ) { clear(); }

    inline void RemoveAt( const K& key )
		{ erase(key); }
    bool RemoveFirst( const T& value );
    bool RemoveAll( const T& value );

    inline T& At( const K& key )       { return at(key); }
    inline T& At( const K& key ) const { return at(key); }
	inline T& operator[]( const K& key )	   { return At(key); }
	inline T& operator[]( const K& key ) const { return At(key); }

    inline bool ContainsKey( const K& key )
		{ return (find(key) != ConstEnd()); }
    bool ContainsValue( const T& value ) const;

    inline bool IsEmpty( void ) const
        { return empty(); }

    K GetIndexOf( const T& item ) const;

    inline size_t GetSize( void ) const { return size(); }

    inline Iterator Find( const K& key )
        { return find(key); }

    inline ConstIterator Find( const K& key ) const
        { return find(key); }

    inline Iterator Begin( void )
        { return begin(); }

    inline Iterator End( void )
        { return end(); }

    inline ReverseIterator RevBegin( void )
        { return rbegin(); }

    inline ReverseIterator RevEnd( void )
        { return rend(); }

    inline ConstIterator ConstBegin( void ) const
        { return cbegin(); }

    inline ConstIterator ConstEnd( void ) const
        { return cend(); }

    inline ConstReverseIterator ConstRevBegin( void ) const
        { return crbegin(); }

    inline ConstReverseIterator ConstRevEnd( void ) const
        { return crend(); }

}; // class Map<T, K, Sort>

template <class K, class T, typename Sort>
bool Dusk::Collections::Map<K, T, Sort>::RemoveFirst( const T& value )
{
	for (auto it = Begin(); it != End(); ++it)
    {
        if (it->second == value)
        {
			erase(it);
            return true;
        }
	}
    return false;
}

template <class K, class T, typename Sort>
bool Dusk::Collections::Map<K, T, Sort>::RemoveAll(const T& value)
{
    bool found = false;
	auto it = Begin();
	while (it != End())
	{
		if (it->second == value)
		{
			it = erase(it);
			found = true;
		}
		else
		{
			++it;
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

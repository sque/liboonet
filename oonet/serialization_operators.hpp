#ifndef OONET_SERIALIZATION_OPERATORS_HPP_INCLUDED
#define OONET_SERIALIZATION_OPERATORS_HPP_INCLUDED

#include <map>
#include <vector>
#include <list>

namespace oonet
{
	//! @name Serialization cast operators
	//! @{
	//! Cast a const POD type to "serializable" object
	template<class T>
	const serialize_const_pod_type<T> serialize_pod(const T & ref)
	{	return serialize_const_pod_type<T>(ref);	}

	//! Cast a POD type to "serializable" object
	template<class T>
	serialize_pod_type<T> serialize_pod(T & ref)
	{	return serialize_pod_type<T>(ref);	}
	//! @}


	//! @name Serialization operators
	//! @{
	//! Serialization of "serializable" objects
	inline binary_data & operator<<(binary_data & dst, const serializable & obj)
	{	return dst += obj.serialize();	}

	//! Serialization of "std::basic_string" objects
	template<class C>
	inline binary_data & operator<<(binary_data & dst, const std::basic_string<C> & str)
	{
		dst << serialize_pod(str.size());		// Push size
		return dst += binary_data(str.c_str(), str.size() * sizeof(C));	// Push data
	}

	//! Serialization of "std::list" object
	template<class T>
	inline binary_data & operator<<(binary_data & dst, const std::list<T> & _list)
	{	typename std::list<T>::const_iterator it;

		// Push size
		dst << serialize_pod(_list.size());

		// Push items
		for(it = _list.begin();it != _list.end();it++)
			dst << (*it);
		return dst;
	};

	//! Serialization of "std::vector" object
	template<class T>
	inline binary_data & operator<<(binary_data & dst, const std::vector<T> & _list)
	{	typename std::vector<T>::const_iterator it;

		// Push size
		dst << serialize_pod(_list.size());

		// Push items
		for(it = _list.begin();it != _list.end();it++)
			dst << (*it);
		return dst;
	};

	//! Serialization of "std::pair" object
	template<class F, class S>
	inline binary_data & operator<<(binary_data & dst, const std::pair<F, S> & _pair)
	{	return dst << _pair.first << _pair.second;	}

	//! Serialization of "std::map" object
	template<class F, class S>
	inline binary_data & operator<<(binary_data & dst, const std::map<F, S> & _map)
	{	typename std::map<F, S>::const_iterator it;

		// Push size
		dst << serialize_pod(_map.size());

		// Push items
		for(it = _map.begin();it != _map.end();it++)
			dst << (*it);
		return dst;
	};
	//! @}


	//! @name Unserialization operators
	//! @{
	//! Unserialize "pod" objects
	template<class T>
	inline binary_data & operator>>(binary_data & dst, serialize_pod_type<T> obj)
	{	return dst = dst.get_from(obj.unserialize(dst));	}

	//! Unserialize "serializable" objects
	/**
	@remarks The r-value binary_data object will loose the extracted object data.
		It is like a pop operation from a stack.
	*/
	inline binary_data & operator>>(binary_data & dst, serializable & obj)
	{	return dst = dst.get_from(obj.unserialize(dst));	}

	//! Unserialize "std::basic_string" objects
	template<class C>
	inline binary_data & operator>>(binary_data & dst, std::basic_string<C> & str)
	{	typename std::basic_string<C>::size_type ssize;

		// Read string size in characters
		serialize_pod(ssize).unserialize(dst);

		// Check if there is enough data
		if ((dst.size() - sizeof(ssize)) < ssize)
			OONET_THROW_EXCEPTION(ExceptionNotFound,
					"Not enough data to hold a serialization of this object");

		// Get string
		str = std::basic_string<C>((C *)(dst.get_data_ptr()+sizeof(ssize)), ssize);
		return dst = dst.get_from((ssize * sizeof(C))+ sizeof(ssize));
	}

	//! Unserialize "std::list objects"
	template<class C>
	inline binary_data & operator>>(binary_data & dst, std::list<C> & _list)
	{	typename std::list<C>::size_type lsize;
		C tmp_item;
		binary_data copy_dst(dst);

		// Read size
		copy_dst >> serialize_pod(lsize);

		// Clear list
		_list.clear();

		while(lsize != 0)
		{
			copy_dst >> tmp_item;
			_list.push_back(tmp_item);
			lsize--;
		}
		return dst = dst.get_from(dst.size() - copy_dst.size());
	}

	//! Unserialize "std::vector objects"
	template<class C>
	inline binary_data & operator>>(binary_data & dst, std::vector<C> & _list)
	{	typename std::vector<C>::size_type lsize;
		C tmp_item;
		binary_data copy_dst(dst);

		// Read size
		copy_dst >> serialize_pod(lsize);

		// Clear list
		_list.clear();

		while(lsize != 0)
		{
			copy_dst >> tmp_item;
			_list.push_back(tmp_item);
			lsize--;
		}
		return dst = dst.get_from(dst.size() - copy_dst.size());
	}

	//! Unserialize "std::pair" object
	template<class F, class S>
	inline binary_data & operator>>(binary_data & dst, std::pair<F, S> & _pair)
	{	return dst >> _pair.first >> _pair.second;	}

	//! Unserialize "std::map objects"
	template<class F, class S>
	inline binary_data & operator>>(binary_data & dst, std::map<F, S> & _map)
	{	typename std::map<F, S>::size_type lsize;
		std::pair<F, S> tmp_item;
		binary_data copy_dst(dst);

		// Read size
		copy_dst >> serialize_pod(lsize);

		// Clear list
		_map.clear();

		while(lsize != 0)
		{
			copy_dst >> tmp_item;
			_map[tmp_item.first] = tmp_item.second;
			lsize--;
		}
		return dst = dst.get_from(dst.size() - copy_dst.size());
	}
	//! @}
};	// !oonet namespace

#endif // OONET_SERIALIZATION_OPERATORS_HPP_INCLUDED

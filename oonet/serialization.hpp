#ifndef OONET_SERIALIZABLE_HPP_INCLUDED
#define OONET_SERIALIZABLE_HPP_INCLUDED

#include "./oonet.hpp"
#include "./binary_data.hpp"
#include <list>
#include <vector>


namespace oonet
{
	//! A class for serializable objectss
	class serializable
	{
	public:

		//! Constructor
		serializable(){}

		//! Destructor
		virtual ~serializable(){}

		//! Archive data to a binary_data object
		/**
			Object will serialize its data and return
			a binary_data object that will contain the archived
			data of this object.
		*/
		virtual binary_data serialize() const = 0;

		//! Unserialize data from a binary_data object
		/**
			Object will read its data from a binary_data object
			that contains the previously serialized copy in
			an archived way.
		@return The size of data that object was holding in the
			binary_data object.
		*/
		virtual size_t unserialize(const binary_data &) = 0;
	};	// !serializable class


	//! Serialization of POD types, usefull for built-in types too
	template<class T>
	class serialize_pod_type
		:public serializable
	{
	public:
		typedef T pod_type;		//! Type of instantiated class

	private:

		//! Pointer to type
		T * p_value;

	public:
		serialize_pod_type(T & pod)
			:p_value(&pod)
		{}

		binary_data serialize() const
		{	return cmem_ref((byte *)p_value, sizeof(T));	}

		size_t unserialize(const binary_data & dt)
		{	// Check size
			if (dt.size() < sizeof(T))
				OONET_THROW_EXCEPTION(ExceptionNotFound,
					"Not enough data to hold a serialization of this object");

			// Get data
			*p_value = *(T *)dt.c_array();

			// Return used size
			return sizeof(T);
		}
	};

	//  Serialization of POD types of const type
	template<class T>
	class serialize_const_pod_type
		:public serializable
	{
	public:
		typedef T pod_type;		//! Type of instantiated class

	private:
		//! Pointer to type
		const pod_type & ref_value;

	public:
		explicit serialize_const_pod_type(const T & pod)
			:ref_value(pod)
		{}

		binary_data serialize() const
		{	return cmem_ref((byte *)&ref_value, sizeof(T));	}

		size_t unserialize(const binary_data & dt)
		{	OONET_THROW_EXCEPTION(ExceptionNotSupported,
				"Cannot unserialize to a const reference object");

			return 0;
		}
	};

};	// !oonet namespace

#include "./serialization_operators.hpp"
#endif // !OONET_SERIALIZABLE_HPP_INCLUDED

#include "./test_serialize.hpp"
#include <oonet/serialization.hpp>

namespace oonet
{
	namespace test
	{
		test_serialize test_serialize_inst;

		class MySerializable
			:public serializable
		{
		public:
			unsigned short age;
			float height;

			MySerializable(){}

			MySerializable(unsigned short _a,  float _h)
				:age(_a),
				height(_h)
			{}


			// Comparison
			bool operator==(const MySerializable & r)
			{	return ((age == r.age) && (height == r.height));		}


			// Comparison
			bool operator!=(const MySerializable & r)
			{	return (!(operator==(r)));		}


			virtual binary_data serialize() const
			{	binary_data tmp = binary_data((byte*)&age, sizeof(age))
					+ binary_data((byte*)&height, sizeof(height));
				return tmp;
			}

			virtual size_t unserialize(const binary_data & r)
			{
				if (r.size() < sizeof(age) + sizeof(height))
					OONET_THROW_EXCEPTION(exception, "BOOM");
				age = *(unsigned short*)r.get_data_ptr();
				height = *(float *)(r.get_data_ptr() + sizeof(age));
				return sizeof(age) + sizeof(height);
			};
		};


		class MySerializablePOD
			:public serializable
		{
		public:
			unsigned short age;
			float height;

			MySerializablePOD(){}

			MySerializablePOD(unsigned short _a,  float _h)
				:age(_a),
				height(_h)
			{}

			// Comparison
			bool operator==(const MySerializablePOD & r)
			{	return ((age == r.age) && (height == r.height));		}

			// Comparison
			bool operator!=(const MySerializablePOD & r)
			{	return (!(operator==(r)));		}

			virtual binary_data serialize() const
			{	binary_data tmp;

				tmp << serialize_pod(age) << serialize_pod(height);
				return tmp;
			}

			virtual size_t unserialize(const binary_data & r)
			{	binary_data tmp_archive(r);
				tmp_archive >> serialize_pod(age) >> serialize_pod(height);
				return sizeof(age) + sizeof(height);
			};
		};

		bool test_serialize::TestBasic::operator()()
		{	MySerializable obj1, obj2;
			binary_data serial;

			obj1.age = 10;
			obj2.height = 3.412f;

			if (obj1 == obj2)
				return false;

			if (!(obj1 != obj2))
				return false;

			serial = obj1.serialize();
			obj2.unserialize(serial);

			if (obj1 != obj2)
				return false;
			return true;
		}

		bool test_serialize::TestLeftOperator::operator()()
		{	MySerializable obj1, obj2;
			binary_data serial;

			obj1.age = 10;
			obj1.height = 3.412f;

			if (obj1 == obj2)
				return false;

			// External operator
			serial << obj1;
			serial << obj2;

			obj2.unserialize(serial);

			if (obj1 != obj2)
				return false;

			return true;
		}

		bool test_serialize::TestLeftConstOperator::operator()()
		{	MySerializable obj1, obj2;
			binary_data serial;
			const MySerializable & const_obj1 = obj1;

			obj1.age = 10;
			obj1.height = 3.412f;

			if (obj1 != const_obj1)
				return false;

			// External operator
			serial << const_obj1;

			obj2.unserialize(serial);

			if (obj1 != obj2)
				return false;

			return true;
		}

		bool test_serialize::TestRightOperator::operator()()
		{	MySerializable obj1, obj2(30, 42);
			binary_data serial;
			const MySerializable & const_obj1 = obj1;

			obj1.age = 10;
			obj1.height = 3.412f;

			if (obj1 != const_obj1)
				return false;

			// Serialize all data
			serial << const_obj1;
			serial << obj2;

			MySerializable obj3, obj4;

			// Unserialize
			serial >> obj3;
			serial >> obj4;

			if (obj1 != obj3)
				return false;

			if (obj2 != obj4)
				return false;

			return true;
		}

		bool test_serialize::TestMultipleActions::operator()()
		{	MySerializable obj1, obj2(30, 42);
			binary_data serial;
			const MySerializable & const_obj1 = obj1;

			obj1.age = 10;
			obj1.height = 3.412f;

			if (obj1 != const_obj1)
				return false;

			// Serialize all data
			serial << const_obj1 << obj2;

			MySerializable obj3, obj4;

			// Unserialize
			serial >> obj3 >> obj4;

			if (obj1 != obj3)
				return false;

			if (obj2 != obj4)
				return false;

			return true;
		}

		bool test_serialize::TestCastPod::operator()()
		{	MySerializablePOD obj1, obj2(30, 42);
			binary_data serial;
			const MySerializablePOD & const_obj1 = obj1;

			obj1.age = 10;
			obj1.height = 3.412f;

			if (obj1 != const_obj1)
				return false;

			// Serialize all data
			serial << const_obj1 << obj2;

			MySerializablePOD obj3, obj4;

			// Unserialize
			serial >> obj3 >> obj4;

			if (obj1 != obj3)
				return false;

			if (obj2 != obj4)
				return false;

			return true;
		}

		bool test_serialize::TestSerializeSpeed::operator()()
		{	MySerializable obj1, obj2(30, 42);
			binary_data serial;

			obj1.age = 10;
			obj1.height = 3.412f;

			for(long i =0 ;i < 1000000; i++)
			{
				serial.clear();
				serial << obj1 << obj2;
			}

			// Final check
			MySerializable obj3, obj4;

			// Unserialize
			serial >> obj3 >> obj4;

			if (obj1 != obj3)
				return false;

			if (obj2 != obj4)
				return false;

			return true;
		}

		bool test_serialize::TestSerializeSpeedWCast::operator()()
		{	MySerializablePOD obj1(10, 3.1234f), obj2(30, 42);
			binary_data serial;

			for(long i =0 ;i < 1000000; i++)
			{
				serial.clear();
				serial << obj1 << obj2;
			}

			// Final check
			MySerializablePOD obj3, obj4;

			// Unserialize
			serial >> obj3 >> obj4;

			if (obj1 != obj3)
				return false;

			if (obj2 != obj4)
				return false;

			return true;
		}

		bool test_serialize::TestSerializeSpeedConst::operator()()
		{	MySerializable obj1(10, 3.141412f), obj2(30, 42);
			binary_data serial;
			const MySerializable & const_obj1 =obj1;
			const MySerializable & const_obj2 =obj2;

			for(long i =0 ;i < 1000000; i++)
			{
				serial.clear();
				serial << const_obj1 << const_obj2;
			}

			// Final check
			MySerializable obj3, obj4;

			// Unserialize
			serial >> obj3 >> obj4;

			if (obj1 != obj3)
				return false;

			if (obj2 != obj4)
				return false;

			return true;
		}

		bool test_serialize::TestSerializeSpeedConstWCast::operator()()
		{	MySerializablePOD obj1(10, 3.1234f), obj2(30, 42);
			binary_data serial;
			const MySerializablePOD & const_obj1 =obj1;
			const MySerializablePOD & const_obj2 =obj2;

			for(long i =0 ;i < 1000000; i++)
			{
				serial.clear();
				serial << const_obj1 << const_obj2;
			}

			// Final check
			MySerializablePOD obj3, obj4;

			// Unserialize
			serial >> obj3 >> obj4;

			if (obj1 != obj3)
				return false;

			if (obj2 != obj4)
				return false;

			return true;
		}

		bool test_serialize::TestUnSerializeSpeed::operator()()
		{	MySerializable obj1(10, 3.1234f), obj2(30, 42);
			binary_data serial, bk_up;


			bk_up << obj1 << obj2;

			// Final check
			MySerializable obj3, obj4;

			// Unserialize
			for(long i =0 ;i < 1000000; i++)
			{	serial = bk_up;
				serial >> obj3 >> obj4;
			}

			if (obj1 != obj3)
				return false;

			if (obj2 != obj4)
				return false;

			return true;
		}

		bool test_serialize::TestUnSerializeSpeedWCast::operator()()
		{	MySerializablePOD obj1(10, 3.1234f), obj2(30, 42);
			binary_data serial, bk_up;

			bk_up << obj1 << obj2;

			// Final check
			MySerializablePOD obj3, obj4;

			// Unserialize
			for(long i =0 ;i < 1000000; i++)
			{
				serial = bk_up;
				serial >> obj3 >> obj4;
			}

			if (obj1 != obj3)
				return false;

			if (obj2 != obj4)
				return false;

			return true;
		}
		bool test_serialize::TestSerializeStrings::operator()()
		{	std::string str1("lalalaaaaaaaa"), str2("la la lalala lalaaaaaaaaaaaaa");
			binary_data serial;

			serial << str1 << str2;

			// Final check
			string str3, str4;

			// Unserialize
			serial >> str3 >> str4;

			if (str1 != str3)
				return false;

			if (str2 != str4)
				return false;

			return true;
		}

		bool test_serialize::TestSerializeWStrings::operator()()
		{	std::wstring str1(L"lalalaaaaaaaa");
			std::string str2("la la lalala lalaaaaaaaaaaaaa");
			binary_data serial;

			serial << str1 << str2;

			// Final check
			std::wstring str3;
			std::string str4;

			// Unserialize
			serial >> str3 >> str4;

			if (str1 != str3)
				return false;

			if (str2 != str4)
				return false;

			return true;
		}


		bool test_serialize::TestSerializeSpeedString::operator()()
		{	std::wstring str1(L"lalalaaaaaaaa");
			std::string str2("la la lalala lalaaaaaaaaaaaaa");
			binary_data serial;

			for(long i =0; i < 1000000;i++)
			{
				serial.clear();
				serial << str1 << str2;
			}

			// Final check
			std::wstring str3;
			std::string str4;

			// Unserialize
			serial >> str3 >> str4;

			if (str1 != str3)
				return false;

			if (str2 != str4)
				return false;

			return true;
		}

		bool test_serialize::TestUnSerializeSpeedString::operator()()
		{	std::wstring str1(L"lalalaaaaaaaa");
			std::string str2("la la lalala lalaaaaaaaaaaaaa");
			binary_data serial, bk_up;

			bk_up << str1 << str2;

			// Final check
			std::wstring str3;
			std::string str4;

			// Unserialize
			for(long i = 0;i < 1000000;i++)
			{
				serial = bk_up;
				serial >> str3 >> str4;
			}

			if (str1 != str3)
				return false;

			if (str2 != str4)
				return false;

			return true;
		}

		bool test_serialize::TestSerializeSTLList::operator()()
		{	std::list<string> m_list;
			binary_data serial, copy_serial;

			// Add data
			m_list.push_back("test1");
			m_list.push_back("test3");
			m_list.push_back("test5");

			serial << m_list;
			copy_serial = serial;

			// Final check
			std::list<string> m_list2;

			// Unserialize (twice)
			serial >> m_list2;
			copy_serial >> m_list2;

			if (m_list != m_list2)
				return false;

			return true;
		}

		bool test_serialize::TestSerializeSTLVector::operator()()
		{	std::vector<string> m_list;
			binary_data serial, copy_serial;

			// Add data
			m_list.push_back("test1");
			m_list.push_back("test3");
			m_list.push_back("test5");

			serial << m_list;
			copy_serial = serial;

			// Final check
			std::vector<string> m_list2;

			// Unserialize (twice)
			serial >> m_list2;
			copy_serial >> m_list2;

			if (m_list != m_list2)
				return false;

			return true;
		}

		bool test_serialize::TestSerializeSTLPair::operator()()
		{	std::pair<string, string> m_pair1, m_pair2;
			binary_data serial, copy_serial;

			// Add data
			m_pair1 = std::pair<string,string>("test2", "lala");
			
			if (m_pair1 == m_pair2)
				return false;

			serial << m_pair1;

			// Unserialize
			serial >> m_pair2;

			if (!(m_pair1 == m_pair2))
				return false;

			return true;
		}

		bool test_serialize::TestSerializeSTLMap::operator()()
		{	std::map<string, string> m_map;
			binary_data serial, copy_serial;

			// Add data
			m_map["test1"] = "blablala";
			m_map["test4"] = "blabasdfasd";
			m_map["test3"] = "blab";

			serial << m_map;
			copy_serial = serial;

			// Final check
			std::map<string, string> m_map2;

			// Unserialize (twice)
			serial >> m_map2;
			copy_serial >> m_map2;

			if (m_map != m_map2)
				return false;

			return true;
		}

		bool test_serialize::TestSerializeSpeedList::operator()()
		{	std::list<string> m_list;
			binary_data serial, copy_serial;

			// Add data
			m_list.push_back("test1");
			m_list.push_back("test3");
			m_list.push_back("test5");

			for(long i = 0; i < 1000000;i++)
			{	serial.clear();
				serial << m_list;
			}
			copy_serial = serial;

			// Final check
			std::list<string> m_list2;

			// Unserialize (twice)
			serial >> m_list2;
			copy_serial >> m_list2;

			if (m_list != m_list2)
				return false;

			return true;
		}

		bool test_serialize::TestUnSerializeSpeedList::operator()()
		{	std::list<string> m_list;
			binary_data serial, copy_serial;

			// Add data
			m_list.push_back("test1");
			m_list.push_back("test3");
			m_list.push_back("test5");

			serial << m_list;
			copy_serial = serial;

			// Final check
			std::list<string> m_list2;

			// Unserialize (twice)
			for(long i = 0;i < 1000000;i++)
			{	copy_serial = serial;
				copy_serial >> m_list2;
			}

			if (m_list != m_list2)
				return false;

			return true;
		}
	}	// !test namespace
};	// !oonet namespace

// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/monotonic/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <string>
#include <iostream>
#define BOOST_HETEROGENOUS
#include <boost/monotonic/local.hpp>
#include <boost/heterogenous/vector.hpp>
#include <boost/heterogenous/map.hpp>
#include <boost/heterogenous/adaptor.hpp>
#include <boost/bind.hpp>
#include <boost/any.hpp>
#include <boost/variant.hpp>

#define BOOST_TEST_MODULE basic_test test
#include <boost/test/unit_test.hpp>
#include <boost/timer.hpp>

using namespace std;
using namespace boost;
using namespace heterogenous;

namespace mulitple_inheritance_test
{
	struct Q0 : cloneable<Q0>
	{
		int num;
		Q0(int n = 0) : num(n) { }
	};

	/// derive from Q0, which is also cloneable<>
	struct Q1 : Q0, cloneable<Q1>
	{
		string str;
		Q1() { }
		Q1(const char * t) : str(t) { }
	};
	
	struct my_region { };
}

BOOST_AUTO_TEST_CASE(test_clones)
{
	using namespace mulitple_inheritance_test;
	monotonic::local<my_region> local;
	monotonic::allocator<int,my_region> alloc = local.make_allocator<int>();

	Q0 *q0 = create<Q0>(alloc);
	BOOST_ASSERT(typeid(*q0) == typeid(Q0));

	Q0 *q0_c = dynamic_cast<Q0 *>(q0->clone(alloc));
	BOOST_ASSERT(typeid(*q0_c) == typeid(Q0));

	Q1 *q1 = create<Q1>(alloc);
	BOOST_ASSERT(typeid(*q1) == typeid(Q1));

	Q0 *q1_c0  = dynamic_cast<Q0 *>(q1->clone_as<Q0>(alloc));
	BOOST_ASSERT(typeid(*q1_c0) == typeid(Q0));

	Q1 *q1_c1  = dynamic_cast<Q1 *>(q1->clone_as<Q1>(alloc));
	BOOST_ASSERT(typeid(*q1_c1) == typeid(Q1));
}	

BOOST_AUTO_TEST_CASE(test_multiple_inheritance)
{
	using namespace mulitple_inheritance_test;
	typedef heterogenous::vector<> vec;
	vec v;
	v.emplace_back<Q0>(42);
	v.emplace_back<Q1>("foo");
	vec v2 = v;
	BOOST_ASSERT(v2.ref_at<Q0>(0).num == 42);
	BOOST_ASSERT(v2.ref_at<Q1>(1).str == "foo");
}

struct my_base
{
	virtual ~my_base() { }
};

struct T0 : cloneable<T0, my_base>
{
	int num;
	T0() : num(0) { }
	T0(int n) : num(n) { }
};

struct T1 : cloneable<T1, my_base>
{
	std::string str;

	T1() { }
	T1(std::string const &n) : str(n) { }
};

struct T2 : cloneable<T2, my_base>
{
	float real;
	int num;
	std::string str;

	T2() { }
	T2(float f, int n, std::string const &s) : real(f), num(n), str(s) { }

	void print() const
	{
		cout << "derived3: " << real << ", " << num << ", " << str << endl;
	}
};

/// some external type that we cannot change
struct ExternalType
{
	std::string text;
	ExternalType() { }
	ExternalType(const char *T) : text(T) { }
};

/// make an adaptor type, which makes `ExternalType` heterogenous
typedef heterogenous::adaptor<ExternalType, my_base> ExternalType_;

BOOST_AUTO_TEST_CASE(test_vector)
{
	// this uses the base type for the contained elements as a region tag for a monotonic allocator.
	// totally unnecessary, could just use a std::allocator, but this way gives more control
	typedef heterogenous::vector<my_base, monotonic::allocator<my_base, my_base> > vec;

	// use a local scoped object to automatically release resources used by the my_base monotonic 
	// storage region on function exit.
	monotonic::local<my_base> local;
	{
		vec bases;

		// type of thing to insert must be passed explicitly, and must derive from common_base.
		// arguments to push_back are passed directly to ctor
		bases.emplace_back<T0>(42);						
		bases.emplace_back<T1>("foo");
		bases.emplace_back<T2>(3.14f, -123, "spam");
		bases.emplace_back<ExternalType_>("external");

		// perform functor on each contained object of the given type
		bases.for_each<T2>(boost::bind(&T2::print, _1));

		// does a deep copy, preserving concrete types
		vec copy = bases;

		// each object in the container can be retrieved generically as a default_base_type
		my_base &generic0 = copy[0];
		my_base &generic1 = copy[1];
		my_base &generic2 = copy[2];

		// get a reference; will throw bad_cast on type mismatch
		T0 &p1 = copy.ref_at<T0>(0);

		// get a pointer; returns null on type mismatch
		T1 *p2 = copy.ptr_at<T1>(1);
		T2 *p3 = copy.ptr_at<T2>(2);
		
		BOOST_ASSERT(p2);
		BOOST_ASSERT(p3);
		
		BOOST_ASSERT(p1.num == 42);
		BOOST_ASSERT(p2->str == "foo");
		BOOST_ASSERT(p3->real == 3.14f);BOOST_ASSERT(p3->num == -123);BOOST_ASSERT(p3->str == "spam");
		BOOST_ASSERT(copy.ref_at<ExternalType_>(3).text == "external");

		bool caught = false;
		try
		{
			my_base &base = copy.ref_at<T1>(0);
		}
		catch (std::bad_cast)
		{
			caught = true;
		}
		BOOST_ASSERT(caught);

	}
}

namespace map_test
{
	struct my_base
	{
		int number;
		my_base(int n = 0) : number(n) { }
		virtual ~my_base() { }
	};

	struct M0 : cloneable<M0, my_base>
	{
		M0(int n = 0) : my_base(n) {}
	};

	struct M1 : cloneable<M1, my_base>
	{
		string str;
		M1() { }
		M1(const char *s) : str(s) { }
	};

	struct M2 : cloneable<M2, my_base>
	{
	};

	struct M3 : cloneable<M3, my_base>
	{
	};

	struct my_less
	{
		bool operator()(my_base const *left, my_base const *right) const
		{
			return left->number < right->number;
		}
	};
}

BOOST_AUTO_TEST_CASE(test_map)
{
	using namespace map_test;
	typedef heterogenous::map<map_test::my_base,my_less> map_type;
	map_type map;
	map .key<M0>(42).value<M1>("foo")
		.key<M2>().value<M3>()
		;
	M0 *m0 = create<M0>(map.get_allocator(), 42);
	map_type::iterator iter = map.find(m0);
	BOOST_ASSERT(iter!= map.end());
	M1 *m1 = dynamic_cast<M1 *>(iter->second);
	BOOST_ASSERT(m1 != 0);
	BOOST_ASSERT(m1->str == "foo");
}

BOOST_AUTO_TEST_CASE(test_hash)
{
	using namespace map_test;
	M0 a, b;
	BOOST_ASSERT(a.hash() != b.hash());
}


BOOST_AUTO_TEST_CASE(test_any)
{
	// this works, after changing boost::any<> to take an allocator type argument
	typedef any<monotonic::allocator<char> > any_type;
	typedef std::vector<any_type, monotonic::allocator<any_type> > vec;
	vec v;

	// an issue here is that instances are copy-constructed into the container.
	// another issue is that this is effectively typeless.
	// but, types added do not have to derive from anything in order for duplication to work.
	v.push_back(T0(42));
	v.push_back(T1("foo"));

	vec v2 = v;

	BOOST_ASSERT(any_cast<T1 &>(v2[1]).str == "foo");
}

BOOST_AUTO_TEST_CASE(test_variant)
{
	// need to declare all the possible types that could be used at the point of declaration
	typedef variant<T0, T1, T2> var;
	typedef std::vector<var, monotonic::allocator<var> > vec;
	vec v0;
	v0.push_back(T0(42));
	v0.push_back(T1("foo"));
	vec v1 = v0;
	BOOST_ASSERT(boost::get<T1>(v1[1]).str == "foo");
}

//EOF

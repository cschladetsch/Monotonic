// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/monotonic/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/

//#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN

#include <string>
#include <boost/monotonic/monotonic.hpp>

#include <boost/monotonic/shared_allocator.hpp>
#include <boost/monotonic/shared_storage.hpp>
#include <boost/monotonic/thread_local_storage.hpp>
#include <boost/monotonic/shared_allocator.hpp>
#include <boost/monotonic/local.hpp>
#include <boost/monotonic/allocator.hpp>
#include <boost/interprocess/containers/list.hpp>
#include <boost/monotonic/reclaimable_storage.hpp>
#include <boost/monotonic/stack.hpp>
#include <boost/iterator.hpp>

#define BOOST_TEST_MODULE basic_test test
#include <boost/test/unit_test.hpp>
#include <boost/timer.hpp>


template <class II>
bool is_sorted(II F, II L)
{
    II G = F;
    for (++G; G != L; ++F, ++G)
    {
        if (*G < *F)
            return false;
    }
    return true;
}

template <class Cont>
bool is_sorted(Cont const &cont)
{
    return std::is_sorted(boost::begin(cont), boost::end(cont));
}

using namespace std;
using namespace boost;

#ifdef WIN32
// warning C4996: 'std::fill_n': Function call with parameters that may be unsafe
#pragma warning(disable:4996)
#endif

using monotonic::heap_region_tag;

struct num_tag;
struct str_tag;

struct Tracked
{
    static int count;
    Tracked() 
    { 
        ++count; 
        std::cout << "T::T(): " << count << endl;
    }
    Tracked(Tracked const &) 
    { 
        ++count; 
        std::cout << "T::T(T const &): " << count << endl;
    }
    Tracked &operator=(Tracked const &)
    {
        ++count; 
        std::cout << "T &operator=(T const &): " << count << endl;
        return *this;
    }
    ~Tracked()
    {
        --count;
        std::cout << "T::~T(): " << count << endl;
    }
};

int Tracked::count = 0;

BOOST_AUTO_TEST_CASE(test_stack)
{
    monotonic::stack<> stack;
    {
        size_t top = stack.top();
        int &n2 = stack.push<int>();
        /*
        float &f0 = stack.push<float>();
        char &n3 = stack.push<char>();
        Tracked &tracked = stack.push<Tracked>();
        boost::array<int, 42> &a = stack.push_array<int, 42>();

        BOOST_ASSERT(stack.size() == 5);

        size_t peak = stack.top();
        cout << "STACK:" << endl;
        BOOST_FOREACH(monotonic::stack<>::value_type const &elem, stack)
        {
            cout << elem.get_type().name() << endl;
        }
        stack.pop();
        stack.pop();
        stack.pop();
        stack.pop();
        stack.pop();
        size_t top2 = stack.top();
        BOOST_ASSERT(top2 == top);
        BOOST_ASSERT(Tracked::count == 0);
        */
    }
}

BOOST_AUTO_TEST_CASE(test_fixed_stack)
{
    monotonic::fixed_stack<> stack;
    {
        size_t top = stack.top();
        int &n2 = stack.push<int>();
        float &f0 = stack.push<float>();
        char &n3 = stack.push<char>();
        Tracked &tracked = stack.push<Tracked>();
        boost::array<int, 42> &a = stack.push_array<int, 42>();

        BOOST_ASSERT(stack.size() == 5);

        size_t peak = stack.top();
        cout << "STACK:" << endl;
		// CJS 2013
        //BOOST_FOREACH(typename monotonic::fixed_stack<>::value_type const &elem, stack)
        //{
        //    cout << elem.get_type().name() << endl;
        //}
        stack.pop();
        stack.pop();
        stack.pop();
        stack.pop();
        stack.pop();
        size_t top2 = stack.top();
        BOOST_ASSERT(top2 == top);
        BOOST_ASSERT(Tracked::count == 0);
    }
}

template <class Number>
Number work(size_t iterations, std::vector<Number> const &data)
{
    Number sum = 0;
    size_t size = data.size();
    for (size_t i = 0; i < iterations; ++i)
    {
        Number a = data[i % size];
        Number b = data[(i + 500)%size];
        sum += a * b;
    }
    return sum;
}

void test_floats()
{
    size_t iterations = 1000*1000*100;
    size_t outter = 1;//00;//0*1000*10;
    double int_t = 0;
    double float_t = 0;

    size_t size = 100000;
    std::vector<int> ints(size);
    srand(42);
    generate_n(ints.begin(), size, rand);
    std::vector<float> floats(size);
    srand(42);
    generate_n(floats.begin(), size, rand);

    boost::timer int_timer;
    int int_sum = 0;
    for (size_t n = 0; n < outter; ++n)
    {
        int_sum += work(iterations, ints);
    }
    int_t = int_timer.elapsed();
    boost::timer float_timer;
    float float_sum = 0;
    for (size_t n = 0; n < outter; ++n)
    {
        float_sum += work(iterations, floats);
    }
    float_t = float_timer.elapsed();
    cout << int_t << ", " << float_t << "; " << int_sum << ", " << float_sum << endl;
}

BOOST_AUTO_TEST_CASE(test_reclaimable)
{
    std::vector<Tracked, monotonic::allocator<Tracked, heap_region_tag> > vec;
    monotonic::storage_base *store = &monotonic::static_storage<heap_region_tag>::get_storage();
    vec.resize(1);
    vec.erase(vec.begin());
    BOOST_ASSERT(Tracked::count == 0);
}

BOOST_AUTO_TEST_CASE(test_interprocess_list)
{
    monotonic::storage<> storage;
    {
        interprocess::list<int, monotonic::allocator<int> > list(storage);
        generate_n(back_inserter(list), 10, rand);
        list.sort();
        BOOST_ASSERT(is_sorted(list));
    }
}

// define some private regions
struct region0 {};
struct region1 {};

BOOST_AUTO_TEST_CASE(test_set)
{

    monotonic::storage<> storage;
    {
        monotonic::set<monotonic::vector<int> > set(storage);
        BOOST_ASSERT(set.get_allocator().get_storage() == &storage);
        set.insert(monotonic::vector<int>(storage));
        monotonic::vector<int> &v = *set.begin();
        BOOST_ASSERT(v.get_allocator().get_storage() == &storage);

    }
}

BOOST_AUTO_TEST_CASE(test_string)
{
    monotonic::string<> str1;
    monotonic::string<region0> str2;
    monotonic::string<region1> str3;

    str1 = "foo";
    str2 = "bar";
    str3 = "bar";
    BOOST_ASSERT(str2 == str3);
    str1 = str3;
    BOOST_ASSERT(str1 == str3);

    monotonic::static_storage<>::release();
    monotonic::static_storage<region0>::release();
    monotonic::static_storage<region1>::release();

    monotonic::storage<> storage;
    {
        monotonic::string<> str("foo", storage);
        BOOST_ASSERT(str == "foo");
        BOOST_ASSERT(str.get_allocator().get_storage() == &storage);
    }
}

BOOST_AUTO_TEST_CASE(test_map)
{
    monotonic::map<int, monotonic::string<region0>, region1> map;
    map[1] = "foo";
    map[2] = "bar";

    monotonic::static_storage<region0>::release();
    monotonic::static_storage<region1>::release();


    monotonic::storage<> storage;
    {
        monotonic::map<int, monotonic::list<int> > local_map(storage);
        BOOST_ASSERT(local_map.get_allocator().get_storage() == &storage);

        local_map[1].push_back(42);
        
        BOOST_ASSERT(local_map.get_allocator() == local_map[1].get_allocator());
    }
}

BOOST_AUTO_TEST_CASE(test_vector)
{
    monotonic::vector<int> vec;
    vec.resize(100);
    fill_n(vec.begin(), 100, 42);

    monotonic::vector<int, region1> vec2;
    vec2.resize(100);
    fill_n(vec2.begin(), 100, 42);

    BOOST_ASSERT(vec == vec2);
    BOOST_ASSERT(!(vec2 != vec));
    BOOST_ASSERT(!(vec < vec2));
    BOOST_ASSERT(!(vec2 < vec));

    vec2[0] = 40;
    BOOST_ASSERT(vec2 != vec);
    BOOST_ASSERT(vec2 < vec);
    BOOST_ASSERT(!(vec < vec2));

    monotonic::static_storage<>::reset();
    monotonic::static_storage<region1>::reset();


    monotonic::storage<> storage;
    {
        monotonic::vector<monotonic::vector<int> > vec(storage);
        BOOST_ASSERT(vec.get_allocator().get_storage() == &storage);
        vec.resize(5);
        BOOST_ASSERT(vec[0].get_allocator().get_storage() == &storage);

        monotonic::vector<monotonic::map<int, monotonic::string<> > > vec2(storage);
        vec2.resize(1);
        vec2[0][42] = "foo";
        BOOST_ASSERT(vec2.get_allocator().get_storage() == &storage);
        BOOST_ASSERT(vec2[0].get_allocator().get_storage() == &storage);
        BOOST_ASSERT(vec2[0][42].get_allocator().get_storage() == &storage);
    }
}

// why does this stall the unit-tests? after this, other tests are not run...
/*
BOOST_AUTO_TEST_CASE(test_list)
{
    monotonic::list<int> cont;
    fill_n(back_inserter(cont), 100, 42);

    monotonic::list<int, region1> cont2;
    fill_n(back_inserter(cont2), 100, 42);

    BOOST_ASSERT(cont == cont2);
    BOOST_ASSERT(!(cont != cont2));
    BOOST_ASSERT(!(cont < cont2));
    cont.front() = 5;
    BOOST_ASSERT(cont2 != cont);
    BOOST_ASSERT(cont < cont2);
    BOOST_ASSERT(!(cont2 < cont));

    monotonic::static_storage<>::reset();
    monotonic::static_storage<region1>::reset();

    monotonic::storage<> storage;
    {
        monotonic::list<monotonic::list<int> > list(storage);
        BOOST_ASSERT(list.get_allocator().get_storage() == &storage);
        list.push_back(monotonic::list<int>());
        // CJS 2013 BOOST_ASSERT(list.get_allocator().get_storage() == list.front().get_allocator().get_storage());
        //generate_n(back_inserter(list.front()), 100, rand);
        //BOOST_ASSERT(!is_sorted(list.front()));
        //size_t used_before = storage.used();
        //list.front().sort();
        //size_t used_after = storage.used();
        //BOOST_ASSERT(used_after > used_before);
        //BOOST_ASSERT(is_sorted(list.front()));
    }
}
*/

BOOST_AUTO_TEST_CASE(test_deque)
{
    monotonic::deque<int, region0> deq0;
    monotonic::deque<int, region1> deq1;

    deq0.push_back(42);
    deq1.push_back(42);
    BOOST_ASSERT(deq0 == deq1);

    monotonic::static_storage<region0>::reset();
    monotonic::static_storage<region1>::reset();
}


/* fatal error in "test_chain": R6010
BOOST_AUTO_TEST_CASE(test_chain)
{
    monotonic::chain<int, 16, region0> deq0;
    monotonic::chain<int, 16, region1> deq1;

    deq0.push_back(1);
    deq1.push_back(1);
    BOOST_ASSERT(deq0 == deq1);

    deq1.push_back(2);
    deq1.push_back(3);
    BOOST_ASSERT(deq0 != deq1);

    int sum = 0;
	// CJS 2013
    //BOOST_FOREACH(int n, deq1)
    //    sum += n;
    //BOOST_CHECK(sum == 6);
    
    monotonic::static_storage<region0>::reset();
    monotonic::static_storage<region1>::reset();
}
*/

BOOST_AUTO_TEST_CASE(test_local)
{
    monotonic::local<region0> storage0;
    monotonic::local<region1> storage1;
    {
        std::list<int, monotonic::allocator<int, region0> > list0;
        std::list<int, monotonic::allocator<int, region1> > list1;
        fill_n(back_inserter(list0), 100, 42);
        fill_n(back_inserter(list1), 100, 42);

        monotonic::string<region0> str("foo");
        str += "bar";
        BOOST_ASSERT(str == "foobar");
    }
}

//struct region0 {};
//struct region1 {};

BOOST_AUTO_TEST_CASE(test_shared_allocation)
{
    //// use default region and access
    //std::list<int, monotonic::allocator<int> > list;

    //// use specific region and access
    //std::list<int, monotonic::allocator<int, region0, monotonic::shared_access_tag> > list;
    //std::list<int, monotonic::allocator<int, region0, monotonic::thread_local_access_tag> > list;

    //// using wrapped container
    //monotonic::list<int> list;
    //monotonic::list<int, region0, monotonic::shared_access_tag> list;
    //monotonic::list<int, region0, monotonic::thread_local_access_tag> list;

    //// use different regions
    //monotonic::map<int, monotonic::list<monotonic::string, region1>, region0> map;
}

BOOST_AUTO_TEST_CASE(test_regional_allocation)
{
    typedef std::list<int, monotonic::allocator<int, region0> > List0;
    typedef std::list<int, monotonic::allocator<int, region1> > List1;
    {
        List0 list0;
        generate_n(back_inserter(list0), 10, rand);
        list0.sort();

        List1 list1;
        generate_n(back_inserter(list1), 10, rand);
        list1.sort();
    }
}


BOOST_AUTO_TEST_CASE(test_local_storage)
{
    monotonic::storage<10*1024> storage;
    {
        storage.allocate_bytes(123);
        BOOST_ASSERT(storage.fixed_used() == 123);
        BOOST_ASSERT(storage.heap_used() == 0);
        BOOST_ASSERT(storage.used() == 123);

        storage.reset();
        BOOST_ASSERT(storage.fixed_used() == 0);
        BOOST_ASSERT(storage.heap_used() == 0);
        BOOST_ASSERT(storage.used() == 0);

        // test alignment
        storage.reset();
        storage.allocate_bytes(12, 16);

        storage.allocate_bytes(12, 64);
        storage.reset();
    }
}

BOOST_AUTO_TEST_CASE(test_local_storage_to_heap)
{
    return;
    monotonic::storage<16> storage;
    {
        storage.allocate_bytes(16);
        BOOST_ASSERT(storage.heap_used() == 0);

        storage.allocate_bytes(200);
        BOOST_ASSERT(storage.heap_used() == 200);

        storage.release();

        BOOST_ASSERT(storage.used() == 0);
        storage.allocate_bytes<2000>();
        BOOST_ASSERT(storage.fixed_used() == 0);
        BOOST_ASSERT(storage.heap_used() == 2000);

        storage.allocate_bytes<10>();
        BOOST_ASSERT(storage.fixed_used() == 10);
        BOOST_ASSERT(storage.heap_used() == 2000);
    }
}

BOOST_AUTO_TEST_CASE(test_local_storage_iter)
{
    size_t length = 4;
    // storage starts on the stack (in this case, 10k of it), then merges into the heap as needed
    monotonic::storage<10*1024> storage;
    for (size_t n = 0; n < length; ++n)
    {
        // create a new int from storage
        int &n0 = storage.create<int>();

        // create a new string (uses correct alignment)
        string const &s1 = storage.create<string>("foo");
        BOOST_ASSERT(s1 == "foo");

        // allocate 37 bytes with alignment 1
        char *array0 = storage.allocate_bytes(37);
        fill_n(array0, 37, 42);

        // allocate 2537 bytes with 64-byte alignment
        char *array1 = storage.allocate_bytes(2537, 64);
        fill_n(array1, 2537, 123);

        // allocate 1283 bytes with machine alignment
        char *array2 = storage.allocate_bytes<1283>();
        fill_n(array2, 1283, 42);

        boost::array<int, 42> &array3 = storage.create<boost::array<int, 42> >();

        // destroy objects. this only calls the destructors; it does not release memory
        storage.destroy(s1);

        //cout << "storage.fixed, heap, total used: " << storage.fixed_used() << ", " << storage.heap_used() << ", " << storage.used() << endl;
    }
    // storage is released. if this was only ever on the stack, no work is done
}

BOOST_AUTO_TEST_CASE(test_ctors)
{
    string foo = "foo";
    {
        monotonic::vector<char> v1(foo.begin(), foo.end());
        BOOST_CHECK(v1.size() == 3);
        BOOST_CHECK(equal(v1.begin(), v1.end(), "foo"));

        monotonic::vector<char> v2(6, 'x');
        BOOST_CHECK(v2.size() == 6);
        BOOST_CHECK(equal(v2.begin(), v2.end(), "xxxxxx"));

        monotonic::set<char> s2(foo.begin(), foo.end());
        BOOST_CHECK(s2.size() == 2);
        BOOST_CHECK(s2.find('f') != s2.end());
        BOOST_CHECK(s2.find('o') != s2.end());

        monotonic::vector<pair<int, string> > v;
        v.push_back(make_pair(42,"foo"));
        v.push_back(make_pair(123,"bar"));

        monotonic::map<int, string> m1(v.begin(), v.end());
        BOOST_CHECK(m1.find(42) != m1.end());
        BOOST_CHECK(m1.find(123) != m1.end());

        monotonic::list<int> l1(foo.begin(), foo.end());
        BOOST_CHECK(equal(l1.begin(), l1.end(), "foo"));
    }
    monotonic::reset_storage();
}

BOOST_AUTO_TEST_CASE( test_copy )
{
    monotonic::storage<> storage;
    monotonic::vector<int> v1(storage);

    for (int n = 0; n < 100; ++n)
        v1.push_back(n);

    size_t rem1 = storage.fixed_remaining();
    monotonic::vector<int> v2(v1);
    size_t rem2 = storage.fixed_remaining();

    //BOOST_CHECK(v2 == v1);
    //BOOST_CHECK_EQUAL(rem1 - rem2, 12 + 100*sizeof(int));
}

#if 0

BOOST_AUTO_TEST_CASE(test_shared_allocators)
{
    monotonic::storage<> sa, sb;
    {
        monotonic::vector<int> v0(sa), v1(sa);
        monotonic::vector<int> v2(sb), v3(sb);
        monotonic::list<int> l0(sa), l1(sb);

        BOOST_CHECK(v0.get_allocator() == v1.get_allocator());
        BOOST_CHECK(v2.get_allocator() == v3.get_allocator());
        BOOST_CHECK(v0.get_allocator() != v2.get_allocator());
        BOOST_CHECK(v3.get_allocator() != v1.get_allocator());

        for (int n = 0; n < 10; ++n)
            v0.push_back(n);

        v1 = v0;
        v1.swap(v2);    // swap from different allocators means they are copied
        BOOST_CHECK(v1.empty() && v3.empty() && v1 == v3);

        BOOST_CHECK(v2 == v0); // both are now [0..9]

        v1.swap(v0);    // swap from same allocators means no copying
        BOOST_CHECK(v2 == v1);
        BOOST_CHECK(v0 == v3);

        //l0.assign(v0.begin(), v0.end());
        //l1 = l0;
        //BOOST_CHECK(l0 == l1);
    }
}
#endif

BOOST_AUTO_TEST_CASE(test_basic)
{
    monotonic::storage<> storage;
    {
        monotonic::vector<int> v1(storage);

        for(int i = 0; i < 100; ++i)
            v1.push_back(i);

        monotonic::vector<int> copy(storage);
        size_t len = storage.used();
        copy = v1;
        size_t len2 = storage.used();

        BOOST_CHECK(copy == v1);

        // create a list that uses inline, monotonically-increasing storage
        monotonic::list<int> list(storage);
        list.push_back(100);
        list.push_back(400);
        list.erase(list.begin());

        // a map from the same storage
        monotonic::map<int, float> map(storage);
        map[42] = 3.14f;
        BOOST_CHECK(map[42] == 3.14f);

        // a set...
        monotonic::set<float> set(storage);
        set.insert(3.14f);
        set.insert(-123.f);
        BOOST_CHECK(set.size() == 2);
    }
}

//EOF

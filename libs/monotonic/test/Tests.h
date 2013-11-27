// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/monotonic/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/

#pragma once

// these are guaranteed to be at least length + length*length long
extern std::vector<int> random_numbers;
extern std::vector<std::pair<int, int> > random_pairs;

struct test_vector_create
{
    template <class Alloc>
    int test(Alloc alloc, size_t length) const
    {
        std::vector<int, typename Rebind<Alloc, int>::type> vector(length*rand()/RAND_MAX);
        return vector.size();
    }
};

struct test_vector_dupe
{
    template <class Alloc>
    int test(Alloc alloc, size_t length) const
    {
        typedef std::vector<int, typename Rebind<Alloc, int>::type> Vector;
        Vector vector(length*rand()/RAND_MAX);
        Vector dupe = vector;
        return dupe.size();
    }
};

template <class Ty>
struct test_vector_sort
{
    template <class Alloc>
    int test(Alloc, size_t length) const
    {
        std::vector<Ty, typename Rebind<Alloc, Ty>::type> vector(length);
        for (size_t n = 0; n < length; ++n)
            vector[n] = length - n;
        sort(vector.begin(), vector.end());
        return 0;
    }
};

struct test_vector_accumulate
{
    template <class Alloc>
    int test(Alloc alloc, size_t length) const
    {
        std::vector<int, typename Rebind<Alloc, int>::type> vector(length*rand()/RAND_MAX);
        return accumulate(vector.begin(), vector.end(), 0);
    }
};

struct test_vector_accumulate_unaligned
{
    template <class Alloc>
    int test(Alloc alloc, size_t length) const
    {
        std::vector<Unaligned, typename Rebind<Alloc, Unaligned>::type> vector(length);
        int total = 0;
        BOOST_FOREACH(Unaligned const &val, vector)
        {
            total += val.c[2];
        }
        return total;
    }
};

template <class Ty>
struct test_list_create
{
    template <class Alloc>
    int test(Alloc alloc, size_t length) const
    {
        std::list<Ty, typename Rebind<Alloc, Ty>::type> list;
        fill_n(back_inserter(list), length, 42);
        return 0;
    }
};

struct test_list_dupe
{
    template <class Alloc>
    int test(Alloc alloc, size_t length) const
    {
        typedef std::list<int, typename Rebind<Alloc, int>::type> List;
        List list;
        fill_n(back_inserter(list), length, 42);
        List dupe = list;
        return dupe.size();
    }
};

template <class Ty>
struct test_list_sort
{
    template <class Alloc>
    int test(Alloc alloc, size_t length) const
    {
        std::list<Ty, typename Rebind<Alloc, Ty>::type> list;
        for (size_t n = 0; n < length; ++n)
            list.push_back(length - n);
        list.sort();
        return 0;
    }
};

struct test_set_vector
{
    template <class Alloc>
    int test(Alloc alloc, size_t length) const
    {
        typedef std::vector<int, typename Rebind<Alloc, int>::type> Vector;
        typedef std::set<Vector, std::less<Vector>, typename Rebind<Alloc, Vector>::type> Set;
        int dummy = 0;
        Set set;
        for (size_t n = 0; n < length; ++n)
        {
            size_t size = length*rand()/RAND_MAX;
            Vector vector(size);
            generate_n(back_inserter(vector), size, rand);
            set.insert(vector);
            dummy += set.size();
        }
        return dummy;
    }
};

template <class Map>
int test_map_vector_impl(size_t length)
{
    Map map;
    size_t mod = length/10;
    if (mod == 0)
        mod = 5;
    for (size_t n = 0; n < length; ++n)
    {
        int random = random_numbers[n] % mod;
        map[random].push_back(n);
    }
    return 0;
}

template <class Ty>
struct test_map_vector
{
    template <class Alloc>
    int test(Alloc, size_t length) const
    {
        return test_map_vector_impl<std::map<int
            , std::vector<Ty, typename Rebind<Alloc, Ty>::type>
            , std::less<int>
            , typename Rebind<Alloc, int>::type> >(length);
    }
};

struct test_map_list_unaligned
{
    template <class Alloc>
    int test(Alloc alloc, size_t length) const
    {
        std::map<int
            , std::list<Unaligned, typename Rebind<Alloc, Unaligned>::type>
            , std::less<int>
            , typename Rebind<Alloc, int>::type
        > map;
        size_t mod = length/10;
        for (size_t n = 0; n < length; ++n)
        {
            int random = random_numbers[n] % mod;
            map[random].push_back(n);
        }
        return 0;
    }
};

struct test_string_cat
{
    template <class Alloc>
    int test(Alloc alloc, size_t length) const
    {
        typedef std::basic_string<char, std::char_traits<char>, typename Rebind<Alloc, char>::type> String;
        String str = "foo";
        for (size_t n = 0; n < length; ++n)
        {
            str += "bar";
        }
        return 0;
    }
};

struct test_list_string
{
    template <class Alloc>
    int test(Alloc alloc, size_t length) const
    {
        typedef std::basic_string<char, std::char_traits<char>, typename Rebind<Alloc, char>::type> String;
        typedef std::list<String, typename Rebind<Alloc, String>::type> List;
        List list;
        for (size_t n = 0; n < length; ++n)
        {
            list.push_back(String("spam"));
        }
        return 0;
    }
};

//Build a std::map of size n.  Loop for O(n^2) iterations.  
//In each iteration insert one random element and lookup with lower_bound one random element and remove it.  
//Precompute the random numbers and don't include the rand() calls in the time measurement of the benchmark.
//http://tinyurl.com/mp6sub
struct test_map_erase
{
    template <class Alloc>
    int test(Alloc alloc, size_t length) const
    {
        typedef std::map<int
            , int
            , std::less<int>
            , typename Rebind<Alloc, int>::type
        > Map;
        Map map;
        std::copy(random_pairs.begin(), random_pairs.begin() + length, inserter(map, map.begin()));
        size_t max_length = length*length;
        for (size_t n = 0; n < max_length; ++n)
        {
            map.insert(random_pairs[length + n]);
            int random_remove = random_numbers[n];
            typename Map::iterator iter = map.lower_bound(random_remove);
            if (iter != map.end())
                map.erase(iter);
        }
        return 0;
    }
};

//EOF

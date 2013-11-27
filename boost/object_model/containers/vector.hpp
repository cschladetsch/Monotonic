// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_CONTAINERS_VECTOR_HPP
#define BOOST_OBJECT_MODEL_CONTAINERS_VECTOR_HPP

#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/generic/object.hpp>

BOOST_OM_BEGIN

namespace containers
{
    template <class Alloc>
    struct vector
    {
        //typedef boost::containers::vector<generic::object, Alloc> implementation;
        typedef std::vector<generic::object, Alloc> implementation;
        typedef typename implementation::value_type value_type;
        typedef typename implementation::iterator iterator;
        typedef typename implementation::const_iterator const_iterator;
        typedef typename implementation::reference reference;
        typedef typename implementation::const_reference const_reference;

    private:
        implementation impl;

    public:
        size_t size() const
        {
            return impl.size();
        }

        const_iterator begin() const
        {
            return impl.begin();
        }
        iterator begin()
        {
            return impl.begin();
        }
        const_iterator end() const
        {
            return impl.end();
        }
        iterator end()
        {
            return impl.end();
        }
        const_reference front() const
        {
            return impl.front();
        }
        reference front()
        {
            return impl.front();
        }
        const_reference back() const
        {
            return impl.back();
        }
        reference back()
        {
            return impl.back();
        }
        void push_back(generic::object obj)
        {
            impl.push_back(obj);
        }
        void pop_back()
        {
            impl.pop_back();
        }
        generic::object pop()
        {
            generic::object top = back();
            impl.pop_back();
            return top;
        }
        reference at(size_t index)
        {
            return impl.at(index);
        }
        const_reference at(size_t index) const
        {
            return impl.at(index);
        }
        reference operator[](size_t index)
        {
            return impl[index];
        }
        const_reference operator[](size_t index) const
        {
            return impl[index];
        }
    };

} // namespace containers

namespace type
{
    /// the type-traits for a vector with any allocator are the same
    template <class Al>
    struct traits<containers::vector<Al> > : traits_base<containers::vector<Al>, number::Vector >
    {
        BOOST_STATIC_CONSTANT(number::value_type, type_number = number::Vector );
        static const char *name;
    };
    template <class Al>
    const char *traits<containers::vector<Al> >::name = "vector";
}

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_CONTAINERS_VECTOR_HPP

//EOF

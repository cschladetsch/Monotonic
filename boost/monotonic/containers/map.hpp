// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_MAP_HPP
#define BOOST_MONOTONIC_MAP_HPP

#include <map>
#include <boost/interprocess/containers/map.hpp>
#include <boost/monotonic/detail/prefix.hpp>
#include <boost/monotonic/detail/container.hpp>

namespace boost
{
    namespace monotonic
    {
        /// A map that uses a monotonic allocator
        template <class K                            // key-type
            , class T                                // value-type
            , class Region = default_region_tag        // allocation region
            , class P = std::less<K>                // predicate
            , class Access = default_access_tag        // access type
        >
        struct map : detail::container<map<K,T,Region,P,Access> >
        {
            typedef P Predicate;
            typedef allocator<K,Region,Access> Allocator;
            typedef detail::container<map<K,T,Region,P,Access> > Parent;
            typedef detail::Create<detail::is_monotonic<T>::value, T> Create;

            typedef std::map<K,T,P,Allocator > Map, Implementation;
            typedef typename Map::iterator iterator;
            typedef typename Map::const_iterator const_iterator;
            typedef typename Map::mapped_type mapped_type;
            typedef typename Map::value_type value_type;
            typedef typename Map::key_type key_type;
            typedef typename Map::size_type size_type;

        private:
            Implementation impl;
            Predicate pred;        ///< do we really need to store a copy of the predicate? used in operator[]

        public:

            map() { }
            map(Allocator const &A)
                : impl(Predicate(), A) { }
            map(Predicate Pr, Allocator A = Allocator()) 
                : impl(Pr, A), pred(Pr) { }
            map(const map& other)
                : impl(other.impl), pred(other.pred) { }
            template <class II>
            map(II F, II L, Predicate const &Pr = Predicate(), Allocator A = Allocator())
                : impl(F,L,Pr,A), pred(Pr) { }

            Allocator get_allocator() const
            {
                return impl.get_allocator();
            }
            void clear()
            {
                impl.clear();
            }
            size_type size() const
            {
                return impl.size();
            }
            bool empty() const
            {
                return impl.empty();
            }
            iterator begin()
            {
                return impl.begin();
            }
            iterator end()
            {
                return impl.end();
            }
            const_iterator begin() const
            {
                return impl.begin();
            }
            const_iterator end() const
            {
                return impl.end();
            }

            void insert(const value_type& value)
            {
                impl.insert(value);
            }
            void erase(iterator first)
            {
                impl.erase(first);
            }
            void erase(iterator first, iterator last)
            {
                impl.erase(first, last);
            }
            size_type erase(key_type const &key)
            {
                return impl.erase(key);
            }
            mapped_type& operator[](const key_type& key)
            {
                iterator where = impl.lower_bound(key);
                if (where == impl.end() || pred(key, where->first))
                {
                    where = impl.insert(where, value_type(key, Create::Given(this->Parent::get_storage())));
                }
                return where->second;
            }
            iterator find(key_type const &key)
            {
                return impl.find(key);
            }
            const_iterator find(key_type const &key) const
            {
                return impl.find(key);
            }
        };

    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_MAP_HPP

//EOF

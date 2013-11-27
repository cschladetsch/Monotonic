// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_SET_HPP
#define BOOST_MONOTONIC_SET_HPP

#include <boost/interprocess/containers/set.hpp>
#include <boost/monotonic/detail/prefix.hpp>
#include <boost/monotonic/detail/container.hpp>

namespace boost
{
    namespace monotonic
    {
        /// A std::set<T,P> that uses a monotonic allocator
        template <class T
            , class Region = default_region_tag        // allocation region
            , class P = std::less<T>                // predicate
            , class Access = default_access_tag>    // access type
        struct set : detail::container<set<T,Region,P,Access> >
        {
            typedef allocator<T,Region,Access> Allocator;
            typedef P Predicate;
            typedef interprocess::set<T,P,Allocator > Set;
            typedef typename Set::iterator iterator;
            typedef typename Set::const_iterator const_iterator;
            typedef typename Set::value_type value_type;
            typedef typename Set::key_type key_type;
            typedef typename Set::size_type size_type;
            typedef detail::Create<detail::is_monotonic<T>::value, T> Create;
            typedef detail::container<set<T,Region,P,Access> > Parent;

        private:
            Set impl;

        public:
            set() { }
            set(Allocator A) 
                : impl(Predicate(), A) { }    
            set(Predicate Pr, Allocator A) 
                : impl(Pr, A) { }
            template <class II>
            set(II F, II L, Allocator A = Allocator())
                : impl(F,L,Predicate(),A) { }
            template <class II>
            set(II F, II L, Predicate Pr, Allocator A = Allocator())
                : impl(F,L,Pr,A) { }

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
                impl.insert(Create::Given(this->Parent::get_storage(), value));
            }
            void erase(iterator first)
            {
                impl.erase(first);
            }
            void erase(iterator first, iterator last)
            {
                impl.erase(first, last);
            }
            iterator find(value_type const &key)
            {
                return impl.find(key);
            }
            const_iterator find(value_type const &key) const
            {
                return impl.find(key);
            }
        };

    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_SET_HPP

//EOF

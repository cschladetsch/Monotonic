// Copyright (C) 2009-2020 Christian@Schladetsch.com
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MONOTONIC_ALLOCATOR_BASE_HPP
#define BOOST_MONOTONIC_ALLOCATOR_BASE_HPP

#ifdef BOOST_HETEROGENOUS
#include <boost/cloneable/abstract_allocator.hpp>
#endif

#include <boost/monotonic/detail/prefix.hpp>
#include <boost/monotonic/static_storage.hpp>
#include <boost/monotonic/detail/container.hpp>
#include <boost/monotonic/detail/construct.hpp>
//#include <boost/type_traits/has_trivial_destructor.hpp>

namespace boost
{
    namespace monotonic
    {
        /// common to other monotonic allocators for type T of type Derived
        template <class T, class Derived>
        struct allocator_base
#ifdef BOOST_HETEROGENOUS
            : cloneable::abstract_allocator
#endif
        {
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef T *pointer;
            typedef const T *const_pointer;
            typedef T &reference;
            typedef const T &const_reference;
            typedef T value_type;
            typedef detail::Construct<detail::is_monotonic<T>::value> Construct;

            static constexpr size_t alignment = 64;//CJS TODO std::aligned_storage<sizeof(T)>::type;

            storage_base *storage;

#ifdef BOOST_HETEROGENOUS
            // override for abstract_allocator
            virtual cloneable::abstract_allocator::pointer allocate_bytes(size_t num_bytes, size_t alignment)
            {
                void *ptr = storage->allocate(num_bytes, alignment);
                return reinterpret_cast<cloneable::abstract_allocator::pointer>(ptr);
            }

            virtual void deallocate_bytes(char * /*bytes*/, size_t /*alignment*/ )
            {
                // do nothing
            }
#endif

        public:
            allocator_base(storage_base &store) throw() 
                : storage(&store) { }

            allocator_base(const allocator_base& alloc) throw() 
                : storage(alloc.storage) { }

            template <class U, class D> 
            allocator_base(const allocator_base<U,D> &alloc) throw()
                : storage(alloc.storage) { }

            pointer address(reference x) const
            {
                return &x;
            }

            const_pointer address(const_reference x) const
            {
                return &x;
            }

            pointer allocate(size_type num, const void * /*hint*/ = 0)
            {
                return reinterpret_cast<T *>(storage->allocate(num*sizeof(T), alignment));
            }

            void deallocate(pointer ptr, size_type num)
            {
                storage->deallocate(ptr);
            }

            size_type max_size() const throw()
            {
                if (!storage)
                    return 0;
                return storage->max_size()/sizeof(value_type);
            }

            void construct(pointer ptr)
            {
                Construct::Given(ptr, DerivedPtr());
            }

            void construct(pointer ptr, const T& val)
            {
                Construct::Given(ptr, val, DerivedPtr());
            }

            Derived *DerivedPtr()
            {
                return static_cast<Derived *>(this);
            }

            void destroy(pointer ptr)
            {
                if (!ptr)
                    return;
                destroy(ptr, std::is_trivially_destructible<value_type>());
            }

            void destroy(pointer ptr, const std::false_type& )
            {
                (*ptr).~value_type();
            }

            void destroy(pointer, const std::true_type& )
            { 
            }

            void swap(allocator<value_type> &other)
            {
                std::swap(storage, other.storage);
            }

            storage_base *get_storage() const
            {
                return storage;
            }

            friend bool operator==(allocator_base<T,Derived> const &A, allocator_base<T,Derived> const &B) 
            { 
                return A.storage == B.storage;
            }

            friend bool operator!=(allocator_base<T,Derived> const &A, allocator_base<T,Derived> const &B) 
            { 
                return A.storage != B.storage;
            }
        };

    } // namespace monotonic

} // namespace boost

#include <boost/monotonic/detail/postfix.hpp>

#endif // BOOST_MONOTONIC_ALLOCATOR_BASE_HPP

//EOF

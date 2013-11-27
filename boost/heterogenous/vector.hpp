// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HETEROGENOUS_VECTOR_HPP
#define BOOST_HETEROGENOUS_VECTOR_HPP

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/monotonic/allocator.hpp>
#include <boost/foreach.hpp>

#include <boost/cloneable/cloneable.hpp>
#include <boost/cloneable/detail/make_clone_allocator.hpp>
#include <boost/cloneable/detail/allocation.hpp>

namespace boost 
{
	namespace heterogenous
	{
		using namespace cloneable;

		/// a vector of heterogenous objects
		template <class Base, class Alloc>//, class AbstractBase>
		struct vector
		{
			typedef Base base_type;
			//typedef AbstractBase abstract_base_type;
			typedef abstract_cloneable<Base> abstract_base_type;
			typedef typename make_clone_allocator<Alloc>::type allocator_type;
			typedef ptr_vector<abstract_base_type, allocator, allocator_type> implementation;
			//typedef ptr_vector<Base, allocator, allocator_type> implementation;
			typedef typename implementation::value_type value_type;
			typedef typename implementation::reference reference;
			typedef typename implementation::const_reference const_reference;
			typedef typename implementation::iterator iterator;
			typedef typename implementation::const_iterator const_iterator;

		private:
			implementation impl;

		public:
			vector()
			{
			}

			vector(allocator_type &a) 
				: impl(a)
			{
			}

			/* purposefully elided
			template <class II>
			vector(II F, II L, allocator_type a = allocator_type());
			vector(size_t reserved);
			*/

			template <class Ty, class Fun>
			Fun for_each(Fun fun)
			{
				BOOST_FOREACH(base_type &b, *this)
				{
					if (Ty *ptr = dynamic_cast<Ty *>(&b))
					{
						fun(*ptr);
					}
				}
				return fun;
			}

			template <class Ty, class Fun>
			Fun for_each(Fun fun) const
			{
				BOOST_FOREACH(const base_type &base, *this)
				{
					if (Ty *ptr = dynamic_cast<Ty *>(&base))
					{
						fun(*ptr);
					}
				}
				return fun;
			}

			size_t size() const
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

			value_type &back()
			{
				return impl.back();
			}
			const value_type &back() const
			{
				return impl.back();
			}
			value_type &front()
			{
				return impl.front();
			}
			const value_type &front() const
			{
				return impl.front();
			}

			reference at(size_t n)
			{
				return impl.at(n);
			}
			const_reference at(size_t n) const
			{
				return impl.at(n);
			}
			reference operator[](size_t n)
			{
				return impl[n];
			}
			const_reference operator[](size_t n) const
			{
				return impl[n];
			}

			template <class Other>
			bool is_type_at(size_t n) const
			{
				return ptr_at<Other>(n) != 0;
			}
			
			template <class Other>
			Other &ref_at(size_t n)
			{
				Other *ptr = ptr_at<Other>(n);
				if (ptr == 0)
					throw std::bad_cast();
				return *ptr;
			}
			template <class Other>
			const Other &ref_at(size_t n) const
			{
				const Other *ptr = ptr_at<const Other>(n);
				if (ptr == 0)
					throw std::bad_cast();
				return *ptr;
			}

			template <class Other>
			Other *ptr_at(size_t n)
			{
				return dynamic_cast<Other *>(&at(n));
			}
			template <class Other>
			const Other *ptr_at(size_t n) const
			{
				return dynamic_cast<const Other *>(&at(n));
			}

			// TODO: use variadic arguments or BOOST_PP to pass ctor args
			template <class U>
			void emplace_back()
			{
				impl.push_back(detail::construct<U,base_type>(get_allocator()).to_abstract());
			}
			template <class U, class A0>
			void emplace_back(A0 a0)
			{
				impl.push_back(detail::construct<U,base_type>(get_allocator(), a0).to_abstract());
			}
			template <class U, class A0, class A1>
			void emplace_back(A0 a0, A1 a1)
			{
				impl.push_back(detail::construct<U,base_type>(get_allocator(), a0,a1).to_abstract());
			}
			template <class U, class A0, class A1, class A2>
			void emplace_back(A0 a0, A1 a1, A2 a2)
			{
				impl.push_back(detail::construct<U,base_type>(get_allocator(), a0,a1,a2).to_abstract());
			}

			typename implementation::allocator_type get_allocator()
			{
				return impl.get_allocator();
			}
		};
	
	} // namespace heterogenous

} // namespace boost

#include <boost/heterogenous/detail/suffix.hpp>

#endif // BOOST_HETEROGENOUS_VECTOR_HPP

//EOF

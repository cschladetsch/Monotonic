// Copyright (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HETEROGENOUS_MAKE_CLONEABLE_ALLOCATOR_HPP
#define BOOST_HETEROGENOUS_MAKE_CLONEABLE_ALLOCATOR_HPP

#include <boost/type_traits/is_convertible.hpp>
#include <boost/heterogenous/detail/prefix.hpp>
#include <boost/heterogenous/allocator.hpp>

namespace boost
{
	namespace heterogenous
	{
		namespace impl
		{
			/// adapts a given Alloc type, modelling the v1 std::allocator concept, to provide
			/// services required by abstract_allocator
			template <class Alloc>
			struct clone_allocator : Alloc, abstract_allocator
			{
				typedef typename Alloc::template rebind<char>::other CharAlloc;

				clone_allocator() { }
				clone_allocator(Alloc &a) : Alloc(a) { }

				struct header
				{
					abstract_allocator::pointer allocated_ptr;
					size_t num_bytes;
				};

				abstract_allocator::pointer allocate_bytes(size_t num_bytes, size_t /*alignment*/)
				{
					CharAlloc alloc(*this);
					return alloc.allocate(num_bytes);
					
					// TODO: do correct alignment, store padding information so dealloc 
					// can retrieve the originally allocated pointer

					//CharAlloc alloc(*this);
					//header head;
					//head.num_bytes = sizeof(header) + num_bytes + alignment;	// don't need this much, but will do for now
					//abstract_allocator::pointer char_ptr = alloc.allocate(head.num_bytes);
					//head.allocated_ptr = (header *)char_ptr;
					//*head.allocated_ptr = head;
					//abstract_allocator::pointer base = char_ptr + sizeof(header);
					//base += calc_padding(base, alignment);
					//return base;
				}

				void deallocate_bytes(abstract_allocator::pointer ptr, size_t /*alignment*/)
				{
					CharAlloc alloc(*this);
					alloc.deallocate(ptr);
					
					// TODO: retreive the originally allocated pointer

					//header *head = reinterpret_cast<header *>(ptr - sizeof(head));
					//alloc.deallocate(head->allocated_ptr, head->num_bytes);
				}

			};

			template <class Alloc, bool>
			struct make_clone_allocator
			{		
				typedef clone_allocator<Alloc> type;
			};

			template <class Alloc>
			struct make_clone_allocator<Alloc, true>
			{
				typedef Alloc type;
			};
		}

		template <class Alloc>
		struct make_clone_allocator
		{
			typedef boost::is_convertible<Alloc *, abstract_allocator *> is_convertible;
			BOOST_STATIC_CONSTANT(bool, is_clone_alloc = is_convertible::value);
			typedef typename impl::make_clone_allocator<Alloc, is_clone_alloc>::type type;
		};

	} // namespace heterogenous

} // namespace boost

#include <boost/heterogenous/detail/suffix.hpp>

#endif // BOOST_HETEROGENOUS_MAKE_CLONEABLE_ALLOCATOR_HPP

//EOF

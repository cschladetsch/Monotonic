// (C) 2009 Christian Schladetsch
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// documentation at https://svn.boost.org/svn/boost/sandbox/monotonic/libs/object_model/doc/index.html
// sandbox at https://svn.boost.org/svn/boost/sandbox/monotonic/object_model/

#ifndef BOOST_OBJECT_MODEL_DETAIL_CLASS_BASE_HPP
#define BOOST_OBJECT_MODEL_DETAIL_CLASS_BASE_HPP

#include <map>
#include <boost/object_model/detail/prefix.hpp>
#include <boost/object_model/generic/class.hpp>

BOOST_OM_BEGIN

namespace detail
{
    template <class Registry>
    struct klass_base : generic::klass
    {
        typedef typename Registry::identifier_type Label;
        typedef typename Registry::allocator_type allocator_type;

        // TODO: use unordered_map
        typedef std::map<Label, generic::property const *, std::less<Label>, allocator_type> properties_type;
        typedef std::map<Label, generic::method<Registry> const *, std::less<Label>, allocator_type> methods_type;

    private:
        properties_type properties;
        methods_type methods;
        Registry &factory;

    public:
        klass_base(Registry &reg, generic::class_name ident, type::number num)
            : generic::klass(ident, num), factory(reg)
        {
        }
        ~klass_base()
        {
            BOOST_FOREACH(methods_type::value_type &val, methods)
            {
                factory.allocator_destroy_deallocate(const_cast<generic::method<Registry> *>(val.second));
            }
        }

        void add_method(Label const &name, generic::method<Registry> const *meth)
        {
            methods[name] = meth;
        }

        generic::method<Registry> const *get_method(Label const &name) const
        {
            methods_type::const_iterator iter = methods.find(name);
            return iter == methods.end() ? 0 : iter->second;
        }

        bool has_method(Label const &name) const
        {
            return methods.find(name) != methods.end();
        }

        bool has_field(Label const &name) const
        {
            return properties.find(name) != properties.end();
        }
    };

} // namespace detail

BOOST_OM_END

#include <boost/object_model/detail/postfix.hpp>

#endif // BOOST_OBJECT_MODEL_DETAIL_CLASS_BASE_HPP

//EOF

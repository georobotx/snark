// This file is part of snark, a generic and flexible library
// for robotics research.
//
// Copyright (C) 2011 The University of Sydney
//
// snark is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// snark is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public
// License along with snark. If not, see <http://www.gnu.org/licenses/>.

#ifndef SNARK_GRAPHICS_QUEUE_HEADER_GUARD_
#define SNARK_GRAPHICS_QUEUE_HEADER_GUARD_

#include <comma/math/cyclic.h>
#include <snark/graphics/impl/renderable.h>

namespace snark { namespace graphics {

template < typename T >
class Queue : public impl::renderable< T >
{
    public:
        Queue( std::size_t capacity ) : impl::renderable< T >( capacity ), m_end( 0, capacity ) {}

        std::size_t capacity() const { return this->m_storage.capacity(); }

        std::size_t size() const { return this->m_storage.size(); }

        bool empty() const { return this->m_storage.empty(); }

        void clear() { this->m_storage.clear(); m_end = 0; }

        void push( const T& t );

    private:
        comma::math::cyclic< std::size_t > m_end;
};

template < typename T >
inline void Queue< T >::push( const T& t )
{
    if( size() == capacity() )
    {
        this->m_storage[ m_end() ] = t;
    }
    else
    {
        this->m_storage.pushBack( t );
    }
    ++m_end;
}

} } // namespace snark { namespace graphics {

#endif // SNARK_GRAPHICS_QUEUE_HEADER_GUARD_

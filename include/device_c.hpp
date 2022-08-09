/*
 * libcutter - xy cutter control library
 * Copyright (c) 2010 - libcutter Developers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Should you need to contact us, the author, you can do so at
 * http://github.com/vangdfang/libcutter
 */
#ifndef DEVICE_C_HPP
#define DEVICE_C_HPP

#include <cstdint>
#include <cstring>
#include <vector>
#include "device.hpp"
#include "types.h"
#include "serial_port.hpp"

namespace Device
{
    class C : public Device::Generic
    {
        public:
            C();
            C( const std::string filename );
            ~C();
            /* virtual */ void init( const std::string filename );
            /* virtual */ bool move_to( const xy &aPoint );
            /* virtual */ bool cut_to( const xy &aPoint );
            /* virtual */ bool curve_to( const xy &p0, const xy &p1, const xy &p2, const xy &p3 );
            /* virtual */ bool start();
            /* virtual */ bool stop();
            /* virtual */ xy   get_dimensions();
            inline void set_move_key( ckey_type k )
            {
                memcpy( m_move_key, k, sizeof(ckey_type) );
            }
            inline void set_line_key( ckey_type k )
            {
                memcpy( m_line_key, k, sizeof(ckey_type) );
            }
            inline void set_curve_key( ckey_type k )
            {
                memcpy( m_curve_key, k, sizeof(ckey_type) );
            }
            inline bool is_open()
            {
                return m_serial.is_open();
            }
            enum model_id
            {
                UNKNOWN,
                PERSONAL,
                MINI,/*unsupported but detectable*/
                EXPRESSION
            };
            int get_version_major();
            int get_version_minor();
            std::string device_make();
            std::string device_model();
            std::string device_version();
            inline void set_serial_debug( int level )
            {
                m_serial.set_debug( level );
            }

            /*usually handled as part of init()*/
            /*but here for debugging purposes*/
            bool enumerate();

        private:
            /*This is in question and needs remeasured*/
            /*See https://github.com/vangdfang/libcutter/issues/20 */
            static const int baud_rate = 200000;
            inline int get_rand() const
            {
                /*No, we're not bad at math. This is cryptographic padding
                designed to make the encrypted packets harder to guess. But
                having done that, there's not much point in doing so ourselves,
                since the cryto-keys are in the wild.*/
                return 12345;
            };
            xy convert_to_internal( const xy &input );
            bool do_command( const xy &pt, const ckey_type k );
            bool do_command_32( uint32_t );
            std::vector<uint8_t> read_response();
            ckey_type m_move_key;
            ckey_type m_line_key;
            ckey_type m_curve_key;
            serial_port m_serial;
            model_id m_model_id;
            int m_version_major;
            int m_version_minor;
    };
}
#endif

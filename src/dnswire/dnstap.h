/*
 * Author Jerry Lundström <jerry@dns-oarc.net>
 * Copyright (c) 2019, OARC, Inc.
 * All rights reserved.
 *
 * This file is part of the dnswire library.
 *
 * dnswire library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dnswire library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with dnswire library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <dnswire/dnstap.pb-c.h>

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef __dnswire_h_dnstap
#define __dnswire_h_dnstap 1

enum dnstap_type {
    DNSTAP_TYPE_UNKNOWN = 0,
    DNSTAP_TYPE_MESSAGE = 1,
};
extern const char const* DNSTAP_TYPE_STRING[];

enum dnstap_message_type {
    DNSTAP_MESSAGE_TYPE_UNKNOWN            = 0,
    DNSTAP_MESSAGE_TYPE_AUTH_QUERY         = 1,
    DNSTAP_MESSAGE_TYPE_AUTH_RESPONSE      = 2,
    DNSTAP_MESSAGE_TYPE_RESOLVER_QUERY     = 3,
    DNSTAP_MESSAGE_TYPE_RESOLVER_RESPONSE  = 4,
    DNSTAP_MESSAGE_TYPE_CLIENT_QUERY       = 5,
    DNSTAP_MESSAGE_TYPE_CLIENT_RESPONSE    = 6,
    DNSTAP_MESSAGE_TYPE_FORWARDER_QUERY    = 7,
    DNSTAP_MESSAGE_TYPE_FORWARDER_RESPONSE = 8,
    DNSTAP_MESSAGE_TYPE_STUB_QUERY         = 9,
    DNSTAP_MESSAGE_TYPE_STUB_RESPONSE      = 10,
    DNSTAP_MESSAGE_TYPE_TOOL_QUERY         = 11,
    DNSTAP_MESSAGE_TYPE_TOOL_RESPONSE      = 12,
};
extern const char const* DNSTAP_MESSAGE_TYPE_STRING[];

enum dnstap_socket_family {
    DNSTAP_SOCKET_FAMILT_UNKNOWN = 0,
    DNSTAP_SOCKET_FAMILY_INET    = 1,
    DNSTAP_SOCKET_FAMILY_INET6   = 2,
};
extern const char const* DNSTAP_SOCKET_FAMILY_STRING[];

enum dnstap_socket_protocol {
    DNSTAP_SOCKET_PROTOCOL_UNKNOWN = 0,
    DNSTAP_SOCKET_PROTOCOL_UDP     = 1,
    DNSTAP_SOCKET_PROTOCOL_TCP     = 2,
};
extern const char const* DNSTAP_SOCKET_PROTOCOL_STRING[];

struct dnstap {
    Dnstap__Dnstap  dnstap;
    Dnstap__Message message;

    Dnstap__Dnstap* unpacked_dnstap;
};

#define DNSTAP_INITIALIZER                        \
    {                                             \
        .dnstap          = DNSTAP__DNSTAP__INIT,  \
        .message         = DNSTAP__MESSAGE__INIT, \
        .unpacked_dnstap = 0,                     \
    }

#include <dnswire/dnstap-macros.h>
#define dnstap_type(d) (enum dnstap_type)((d).dnstap.type)
#define dnstap_set_type(d, v)                     \
    switch (v) {                                  \
    case DNSTAP_TYPE_MESSAGE:                     \
        (d).dnstap.type    = v;                   \
        (d).dnstap.message = &(d).message;        \
        break;                                    \
    default:                                      \
        (d).dnstap.type    = DNSTAP_TYPE_UNKNOWN; \
        (d).dnstap.message = 0;                   \
    }
#define dnstap_has_message(d) ((d).dnstap.message != 0)

#define dnstap_message_type(d) (enum dnstap_message_type)((d).message.type)
#define dnstap_message_set_type(d, v)                   \
    switch (v) {                                        \
    case DNSTAP_MESSAGE_TYPE_AUTH_QUERY:                \
    case DNSTAP_MESSAGE_TYPE_AUTH_RESPONSE:             \
    case DNSTAP_MESSAGE_TYPE_RESOLVER_QUERY:            \
    case DNSTAP_MESSAGE_TYPE_RESOLVER_RESPONSE:         \
    case DNSTAP_MESSAGE_TYPE_CLIENT_QUERY:              \
    case DNSTAP_MESSAGE_TYPE_CLIENT_RESPONSE:           \
    case DNSTAP_MESSAGE_TYPE_FORWARDER_QUERY:           \
    case DNSTAP_MESSAGE_TYPE_FORWARDER_RESPONSE:        \
    case DNSTAP_MESSAGE_TYPE_STUB_QUERY:                \
    case DNSTAP_MESSAGE_TYPE_STUB_RESPONSE:             \
    case DNSTAP_MESSAGE_TYPE_TOOL_QUERY:                \
    case DNSTAP_MESSAGE_TYPE_TOOL_RESPONSE:             \
        (d).message.type = v;                           \
        break;                                          \
    default:                                            \
        (d).message.type = DNSTAP_MESSAGE_TYPE_UNKNOWN; \
    }
#define dnstap_message_set_socket_family(d, v)                       \
    switch (v) {                                                     \
    case DNSTAP_SOCKET_FAMILY_INET:                                  \
    case DNSTAP_SOCKET_FAMILY_INET6:                                 \
        (d).message.has_socket_family = true;                        \
        (d).message.socket_family     = v;                           \
        break;                                                       \
    default:                                                         \
        (d).message.has_socket_family = false;                       \
        (d).message.socket_family     = DNSTAP_MESSAGE_TYPE_UNKNOWN; \
    }
#define dnstap_message_set_socket_protocol(d, v)                       \
    switch (v) {                                                       \
    case DNSTAP_SOCKET_PROTOCOL_UDP:                                   \
    case DNSTAP_SOCKET_PROTOCOL_TCP:                                   \
        (d).message.has_socket_protocol = true;                        \
        (d).message.socket_protocol     = v;                           \
        break;                                                         \
    default:                                                           \
        (d).message.has_socket_protocol = false;                       \
        (d).message.socket_protocol     = DNSTAP_MESSAGE_TYPE_UNKNOWN; \
    }

int dnstap_decode_protobuf(struct dnstap*, const uint8_t*, size_t);
// int dnstap_decode_cbor(struct dnstap*, const uint8_t*, size_t);

size_t dnstap_encode_protobuf_size(const struct dnstap*);
size_t dnstap_encode_protobuf(const struct dnstap*, uint8_t*);

void dnstap_cleanup(struct dnstap*);

#endif

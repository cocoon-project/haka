/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <lua.h>
#include <lauxlib.h>

#include <haka/config.h>
#include <haka/lua/luautils.h>
#include <haka/luabinding.h>
#include <haka/packet.h>
#include <haka/types.h>

#include "packet.h"
#include "thread.h"

#include "lua/packet.h"

#ifdef HAKA_FFI

void packet_receive_wrapper_wrap(void *_state, struct receive_result *res)
{
	struct thread_state *state;
	state = (struct thread_state *)_state;

	if (state == NULL) return;

	packet_receive_wrapper(state, &res->pkt, &res->has_interrupts, &res->stop);
}

LUA_BIND_INIT(packet)
{
	LUA_LOAD(packet, L);
	lua_call(L, 0, 1);

	return 1;
}

#else

int packet_receive_wrapper_wrap()
{
	struct packet *pkt;
	bool has_interrupts;
	bool stop;

	// push result on stack
	packet_receive_wrapper(state, &pkt, &has_interrupts, &stop);
}

#endif
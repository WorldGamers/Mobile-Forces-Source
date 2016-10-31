//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef LC_RECIPIENTFILTER_H
#define LC_RECIPIENTFILTER_H
#ifdef _WIN32
#pragma once
#endif

#ifdef LUA_SDK

/* type for CRecipientFilter functions */
typedef C_RecipientFilter lua_CRecipientFilter;


/* type for CPASFilter functions */
typedef CPASFilter lua_CPASFilter;



/*
** access functions (stack -> C)
*/

LUA_API lua_CRecipientFilter     &(lua_torecipientfilter) (lua_State *L, int idx);
LUA_API lua_CPASFilter     &(lua_topasfilter) (lua_State *L, int idx);


/*
** push functions (C -> stack)
*/
LUA_API void  (lua_pushrecipientfilter) (lua_State *L, lua_CRecipientFilter &filter);
LUA_API void  (lua_pushpasfilter) (lua_State *L, lua_CPASFilter &filter);



LUALIB_API lua_CRecipientFilter &(luaL_checkrecipientfilter) (lua_State *L, int narg);
LUALIB_API lua_CPASFilter &(luaL_checkpasfilter) (lua_State *L, int narg);

#endif
#endif // LC_RECIPIENTFILTER_H
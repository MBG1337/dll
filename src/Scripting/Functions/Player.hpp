#pragma once

#include <lua.hpp>
#include <d2d1helper.h>
#include "../../Client/GUI/Engine/Engine.hpp"
#include <string>
#include <codecvt>
#include "../../SDK/Client/Actor/Player.hpp"


namespace player {
    int lua_getPlayerName(lua_State* L) {
        if (SDK::clientInstance != nullptr){
            return 0;
        }
        lua_pushstring(L, SDK::clientInstance->getLocalPlayer()->getPlayerName().c_str());
        
        return 1;
    }
    
    
    void registerPlayer(lua_State *L) {
        lua_newtable(L);

        lua_pushcfunction(L, lua_getPlayerName);
        lua_setfield(L, -2, "getPlayerName");

        lua_setglobal(L, "Player");


    }
}
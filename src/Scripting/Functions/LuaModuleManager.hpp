#pragma once

#include <lua.hpp>
#include <d2d1helper.h>
#include "../../Client/GUI/Engine/Engine.hpp"
#include "../../Client/Module/Manager.hpp"
#include "../ScriptModuleBase.hpp"
#include "../LUAHelper.hpp"
#include <string>
#include <codecvt>


namespace LuaModuleManager {

    std::optional<std::shared_ptr<Module>> getModule(const std::string& name) {
        for (const auto& obj : ModuleManager::getModules()) {
            if (obj->name == name) {
                return obj;
            }
        }
        return std::nullopt;
    }

    int lua_GetModules(lua_State *L) {
        lua_newtable(L);
        const std::vector<std::shared_ptr<Module>> moduleList = ModuleManager::getModules();
        for (const auto &module : moduleList){
            lua_pushlightuserdata(L, module.get());
            lua_rawseti(L, -2, std::distance((moduleList.begin()), std::find(moduleList.begin(), moduleList.end(),module))+1);
        };
        return 1;
    }


    int lua_GetModuleByName(lua_State *L) {
        std::string name = luaL_checkstring(L, 1);
        std::optional<std::shared_ptr<Module>> mod = getModule(name);

        if(mod == std::nullopt){
            lua_error(L);
            return 0;
        }else{
            lua_pushlightuserdata(L, &mod);
        }
        return 1;
    }



    void registerModuleManager(lua_State *L) {
        LUAHelper(L)
                .getClass("ModuleManager")
                .registerFunction("GetModuleByName", lua_GetModuleByName)
                .registerFunction("GetModules", lua_GetModules);
    }
}
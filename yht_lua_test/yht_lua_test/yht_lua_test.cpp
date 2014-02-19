// yht_lua_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
extern "C" 
{   
#include "lua.h"   
#include "lualib.h"   
#include "lauxlib.h"   
}  


bool loadfile(const char *filename, lua_State * m_ls)
{
	lua_State *l = m_ls;
	int n = 0;

	// 加载脚本文件
	n = lua_gettop(m_ls);
	int ret = luaL_loadfile(m_ls, filename);
	if (ret != 0)
	{
		const char *err = lua_tostring(m_ls, -1);
		int n = lua_gettop(m_ls);
		lua_pop(m_ls, 1);
		return false;
	}

	ret = lua_pcall(m_ls, 0, LUA_MULTRET, 0);
	// 如果发生错误，恢复堆栈
	if (ret != 0)
	{
		const char *err = lua_tostring(m_ls, -1);
		lua_pop(m_ls, 1);
		return false;
	}

	return true;
}


int _tmain(int argc, _TCHAR* argv[])
{

	printf("%d,%d,%d",sizeof(int),sizeof(long),sizeof(unsigned long));
	return 0;
}


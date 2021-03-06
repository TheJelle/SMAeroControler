/*
**
** Aero Jail Controler Plugin - Interface Control partial File
** Author: _AeonOne_
**
** binding license: GPLv3
** voluntary license:
** "THE BEER-WARE LICENSE" (Revision 43-1 by Julien Kluge):
** Julien Kluge wrote this file. As long as you retain this notice you
** can do what is defined in the binding license (GPLv3). If we meet some day, and you think
** this stuff is worth it, you can buy me a beer, pizza or something else which you think is appropriate.
** This license is a voluntary license. You don't have to observe it.
**
*/

functag public buildCMDMenuForward(client, Handle:menu);

stock void AC_InterfaceControlRegister()
{
	tagChangedForward = CreateGlobalForward("ac_OnCoreComTagChanged", ET_Ignore, Param_String);
	clientRoundReadyForward = CreateGlobalForward("ac_OnClientIsReadyForRound", ET_Ignore, Param_Cell);
	coreStateForward = CreateGlobalForward("ac_OnCoreStateChanged", ET_Ignore, Param_Cell);
	cmdMenuBuildForward = CreateForward(ET_Hook, Param_Cell, Param_Cell);
	
	CreateNative("ac_setCoreOffline", view_as<NativeCall>AC_Native_SetCoreOffline);
	CreateNative("ac_setCoreOnline", view_as<NativeCall>AC_Native_SetCoreOnline);
	CreateNative("ac_getCoreComTag", view_as<NativeCall>AC_Native_GetCoreComTag);
	CreateNative("ac_parseTransFile", view_as<NativeCall>AC_Native_ParseTransFile);
	CreateNative("ac_setClientRefuseVars", view_as<NativeCall>AC_Native_SetClientRefuseVars);
	CreateNative("ac_getClientRefuseVars", view_as<NativeCall>AC_Native_GetClientRefuseVars);
	CreateNative("ac_setClientCapitulateVars", view_as<NativeCall>AC_Native_SetClientCapitulateVars);
	CreateNative("ac_getClientCapitulateVars", view_as<NativeCall>AC_Native_GetClientCapitulateVars);
	CreateNative("ac_setClientDiceVars", view_as<NativeCall>AC_Native_SetClientDiceVars);
	CreateNative("ac_getClientDiceVars", view_as<NativeCall>AC_Native_GetClientDiceVars);
	CreateNative("ac_isClientRebell", view_as<NativeCall>AC_Native_IsClientRebell);
	CreateNative("ac_registerPluginExtension", view_as<NativeCall>AC_Native_RegisterPluginExtension);
	CreateNative("ac_unregisterPluginExtension", view_as<NativeCall>AC_Native_UnRegisterPluginExtension);
	CreateNative("ac_performDiceOnClient", view_as<NativeCall>AC_Native_PerformDiceOnClient);
	CreateNative("ac_registerCMDMenuBuildForward", view_as<NativeCall>AC_Native_RegisterCMDMenuBuildForward);
	
	RegPluginLibrary("ac_core");
}

public int AC_Native_SetCoreOffline(Handle plugin, int numParams)
{
	OverrideWorkToFalse = true; SetCoreState(false); return 0;
}

public int AC_Native_SetCoreOnline(Handle plugin, int numParams)
{
	OverrideWorkToFalse = false; SetCoreState(true); return 0;
}

public int AC_Native_GetCoreComTag(Handle plugin, int numParams)
{
	int length = GetNativeCell(2);
	SetNativeString(1, Tag, length);
	return 0;
}

public bool AC_Native_ParseTransFile(Handle plugin, numParams)
{
	char file_Dest[PLATFORM_MAX_PATH];
	char file_Srce[PLATFORM_MAX_PATH];
	GetNativeString(1, file_Srce, sizeof(file_Srce));
	GetNativeString(2, file_Dest, sizeof(file_Dest));
	if (FileExists(file_Srce))
	{
		if (FileExists(file_Dest)) { DeleteFile(file_Dest); }
		return ParseTransFile(file_Srce, file_Dest);
	}
	return false;
}

public int AC_Native_SetClientRefuseVars(Handle plugin, numParams)
{
	int client = GetNativeCell(1);
	int refusings = GetNativeCell(2);
	int maxRefusings = GetNativeCell(3);
	int baseRefusings = GetNativeCell(4);
	int oneBaseRefusings = GetNativeCell(5);
	if (IsClientValid(client))
	{
		if (refusings != -1)
		{ c_r[client] = refusings; }
		if (maxRefusings != -1)
		{ c_rBaseMax[client] = maxRefusings; }
		if (baseRefusings != -1)
		{ c_rBase[client] = baseRefusings; }
		if (oneBaseRefusings != -1)
		{ c_rSubBase[client] = oneBaseRefusings; }
	}
	return 0;
}

public int AC_Native_GetClientRefuseVars(Handle plugin, numParams)
{
	int client = GetNativeCell(1);
	if (IsClientValid(client))
	{
		SetNativeCellRef(2, c_r[client]);
		SetNativeCellRef(3, c_rBaseMax[client]);
		SetNativeCellRef(4, c_rBase[client]);
		SetNativeCellRef(5, c_rSubBase[client]);
	}
	else
	{
		SetNativeCellRef(2, -1);
		SetNativeCellRef(3, -1);
		SetNativeCellRef(4, -1);
		SetNativeCellRef(5, -1);
	}
	return 0;
}

public int AC_Native_SetClientCapitulateVars(Handle plugin, numParams)
{
	int client = GetNativeCell(1);
	int capitulatings = GetNativeCell(2);
	int maxCapitulatings = GetNativeCell(3);
	int baseCapitulatings = GetNativeCell(4);
	int oneBaseCapitulatings = GetNativeCell(5);
	if (IsClientValid(client))
	{
		if (capitulatings != -1)
		{ c_c[client] = capitulatings; }
		if (maxCapitulatings != -1)
		{ c_cBaseMax[client] = maxCapitulatings; }
		if (baseCapitulatings != -1)
		{ c_cBase[client] = baseCapitulatings; }
		if (oneBaseCapitulatings != -1)
		{ c_cSubBase[client] = oneBaseCapitulatings; }
	}
	return 0;
}

public int AC_Native_GetClientCapitulateVars(Handle plugin, numParams)
{
	int client = GetNativeCell(1);
	if (IsClientValid(client))
	{
		SetNativeCellRef(2, c_c[client]);
		SetNativeCellRef(3, c_cBaseMax[client]);
		SetNativeCellRef(4, c_cBase[client]);
		SetNativeCellRef(5, c_cSubBase[client]);
	}
	else
	{
		SetNativeCellRef(2, -1);
		SetNativeCellRef(3, -1);
		SetNativeCellRef(4, -1);
		SetNativeCellRef(5, -1);
	}
	return 0;
}

public int AC_Native_SetClientDiceVars(Handle plugin, numParams)
{
	int client = GetNativeCell(1);
	int dicings = GetNativeCell(2);
	int baseDicings = GetNativeCell(3);
	int oneBaseDicings = GetNativeCell(4);
	if (IsClientValid(client))
	{
		if (dicings != -1)
		{ c_dices[client] = dicings; }
		if (baseDicings != -1)
		{ c_dicesBase[client] = baseDicings; }
		if (oneBaseDicings != -1)
		{ c_dicesSubBase[client] = oneBaseDicings; }
	}
	return 0;
}

public int AC_Native_GetClientDiceVars(Handle plugin, numParams)
{
	int client = GetNativeCell(1);
	if (IsClientValid(client))
	{
		SetNativeCellRef(2, c_dices[client]);
		SetNativeCellRef(3, c_dicesBase[client]);
		SetNativeCellRef(4, c_dicesSubBase[client]);
	}
	else
	{
		SetNativeCellRef(2, -1);
		SetNativeCellRef(3, -1);
		SetNativeCellRef(4, -1);
	}
	return 0;
}

public bool AC_Native_IsClientRebell(Handle plugin, numParams)
{
	int client = GetNativeCell(1);
	if (IsClientValid(client))
	{
		return c_rebell[client];
	}
	return false;
}

public int AC_Native_RegisterPluginExtension(Handle plugin, numParams)
{
	char subString[64];
	GetNativeString(1, subString, sizeof(subString));
	int index = PushArrayString(extensionPlugins, subString);
	GetNativeString(2, subString, sizeof(subString));
	PushArrayString(extensionPlugins, subString);
	GetNativeString(3, subString, sizeof(subString));
	PushArrayString(extensionPlugins, subString);
	PushArrayString(extensionPlugins, "- - - -");
	return index;
}

public int AC_Native_UnRegisterPluginExtension(Handle plugin, numParams)
{
	int index = GetNativeCell(1);
	for (int i = 0; i < 4; i++)
	{ SetArrayString(extensionPlugins, index + i, ""); } //not the yellow from the egg ... i know...
	return 0;
}

public int AC_Native_PerformDiceOnClient(Handle plugin, numParams)
{
	int client = GetNativeCell(1);
	float value = view_as<float>GetNativeCell(2);
	bool lowerDiceCount = view_as<bool>GetNativeCell(3);
	if (lowerDiceCount)
	{ c_dices[client]--; }
	ThrowDice(client, value, false);
	return 0;
}

public int AC_Native_RegisterCMDMenuBuildForward(Handle plugin, numParams)
{
	Function func = GetNativeCell(1);
	AddToForward(cmdMenuBuildForward, plugin, func);
	return 0;
}
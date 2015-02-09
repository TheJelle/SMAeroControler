#pragma semicolon 1

/*
**
** Aero Jail Controler Plugin
** Standart WARs
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

//#define DEBUG

/* γ = dev : α = canditae for control testing : β = proving ground/release candidate : λ = Final stable/RTM */
#define PLUGIN_VERSION "1.01λ"

#include <sourcemod>
#include <sdktools>
#include <cstrike>
#include <sdkhooks>

#include "AeroControler\\aerocontroler_core_interface.inc" //interface to the core
#include "AeroControler\\aerocontroler_war_interface.inc" //interface to the war-base

#include "AeroControler\\SharedPluginBase\\AC_ErrorSys.inc"
#include "AeroControler\\SharedPluginBase\\AC_UISys.inc"
#include "AeroControler\\SharedPluginBase\\AC_ClientSys.inc"

#include "AeroControler\\War_Sys\\Scripts\\AC_STDWAR_Vars.inc"
#include "AeroControler\\War_Sys\\Scripts\\AC_STDWAR_Stocks.inc"
#include "AeroControler\\War_Sys\\Scripts\\AC_STDWAR_HandlerCallbacks.inc"
#include "AeroControler\\War_Sys\\Scripts\\AC_STDWAR_Events.inc"
#include "AeroControler\\War_Sys\\Scripts\\AC_STDWAR_Configs.inc"

public Plugin:myinfo = 
{
	name = "Aero Controler - Standart WARs",
	author = "_AeonOne_",
	description = "Provides 3 standart WARs.",
	version = PLUGIN_VERSION,
	url = "Julien.Kluge@gmail.com"
};

public OnPluginStart()
{
	LoadTranslationFiles();

	ac_getCoreComTag(Tag, sizeof(Tag));
	ExtensionEntryIndex = ac_registerPluginExtension("Aero Standart WARs", "_AeonOne_", PLUGIN_VERSION);

	RegisterWars();
	
	HookEvent("player_spawn", Event_PlayerSpawn, EventHookMode_Post);
}

public OnPluginEnd()
{
	if (LibraryExists("ac_core")) //alibi check
	{
		ac_unregisterPluginExtension(ExtensionEntryIndex);
	}
}

public OnLibraryAdded(const String:name[])
{
	if (StrEqual(name, "ac_war_sys"))
	{
		RegisterWars();
	}
}

public OnLibraryRemoved(const String:name[])
{
	if (StrEqual(name, "ac_war_sys"))
	{
		Ready = false;
	}
}

public ac_OnCoreComTagChanged(const String:tag[])
{
	Format(Tag, sizeof(Tag), "%s", tag);
}

public OnClientPutInServer(client)
{
	SDKHook(client, SDKHook_OnTakeDamage, SDKH_OnTakeDamage);
}
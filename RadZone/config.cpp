////////////////////////////////////////////////////////////////////
//DeRap: RadZone\config.bin
//Produced from mikero's Dos Tools Dll version 8.01
//https://mikero.bytex.digital/Downloads
//'now' is Thu Jun 10 14:44:34 2021 : 'file' last modified on Wed Apr 21 16:47:09 2021
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class RadZone_Script
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Characters_Headgear","DZ_Characters_Gloves","DZ_Characters_Masks","DZ_Characters_Tops","DZ_Characters_Pants","DZ_Characters_Shoes","GMADefine"};
	};
};
class CfgMods
{
	class RadZone
	{
		dir = "RadZone";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "RadZone";
		credits = "TheDmitri";
		author = "TheDmitri";
		authorID = "0";
		version = "1.1";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"RadZone/scripts/Common","RadZone/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"RadZone/scripts/Common","RadZone/scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"RadZone/scripts/Common","RadZone/scripts/5_Mission"};
			};
		};
	};
};

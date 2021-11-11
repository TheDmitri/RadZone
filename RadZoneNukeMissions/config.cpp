class CfgPatches
{
	class RadZoneNukeMissions_Script
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"RadZone_Data_Script"
		};
	};
};
class CfgMods
{
	class RadZoneNukeMissions
	{
		dir="RadZoneNukeMissions";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="RadZoneNukeMissions";
		credits="TheDmitri";
		author="TheDmitri";
		authorID="0";
		version="1.1";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"RadZoneNukeMissions/scripts/Common",
					"RadZoneNukeMissions/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"RadZoneNukeMissions/scripts/Common",
					"RadZoneNukeMissions/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"RadZoneNukeMissions/scripts/Common",
					"RadZoneNukeMissions/scripts/5_Mission"
				};
			};
		};
	};
};
class CfgVehicles
{
	class HouseNoDestruct;
	class RZSiren: HouseNoDestruct
	{
		scope=2;
		displayName="RZSiren";
		weight=36;
		rotationFlags=16;
	};
	class NukeBombEffect: HouseNoDestruct
	{
		scope=2;
		displayName="NukeBombEffect";
		forceFarBubble="true";
		carveNavmesh=1;
		rotationFlags=2;
		itemSize[]={1,1};
		weight=1;
	};
	class IrradiedDirtPile: HouseNoDestruct
	{
		scope=2;
		displayName="IrradiedDirtPile";
		model="\DZ\structures\ruins\rubble_dirtpile_medium2.p3d";
	};
	class NukeCrater: IrradiedDirtPile
	{
		scope=2;
		displayName="NukeCrater";
		model="\DZ\structures_bliss\military\Training\ShellCrater2_Large.p3d";
	};
};
class CfgSoundShaders
{
	class rz_Siren_SoundShader
	{
		samples[]=
		{

			{
				"RadZoneNukeMissions\sounds\SirenLoopMono",
				1
			}
		};
		range=2500;
		volume=0.60000002;
	};
	class rz_NukeBomb_SoundShader
	{
		samples[]=
		{

			{
				"RadZoneNukeMissions\sounds\NukeExplosion",
				1
			}
		};
		range=3500;
		volume=20;
	};
	class rz_Whistle_SoundShader
	{
		samples[]=
		{

			{
				"RadZoneNukeMissions\sounds\BombWhistle",
				1
			}
		};
		range=1500;
		volume=20;
	};
	class rz_BomberPlane_SoundShader
	{
		samples[]=
		{

			{
				"RadZoneNukeMissions\sounds\BomberPlane",
				1
			}
		};
		range=1200;
		volume=4;
	};
};
class CfgSoundSets
{
	class rz_Bomberplane_SoundSet
	{
		soundShaders[]=
		{
			"rz_BomberPlane_SoundShader"
		};
	};
	class rz_Siren_SoundSet
	{
		soundShaders[]=
		{
			"rz_Siren_SoundShader"
		};
	};
	class rz_Whistle_SoundSet
	{
		soundShaders[]=
		{
			"rz_Whistle_SoundShader"
		};
	};
	class rz_NukeBomb_SoundSet
	{
		soundShaders[]=
		{
			"rz_NukeBomb_SoundShader"
		};
	};
};
class CfgSounds
{
	class default
	{
		name="";
		titles[]={};
	};
	class rz_BomberPlane_Sound: default
	{
		sound[]=
		{
			"\RadZoneNukeMissions\sounds\BomberPlane",
			10,
			1,
			1500
		};
	};
};

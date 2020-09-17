// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class WeatherApp : ModuleRules
{
	public WeatherApp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "CISQLite3", "HTTP", "Json", "JsonUtilities" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");


        /////////////////////////////
        var path = Path.GetDirectoryName(RulesCompiler.GetFileNameFromType(this.GetType()));
        PublicIncludePaths.Add(Path.Combine(path, "sqlite", "bin"));

        //PublicDelayLoadDLLs.Add("mylib.dll");
        PublicAdditionalLibraries.Add(Path.Combine(path, "sqlite", "bin", "sqlite3.lib"));

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}

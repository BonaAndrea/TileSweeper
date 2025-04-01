// Copyright(c) Forge Reply. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TileSweeperTarget : TargetRules
{
	public TileSweeperTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("TileSweeper");
	}
}

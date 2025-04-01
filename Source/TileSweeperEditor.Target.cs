// Copyright(c) Forge Reply. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TileSweeperEditorTarget : TargetRules
{
	public TileSweeperEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("TileSweeper");
	}
}

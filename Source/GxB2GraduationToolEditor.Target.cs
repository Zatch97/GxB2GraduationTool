// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class GxB2GraduationToolEditorTarget : TargetRules
{
	public GxB2GraduationToolEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "GxB2GraduationTool" } );
	}
}

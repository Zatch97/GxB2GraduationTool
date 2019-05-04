// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class GxB2GraduationToolTarget : TargetRules
{
	public GxB2GraduationToolTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "GxB2GraduationTool" } );
	}
}

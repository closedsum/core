// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCustomShaderDirectory.h"

#include "Misc/Paths.h"
#include "ShaderCore.h"

#define LOCTEXT_NAMESPACE "FCsCustomShaderDirectory"

void FCsCustomShaderDirectory::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FString ShaderDir = FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("CsCustomShaderDirectory/Shaders"));
	AddShaderSourceDirectoryMapping("/Plugins/CsCustomShaderDirectory", ShaderDir);

	//FString ProjectShaderDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("/AwesomeShaders"));
	//AddShaderSourceDirectoryMapping("/Project/AwesomeShaders", ProjectShaderDir);
}

void FCsCustomShaderDirectory::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FCsCustomShaderDirectory, CsCustomShaderDirectory)
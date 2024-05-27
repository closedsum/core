// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsCVars.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsCVars)

// FCsCVarLogMap
#pragma region

void FCsCVarLogMap::Resolve()
{
	for (TCsAutoConsoleVariable_int32& Var : Map)
	{
		Var.Resolve();
	}
}

void FCsCVarLogMap::Reset()
{
	for (int32 I = 0; I < Num; ++I)
	{
		Map[I].Set(DefaultValues[I], ECVF_SetByConsole);
		DirtyMap[I] = false;
	}
}

void FCsCVarLogMap::ResetDirty()
{
	for (int32 I = 0; I < Num; ++I)
	{
		if (DirtyMap[I])
			Map[I].Set(DefaultValues[I], ECVF_SetByConsole);
		DirtyMap[I] = false;
	}
}

#pragma endregion FCsCVarLogMap

// FCsCVarToggleMap
#pragma region

void FCsCVarToggleMap::Resolve()
{
	for (TCsAutoConsoleVariable_bool& Var : Map)
	{
		Var.Resolve();
	}
}

void FCsCVarToggleMap::Reset()
{
	for (int32 I = 0; I < Num; ++I)
	{
		Map[I].Set(DefaultValues[I], ECVF_SetByConsole);
		DirtyMap[I] = false;
	}
}

void FCsCVarToggleMap::ResetDirty()
{
	for (int32 I = 0; I < Num; ++I)
	{
		if (DirtyMap[I])
			Map[I].Set(DefaultValues[I], ECVF_SetByConsole);
		DirtyMap[I] = false;
	}
}

#pragma endregion FCsCVarToggleMap

// FCsCVarDrawMap
#pragma region

void FCsCVarDrawMap::Resolve()
{
	for (TCsAutoConsoleVariable_int32& Var : Map)
	{
		Var.Resolve();
	}
}

void FCsCVarDrawMap::Reset()
{
	for (int32 I = 0; I < Num; ++I)
	{
		Map[I].Set(DefaultValues[I], ECVF_SetByConsole);
		DirtyMap[I] = false;
	}
}

void FCsCVarDrawMap::ResetDirty()
{
	for (int32 I = 0; I < Num; ++I)
	{
		if (DirtyMap[I])
			Map[I].Set(DefaultValues[I], ECVF_SetByConsole);
		DirtyMap[I] = false;
	}
}

#pragma endregion FCsCVarDrawMap

// FCsScopedGroupMap
#pragma region

void FCsScopedGroupMap::Resolve()
{
	for (TCsAutoConsoleVariable_int32& Var : Map)
	{
		Var.Resolve();
	}
}

void FCsScopedGroupMap::Reset()
{
	for (int32 I = 0; I < Num; ++I)
	{
		Map[I].Set(DefaultValues[I], ECVF_SetByConsole);
		DirtyMap[I] = false;
	}
}

void FCsScopedGroupMap::ResetDirty()
{
	for (int32 I = 0; I < Num; ++I)
	{
		if (DirtyMap[I])
			Map[I].Set(DefaultValues[I], ECVF_SetByConsole);
		DirtyMap[I] = false;
	}
}

#pragma endregion FCsScopedGroupMap
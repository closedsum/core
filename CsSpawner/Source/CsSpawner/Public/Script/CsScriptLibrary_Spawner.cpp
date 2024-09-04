// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Script/CsScriptLibrary_Spawner.h"
#include "CsSpawner.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Log
#include "Utility/CsSpawnerLog.h"
// Spawner
#include "CsSpawnerImpl.h"
#include "Point/CsSpawnerPointImpl.h"
#include "Point/CsSpawnerPoint_ShapeCircleImpl.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Spawner)

namespace NCsScriptLibrarySpawner
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Spawner, SetParams_DefaultImpl);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Spawner, SetParams_ShapeCircleImpl);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Spawner, PointImpl_SetCenterAsActor);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Spawner, PointImpl_SetCenterAsTransform);
		}
	}
}

UCsScriptLibrary_Spawner::UCsScriptLibrary_Spawner(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

ACsSpawnerImpl* UCsScriptLibrary_Spawner::GetSpawnerImpl(const FString& Context, UObject* Spawner)
{
	if (!Spawner)
	{
		UE_LOG(LogCsSpawner, Warning, TEXT("%s: Spawner is NULL."), *Context);
		return nullptr;
	}

	if (!Spawner->GetClass()->ImplementsInterface(UCsSpawner::StaticClass()))
	{
		UE_LOG(LogCsSpawner, Warning, TEXT("%s: Spawner: %s with Class: %s does NOT implement the interface: ICsSpawner."), *Context, *(Spawner->GetName()), *(Spawner->GetClass()->GetName()));
		return nullptr;
	}

	ICsSpawner* Interface = Cast<ICsSpawner>(Spawner);

	if (!Interface)
	{
		UE_LOG(LogCsSpawner, Warning, TEXT("%s: Spawner: %s with Class: %s does NOT implement the interface: ICsSpawner natively (c++). Implementing a script based interface is currently NOT supported."), *Context, *(Spawner->GetName()), *(Spawner->GetClass()->GetName()));
		return nullptr;
	}

	ACsSpawnerImpl* Impl = Cast<ACsSpawnerImpl>(Spawner);

	if (!Impl)
	{
		UE_LOG(LogCsSpawner, Warning, TEXT("%s: Spawner: %s with Class: %s does NOT derive from ACsSpawnerImpl. Currently this is the ONLY supported parent class."), *Context, *(Spawner->GetName()), *(Spawner->GetClass()->GetName()));
	}
	return Impl;
}

bool UCsScriptLibrary_Spawner::SetParams_DefaultImpl(const FString& Context, UObject* Spawner, const FCsSpawnerParamsImpl& Params)
{
	using namespace NCsScriptLibrarySpawner::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetParams_DefaultImpl : Context;

	ACsSpawnerImpl* Impl = GetSpawnerImpl(Ctxt, Spawner);

	if (!Impl)
		return false;

	const_cast<FCsSpawnerParamsImpl*>(&Params)->Update();

	if (!Params.IsValid(Ctxt))
		return false;

	// Construct and Set PointImpl
	typedef NCsSpawner::NPoint::FImpl PointImplType;

	PointImplType* PointImpl = new PointImplType();

	Impl->SetPointImpl(Ctxt, PointImpl, &PointImplType::Deconstruct);

	// Construct and Set Params
	typedef NCsSpawner::NParams::FImpl ParamsType;

	ParamsType* ParamsImpl = Params.ConstructParamsImpl();

	Impl->SetParams(Ctxt, ParamsImpl, &ParamsType::Deconstruct, &ParamsType::IsValidChecked);
	return true;
}

bool UCsScriptLibrary_Spawner::SetParams_ShapeCircleImpl(const FString& Context, UObject* Spawner, const FCsSpawnerParams_ShapeCircleImpl& Params)
{
	using namespace NCsScriptLibrarySpawner::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SetParams_ShapeCircleImpl : Context;

	ACsSpawnerImpl* Impl = GetSpawnerImpl(Ctxt, Spawner);

	if (!Impl)
		return false;

	const_cast<FCsSpawnerParams_ShapeCircleImpl*>(&Params)->Update();

	if (!Params.IsValid(Ctxt))
		return false;

	// Construct and Set PointImpl
	typedef NCsSpawner::NPoint::NShape::NCircle::FImpl PointImplType;

	PointImplType* PointImpl = new PointImplType();

	Impl->SetPointImpl(Ctxt, PointImpl, &PointImplType::Deconstruct);

	// Construct and Set Params
	typedef NCsSpawner::NParams::NShape::NCircle::FImpl ParamsType;

	ParamsType* ParamsImpl = Params.ConstructParamsImpl();

	Impl->SetParams(Ctxt, ParamsImpl, &ParamsType::Deconstruct, &ParamsType::IsValidChecked);
	return true;
}

bool UCsScriptLibrary_Spawner::PointImpl_SetCenterAsActor(const FString& Context, UObject* Spawner, AActor* Center)
{
	using namespace NCsScriptLibrarySpawner::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::PointImpl_SetCenterAsActor : Context;

	ACsSpawnerImpl* Impl = GetSpawnerImpl(Ctxt, Spawner);

	if (!Impl)
		return false;

	void(*Log)(const FString&) = &NCsSpawner::FLog::Warning;

	CS_IS_PTR_NULL(Center)

	Impl->SetPointCenter(Center);
	return true;
}

bool UCsScriptLibrary_Spawner::PointImpl_SetCenterAsTransform(const FString& Context, UObject* Spawner, const FTransform3f& Center)
{
	using namespace NCsScriptLibrarySpawner::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::PointImpl_SetCenterAsTransform : Context;

	ACsSpawnerImpl* Impl = GetSpawnerImpl(Ctxt, Spawner);

	if (!Impl)
		return false;

	Impl->SetPointCenter(Center);
	return true;
}
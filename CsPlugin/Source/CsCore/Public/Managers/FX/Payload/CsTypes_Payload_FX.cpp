// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Payload/CsTypes_Payload_FX.h"
#include "CsCore.h"

// Library
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"

#define PayloadType NCsFX::NPayload::FImpl
void FCsPayload_FX::CopyToPayloadAsValueChecked(const FString& Context, UObject* WorldContext, PayloadType* Payload) const
{
#undef PayloadType
	
	Payload->Instigator = Instigator;
	Payload->Owner = Owner;
	Payload->Parent = Parent;
	Payload->Time = Time;
	Payload->PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

	typedef NCsFX::EDeallocateMethod DeallocateMethodType;

	Payload->FXSystem = FX.GetChecked(Context);
	Payload->DeallocateMethod = (DeallocateMethodType)FX.DeallocateMethod;
	Payload->LifeTime = FX.LifeTime;
	Payload->AttachmentTransformRules = FX.AttachmentTransformRules;
	Payload->Bone = FX.Bone;
	Payload->TransformRules = FX.TransformRules;
	Payload->Transform = FX.Transform;

	typedef NCsFX::NManager::FLibrary FXManagerLibrary;

	UObject* ContextRoot			= FXManagerLibrary::GetContextRootChecked(Context, WorldContext);
	UCsManager_FX_Actor* Manager_FX = UCsManager_FX_Actor::Get(ContextRoot);

	// Int
	for (const FCsFXParameterInt& Param : FX.IntParameters)
	{
		typedef NCsFX::NParameter::NInt::FIntType ParameterIntType;

		ParameterIntType* IntType = Manager_FX->AllocateValue<ParameterIntType>();

		Payload->Parameters.Add(IntType);
	}
	// Float
	for (const FCsFXParameterFloat& Param : FX.FloatParameters)
	{
		typedef NCsFX::NParameter::NFloat::FFloatType ParameterFloatType;

		ParameterFloatType* FloatType = Manager_FX->AllocateValue<ParameterFloatType>();

		Payload->Parameters.Add(FloatType);
	}
	// Vector
	for (const FCsFXParameterVector& Param : FX.VectorParameters)
	{
		typedef NCsFX::NParameter::NVector::FVectorType ParameterVectorType;

		ParameterVectorType* VectorType = Manager_FX->AllocateValue<ParameterVectorType>();

		Payload->Parameters.Add(VectorType);
	}
}

bool FCsPayload_FX::IsValidChecked(const FString& Context) const
{
	check(FX.IsValidChecked(Context));
	return true;
}

bool FCsPayload_FX::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!FX.IsValid(Context, Log))
		return false;
	return true;
}
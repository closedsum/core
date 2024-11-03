// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Payload/CsTypes_Payload_FX.h"
#include "CsFX.h"

// Library
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/FX/Actor/CsManager_FX.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Payload_FX)

using PayloadImplType = NCsFX::NPayload::NImpl::FImpl;
using IntParameterType = NCsFX::NParameter::NInt::FIntType;
using FloatParameterType = NCsFX::NParameter::NFloat::FFloatType;
using VectorParameterType = NCsFX::NParameter::NVector::FVectorType;
using ScaledIntParameterType = NCsFX::NParameter::NScaled::NInt::FIntType;
using ScaledFloatParameterType = NCsFX::NParameter::NScaled::NFloat::FFloatType;
using ScaledVectorParameterType = NCsFX::NParameter::NScaled::NVector::FVectorType;
using SkeletalMeshParameterType = NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType;
using DeallocateMethodType = NCsFX::EDeallocateMethod;

void FCsPayload_FX::CopyToPayloadAsValueChecked(const FString& Context, UObject* WorldContext, PayloadImplType* Payload) const
{
	Payload->Instigator = Instigator;
	Payload->Owner		= Owner;
	Payload->Parent		= Parent;
	Payload->Time		= Time;
	Payload->PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

	Payload->FXSystem					= FX.GetChecked(Context);
	Payload->DeallocateMethod			= (DeallocateMethodType)FX.DeallocateMethod;
	Payload->LifeTime					= FX.LifeTime;
	Payload->AttachmentTransformRules	= FX.AttachmentTransformRules;
	Payload->Bone						= FX.Bone;
	Payload->TransformRules				= FX.TransformRules;
	Payload->Transform					= FX.Transform;


	UObject* ContextRoot	  = CsFXManagerLibrary::GetContextRootChecked(Context, WorldContext);
	UCsManager_FX* Manager_FX = UCsManager_FX::Get(ContextRoot);

	// Int
	for (const FCsFXParameterInt& Param : FX.IntParameters)
	{
		IntParameterType* IntType = Manager_FX->AllocateValue<IntParameterType>();

		Param.CopyToParamsAsValue(IntType);
		Payload->Parameters.Add(IntType);
	}
	// Float
	for (const FCsFXParameterFloat& Param : FX.FloatParameters)
	{
		FloatParameterType* FloatType = Manager_FX->AllocateValue<FloatParameterType>();

		Param.CopyToParamsAsValue(FloatType);
		Payload->Parameters.Add(FloatType);
	}
	// Vector
	for (const FCsFXParameterVector& Param : FX.VectorParameters)
	{
		VectorParameterType* VectorType = Manager_FX->AllocateValue<VectorParameterType>();
		
		Param.CopyToParamsAsValue(VectorType);
		Payload->Parameters.Add(VectorType);
	}
	// Scaled
	{
		// Int
		for (const FCsFX_Parameter_Scaled_Int& Param : FX.ScaledParameters.Ints)
		{
			ScaledIntParameterType* IntType = Manager_FX->AllocateValue<ScaledIntParameterType>();

			Param.CopyToParamsAsValue(IntType);
			Payload->ScaledParameters.Add(IntType);
		}
		// Float
		for (const FCsFX_Parameter_Scaled_Float& Param : FX.ScaledParameters.Floats)
		{
			ScaledFloatParameterType* FloatType = Manager_FX->AllocateValue<ScaledFloatParameterType>();

			Param.CopyToParamsAsValue(FloatType);
			Payload->ScaledParameters.Add(FloatType);
		}
		// Vector
		for (const FCsFX_Parameter_Scaled_Vector& Param : FX.ScaledParameters.Vectors)
		{
			ScaledVectorParameterType* VectorType = Manager_FX->AllocateValue<ScaledVectorParameterType>();

			Param.CopyToParamsAsValue(VectorType);
			Payload->ScaledParameters.Add(VectorType);
		}
	}
	// Data Interface
	{
		// Skeletal Mesh
		for (const FCsFX_Parameters_DataInterface_SkeletalMesh& Param : FX.DataInterfaceParameters.SkeletalMeshes)
		{
			SkeletalMeshParameterType* SkeletalMeshType = Manager_FX->AllocateValue<SkeletalMeshParameterType>();

			Param.CopyToParamsAsValue(SkeletalMeshType);
			Payload->SkeletalMeshParameters.Add(SkeletalMeshType);
		}
	}
}

bool FCsPayload_FX::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(FX);
	return true;
}

bool FCsPayload_FX::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/) const
{
	CS_IS_VALID(FX)
	return true;
}
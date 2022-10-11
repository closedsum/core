// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsLibrary_FX.h"
#include "CsCore.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
	// Common
#include "Game/CsLibrary_GameInstance.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// FX
#include "Managers/FX/Params/CsLibrary_Params_FX.h"
#include "NiagaraActor.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraDataInterfaceArrayInt.h"
#include "NiagaraDataInterfaceArrayFloat.h"
#include "NiagaraFunctionLibrary.h"

namespace NCsFX
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::FLibrary, SafeHasVariableName);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::FLibrary, SafeHasParameter);
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::FLibrary, Spawn_Internal);
			}

			namespace Name
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(NCsFX::FLibrary, Spawn_Internal);
			}
		}
	}

	FLibrary::FLibrary() :
		Manager_SpawnParams()
	{
	}

	FLibrary::~FLibrary()
	{
		Manager_SpawnParams.Shutdown();
	}

	// Load
	#pragma region

	UNiagaraSystem* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UNiagaraSystem>(Context, Path, Log);
	}

	UNiagaraSystem* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UNiagaraSystem>(Context, Path, Log);
	}

	#pragma endregion Load

	// Parameter
	#pragma region

	#define ParameterValueType NCsFX::NParameter::EValue

	bool FLibrary::HasVariableNameChecked(const FString& Context, UNiagaraSystem* System, const FName& Name, const ParameterValueType& ValueType)
	{
		// Check System is Valid
		CS_IS_PTR_NULL_CHECKED(System)
		// Check Name is Valid
		CS_IS_NAME_NONE_CHECKED(Name)
		// Check ValueType is Valid
		typedef NCsFX::NParameter::EMValue ParameterValueMapType;

		check(ParameterValueMapType::Get().IsValidEnumChecked(Context, ValueType));

		static TArray<FNiagaraVariable> Parameters;

		Parameters.Reset(Parameters.Max());

		System->GetExposedParameters().GetParameters(Parameters);

		bool Found = false;

		for (FNiagaraVariable& Var : Parameters)
		{
			if (Name == Var.GetName())
				Found = true;
		}

		checkf(Found, TEXT("%s: Failed to find Parameter with Name: %s on System: %s."), *Context, *(Name.ToString()), *(System->GetName()));
		return true;
	}

	bool FLibrary::SafeHasVariableName(const FString& Context, UNiagaraSystem* System, const FName& Name, const ParameterValueType& ValueType, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check System is Valid
		CS_IS_PTR_NULL(System)
		// Check Name is Valid
		CS_IS_NAME_NONE(Name)
		// Check ValueType is Valid
		typedef NCsFX::NParameter::EMValue ParameterValueMapType;

		if (!ParameterValueMapType::Get().IsValidEnum(ValueType))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ValueType: %s is NOT Valid."), *Context, ParameterValueMapType::Get().ToChar(ValueType)));
			return false;
		}

		static TArray<FNiagaraVariable> Parameters;

		Parameters.Reset(Parameters.Max());

		System->GetExposedParameters().GetParameters(Parameters);

		for (FNiagaraVariable& Var : Parameters)
		{
			if (Name == Var.GetName())
			{
				// Check ValueType is the same as Var's Type
				if (NCsFX::NParameter::NValue::GetSizeInBytes(ValueType) != Var.GetSizeInBytes())
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ValueType: %s does NOT match variable type."), *Context, ParameterValueMapType::Get().ToChar(ValueType)));
					return false;
				}
				return true;
			}
		}

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Parameter with Name: %s on System: %s."), *Context, *(Name.ToString()), *(System->GetName())));
		return false;
	}

	bool FLibrary::SafeHasVariableName(UNiagaraSystem* System, const FName& Name, const ParameterValueType& ValueType)
	{
		using namespace NCsFX::NLibrary::NCached;

		const FString& Context = Str::SafeHasVariableName;

		return SafeHasVariableName(Context, System, Name, ValueType, nullptr);
	}

	#undef ParameterValueType

	#define ParameterType NCsFX::NParameter::IParameter
	#define ScaledParameterType NCsFX::NParameter::NScaled::IScaled

	bool FLibrary::HasParameterChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter)
	{
		// Check System is Valid
		CS_IS_PTR_NULL_CHECKED(System)
		// Check Parameter is Valid
		typedef NCsFX::NParameter::FLibrary ParameterLibrary;

		check(ParameterLibrary::IsValidChecked(Context, Parameter));

		const FName& Name = Parameter->GetName();

		static TArray<FNiagaraVariable> Parameters;
		Parameters.Reset(Parameters.Max());

		System->GetExposedParameters().GetParameters(Parameters);

		bool Found = false;

		for (FNiagaraVariable& Var : Parameters)
		{
			if (Name == Var.GetName())
			{
				// Check Parameter's Type is the same as Var's Type
				typedef NCsFX::NParameter::EMValue ParameterValueMapType;

				checkf(Parameter->GetSizeInBytes() == Var.GetSizeInBytes(), TEXT("%s: Parameter type: %s does NOT match variable type."), *Context, ParameterValueMapType::Get().ToChar(Parameter->GetValueType()));

				Found = true;
				break;
			}
		}

		checkf(Found, TEXT("%s: Failed to find Parameter with Name: %s on System: %s."), *Context, *(Name.ToString()), *(System->GetName()));
		return true;
	}

	bool FLibrary::SafeHasParameter(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check System is Valid
		CS_IS_PTR_NULL(System)
		// Check Parameter is Valid
		typedef NCsFX::NParameter::FLibrary ParameterLibrary;

		if (!ParameterLibrary::IsValid(Context, Parameter, Log))
			return false;

		const FName& Name = Parameter->GetName();

		static TArray<FNiagaraVariable> Parameters;

		Parameters.Reset(Parameters.Max());

		System->GetExposedParameters().GetParameters(Parameters);

		for (FNiagaraVariable& Var : Parameters)
		{
			if (Name == Var.GetName())
			{
				// Check Parameter's Type is the same as Var's Type
				if (Parameter->GetSizeInBytes() != Var.GetSizeInBytes())
				{
					typedef NCsFX::NParameter::EMValue ParameterValueMapType;

					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Parameter type: %s does NOT match variable type."), *Context, ParameterValueMapType::Get().ToChar(Parameter->GetValueType())));
					return false;
				}
				return true;
			}
		}
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Parameter with Name: %s on System: %s."), *Context, *(Name.ToString()), *(System->GetName())));
		return false;
	}

	bool FLibrary::SafeHasParameter(UNiagaraSystem* System, const ParameterType* Parameter)
	{
		using namespace NCsFX::NLibrary::NCached;

		const FString& Context = Str::SafeHasVariableName;

		return SafeHasParameter(Context, System, Parameter, nullptr);
	}

	
	bool FLibrary::HasParameterChecked(const FString& Context, UNiagaraSystem* System, const ScaledParameterType* Parameter)
	{
		// Check System is Valid
		CS_IS_PTR_NULL_CHECKED(System)

		CS_IS_PTR_NULL_CHECKED(Parameter)
		return HasParameterChecked(Context, System, Parameter->GetParameter());
	}

	void FLibrary::SetParameterChecked(const FString& Context, UNiagaraComponent* Component, const ParameterType* Parameter)
	{
		CS_IS_PTR_NULL_CHECKED(Component)

		UNiagaraSystem* System = Component->GetAsset();

		checkf(System, TEXT("%s: Asset on Component: %s is NULL."), *Context, *(Component->GetName()));

		check(HasParameterChecked(Context, System, Parameter));

		typedef NCsFX::NParameter::EValue ParameterValueType;
		typedef NCsFX::NParameter::FLibrary ParameterLibrary;

		const ParameterValueType& ValueType = Parameter->GetValueType();

		// Int
		if (ValueType == ParameterValueType::Int)
			Component->SetVariableInt(Parameter->GetName(), ParameterLibrary::GetIntChecked(Context, Parameter));
		// Float
		if (ValueType == ParameterValueType::Float)
			Component->SetVariableFloat(Parameter->GetName(), ParameterLibrary::GetFloatChecked(Context, Parameter));
		// Vector
		else
		if (ValueType == ParameterValueType::Vector)
			Component->SetVariableVec3(Parameter->GetName(), ParameterLibrary::GetVectorChecked(Context, Parameter));
	}

	void FLibrary::SetParameterChecked(const FString& Context, UNiagaraComponent* Component, const ScaledParameterType* ScaledParameter, const float& Scale)
	{
		CS_IS_PTR_NULL_CHECKED(Component)

		UNiagaraSystem* System = Component->GetAsset();

		checkf(System, TEXT("%s: Asset on Component: %s is NULL."), *Context, *(Component->GetName()));

		check(HasParameterChecked(Context, System, ScaledParameter));

		typedef NCsFX::NParameter::EValue ParameterValueType;
		typedef NCsFX::NParameter::FLibrary ParameterLibrary;

		const ParameterType* Parameter		= ScaledParameter->GetParameter();
		const ParameterValueType& ValueType = Parameter->GetValueType();

		// Int
		if (ValueType == ParameterValueType::Int)
		{
			int32 Value = 0.0f;

			if (ScaledParameter->ShouldSetValue())
			{
				Value = ParameterLibrary::GetIntChecked(Context, Parameter);
			}
			else
			{
				Value = GetDefaultVariableIntChecked(Context, System, Parameter);
			}

			const float Max	   = Component->GetComponentScale().GetMax() * Scale;
			const float Result = ScaledParameter->ShouldApplyInverse() ? 1.0f / Max : Max;
			Value			   = ScaledParameter->GetScale() * Result * Value;

			Component->SetVariableInt(Parameter->GetName(), Value);
		}
		// Float
		else
		if (ValueType == ParameterValueType::Float)
		{
			float Value = 0.0f;

			if (ScaledParameter->ShouldSetValue())
			{
				Value = ParameterLibrary::GetFloatChecked(Context, Parameter);
			}
			else
			{
				Value = GetDefaultVariableFloatChecked(Context, System, Parameter);
			}

			const float Max	   = Component->GetComponentScale().GetMax() * Scale;
			const float Result = ScaledParameter->ShouldApplyInverse() ? 1.0f / Max : Max;
			Value			   = ScaledParameter->GetScale() * Result * Value;

			Component->SetVariableFloat(Parameter->GetName(), Value);
		}
		// Vector
		else
		if (ValueType == ParameterValueType::Vector)
		{
			FVector Value = FVector::ZeroVector;

			if (ScaledParameter->ShouldSetValue())
			{
				Value = ParameterLibrary::GetVectorChecked(Context, Parameter);
			}
			else
			{
				Value = GetDefaultVariableVectorChecked(Context, System, Parameter);
			}

			const float Max	   = Component->GetComponentScale().GetMax() * Scale;
			const float Result = ScaledParameter->ShouldApplyInverse() ? 1.0f / Max : Max;
			Value			   = ScaledParameter->GetScale() * Scale * Value;

			Component->SetVariableVec3(Parameter->GetName(), Value);
		}
	}

	FNiagaraVariable* FLibrary::GetDefaultVariableChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter)
	{
		CS_IS_PTR_NULL_CHECKED(System)

		// Check Parameter is Valid
		typedef NCsFX::NParameter::FLibrary ParameterLibrary;

		check(ParameterLibrary::IsValidChecked(Context, Parameter));

		const FNiagaraSystemCompiledData& CompiledData = System->GetSystemCompiledData();

		static TArray<FNiagaraVariable> Parameters;
		Parameters.Reset(Parameters.Max());

		CompiledData.InstanceParamStore.GetParameters(Parameters);

		const FName& Name = Parameter->GetName();

		for (FNiagaraVariable& Var : Parameters)
		{
			if (Name == Var.GetName())
			{
				return &Var;
			}
		}
		checkf(0, TEXT("%s: Failed to find Parameter with Name: %s on System: %s."), *Context, *(Name.ToString()), *(System->GetName()));
		return nullptr;
	}

	int32 FLibrary::GetDefaultVariableIntChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter)
	{
		FNiagaraVariable* Var = GetDefaultVariableChecked(Context, System, Parameter);

		const FNiagaraSystemCompiledData& CompiledData = System->GetSystemCompiledData();
		const FNiagaraParameterStore& Store			   = CompiledData.InstanceParamStore;

		// Check Parameter's Type is the same as Var's Type
		typedef NCsFX::NParameter::EMValue ParameterValueMapType;

		checkf(Parameter->GetSizeInBytes() == Var->GetSizeInBytes(), TEXT("%s: Parameter type: %s does NOT match variable type."), *Context, ParameterValueMapType::Get().ToChar(Parameter->GetValueType()));

		return Store.GetParameterValue<int32>(*Var);
	}

	float FLibrary::GetDefaultVariableFloatChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter)
	{
		FNiagaraVariable* Var = GetDefaultVariableChecked(Context, System, Parameter);

		const FNiagaraSystemCompiledData& CompiledData = System->GetSystemCompiledData();
		const FNiagaraParameterStore& Store			   = CompiledData.InstanceParamStore;

		// Check Parameter's Type is the same as Var's Type
		typedef NCsFX::NParameter::EMValue ParameterValueMapType;

		checkf(Parameter->GetSizeInBytes() == Var->GetSizeInBytes(), TEXT("%s: Parameter type: %s does NOT match variable type."), *Context, ParameterValueMapType::Get().ToChar(Parameter->GetValueType()));

		return Store.GetParameterValue<float>(*Var);
	}

	FVector FLibrary::GetDefaultVariableVectorChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter)
	{
		FNiagaraVariable* Var = GetDefaultVariableChecked(Context, System, Parameter);

		const FNiagaraSystemCompiledData& CompiledData = System->GetSystemCompiledData();
		const FNiagaraParameterStore& Store			   = CompiledData.InstanceParamStore;

		// Check Parameter's Type is the same as Var's Type
		typedef NCsFX::NParameter::EMValue ParameterValueMapType;

		checkf(Parameter->GetSizeInBytes() == Var->GetSizeInBytes(), TEXT("%s: Parameter type: %s does NOT match variable type."), *Context, ParameterValueMapType::Get().ToChar(Parameter->GetValueType()));

		return Store.GetParameterValue<FVector>(*Var);
	}

	#undef ParameterType
	#undef ScaledParameterType

	void FLibrary::SetArrayInt32Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<int32>& ArrayData)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, int32)

		UNiagaraDataInterfaceArrayInt32* ArrayDI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceArrayInt32>(System, OverrideName);

		checkf(ArrayDI, TEXT("%s: Failed to find TArray<int32> Parameter for System: %s with OverrideName: %s."), *Context, *(System->GetName()), *(OverrideName.ToString()));
		
		FRWScopeLock WriteLock(ArrayDI->ArrayRWGuard, SLT_Write);
		ArrayDI->IntData = ArrayData;
		ArrayDI->MarkRenderDataDirty();
	}

	void FLibrary::SetArrayInt32Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<int32>& ArrayData, TArray<int32>& Indices)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, int32)
		CS_IS_TARRAY_EMPTY_CHECKED(Indices, int32)

		UNiagaraDataInterfaceArrayInt32* ArrayDI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceArrayInt32>(System, OverrideName);

		checkf(ArrayDI, TEXT("%s: Failed to find TArray<int32> Parameter for System: %s with OverrideName: %s."), *Context, *(System->GetName()), *(OverrideName.ToString()));
		
		FRWScopeLock WriteLock(ArrayDI->ArrayRWGuard, SLT_Write);

		if (ArrayData.Num() > ArrayDI->IntData.Num())
		{
			ArrayDI->IntData = ArrayData;
			Indices.Reset(Indices.Max());
		}
		else
		{
			const int32 Count = Indices.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const int32& Index = Indices[I];

				ArrayDI->IntData[Index] = ArrayData[Index];
				Indices.RemoveAt(I, 1, false);
			}
		}
		ArrayDI->MarkRenderDataDirty();
	}

	void FLibrary::SetArrayFloatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<float>& ArrayData)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, float)

		UNiagaraDataInterfaceArrayFloat* ArrayDI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceArrayFloat>(System, OverrideName);

		checkf(ArrayDI, TEXT("%s: Failed to find TArray<float> Parameter for System: %s with OverrideName: %s."), *Context, *(System->GetName()), *(OverrideName.ToString()));
		
		FRWScopeLock WriteLock(ArrayDI->ArrayRWGuard, SLT_Write);
		ArrayDI->FloatData = ArrayData;
		ArrayDI->MarkRenderDataDirty();
	}

	void FLibrary::SetArrayFloatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<float>& ArrayData, TArray<int32>& Indices)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, float)
		CS_IS_TARRAY_EMPTY_CHECKED(Indices, int32)

		UNiagaraDataInterfaceArrayFloat* ArrayDI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceArrayFloat>(System, OverrideName);

		checkf(ArrayDI, TEXT("%s: Failed to find TArray<float> Parameter for System: %s with OverrideName: %s."), *Context, *(System->GetName()), *(OverrideName.ToString()));
		
		FRWScopeLock WriteLock(ArrayDI->ArrayRWGuard, SLT_Write);

		if (ArrayData.Num() > ArrayDI->FloatData.Num())
		{
			ArrayDI->FloatData = ArrayData;
			Indices.Reset(Indices.Max());
		}
		else
		{
			const int32 Count = Indices.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const int32& Index = Indices[I];

				ArrayDI->FloatData[Index] = ArrayData[Index];
				Indices.RemoveAt(I, 1, false);
			}
		}
		ArrayDI->MarkRenderDataDirty();
	}

	void FLibrary::SetArrayVectorChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector>& ArrayData)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, FVector)

		UNiagaraDataInterfaceArrayFloat3* ArrayDI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceArrayFloat3>(System, OverrideName);
	
		checkf(ArrayDI, TEXT("%s: Failed to find TArray<FVector> Parameter for System: %s with OverrideName: %s."), *Context, *(System->GetName()), *(OverrideName.ToString()));

		FRWScopeLock WriteLock(ArrayDI->ArrayRWGuard, SLT_Write);
		ArrayDI->FloatData = ArrayData;
		ArrayDI->MarkRenderDataDirty();
	}

	void FLibrary::SetArrayVectorChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector>& ArrayData, TArray<int32>& Indices)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, FVector)
		CS_IS_TARRAY_EMPTY_CHECKED(Indices, int32)

		UNiagaraDataInterfaceArrayFloat3* ArrayDI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceArrayFloat3>(System, OverrideName);
	
		checkf(ArrayDI, TEXT("%s: Failed to find TArray<FVector> Parameter for System: %s with OverrideName: %s."), *Context, *(System->GetName()), *(OverrideName.ToString()));

		FRWScopeLock WriteLock(ArrayDI->ArrayRWGuard, SLT_Write);
		
		if (ArrayData.Num() > ArrayDI->FloatData.Num())
		{
			ArrayDI->FloatData = ArrayData;
			Indices.Reset(Indices.Max());
		}
		else
		{
			const int32 Count = Indices.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const int32& Index = Indices[I];

				ArrayDI->FloatData[Index] = ArrayData[Index];
				Indices.RemoveAt(I, 1, false);
			}
		}
		ArrayDI->MarkRenderDataDirty();
	}

	void FLibrary::SetArrayVector4Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector4>& ArrayData)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, FVector4)

		UNiagaraDataInterfaceArrayFloat4* ArrayDI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceArrayFloat4>(System, OverrideName);
	
		checkf(ArrayDI, TEXT("%s: Failed to find TArray<FVector> Parameter for System: %s with OverrideName: %s."), *Context, *(System->GetName()), *(OverrideName.ToString()));

		FRWScopeLock WriteLock(ArrayDI->ArrayRWGuard, SLT_Write);
		ArrayDI->FloatData = ArrayData;
		ArrayDI->MarkRenderDataDirty();
	}

	void FLibrary::SetArrayVector4Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector4>& ArrayData, TArray<int32>& Indices)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, FVector4)
		CS_IS_TARRAY_EMPTY_CHECKED(Indices, int32)

		UNiagaraDataInterfaceArrayFloat4* ArrayDI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceArrayFloat4>(System, OverrideName);
	
		checkf(ArrayDI, TEXT("%s: Failed to find TArray<FVector> Parameter for System: %s with OverrideName: %s."), *Context, *(System->GetName()), *(OverrideName.ToString()));

		FRWScopeLock WriteLock(ArrayDI->ArrayRWGuard, SLT_Write);
		
		if (ArrayData.Num() > ArrayDI->FloatData.Num())
		{
			ArrayDI->FloatData = ArrayData;
			Indices.Reset(Indices.Max());
		}
		else
		{
			const int32 Count = Indices.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const int32& Index = Indices[I];

				ArrayDI->FloatData[Index] = ArrayData[Index];
				Indices.RemoveAt(I, 1, false);
			}
		}
		ArrayDI->MarkRenderDataDirty();
	}

	void FLibrary::SetArrayQuatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FQuat>& ArrayData)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, FQuat)

		UNiagaraDataInterfaceArrayQuat* ArrayDI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceArrayQuat>(System, OverrideName);

		checkf(ArrayDI, TEXT("%s: Failed to find TArray<FQuat> Parameter for System: %s with OverrideName: %s."), *Context, *(System->GetName()), *(OverrideName.ToString()));

		FRWScopeLock WriteLock(ArrayDI->ArrayRWGuard, SLT_Write);
		ArrayDI->QuatData = ArrayData;
		ArrayDI->MarkRenderDataDirty();
	}

	void FLibrary::SetArrayQuatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FQuat>& ArrayData, TArray<int32>& Indices)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, FQuat)
		CS_IS_TARRAY_EMPTY_CHECKED(Indices, int32)

		UNiagaraDataInterfaceArrayQuat* ArrayDI = UNiagaraFunctionLibrary::GetDataInterface<UNiagaraDataInterfaceArrayQuat>(System, OverrideName);

		checkf(ArrayDI, TEXT("%s: Failed to find TArray<FQuat> Parameter for System: %s with OverrideName: %s."), *Context, *(System->GetName()), *(OverrideName.ToString()));

		FRWScopeLock WriteLock(ArrayDI->ArrayRWGuard, SLT_Write);
		
		if (ArrayData.Num() > ArrayDI->QuatData.Num())
		{
			ArrayDI->QuatData = ArrayData;
			Indices.Reset(Indices.Max());
		}
		else
		{
			const int32 Count = Indices.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const int32& Index = Indices[I];

				ArrayDI->QuatData[Index] = ArrayData[Index];
				Indices.RemoveAt(I, 1, false);
			}
		}
		ArrayDI->MarkRenderDataDirty();
	}

	#pragma endregion Parameter

	// Spawn
	#pragma region

	#define ParamsResourceType NCsFX::NSpawn::NParams::FResource
	#define ParamsType NCsFX::NSpawn::NParams::FParams

	FCsRoutineHandle FLibrary::SpawnChecked(const FString& Context, UObject* WorldContext, ParamsResourceType* Params)
	{
		using namespace NCsFX::NLibrary::NCached;

		check(Get().Manager_SpawnParams.ContainsChecked(Context, Params));

		check(Params->Get()->IsValidChecked(Context));

		typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

		UObject* ContextRoot = CoroutineSchedulerLibrary::GetContextRootChecked(Context, WorldContext);

		UCsCoroutineScheduler* Scheduler   = UCsCoroutineScheduler::Get(ContextRoot);
		const FECsUpdateGroup& UpdateGroup = Params->Get()->Group;

		typedef NCsCoroutine::NPayload::FImpl PayloadType;

		PayloadType* Payload = Scheduler->AllocatePayload(UpdateGroup);

		#define COROUTINE Spawn_Internal

		Payload->CoroutineImpl.BindStatic(&NCsFX::FLibrary::COROUTINE);
		Payload->StartTime = UCsManager_Time::Get(ContextRoot)->GetTime(UpdateGroup);
		Payload->Owner.SetObject(WorldContext);
		Payload->SetName(Str::COROUTINE);
		Payload->SetFName(Name::COROUTINE);

		#undef COROUTINE

		// Set End callback (to free any allocated references)
		typedef NCsCoroutine::FOnEnd OnEndType;

		Payload->OnEnds.AddDefaulted();
		OnEndType& OnEnd = Payload->OnEnds.Last();
		OnEnd.BindStatic(&FLibrary::Spawn_Internal_OnEnd);

		static const int32 RESOURCE = 0;
		Payload->SetValue_Void(RESOURCE, Params);

		ParamsType* P = Params->Get();
		P->Update();
	
		typedef NCsSpawner::NParams::FFrequency FrequencyParamsType;

		const FrequencyParamsType& FrequencyParams = Params->Get()->FrequencyParams;
		const float TotalTime = FrequencyParams.CalculateTotalTime();

		static const int32 TOTAL_TIME = 0;
		Payload->SetValue_Float(TOTAL_TIME, TotalTime);

		return Scheduler->Start(Payload);
	}

	FCsRoutineHandle FLibrary::SafeSpawn(const FString& Context, UObject* WorldContext, ParamsResourceType* Params, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		// Check to get Context Root for Manager_FX
		{
			typedef NCsFX::NManager::FLibrary FXManagerLibrary;

			UObject* ContextRoot = FXManagerLibrary::GetSafeContextRoot(Context, WorldContext, Log);

#if WITH_EDITOR
			if (!ContextRoot)
				return FCsRoutineHandle::Invalid;
#endif // #if WITH_EDITOR
		}

		// Check Params are Valid.
		if (!Params)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Params is NULL."), *Context));
			return FCsRoutineHandle::Invalid;
		}
		// Check Params's Resource is Valid.
		if (!Params->Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Params's Resource is NULL."), *Context));
			return FCsRoutineHandle::Invalid;
		}

		if (!Params->Get()->IsValid(Context))
			return FCsRoutineHandle::Invalid;

		if (!Get().Manager_SpawnParams.Contains(Params))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Params has NOT been allocated from pool. Use the method that passes by const reference."), *Context));
			return FCsRoutineHandle::Invalid;
		}
		
		// Check to get Context Root for CoroutineScheduler
		{
			typedef NCsCoroutine::NScheduler::FLibrary CoroutineSchedulerLibrary;

			UObject* ContextRoot = CoroutineSchedulerLibrary::GetSafeContextRoot(Context, WorldContext, Log);

#if WITH_EDITOR
			if (!ContextRoot)
				return FCsRoutineHandle::Invalid;
#endif // #if WITH_EDITOR
		}

		return SpawnChecked(Context, WorldContext, Params);
	}

	char FLibrary::Spawn_Internal(FCsRoutine* R)
	{
		using namespace NCsFX::NLibrary::NCached;

		const FString& Context = Str::Spawn_Internal;

		static const int32 RESOURCE				  = 0;
		const ParamsResourceType* ParamsContainer = R->GetValue_Void<ParamsResourceType>(RESOURCE);
		const ParamsType* Params				  = ParamsContainer->Get();

		typedef NCsSpawner::NParams::FFrequency FrequencyParamsType;
		typedef NCsSpawner::EFrequency FrequencyType;

		const FrequencyParamsType& FrequencyParams = Params->FrequencyParams;
		const NCsSpawner::EFrequency& FreqType = FrequencyParams.GetType();

		static const int32 CAN_SPAWN = 0;
		bool& CanSpawn				 = R->GetValue_Flag(CAN_SPAWN);

		static const int32 HAS_SPAWN_INTERVAL = 1;
		bool& HasSpawnInterval				  = R->GetValue_Flag(HAS_SPAWN_INTERVAL);

		static const int32 SPAWN_COUNT = 0;
		int32& SpawnCount			   = R->GetValue_Int(SPAWN_COUNT);

		static const int32 TOTAL_TIME = 0;
		const float& TotalTime		  = R->GetValue_Float(TOTAL_TIME);

		FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);
		ElapsedTime += R->DeltaTime;

		CS_COROUTINE_BEGIN(R)

		do
		{
			{
				ElapsedTime.Reset();

				// Spawn FX
				{
					typedef NCsFX::NManager::FLibrary FXManagerLibrary;
					typedef NCsPooledObject::NPayload::FImplSlice PayloadImplType;

					UObject* Owner = R->GetOwnerAsObject();

					PayloadImplType Payload;
					Payload.Instigator = Owner;
					Payload.Parent	   = Params->GetActor();

					FXManagerLibrary::SpawnChecked(Context, R->GetOwnerAsObject(), &Payload, Params->FX);
				}

				++SpawnCount;

				// Once
				if (FreqType == FrequencyType::Once)
				{
					 // Do Nothing 
				}
				// Count | TimeCount | TimeInterval
				else
				if (FreqType == FrequencyType::Count ||
					FreqType == FrequencyType::TimeCount ||
					FreqType == FrequencyType::TimeInterval)
				{
					CanSpawn		 = SpawnCount < FrequencyParams.GetCount();
					HasSpawnInterval = CanSpawn && FrequencyParams.GetInterval() > 0.0f;
				}
				// Infinite
				else
				if (FreqType == FrequencyType::Infinite)
				{
					CanSpawn		 = true;
					HasSpawnInterval = true;
				}

				if (HasSpawnInterval)
				{
					CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= FrequencyParams.GetInterval());
				}
			}
		} while (CanSpawn);

		CS_COROUTINE_WAIT_UNTIL(R, R->ElapsedTime.Time >= TotalTime);

		CS_COROUTINE_END(R)
	}

	void FLibrary::Spawn_Internal_OnEnd(FCsRoutine* R)
	{
		static const int32 RESOURCE  = 0;
		ParamsResourceType* Resource = R->GetValue_Void<ParamsResourceType>(RESOURCE);
		ParamsType* Params			 = Resource->Get();
		Params->Reset();

		Get().Manager_SpawnParams.Deallocate(Resource);
	}

	#undef ParamsResourceType
	#undef ParamsType

	#pragma endregion Spawn

	// State
	#pragma region

	bool FLibrary::IsCompleteChecked(const FString& Context, ANiagaraActor* Actor)
	{
		CS_IS_PTR_NULL_CHECKED(Actor)

		UNiagaraComponent* Component = Actor->GetNiagaraComponent();

		return IsCompleteChecked(Context, Component);
	}

	bool FLibrary::IsCompleteChecked(const FString& Context, UNiagaraComponent* Component)
	{
		CS_IS_PTR_NULL_CHECKED(Component)

		FNiagaraSystemInstance* SystemInstance = Component->GetSystemInstance();

		// NOTE: FUTURE: HACK: check to deal with Mobile PIE crashes
	#if WITH_EDITOR
		typedef NCsGameInstance::FLibrary GameInstanceLibrary;

		if (GameInstanceLibrary::IsStandaloneMobileFromEditorChecked(Context, Component))
		{
			if (!SystemInstance)
				return true;
		}
	#endif // #if WITH_EDITOR

		checkf(SystemInstance, TEXT("%s: SystemInstance is NULL on FXComponent: %s."), *Context, *(Component->GetName()));

		const ENiagaraExecutionState ExecutionState = SystemInstance->GetActualExecutionState();

		return ExecutionState == ENiagaraExecutionState::Complete ||
			   ExecutionState == ENiagaraExecutionState::Disabled;
	}

	bool FLibrary::IsInactiveChecked(const FString& Context, UNiagaraComponent* Component)
	{
		CS_IS_PTR_NULL_CHECKED(Component)
	
		FNiagaraSystemInstance* SystemInstance = Component->GetSystemInstance();

		// NOTE: FUTURE: HACK: check to deal with Mobile PIE crashes
	#if WITH_EDITOR
		typedef NCsGameInstance::FLibrary GameInstanceLibrary;

		if (GameInstanceLibrary::IsStandaloneMobileFromEditorChecked(Context, Component))
		{
			if (!SystemInstance)
				return true;
		}
	#endif // #if WITH_EDITOR

		checkf(SystemInstance, TEXT("%s: SystemInstance is NULL on FXComponent: %s."), *Context, *(Component->GetName()));

		const ENiagaraExecutionState ExecutionState = SystemInstance->GetActualExecutionState();

		return ExecutionState == ENiagaraExecutionState::Inactive;
	}

	void FLibrary::ResetAllChecked(const FString& Context, UNiagaraComponent* Component)
	{
		CS_IS_PTR_NULL_CHECKED(Component)

		FNiagaraSystemInstance* SystemInstance = Component->GetSystemInstance();

		checkf(SystemInstance, TEXT("%s: SystemInstance is NULL on FXComponent: %s."), *Context, *(Component->GetName()));

		SystemInstance->Reset(FNiagaraSystemInstance::EResetMode::ReInit);
	}

	#pragma endregion State
}
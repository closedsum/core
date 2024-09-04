// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/CsLibrary_FX.h"
#include "CsFX.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
	// Common
#include "NiagaraFunctionLibrary.h"
#include "Library/CsLibrary_World.h"
#include "Game/CsLibrary_GameInstanceImpl.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Time/CsManager_Time.h"
#include "Managers/FX/Actor/CsManager_FX.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// FX
#include "Managers/FX/Params/CsLibrary_Params_FX.h"
#include "NiagaraActor.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraDataInterfaceArrayInt.h"
#include "NiagaraDataInterfaceArrayFloat.h"
#include "DataInterface/CsNiagaraDataInterfaceArrayFloatRW.h"
#include "DataInterface/CsNiagaraDataInterfaceArrayRWImpl.h"
#include "NiagaraDataInterfaceSkeletalMesh.h"
#include "NiagaraDataInterfaceArrayImpl.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraParameterCollection.h"
#include "NiagaraSystemInstanceController.h"

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

	UNiagaraSystem* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UNiagaraSystem>(Context, Path, Log);
	}

	UNiagaraSystem* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		return ObjectLibrary::SafeLoad<UNiagaraSystem>(Context, Path, Log);
	}

	#pragma endregion Load

	UNiagaraParameterCollectionInstance* FLibrary::GetInstancedChecked(const FString& Context, const UObject* WorldContext, UNiagaraParameterCollection* Collection)
	{
		CS_IS_PENDING_KILL_CHECKED(WorldContext)
		CS_IS_PTR_NULL_CHECKED(Collection)

		UWorld* World = CsWorldLibrary::GetChecked(Context, WorldContext);

		UNiagaraParameterCollectionInstance* Instance = UNiagaraFunctionLibrary::GetNiagaraParameterCollection(World, Collection);
		
		CS_IS_PTR_NULL_CHECKED(Instance)
		return Instance;
	}

	// Parameter
	#pragma region

	bool FLibrary::IsValidUserVariableNameChecked(const FString& Context, const FName& Name)
	{
		CS_IS_NAME_NONE_CHECKED(Name)
		checkf(Name.ToString().StartsWith(TEXT("User.")), TEXT("%s: %s does NOT start with 'User.'"), *Context);
		return true;
	}

	bool FLibrary::IsValidUserVariableName(const FString& Context, const FName& Name, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
	{
		CS_IS_NAME_NONE(Name)

		if (!Name.ToString().StartsWith(TEXT("User.")))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT start with 'User.'"), *Context));
			return false;
		}
		return true;
	}

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

	bool FLibrary::SafeHasVariableName(const FString& Context, UNiagaraSystem* System, const FName& Name, const ParameterValueType& ValueType, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
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
		CS_IS_PENDING_KILL_CHECKED(System)
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

	bool FLibrary::SafeHasParameter(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
	{
		// Check System is Valid
		CS_IS_PENDING_KILL(System)
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
		typedef NCsMath::FLibrary MathLibrary;

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
			Component->SetVariableVec3(Parameter->GetName(), MathLibrary::Convert(ParameterLibrary::GetVectorChecked(Context, Parameter)));
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
			FVector3f Value = FVector3f::ZeroVector;

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

			typedef NCsMath::FLibrary MathLibrary;

			Component->SetVariableVec3(Parameter->GetName(), MathLibrary::Convert(Value));
		}
	}

	void FLibrary::SetIntParameterChecked(const FString& Context, ANiagaraActor* Actor, const FName& ParameterName, const int32& Value)
	{
		CS_IS_PENDING_KILL_CHECKED(Actor)

		SetIntParameterChecked(Context, Actor->GetNiagaraComponent(), ParameterName, Value);
	}

	void FLibrary::SetIntParameterChecked(const FString& Context, UNiagaraComponent* Component, const FName& ParameterName, const int32& Value)
	{
		typedef NCsFX::NParameter::NInt::FIntType IntType;

		IntType Parameter;
		Parameter.SetName(ParameterName);
		Parameter.SetValue(Value);

		SetParameterChecked(Context, Component, &Parameter);
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

	FVector3f FLibrary::GetDefaultVariableVectorChecked(const FString& Context, UNiagaraSystem* System, const ParameterType* Parameter)
	{
		FNiagaraVariable* Var = GetDefaultVariableChecked(Context, System, Parameter);

		const FNiagaraSystemCompiledData& CompiledData = System->GetSystemCompiledData();
		const FNiagaraParameterStore& Store			   = CompiledData.InstanceParamStore;

		// Check Parameter's Type is the same as Var's Type
		typedef NCsFX::NParameter::EMValue ParameterValueMapType;

		checkf(Parameter->GetSizeInBytes() == Var->GetSizeInBytes(), TEXT("%s: Parameter type: %s does NOT match variable type."), *Context, ParameterValueMapType::Get().ToChar(Parameter->GetValueType()));

		return Store.GetParameterValue<FVector3f>(*Var);
	}

	#undef ParameterType
	#undef ScaledParameterType

	#define SkeletalMeshParameterType NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType

	UNiagaraDataInterfaceSkeletalMesh* FLibrary::GetDataInterfaceChecked(const FString& Context, UNiagaraComponent* Component, const SkeletalMeshParameterType* Parameter)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)
		CS_IS_PTR_NULL_CHECKED(Parameter)
		check(Parameter->IsValidChecked(Context));

		const FNiagaraParameterStore& OverrideParameters = Component->GetOverrideParameters();

		FNiagaraVariable Variable(FNiagaraTypeDefinition(UNiagaraDataInterfaceSkeletalMesh::StaticClass()), Parameter->GetName());

		const int32 Index = OverrideParameters.IndexOf(Variable);

		UNiagaraSystem* System = Component->GetAsset();

		CS_IS_PENDING_KILL_CHECKED(System)

		checkf(Index != INDEX_NONE, TEXT("%s: Failed to find Data Interface of type: Skeletal Mesh with name: %s for System: %s."), *Context, *(Parameter->GetName().ToString()), *(System->GetName()));

		UNiagaraDataInterfaceSkeletalMesh* DataInterface = Cast<UNiagaraDataInterfaceSkeletalMesh>(OverrideParameters.GetDataInterface(Index));
	
		checkf(DataInterface, TEXT("%s: Data Interface: %s is NOT of type: Skeletal Mesh."), *Context, *(Parameter->GetName().ToString()));
		return DataInterface;
	}

	UNiagaraDataInterfaceSkeletalMesh* FLibrary::GetSafeDataInterface(const FString& Context, UNiagaraComponent* Component, const SkeletalMeshParameterType* Parameter, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
	{
		CS_IS_PENDING_KILL_RET_NULL(Component)
		CS_IS_PTR_NULL_RET_NULL(Parameter)

		if (!Parameter->IsValid(Context, Log))
			return nullptr;

		const FNiagaraParameterStore& OverrideParameters = Component->GetOverrideParameters();

		FNiagaraVariable Variable(FNiagaraTypeDefinition(UNiagaraDataInterfaceSkeletalMesh::StaticClass()), Parameter->GetName());

		const int32 Index = OverrideParameters.IndexOf(Variable);

		UNiagaraSystem* System = Component->GetAsset();

		CS_IS_PENDING_KILL_RET_NULL(System)

		if (Index == INDEX_NONE)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Data Interface of type: Skeletal Mesh with name: %s for System: %s."), *Context, *(Parameter->GetName().ToString()), *(System->GetName())));
			return nullptr;
		}

		UNiagaraDataInterfaceSkeletalMesh* DataInterface = Cast<UNiagaraDataInterfaceSkeletalMesh>(OverrideParameters.GetDataInterface(Index));
	
		if (!DataInterface)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data Interface: %s is NOT of type: Skeletal Mesh."), *Context, *(Parameter->GetName().ToString())));
		}
		return DataInterface;
	}

	void FLibrary::SetParameterChecked(const FString& Context, UNiagaraComponent* Component, const SkeletalMeshParameterType* Parameter)
	{
		UNiagaraDataInterfaceSkeletalMesh* DataInterface = GetDataInterfaceChecked(Context, Component, Parameter);

		DataInterface->SetSourceComponentFromBlueprints(Parameter->GetComponent());
	}

	void FLibrary::SetSafeParameter(const FString& Context, UNiagaraComponent* Component, const SkeletalMeshParameterType* Parameter, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
	{
		if (UNiagaraDataInterfaceSkeletalMesh* DataInterface = GetSafeDataInterface(Context, Component, Parameter, Log))
		{
			DataInterface->SetSourceComponentFromBlueprints(Parameter->GetComponent());
		}
	}

	#undef SkeletalMeshParameterType

	template<typename TArrayType, typename TDataInterace>
	void SetNiagaraVariantArray(UNiagaraComponent* NiagaraComponent, FName OverrideName, TDataInterace* ExistingDataInterface)
	{
		// NOTE: Copied from Engine\Plugins\FX\Niagara\Source\Niagara\Private\NiagaraDataInterfaceArrayFunctionLibrary.h
	#if WITH_EDITOR
			// We only need to do this for editor instances of the component as we are storing instance data on them
			// For runtime instances they already have a unique copy of the data interface that we are modifying
			UWorld* World = NiagaraComponent->GetWorld();
			if (World == nullptr || World->IsGameWorld())
			{
				return;
			}

			TDataInterace* VariantDataInterface = CastChecked<TDataInterace>(DuplicateObject(ExistingDataInterface, NiagaraComponent));
			auto* ExistingProxy = static_cast<typename TDataInterace::FProxyType*>(ExistingDataInterface->GetProxy());
			auto* VariantProxy = static_cast<typename TDataInterace::FProxyType*>(VariantDataInterface->GetProxy());
			TArray<TArrayType> TempArrayCopy = ExistingProxy->template GetArrayDataCopy<TArrayType>();
			VariantProxy->template SetArrayData<TArrayType>(MakeArrayView<TArrayType>(TempArrayCopy.GetData(), TempArrayCopy.Num()));
			NiagaraComponent->SetParameterOverride(FNiagaraVariableBase(FNiagaraTypeDefinition(TDataInterace::StaticClass()), OverrideName), FNiagaraVariant(VariantDataInterface));
	#endif // #if WITH_EDITOR
	}

	UNiagaraDataInterfaceArrayInt32* FLibrary::GetArrayInt32Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)

		const FNiagaraParameterStore& OverrideParameters = System->GetOverrideParameters();

		FNiagaraVariable Variable(FNiagaraTypeDefinition(UNiagaraDataInterfaceArrayInt32::StaticClass()), OverrideName);

		const int32 Index = OverrideParameters.IndexOf(Variable);

		checkf(Index != INDEX_NONE, TEXT("%s: Failed to find Data Interface of type: TArray<int32> with name: %s for System: %s."), *Context, *(OverrideName.ToString()), *(System->GetName()));

		UNiagaraDataInterfaceArrayInt32* DataInterface = Cast<UNiagaraDataInterfaceArrayInt32>(OverrideParameters.GetDataInterface(Index));
	
		checkf(DataInterface, TEXT("%s: Data Interface: %s is NOT of type: TArray<int32>."), *Context, *(OverrideName.ToString()));
		return DataInterface;
	}

	UNiagaraDataInterfaceArrayInt32* FLibrary::GetArrayInt32Checked(const FString& Context, UNiagaraParameterCollectionInstance* Collection, const FName& ParameterName)
	{
		CS_IS_PTR_NULL_CHECKED(Collection)
		CS_IS_NAME_NONE_CHECKED(ParameterName)

		FNiagaraParameterStore& Store = Collection->GetParameterStore();

		FNiagaraVariable Variable(FNiagaraTypeDefinition(UNiagaraDataInterfaceArrayInt32::StaticClass()), ParameterName);

		const int32 Index = Store.IndexOf(Variable);

		checkf(Index != INDEX_NONE, TEXT("%s: Failed to find Data Interface of type: TArray<int32> with name: %s for System: %s."), *Context, *(ParameterName.ToString()), *(Collection->GetName()));

		UNiagaraDataInterfaceArrayInt32* DataInterface = Cast<UNiagaraDataInterfaceArrayInt32>(Store.GetDataInterface(Index));

		checkf(DataInterface, TEXT("%s: Data Interface: %s is NOT of type: TArray<int32>."), *Context, *(ParameterName.ToString()));
		return DataInterface;
	}

	void FLibrary::SetArrayInt32Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<int32>& ArrayData)
	{
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, int32)

		// TODO: FIX
		check(0);
		/*UNiagaraDataInterfaceArrayInt32* ArrayDI = GetArrayInt32Checked(Context, System, OverrideName);

		auto* ArrayProxy			   = static_cast<typename UNiagaraDataInterfaceArrayInt32::FProxyType*>(ArrayDI->GetProxy());
		TConstArrayView<int32> ArrData(ArrayData);
		ArrayProxy->SetArrayData(ArrData);
		SetNiagaraVariantArray<int32, UNiagaraDataInterfaceArrayInt32>(System, OverrideName, ArrayDI);*/
	}

	void FLibrary::SetArrayInt32Checked(const FString& Context, UNiagaraDataInterfaceArrayInt32* ArrayDI, const TArray<int32>& ArrayData, TArray<int32>& Indices)
	{
		CS_IS_PTR_NULL_CHECKED(ArrayDI)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, int32)
		CS_IS_TARRAY_EMPTY_CHECKED(Indices, int32)

		// TODO: FIX
		check(0);
		/*auto* ArrayProxy			   = static_cast<typename UNiagaraDataInterfaceArrayInt32::FProxyType*>(ArrayDI->GetProxy());
		TConstArrayView<int32> ArrData(ArrayData);
		ArrayProxy->SetArrayData(ArrData);*/
	}

	void FLibrary::SetArrayInt32Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<int32>& ArrayData, TArray<int32>& Indices)
	{
		UNiagaraDataInterfaceArrayInt32* ArrayDI = GetArrayInt32Checked(Context, System, OverrideName);

		SetArrayInt32Checked(Context, ArrayDI, ArrayData, Indices);
		// TODO: FIX
		check(0);
		//SetNiagaraVariantArray<int32, UNiagaraDataInterfaceArrayInt32>(System, OverrideName, ArrayDI);
	}

	UNiagaraDataInterfaceArrayFloat* FLibrary::GetArrayFloatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)

		const FNiagaraParameterStore& OverrideParameters = System->GetOverrideParameters();

		FNiagaraVariable Variable(FNiagaraTypeDefinition(UNiagaraDataInterfaceArrayFloat::StaticClass()), OverrideName);

		const int32 Index = OverrideParameters.IndexOf(Variable);

		checkf(Index != INDEX_NONE, TEXT("%s: Failed to find Data Interface of type: TArray<float> with name: %s for System: %s."), *Context, *(OverrideName.ToString()), *(System->GetName()));

		UNiagaraDataInterfaceArrayFloat* DataInterface = Cast<UNiagaraDataInterfaceArrayFloat>(OverrideParameters.GetDataInterface(Index));
	
		checkf(DataInterface, TEXT("%s: Data Interface: %s is NOT of type: TArray<float>."), *Context, *(OverrideName.ToString()));
		return DataInterface;
	}

	UNiagaraDataInterfaceArrayFloat* FLibrary::GetArrayFloatChecked(const FString& Context, UNiagaraParameterCollectionInstance* Collection, const int32& Index)
	{
		CS_IS_PTR_NULL_CHECKED(Collection)
		CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)

		FNiagaraParameterStore& Store = Collection->GetParameterStore();

		const TArray<UNiagaraDataInterface*>& DataInterfaces = Store.GetDataInterfaces();

		checkf(Index < DataInterfaces.Num(), TEXT("%s: No Data Interface at Index: %d."), *Context, Index);

		UNiagaraDataInterfaceArrayFloat* DataInterface = Cast<UNiagaraDataInterfaceArrayFloat>(DataInterfaces[Index]);

		checkf(DataInterface, TEXT("%s: Data Interface at Index: %d is NOT of type: TArray<float>."), *Context, Index);
		return DataInterface;
	}

	/*
	UCsNiagaraDataInterfaceArrayFloatRW* FLibrary::GetArrayFloatRWChecked(const FString& Context, UNiagaraParameterCollectionInstance* Collection, const int32& Index)
	{
		CS_IS_PTR_NULL_CHECKED(Collection)
		CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Index, 0)

		FNiagaraParameterStore& Store = Collection->GetParameterStore();

		const TArray<UNiagaraDataInterface*>& DataInterfaces = Store.GetDataInterfaces();

		checkf(Index < DataInterfaces.Num(), TEXT("%s: No Data Interface at Index: %d."), *Context, Index);

		UCsNiagaraDataInterfaceArrayFloatRW* DataInterface = Cast<UCsNiagaraDataInterfaceArrayFloatRW>(DataInterfaces[Index]);

		checkf(DataInterface, TEXT("%s: Data Interface at Index: %d is NOT of type: TArray<float> (RW)."), *Context, Index);
		return DataInterface;
	}
	*/

	void FLibrary::InitArrayFloatChecked(const FString & Context, UNiagaraDataInterfaceArrayFloat* ArrayDI, const TArray<float>&ArrayData)
	{
		CS_IS_PTR_NULL_CHECKED(ArrayDI)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, float)

		FRWScopeLock WriteLock(ArrayDI->ArrayRWGuard, SLT_Write);

		ArrayDI->FloatData = ArrayData;

		ArrayDI->MarkRenderDataDirty();

		/*
		FNiagaraDataInterfaceProxyArrayImpl* ProxyImpl = static_cast<FNiagaraDataInterfaceProxyArrayImpl*>(ArrayDI->GetProxy());
		TArray<float>* DataPtr						   = const_cast<TArray<float>*>(&ArrayData);
		
		ENQUEUE_RENDER_COMMAND(InitArray)
		(
			[ProxyImpl, DataPtr](FRHICommandListImmediate& RHICmdList)
			{
				ProxyImpl->Buffer.Release();
				ProxyImpl->NumElements = DataPtr->Num();

				const int32 BufferStride	  = FCsNDIArrayImplHelper<float>::GPUGetTypeStride();
				const int32 BufferSize		  = DataPtr->GetTypeSize() * DataPtr->Num();
				const int32 BufferNumElements = BufferSize / BufferStride;
				check((sizeof(float) % BufferStride) == 0);
				check(BufferSize == BufferNumElements * BufferStride);

				ProxyImpl->Buffer.Initialize(BufferStride, BufferNumElements, PF_R32_FLOAT, BUF_AnyDynamic, TEXT("NiagaraArrayFloat"));
				void* GPUMemory = RHICmdList.LockVertexBuffer(ProxyImpl->Buffer.Buffer, 0, BufferSize, RLM_WriteOnly);
				FMemory::Memcpy(GPUMemory, DataPtr->GetData(), BufferSize);
				RHICmdList.UnlockVertexBuffer(ProxyImpl->Buffer.Buffer);

			}
		);
		*/
	}

	/*
	void FLibrary::InitArrayFloatChecked(const FString& Context, UCsNiagaraDataInterfaceArrayFloatRW* ArrayDI, const TArray<float>& ArrayData)
	{
		FCsNiagaraDataInterfaceProxyArrayRWImpl* ProxyImpl = static_cast<FCsNiagaraDataInterfaceProxyArrayRWImpl*>(ArrayDI->GetProxy());
		TArray<float>* DataPtr							   = const_cast<TArray<float>*>(&ArrayData);
		
		ENQUEUE_RENDER_COMMAND(InitArray)
		(
			[ProxyImpl, DataPtr](FRHICommandListImmediate& RHICmdList)
			{
				ProxyImpl->Buffer.Release();
				ProxyImpl->NumElements = DataPtr->Num();

				const int32 BufferStride	  = FCsNDIArrayImplHelper<float>::GPUGetTypeStride();
				const int32 BufferSize		  = DataPtr->GetTypeSize() * DataPtr->Num();
				const int32 BufferNumElements = BufferSize / BufferStride;
				check((sizeof(float) % BufferStride) == 0);
				check(BufferSize == BufferNumElements * BufferStride);

				ProxyImpl->Buffer.Initialize(TEXT("NCsFX::FLibrary::InitArrayFloatChecked"), BufferStride, BufferNumElements, PF_R32_FLOAT, ERHIAccess::UAVCompute, BUF_AnyDynamic, TEXT("NiagaraArrayFloat"));
				void* GPUMemory = RHICmdList.LockBuffer(ProxyImpl->Buffer.Buffer, 0, BufferSize, RLM_WriteOnly);
				FMemory::Memcpy(GPUMemory, DataPtr->GetData(), BufferSize);
				RHICmdList.UnlockBuffer(ProxyImpl->Buffer.Buffer);

			}
		);
	}
	*/

	void FLibrary::SetArrayFloatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<float>& ArrayData)
	{
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, float)

		// TODO: FIX
		check(0);
		/*UNiagaraDataInterfaceArrayFloat* ArrayDI = GetArrayFloatChecked(Context, System, OverrideName);

		auto* ArrayProxy = static_cast<typename UNiagaraDataInterfaceArrayFloat::FProxyType*>(ArrayDI->GetProxy());
		TConstArrayView<float> ArrData(ArrayData);
		ArrayProxy->SetArrayData(ArrData);
		SetNiagaraVariantArray<float, UNiagaraDataInterfaceArrayFloat>(System, OverrideName, ArrayDI);*/
	}

	void FLibrary::SetArrayFloatChecked(const FString& Context, UNiagaraDataInterfaceArrayFloat* ArrayDI, const TArray<float>& ArrayData, TArray<int32>& Indices)
	{
		CS_IS_PTR_NULL_CHECKED(ArrayDI)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, float)
		CS_IS_TARRAY_EMPTY_CHECKED(Indices, int32)
		
		// TODO: FIX
		check(0);
		/*auto* ArrayProxy = static_cast<typename UNiagaraDataInterfaceArrayFloat::FProxyType*>(ArrayDI->GetProxy());
		TConstArrayView<float> ArrData(ArrayData);
		ArrayProxy->SetArrayData(ArrData);*/
	}

	void FLibrary::SetArrayFloatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<float>& ArrayData, TArray<int32>& Indices)
	{
		UNiagaraDataInterfaceArrayFloat* ArrayDI = GetArrayFloatChecked(Context, System, OverrideName);

		SetArrayFloatChecked(Context, ArrayDI, ArrayData, Indices);
		// TODO: FIX
		check(0);
		//SetNiagaraVariantArray<float, UNiagaraDataInterfaceArrayFloat>(System, OverrideName, ArrayDI);
	}

	#define PayloadType NCsFX::NLibrary::NSetArrayFloatChecked::FPayload

	void FLibrary::SetArrayFloatChecked(const FString& Context, UNiagaraDataInterfaceArrayFloat* ArrayDI, PayloadType& Payload)
	{
		CS_IS_PTR_NULL_CHECKED(ArrayDI)
		CS_IS_VALID_CHECKED(Payload);

		Payload.Start();
		
		//FNiagaraDataInterfaceProxyArrayImpl* ProxyImpl = static_cast<FNiagaraDataInterfaceProxyArrayImpl*>(ArrayDI->GetProxy());
		//PayloadType* PayloadPtr						   = &Payload;

		////-TODO: Only create RT resource if we are servicing a GPU system
		//ENQUEUE_RENDER_COMMAND(UpdateArray)
		//(
		//	[ArrayDI, ProxyImpl, PayloadPtr](FRHICommandListImmediate& RHICmdList)
		//	{
		//		ProxyImpl->Buffer.Release();
		//		ProxyImpl->NumElements = PayloadPtr->Values.Num();

		//		const int32 BufferStride	  = FCsNDIArrayImplHelper<float>::GPUGetTypeStride();
		//		const int32 BufferSize		  = PayloadPtr->Values.GetTypeSize() * PayloadPtr->Values.Num();
		//		const int32 BufferNumElements = BufferSize / BufferStride;
		//		check((sizeof(float) % BufferStride) == 0);
		//		check(BufferSize == BufferNumElements * BufferStride);

		//		ProxyImpl->Buffer.Initialize(BufferStride, BufferNumElements, PF_R32_FLOAT, BUF_Static, TEXT("NiagaraArrayFloat"));

		//		float* BufferData = (float*)(RHICmdList.LockVertexBuffer(ProxyImpl->Buffer.Buffer, 0, BufferSize, RLM_WriteOnly));

		//		//const int32& Count			 = PayloadPtr->Count;
		//		//const TArray<int32>& Indices = PayloadPtr->Indices;
		//		//const int32& Stride			 = PayloadPtr->Stride;
		//		//
		//		//int32 DestOffset = 0;
		//		//int32 SrcOffset = 0;

		//		//for (int32 I = 0; I < Count; ++I)
		//		//{
		//		//	const int32& Index = Indices[I];
		//		//	DestOffset		   = Stride * Index;
		//		//	SrcOffset		   = Stride * I;

		//		//	FMemory::Memcpy(ArrayDI->FloatData.GetData() + DestOffset, PayloadPtr->Values.GetData() + SrcOffset, Stride * sizeof(float));
		//		//	FMemory::Memcpy(BufferData + DestOffset, PayloadPtr->Values.GetData() + SrcOffset, Stride * sizeof(float));
		//		//}

		//		//FMemory::Memcpy(ArrayDI->FloatData.GetData(), PayloadPtr->Values.GetData(), BufferSize);
		//		FMemory::Memcpy(BufferData, PayloadPtr->Values.GetData(), BufferSize);

		//		RHICmdList.UnlockVertexBuffer(ProxyImpl->Buffer.Buffer);

		//		PayloadPtr->Clear();
		//		PayloadPtr->Complete();
		//	}
		//);
	}

	/*
	void FLibrary::SetArrayFloatChecked(const FString& Context, UCsNiagaraDataInterfaceArrayFloatRW* ArrayDI, PayloadType& Payload)
	{
		CS_IS_PTR_NULL_CHECKED(ArrayDI)
		CS_IS_VALID_CHECKED(Payload);

		Payload.Start();
		
		FCsNiagaraDataInterfaceProxyArrayRWImpl* ProxyImpl = static_cast<FCsNiagaraDataInterfaceProxyArrayRWImpl*>(ArrayDI->GetProxy());
		PayloadType* PayloadPtr							   = &Payload;

		//-TODO: Only create RT resource if we are servicing a GPU system
		ENQUEUE_RENDER_COMMAND(UpdateArray)
		(
			[ArrayDI, ProxyImpl, PayloadPtr](FRHICommandListImmediate& RHICmdList)
			{
				const int32 BufferSize = PayloadPtr->Values.GetAllocatedSize();

				float* BufferData = (float*)(RHICmdList.LockVertexBuffer(ProxyImpl->Buffer.Buffer, 0, BufferSize, RLM_WriteOnly));

				const int32& Count			 = PayloadPtr->Count;
				const TArray<int32>& Indices = PayloadPtr->Indices;
				const int32& Stride			 = PayloadPtr->Stride;
				
				int32 DestOffset = 0;
				int32 SrcOffset = 0;

				for (int32 I = 0; I < Count; ++I)
				{
					const int32& Index = Indices[I];
					DestOffset		   = Stride * Index;
					SrcOffset		   = Stride * I;

					FMemory::Memcpy(ArrayDI->FloatData.GetData() + DestOffset, PayloadPtr->Values.GetData() + SrcOffset, Stride * sizeof(float));
					FMemory::Memcpy(BufferData + DestOffset, PayloadPtr->Values.GetData() + SrcOffset, Stride * sizeof(float));
				}
				
				//FMemory::Memcpy(ArrayDI->FloatData.GetData(), PayloadPtr->Values.GetData(), BufferSize);
				//FMemory::Memcpy(BufferData, PayloadPtr->Values.GetData(), BufferSize);

				RHICmdList.UnlockVertexBuffer(ProxyImpl->Buffer.Buffer);

				PayloadPtr->Clear();
				PayloadPtr->Complete();
			}
		);
	}
	*/

	#undef PayloadType

	UNiagaraDataInterfaceArrayFloat3* FLibrary::GetArrayVectorChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)

		const FNiagaraParameterStore& OverrideParameters = System->GetOverrideParameters();

		FNiagaraVariable Variable(FNiagaraTypeDefinition(UNiagaraDataInterfaceArrayFloat3::StaticClass()), OverrideName);

		const int32 Index = OverrideParameters.IndexOf(Variable);

		checkf(Index != INDEX_NONE, TEXT("%s: Failed to find Data Interface of type: TArray<FVector3f> with name: %s for System: %s."), *Context, *(OverrideName.ToString()), *(System->GetName()));

		UNiagaraDataInterfaceArrayFloat3* DataInterface = Cast<UNiagaraDataInterfaceArrayFloat3>(OverrideParameters.GetDataInterface(Index));
	
		checkf(DataInterface, TEXT("%s: Data Interface: %s is NOT of type: TArray<FVector3f>."), *Context, *(OverrideName.ToString()));
		return DataInterface;
	}

	UNiagaraDataInterfaceArrayFloat3* FLibrary::GetArrayVectorChecked(const FString& Context, UNiagaraParameterCollectionInstance* Collection, const FName& ParameterName)
	{
		CS_IS_PTR_NULL_CHECKED(Collection)
		CS_IS_NAME_NONE_CHECKED(ParameterName)

		FNiagaraParameterStore& Store = Collection->GetParameterStore();

		FNiagaraVariable Variable(FNiagaraTypeDefinition(UNiagaraDataInterfaceArrayFloat3::StaticClass()), ParameterName);

		UNiagaraDataInterfaceArrayFloat3* DataInterface = Cast<UNiagaraDataInterfaceArrayFloat3>(Store.GetDataInterface(Variable));

		checkf(DataInterface, TEXT("%s: Data Interface: %s is NOT of type: TArray<FVector3f>."), *Context, *(ParameterName.ToString()));
		return DataInterface;
	}

	void FLibrary::SetArrayVectorChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector3f>& ArrayData)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, FVector3f)

		// TODO: FIX
		check(0);
		/*UNiagaraDataInterfaceArrayFloat3* ArrayDI = GetArrayVectorChecked(Context, System, OverrideName);

		auto* ArrayProxy = static_cast<typename UNiagaraDataInterfaceArrayFloat3::FProxyType*>(ArrayDI->GetProxy());
		TConstArrayView<FVector3f> ArrData(ArrayData);
		ArrayProxy->SetArrayData(ArrData);
		SetNiagaraVariantArray<FVector3f, UNiagaraDataInterfaceArrayFloat3>(System, OverrideName, ArrayDI);*/
	}

	void FLibrary::SetArrayVectorChecked(const FString& Context, UNiagaraDataInterfaceArrayFloat3* ArrayDI, const TArray<FVector3f>& ArrayData, TArray<int32>& Indices)
	{
		CS_IS_PTR_NULL_CHECKED(ArrayDI)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, FVector3f)
		CS_IS_TARRAY_EMPTY_CHECKED(Indices, int32)
		
		// TODO: FIX
		check(0);
		/*auto* ArrayProxy = static_cast<typename UNiagaraDataInterfaceArrayFloat3::FProxyType*>(ArrayDI->GetProxy());
		TConstArrayView<FVector3f> ArrData(ArrayData);
		ArrayProxy->SetArrayData(ArrData);*/
	}

	void FLibrary::SetArrayVectorChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector3f>& ArrayData, TArray<int32>& Indices)
	{
		UNiagaraDataInterfaceArrayFloat3* ArrayDI = GetArrayVectorChecked(Context, System, OverrideName);

		SetArrayVectorChecked(Context, ArrayDI, ArrayData, Indices);
		// TODO: FIX
		check(0);
		//SetNiagaraVariantArray<FVector3f, UNiagaraDataInterfaceArrayFloat3>(System, OverrideName, ArrayDI);
	}

	UNiagaraDataInterfaceArrayFloat4* FLibrary::GetArrayVector4Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)

		const FNiagaraParameterStore& OverrideParameters = System->GetOverrideParameters();

		FNiagaraVariable Variable(FNiagaraTypeDefinition(UNiagaraDataInterfaceArrayFloat4::StaticClass()), OverrideName);

		const int32 Index = OverrideParameters.IndexOf(Variable);

		checkf(Index != INDEX_NONE, TEXT("%s: Failed to find Data Interface of type: TArray<FVector4f> with name: %s for System: %s."), *Context, *(OverrideName.ToString()), *(System->GetName()));

		UNiagaraDataInterfaceArrayFloat4* DataInterface = Cast<UNiagaraDataInterfaceArrayFloat4>(OverrideParameters.GetDataInterface(Index));
	
		checkf(DataInterface, TEXT("%s: Data Interface: %s is NOT of type: TArray<FVector4f>."), *Context, *(OverrideName.ToString()));
		return DataInterface;
	}

	UNiagaraDataInterfaceArrayFloat4* FLibrary::GetArrayVector4Checked(const FString& Context, UNiagaraParameterCollectionInstance* Collection, const FName& ParameterName)
	{
		CS_IS_PTR_NULL_CHECKED(Collection)
		CS_IS_NAME_NONE_CHECKED(ParameterName)

		FNiagaraParameterStore& Store = Collection->GetParameterStore();

		FNiagaraVariable Variable(FNiagaraTypeDefinition(UNiagaraDataInterfaceArrayFloat4::StaticClass()), ParameterName);

		UNiagaraDataInterfaceArrayFloat4* DataInterface = Cast<UNiagaraDataInterfaceArrayFloat4>(Store.GetDataInterface(Variable));

		checkf(DataInterface, TEXT("%s: Data Interface: %s is NOT of type: TArray<FVector4f>."), *Context, *(ParameterName.ToString()));
		return DataInterface;
	}

	void FLibrary::SetArrayVector4Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector4f>& ArrayData)
	{
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, FVector4f)

		// TODO: FIX
		check(0);
		/*UNiagaraDataInterfaceArrayFloat4* ArrayDI = GetArrayVector4Checked(Context, System, OverrideName);
	
		auto* ArrayProxy = static_cast<typename UNiagaraDataInterfaceArrayFloat4::FProxyType*>(ArrayDI->GetProxy());
		TConstArrayView<FVector4f> ArrData(ArrayData);
		ArrayProxy->SetArrayData(ArrData);
		SetNiagaraVariantArray<FVector4f, UNiagaraDataInterfaceArrayFloat4>(System, OverrideName, ArrayDI);*/
	}

	void FLibrary::SetArrayVector4Checked(const FString& Context, UNiagaraDataInterfaceArrayFloat4* ArrayDI, const TArray<FVector4f>& ArrayData, TArray<int32>& Indices)
	{
		CS_IS_PTR_NULL_CHECKED(ArrayDI)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, FVector4f)
		CS_IS_TARRAY_EMPTY_CHECKED(Indices, int32)
		
		// TODO: FIX
		check(0);
		/*auto* ArrayProxy = static_cast<typename UNiagaraDataInterfaceArrayFloat4::FProxyType*>(ArrayDI->GetProxy());
		TConstArrayView<FVector4f> ArrData(ArrayData);
		ArrayProxy->SetArrayData(ArrData);*/
	}

	void FLibrary::SetArrayVector4Checked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FVector4f>& ArrayData, TArray<int32>& Indices)
	{
		UNiagaraDataInterfaceArrayFloat4* ArrayDI = GetArrayVector4Checked(Context, System, OverrideName);

		SetArrayVector4Checked(Context, ArrayDI, ArrayData, Indices);
		// TODO: FIX
		check(0);
		//SetNiagaraVariantArray<FVector4f, UNiagaraDataInterfaceArrayFloat4>(System, OverrideName, ArrayDI);
	}

	UNiagaraDataInterfaceArrayQuat* FLibrary::GetArrayQuatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)

		const FNiagaraParameterStore& OverrideParameters = System->GetOverrideParameters();

		FNiagaraVariable Variable(FNiagaraTypeDefinition(UNiagaraDataInterfaceArrayQuat::StaticClass()), OverrideName);

		const int32 Index = OverrideParameters.IndexOf(Variable);

		checkf(Index != INDEX_NONE, TEXT("%s: Failed to find Data Interface of type: TArray<FQuat4f> with name: %s for System: %s."), *Context, *(OverrideName.ToString()), *(System->GetName()));

		UNiagaraDataInterfaceArrayQuat* DataInterface = Cast<UNiagaraDataInterfaceArrayQuat>(OverrideParameters.GetDataInterface(Index));
	
		checkf(DataInterface, TEXT("%s: Data Interface: %s is NOT of type: TArray<FQuat4f>."), *Context, *(OverrideName.ToString()));
		return DataInterface;
	}

	UNiagaraDataInterfaceArrayQuat* FLibrary::GetArrayQuatChecked(const FString& Context, UNiagaraParameterCollectionInstance* Collection, const FName& ParameterName)
	{
		CS_IS_PTR_NULL_CHECKED(Collection)
		CS_IS_NAME_NONE_CHECKED(ParameterName)

		FNiagaraParameterStore& Store = Collection->GetParameterStore();

		FNiagaraVariable Variable(FNiagaraTypeDefinition(UNiagaraDataInterfaceArrayQuat::StaticClass()), ParameterName);

		const int32 Index = Store.IndexOf(Variable);

		checkf(Index != INDEX_NONE, TEXT("%s: Failed to find Data Interface of type: TArray<FQuat4f> with name: %s for System: %s."), *Context, *(ParameterName.ToString()), *(Collection->GetName()));

		UNiagaraDataInterfaceArrayQuat* DataInterface = Cast<UNiagaraDataInterfaceArrayQuat>(Store.GetDataInterface(Index));

		checkf(DataInterface, TEXT("%s: Data Interface: %s is NOT of type: TArray<FQuat4f>."), *Context, *(ParameterName.ToString()));
		return DataInterface;
	}

	void FLibrary::SetArrayQuatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FQuat4f>& ArrayData)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(OverrideName)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, FQuat4f)

		// TODO: FIX
		check(0);
		/*UNiagaraDataInterfaceArrayQuat* ArrayDI = GetArrayQuatChecked(Context, System, OverrideName);

		auto* ArrayProxy = static_cast<typename UNiagaraDataInterfaceArrayQuat::FProxyType*>(ArrayDI->GetProxy());
		TConstArrayView<FQuat4f> ArrData(ArrayData);
		ArrayProxy->SetArrayData(ArrData);
		SetNiagaraVariantArray<FQuat4f, UNiagaraDataInterfaceArrayQuat>(System, OverrideName, ArrayDI);*/
	}

	void FLibrary::SetArrayQuatChecked(const FString& Context, UNiagaraDataInterfaceArrayQuat* ArrayDI, const TArray<FQuat4f>& ArrayData, TArray<int32>& Indices)
	{
		CS_IS_PTR_NULL_CHECKED(ArrayDI)
		CS_IS_TARRAY_EMPTY_CHECKED(ArrayData, FQuat4f)
		CS_IS_TARRAY_EMPTY_CHECKED(Indices, int32)

		// TODO: FIX
		check(0);
		/*auto* ArrayProxy = static_cast<typename UNiagaraDataInterfaceArrayQuat::FProxyType*>(ArrayDI->GetProxy());
		TConstArrayView<FQuat4f> ArrData(ArrayData);
		ArrayProxy->SetArrayData(ArrData);*/
	}

	void FLibrary::SetArrayQuatChecked(const FString& Context, UNiagaraComponent* System, const FName& OverrideName, const TArray<FQuat4f>& ArrayData, TArray<int32>& Indices)
	{
		UNiagaraDataInterfaceArrayQuat* ArrayDI = GetArrayQuatChecked(Context, System, OverrideName);

		SetArrayQuatChecked(Context, ArrayDI, ArrayData, Indices);
		// TODO: FIX
		check(0);
		//SetNiagaraVariantArray<FQuat4f, UNiagaraDataInterfaceArrayQuat>(System, OverrideName, ArrayDI);
	}

	#pragma endregion Parameter

	// Variable
	#pragma region

	FNiagaraVariable* FLibrary::GetExposedVariableChecked(const FString& Context, UNiagaraSystem* System, const FName& Name)
	{
		CS_IS_PTR_NULL_CHECKED(System)
		CS_IS_NAME_NONE_CHECKED(Name)

		FNiagaraUserRedirectionParameterStore& Store = System->GetExposedParameters();

		static TArray<FNiagaraVariable> Parameters;
		Parameters.Reset(Parameters.Max());

		Store.GetParameters(Parameters);

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

	FNiagaraVariable* FLibrary::GetSafeExposedVariable(const FString& Context, UNiagaraSystem* System, const FName& Name, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
	{
		CS_IS_PTR_NULL_RET_NULL(System)
		CS_IS_NAME_NONE_RET_NULL(Name)

		FNiagaraUserRedirectionParameterStore& Store = System->GetExposedParameters();

		static TArray<FNiagaraVariable> Parameters;
		Parameters.Reset(Parameters.Max());

		Store.GetParameters(Parameters);

		for (FNiagaraVariable& Var : Parameters)
		{
			if (Name == Var.GetName())
			{
				return &Var;
			}
		}

		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Parameter with Name: %s on System: %s."), *Context, *(Name.ToString()), *(System->GetName())));
		return nullptr;
	}

	bool FLibrary::SafeIsExposedVariableInt(const FString& Context, UNiagaraSystem* System, const FName& Name, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
	{
		if (FNiagaraVariable* Variable = GetSafeExposedVariable(Context, System, Name, Log))
		{
			return Variable->GetType() == FNiagaraTypeDefinition::GetIntDef();
		}
		return false;
	}

	bool FLibrary::SetSafeExposedVariableInt(const FString& Context, UNiagaraSystem* System, const FName& Name, const int32& Value, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
	{
		CS_IS_PTR_NULL(System)
		CS_IS_NAME_NONE(Name)

		FNiagaraUserRedirectionParameterStore& Store = System->GetExposedParameters();

		static TArray<FNiagaraVariable> Parameters;
		Parameters.Reset(Parameters.Max());

		Store.GetParameters(Parameters);

		for (FNiagaraVariable& Var : Parameters)
		{
			if (Name == Var.GetName() &&
				Var.GetType() == FNiagaraTypeDefinition::GetIntDef())
			{
				Store.SetParameterValue(Value, Var);
				return true;
			}
		}
		return false;
	}

	#if WITH_EDITOR
	bool FLibrary::SafeExposedParameters_PostGenericEditChange(const FString& Context, UNiagaraSystem* System, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
	{
		CS_IS_PENDING_KILL(System)

		FNiagaraUserRedirectionParameterStore& Store = System->GetExposedParameters();

		Store.PostGenericEditChange();
		return true;
	}
	#endif // #if WITH_EDITOR

	#pragma endregion Variable

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
	
		typedef NCsFX::NSpawn::NParams::FFrequency FrequencyParamsType;

		const FrequencyParamsType& FrequencyParams = Params->Get()->FrequencyParams;
		const float TotalTime = FrequencyParams.CalculateTotalTime();

		static const int32 TOTAL_TIME = 0;
		Payload->SetValue_Float(TOTAL_TIME, TotalTime);

		return Scheduler->Start(Payload);
	}

	FCsRoutineHandle FLibrary::SafeSpawn(const FString& Context, UObject* WorldContext, ParamsResourceType* Params, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
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

	FCsRoutineHandle FLibrary::Spawn_GameState_OnceWithDelayChecked(const FString& Context, UObject* WorldContext, const FCsFX& FX, const float& Delay)
	{
		CS_IS_FLOAT_GREATER_THAN_CHECKED(Delay, 0.0f)

		ParamsResourceType* ParmsContainer = Get().AllocateSpawnParams();
		ParamsType* Parms				   = ParmsContainer->Get();

		Parms->FX    = FX;
		Parms->Delay = Delay;
		Parms->Group = NCsUpdateGroup::GameState;

		return SpawnChecked(Context, WorldContext, ParmsContainer);
	}

	FCsRoutineHandle FLibrary::SafeSpawn_GameState_OnceWithDelay(const FString& Context, UObject* WorldContext, const FCsFX& FX, const float& Delay, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
	{
		CS_IS_FLOAT_GREATER_THAN_RET_VALUE(Delay, 0.0f, FCsRoutineHandle::Invalid)

		ParamsResourceType* ParmsContainer = Get().AllocateSpawnParams();
		ParamsType* Parms				   = ParmsContainer->Get();

		Parms->FX    = FX;
		Parms->Delay = Delay;
		Parms->Group = NCsUpdateGroup::GameState;

		return SafeSpawn(Context, WorldContext, ParmsContainer, Log);
	}

	char FLibrary::Spawn_Internal(FCsRoutine* R)
	{
		using namespace NCsFX::NLibrary::NCached;

		const FString& Context = Str::Spawn_Internal;

		static const int32 RESOURCE				  = 0;
		const ParamsResourceType* ParamsContainer = R->GetValue_Void<ParamsResourceType>(RESOURCE);
		const ParamsType* Params				  = ParamsContainer->Get();

		typedef NCsFX::NSpawn::NParams::FFrequency FrequencyParamsType;
		typedef NCsFX::NSpawn::EFrequency FrequencyType;

		const FrequencyParamsType& FrequencyParams = Params->FrequencyParams;
		const FrequencyType& FreqType			   = FrequencyParams.GetType();

		static const int32 CAN_SPAWN = 0;
		bool& CanSpawn				 = R->GetValue_Flag(CAN_SPAWN);

		static const int32 HAS_SPAWN_INTERVAL = 1;
		bool& HasSpawnInterval				  = R->GetValue_Flag(HAS_SPAWN_INTERVAL);

		static const int32 SPAWN_COUNT = 0;
		int32& SpawnCount			   = R->GetValue_Int(SPAWN_COUNT);

		static const int32 TOTAL_TIME = 0;
		const float& TotalTime		  = R->GetValue_Float(TOTAL_TIME);

		FCsDeltaTime& ElapsedTime = R->GetValue_DeltaTime(CS_FIRST);
		ElapsedTime += R->GetDeltaTime();

		CS_COROUTINE_BEGIN(R)

		if (Params->Delay > 0.0f)
		{
			CS_COROUTINE_WAIT_UNTIL(R, ElapsedTime.Time >= Params->Delay);
		}

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

		CS_COROUTINE_WAIT_UNTIL(R, R->GetElapsedTime().Time >= TotalTime);

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

	bool FLibrary::IsReadyToRunChecked(const FString& Context, const UNiagaraComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)
	
		const UNiagaraSystem* System = Component->GetAsset();

		CS_IS_PENDING_KILL_CHECKED(System);

	#if WITH_EDITOR
		if (System->HasOutstandingCompilationRequests(true))
			return false;
	#endif // #if WITH_EDITOR

		if (!System->IsReadyToRun() || 
			!Component->IsWorldReadyToRun())
		{
			return false;
		}
		// TODO: HACK: This is a bit unintuitive based on the name of function. May need to put this somewhere else.
	#if WITH_EDITOR
		if (!SafeHasSystemInstance(Context, Component, nullptr))
			return false;
	#endif // #if WITH_EDITOR
		return true;
	}

	bool FLibrary::IsCompleteChecked(const FString& Context, ANiagaraActor* Actor)
	{
		CS_IS_PENDING_KILL_CHECKED(Actor)

		UNiagaraComponent* Component = Actor->GetNiagaraComponent();

		return IsCompleteChecked(Context, Component);
	}

	bool FLibrary::IsCompleteChecked(const FString& Context, UNiagaraComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component)

		FNiagaraSystemInstance* SystemInstance = GetSystemInstanceChecked(Context, Component);

	#if WITH_EDITOR
		if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(Component))
		{
			// Do Nothing
		}
		// NOTE: FUTURE: HACK: check to deal with Mobile PIE crashes
		else
		{
			typedef NCsGameInstance::NImpl::FLibrary GameInstanceImplLibrary;

			if (GameInstanceImplLibrary::IsStandaloneMobileFromEditorChecked(Context, Component))
			{
				if (!SystemInstance)
					return true;
			}
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
	
		FNiagaraSystemInstance* SystemInstance = GetSystemInstanceChecked(Context, Component);

	#if WITH_EDITOR
		if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(Component))
		{
			// Do Nothing
		}
		// NOTE: FUTURE: HACK: check to deal with Mobile PIE crashes
		else
		{
			typedef NCsGameInstance::NImpl::FLibrary GameInstanceImplLibrary;

			if (GameInstanceImplLibrary::IsStandaloneMobileFromEditorChecked(Context, Component))
			{
				if (!SystemInstance)
					return true;
			}
		}
	#endif // #if WITH_EDITOR

		checkf(SystemInstance, TEXT("%s: SystemInstance is NULL on FXComponent: %s."), *Context, *(Component->GetName()));

		const ENiagaraExecutionState ExecutionState = SystemInstance->GetActualExecutionState();

		return ExecutionState == ENiagaraExecutionState::Inactive;
	}

	void FLibrary::ResetAllChecked(const FString& Context, UNiagaraComponent* Component)
	{
		CS_IS_PTR_NULL_CHECKED(Component)

		FNiagaraSystemInstance* SystemInstance = GetSystemInstanceChecked(Context, Component);

		checkf(SystemInstance, TEXT("%s: SystemInstance is NULL on FXComponent: %s."), *Context, *(Component->GetName()));

		SystemInstance->Reset(FNiagaraSystemInstance::EResetMode::ReInit);
	}

	#pragma endregion State

	// System
	#pragma region
	
	const FNiagaraSystemInstance* FLibrary::GetSystemInstanceChecked(const FString& Context, const UNiagaraComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component);

		FNiagaraSystemInstanceControllerConstPtr Controller = Component->GetSystemInstanceController();

		check(Controller.Get());
		check(Controller->IsValid());

		const FNiagaraSystemInstance* System = Controller->GetSystemInstance_Unsafe();

		CS_IS_PTR_NULL_CHECKED(System)

		return System;
	}

	FNiagaraSystemInstance* FLibrary::GetSystemInstanceChecked(const FString& Context, UNiagaraComponent* Component)
	{
		CS_IS_PENDING_KILL_CHECKED(Component);

		FNiagaraSystemInstanceControllerPtr Controller = Component->GetSystemInstanceController();

		check(Controller.Get());
		check(Controller->IsValid());

		FNiagaraSystemInstance* System = Controller->GetSystemInstance_Unsafe();

		CS_IS_PTR_NULL_CHECKED(System)

		return System;
	}

	FNiagaraSystemInstance* FLibrary::GetSafeSystemInstance(const FString& Context, UNiagaraComponent* Component, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
	{
		CS_IS_PENDING_KILL_RET_NULL(Component)

		FNiagaraSystemInstanceControllerPtr Controller = Component->GetSystemInstanceController();

		if (!Controller.IsValid() ||
			!Controller->IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: System Instance Controller is NOT Valid for Component: %s."), *Context, *(Component->GetName())));
			return nullptr;
		}

		FNiagaraSystemInstance* System = Controller->GetSystemInstance_Unsafe();

		if (!System)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: System instance is NOT Valid for Component: %s."), *Context, *(Component->GetName())));
			return nullptr;
		}
		return System;
	}

	bool FLibrary::SafeHasSystemInstance(const FString& Context, const UNiagaraComponent* Component, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
	{
		CS_IS_PENDING_KILL(Component)

		FNiagaraSystemInstanceControllerConstPtr Controller = Component->GetSystemInstanceController();

		if (!Controller.IsValid() ||
			!Controller->IsValid())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: System Instance Controller is NOT Valid for Component: %s."), *Context, *(Component->GetName())));
			return false;
		}

		const FNiagaraSystemInstance* System = Controller->GetSystemInstance_Unsafe();

		if (!System)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: System instance is NOT Valid for Component: %s."), *Context, *(Component->GetName())));
			return false;
		}
		return true;
	}

	TSharedPtr<FNiagaraSystemSimulation, ESPMode::ThreadSafe> FLibrary::GetSystemSimulationChecked(const FString& Context, UNiagaraComponent* Component)
	{
		FNiagaraSystemInstance* System = GetSystemInstanceChecked(Context, Component);

		TSharedPtr<FNiagaraSystemSimulation, ESPMode::ThreadSafe> Simulation = System->GetSystemSimulation();

		checkf(Simulation.IsValid(), TEXT("%s: Simulation is NOT Valid."), *Context);
		return Simulation;
	}
	
	TSharedPtr<FNiagaraSystemSimulation, ESPMode::ThreadSafe> FLibrary::GetSafeSystemSimulation(const FString& Context, UNiagaraComponent* Component, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/)
	{
		if (FNiagaraSystemInstance* System = GetSafeSystemInstance(Context, Component, Log))
		{
			TSharedPtr<FNiagaraSystemSimulation, ESPMode::ThreadSafe> Simulation = System->GetSystemSimulation();

			if (Simulation.IsValid())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Simulation is NOT Valid."), *Context));
				return TSharedPtr<FNiagaraSystemSimulation, ESPMode::ThreadSafe>();
			}
			return Simulation;
		}
		return TSharedPtr<FNiagaraSystemSimulation, ESPMode::ThreadSafe>();
	}

	#pragma endregion System
}
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/CsTypes_FX.h"
#include "CsFX.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/FX/CsLibrary_FX.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsFXSettings.h"
// Param
#include "Managers/FX/Params/CsParams_FX.h"
// Engine
#include "Engine/DataTable.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_FX)

// FX
#pragma region

namespace NCsFX
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UCsFXSettings* Settings = GetMutableDefault<UCsFXSettings>())
		{
			EMCsFX::Get().ClearUserDefinedEnums();

			// Enum Settings
			if (Settings->ECsFX_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
			{
				const TArray<FCsSettings_Enum>& Enums = Settings->GetSettingsEnum<FECsFX>();
				const FString& EnumSettingsPath		  = Settings->GetSettingsEnumPath<FECsFX>();

				if (!Enums.IsEmpty())
				{
					for (const FCsSettings_Enum& Enum : Enums)
					{
						const FString& Name = Enum.Name;
						const FString& DisplayName = Enum.DisplayName;

						if (Name.IsEmpty())
						{
							UE_LOG(LogCsFX, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
							return;
						}

						checkf(!EMCsFX::Get().IsValidEnum(Name), TEXT("%s: FX (Name): %s already exists (declared in native)."), *Context, *Name);

						if (!Enum.DisplayName.IsEmpty())
						{
							checkf(!EMCsFX::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: FX (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

							EMCsFX::Get().Create(Name, DisplayName, true);
						}
						else
						{
							EMCsFX::Get().Create(Name, true);
						}
					}
				}
				else
				{
					UE_LOG(LogCsFX, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
				}
			}

			// DataTable
			if (Settings->ECsFX_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::DataTable)
			{
				for (TSoftObjectPtr<UDataTable>& SoftObjectPtr : Settings->FXs)
				{
					// Check DataTable of Projectiles
					TSoftObjectPtr<UDataTable> DT_SoftObject = SoftObjectPtr;

					if (UDataTable* DT = DT_SoftObject.LoadSynchronous())
					{
						const UScriptStruct* RowStruct	  = DT->GetRowStruct();
						const TMap<FName, uint8*>& RowMap = DT->GetRowMap();
						{
							// Set if the Row Struct has the properties Name and DisplayName
	
							FStrProperty* NameProperty		  = CastField<FStrProperty>(RowStruct->FindPropertyByName(FName("Name")));
							NameProperty					  = NameProperty ? NameProperty : CastField<FStrProperty>(RowStruct->CustomFindProperty(FName("Name")));
							FStrProperty* DisplayNameProperty = CastField<FStrProperty>(RowStruct->FindPropertyByName(FName("DisplayName")));
							DisplayNameProperty				  = DisplayNameProperty ? DisplayNameProperty: CastField<FStrProperty>(RowStruct->CustomFindProperty(FName("DisplayName")));

							if (NameProperty &&
								DisplayNameProperty)
							{
								for (const TPair<FName, uint8*>& Pair : RowMap)
								{
									const FName& RowName = Pair.Key;
									const uint8* RowPtr = Pair.Value;

									const FString& Name		   = NameProperty->GetPropertyValue_InContainer(RowPtr);
									const FString& DisplayName = DisplayNameProperty->GetPropertyValue_InContainer(RowPtr);

									checkf(Name.Compare(RowName.ToString(), ESearchCase::IgnoreCase) == 0, TEXT("%s: Row Name != FX Name (%s != %s)."), *Context, *(RowName.ToString()), *Name);

									checkf(!EMCsFX::Get().IsValidEnum(Name), TEXT("%s: FX (Name): %s already exists (declared in native)."), *Context, *Name);

									if (!DisplayName.IsEmpty())
									{
										checkf(!EMCsFX::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: FX (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

										EMCsFX::Get().Create(Name, DisplayName, true);
									}
									else
									{
										EMCsFX::Get().Create(Name, true);
									}
								}
							}
							else
							{
								UE_LOG(LogCsFX, Warning, TEXT("%s: Failed to find properties with name: Name and Display for struct: %s."), *Context, *(RowStruct->GetName()));
							}
						}
					}
					else
					{
						UE_LOG(LogCsFX, Warning, TEXT("%s: Failed to Load DataTable @ %s."), *Context, *(DT_SoftObject.ToSoftObjectPath().ToString()));
					}
				}
			}
		}
	}
}

#pragma endregion FX

// FXPriority
#pragma region

namespace NCsFXPriority
{
	namespace Ref
	{
		typedef EMCsFXPriority EnumMapType;

		CSFX_API CS_ADD_TO_ENUM_MAP(Low);
		CSFX_API CS_ADD_TO_ENUM_MAP(Medium);
		CSFX_API CS_ADD_TO_ENUM_MAP(High);
		CSFX_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXPriority_MAX, "MAX");
	}

	CSFX_API const uint8 MAX = (uint8)Type::ECsFXPriority_MAX;
}

#pragma endregion FXPriority

// FXDeallocateMethod
#pragma region

namespace NCsFXDeallocateMethod
{
	namespace Ref
	{
		typedef EMCsFXDeallocateMethod EnumMapType;

		CSFX_API CS_ADD_TO_ENUM_MAP(LifeTime);
		CSFX_API CS_ADD_TO_ENUM_MAP(Complete);
		CSFX_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXDeallocateMethod_MAX, "MAX");
	}

	CSFX_API const uint8 MAX = (uint8)Type::ECsFXDeallocateMethod_MAX;
}

namespace NCsFX
{
	namespace NDeallocateMethod
	{
		namespace Ref
		{
			typedef EMDeallocateMethod EnumMapType;

			CSFX_API CS_ADD_TO_ENUM_MAP(LifeTime);
			CSFX_API CS_ADD_TO_ENUM_MAP(Complete);
		}
	}
}

#pragma endregion FXDeallocateMethod

// FXAttachPoint
#pragma region

namespace NCsFXAttachPoint
{
	namespace Ref
	{
		typedef EMCsFXAttachPoint EnumMapType;

		CSFX_API CS_ADD_TO_ENUM_MAP(None);
		CSFX_API CS_ADD_TO_ENUM_MAP(Bone);
		CSFX_API CS_ADD_TO_ENUM_MAP(Socket);
		CSFX_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXAttachPoint_MAX, "MAX");
	}

	CSFX_API const uint8 MAX = (uint8)Type::ECsFXAttachPoint_MAX;
}

#pragma endregion FXAttachPoint

// FXOrientationRules
#pragma region

namespace NCsFXOrientationRule
{
	namespace Ref
	{
		typedef EMCsFXOrientationRule EnumMapType;

		CSFX_API CS_ADD_TO_ENUM_MAP(None);
		CSFX_API CS_ADD_TO_ENUM_MAP(Parent);
		CSFX_API CS_ADD_TO_ENUM_MAP(Movement);
		CSFX_API CS_ADD_TO_ENUM_MAP(Custom);
		CSFX_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXOrientationRule_MAX, "MAX");
	}
}

#pragma endregion FXOrientationRules

// FXParameterValue
#pragma region

namespace NCsFXParameterValue
{
	namespace Ref
	{
		typedef EMCsFXParameterValue EnumMapType;

		CSFX_API CS_ADD_TO_ENUM_MAP(Int);
		CSFX_API CS_ADD_TO_ENUM_MAP(Float);
		CSFX_API CS_ADD_TO_ENUM_MAP(Vector);
		CSFX_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXParameterValue_MAX, "MAX");
	}

	CSFX_API const uint8 MAX = (uint8)Type::ECsFXParameterValue_MAX;
}

#pragma endregion FXParameterValue

// FCsFXParameterInt
#pragma region

namespace NCsFXParameterInt
{
	void FImpl::CopyToParams(ThisType* This, ParameterType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, Name);
		CS_THIS_COPY_TO_PROXY(Params, Value);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParameterType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Name);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Value);
	}
}

bool FCsFXParameterInt::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/) const
{
	if (Name == NAME_None)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
		return false;
	}

	const FString NameAsString = Name.ToString();

	if (!NameAsString.StartsWith(TEXT("User.")))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Int Parameter Name."), *Context, *NameAsString));
		return false;
	}
	return true;
}

#pragma endregion FCsFXParameterInt

// FCsFXParameterFloat
#pragma region

namespace NCsFXParameterFloat
{
	void FImpl::CopyToParams(ThisType* This, ParameterType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, Name);
		CS_THIS_COPY_TO_PROXY(Params, Value);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParameterType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Name);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Value);
	}
}

bool FCsFXParameterFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/) const
{
	if (Name == NAME_None)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
		return false;
	}

	const FString NameAsString = Name.ToString();

	if (!NameAsString.StartsWith(TEXT("User.")))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Float Parameter Name."), *Context, *NameAsString));
		return false;
	}
	return true;
}

#pragma endregion FCsFXParameterFloat

// FCsFXParameterVector
#pragma region

namespace NCsFXParameterVector
{
	void FImpl::CopyToParams(ThisType* This, ParameterType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, Name);
		CS_THIS_COPY_TO_PROXY(Params, Value);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParameterType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Name);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Value);
	}
}

bool FCsFXParameterVector::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/) const
{
	if (Name == NAME_None)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Name: None is NOT Valid."), *Context));
		return false;
	}

	const FString NameAsString = Name.ToString();

	if (!NameAsString.StartsWith(TEXT("User.")))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Vector Parameter Name."), *Context, *NameAsString));
		return false;
	}
	return true;
}

#pragma endregion FCsFXParameterVector

// FCsFX_Parameter_Scaled_Int
#pragma region

namespace NCsFX_Parameter_Scaled_Int
{
	void FImpl::CopyToParams(ThisType* This, ParameterType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params->GetParameterPtr(), Name);
		CS_THIS_COPY_TO_PROXY(Params, bValue);
		CS_THIS_COPY_TO_PROXY(Params->GetParameterPtr(), Value);
		CS_THIS_COPY_TO_PROXY(Params, bInverse);
		CS_THIS_COPY_TO_PROXY(Params, Scale);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParameterType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params->GetParameterPtr(), Name);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bValue);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params->GetParameterPtr(), Value);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bInverse);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Scale);
	}
}

bool FCsFX_Parameter_Scaled_Int::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)

	const FString NameAsString = Name.ToString();

	checkf(NameAsString.StartsWith(TEXT("User.")), TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Int Parameter Name."), *Context, *NameAsString);
	return true;
}

bool FCsFX_Parameter_Scaled_Int::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/) const
{
	CS_IS_NAME_NONE(Name)

	const FString NameAsString = Name.ToString();

	if (!NameAsString.StartsWith(TEXT("User.")))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Int Parameter Name."), *Context, *NameAsString));
		return false;
	}
	return true;
}

#pragma endregion FCsFX_Parameter_Scaled_Int

// FCsFX_Parameter_Scaled_Float
#pragma region

namespace NCsFX_Parameter_Scaled_Float
{
	void FImpl::CopyToParams(ThisType* This, ParameterType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params->GetParameterPtr(), Name);
		CS_THIS_COPY_TO_PROXY(Params, bValue);
		CS_THIS_COPY_TO_PROXY(Params->GetParameterPtr(), Value);
		CS_THIS_COPY_TO_PROXY(Params, bInverse);
		CS_THIS_COPY_TO_PROXY(Params, Scale);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParameterType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params->GetParameterPtr(), Name);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bValue);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params->GetParameterPtr(), Value);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bInverse);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Scale);
	}
}

bool FCsFX_Parameter_Scaled_Float::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)

	const FString NameAsString = Name.ToString();

	checkf(NameAsString.StartsWith(TEXT("User.")), TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Float Parameter Name."), *Context, *NameAsString);
	return true;
}

bool FCsFX_Parameter_Scaled_Float::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/) const
{
	CS_IS_NAME_NONE(Name)

	const FString NameAsString = Name.ToString();

	if (!NameAsString.StartsWith(TEXT("User.")))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Float Parameter Name."), *Context, *NameAsString));
		return false;
	}
	return true;
}

#pragma endregion FCsFX_Parameter_Scaled_Float

// FCsFX_Parameter_Scaled_Vector
#pragma region

namespace NCsFX_Parameter_Scaled_Vector
{
	void FImpl::CopyToParams(ThisType* This, ParameterType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params->GetParameterPtr(), Name);
		CS_THIS_COPY_TO_PROXY(Params, bValue);
		CS_THIS_COPY_TO_PROXY(Params->GetParameterPtr(), Value);
		CS_THIS_COPY_TO_PROXY(Params, bInverse);
		CS_THIS_COPY_TO_PROXY(Params, Scale);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParameterType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params->GetParameterPtr(), Name);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bValue);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params->GetParameterPtr(), Value);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bInverse);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Scale);
	}
}

bool FCsFX_Parameter_Scaled_Vector::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)

	const FString NameAsString = Name.ToString();

	checkf(NameAsString.StartsWith(TEXT("User.")), TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Vector Parameter Name."), *Context, *NameAsString);
	return true;
}

bool FCsFX_Parameter_Scaled_Vector::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/) const
{
	CS_IS_NAME_NONE(Name)

	const FString NameAsString = Name.ToString();

	if (!NameAsString.StartsWith(TEXT("User.")))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Vector Parameter Name."), *Context, *NameAsString));
		return false;
	}
	return true;
}

#pragma endregion FCsFX_Parameter_Scaled_Vector

// FCsFX_Parameters_Scaled
#pragma region

bool FCsFX_Parameters_Scaled::IsValidChecked(const FString& Context) const
{
	for (const FCsFX_Parameter_Scaled_Int& Param : Ints)
	{
		CS_IS_VALID_CHECKED(Param);
	}
	for (const FCsFX_Parameter_Scaled_Float& Param : Floats)
	{
		CS_IS_VALID_CHECKED(Param);
	}
	for (const FCsFX_Parameter_Scaled_Vector& Param : Vectors)
	{
		CS_IS_VALID_CHECKED(Param);
	}
	return true;
}

bool FCsFX_Parameters_Scaled::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/) const
{
	for (const FCsFX_Parameter_Scaled_Int& Param : Ints)
	{
		CS_IS_VALID(Param)
	}
	for (const FCsFX_Parameter_Scaled_Float& Param : Floats)
	{
		CS_IS_VALID(Param)
	}
	for (const FCsFX_Parameter_Scaled_Vector& Param : Vectors)
	{
		CS_IS_VALID(Param)
	}
	return true;
}

#pragma endregion FCsFX_Parameters_Scaled

// FXParameterDataInterfaceSkeletalMeshMethod
#pragma region

namespace NCsFXParameterDataInterfaceSkeletalMeshMethod
{
	namespace Ref
	{
		typedef EMCsFXParameterDataInterfaceSkeletalMeshMethod EnumMapType;

		CSFX_API CS_ADD_TO_ENUM_MAP(Explicit);
		CSFX_API CS_ADD_TO_ENUM_MAP(Owner_RootComponent);
		CSFX_API CS_ADD_TO_ENUM_MAP(Parent_RootComponent);
		CSFX_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXParameterDataInterfaceSkeletalMeshMethod_MAX, "MAX");
	}
}

#pragma endregion FXParameterDataInterfaceSkeletalMeshMethod

// FCsFX_Parameters_DataInterface_SkeletalMesh
#pragma region

namespace NFCsFX_Parameters_DataInterface_SkeletalMesh
{
	using MethodType = NCsFX::NParameter::NDataInterface::NSkeletalMesh::EMethod;

	void FImpl::CopyToParams(ThisType* This, ParameterType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, Name);
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Method, MethodType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Component);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParameterType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Name);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Method, MethodType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Component);
	}
}

bool FCsFX_Parameters_DataInterface_SkeletalMesh::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)

	const FString NameAsString = Name.ToString();

	checkf(NameAsString.StartsWith(TEXT("User.")), TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Int Parameter Name."), *Context, *NameAsString);
	return true;
}

bool FCsFX_Parameters_DataInterface_SkeletalMesh::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/) const
{
	CS_IS_NAME_NONE(Name)

	const FString NameAsString = Name.ToString();

	if (!NameAsString.StartsWith(TEXT("User.")))
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Int Parameter Name."), *Context, *NameAsString));
		return false;
	}
	return true;
}

#pragma endregion FCsFX_Parameters_DataInterface_SkeletalMesh

// FCsFX_Parameters_DataInterface
#pragma region

bool FCsFX_Parameters_DataInterface::IsValidChecked(const FString& Context) const
{
	for (const FCsFX_Parameters_DataInterface_SkeletalMesh& Param : SkeletalMeshes)
	{
		CS_IS_VALID_CHECKED(Param);
	}
	return true;
}

bool FCsFX_Parameters_DataInterface::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/) const
{
	for (const FCsFX_Parameters_DataInterface_SkeletalMesh& Param : SkeletalMeshes)
	{
		CS_IS_VALID(Param)
	}
	return true;
}

#pragma endregion FCsFX_Parameters_DataInterface

// FCsFX
#pragma region

const FCsFX FCsFX::Invalid;

bool FCsFX::IsValidChecked(const FString& Context) const
{
	// Check FX is Valid.
	check(GetChecked(Context));
	// Check Type is Valid
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsFX, Type);
	// Check DeallocateMethod is Valid
	CS_IS_ENUM_VALID_CHECKED(EMCsFXDeallocateMethod, DeallocateMethod);
	// Check LifeTime is Valid
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(LifeTime, 0.0f)

	if (DeallocateMethod == ECsFXDeallocateMethod::LifeTime)
	{
		CS_IS_FLOAT_GREATER_THAN_CHECKED(LifeTime, 0.0f)
	}
	// Check DeathTime is Valid
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(DeathTime, 0.0f)

	if (!Transform.Equals(FTransform3f::Identity))
	{
		checkf(TransformRules != 0, TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString()));
	}

	// Character Parameters are Valid.
	typedef NCsFX::NParameter::EValue ParameterValueType;

		// Int
	for (const FCsFXParameterInt& Param : IntParameters)
	{
		check(CsFXLibrary::HasVariableNameChecked(Context, FX_Internal, Param.Name, ParameterValueType::Int));
	}
		// Float
	for (const FCsFXParameterFloat& Param : FloatParameters)
	{
		check(CsFXLibrary::HasVariableNameChecked(Context, FX_Internal, Param.Name, ParameterValueType::Float));
	}
		// Vector
	for (const FCsFXParameterVector& Param : VectorParameters)
	{
		check(CsFXLibrary::HasVariableNameChecked(Context, FX_Internal, Param.Name, ParameterValueType::Vector));
	}

		// Scaled
		
			// Int
	for (const FCsFX_Parameter_Scaled_Int& Param : ScaledParameters.Ints)
	{
		check(CsFXLibrary::HasVariableNameChecked(Context, FX_Internal, Param.Name, ParameterValueType::Int));
	}
			// Float
	for (const FCsFX_Parameter_Scaled_Float& Param : ScaledParameters.Floats)
	{
		check(CsFXLibrary::HasVariableNameChecked(Context, FX_Internal, Param.Name, ParameterValueType::Float));
	}
			// Vector
	for (const FCsFX_Parameter_Scaled_Vector& Param : ScaledParameters.Vectors)
	{
		check(CsFXLibrary::HasVariableNameChecked(Context, FX_Internal, Param.Name, ParameterValueType::Vector));
	}
	CS_IS_VALID_CHECKED(DataInterfaceParameters);
	return true;
}

bool FCsFX::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsFX::FLog::Warning*/) const
{
	// Check FX Path is Valid.
	if (!FX.ToSoftObjectPath().IsValid())
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: FX is NULL."), *Context));
		return false;
	}
	// Check FX is Valid.
	if (!FX_Internal)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: FX has NOT been loaded from Path @ %s."), *Context, *(FX.ToSoftObjectPath().ToString())));
		return false;
	}
	// Check Type is Valid.
	CS_IS_ENUM_STRUCT_VALID(EMCsFX, FECsFX, Type);
	// Check DeallocateMethod is Valid
	CS_IS_ENUM_VALID(EMCsFXDeallocateMethod, ECsFXDeallocateMethod, DeallocateMethod);
	// Check LifeTime is Valid
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(LifeTime, 0.0f)

	if (DeallocateMethod == ECsFXDeallocateMethod::LifeTime)
	{
		CS_IS_FLOAT_GREATER_THAN(LifeTime, 0.0f)
	}
	// Check DeathTime is Valid
	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(DeathTime, 0.0f)

	if (!Transform.Equals(FTransform3f::Identity) &&
		TransformRules == 0)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString())));
		return false;
	}
	// Character Parameters are Valid.
	typedef NCsFX::NParameter::EValue ParameterValueType;

	// Int
	for (const FCsFXParameterInt& Param : IntParameters)
	{
		if (!CsFXLibrary::SafeHasVariableName(Context, FX_Internal, Param.Name, ParameterValueType::Int, Log))
			return false;
	}
	// Float
	for (const FCsFXParameterFloat& Param : FloatParameters)
	{
		if (!CsFXLibrary::SafeHasVariableName(Context, FX_Internal, Param.Name, ParameterValueType::Float, Log))
			return false;
	}
	// Vector
	for (const FCsFXParameterVector& Param : VectorParameters)
	{
		if (!CsFXLibrary::SafeHasVariableName(Context, FX_Internal, Param.Name, ParameterValueType::Vector, Log))
			return false;
	}
	
		// Scaled

			// Int
	for (const FCsFX_Parameter_Scaled_Int& Param : ScaledParameters.Ints)
	{
		if (!CsFXLibrary::SafeHasVariableName(Context, FX_Internal, Param.Name, ParameterValueType::Int, Log))
			return false;
	}
			// Float
	for (const FCsFX_Parameter_Scaled_Float& Param : ScaledParameters.Floats)
	{
		if (!CsFXLibrary::SafeHasVariableName(Context, FX_Internal, Param.Name, ParameterValueType::Float, Log))
			return false;
	}
			// Vector
	for (const FCsFX_Parameter_Scaled_Vector& Param : ScaledParameters.Vectors)
	{
		if (!CsFXLibrary::SafeHasVariableName(Context, FX_Internal, Param.Name, ParameterValueType::Vector, Log))
			return false;
	}
	CS_IS_VALID(DataInterfaceParameters)
	return true;
}

void FCsFX::Reset()
{
	FX = nullptr;
	FX_LoadFlags = 0;
	FX_Internal= nullptr;
	Type = EMCsFX::Get().GetMAX();
	DeallocateMethod = ECsFXDeallocateMethod::Complete;
	LifeTime = 0.0f;
	DeathTime = 0.0f;
	bHideOnQueueDeallocate = false;
	AttachmentTransformRules = FCsAttachmentTransformRules::SnapToTargetNotIncludingScale;
	Bone = NAME_None;
	TransformRules =7; // NCsTransformRules::All
	Transform = FTransform3f::Identity;
	OrientationRules.Reset();
	bApplyTransformScale = false;
	IntParameters.Reset(IntParameters.Max());
	FloatParameters.Reset(FloatParameters.Max());
	VectorParameters.Reset(VectorParameters.Max());
	ScaledParameters.Reset();
	DataInterfaceParameters.Reset();
}

#pragma endregion FCsFX

// FXPayloadChange
#pragma region

namespace NCsFXPayloadChange
{
	namespace Ref
	{
		typedef EMCsFXPayloadChange EnumMapType;

		CSFX_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(FXSystem, "FX System");
		CSFX_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(KeepRelativeTransform, "Keep Relative Transform");
		CSFX_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(KeepWorldTransform, "Keep World Transform");
		CSFX_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(SnapToTargetNotIncludingScale, "Snap to Target not Including Scale");
		CSFX_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(SnapToTargetIncludingScale, "Snap to Target Including Scale");
		CSFX_API CS_ADD_TO_ENUM_FLAG_MAP(Transform);
		CSFX_API CS_ADD_TO_ENUM_FLAG_MAP(Parameter);
	}

	CSFX_API const int32 None = 0;
	CSFX_API const int32 All = 127; // 1 + 2 + 4 + 8 + 16 + 32 + 64
}

#pragma endregion FXPayloadChange
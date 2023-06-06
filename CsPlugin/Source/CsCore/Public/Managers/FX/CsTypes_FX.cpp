// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/CsTypes_FX.h"
#include "CsCore.h"

// Library
#include "Managers/FX/CsLibrary_FX.h"
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsDeveloperSettings.h"
// Param
#include "Managers/FX/Params/CsParams_FX.h"

// FX
#pragma region

namespace NCsFX
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>())
		{
			EMCsFX::Get().ClearUserDefinedEnums();

			// Enum Settings
			if (Settings->ECsFX_PopulateEnumMapMethod == ECsPopulateEnumMapMethod::EnumSettings)
			{
				const TArray<FCsSettings_Enum>& Enums = Settings->GetSettingsEnum<FECsFX>();
				const FString& EnumSettingsPath		  = Settings->GetSettingsEnumPath<FECsFX>();

				if (Enums.Num() > CS_EMPTY)
				{
					for (const FCsSettings_Enum& Enum : Enums)
					{
						const FString& Name = Enum.Name;
						const FString& DisplayName = Enum.DisplayName;

						if (Name.IsEmpty())
						{
							UE_LOG(LogCs, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
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
					UE_LOG(LogCs, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
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
								UE_LOG(LogCs, Warning, TEXT("%s: Failed to find properties with name: Name and Display for struct: %s."), *Context, *(RowStruct->GetName()));
							}
						}
					}
					else
					{
						UE_LOG(LogCs, Warning, TEXT("%s: Failed to Load DataTable @ %s."), *Context, *(DT_SoftObject.ToSoftObjectPath().ToString()));
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

		CSCORE_API CS_ADD_TO_ENUM_MAP(Low);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Medium);
		CSCORE_API CS_ADD_TO_ENUM_MAP(High);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXPriority_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsFXPriority_MAX;
}

#pragma endregion FXPriority

// FXDeallocateMethod
#pragma region

namespace NCsFXDeallocateMethod
{
	namespace Ref
	{
		typedef EMCsFXDeallocateMethod EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(LifeTime);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Complete);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXDeallocateMethod_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsFXDeallocateMethod_MAX;
}

namespace NCsFX
{
	namespace NDeallocateMethod
	{
		namespace Ref
		{
			typedef EMDeallocateMethod EnumMapType;

			CSCORE_API CS_ADD_TO_ENUM_MAP(LifeTime);
			CSCORE_API CS_ADD_TO_ENUM_MAP(Complete);
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

		CSCORE_API CS_ADD_TO_ENUM_MAP(None);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Bone);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Socket);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXAttachPoint_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsFXAttachPoint_MAX;
}

#pragma endregion FXAttachPoint

// FXOrientationRules
#pragma region

namespace NCsFXOrientationRule
{
	namespace Ref
	{
		typedef EMCsFXOrientationRule EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(None);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Parent);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Movement);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Custom);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXOrientationRule_MAX, "MAX");
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

		CSCORE_API CS_ADD_TO_ENUM_MAP(Int);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Float);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Vector);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXParameterValue_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsFXParameterValue_MAX;
}

#pragma endregion FXParameterValue

// FCsFXParameterInt
#pragma region

#define ParameterType NCsFX::NParameter::NInt::FIntType

void FCsFXParameterInt::CopyToParams(ParameterType* Params)
{
	Params->SetName(&Name);
	Params->SetValue(&Value);
}

void FCsFXParameterInt::CopyToParamsAsValue(ParameterType* Params) const
{
	Params->SetName(Name);
	Params->SetValue(Value);
}

#undef ParameterType

bool FCsFXParameterInt::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

#define ParameterType NCsFX::NParameter::NFloat::FFloatType

void FCsFXParameterFloat::CopyToParams(ParameterType* Params)
{
	Params->SetName(&Name);
	Params->SetValue(&Value);
}

void FCsFXParameterFloat::CopyToParamsAsValue(ParameterType* Params) const
{
	Params->SetName(Name);
	Params->SetValue(Value);
}

#undef ParameterType

bool FCsFXParameterFloat::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

#define ParameterType NCsFX::NParameter::NVector::FVectorType

void FCsFXParameterVector::CopyToParams(ParameterType* Params)
{
	Params->SetName(&Name);
	Params->SetValue(&Value);
}

void FCsFXParameterVector::CopyToParamsAsValue(ParameterType* Params) const
{
	Params->SetName(Name);
	Params->SetValue(Value);
}

#undef ParameterType

bool FCsFXParameterVector::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

#define ParameterType NCsFX::NParameter::NScaled::NInt::FIntType

void FCsFX_Parameter_Scaled_Int::CopyToParams(ParameterType* Params)
{
	Params->GetParameterPtr()->SetName(&Name);
	Params->SetbValue(&bValue);
	Params->GetParameterPtr()->SetValue(&Value);
	Params->SetbInverse(&bInverse);
	Params->SetScale(&Scale);
}

void FCsFX_Parameter_Scaled_Int::CopyToParamsAsValue(ParameterType* Params) const
{
	Params->GetParameterPtr()->SetName(Name);
	Params->SetbValue(bValue);
	Params->GetParameterPtr()->SetValue(Value);
	Params->SetbInverse(bInverse);
	Params->SetScale(Scale);
}

#undef ParameterType

bool FCsFX_Parameter_Scaled_Int::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)

	const FString NameAsString = Name.ToString();

	checkf(NameAsString.StartsWith(TEXT("User.")), TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Int Parameter Name."), *Context, *NameAsString);
	return true;
}

bool FCsFX_Parameter_Scaled_Int::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

#define ParameterType NCsFX::NParameter::NScaled::NFloat::FFloatType

void FCsFX_Parameter_Scaled_Float::CopyToParams(ParameterType* Params)
{
	Params->GetParameterPtr()->SetName(&Name);
	Params->SetbValue(&bValue);
	Params->GetParameterPtr()->SetValue(&Value);
	Params->SetbInverse(&bInverse);
	Params->SetScale(&Scale);
}

void FCsFX_Parameter_Scaled_Float::CopyToParamsAsValue(ParameterType* Params) const
{
	Params->GetParameterPtr()->SetName(Name);
	Params->SetbValue(bValue);
	Params->GetParameterPtr()->SetValue(Value);
	Params->SetbInverse(bInverse);
	Params->SetScale(Scale);
}

#undef ParameterType

bool FCsFX_Parameter_Scaled_Float::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)

	const FString NameAsString = Name.ToString();

	checkf(NameAsString.StartsWith(TEXT("User.")), TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Float Parameter Name."), *Context, *NameAsString);
	return true;
}

bool FCsFX_Parameter_Scaled_Float::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

#define ParameterType NCsFX::NParameter::NScaled::NVector::FVectorType

void FCsFX_Parameter_Scaled_Vector::CopyToParams(ParameterType* Params)
{
	Params->GetParameterPtr()->SetName(&Name);
	Params->SetbValue(&bValue);
	Params->GetParameterPtr()->SetValue(&Value);
	Params->SetbInverse(&bInverse);
	Params->SetScale(&Scale);
}

void FCsFX_Parameter_Scaled_Vector::CopyToParamsAsValue(ParameterType* Params) const
{
	Params->GetParameterPtr()->SetName(Name);
	Params->SetbValue(bValue);
	Params->GetParameterPtr()->SetValue(Value);
	Params->SetbInverse(bInverse);
	Params->SetScale(Scale);
}

#undef ParameterType

bool FCsFX_Parameter_Scaled_Vector::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)

	const FString NameAsString = Name.ToString();

	checkf(NameAsString.StartsWith(TEXT("User.")), TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Vector Parameter Name."), *Context, *NameAsString);
	return true;
}

bool FCsFX_Parameter_Scaled_Vector::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

bool FCsFX_Parameters_Scaled::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

		CSCORE_API CS_ADD_TO_ENUM_MAP(Explicit);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Owner_RootComponent);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Parent_RootComponent);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsFXParameterDataInterfaceSkeletalMeshMethod_MAX, "MAX");
	}
}

#pragma endregion FXParameterDataInterfaceSkeletalMeshMethod

// FCsFX_Parameters_DataInterface_SkeletalMesh
#pragma region

#define ParameterType NCsFX::NParameter::NDataInterface::NSkeletalMesh::FSkeletalMeshType

void FCsFX_Parameters_DataInterface_SkeletalMesh::CopyToParams(ParameterType* Params)
{
	Params->SetName(&Name);

	typedef NCsFX::NParameter::NDataInterface::NSkeletalMesh::EMethod MethodType;

	Params->SetMethod((MethodType*)(&Method));
	Params->SetComponent(Component);
}

void FCsFX_Parameters_DataInterface_SkeletalMesh::CopyToParamsAsValue(ParameterType* Params) const
{
	Params->SetName(Name);

	typedef NCsFX::NParameter::NDataInterface::NSkeletalMesh::EMethod MethodType;

	Params->SetMethod((MethodType)Method);
	Params->SetComponent(Component);
}

#undef ParameterType

bool FCsFX_Parameters_DataInterface_SkeletalMesh::IsValidChecked(const FString& Context) const
{
	CS_IS_NAME_NONE_CHECKED(Name)

	const FString NameAsString = Name.ToString();

	checkf(NameAsString.StartsWith(TEXT("User.")), TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Int Parameter Name."), *Context, *NameAsString);
	return true;
}

bool FCsFX_Parameters_DataInterface_SkeletalMesh::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

bool FCsFX_Parameters_DataInterface::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

	if (!Transform.Equals(FTransform::Identity))
	{
		checkf(TransformRules != 0, TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString()));
	}

	// Character Parameters are Valid.
	typedef NCsFX::FLibrary FXLibrary;
	typedef NCsFX::NParameter::EValue ParameterValueType;

		// Int
	for (const FCsFXParameterInt& Param : IntParameters)
	{
		check(FXLibrary::HasVariableNameChecked(Context, FX_Internal, Param.Name, ParameterValueType::Int));
	}
		// Float
	for (const FCsFXParameterFloat& Param : FloatParameters)
	{
		check(FXLibrary::HasVariableNameChecked(Context, FX_Internal, Param.Name, ParameterValueType::Float));
	}
		// Vector
	for (const FCsFXParameterVector& Param : VectorParameters)
	{
		check(FXLibrary::HasVariableNameChecked(Context, FX_Internal, Param.Name, ParameterValueType::Vector));
	}

		// Scaled
		
			// Int
	for (const FCsFX_Parameter_Scaled_Int& Param : ScaledParameters.Ints)
	{
		check(FXLibrary::HasVariableNameChecked(Context, FX_Internal, Param.Name, ParameterValueType::Int));
	}
			// Float
	for (const FCsFX_Parameter_Scaled_Float& Param : ScaledParameters.Floats)
	{
		check(FXLibrary::HasVariableNameChecked(Context, FX_Internal, Param.Name, ParameterValueType::Float));
	}
			// Vector
	for (const FCsFX_Parameter_Scaled_Vector& Param : ScaledParameters.Vectors)
	{
		check(FXLibrary::HasVariableNameChecked(Context, FX_Internal, Param.Name, ParameterValueType::Vector));
	}
	CS_IS_VALID_CHECKED(DataInterfaceParameters);
	return true;
}

bool FCsFX::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
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

	if (!Transform.Equals(FTransform::Identity) &&
		TransformRules == 0)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No TransformRules set for Transform: %s."), *Context, *(Transform.ToString())));
		return false;
	}
	// Character Parameters are Valid.
	typedef NCsFX::FLibrary FXLibrary;
	typedef NCsFX::NParameter::EValue ParameterValueType;

	// Int
	for (const FCsFXParameterInt& Param : IntParameters)
	{
		if (!FXLibrary::SafeHasVariableName(Context, FX_Internal, Param.Name, ParameterValueType::Int, Log))
			return false;
	}
	// Float
	for (const FCsFXParameterFloat& Param : FloatParameters)
	{
		if (!FXLibrary::SafeHasVariableName(Context, FX_Internal, Param.Name, ParameterValueType::Float, Log))
			return false;
	}
	// Vector
	for (const FCsFXParameterVector& Param : VectorParameters)
	{
		if (!FXLibrary::SafeHasVariableName(Context, FX_Internal, Param.Name, ParameterValueType::Vector, Log))
			return false;
	}
	
		// Scaled

			// Int
	for (const FCsFX_Parameter_Scaled_Int& Param : ScaledParameters.Ints)
	{
		if (!FXLibrary::SafeHasVariableName(Context, FX_Internal, Param.Name, ParameterValueType::Int, Log))
			return false;
	}
			// Float
	for (const FCsFX_Parameter_Scaled_Float& Param : ScaledParameters.Floats)
	{
		if (!FXLibrary::SafeHasVariableName(Context, FX_Internal, Param.Name, ParameterValueType::Float, Log))
			return false;
	}
			// Vector
	for (const FCsFX_Parameter_Scaled_Vector& Param : ScaledParameters.Vectors)
	{
		if (!FXLibrary::SafeHasVariableName(Context, FX_Internal, Param.Name, ParameterValueType::Vector, Log))
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
	Transform = FTransform::Identity;
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

		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(FXSystem, "FX System");
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(KeepRelativeTransform, "Keep Relative Transform");
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(KeepWorldTransform, "Keep World Transform");
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(SnapToTargetNotIncludingScale, "Snap to Target not Including Scale");
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP_CUSTOM(SnapToTargetIncludingScale, "Snap to Target Including Scale");
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Transform);
		CSCORE_API CS_ADD_TO_ENUM_FLAG_MAP(Parameter);
	}

	CSCORE_API const int32 None = 0;
	CSCORE_API const int32 All = 127; // 1 + 2 + 4 + 8 + 16 + 32 + 64
}

#pragma endregion FXPayloadChange
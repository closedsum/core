// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Cached.h"
#include "CsTypes_Modifier.h"
#include "Modifier/Types/CsTypes_DamageModifier.h"
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"
// Interface
#include "ICsModifier.h"
#include "CsModifier_Int.h"
#include "CsModifier_Float.h"
#include "CsModifier_Float_Range.h"
#include "CsModifier_Toggle.h"
#include "Modifier/CsDamageModifier.h"
#include "Modifier/Types/CsGetDamageModifierType.h"
#include "Valid/CsIsValid.h"
#include "Modifier/Copy/CsDamageModifier_Copy.h"
#include "Reset/CsReset.h"
// Damage
#include "Modifier/CsAllocated_DamageModifier.h"
// Log
#include "Utility/CsDmgLog.h"

#include "CsDamageModifierImpl.generated.h"

// FCsDamageModifier_Int
#pragma region

struct FCsDamageModifier_Int;

// ModifierType (NCsDamage::NModifier::NInt::FInt)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NModifier, NInt, FInt)

namespace NCsDamageModifier_Int
{
	using ThisType = FCsDamageModifier_Int;
	using ModifierType = NCsDamage::NModifier::NInt::FInt;

	// Separate implementation to allow for clearer use of aliases
	struct CSDMG_API FImpl
	{
	public:

		static void CopyToModifier(ThisType* This, ModifierType* Modifier);
		static void CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier);
	};
}

// ModifierType (NCsDamage::NModifier::NInt::FInt)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NModifier, NInt, FInt)

/**
* Describes how to modify any int properties on a Damage.
*  Damage is an object that implements the interface: ICsDamage.
*/
USTRUCT(BlueprintType)
struct CSDMG_API FCsDamageModifier_Int
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier")
	FECsDamageModifier Type;

	/** The value to apply to the Int property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier", meta = (UIMin = "0", ClampMin = "0"))
	int32 Value;

	/** How Value is applied to the existing Int property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier")
	ECsNumericValueModifierApplication Application;

	/** The set of Damage Datas (by Type) the Modifier applies to.
		If the set is EMPTY, the Modifier applies to all Damage Datas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier")
	TSet<FECsDamageData> WhitelistByDataTypeSet;

	FCsDamageModifier_Int() :
		Type(),
		Value(0),
		Application(ECsNumericValueModifierApplication::Multiply),
		WhitelistByDataTypeSet()
	{
	}

	using ModifierType = NCsDamage::NModifier::NInt::FInt;
	using _Impl = NCsDamageModifier_Int::FImpl;

	FORCEINLINE void CopyToModifier(ModifierType* Modifier)					{ _Impl::CopyToModifier(this, Modifier); }
	FORCEINLINE void CopyToModifierAsValue(ModifierType* Modifier) const	{ _Impl::CopyToModifierAsValue(this, Modifier); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(NCsDamage, NModifier, NInt, Int)

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NInt
		{
			using CopyType = NCsDamage::NModifier::NCopy::ICopy;

			/**
			* Describes how to modify any int properties on a Damage.
			*  Damage is an object that implements the interface: ICsDamage.
			*/
			struct CSDMG_API FInt : public CsModifierType,
									public CsIntModifierType,
									public CsDamageModifierType,
									public ICsGetDamageModifierType,
									public ICsIsValid,
									public CopyType,
									public ICsReset
			{
			public:

				static const FName Name;

			private:

				using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

				CS_USING_CACHED_FUNCTION_NAME_NESTED_3(NCsDamage, NModifier, NInt, Int);

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

				CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
				CS_DECLARE_MEMBER_WITH_PROXY(Value, int32)
				CS_DECLARE_MEMBER_WITH_PROXY(Application, ApplicationType)
				CS_DECLARE_MEMBER_WITH_PROXY(WhitelistByDataTypeSet, TSet<FECsDamageData>)

			public:

				FInt();
				~FInt();

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			// CsIntModifierType (NCsModifier::NInt::IInt)
			#pragma region
			public:

				FORCEINLINE int32 Modify(const int32& InValue) const
				{
					return NCsModifier::NValue::NNumeric::NApplication::Modify(InValue, GetValue(), GetApplication());
				}

			#pragma endregion CsIntModifierType (NCsModifier::NInt::IInt)

			// ICsGetDamageModifierType
			#pragma region
			public:

				FORCEINLINE const FECsDamageModifier& GetDamageModifierType() const { return GetType(); }

			#pragma endregion ICsGetDamageModifierType

			// ICsIsValid
			#pragma region
			public:

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;

			#pragma endregion ICsIsValid

			// CopyType (NCsDamage::NModifier::NCopy::ICopy)
			#pragma region
			public:

				void Copy(const CsDamageModifierType* From);

			#pragma endregion CopyType (NCsDamage::NModifier::NCopy::ICopy)

			// ICsReset
			#pragma region
			public:

				FORCEINLINE void Reset()
				{
					CS_RESET_MEMBER_WITH_PROXY(Type, EMCsDamageModifier::Get().GetMAX())
					CS_RESET_MEMBER_WITH_PROXY(Value, 0)
					CS_RESET_MEMBER_WITH_PROXY(Application, ApplicationType::EApplication_MAX)
					CS_RESET_MEMBER_SET_WITH_PROXY(WhitelistByDataTypeSet)
				}

			#pragma endregion ICsReset

			public:

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Application, ApplicationType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(WhitelistByDataTypeSet, TSet<FECsDamageData>)
			};
		}
	}
}

#pragma endregion FCsDamageModifier_Int

// FCsDamageModifier_Float
#pragma region

struct FCsDamageModifier_Float;

// ModifierType (NCsDamage::NModifier::NFloat::FFloat)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NModifier, NFloat, FFloat)

namespace NCsDamageModifier_Float
{
	using ThisType = FCsDamageModifier_Float;
	using ModifierType = NCsDamage::NModifier::NFloat::FFloat;

	// Separate implementation to allow for clearer use of aliases
	struct CSDMG_API FImpl
	{
	public:

		static void CopyToModifier(ThisType* This, ModifierType* Modifier);
		static void CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier);
	};
}

// ModifierType (NCsDamage::NModifier::NFloat::FFloat)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NModifier, NFloat, FFloat)

/**
* Describes how to modify any float properties on a Damage.
*  Damage is an object that implements the interface: ICsDamage.
*/
USTRUCT(BlueprintType)
struct CSDMG_API FCsDamageModifier_Float
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier")
	FECsDamageModifier Type;

	/** The value to apply to the Float property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Value;

	/** How Value is applied to the existing Float property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier")
	ECsNumericValueModifierApplication Application;

	/** The set of Damage Datas (by Type) the Modifier applies to.
		If the set is EMPTY, the Modifier applies to all Damage Datas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier")
	TSet<FECsDamageData> WhitelistByDataTypeSet;

	FCsDamageModifier_Float() :
		Type(),
		Value(0.0f),
		Application(ECsNumericValueModifierApplication::Multiply),
		WhitelistByDataTypeSet()
	{
	}

	using ModifierType = NCsDamage::NModifier::NFloat::FFloat;
	using _Impl = NCsDamageModifier_Float::FImpl;

	FORCEINLINE void CopyToModifier(ModifierType* Modifier)					{ _Impl::CopyToModifier(this, Modifier); }
	FORCEINLINE void CopyToModifierAsValue(ModifierType* Modifier) const	{ _Impl::CopyToModifierAsValue(this, Modifier); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(NCsDamage, NModifier, NFloat, Float)

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NFloat
		{
			using CopyType = NCsDamage::NModifier::NCopy::ICopy;

			/**
			* Describes how to modify any float properties on a Damage.
			*  Damage is an object that implements the interface: ICsDamage.
			*/
			struct CSDMG_API FFloat : public CsModifierType,
									  public CsFloatModifierType,
									  public CsDamageModifierType,
									  public ICsGetDamageModifierType,
									  public ICsIsValid,
									  public CopyType,
									  public ICsReset
			{
			public:

				static const FName Name;

			private:

				using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

				CS_USING_CACHED_FUNCTION_NAME_NESTED_3(NCsDamage, NModifier, NFloat, Float);

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

				CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
				CS_DECLARE_MEMBER_WITH_PROXY(Value, float)
				CS_DECLARE_MEMBER_WITH_PROXY(Application, ApplicationType)
				CS_DECLARE_MEMBER_WITH_PROXY(WhitelistByDataTypeSet, TSet<FECsDamageData>)

			public:

				FFloat();
				~FFloat();

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			// CsFloatModifierType (NCsModifier::NFloat::IFloat)
			#pragma region
			public:

				FORCEINLINE float Modify(const float& InValue) const
				{
					return NCsModifier::NValue::NNumeric::NApplication::Modify(InValue, GetValue(), GetApplication());
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Application, ApplicationType)

			#pragma endregion CsFloatModifierType (NCsModifier::NFloat::IFloat)

			// ICsGetDamageModifierType
			#pragma region
			public:

				FORCEINLINE const FECsDamageModifier& GetDamageModifierType() const { return GetType(); }

			#pragma endregion ICsGetDamageModifierType

			// ICsIsValid
			#pragma region
			public:

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;

			#pragma endregion ICsIsValid

			// CopyType (NCsDamage::NModifier::NCopy::ICopy)
			#pragma region
			public:

				void Copy(const CsDamageModifierType* From);

			#pragma endregion CopyType (NCsDamage::NModifier::NCopy::ICopy)

			// ICsReset
			#pragma region
			public:

				FORCEINLINE void Reset()
				{
					CS_RESET_MEMBER_WITH_PROXY(Type, EMCsDamageModifier::Get().GetMAX())
					CS_RESET_MEMBER_WITH_PROXY(Value, 0.0)
					CS_RESET_MEMBER_WITH_PROXY(Application, ApplicationType::EApplication_MAX)
					CS_RESET_MEMBER_SET_WITH_PROXY(WhitelistByDataTypeSet)
				}

			#pragma endregion ICsREset

			public:

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(WhitelistByDataTypeSet, TSet<FECsDamageData>)
			};
		}
	}
}

#pragma endregion FCsDamageModifier_Float

// FCsDamageModifier_Float_Range
#pragma region

struct FCsDamageModifier_Float_Range;

// ModifierType (NCsDamage::NModifier::NFloat::NRange::FRange)
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsDamage, NModifier, NFloat, NRange, FRange)

namespace NCsDamageModifier_Float_Range
{
	using ThisType = FCsDamageModifier_Float_Range;
	using ModifierType = NCsDamage::NModifier::NFloat::NRange::FRange;

	// Separate implementation to allow for clearer use of aliases
	struct CSDMG_API FImpl
	{
	public:

		static void CopyToModifier(ThisType* This, ModifierType* Modifier);
		static void CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier);
	};
}

// ModifierType (NCsDamage::NModifier::NFloat::NRange::FRange)
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsDamage, NModifier, NFloat, NRange, FRange)

/**
* Describes how to modify any float properties on a Damage.
*  Damage is an object that implements the interface: ICsDamage.
*/
USTRUCT(BlueprintType)
struct CSDMG_API FCsDamageModifier_Float_Range
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier")
	FECsDamageModifier Type;

	/** The minimum value to apply to the Float property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Min;

	/** How minimum value is applied to the existing Float property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier")
	ECsNumericValueModifierApplication MinApplication;

	/** The maximum value to apply to the Float property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Max;

	/** How minimum value is applied to the existing Float property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier")
	ECsNumericValueModifierApplication MaxApplication;

	/** The set of Damage Datas (by Type) the Modifier applies to.
		If the set is EMPTY, the Modifier applies to all Damage Datas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier")
	TSet<FECsDamageData> WhitelistByDataTypeSet;

	FCsDamageModifier_Float_Range() :
		Type(),
		Min(0.0f),
		MinApplication(ECsNumericValueModifierApplication::Multiply),
		Max(0.0f),
		MaxApplication(ECsNumericValueModifierApplication::Multiply),
		WhitelistByDataTypeSet()
	{
	}

	using ModifierType = NCsDamage::NModifier::NFloat::NRange::FRange;
	using _Impl = NCsDamageModifier_Float_Range::FImpl;

	FORCEINLINE void CopyToModifier(ModifierType* Modifier)					{ _Impl::CopyToModifier(this, Modifier); }
	FORCEINLINE void CopyToModifierAsValue(ModifierType* Modifier) const	{ _Impl::CopyToModifierAsValue(this, Modifier); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_4(NCsDamage, NModifier, NFloat, NRange, Range)

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NFloat
		{
			namespace NRange
			{
				using CopyType = NCsDamage::NModifier::NCopy::ICopy;

				/**
				* Describes how to modify any float properties on a Damage.
				*  Damage is an object that implements the interface: ICsDamage.
				*/
				struct CSDMG_API FRange : public CsModifierType,
										  public CsFloatRangeModifierType,
										  public CsDamageModifierType,
										  public ICsGetDamageModifierType,
										  public ICsIsValid,
										  public CopyType,
										  public ICsReset
				{
				public:

					static const FName Name;

				private:

					using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

					CS_USING_CACHED_FUNCTION_NAME_NESTED_4(NCsDamage, NModifier, NFloat, NRange, Range);
					
				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
					CS_DECLARE_MEMBER_WITH_PROXY(Min, float)
					CS_DECLARE_MEMBER_WITH_PROXY(MinApplication, ApplicationType)
					CS_DECLARE_MEMBER_WITH_PROXY(Max, float)
					CS_DECLARE_MEMBER_WITH_PROXY(MaxApplication, ApplicationType)
					CS_DECLARE_MEMBER_WITH_PROXY(WhitelistByDataTypeSet, TSet<FECsDamageData>)

				public:

					FRange();
					~FRange();

					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				// CsFloatModifierType (NCsModifier::NFloat::IFloat)
				#pragma region
				public:

					FORCEINLINE float ModifyMin(const float& InValue) const
					{
						return NCsModifier::NValue::NNumeric::NApplication::Modify(InValue, GetMin(), GetMinApplication());
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MinApplication, ApplicationType)

					FORCEINLINE float ModifyMax(const float& InValue) const
					{
						return NCsModifier::NValue::NNumeric::NApplication::Modify(InValue, GetMax(), GetMaxApplication());
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(MaxApplication, ApplicationType)

				#pragma endregion CsFloatModifierType (NCsModifier::NFloat::IFloat)

				// ICsGetDamageModifierType
				#pragma region
				public:

					FORCEINLINE const FECsDamageModifier& GetDamageModifierType() const { return GetType(); }

				#pragma endregion ICsGetDamageModifierType

				// ICsIsValid
				#pragma region
				public:

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;

				#pragma endregion ICsIsValid

				// CopyType (NCsDamage::NModifier::NCopy::ICopy)
				#pragma region
				public:

					void Copy(const CsDamageModifierType* From);

				#pragma endregion CopyType (NCsDamage::NModifier::NCopy::ICopy)

				// ICsReset
				#pragma region
				public:

					FORCEINLINE void Reset()
					{
						CS_RESET_MEMBER_WITH_PROXY(Type, EMCsDamageModifier::Get().GetMAX())
						CS_RESET_MEMBER_WITH_PROXY(Min, 0.0)
						CS_RESET_MEMBER_WITH_PROXY(MinApplication, ApplicationType::EApplication_MAX)
						CS_RESET_MEMBER_WITH_PROXY(Max, 0.0)
						CS_RESET_MEMBER_WITH_PROXY(MaxApplication, ApplicationType::EApplication_MAX)
						CS_RESET_MEMBER_SET_WITH_PROXY(WhitelistByDataTypeSet)
					}

				#pragma endregion ICsREset

				public:

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Min, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Max, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(WhitelistByDataTypeSet, TSet<FECsDamageData>)
				};
			}
		}
	}
}

#pragma endregion FCsDamageModifier_Float_Range

// FCsDamageModifier_Toggle
#pragma region

struct FCsDamageModifier_Toggle;

// ModifierType (NCsDamage::NModifier::NToggle::FToggle)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NModifier, NToggle, FToggle)

namespace NCsDamageModifier_Toggle
{
	using ThisType = FCsDamageModifier_Toggle;
	using ModifierType = NCsDamage::NModifier::NToggle::FToggle;

	// Separate implementation to allow for clearer use of aliases
	struct CSDMG_API FImpl
	{
	public:

		static void CopyToModifier(ThisType* This, ModifierType* Modifier);
		static void CopyToModifierAsValue(const ThisType* This, ModifierType* Modifier);
	};
}

// ModifierType (NCsDamage::NModifier::NToggle::FToggle)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NModifier, NToggle, FToggle)

/**
* Describes whether to toggle any properties on a Damage.
*  Damage is an object that implements the interface: ICsDamage.
*/
USTRUCT(BlueprintType)
struct CSDMG_API FCsDamageModifier_Toggle
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier")
	FECsDamageModifier Type;

	/** Whether the property associated with Type is enabled or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier", meta = (UIMin = "0.0", ClampMin = "0.0"))
	bool bEnable;

	/** The set of Damage Datas (by Type) the Modifier applies to.
		If the set is EMPTY, the Modifier applies to all Damage Datas. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg|Modifier")
	TSet<FECsDamageData> WhitelistByDataTypeSet;

	FCsDamageModifier_Toggle() :
		Type(),
		bEnable(false),
		WhitelistByDataTypeSet()
	{
	}

	using ModifierType = NCsDamage::NModifier::NToggle::FToggle;
	using _Impl = NCsDamageModifier_Toggle::FImpl;

	FORCEINLINE void CopyToModifier(ModifierType* Modifier)					{ _Impl::CopyToModifier(this, Modifier); }
	FORCEINLINE void CopyToModifierAsValue(ModifierType* Modifier) const	{ _Impl::CopyToModifierAsValue(this, Modifier); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(NCsDamage, NModifier, NToggle, Toggle)

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NToggle
		{
			using CopyType = NCsDamage::NModifier::NCopy::ICopy;

			/**
			* Describes whether to toggle any properties on a Damage.
			*  Damage is an object that implements the interface: ICsDamage.
			*/
			struct CSDMG_API FToggle : public CsModifierType,
									   public CsToggleModifierType,
									   public CsDamageModifierType,
									   public ICsGetDamageModifierType,
									   public ICsIsValid,
									   public CopyType,
									   public ICsReset
			{
			public:

				static const FName Name;

			private:

				using ApplicationType = NCsModifier::NValue::NNumeric::EApplication;

				CS_USING_CACHED_FUNCTION_NAME_NESTED_3(NCsDamage, NModifier, NToggle, Toggle);

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

				CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
				CS_DECLARE_MEMBER_WITH_PROXY(bEnable, bool)
				CS_DECLARE_MEMBER_WITH_PROXY(WhitelistByDataTypeSet, TSet<FECsDamageData>)

			public:

				FToggle();
				~FToggle();

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			// CsToggleModifierType (NCsModifier::NToggle::IToggle)
			#pragma region
			public:

				FORCEINLINE bool IsEnabled() const { return GetbEnable(); }

			#pragma endregion CsToggleModifierType (NCsModifier::NToggle::IToggle)

			// ICsGetDamageModifierType
			#pragma region
			public:

				FORCEINLINE const FECsDamageModifier& GetDamageModifierType() const { return GetType(); }

			#pragma endregion ICsGetDamageModifierType

			// ICsIsValid
			#pragma region
			public:

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;

			#pragma endregion ICsIsValid

			// CopyType (NCsDamage::NModifier::NCopy::ICopy)
			#pragma region
			public:

				void Copy(const CsDamageModifierType* From);

			#pragma endregion CopyType (NCsDamage::NModifier::NCopy::ICopy)

			// ICsReset
			#pragma region
			public:

				FORCEINLINE void Reset()
				{
					CS_RESET_MEMBER_WITH_PROXY(Type, EMCsDamageModifier::Get().GetMAX())
					CS_RESET_MEMBER_WITH_PROXY(bEnable, false)
					CS_RESET_MEMBER_SET_WITH_PROXY(WhitelistByDataTypeSet)
				}

			#pragma endregion ICsREset

			public:

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bEnable, bool)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(WhitelistByDataTypeSet, TSet<FECsDamageData>)
			};
		}
	}
}

#pragma endregion FCsDamageModifier_Toggle

// FCsDamageModifierInfo
#pragma region

struct FCsDamageModifierInfo;

// InfoType (NCsDamage::NModifier::FInfo)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, FInfo)

namespace NCsDamageModifierInfo
{
	using ThisType = FCsDamageModifierInfo;
	using InfoType = NCsDamage::NModifier::FInfo;

	// Separate implementation to allow for clearer use of aliases
	struct CSDMG_API FImpl
	{
	public:

		static void CopyToInfo(ThisType* This, InfoType* Info);
		static void CopyToInfoAsValue(const ThisType* This, InfoType* Info);
	};
}

// InfoType (NCsDamage::NModifier::FInfo)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, FInfo)

USTRUCT(BlueprintType)
struct CSDMG_API FCsDamageModifierInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Modifier")
	TArray<FCsDamageModifier_Int> Ints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Modifier")
	TArray<FCsDamageModifier_Float> Floats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Modifier")
	TArray<FCsDamageModifier_Float_Range> FloatRanges;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Modifier")
	TArray<FCsDamageModifier_Toggle> Toggles;

	FCsDamageModifierInfo() :
		Ints(),
		Floats(),
		FloatRanges(),
		Toggles()
	{
	}

	using InfoType = NCsDamage::NModifier::FInfo;
	using _Impl = NCsDamageModifierInfo::FImpl;

	FORCEINLINE void CopyToInfo(InfoType* Info)					{ _Impl::CopyToInfo(this, Info); }
	FORCEINLINE void CopyToInfoAsValue(InfoType* Info) const	{ _Impl::CopyToInfoAsValue(this, Info); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

namespace NCsDamage
{
	namespace NModifier
	{
		struct CSDMG_API FInfo
		{
		private:

			using IntModifierType = NCsDamage::NModifier::NInt::FInt;
			using FloatModifierType = NCsDamage::NModifier::NFloat::FFloat;
			using FloatRangeModifierType = NCsDamage::NModifier::NFloat::NRange::FRange;
			using ToggleModifierType = NCsDamage::NModifier::NToggle::FToggle;
			using ModifierType = NCsDamage::NModifier::IModifier;

		public:

			TArray<IntModifierType> Ints;

			TArray<FloatModifierType> Floats;

			TArray<FloatRangeModifierType> FloatRanges;

			TArray<ToggleModifierType> Toggles;

		private:

			TArray<ModifierType*> Modifiers;

		public:

			FInfo() :
				Ints(),
				Floats(),
				FloatRanges(),
				Toggles(),
				Modifiers()
			{
			}

			FORCEINLINE const TArray<ModifierType*>& GetModifiers() const { return Modifiers; }
			FORCEINLINE TArray<ModifierType*>* GetModifiersPtr() { return &Modifiers; }

			FORCEINLINE int32 GetTotalSize() const { return Ints.Num() + Floats.Num() + Toggles.Num(); }

			FORCEINLINE void PopulateModifiers()
			{
				Modifiers.Reset(GetTotalSize());

				for (IntModifierType& Modifier : Ints)
				{
					Modifiers.Add(&Modifier);
				}

				for (FloatModifierType& Modifier : Floats)
				{
					Modifiers.Add(&Modifier);
				}

				for (FloatRangeModifierType& Modifier : FloatRanges)
				{
					Modifiers.Add(&Modifier);
				}

				for (ToggleModifierType& Modifier : Toggles)
				{
					Modifiers.Add(&Modifier);
				}
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
		};
	}
}

#pragma endregion FCsDamageModifierInfo

// FCsDamageModifier_Create_Int
#pragma region

struct FCsDamageModifier_Create_Int;

// CreateModifierType (NCsDamage::NModifier::NCreate::FInt)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NModifier, NCreate, FInt)

namespace NCsDamageModifier_Create_Int
{
	using ThisType = FCsDamageModifier_Create_Int;
	using CreateModifierType = NCsDamage::NModifier::NCreate::FInt;

	// Separate implementation to allow for clearer use of aliases
	struct CSDMG_API FImpl
	{
	public:

		static void CopyToCreateModifier(ThisType* This, CreateModifierType* CreateModifier);
		static void CopyToCreateModifierAsValue(const ThisType* This, CreateModifierType* CreateModifier);
	};
}

// CreateModifierType (NCsDamage::NModifier::NCreate::FInt)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NModifier, NCreate, FInt)

/**
* Describes how to create a modifier for an int properties on a Damage.
*  Damage is an object that implements the interface: ICsDamage.
*/
USTRUCT(BlueprintType)
struct CSDMG_API FCsDamageModifier_Create_Int
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg")
	ECsNumericValueCreateModifier Type;

	/** Used another value determined by Type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg")
	int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg")
	FCsDamageModifier_Int Modifier;

	FCsDamageModifier_Create_Int() :
		Type(),
		Value(0),
		Modifier()
	{
	}

	using CreateModifierType = NCsDamage::NModifier::NCreate::FInt;
	using _Impl = NCsDamageModifier_Create_Int::FImpl;

	FORCEINLINE void CopyToCreateModifier(CreateModifierType* CreateModifier)				{ _Impl::CopyToCreateModifier(this, CreateModifier); }
	FORCEINLINE void CopyToCreateModifierAsValue(CreateModifierType* CreateModifier) const	{ _Impl::CopyToCreateModifierAsValue(this, CreateModifier); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

class UObject;

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NCreate
		{
			struct CSDMG_API FInt
			{
			private:

				using CreateType = NCsModifier::NValue::NNumeric::ECreate;
				using ModifierType = NCsDamage::NModifier::NInt::FInt;
				using AllocatedModifierType = NCsDamage::NModifier::FAllocated;

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Type, CreateType)
				CS_DECLARE_MEMBER_WITH_PROXY(Value, int32)

			public:

				ModifierType Modifier;

				FInt() :
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0),
					Modifier()
				{
					CS_CTOR_SET_MEMBER_PROXY(Type);
					CS_CTOR_SET_MEMBER_PROXY(Value);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, CreateType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, int32)
				FORCEINLINE ModifierType* GetModifierPtr() { return &Modifier; }

				void CreateChecked(const FString& Context, const UObject* WorldContext, const int32& InValue, AllocatedModifierType& OutModifier);

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
			};
		}
	}
}

#pragma endregion FCsDamageModifier_Int

// FCsDamageModifier_Create_Float
#pragma region

struct FCsDamageModifier_Create_Float;

// CreateModifierType (NCsDamage::NModifier::NCreate::FFloat)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NModifier, NCreate, FFloat)

namespace NCsDamageModifier_Create_Float
{
	using ThisType = FCsDamageModifier_Create_Float;
	using CreateModifierType = NCsDamage::NModifier::NCreate::FFloat;

	// Separate implementation to allow for clearer use of aliases
	struct CSDMG_API FImpl
	{
	public:

		static void CopyToCreateModifier(ThisType* This, CreateModifierType* CreateModifier);
		static void CopyToCreateModifierAsValue(const ThisType* This, CreateModifierType* CreateModifier);
	};
}

// CreateModifierType (NCsDamage::NModifier::NCreate::FFloat)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NModifier, NCreate, FFloat)

/**
* Describes how to create a modifier for an float properties on a Damage.
*  Damage is an object that implements the interface: ICsDamage.
*/
USTRUCT(BlueprintType)
struct CSDMG_API FCsDamageModifier_Create_Float
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg")
	ECsNumericValueCreateModifier Type;

	/** Used another value determined by Type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg")
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsDmg")
	FCsDamageModifier_Float Modifier;

	FCsDamageModifier_Create_Float() :
		Type(),
		Value(0.0f),
		Modifier()
	{
	}

	using CreateModifierType = NCsDamage::NModifier::NCreate::FFloat;
	using _Impl = NCsDamageModifier_Create_Float::FImpl;

	FORCEINLINE void CopyToCreateModifier(CreateModifierType* CreateModifier)				{ _Impl::CopyToCreateModifier(this, CreateModifier); }
	FORCEINLINE void CopyToCreateModifierAsValue(CreateModifierType* CreateModifier) const	{ _Impl::CopyToCreateModifierAsValue(this, CreateModifier); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

class UObject;

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NCreate
		{
			struct CSDMG_API FFloat
			{
			private:

				using CreateType = NCsModifier::NValue::NNumeric::ECreate;
				using ModifierType = NCsDamage::NModifier::NFloat::FFloat;
				using AllocatedModifierType = NCsDamage::NModifier::FAllocated;

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Type, CreateType)
				CS_DECLARE_MEMBER_WITH_PROXY(Value, float)

			public:

				ModifierType Modifier;

				FFloat() :
					CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Type),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f),
					Modifier()
				{
					CS_CTOR_SET_MEMBER_PROXY(Type);
					CS_CTOR_SET_MEMBER_PROXY(Value);
				}

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, CreateType)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, float)
				FORCEINLINE ModifierType* GetModifierPtr() { return &Modifier; }
		
				void CreateChecked(const FString& Context, const UObject* WorldContext, const float& InValue, AllocatedModifierType& OutModifier);

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
			};
		}
	}
}

#pragma endregion FCsDamageModifier_Float

// FCsDamageModifier_CreateInfo
#pragma region

struct FCsDamageModifier_CreateInfo;

// InfoType (NCsDamage::NModifier::NCreate::FInfo)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NModifier, NCreate, FInfo)

namespace NCsDamageModifier_CreateInfo
{
	using ThisType = FCsDamageModifier_CreateInfo;
	using InfoType = NCsDamage::NModifier::NCreate::FInfo;

	// Separate implementation to allow for clearer use of aliases
	struct CSDMG_API FImpl
	{
	public:

		static void CopyToInfo(ThisType* This, InfoType* Info);
		static void CopyToInfoAsValue(const ThisType* This, InfoType* Info);
	};
}

// InfoType (NCsDamage::NModifier::NCreate::FInfo)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NModifier, NCreate, FInfo)

USTRUCT(BlueprintType)
struct CSDMG_API FCsDamageModifier_CreateInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Modifier")
	TArray<FCsDamageModifier_Create_Int> Ints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Modifier")
	TArray<FCsDamageModifier_Create_Float> Floats;

	FCsDamageModifier_CreateInfo() :
		Ints(),
		Floats()
	{
	}

	using InfoType = NCsDamage::NModifier::NCreate::FInfo;
	using _Impl = NCsDamageModifier_CreateInfo::FImpl;

	FORCEINLINE void CopyToInfo(InfoType* Info)					{ _Impl::CopyToInfo(this, Info); }
	FORCEINLINE void CopyToInfoAsValue(InfoType* Info) const	{ _Impl::CopyToInfoAsValue(this, Info); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NCreate
		{
			struct CSDMG_API FInfo
			{
			private:

				using CreateIntModifierType = NCsDamage::NModifier::NCreate::FInt;
				using CreateFloatModifierType = NCsDamage::NModifier::NCreate::FFloat;
				using AllocatedModifierType = NCsDamage::NModifier::FAllocated;

			public:

				TArray<CreateIntModifierType> Ints;

				TArray<CreateFloatModifierType> Floats;

			public:

				FInfo() :
					Ints(),
					Floats()
				{
				}

				FORCEINLINE int32 GetTotalSize() const { return Ints.Num() + Floats.Num(); }
	
				void CreateChecked(const FString& Context, const UObject* WorldContext, const TArray<int32>& IntValues, const TArray<float>& FloatValues, TArray<AllocatedModifierType>& OutModifiers);
				void AddChecked(const FString& Context, const UObject* WorldContext, const TArray<int32>& IntValues, const TArray<float>& FloatValues, TArray<AllocatedModifierType>& OutModifiers);

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;

			};
		}
	}
}

#pragma endregion FCsDamageModifier_CreateInfo
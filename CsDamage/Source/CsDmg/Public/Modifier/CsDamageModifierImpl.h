// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Modifier/CsTypes_Modifier.h"
#include "Modifier/Types/CsTypes_DamageModifier.h"
// Interface
#include "Modifier/CsModifier.h"
#include "Modifier/CsModifier_Int.h"
#include "Modifier/CsModifier_Float.h"
#include "Modifier/CsModifier_Float_Range.h"
#include "Modifier/CsModifier_Toggle.h"
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

// NCsDamage::NModifier::FInt
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, FInt)

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

	FCsDamageModifier_Int() :
		Type(),
		Value(0),
		Application(ECsNumericValueModifierApplication::Multiply)
	{
	}

#define ModifierType NCsDamage::NModifier::FInt
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsDamage
{
	namespace NModifier
	{
	#define ModifierType NCsModifier::IModifier
	#define IntModifierType NCsModifier::NInt::IInt
	#define DmgModifierType NCsDamage::NModifier::IModifier
	#define CopyType NCsDamage::NModifier::NCopy::ICopy

		/**
		* Describes how to modify any int properties on a Damage.
		*  Damage is an object that implements the interface: ICsDamage.
		*/
		struct CSDMG_API FInt : public ModifierType,
								public IntModifierType,
								public DmgModifierType,
								public ICsGetDamageModifierType,
								public ICsIsValid,
								public CopyType,
								public ICsReset
		{
		public:

			static const FName Name;

		#define ApplicationType NCsModifier::NValue::NNumeric::EApplication

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

			CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
			CS_DECLARE_MEMBER_WITH_PROXY(Value, int32)
			CS_DECLARE_MEMBER_WITH_PROXY(Application, ApplicationType)

		public:

			FInt();
			~FInt();

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		// IntModifierType (NCsModifier::NInt::IInt)
		#pragma region
		public:

			FORCEINLINE int32 Modify(const int32& InValue) const
			{
				return NCsModifier::NValue::NNumeric::NApplication::Modify(InValue, GetValue(), GetApplication());
			}

		#pragma endregion IntModifierType (NCsModifier::NInt::IInt)

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

			void Copy(const DmgModifierType* From);

		#pragma endregion CopyType (NCsDamage::NModifier::NCopy::ICopy)

		// ICsReset
		#pragma region
		public:

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Type, EMCsDamageModifier::Get().GetMAX())
				CS_RESET_MEMBER_WITH_PROXY(Value, 0)
				CS_RESET_MEMBER_WITH_PROXY(Application, ApplicationType::EApplication_MAX)
			}

		#pragma endregion ICsReset

		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Application, ApplicationType)

		#undef ApplicationType
		};

	#undef ModifierType
	#undef IntModifierType
	#undef DmgModifierType
	#undef CopyType
	}
}

#pragma endregion FCsDamageModifier_Int

// FCsDamageModifier_Float
#pragma region

// NCsDamage::NModifier::FFloat
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, FFloat)

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

	FCsDamageModifier_Float() :
		Type(),
		Value(0.0f),
		Application(ECsNumericValueModifierApplication::Multiply)
	{
	}

#define ModifierType NCsDamage::NModifier::FFloat
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsDamage
{
	namespace NModifier
	{
	#define ModifierType NCsModifier::IModifier
	#define FloatModifierType NCsModifier::NFloat::IFloat
	#define DmgModifierType NCsDamage::NModifier::IModifier
	#define CopyType NCsDamage::NModifier::NCopy::ICopy

		/**
		* Describes how to modify any float properties on a Damage.
		*  Damage is an object that implements the interface: ICsDamage.
		*/
		struct CSDMG_API FFloat : public ModifierType,
								  public FloatModifierType,
								  public DmgModifierType,
								  public ICsGetDamageModifierType,
								  public ICsIsValid,
								  public CopyType,
								  public ICsReset
		{
		public:

			static const FName Name;

		#define ApplicationType NCsModifier::NValue::NNumeric::EApplication

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

			CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
			CS_DECLARE_MEMBER_WITH_PROXY(Value, float)
			CS_DECLARE_MEMBER_WITH_PROXY(Application, ApplicationType)

		public:

			FFloat();
			~FFloat();

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		// FloatModifierType (NCsModifier::NFloat::IFloat)
		#pragma region
		public:

			FORCEINLINE float Modify(const float& InValue) const
			{
				return NCsModifier::NValue::NNumeric::NApplication::Modify(InValue, GetValue(), GetApplication());
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Application, ApplicationType)

		#pragma endregion FloatModifierType (NCsModifier::NFloat::IFloat)

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

			void Copy(const DmgModifierType* From);

		#pragma endregion CopyType (NCsDamage::NModifier::NCopy::ICopy)

		// ICsReset
		#pragma region
		public:

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Type, EMCsDamageModifier::Get().GetMAX())
				CS_RESET_MEMBER_WITH_PROXY(Value, 0.0)
				CS_RESET_MEMBER_WITH_PROXY(Application, ApplicationType::EApplication_MAX)
			}

		#pragma endregion ICsREset

		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, float)

		#undef ApplicationType
		};

	#undef ModifierType
	#undef FloatModifierType
	#undef DmgModifierType
	#undef CopyType
	}
}

#pragma endregion FCsDamageModifier_Float

// FCsDamageModifier_Float_Range
#pragma region

// NCsDamage::NModifier::NFloat::FRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsDamage, NModifier, NFloat, FRange)

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

	FCsDamageModifier_Float_Range() :
		Type(),
		Min(0.0f),
		MinApplication(ECsNumericValueModifierApplication::Multiply),
		Max(0.0f),
		MaxApplication(ECsNumericValueModifierApplication::Multiply)
	{
	}

#define ModifierType NCsDamage::NModifier::NFloat::FRange
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NFloat
		{
		#define ModifierType NCsModifier::IModifier
		#define FloatRangeModifierType NCsModifier::NFloat::NRange::IRange
		#define DmgModifierType NCsDamage::NModifier::IModifier
		#define CopyType NCsDamage::NModifier::NCopy::ICopy

			/**
			* Describes how to modify any float properties on a Damage.
			*  Damage is an object that implements the interface: ICsDamage.
			*/
			struct CSDMG_API FRange : public ModifierType,
									  public FloatRangeModifierType,
									  public DmgModifierType,
									  public ICsGetDamageModifierType,
									  public ICsIsValid,
									  public CopyType,
									  public ICsReset
			{
			public:

				static const FName Name;

			#define ApplicationType NCsModifier::NValue::NNumeric::EApplication

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

				CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
				CS_DECLARE_MEMBER_WITH_PROXY(Min, float)
				CS_DECLARE_MEMBER_WITH_PROXY(MinApplication, ApplicationType)
				CS_DECLARE_MEMBER_WITH_PROXY(Max, float)
				CS_DECLARE_MEMBER_WITH_PROXY(MaxApplication, ApplicationType)

			public:

				FRange();
				~FRange();

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			// FloatModifierType (NCsModifier::NFloat::IFloat)
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

			#pragma endregion FloatModifierType (NCsModifier::NFloat::IFloat)

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

				void Copy(const DmgModifierType* From);

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
				}

			#pragma endregion ICsREset

			public:

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Min, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Max, float)

			#undef ApplicationType
			};

		#undef ModifierType
		#undef FloatRangeModifierType
		#undef DmgModifierType
		#undef CopyType
		}
	}
}

#pragma endregion FCsDamageModifier_Float_Range

// FCsDamageModifier_Toggle
#pragma region

// NCsDamage::NModifier::FToggle
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, FToggle)

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

	FCsDamageModifier_Toggle() :
		Type(),
		bEnable(false)
	{
	}

#define ModifierType NCsDamage::NModifier::FToggle
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsDamage
{
	namespace NModifier
	{
	#define ModifierType NCsModifier::IModifier
	#define ToggleModifierType NCsModifier::NToggle::IToggle
	#define DmgModifierType NCsDamage::NModifier::IModifier
	#define CopyType NCsDamage::NModifier::NCopy::ICopy

		/**
		* Describes whether to toggle any properties on a Damage.
		*  Damage is an object that implements the interface: ICsDamage.
		*/
		struct CSDMG_API FToggle : public ModifierType,
								   public ToggleModifierType,
								   public DmgModifierType,
								   public ICsGetDamageModifierType,
								   public ICsIsValid,
								   public CopyType,
								   public ICsReset
		{
		public:

			static const FName Name;

		#define ApplicationType NCsModifier::NValue::NNumeric::EApplication

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

			CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
			CS_DECLARE_MEMBER_WITH_PROXY(bEnable, bool)

		public:

			FToggle();
			~FToggle();

			FORCEINLINE UObject* _getUObject() const { return nullptr; }

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		// ToggleModifierType (NCsModifier::NToggle::IToggle)
		#pragma region
		public:

			FORCEINLINE bool IsEnabled() const { return GetbEnable(); }

		#pragma endregion ToggleModifierType (NCsModifier::NToggle::IToggle)

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

			void Copy(const DmgModifierType* From);

		#pragma endregion CopyType (NCsDamage::NModifier::NCopy::ICopy)

		// ICsReset
		#pragma region
		public:

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Type, EMCsDamageModifier::Get().GetMAX())
				CS_RESET_MEMBER_WITH_PROXY(bEnable, false)
			}

		#pragma endregion ICsREset

		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsDamageModifier)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bEnable, bool)

		#undef ApplicationType
		};

	#undef ModifierType
	#undef ToggleModifierType
	#undef DmgModifierType
	#undef CopyType
	}
}

#pragma endregion FCsDamageModifier_Toggle

// FCsDamageModifierInfo
#pragma region

// NCsDamage::NModifier::FInfo
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

#define InfoType NCsDamage::NModifier::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;
};

namespace NCsDamage
{
	namespace NModifier
	{
		struct CSDMG_API FInfo
		{
		#define IntModifierType NCsDamage::NModifier::FInt
		#define FloatModifierType NCsDamage::NModifier::FFloat
		#define FloatRangeModifierType NCsDamage::NModifier::NFloat::FRange
		#define ToggleModifierType NCsDamage::NModifier::FToggle
		#define ModifierType NCsDamage::NModifier::IModifier

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

		#undef IntModifierType
		#undef FloatModifierType
		#undef FloatRangeModifierType
		#undef ToggleModifierType
		#undef ModifierType
		};
	}
}

#pragma endregion FCsDamageModifierInfo

// FCsDamageModifier_Create_Int
#pragma region

// NCsDamage::NModifier::NCreate::FInt
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

#define CreateModifierType NCsDamage::NModifier::NCreate::FInt
	void CopyToCreateModifier(CreateModifierType* CreateModifier);
	void CopyToCreateModifierAsValue(CreateModifierType* CreateModifier) const;
#undef CreateModifierType

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
			#define CreateType NCsModifier::NValue::NNumeric::ECreate
			#define ModifierType NCsDamage::NModifier::FInt

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

			#define AllocatedModifierType NCsDamage::NModifier::FAllocated
				void CreateChecked(const FString& Context, const UObject* WorldContext, const int32& InValue, AllocatedModifierType& OutModifier);
			#undef AllocatedModifierType

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;

			#undef CreateType
			#undef ModifierType
			};
		}
	}
}

#pragma endregion FCsDamageModifier_Int

// FCsDamageModifier_Create_Float
#pragma region

// NCsDamage::NModifier::NCreate::FFloat
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

#define CreateModifierType NCsDamage::NModifier::NCreate::FFloat
	void CopyToCreateModifier(CreateModifierType* CreateModifier);
	void CopyToCreateModifierAsValue(CreateModifierType* CreateModifier) const;
#undef CreateModifierType

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
			#define CreateType NCsModifier::NValue::NNumeric::ECreate
			#define ModifierType NCsDamage::NModifier::FFloat

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

			#define AllocatedModifierType NCsDamage::NModifier::FAllocated
				void CreateChecked(const FString& Context, const UObject* WorldContext, const float& InValue, AllocatedModifierType& OutModifier);
			#undef AllocatedModifierType

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;

			#undef CreateType
			#undef ModifierType
			};
		}
	}
}

#pragma endregion FCsDamageModifier_Float

// FCsDamageModifier_CreateInfo
#pragma region

// NCsDamage::NModifier::NCreate::FInfo
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

#define InfoType NCsDamage::NModifier::NCreate::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

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
			#define CreateIntModifierType NCsDamage::NModifier::NCreate::FInt
			#define CreateFloatModifierType NCsDamage::NModifier::NCreate::FFloat

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

			#define AllocatedModifierType NCsDamage::NModifier::FAllocated
				void CreateChecked(const FString& Context, const UObject* WorldContext, const TArray<int32>& IntValues, const TArray<float>& FloatValues, TArray<AllocatedModifierType>& OutModifiers);
				void AddChecked(const FString& Context, const UObject* WorldContext, const TArray<int32>& IntValues, const TArray<float>& FloatValues, TArray<AllocatedModifierType>& OutModifiers);
			#undef AllocatedModifierType

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) const;

			#undef CreateIntModifierType
			#undef CreateFloatModifierType
			};
		}
	}
}

#pragma endregion FCsDamageModifier_CreateInfo
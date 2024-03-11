// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsTypes_Modifier.h"
#include "Modifier/Types/CsTypes_SpawnerModifier.h"
// Interface
#include "ICsModifier.h"
#include "CsModifier_Int.h"
#include "CsModifier_Float.h"
#include "CsModifier_Toggle.h"
#include "Modifier/CsSpawnerModifier.h"
#include "Modifier/Types/CsGetSpawnerModifierType.h"
#include "Valid/CsIsValid.h"
#include "Modifier/Copy/CsSpawnerModifier_Copy.h"
#include "Reset/CsReset.h"
// Log
#include "Utility/CsLog.h"

#include "CsSpawnerModifierImpl.generated.h"

// FCsSpawnerModifier_Int
#pragma region

// NCsSpawner::NModifier::FInt
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NModifier, FInt)

/**
* Describes how to modify any int properties on a Spawner.
*  Spawner is an object that implements the interface: ICsSpawner.
*/
USTRUCT(BlueprintType)
struct CSSPAWNER_API FCsSpawnerModifier_Int
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsSpawnerModifier Type;

	/** The value to apply to the Int property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0", ClampMin = "0"))
	int32 Value;

	/** How Value is applied to the existing Int property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsNumericValueModifierApplication Application;

	FCsSpawnerModifier_Int() :
		Type(),
		Value(0),
		Application(ECsNumericValueModifierApplication::Multiply)
	{
	}

#define ModifierType NCsSpawner::NModifier::FInt
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsSpawner
{
	namespace NModifier
	{
	#define ModifierType NCsModifier::IModifier
	#define IntModifierType NCsModifier::NInt::IInt
	#define SpawnerModifierType NCsSpawner::NModifier::IModifier
	#define CopyType NCsSpawner::NModifier::NCopy::ICopy

		struct CSSPAWNER_API FInt : public ModifierType,
								    public IntModifierType,
									public SpawnerModifierType,
									public ICsGetSpawnerModifierType,
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

			CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsSpawnerModifier)
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

		// ICsGetSpawnerModifierType
		#pragma region
		public:

			FORCEINLINE const FECsSpawnerModifier& GetSpawnerModifierType() const { return GetType(); }

		#pragma endregion ICsGetSpawnerModifierType

		// ICsIsValid
		#pragma region
		public:

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

		#pragma endregion ICsIsValid

		// CopyType (NCsSpawner::NModifier::NCopy::ICopy)
		#pragma region
		public:

			void Copy(const SpawnerModifierType* From);

		#pragma endregion CopyType (NCsSpawner::NModifier::NCopy::ICopy)

		// ICsReset
		#pragma region
		public:

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Type, EMCsSpawnerModifier::Get().GetMAX())
				CS_RESET_MEMBER_WITH_PROXY(Value, 0)
				CS_RESET_MEMBER_WITH_PROXY(Application, ApplicationType::EApplication_MAX)
			}

		#pragma endregion ICsREset

		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsSpawnerModifier)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Application, ApplicationType)

		#undef ApplicationType
		};

	#undef ModifierType
	#undef IntModifierType
	#undef SpawnerModifierType
	#undef CopyType
	}
}

#pragma endregion FCsSpawnerModifier_Float

// FCsSpawnerModifier_Float
#pragma region

// NCsSpawner::NModifier::FFloat
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NModifier, FFloat)

/**
* Describes how to modify any float properties on a Spawner.
*  Spawner is an object that implements the interface: ICsSpawner.
*/
USTRUCT(BlueprintType)
struct CSSPAWNER_API FCsSpawnerModifier_Float
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsSpawnerModifier Type;

	/** The value to apply to the Float property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Value;

	/** How Value is applied to the existing Float property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECsNumericValueModifierApplication Application;

	FCsSpawnerModifier_Float() :
		Type(),
		Value(0.0f),
		Application(ECsNumericValueModifierApplication::Multiply)
	{
	}

#define ModifierType NCsSpawner::NModifier::FFloat
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsSpawner
{
	namespace NModifier
	{
	#define ModifierType NCsModifier::IModifier
	#define FloatModifierType NCsModifier::NFloat::IFloat
	#define SpawnerModifierType NCsSpawner::NModifier::IModifier
	#define CopyType NCsSpawner::NModifier::NCopy::ICopy

		struct CSSPAWNER_API FFloat : public ModifierType,
									  public FloatModifierType,
									  public SpawnerModifierType,
									  public ICsGetSpawnerModifierType,
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

			CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsSpawnerModifier)
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

		// ICsGetSpawnerModifierType
		#pragma region
		public:

			FORCEINLINE const FECsSpawnerModifier& GetSpawnerModifierType() const { return GetType(); }

		#pragma endregion ICsGetSpawnerModifierType

		// ICsIsValid
		#pragma region
		public:

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

		#pragma endregion ICsIsValid

		// CopyType (NCsSpawner::NModifier::NCopy::ICopy)
		#pragma region
		public:

			void Copy(const SpawnerModifierType* From);

		#pragma endregion CopyType (NCsSpawner::NModifier::NCopy::ICopy)

		// ICsReset
		#pragma region
		public:

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Type, EMCsSpawnerModifier::Get().GetMAX())
				CS_RESET_MEMBER_WITH_PROXY(Value, 0.0)
				CS_RESET_MEMBER_WITH_PROXY(Application, ApplicationType::EApplication_MAX)
			}

		#pragma endregion ICsREset

		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsSpawnerModifier)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, float)

		#undef ApplicationType
		};

	#undef ModifierType
	#undef FloatModifierType
	#undef SpawnerModifierType
	#undef CopyType
	}
}

#pragma endregion FCsSpawnerModifier_Float

// FCsSpawnerModifier_Toggle
#pragma region

// NCsSpawner::NModifier::FToggle
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NModifier, FToggle)

/**
* Describes whether to toggle any properties on a Spawner.
*  Spawner is an object that implements the interface: ICsSpawner.
*/
USTRUCT(BlueprintType)
struct CSSPAWNER_API FCsSpawnerModifier_Toggle
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsSpawnerModifier Type;

	/** Whether the property associated with Type is enabled or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = "0.0", ClampMin = "0.0"))
	bool bEnable;

	FCsSpawnerModifier_Toggle() :
		Type(),
		bEnable(false)
	{
	}

#define ModifierType NCsSpawner::NModifier::FToggle
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsSpawner
{
	namespace NModifier
	{
	#define ModifierType NCsModifier::IModifier
	#define ToggleModifierType NCsModifier::NToggle::IToggle
	#define SpawnerModifierType NCsSpawner::NModifier::IModifier
	#define CopyType NCsSpawner::NModifier::NCopy::ICopy

		struct CSSPAWNER_API FToggle : public ModifierType,
									   public ToggleModifierType,
									   public SpawnerModifierType,
									   public ICsGetSpawnerModifierType,
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

			CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsSpawnerModifier)
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

		// ICsGetSpawnerModifierType
		#pragma region
		public:

			FORCEINLINE const FECsSpawnerModifier& GetSpawnerModifierType() const { return GetType(); }

		#pragma endregion ICsGetSpawnerModifierType

		// ICsIsValid
		#pragma region
		public:

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

		#pragma endregion ICsIsValid

		// CopyType (NCsSpawner::NModifier::NCopy::ICopy)
		#pragma region
		public:

			void Copy(const SpawnerModifierType* From);

		#pragma endregion CopyType (NCsSpawner::NModifier::NCopy::ICopy)

		// ICsReset
		#pragma region
		public:

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Type, EMCsSpawnerModifier::Get().GetMAX())
				CS_RESET_MEMBER_WITH_PROXY(bEnable, false)
			}

		#pragma endregion ICsREset

		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsSpawnerModifier)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bEnable, bool)

		#undef ApplicationType
		};

	#undef ModifierType
	#undef ToggleModifierType
	#undef SpawnerModifierType
	#undef CopyType
	}
}

#pragma endregion FCsSpawnerModifier_Toggle

// FCsSpawnerModifierInfo
#pragma region

// NCsSpawner::NModifier::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NModifier, FInfo)

USTRUCT(BlueprintType)
struct CSSPAWNER_API FCsSpawnerModifierInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Modifier")
	TArray<FCsSpawnerModifier_Int> Ints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Modifier")
	TArray<FCsSpawnerModifier_Float> Floats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Modifier")
	TArray<FCsSpawnerModifier_Toggle> Toggles;

	FCsSpawnerModifierInfo() :
		Ints(),
		Floats(),
		Toggles()
	{
	}

#define InfoType NCsSpawner::NModifier::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info);
#undef InfoType

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

namespace NCsSpawner
{
	namespace NModifier
	{
		struct CSSPAWNER_API FInfo
		{
		#define IntModifierType NCsSpawner::NModifier::FInt
		#define FloatModifierType NCsSpawner::NModifier::FFloat
		#define ToggleModifierType NCsSpawner::NModifier::FToggle
		#define ModifierType NCsSpawner::NModifier::IModifier

		public:

			TArray<IntModifierType> Ints;

			TArray<FloatModifierType> Floats;

			TArray<ToggleModifierType> Toggles;

		private:

			TArray<ModifierType*> Modifiers;

		public:

			FInfo() :
				Ints(),
				Floats(),
				Toggles(),
				Modifiers()
			{
			}

			FORCEINLINE const TArray<ModifierType*>& GetModifiers() const { return Modifiers; }
			FORCEINLINE TArray<ModifierType*>* GetModifiersPtr() { return &Modifiers; }

			FORCEINLINE void PopulateModifiers()
			{
				Modifiers.Reset(Ints.Num() + Floats.Num() + Toggles.Num());

				for (IntModifierType& Modifier : Ints)
				{
					Modifiers.Add(&Modifier);
				}

				for (FloatModifierType& Modifier : Floats)
				{
					Modifiers.Add(&Modifier);
				}

				for (ToggleModifierType& Modifier : Toggles)
				{
					Modifiers.Add(&Modifier);
				}
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

		#undef IntModifierType
		#undef FloatModifierType
		#undef ToggleModifierType
		#undef ModifierType
		};
	}
}

#pragma endregion FCsSpawnerModifierInfo
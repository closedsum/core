// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Proxy.h"
#include "CsTypes_Modifier.h"
#include "Modifier/Types/CsTypes_ProjectileModifier.h"
// Interface
#include "ICsModifier.h"
#include "CsModifier_Int.h"
#include "CsModifier_Float.h"
#include "CsModifier_Toggle.h"
#include "Modifier/CsProjectileModifier.h"
#include "Modifier/Types/CsGetProjectileModifierType.h"
#include "Valid/CsIsValid.h"
#include "Modifier/Copy/CsProjectileModifier_Copy.h"
#include "Reset/CsReset.h"
// Projectile
#include "Modifier/CsAllocated_ProjectileModifier.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsProjectileModifierImpl.generated.h"

// FCsProjectileModifier_Int
#pragma region

// NCsProjectile::NModifier::FInt
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, FInt)

/**
* Describes how to modify any int properties on a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_Int
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier")
	FECsProjectileModifier Type;

	/** The value to apply to the Int property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier", meta = (UIMin = "0", ClampMin = "0"))
	int32 Value;

	/** How Value is applied to the existing Int property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier")
	ECsNumericValueModifierApplication Application;

	FCsProjectileModifier_Int() :
		Type(),
		Value(0),
		Application(ECsNumericValueModifierApplication::Multiply)
	{
	}

#define ModifierType NCsProjectile::NModifier::FInt
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsProjectile
{
	namespace NModifier
	{
	#define PrjModifierType NCsProjectile::NModifier::IModifier
	#define CopyType NCsProjectile::NModifier::NCopy::ICopy

		/**
		* Describes how to modify any int properties on a Projectile.
		*  Projectile is an object that implements the interface: ICsProjectile.
		*/
		struct CSPRJ_API FInt : public CsModifierType,
								public CsIntModifierType,
								public PrjModifierType,
								public ICsGetProjectileModifierType,
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

			CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsProjectileModifier)
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

		// CsIntModifierType (NCsModifier::NInt::IInt)
		#pragma region
		public:

			FORCEINLINE int32 Modify(const int32& InValue) const
			{
				return NCsModifier::NValue::NNumeric::NApplication::Modify(InValue, GetValue(), GetApplication());
			}

		#pragma endregion CsIntModifierType (NCsModifier::NInt::IInt)

		// ICsGetProjectileModifierType
		#pragma region
		public:

			FORCEINLINE const FECsProjectileModifier& GetProjectileModifierType() const { return GetType(); }

		#pragma endregion ICsGetProjectileModifierType

		// ICsIsValid
		#pragma region
		public:

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

		#pragma endregion ICsIsValid

		// CopyType (NCsProjectile::NModifier::NCopy::ICopy)
		#pragma region
		public:

			void Copy(const PrjModifierType* From);

		#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)

		// ICsReset
		#pragma region
		public:

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Type, EMCsProjectileModifier::Get().GetMAX())
				CS_RESET_MEMBER_WITH_PROXY(Value, 0)
				CS_RESET_MEMBER_WITH_PROXY(Application, ApplicationType::EApplication_MAX)
			}

		#pragma endregion ICsReset

		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsProjectileModifier)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, int32)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Application, ApplicationType)

		#undef ApplicationType
		};

	#undef PrjModifierType
	#undef CopyType
	}
}

#pragma endregion FCsProjectileModifier_Int

// FCsProjectileModifier_Float
#pragma region

// NCsProjectile::NModifier::FFloat
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, FFloat)

/**
* Describes how to modify any float properties on a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_Float
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier")
	FECsProjectileModifier Type;

	/** The value to apply to the Float property. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Value;

	/** How Value is applied to the existing Float property.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier")
	ECsNumericValueModifierApplication Application;

	FCsProjectileModifier_Float() :
		Type(),
		Value(0.0f),
		Application(ECsNumericValueModifierApplication::Multiply)
	{
	}

#define ModifierType NCsProjectile::NModifier::FFloat
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsProjectile
{
	namespace NModifier
	{
	#define PrjModifierType NCsProjectile::NModifier::IModifier
	#define CopyType NCsProjectile::NModifier::NCopy::ICopy

		/**
		* Describes how to modify any float properties on a Projectile.
		*  Projectile is an object that implements the interface: ICsProjectile.
		*/
		struct CSPRJ_API FFloat : public CsModifierType,
								  public CsFloatModifierType,
								  public PrjModifierType,
								  public ICsGetProjectileModifierType,
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

			CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsProjectileModifier)
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

		// CsFloatModifierType (NCsModifier::NFloat::IFloat)
		#pragma region
		public:

			FORCEINLINE float Modify(const float& InValue) const
			{
				return NCsModifier::NValue::NNumeric::NApplication::Modify(InValue, GetValue(), GetApplication());
			}

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Application, ApplicationType)

		#pragma endregion CsFloatModifierType (NCsModifier::NFloat::IFloat)

		// ICsGetProjectileModifierType
		#pragma region
		public:

			FORCEINLINE const FECsProjectileModifier& GetProjectileModifierType() const { return GetType(); }

		#pragma endregion ICsGetProjectileModifierType

		// ICsIsValid
		#pragma region
		public:

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

		#pragma endregion ICsIsValid

		// CopyType (NCsProjectile::NModifier::NCopy::ICopy)
		#pragma region
		public:

			void Copy(const PrjModifierType* From);

		#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)

		// ICsReset
		#pragma region
		public:

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Type, EMCsProjectileModifier::Get().GetMAX())
				CS_RESET_MEMBER_WITH_PROXY(Value, 0.0)
				CS_RESET_MEMBER_WITH_PROXY(Application, ApplicationType::EApplication_MAX)
			}

		#pragma endregion ICsREset

		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsProjectileModifier)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Value, float)

		#undef ApplicationType
		};

	#undef PrjModifierType
	#undef CopyType
	}
}

#pragma endregion FCsProjectileModifier_Float

// FCsProjectileModifier_Toggle
#pragma region

// NCsProjectile::NModifier::FToggle
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, FToggle)

/**
* Describes whether to toggle any properties on a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_Toggle
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier")
	FECsProjectileModifier Type;

	/** Whether the property associated with Type is enabled or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj|Modifier", meta = (UIMin = "0.0", ClampMin = "0.0"))
	bool bEnable;

	FCsProjectileModifier_Toggle() :
		Type(),
		bEnable(false)
	{
	}

#define ModifierType NCsProjectile::NModifier::FToggle
	void CopyToModifier(ModifierType* Modifier);
	void CopyToModifierAsValue(ModifierType* Modifier) const;
#undef ModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

struct FCsInterfaceMap;
class UObject;

namespace NCsProjectile
{
	namespace NModifier
	{
	#define PrjModifierType NCsProjectile::NModifier::IModifier
	#define CopyType NCsProjectile::NModifier::NCopy::ICopy

		/**
		* Describes whether to toggle any properties on a Projectile.
		*  Projectile is an object that implements the interface: ICsProjectile.
		*/
		struct CSPRJ_API FToggle : public CsModifierType,
								   public CsToggleModifierType,
								   public PrjModifierType,
								   public ICsGetProjectileModifierType,
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

			CS_DECLARE_MEMBER_WITH_PROXY(Type, FECsProjectileModifier)
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

		// CsToggleModifierType (NCsModifier::NToggle::IToggle)
		#pragma region
		public:

			FORCEINLINE bool IsEnabled() const { return GetbEnable(); }

		#pragma endregion CsToggleModifierType (NCsModifier::NToggle::IToggle)

		// ICsGetProjectileModifierType
		#pragma region
		public:

			FORCEINLINE const FECsProjectileModifier& GetProjectileModifierType() const { return GetType(); }

		#pragma endregion ICsGetProjectileModifierType

		// ICsIsValid
		#pragma region
		public:

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

		#pragma endregion ICsIsValid

		// CopyType (NCsProjectile::NModifier::NCopy::ICopy)
		#pragma region
		public:

			void Copy(const PrjModifierType* From);

		#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)

		// ICsReset
		#pragma region
		public:

			FORCEINLINE void Reset()
			{
				CS_RESET_MEMBER_WITH_PROXY(Type, EMCsProjectileModifier::Get().GetMAX())
				CS_RESET_MEMBER_WITH_PROXY(bEnable, false)
			}

		#pragma endregion ICsREset

		public:

			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, FECsProjectileModifier)
			CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bEnable, bool)

		#undef ApplicationType
		};

	#undef PrjModifierType
	#undef CopyType
	}
}

#pragma endregion FCsWeaponModifier_Toggle

// FCsProjectileModifierInfo
#pragma region

// NCsProjectile::NModifier::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, FInfo)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifierInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Modifier")
	TArray<FCsProjectileModifier_Int> Ints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Modifier")
	TArray<FCsProjectileModifier_Float> Floats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Modifier")
	TArray<FCsProjectileModifier_Toggle> Toggles;

	FCsProjectileModifierInfo() :
		Ints(),
		Floats(),
		Toggles()
	{
	}

#define InfoType NCsProjectile::NModifier::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NModifier
	{
		struct CSPRJ_API FInfo
		{
		#define IntModifierType NCsProjectile::NModifier::FInt
		#define FloatModifierType NCsProjectile::NModifier::FFloat
		#define ToggleModifierType NCsProjectile::NModifier::FToggle
		#define ModifierType NCsProjectile::NModifier::IModifier

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

				for (ToggleModifierType& Modifier : Toggles)
				{
					Modifiers.Add(&Modifier);
				}
			}

			bool IsValidChecked(const FString& Context) const;
			bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

		#undef IntModifierType
		#undef FloatModifierType
		#undef ToggleModifierType
		#undef ModifierType
		};
	}
}

#pragma endregion FCsProjectileModifierInfo

// FCsProjectileModifier_Create_Int
#pragma region

// NCsProjectile::NModifier::NCreate::FInt
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NCreate, FInt)

/**
* Describes how to create a modifier for an int properties on a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_Create_Int
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	ECsNumericValueCreateModifier Type;

	/** Used another value determined by Type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	FCsProjectileModifier_Int Modifier;

	FCsProjectileModifier_Create_Int() :
		Type(),
		Value(0),
		Modifier()
	{
	}

#define CreateModifierType NCsProjectile::NModifier::NCreate::FInt
	void CopyToCreateModifier(CreateModifierType* CreateModifier);
	void CopyToCreateModifierAsValue(CreateModifierType* CreateModifier) const;
#undef CreateModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

class UObject;

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NCreate
		{
			struct CSPRJ_API FInt
			{
			#define CreateType NCsModifier::NValue::NNumeric::ECreate
			#define ModifierType NCsProjectile::NModifier::FInt

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

			#define AllocatedModifierType NCsProjectile::NModifier::FAllocated
				void CreateChecked(const FString& Context, const UObject* WorldContext, const int32& InValue, AllocatedModifierType& OutModifier);
			#undef AllocatedModifierType

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

			#undef CreateType
			#undef ModifierType
			};
		}
	}
}

#pragma endregion FCsProjectileModifier_Int

// FCsProjectileModifier_Create_Float
#pragma region

// NCsProjectile::NModifier::NCreate::FFloat
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NCreate, FFloat)

/**
* Describes how to create a modifier for an float properties on a Projectile.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_Create_Float
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	ECsNumericValueCreateModifier Type;

	/** Used another value determined by Type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	float Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsPrj")
	FCsProjectileModifier_Float Modifier;

	FCsProjectileModifier_Create_Float() :
		Type(),
		Value(0.0f),
		Modifier()
	{
	}

#define CreateModifierType NCsProjectile::NModifier::NCreate::FFloat
	void CopyToCreateModifier(CreateModifierType* CreateModifier);
	void CopyToCreateModifierAsValue(CreateModifierType* CreateModifier) const;
#undef CreateModifierType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

class UObject;

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NCreate
		{
			struct CSPRJ_API FFloat
			{
			#define CreateType NCsModifier::NValue::NNumeric::ECreate
			#define ModifierType NCsProjectile::NModifier::FFloat

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

			#define AllocatedModifierType NCsProjectile::NModifier::FAllocated
				void CreateChecked(const FString& Context, const UObject* WorldContext, const float& InValue, AllocatedModifierType& OutModifier);
			#undef AllocatedModifierType

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

			#undef CreateType
			#undef ModifierType
			};
		}
	}
}

#pragma endregion FCsProjectileModifier_Float

// FCsProjectileModifier_CreateInfo
#pragma region

// NCsProjectile::NModifier::NCreate::FInfo
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsProjectile, NModifier, NCreate, FInfo)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectileModifier_CreateInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Modifier")
	TArray<FCsProjectileModifier_Create_Int> Ints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|Modifier")
	TArray<FCsProjectileModifier_Create_Float> Floats;

	FCsProjectileModifier_CreateInfo() :
		Ints(),
		Floats()
	{
	}

#define InfoType NCsProjectile::NModifier::NCreate::FInfo
	void CopyToInfo(InfoType* Info);
	void CopyToInfoAsValue(InfoType* Info) const;
#undef InfoType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NCreate
		{
			struct CSPRJ_API FInfo
			{
			#define CreateIntModifierType NCsProjectile::NModifier::NCreate::FInt
			#define CreateFloatModifierType NCsProjectile::NModifier::NCreate::FFloat

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

			#define AllocatedModifierType NCsProjectile::NModifier::FAllocated
				void CreateChecked(const FString& Context, const UObject* WorldContext, const TArray<int32>& IntValues, const TArray<float>& FloatValues, TArray<AllocatedModifierType>& OutModifiers);
				void AddChecked(const FString& Context, const UObject* WorldContext, const TArray<int32>& IntValues, const TArray<float>& FloatValues, TArray<AllocatedModifierType>& OutModifiers);
			#undef AllocatedModifierType

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

			#undef CreateIntModifierType
			#undef CreateFloatModifierType
			};
		}
	}
}

#pragma endregion FCsProjectileModifier_CreateInfo
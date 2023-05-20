// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_StatusEffect.h"
#include "Process/Payload/CsProcessStatusEffectDataPayload.h"
// Log
#include "Utility/CsSeLog.h"

class UObject;
class UCsCoordinator_StatusEffect;

// NCsData::NManager::NHandler::TData
namespace NCsData {
	namespace NManager {
		namespace NHandler {
			template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
			class TData;
		}
	}
}

// NCsStatusEffect::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, IData)
// NCsStatusEffect::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, FInterfaceMap)

// NCsStatusEffect::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsStatusEffect, FResource)
// NCsStatusEffect::IStatusEffect
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsStatusEffect, IStatusEffect)
// NCsStatusEffect::FAllocated
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsStatusEffect, FAllocated)

// NCsStatusEffect::NEvent::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NEvent, FResource)

namespace NCsStatusEffect
{
	namespace NCoordinator
	{
		struct CSSE_API FLibrary final
		{
		// Print
		#pragma region
		public:

			static FString PrintObjectWithClass(const UCsCoordinator_StatusEffect* Coordinator);

		#pragma endregion Print

		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoordinator_StatusEffect from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsCoordinator_StatusEffect
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoordinator_StatusEffect from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				Context for UCsCoordinator_StatusEffect
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoordinator_StatusEffect from a WorldContext.
			*
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsCoordinator_StatusEffect
			*/
			static UObject* GetSafeContextRoot(const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsCoordinator_StatusEffect from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsCoordinator_StatusEffect.
			*/
			static UCsCoordinator_StatusEffect* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Get the reference to UCsCoordinator_StatusEffect from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsCoordinator_StatusEffect.
			*/
			template<typename T>
			static T* GetChecked(const FString& Context, const UObject* ContextObject)
			{
				UCsCoordinator_StatusEffect* O = GetChecked(Context, ContextObject);
				T* Other					   = Cast<T>(O);

				checkf(Other, TEXT("%s: %s is NOT of type: %s."), *Context, *PrintObjectWithClass(O), *(T::StaticClass()->GetName()));
				return Other;
			}

			/**
			* Safely get the reference to UCsCoordinator_StatusEffect from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				UCsCoordinator_StatusEffect.
			*/
			static UCsCoordinator_StatusEffect* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning);

			/**
			* Safely get the reference to UCsCoordinator_StatusEffect from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				UCsCoordinator_StatusEffect.
			*/
			template<typename T>
			static T* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning)
			{
				UCsCoordinator_StatusEffect* O = GetSafe(Context, ContextObject, Log);

				if (!O)
					return nullptr;

				T* Other = Cast<T>(O);

				if (!Other)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NOT of type: %s."), *Context, *PrintObjectWithClass(O), *(T::StaticClass()->GetName())));
				}
				return Other;
			}

			/**
			* Safely get the reference to UCsCoordinator_StatusEffect from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsCoordinator_StatusEffect.
			*/
			static UCsCoordinator_StatusEffect* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Data
		#pragma region
		public:

		#define DataType NCsStatusEffect::NData::IData

		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define DataInterfaceMapType NCsStatusEffect::NData::FInterfaceMap

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			*/
			static DataHandlerType<DataType, FCsData_StatusEffectPtr, DataInterfaceMapType>* GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning);

		#undef DataHandlerType
		#undef DataInterfaceMapType

			/**
			* Get the Data (implements interface: DataType (NCsStatusEffect::NData::IData)) associated with Name of the Status Effect type.
			* "Checked" in regards to returning a valid pointer.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name			Name of the Status Effect.
			* return				Data that implements the interface: DataType (NCsStatusEffect::NData::IData).
			*/
			static DataType* GetDataChecked(const FString& Context, const UObject* WorldContext, const FName& Name);

			/**
			* Safely get the Data (implements interface: DataType (NCsStatusEffect::NData::IData)) associated with Name of the Status Effect type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name			Name of the Status Effect.
			* @param Log			(optional)
			* return				Data that implements the interface: DataType (NCsStatusEffect::NData::IData).
			*/
			static DataType* GetSafeData(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning);

			/**
			* Get the Data (implements interface: DataType (NCsStatusEffect::NData::IData)) associated with Type.
			* "Checked" in regards to returning a valid pointer.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Status Effect type.
			* return				Data that implements the interface: DataType (NCsStatusEffect::NData::IData).
			*/
			static DataType* GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsStatusEffect& Type);

			/**
			* Get the Data (implements interface: DataType (NCsStatusEffect::NData::IData)) associated with Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Status Effect type.
			* @param Log			(optional)
			* return				Data that implements the interface: DataType (NCsStatusEffect::NData::IData).
			*/
			static DataType* GetSafeData(const FString& Context, const UObject* WorldContext, const FECsStatusEffect& Type, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning);

		#define ProcessPayloadType NCsStatusEffect::NData::NProcess::FPayload

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ProcessPayload
			*/
			static void ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ProcessPayloadType& ProcessPayload);

		#undef ProcessPayloadType

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Status Effect type.
			* @param Data			Object that implements the interface: DataType (NCsStatusEffect::NData::IData).
			* @param Instigator
			* @param Causer
			* @param Receiver
			*/
			static void ProcessDataChecked(const FString& Context, const UObject* WorldContext, const FECsStatusEffect& Type, DataType* Data, UObject* Instigator, UObject* Causer, UObject* Receiver);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Status Effect type.
			* @param Instigator
			* @param Causer
			* @param Receiver
			*/
			static void ProcessDataChecked(const FString& Context, const UObject* WorldContext, const FECsStatusEffect& Type, UObject* Instigator, UObject* Causer, UObject* Receiver);

		#undef DataType

		#pragma endregion Data

		// StatusEffect
		#pragma region
		public:
		
		#define SeResourceType NCsStatusEffect::FResource
		#define StatusEffectType NCsStatusEffect::IStatusEffect
		#define SeAllocatedType NCsStatusEffect::FAllocated
		
			static SeResourceType* AllocateStatusEffectChecked(const FString& Context, const UObject* WorldContext, const FECsStatusEffectImpl& Type);

			static void DeallocateStatusEffectChecked(const FString& Context, const UObject* WorldContext, const FECsStatusEffectImpl& Type, SeResourceType* StatusEffect);

			static const FECsStatusEffectImpl& GetStatusEffectImplTypeChecked(const FString& Context, const UObject* WorldContext, const StatusEffectType* StatusEffect);

			static SeResourceType* CreateCopyOfStatusEffectChecked(const FString& Context, const UObject* WorldContext, const StatusEffectType* StatusEffect, FECsStatusEffectImpl& OutType);

			static SeResourceType* CreateCopyOfStatusEffectChecked(const FString& Context, const UObject* WorldContext, const StatusEffectType* StatusEffect);

			static SeResourceType* CreateCopyOfStatusEffectChecked(const FString& Context, const UObject* WorldContext, const SeResourceType* StatusEffect);

			static void CreateCopyOfStatusEffectChecked(const FString& Context, const UObject* WorldContext, const StatusEffectType* StatusEffect, SeAllocatedType*& OutAllocated);

		#undef SeResourceType
		#undef StatusEffectType
		#undef SeAllocatedType

		#pragma endregion StatusEffect
		};

		namespace NEvent
		{
			struct CSSE_API FLibrary
			{
			public:

				FORCEINLINE static UCsCoordinator_StatusEffect* GetCoordinatorChecked(const FString& Context, const UObject* WorldContext)
				{
					typedef NCsStatusEffect::NCoordinator::FLibrary SeCoordinatorLibrary;

					return SeCoordinatorLibrary::GetChecked(Context, WorldContext);
				}

			#define EventResourceType NCsStatusEffect::NEvent::FResource

				static EventResourceType* AllocateChecked(const FString& Context, const UObject* WorldContext, const FECsStatusEffectEvent& Type);

				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, EventResourceType* Event, const FECsStatusEffectEvent& Type);
				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, EventResourceType* Event);

			#undef EventResourceType
			};
		}
	}
}
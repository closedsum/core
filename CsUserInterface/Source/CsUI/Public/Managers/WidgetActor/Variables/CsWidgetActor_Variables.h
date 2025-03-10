// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Managers/WidgetActor/Types/CsTypes_WidgetActor.h"
	// Time
#include "Managers/Time/CsTypes_Time.h"
// Resource
#include "Managers/Resource/CsManager_ResourceValueType_Fixed_Int32.h"

#include "CsWidgetActor_Variables.generated.h"

// NCsWidgetActor::NVariables::NAllocate::FPayload
#pragma region

class ICsWidgetActor;
class USceneComponent;

namespace NCsWidgetActor
{
	namespace NVariables
	{
		namespace NAllocate
		{
			struct CSUI_API FPayload
			{
			public:

				ICsWidgetActor* WidgetActor;

				USceneComponent* RotateComponent;

				FPayload() :
					WidgetActor(nullptr),
					RotateComponent(nullptr)
				{
				}

				bool IsValidChecked(const FString& Context) const;
			};
		}
	}
}

#pragma endregion NCsWidgetActor::NVariables::NAllocate::FPayload

// NCsWidgetActor::NVariables::FVariables
#pragma region

// NCsWidgetActor::NVariables::FManager
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWidgetActor, NVariables, FManager)

namespace NCsWidgetActor
{
	namespace NVariables
	{
		struct CSUI_API FVariables
		{
		private:

			NCsWidgetActor::NVariables::FManager* Outer;

		public:

			int32 ID;

			struct FCameraInfo
			{
				friend struct NCsWidgetActor::NVariables::FVariables;

			private:

				NCsWidgetActor::NVariables::FVariables* Outer;

			public:

				FCameraInfo() :
					Outer(nullptr)
				{
				}

				FORCEINLINE void SetOuter(NCsWidgetActor::NVariables::FVariables* InOuter) { Outer = InOuter; }

				FORCEINLINE const NCsWidgetActor::NVariables::FVariables* GetOuter() const { return Outer; }
				FORCEINLINE NCsWidgetActor::NVariables::FVariables* GetOuter() { return Outer; }

				FORCEINLINE const NCsWidgetActor::NVariables::FManager* GetOuterMost() const { return Outer->GetOuter(); }
				FORCEINLINE NCsWidgetActor::NVariables::FManager* GetOuterMost() { return Outer->GetOuter(); }

				FORCEINLINE const int32& GetID() const { return Outer->GetID(); }

				const float& GetLerpRate() const;
				float& GetLerpRate();
				const int32& GetLockAxes() const;
				int32& GetLockAxes();
				const FRotator3f& GetRotation() const;
				FRotator3f& GetRotation();
			};
			
			FCameraInfo CameraInfo;

			FVariables() :
				Outer(nullptr),
				ID(INDEX_NONE),
				CameraInfo()
			{
				CameraInfo.Outer = this;
			}

			FORCEINLINE void SetOuter(NCsWidgetActor::NVariables::FManager* InOuter)
			{
				Outer = InOuter;
				CameraInfo.SetOuter(this);
			}
			FORCEINLINE NCsWidgetActor::NVariables::FManager* GetOuter() { return Outer; }

			FORCEINLINE const int32& GetID() const { return ID; }

			const FVector3f& GetLastLocation() const;
			FVector3f& GetLastLocation();
			const FVector3f& GetLocation() const;
			FVector3f& GetLocation();
			const FRotator3f& GetRotation() const;
			FRotator3f& GetRotation();
			const FQuat4f& GetOrientation() const;
			FQuat4f& GetOrientation();

			FORCEINLINE void ResolveOrientation() { GetOrientation() = GetRotation().Quaternion(); }

			FORCEINLINE bool IsValidChecked(const FString& Context) const 
			{ 
				checkf(ID != INDEX_NONE, TEXT("%s: ID == INDEX_NONE is NOT Valid."), *Context); 
				return true;
			}
			FORCEINLINE bool IsValid() const { return ID != INDEX_NONE; }

			void Reset()
			{
				ID = INDEX_NONE;
			}
		};
	}
}

#pragma endregion NCsWidgetActor::NVariables::FVariables

// NCsWidgetActor::NVariables::FManager
#pragma region

class UCsManager_WidgetActor;
class ICsWidgetActor;
class USceneComponent;

namespace NCsWidgetActor
{
	namespace NVariables
	{
		struct CSUI_API FManager final
		{
			friend class UCManager_Character;

		private:

			using IDManagerType = NCsResource::NManager::NValue::NFixed::NInt32::FManager;
			using VariablesType = NCsWidgetActor::NVariables::FVariables;
			using VariablesPayloadType = NCsWidgetActor::NVariables::NAllocate::FPayload;

		private:

			UCsManager_WidgetActor* Outer;

		public:

			TArray<ICsWidgetActor*> WidgetActors;

		// IDs

			IDManagerType Manager_ID;

			TArray<int32> AllocatedIDs;

			TArray<VariablesType> Variables;

			int32 ActiveCount;

			TArray<int32> ActiveIDs;

			TArray<USceneComponent*> RotateComponents;

			TArray<FVector3f> Last_Locations;
			TArray<FVector3f> Locations;

			TArray<FRotator3f> Rotations;
			TArray<FQuat4f> Orientations;

			struct FCameraInfos
			{
				friend struct NCsWidgetActor::NVariables::FManager;

			private:

				NCsWidgetActor::NVariables::FManager* Outer;

			public:

				TArray<float> LerpRates;

				TArray<int32> LockAxes;

				TArray<FRotator3f> Rotations;

				FCameraInfos() :
					Outer(nullptr),
					LerpRates(),
					LockAxes(),
					Rotations()
				{
				}

				FORCEINLINE void SetOuter(NCsWidgetActor::NVariables::FManager* InOuter)
				{
					Outer = InOuter;
				}

				FORCEINLINE const NCsWidgetActor::NVariables::FManager* GetOuter() const { return Outer; }
				FORCEINLINE NCsWidgetActor::NVariables::FManager* GetOuter() { return Outer; }

				FORCEINLINE const UCsManager_WidgetActor* GetOuterMost() const { return Outer->GetOuter(); }
				FORCEINLINE UCsManager_WidgetActor* GetOuterMost() { return Outer->GetOuter(); }

				FORCEINLINE const UObject* GetWorldContext() const { return Outer->GetWorldContext(); }

				void SetSize(const int32& InSize)
				{
					LerpRates.Reset(InSize);
					LockAxes.Reset(InSize);
					Rotations.Reset(InSize);

					for (int32 I = 0; I < InSize; ++I)
					{
						LerpRates.Add(0.0f);
						LockAxes.Add(4); // Roll (1 << 2)
						Rotations.Add(FRotator3f::ZeroRotator);
					}
				}

				void Update(const FCsDeltaTime& DeltaTime);

				FORCEINLINE void Reset(const int32& Index)
				{
					LerpRates[Index] = 0.0f;
					LockAxes[Index]  = 4; // Roll (1 << 2)
					Rotations[Index] = FRotator3f::ZeroRotator;
				}

			};

			FCameraInfos CameraInfos;

			struct FScaleInfos
			{
			};

			FScaleInfos ScaleInfos;

			FManager() :
				Outer(nullptr),
				WidgetActors(),
				// IDs
				Manager_ID(),
				AllocatedIDs(),
				Variables(),
				ActiveCount(0),
				ActiveIDs(),
				RotateComponents(),
				Last_Locations(),
				Locations(),
				Rotations(),
				Orientations(),
				CameraInfos()
			{
				CameraInfos.Outer = this;
			}

			FORCEINLINE void SetOuter(UCsManager_WidgetActor* InOuter) 
			{ 
				Outer = InOuter;
				CameraInfos.SetOuter(this);
			}

			FORCEINLINE const UCsManager_WidgetActor* GetOuter() const { return Outer; }
			FORCEINLINE UCsManager_WidgetActor* GetOuter() { return Outer; }

			const UObject* GetWorldContext() const;

			FORCEINLINE VariablesType* GetVariablesPtr(const int32& Index) { return &(Variables[Index]); }

			FORCEINLINE const TArray<ICsWidgetActor*>& GetWidgetActors() const { return WidgetActors; }

			// Movement
			FORCEINLINE FVector3f* GetLocationPtr(const int32& Index) { return &(Locations[Index]); }
			FORCEINLINE FRotator3f* GetRotationPtr(const int32& Index) { return &(Rotations[Index]); }
			FORCEINLINE FQuat4f* GetOrientationPtr(const int32& Index) { return &(Orientations[Index]); }

			void SetSize(const int32& InSize)
			{
				Manager_ID.CreatePool(InSize);

				WidgetActors.Reset(InSize);
				AllocatedIDs.Reset(InSize);
				ActiveIDs.Reset(InSize);
				RotateComponents.Reset(InSize);
				Last_Locations.Reset(InSize);
				Locations.Reset(InSize);
				Rotations.Reset(InSize);
				Orientations.Reset(InSize);

				typedef NCsResource::NManager::NValue::NFixed::NInt32::FResource ResourceType;

				const TArray<ResourceType*>& Resources = Manager_ID.GetPool();

				for (int32 I = 0; I < InSize; ++I)
				{
					// Manager_ID					
					ResourceType* C = Resources[I];
					int32& ID	= C->GetRef();
					ID			= I;

					WidgetActors.Add(nullptr);
					AllocatedIDs.Add(INDEX_NONE);
					Variables.AddDefaulted();
					ActiveIDs.Add(INDEX_NONE);
					RotateComponents.Add(nullptr);
					Last_Locations.Add(FVector3f::ZeroVector);
					Locations.Add(FVector3f::ZeroVector);
					Rotations.Add(FRotator3f::ZeroRotator);
					Orientations.Add(FQuat4f::Identity);
				}

				for (int32 I = 0; I < InSize; ++I)
				{
					Variables[I].SetOuter(this);
				}

				CameraInfos.SetSize(InSize);
			}

			void Update(const FCsDeltaTime& DeltaTime);

			FORCEINLINE bool IsValid(const int32& Index) const { return Variables[Index].IsValid(); }

			VariablesType* AllocateChecked(const FString& Context, const VariablesPayloadType& Payload);

			void DeallocateChecked(const FString& Context, VariablesType* Variables);

			FORCEINLINE void Reset(const int32& Index)
			{
				Variables[Index].Reset();
				WidgetActors[Index] = nullptr;
				RotateComponents[Index] = nullptr;
				Locations[Index] = FVector3f::ZeroVector;
				Rotations[Index] = FRotator3f::ZeroRotator;
				Orientations[Index] = FQuat4f::Identity;
				CameraInfos.Reset(Index);
				Manager_ID.DeallocateAt(Index);
			}
		};
	}
}

#pragma endregion NCsWidgetActor::NVariables::FManager

UINTERFACE(Blueprintable)
class CSUI_API UCsWidgetActor_Variables : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// NCsWidgetActor::NVariables::FVariables
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWidgetActor, NVariables, FVariables)

class CSUI_API ICsWidgetActor_Variables
{
	GENERATED_IINTERFACE_BODY()

private:

	// Allow clearer names without name collisions
	struct _
	{
		using VariablesType = NCsWidgetActor::NVariables::FVariables;
	};

public:

	virtual const _::VariablesType* GetVariables() const = 0;

	virtual _::VariablesType* GetVariables() = 0;
};
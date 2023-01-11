// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/Variables/CsWidgetActor_Variables.h"

// Library
	// Common
#include "Library/CsLibrary_Player.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/WidgetActor/CsManager_WidgetActor.h"

// NCsWidgetActor::NVariables::NAllocate::FPayload
#pragma region

namespace NCsWidgetActor
{
	namespace NVariables
	{
		namespace NAllocate
		{
			bool FPayload::IsValidChecked(const FString& Context) const
			{
				return true;
			}
		}
	}
}

#pragma endregion NCsWidgetActor::NVariables::NAllocate::FPayload

// NCsWidgetActor::NVariables::FVariables
#pragma region

namespace NCsWidgetActor
{
	namespace NVariables
	{
		// FVariables::FCameraInfo
		
		#define PROXY FVariables::FCameraInfo
		#define GET_BASE GetOuterMost()->CameraInfos

		const float& PROXY::GetLerpRate() const { return GET_BASE.LerpRates[GetID()]; }
		float& PROXY::GetLerpRate() { return GET_BASE.LerpRates[GetID()]; }
		const int32& PROXY::GetLockAxes() const { return GET_BASE.LockAxes[GetID()]; }
		int32& PROXY::GetLockAxes() { return GET_BASE.LockAxes[GetID()]; }
		const FRotator& PROXY::GetRotation() const { return GET_BASE.Rotations[GetID()]; }
		FRotator& PROXY::GetRotation() { return GET_BASE.Rotations[GetID()]; }

		#undef PROXY
		#undef GET_BASE

		// FVariables

		const FVector& FVariables::GetLastLocation() const { return Outer->Last_Locations[ID]; }
		FVector& FVariables::GetLastLocation() { return Outer->Last_Locations[ID]; }
		const FVector& FVariables::GetLocation() const { return Outer->Locations[ID]; }
		FVector& FVariables::GetLocation() { return Outer->Locations[ID]; }
		const FRotator& FVariables::GetRotation() const { return Outer->Rotations[ID]; }
		FRotator& FVariables::GetRotation() { return Outer->Rotations[ID]; }
		const FQuat& FVariables::GetOrientation() const { return Outer->Orientations[ID]; }
		FQuat& FVariables::GetOrientation() { return Outer->Orientations[ID]; }
	}
}

#pragma endregion NCsWidgetActor::NVariables::FVariables

// NCsWidgetActor::NVariables::FManager
#pragma region

namespace NCsWidgetActor
{
	namespace NVariables
	{
		namespace NManager
		{
			namespace NCached
			{
				namespace Str
				{

				}
			}

			namespace NCameraInfos
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidgetActor::NVariables::FManager::FCameraInfos, Update);
					}
				}
			}
		}

		void FManager::FCameraInfos::Update(const FCsDeltaTime& DeltaTime)
		{
			using namespace NCsWidgetActor::NVariables::NManager::NCameraInfos::NCached;

			const FString& Context = Str::Update;

			// FManager = Outer
			const TArray<int32>& _ActiveIDs = Outer->ActiveIDs;
			const int32& _ActiveCount	    = Outer->ActiveCount;


		}

		const UObject* FManager::GetWorldContext() const
		{
			return Outer->GetMyRoot();
		}

		void FManager::Update(const FCsDeltaTime& DeltaTime)
		{
			typedef NCsResource::NManager::NValue::NFixed::NInt32::FResource ResourceType;

			TCsDoubleLinkedList<ResourceType*>* Current = Manager_ID.GetAllocatedHead();
			TCsDoubleLinkedList<ResourceType*>* Next	= Current;

			int32 AllocatedCount = 0;
			ActiveCount = 0;

			while (Next)
			{
				Current			= Next;
				ResourceType* C = **Current;
				Next			= Current->GetNextLink();

				int32& ID = C->GetRef();

				AllocatedIDs[AllocatedCount] = ID;
				ActiveIDs[ActiveCount]		 = ID;

				++ActiveCount;
				++AllocatedCount;
			}

			CameraInfos.Update(DeltaTime);
		}

		#define VariablesType NCsWidgetActor::NVariables::FVariables
		#define VariablesPayloadType NCsWidgetActor::NVariables::NAllocate::FPayload
		VariablesType* FManager::AllocateChecked(const FString& Context, const VariablesPayloadType& Payload)
		{
		#undef VariablesPayloadType

			const int32& ID = Manager_ID.Allocate()->GetRef();

			Variables[ID].ID = ID;

			WidgetActors[ID]	 = Payload.WidgetActor;
			RotateComponents[ID] = Payload.RotateComponent;

			return GetVariablesPtr(ID);
		}

		void FManager::DeallocateChecked(const FString& Context, VariablesType* Vars)
		{
			CS_IS_PTR_NULL_CHECKED(Vars);

			check(Vars->IsValidChecked(Context));

			const int32 ID = Vars->GetID();

			check(Manager_ID.IsAllocatedChecked(Context, ID));
			checkf(Vars == GetVariablesPtr(ID), TEXT("%s: ID: %s is NOT correct for Vars."), *Context, ID);

			Reset(ID);
		}

		#undef VariablesType
	}
}

#pragma endregion NCsWidgetActor::NVariables::FManager

UCsWidgetActor_Variables::UCsWidgetActor_Variables(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}
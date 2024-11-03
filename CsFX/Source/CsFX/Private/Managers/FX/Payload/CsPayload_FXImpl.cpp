// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Payload/CsPayload_FXImpl.h"

// Types
#include "CsMacro_Misc.h"
#include "CsMacro_Interface.h"
// Library
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
// Containers
#include "Containers/CsInterfaceMap.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsFX::NPayload::NImpl::FImpl);

namespace NCsFX
{
	namespace NPayload
	{
		namespace NImpl
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NPayload::NImpl, Reset);
				}
			}

			using ParameterLibrary = NCsFX::NManager::NParameter::FLibrary;

			FImpl::FImpl() :
				Root(nullptr),
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
				bAllocated(false),
				UpdateType(NCsPooledObject::EUpdate::Manager),
				Instigator(nullptr),
				Owner(nullptr),
				Parent(nullptr),
				Time(),
				PreserveChangesFromDefaultMask(0),
				// FXPayloadType (NCsFX::Payload::IPayload)
				FXSystem(nullptr),
				DeallocateMethod(DeallocateMethodType::Complete),
				LifeTime(0.0f),
				DeathTime(0.0f),
				bHideOnQueueDeallocate(false),
				AttachmentTransformRules(FAttachmentTransformRules::SnapToTargetNotIncludingScale),
				Bone(NAME_None),
				TransformRules(0),
				Transform(FTransform3f::Identity),
				bAbsoluteLocation(false),
				bAbsoluteRotation(false),
				bAbsoluteScale(false),
				bApplyTransformScale(true),
				Parameters(),
				ScaledParameters(),
				SkeletalMeshParameters()
			{
				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FImpl>(this);

				InterfaceMap->Add<PooledPayloadType>(static_cast<PooledPayloadType*>(this));
				InterfaceMap->Add<PayloadType>(static_cast<PayloadType*>(this));
			}

			FImpl::~FImpl()
			{
				delete InterfaceMap;
			}

			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			#pragma region

			void FImpl::Reset()
			{
				using namespace NCsFX::NPayload::NImpl::NCached;

				const FString& Context = Str::Reset;

				// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
				bAllocated = false;
				UpdateType = NCsPooledObject::EUpdate::Manager;
				Instigator = nullptr;
				Owner = nullptr;
				Parent = nullptr;

				Time.Reset();

				PreserveChangesFromDefaultMask = 0;

				// PayloadType (NCsFX::NPayload::IPayload)
				FXSystem = nullptr;
				DeallocateMethod = DeallocateMethodType::Complete;
				LifeTime = 0.0f;
				DeathTime = 0.0f;
				bHideOnQueueDeallocate = false;
				AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
				Bone = NAME_None;
				TransformRules = 0;
				Transform = FTransform3f::Identity;
				bAbsoluteLocation = false;
				bAbsoluteRotation = false;
				bAbsoluteScale = false;
				bApplyTransformScale = true;

				ParameterLibrary::DeallocateChecked(Context, GetRoot(), Parameters);
				ParameterLibrary::DeallocateChecked(Context, GetRoot(), ScaledParameters);
				ParameterLibrary::DeallocateChecked(Context, GetRoot(), SkeletalMeshParameters);
			}

			#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		}
	}
}
// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Payload/CsPayload_FXImpl.h"

// Library
#include "Managers/FX/Actor/CsLibrary_Manager_FX.h"
// Containers
#include "Containers/CsInterfaceMap.h"

const FName NCsFX::NPayload::FImpl::Name = FName("NCsFX::NPayload::FImpl");;

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
		}

		#define DeallocateMethodType NCsFX::EDeallocateMethod

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
			AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
			Bone(NAME_None),
			TransformRules(0),
			Transform(FTransform::Identity),
			bApplyTransformScale(true),
			Parameters(),
			ScaledParameters()
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;
			typedef NCsFX::NPayload::IPayload FXPayloadType;

			InterfaceMap->Add<PooledPayloadType>(static_cast<PooledPayloadType*>(this));
			InterfaceMap->Add<FXPayloadType>(static_cast<FXPayloadType*>(this));
		}

		#undef DeallocateMethodType

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

			// FXPayloadType (NCsFX::NPayload::IPayload)
			typedef NCsFX::EDeallocateMethod DeallocateMethodType;

			FXSystem = nullptr;
			DeallocateMethod = DeallocateMethodType::Complete;
			LifeTime = 0.0f;
			DeathTime = 0.0f;
			bHideOnQueueDeallocate = false;
			AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
			Bone = NAME_None;
			TransformRules = 0;
			Transform = FTransform::Identity;
			bApplyTransformScale = true;

			typedef NCsFX::NManager::FLibrary FXManagerLibrary;
			typedef NCsFX::NParameter::IParameter ParameterType;
			typedef NCsFX::NParameter::NScaled::IScaled ScaledParameterType;

			for (ParameterType* Param : Parameters)
			{
				FXManagerLibrary::DeallocateValueChecked(Context, Root, Param);
			}
			Parameters.Reset(Parameters.Max());

			for (ScaledParameterType* Param : ScaledParameters)
			{
				FXManagerLibrary::DeallocateValueChecked(Context, Root, Param);
			}
			ScaledParameters.Reset(ScaledParameters.Max());
		}

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)
	}
}
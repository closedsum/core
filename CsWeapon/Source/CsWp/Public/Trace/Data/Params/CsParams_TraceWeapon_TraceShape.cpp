// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Data/Params/CsParams_TraceWeapon_TraceShape.h"

#include "Containers/CsInterfaceMap.h"
#include "Managers/Trace/CsTypes_Trace.h"

#define NCurrentNamespace NCsWeapon::NTrace::NParams::NTrace

const FName NCurrentNamespace::FLineImpl::Name = FName("NCsWeapon::NTrace::NParams::NTrace::FLineImpl");
const FName NCurrentNamespace::FBoxImpl::Name = FName("NCsWeapon::NTrace::NParams::NTrace::FBoxImpl");
const FName NCurrentNamespace::FSphereImpl::Name = FName("NCsWeapon::NTrace::NParams::NTrace::FSphereImpl");
const FName NCurrentNamespace::FCapsuleImpl::Name = FName("NCsWeapon::NTrace::NParams::NTrace::FCapsuleImpl");

#undef NCurrentNamespace

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NParams
		{
			namespace NTrace
			{
			// FLineImpl
			#pragma region

				FLineImpl::FLineImpl() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// ITrace
					LocationInfo(),
					DirectionInfo(),
					ObjectTypes(),
					Shape(),
					Distance(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FLineImpl>(this);

					InterfaceMap->Add<ITrace>(static_cast<ITrace*>(this));
				}

				FLineImpl::~FLineImpl()
				{
					delete InterfaceMap;
				}

			#pragma endregion FBoxImpl

			// FBoxImpl
			#pragma region

				FBoxImpl::FBoxImpl() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// ITrace
					LocationInfo(),
					DirectionInfo(),
					ObjectTypes(),
					Shape(),
					Distance(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FBoxImpl>(this);

					InterfaceMap->Add<ITrace>(static_cast<ITrace*>(this));
				}

				FBoxImpl::~FBoxImpl()
				{
					delete InterfaceMap;
				}

				void FBoxImpl::SetShape(FCsTraceCollisionBox* Value)
				{
					Shape.ShapeType		  = ECollisionShape::Box;
					Shape.Box.HalfExtentX = Value->HalfExtentX;
					Shape.Box.HalfExtentY = Value->HalfExtentY;
					Shape.Box.HalfExtentZ = Value->HalfExtentZ;
				}

			#pragma endregion FBoxImpl

			// FSphereImpl
			#pragma region

				FSphereImpl::FSphereImpl() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// ITrace
					LocationInfo(),
					DirectionInfo(),
					ObjectTypes(),
					Shape(),
					Distance(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FSphereImpl>(this);

					InterfaceMap->Add<ITrace>(static_cast<ITrace*>(this));
				}

				FSphereImpl::~FSphereImpl()
				{
					delete InterfaceMap;
				}

				void FSphereImpl::SetShape(FCsTraceCollisionSphere* Value)
				{
					Shape.ShapeType		= ECollisionShape::Sphere;
					Shape.Sphere.Radius = Value->Radius;
				}

			#pragma endregion FSphereImpl

			// FCapsuleImpl
			#pragma region

				FCapsuleImpl::FCapsuleImpl() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// ITrace
					LocationInfo(),
					DirectionInfo(),
					ObjectTypes(),
					Shape(),
					Distance(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FCapsuleImpl>(this);

					InterfaceMap->Add<ITrace>(static_cast<ITrace*>(this));
				}

				FCapsuleImpl::~FCapsuleImpl()
				{
					delete InterfaceMap;
				}

				void FCapsuleImpl::SetShape(FCsTraceCollisionCapsule* Value)
				{
					Shape.ShapeType			 = ECollisionShape::Capsule;
					Shape.Capsule.Radius	 = Value->Radius;
					Shape.Capsule.HalfHeight = Value->HalfHeight;
				}

			#pragma endregion FCapsuleImpl
			}
		}
	}
}
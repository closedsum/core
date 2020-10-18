// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Data/Params/CsParams_TraceWeapon_TraceShape.h"

#include "Containers/CsInterfaceMap.h"
#include "Managers/Trace/CsTypes_Trace.h"

#define NCurrentNamespace NCsWeapon::NTrace::NParams::NTrace

const FName NCurrentNamespace::FLineEmu::Name = FName("NCsWeapon::NTrace::NParams::NTrace::FLineEmu");
const FName NCurrentNamespace::FBoxEmu::Name = FName("NCsWeapon::NTrace::NParams::NTrace::FBoxEmu");
const FName NCurrentNamespace::FSphereEmu::Name = FName("NCsWeapon::NTrace::NParams::NTrace::FSphereEmu");
const FName NCurrentNamespace::FCapsuleEmu::Name = FName("NCsWeapon::NTrace::NParams::NTrace::FCapsuleEmu");

#undef NCurrentNamespace

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NParams
		{
			namespace NTrace
			{
			// FLineEmu
			#pragma region

				FLineEmu::FLineEmu() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// ITrace
					Location(nullptr),
					Direction(nullptr),
					DirectionRules(nullptr),
					ObjectType(ECollisionChannel::ECC_MAX),
					Shape(),
					Distance(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRootName(FLineEmu::Name);

					InterfaceMap->Add<ITrace>(static_cast<ITrace*>(this));
				}

				FLineEmu::~FLineEmu()
				{
					delete InterfaceMap;
				}

			#pragma endregion FBoxEmu

			// FBoxEmu
			#pragma region

				FBoxEmu::FBoxEmu() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// ITrace
					Location(nullptr),
					Direction(nullptr),
					DirectionRules(nullptr),
					ObjectType(ECollisionChannel::ECC_MAX),
					Shape(),
					Distance(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRootName(FBoxEmu::Name);

					InterfaceMap->Add<ITrace>(static_cast<ITrace*>(this));
				}

				FBoxEmu::~FBoxEmu()
				{
					delete InterfaceMap;
				}

				void FBoxEmu::SetShape(FCsTraceCollisionBox* Value)
				{
					Shape.ShapeType		  = ECollisionShape::Box;
					Shape.Box.HalfExtentX = Value->HalfExtentX;
					Shape.Box.HalfExtentY = Value->HalfExtentY;
					Shape.Box.HalfExtentZ = Value->HalfExtentZ;
				}

			#pragma endregion FBoxEmu

			// FSphereEmu
			#pragma region

				FSphereEmu::FSphereEmu() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// ITrace
					Location(nullptr),
					Direction(nullptr),
					DirectionRules(nullptr),
					ObjectType(ECollisionChannel::ECC_MAX),
					Shape(),
					Distance(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRootName(FSphereEmu::Name);

					InterfaceMap->Add<ITrace>(static_cast<ITrace*>(this));
				}

				FSphereEmu::~FSphereEmu()
				{
					delete InterfaceMap;
				}

				void FSphereEmu::SetShape(FCsTraceCollisionSphere* Value)
				{
					Shape.ShapeType		= ECollisionShape::Sphere;
					Shape.Sphere.Radius = Value->Radius;
				}

			#pragma endregion FSphereEmu

			// FCapsuleEmu
			#pragma region

				FCapsuleEmu::FCapsuleEmu() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// ITrace
					Location(nullptr),
					Direction(nullptr),
					DirectionRules(nullptr),
					ObjectType(ECollisionChannel::ECC_MAX),
					Shape(),
					Distance(nullptr)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRootName(FCapsuleEmu::Name);

					InterfaceMap->Add<ITrace>(static_cast<ITrace*>(this));
				}

				FCapsuleEmu::~FCapsuleEmu()
				{
					delete InterfaceMap;
				}

				void FCapsuleEmu::SetShape(FCsTraceCollisionCapsule* Value)
				{
					Shape.ShapeType			 = ECollisionShape::Capsule;
					Shape.Capsule.Radius	 = Value->Radius;
					Shape.Capsule.HalfHeight = Value->HalfHeight;
				}

			#pragma endregion FCapsuleEmu
			}
		}
	}
}
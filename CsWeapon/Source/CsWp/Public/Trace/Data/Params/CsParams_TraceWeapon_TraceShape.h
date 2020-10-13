// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interface
#include "Trace/Data/Params/CsParams_TraceWeapon_Trace.h"

class UObject;
struct FCsInterfaceMap;
struct FCsTraceCollisionBox;

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NParams
		{
			namespace NTrace
			{
				/**
				*/
				struct CSWP_API FBoxEmu : public ITrace
				{
				public:

					static const FName Name;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

					// ITrace

					ELocation* Location;

					EDirection* Direction;

					TEnumAsByte<ECollisionChannel>* ObjectTypeEmu;

					ECollisionChannel ObjectType;

					FCsTraceCollisionBox* Box;

					FCollisionShape Shape;

				public:

					FBoxEmu();
					~FBoxEmu();
					
					FORCEINLINE UObject* _getUObject() const { return nullptr; }

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

					FORCEINLINE void SetLocationType(ELocation* Value) { Location = Value; }
					FORCEINLINE void SetDirectionType(EDirection* Value) { Direction = Value; }
					FORCEINLINE void SetObjectType(TEnumAsByte<ECollisionChannel>* Value) { ObjectTypeEmu = Value; }
					FORCEINLINE void SetObjectType() { ObjectType = ObjectTypeEmu->GetValue(); }
					FORCEINLINE void SetShape(FCsTraceCollisionBox* Value) { Box = Value; }

					void SetShape();

				// ITrace
				#pragma region
				public:

					FORCEINLINE const ELocation& GetLocationType() const { return *Location; }
					FORCEINLINE const EDirection& GetDirectionType() const { return *Direction; }

					FORCEINLINE const ECollisionChannel& GetObjectType() const
					{
						SetObjectType();
						return ObjectType;
					}

					FORCEINLINE const FCollisionShape& GetShape() const
					{
						SetShape();
						return Shape;
					}

				#pragma endregion ITrace
				};
			}
		}
	}
}
// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Data/CsLibrary_Data_TraceWeapon.h"
#include "CsWp.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Data
#include "Trace/Data/CsData_TraceWeapon.h"

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NData
		{
			#define DataType NCsWeapon::NTrace::NData::IData

			bool FLibrary::IsValidChecked(const FString& Context, const DataType* Data)
			{
				// Check Data is Valid
				CS_IS_PTR_NULL_CHECKED(Data)
				// Check MaxAmmo is a valid value
				if (!Data->HasInfiniteAmmo())
				{
					CS_IS_INT_GREATER_THAN_CHECKED(Data->GetMaxAmmo(), 0)
				}
				// Check TimeBetweenShots > 0.0f
				CS_IS_FLOAT_GREATER_THAN_CHECKED(Data->GetTimeBetweenShots(), 0.0f)
				// Check TracesPerShot >= 1
				CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Data->GetTracesPerShot(), 1)
				// Check TimeBetweenTracesPerShot is valid when TracesPerShot > 1
				if (Data->GetTracesPerShot() > 1)
				{
					checkf(Data->GetTimeBetweenTracesPerShot() > 0.0f, TEXT("%s: TimeBetweenTracesPerShot must be > 0.0f when TracesPerShot > 1."), *Context);
				}
				return true;
			}

			bool FLibrary::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
			{
				// Check Data is Valid
				CS_IS_PTR_NULL(Data)
				// Check MaxAmmo is a valid value
				if (!Data->HasInfiniteAmmo())
				{
					CS_IS_INT_GREATER_THAN(Data->GetMaxAmmo(), 0)
				}
				// Check TimeBetweenShots > 0.0f
				CS_IS_FLOAT_GREATER_THAN(Data->GetTimeBetweenShots(), 0.0f)
				// Check TracesPerShot >= 1
				CS_IS_INT_GREATER_THAN_OR_EQUAL(Data->GetTracesPerShot(), 1)
				// Check TimeBetweenTracesPerShot is valid when TracesPerShot > 1
				if (Data->GetTracesPerShot() > 1)
				{
					if (Data->GetTimeBetweenTracesPerShot() <= 0.0f)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: TimeBetweenTracesPerShot must be > 0.0f when TracesPerShot > 1."), *Context));
						return false;
					}
				}
				return true;
			}

			#undef DataType
		}
	}
}
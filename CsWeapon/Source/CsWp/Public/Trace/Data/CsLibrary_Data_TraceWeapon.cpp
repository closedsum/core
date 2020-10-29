// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Data/CsLibrary_Data_TraceWeapon.h"
#include "CsWp.h"

// Data
#include "Trace/Data/CsData_TraceWeapon.h"

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NData
		{
			#define DataType NCsWeapon::NTrace::NData::IData
			bool FLibrary::IsValidChecked(const FString& Context, DataType* Data)
			{
			#undef DataType

				checkf(Data, TEXT("%s: Data is NULL."), *Context);

				// Check MaxAmmo is a valid value
				if (!Data->HasInfiniteAmmo())
				{
					checkf(Data->GetMaxAmmo() > 0, TEXT("%s: MaxAmmo must be > 0."), *Context);
				}
				// Check TimeBetweenShots > 0.0f
				checkf(Data->GetTimeBetweenShots() > 0.0f, TEXT("%s: TimeBetweenShots must be > 0.0f."), *Context);
				// Check TracesPerShot >= 1
				checkf(Data->GetTracesPerShot() >= 1, TEXT("%s: TracesPerShot must be >= 1."), *Context);
				// Check TimeBetweenTracesPerShot is valid when TracesPerShot > 1
				if (Data->GetTracesPerShot() > 1)
				{
					checkf(Data->GetTimeBetweenTracesPerShot() > 0.0f, TEXT("%s: TimeBetweenTracesPerShot must be > 0.0f when TracesPerShot > 1."), *Context);
				}
				return true;
			}
		}
	}
}
// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections.Generic;
    using System.Reflection;

    #region "Enums"

    public interface ICgEnum
    {
        string GetName();
    }

    public abstract class TCgEnum<T> : ICgEnum where T : struct, IConvertible
    {
        #region "Delegates"

        public delegate TCgEnum<T> Get(T t);
        public delegate TCgEnum<T> GetMAX();
        public delegate TCgEnum<T> ToType(string s);
        public delegate string ToStr(TCgEnum<T> e);

        public delegate int ToMask(string s);
        public delegate string MaskToStr(int m);

        #endregion // Delegates

        #region "Data Members"

        public readonly T Value;
        public readonly string Name;

        #endregion // Data Members

        public TCgEnum()
        {
            Value = default(T);
            Name = "";
        }

        public TCgEnum(T value)
        {
            Value = value;
            Name = "";
        }

        public TCgEnum(T value, string name)
        {
            Value = value;
            Name = name;
        }

        public static implicit operator T(TCgEnum<T> e)
        {
            return e.Value;
        }

        public static implicit operator string(TCgEnum<T> e)
        {
            return e.Name;
        }

        public static bool operator ==(TCgEnum<T> lhs, TCgEnum<T> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Value.Equals(rhs.Value) && lhs.Name == rhs.Name;
        }

        public static bool operator !=(TCgEnum<T> lhs, TCgEnum<T> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgEnum<T> lhs, T rhs)
        {
            return lhs.Value.Equals(rhs);
        }

        public static bool operator !=(TCgEnum<T> lhs, T rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(T lhs, TCgEnum<T> rhs)
        {
            return lhs.Equals(rhs.Value);
        }

        public static bool operator !=(T lhs, TCgEnum<T> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgEnum<T> lhs, string rhs)
        {
            return lhs.Name ==rhs;
        }

        public static bool operator !=(TCgEnum<T> lhs, string rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(string lhs, TCgEnum<T> rhs)
        {
            return lhs == rhs.Name;
        }

        public static bool operator !=(string lhs, TCgEnum<T> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgEnum<T>))
                return false;

            TCgEnum<T> rhs = (TCgEnum<T>)obj;

            if (!Value.Equals(rhs.Value)) return false;
            if (Name != rhs.Name) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Value.GetHashCode() ^ Name.GetHashCode();
        }

        public string GetName()
        {
            return Name;
        }
    }

    public class ECgEnum_byte : TCgEnum<byte>
    {
        public ECgEnum_byte() : base() { }
        public ECgEnum_byte(byte value) : base(value) { }
        public ECgEnum_byte(byte value, string name) : base(value, name) { }
    }

    public class ECgEnum_int : TCgEnum<int>
    {
        public ECgEnum_int() : base() { }
        public ECgEnum_int(int value) : base(value) { }
        public ECgEnum_int(int value, string name) : base(value, name) { }
    }

    public class ECgEnum_uint : TCgEnum<uint>
    {
        public ECgEnum_uint() : base() { }
        public ECgEnum_uint(uint value) : base(value) { }
        public ECgEnum_uint(uint value, string name) : base(value, name) { }
    }

    public class ECgEnumMap<EnumClass, EnumType>
        where EnumClass : TCgEnum<EnumType>
        where EnumType : struct, IConvertible
    {
        protected sealed class EnumTypeEqualityComparer : IEqualityComparer<EnumType>
        {
            public bool Equals(EnumType lhs, EnumType rhs)
            {
                return lhs.Equals(rhs);
            }

            public int GetHashCode(EnumType x)
            {
                return x.GetHashCode();
            }
        }

        private List<EnumClass> Enums;
        private Dictionary<string, EnumClass> StringMap;
        private Dictionary<EnumType, EnumClass> TypeMap;
        private EnumClass Max;

        public int Count
        {
            get { return Enums.Count; }
        }

        public ECgEnumMap()
        {
            Enums = new List<EnumClass>();
            StringMap = new Dictionary<string, EnumClass>();
            TypeMap = new Dictionary<EnumType, EnumClass>(new EnumTypeEqualityComparer());
        }

        public EnumClass Create(string name)
        {
            EnumClass e = null;

            StringMap.TryGetValue(name, out e);

            if (e != null)
            {
                CgDebug.LogError(this.GetType().Name + ".Create: Enum with name: " + name + " already exists. It is being defined in move than one place.");
                return e;
            }

            Type type = typeof(EnumClass);
            // Get Constructor
            Type[] types = new Type[2];
            types[0]     = typeof(EnumType);
            types[1]     = typeof(string);
            ConstructorInfo constructor = type.GetConstructor(types);

            // Get Params for Constructor and create EnumClass
            object[] param  = new object[2];
            param[0]        = (EnumType)Convert.ChangeType(Enums.Count, typeof(EnumType));
            param[1]        = name;
            e               = (EnumClass)constructor.Invoke(param);

            Max = (EnumClass)constructor.Invoke(param);

            // Add to List and Maps
            EnumType index = (EnumType)Convert.ChangeType(Enums.Count, typeof(EnumType));

            Enums.Add(e);
            StringMap.Add(name, e);
            TypeMap.Add(index, e);

            return e;
        }

        public EnumClass this[string key]
        {
            get
            {
                EnumClass e = null;
                StringMap.TryGetValue(key, out e);

                if (e == null)
                    CgDebug.LogError(this.GetType().Name + ".Get: No enum created of type: " + typeof(EnumClass).Name + " and name: " + key);
                return e;
            }
        }

        public EnumClass this[EnumType key]
        {
            get
            {
                EnumClass e = null;
                TypeMap.TryGetValue(key, out e);

                if (e == null)
                    CgDebug.LogError(this.GetType().Name + ".Get: No enum created of type: " + typeof(EnumClass).Name + " and name: " + key);
                return e;
            }
        }

        public bool IsValidEnum(EnumClass e)
        {
            return Enums.Find(em => em == e) != null;
        }

        public bool IsValidEnum(string name)
        {
            return StringMap.ContainsKey(name);
        }

        public EnumClass GetEnumAt(int index)
        {
            return Enums[index];
        }

        public EnumClass GetSafeEnumAt(int index)
        {
            return index < Count ? Enums[index] : Max;
        }

        public EnumClass GetEnum(string name)
        {
            return StringMap[name];
        }

        public EnumClass GetSafeEnum(string name)
        {
            return IsValidEnum(name) ? StringMap[name] : Max;
        }

        public EnumClass GetEnum(EnumType type)
        {
            return TypeMap[type];
        }

        public EnumClass GetMAX()
        {
            return Max;
        }
    }

    public class ECgEnumMaskMap<EnumClass, EnumType>
        where EnumClass : TCgEnum<EnumType>
        where EnumType : struct, IConvertible
    {
        protected sealed class EnumTypeEqualityComparer : IEqualityComparer<EnumType>
        {
            public bool Equals(EnumType lhs, EnumType rhs)
            {
                return lhs.Equals(rhs);
            }

            public int GetHashCode(EnumType x)
            {
                return x.GetHashCode();
            }
        }

        private List<EnumClass> Enums;
        private Dictionary<string, EnumClass> StringMap;
        private Dictionary<EnumType, EnumClass> TypeMap;

        public int Count
        {
            get { return Enums.Count; }
        }

        public ECgEnumMaskMap()
        {
            Enums = new List<EnumClass>();
            StringMap = new Dictionary<string, EnumClass>();
            TypeMap = new Dictionary<EnumType, EnumClass>(new EnumTypeEqualityComparer());
        }

        public EnumClass Create(string name)
        {
            EnumClass e = null;

            StringMap.TryGetValue(name, out e);

            if (e != null)
            {
                CgDebug.LogError(this.GetType().Name + ".Create: Enum with name: " + name + " already exists. It is being defined in move than one place.");
                return e;
            }

            Type type = typeof(EnumClass);
            // Get Constructor
            Type[] types = new Type[2];
            types[0] = typeof(EnumType);
            types[1] = typeof(string);
            ConstructorInfo constructor = type.GetConstructor(types);

            // Get Params for Constructor and create EnumClass
            object[] param = new object[2];
            param[0] = (EnumType)Convert.ChangeType(Enums.Count, typeof(EnumType));
            param[1] = name;
            e = (EnumClass)constructor.Invoke(param);

            // Add to List and Maps
            EnumType index = (EnumType)Convert.ChangeType(Enums.Count, typeof(EnumType));

            Enums.Add(e);
            StringMap.Add(name, e);
            TypeMap.Add(index, e);

            return e;
        }

        public EnumClass this[string key]
        {
            get
            {
                EnumClass e = null;
                StringMap.TryGetValue(key, out e);

                if (e == null)
                    CgDebug.LogError(this.GetType().Name + ".Get: No enum created of type: " + typeof(EnumClass).Name + " and name: " + key);
                return e;
            }
        }

        public EnumClass this[EnumType key]
        {
            get
            {
                EnumClass e = null;
                TypeMap.TryGetValue(key, out e);

                if (e == null)
                    CgDebug.LogError(this.GetType().Name + ".Get: No enum created of type: " + typeof(EnumClass).Name + " and name: " + key);
                return e;
            }
        }

        public int ToMask(string s)
        {
            int mask = 0;

            Dictionary<string, EnumClass>.KeyCollection keys = StringMap.Keys;

            foreach (string key in keys)
            {
                if (s.Contains(key))
                {
                    int value = (int)Convert.ChangeType(StringMap[key].Value, typeof(int));
                    mask     |= value;
                }
            }
            return mask;
        }

        public string MaskToStr(int m)
        {
            string s = "";

            Dictionary<string, EnumClass>.KeyCollection keys = StringMap.Keys;

            foreach (string key in keys)
            {
                int value = (int)Convert.ChangeType(StringMap[key].Value, typeof(int));

                if ((m & value) == value)
                    s += s == "" ? key : " | " + key;
            }
            return s;
        }
    }

    #endregion // Enums

    #region "Primitive Types"

    public interface ICgProperty
    {
        void UpdateIsDirty();
        void Clear();
        void ResetValue();
        void Reset();
        bool HasChanged();
        void MarkDirty();
        void Resolve();
    }

    public abstract class CgProperty : ICgProperty
    {
        public abstract void UpdateIsDirty();
        public abstract void Clear();
        public abstract void ResetValue();
        public abstract void Reset();
        public abstract bool HasChanged();
        public abstract void MarkDirty();
        public abstract void Resolve();
    }

    public class TCgPropertyType<T> : CgProperty 
        where T : struct
    {
        public sealed class OnChange : TCgMulticastDelegate_OneParam<T> { }

        #region "Data Members"

        public T Value;
        public T Last_Value;

        protected bool IsDirty;

        public OnChange OnChange_Event;

        #endregion // Data Members

        public TCgPropertyType()
        {
            OnChange_Event = new OnChange();
        }

        #region "Operators"

        public static bool operator ==(TCgPropertyType<T> lhs, TCgPropertyType<T> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Value.Equals(rhs.Value);
        }

        public static bool operator !=(TCgPropertyType<T> lhs, TCgPropertyType<T> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgPropertyType<T> lhs, T rhs)
        {
            return lhs.Value.Equals(rhs);
        }

        public static bool operator !=(TCgPropertyType<T> lhs, T rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(T lhs, TCgPropertyType<T> rhs)
        {
            return lhs.Equals(rhs.Value);
        }

        public static bool operator !=(T lhs, TCgPropertyType<T> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgPropertyType<T>))
                return false;

            TCgPropertyType<T> rhs = (TCgPropertyType<T>)obj;

            if (!Value.Equals(rhs.Value)) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Value.GetHashCode();
        }

        #endregion // Operators

        public override void UpdateIsDirty()
        {
            IsDirty = !Value.Equals(Last_Value);

            if (IsDirty)
                OnChange_Event.Broadcast(Value);
        }

        public void Set(T inValue)
        {
            Value = inValue;
            UpdateIsDirty();
        }

        public T Get() { return Value; }

        public override void Clear()
        {
            Last_Value = Value;
            IsDirty = false;
        }

        public override void ResetValue()
        {
            Value = default(T);
            Last_Value = Value;
            IsDirty = false;
        }

        public override void Reset()
        {
            ResetValue();

            OnChange_Event.Clear();
        }

        public override bool HasChanged() { return IsDirty; }
        public override void MarkDirty() { IsDirty = true; }

        public override void Resolve()
        {
            UpdateIsDirty();
            Clear();
        }
    }
    
    #region "Map"

    public class TCgProperty_TMap<KeyType, ValueType>
        where T : struct
    {
	    public ValueType DefaultValue;
        public ValueType Value;
        public ValueType Last_Value;

        public Dictionary<KeyType, ValueType> Values;
        public Dictionary<KeyType, ValueType> Last_Values;

        protected:
	bool IsDirty;

        TMap<KeyType, bool> IsDirtys;
        public:
	TBaseDelegate<ValueType, const KeyType&> GetDelegate;
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const KeyType&, const ValueType&> OnChangeMap_Event;

public:

	TCsProperty_TMap() { }
        virtual ~TCsProperty_TMap() { }

        void SetDefaultValue(const ValueType& InDefaultValue)
	{
		DefaultValue = InDefaultValue;
	}

    void Init(const KeyType &Key)
    {
        Values.Add(Key, DefaultValue);
        Last_Values.Add(Key, DefaultValue);
        IsDirtys.Add(Key, false);
    }

    FORCEINLINE virtual void UpdateIsDirty()
    {
        IsDirty = Value != Last_Value;

        if (IsDirty)
            OnChange_Event.Broadcast(Value);
    }

    FORCEINLINE virtual void UpdateIsDirtys(const KeyType &Key)
    {
        IsDirtys[Key] = Values[Key] != Last_Values[Key];

        if (IsDirtys[Key])
            OnChangeMap_Event.Broadcast(Key, Values[Key]);
    }

    FORCEINLINE TCsProperty_TMap& operator=(const TCsProperty_TMap& B)
    {
        Value = B.Value;
        UpdateIsDirty();

        TArray<KeyType> Keys;
        Values.GetKeys(Keys);

        for (const KeyType&Key : Keys)
		{
            Values[Key] = B.Values[Key];
            UpdateIsDirtys(Key);
        }
        return *this;
    }

    FORCEINLINE bool operator ==(const TCsProperty_TMap& B) const
	{
		TArray<KeyType> Keys;
    Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			if (Values[Key] != B.Values[Key])
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator !=(const TCsProperty_TMap& B) const
	{
		return !(*this == B);
}

FORCEINLINE void Set(const ValueType &InValue)
{
    Value = InValue;
    UpdateIsDirty();
}

FORCEINLINE void Set(const KeyType& Key, const ValueType &InValue)
{
    Values[Key] = InValue;
    UpdateIsDirtys(Key);
}

FORCEINLINE const ValueType& operator[] (const KeyType &Key)
{
    return Values[Key];
}

FORCEINLINE const ValueType& Get() { return Value; }
FORCEINLINE const ValueType& Get(const KeyType& Key) { return Values[Key]; }

FORCEINLINE ValueType GetEX(const KeyType &Key) { return GetDelegate.Execute(Key); }

void Clear()
{
    Last_Value = Value;
    IsDirty = false;

    TArray<KeyType> Keys;
    Values.GetKeys(Keys);

    for (const KeyType&Key : Keys)
		{
        Last_Values[Key] = Values[Key];
        IsDirtys[Key] = false;
    }
}

void ResetValues()
{
    Value = DefaultValue;
    Last_Value = Value;
    IsDirty = false;

    TArray<KeyType> Keys;
    Values.GetKeys(Keys);

    for (const KeyType&Key : Keys)
		{
        Values[Key] = Value;
        Last_Values[Key] = Value;
        IsDirtys[Key] = false;
    }
}

void Reset()
{
    ResetValues();

    GetDelegate.Unbind();
    OnChange_Event.Clear();
    OnChangeMap_Event.Clear();
}

FORCEINLINE bool HasChanged() { return IsDirty; }
FORCEINLINE bool HasChanged(const KeyType &Key) { return IsDirtys[Key]; }

FORCEINLINE void Resolve()
{
    UpdateIsDirty();

    TArray<KeyType> Keys;
    Values.GetKeys(Keys);

    for (const KeyType&Key : Keys)
		{
        UpdateIsDirtys(Key);
    }
    Clear();
}
};

template<typename KeyType, typename ValueType>
struct TCsIntegralType_TMap : public TCsProperty_TMap<KeyType, ValueType>
{
	TCsIntegralType_TMap() { }
~TCsIntegralType_TMap() { }

FORCEINLINE void Add(const ValueType& InValue)
{
    Value += InValue;
    UpdateIsDirty();
}

FORCEINLINE void Add(const KeyType &Key, const ValueType &InValue)
{
    Values[Key] += InValue;
    UpdateIsDirtys(Key);
}

FORCEINLINE void Subtract(const ValueType &InValue)
{
    Value -= InValue;
    UpdateIsDirty();
}

FORCEINLINE void Subtract(const KeyType &Key, const ValueType &InValue)
{
    Values[Index] -= inValue;
    UpdateIsDirtys(Index);
}

FORCEINLINE ValueType Max()
{
    TArray<KeyType> Keys;
    Values.GetKeys(Keys);

    ValueType max = Values[Keys[0]];

    const uint8 Count = Keys.Num();

    for (uint8 I = 1; I < Count; ++I)
    {
        max = (KeyType)FMath::Max(max, Values[Keys[I]]);
    }
    return max;
}

FORCEINLINE ValueType Min()
{
    TArray<KeyType> Keys;
    Values.GetKeys(Keys);

    ValueType min = Values[Keys[0]];

    const uint8 Count = Keys.Num();

    for (uint8 I = 1; I < Count; ++I)
    {
        min = (ValueType)FMath::Min(min, Values[Keys[I]]);
    }
    return min;
}
};

template<typename KeyType>
struct TCsIntegralType_TMap_uint8 : public TCsIntegralType_TMap<KeyType, uint8>
{
	TCsIntegralType_TMap_uint8()
{
    DefaultValue = 0;
}
~TCsIntegralType_TMap_uint8() { }
};

template<typename KeyType>
struct TCsIntegralType_TMap_float : public TCsIntegralType_TMap<KeyType, float>
{
	TCsIntegralType_TMap_float()
{
    DefaultValue = 0.0f;
}
~TCsIntegralType_TMap_float() { }
};

template<typename KeyType>
struct TCsProperty_TMap_bool : public TCsProperty_TMap<KeyType, bool>
{
	TCsProperty_TMap_bool()
{
    DefaultValue = false;
}
~TCsProperty_TMap_bool() { }

FORCEINLINE bool Or()
{
    TArray<KeyType> Keys;
    Values.GetKeys(Keys);

    bool or = Values[Keys[0]];

    const uint8 Count = Keys.Num();

    for (uint8 I = 1; I < Count; ++I)
    {
        or |= Values[Keys[I]];
    }
    return or;
}

FORCEINLINE bool And()
{
    TArray<KeyType> Keys;
    Values.GetKeys(Keys);

    bool and = Values[Keys[0]];

    const uint8 Count = Keys.Num();

    for (uint8 I = 1; I < Count; ++I)
    {
        and &= Values[Keys[I]];
    }
    return and;
}
};

        #endregion // Map

    #endregion // Primitive Types

    #region "Primitive Classes"

    public class TCgPropertyClass<T> : CgProperty where T : class
    {
        public sealed class OnChange : TCgMulticastDelegate_OneParam<T> { }

        #region "Data Members"

        public T Value;
        public T Last_Value;

        protected bool IsDirty;

        public OnChange OnChange_Event;

        #endregion // Data Members

        public TCgPropertyClass()
        {
            OnChange_Event = new OnChange();
        }

        #region "Operators"

        public static bool operator ==(TCgPropertyClass<T> lhs, TCgPropertyClass<T> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Value.Equals(rhs.Value);
        }

        public static bool operator !=(TCgPropertyClass<T> lhs, TCgPropertyClass<T> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgPropertyClass<T> lhs, T rhs)
        {
            return lhs.Value.Equals(rhs);
        }

        public static bool operator !=(TCgPropertyClass<T> lhs, T rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(T lhs, TCgPropertyClass<T> rhs)
        {
            return lhs.Equals(rhs.Value);
        }

        public static bool operator !=(T lhs, TCgPropertyClass<T> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgPropertyClass<T>))
                return false;

            TCgPropertyClass<T> rhs = (TCgPropertyClass<T>)obj;

            if (!Value.Equals(rhs.Value)) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Value.GetHashCode();
        }

        #endregion // Operators

        public override void UpdateIsDirty()
        {
            IsDirty = !Value.Equals(Last_Value);

            if (IsDirty)
                OnChange_Event.Broadcast(Value);
        }

        public void Set(T inValue)
        {
            Value = inValue;
            UpdateIsDirty();
        }

        public T Get() { return Value; }

        public override void Clear()
        {
            Last_Value = Value;
            IsDirty = false;
        }

        public override void ResetValue()
        {
            Value = default(T);
            Last_Value = Value;
            IsDirty = false;
        }

        public override void Reset()
        {
            ResetValue();

            OnChange_Event.Clear();
        }

        public override bool HasChanged() { return IsDirty; }
        public override void MarkDirty() { IsDirty = true; }

        public override void Resolve()
        {
            UpdateIsDirty();
            Clear();
        }
    }

    #endregion // Primitive Classes

    #region "Flags"

    public interface ICgFlag
    {
        bool IsEqual();
    }

    public abstract class CgFlag : ICgFlag
    {
        public abstract bool IsEqual();
    }

    public class TCgFlagType<T> : CgFlag where T : struct
    {
        public sealed class OnEqual : CgMulticastDelegate { }

        #region "Data Members"

        public T StartValue;
        public T EndValue;

        public OnEqual OnEqual_Event;

        #endregion // Data Members

        public TCgFlagType(T startValue, T endValue)
        {
            StartValue    = startValue;
            EndValue      = endValue;
            OnEqual_Event = new OnEqual();
        }

        #region "Operators"

        public static bool operator ==(TCgFlagType<T> lhs, TCgFlagType<T> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.StartValue.Equals(rhs.StartValue);
        }

        public static bool operator !=(TCgFlagType<T> lhs, TCgFlagType<T> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgFlagType<T> lhs, T rhs)
        {
            return lhs.StartValue.Equals(rhs);
        }

        public static bool operator !=(TCgFlagType<T> lhs, T rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(T lhs, TCgFlagType<T> rhs)
        {
            return lhs.Equals(rhs.StartValue);
        }

        public static bool operator !=(T lhs, TCgFlagType<T> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgFlagType<T>))
                return false;

            TCgFlagType<T> rhs = (TCgFlagType<T>)obj;

            if (!StartValue.Equals(rhs.StartValue)) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return StartValue.GetHashCode();
        }

        #endregion // Operators

        public void Init(T startValue, T endValue)
        {
            StartValue = startValue;
            EndValue = endValue;
        }

        public void SetStart(T startValue)
        {
            StartValue = startValue;
        }

        public void SetEnd(T endValue)
        {
            EndValue = endValue;

            if (StartValue.Equals(EndValue))
                OnEqual_Event.Broadcast();
        }

        public T GetStart() { return StartValue; }
        public T GetEnd() { return EndValue; }

        public void ResetValues()
        {
            StartValue = default(T);
            EndValue = default(T);
        }

        public void Reset()
        {
            ResetValues();

            OnEqual_Event.Clear();
        }

        public override bool IsEqual() { return StartValue.Equals(EndValue); }
    }

    #endregion "Flags"

    #region "Attribute"

    public class TCgAttributeValue<T> where T : struct
    {
        public T Value;
        public T UnSetValue;
        public bool IsSet;

        public TCgAttributeValue(T value)
        {
            Value = value;
            UnSetValue = default(T);
            IsSet = true;
        }

        public void Set(T value)
        {
            Value = value;
            IsSet = true;
        }

        public void UnSet()
        {
            Value = UnSetValue;
            IsSet = false;
        }

        public bool IsValid()
        {
            return IsSet ? !Value.Equals(UnSetValue) : true;
        }
    }

    public class TCgAttributeRef<T> where T : class
    {
        public T Ref;
        public T UnSetRef;
        public bool IsSet;

        public TCgAttributeRef(T inRef)
        {
            Ref = inRef;
            UnSetRef = default(T);
            IsSet = true;
        }

        public void Set(T inRef)
        {
            Ref = inRef;
            IsSet = true;
        }

        public void UnSet()
        {
            Ref = UnSetRef;
            IsSet = false;
        }

        public bool IsValid()
        {
            return IsSet ? Ref != UnSetRef : true;
        }
    }
    
    public sealed class CgAttribute
    {
        private Type ValueType;
        private object Value;
        private object UnSetValue;
        private bool IsSet;

        public CgAttribute()
        {
            ValueType = null;
            Value = null;
            UnSetValue = null;
            IsSet = false;
        }

        public void Set(object value)
        {
            Value      = value;
            ValueType  = value != null ? value.GetType() : null;
            UnSetValue = ValueType != null ? default(ValueType) : null;

            if (ValueType != null &&
                ValueType.IsClass)
            {
                if (value.Equals(null))
                {
                    IsSet = false;
                }
                else
                {
                    IsSet = true;
                }
            }
        }

        public void UnSet()
        {
            ValueType  = null;
            Value      = null;
            UnSetValue = null;
            IsSet      = false;
        }

        public bool IsValid()
        {
            return IsSet ? !Value.Equals(UnSetValue) : true;
        }

        public object Get()
        {
            return Value;
        }
    }

    #endregion // Attribute
}
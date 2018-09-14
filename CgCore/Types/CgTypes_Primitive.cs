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

    public abstract class TCgEnum<T> : System.Object, ICgEnum where T : struct, IConvertible
    {
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

        #region "Operators"

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

        #endregion // Operators

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

    [Serializable]
    public class FECgEnum_byte : TCgEnum<byte>
    {
        public FECgEnum_byte() : base() { }
        public FECgEnum_byte(byte value) : base(value) { }
        public FECgEnum_byte(byte value, string name) : base(value, name) { }
    }

    [Serializable]
    public class ECgEnum_int : TCgEnum<int>
    {
        public ECgEnum_int() : base() { }
        public ECgEnum_int(int value) : base(value) { }
        public ECgEnum_int(int value, string name) : base(value, name) { }

        public static int operator &(ECgEnum_int lhs, int rhs)
        {
            return lhs.Value & rhs;
        }

        public static int operator &(int lhs, ECgEnum_int rhs)
        {
            return lhs & rhs.Value;
        }

        public static int operator |(ECgEnum_int lhs, int rhs)
        {
            return lhs.Value & rhs;
        }

        public static int operator |(int lhs, ECgEnum_int rhs)
        {
            return lhs & rhs.Value;
        }
    }

    [Serializable]
    public class ECgEnum_uint : TCgEnum<uint>
    {
        public ECgEnum_uint() : base() { }
        public ECgEnum_uint(uint value) : base(value) { }
        public ECgEnum_uint(uint value, string name) : base(value, name) { }
    }

    public class TCgEnumMap<EnumClass, EnumType>
        where EnumClass : TCgEnum<EnumType>
        where EnumType : struct, IConvertible
    {
        protected sealed class FEnumTypeEqualityComparer : IEqualityComparer<EnumType>
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

        public TCgEnumMap()
        {
            Enums = new List<EnumClass>();
            StringMap = new Dictionary<string, EnumClass>();
            TypeMap = new Dictionary<EnumType, EnumClass>(new FEnumTypeEqualityComparer());
        }

        public EnumClass Create(string name)
        {
            EnumClass e = null;

            StringMap.TryGetValue(name, out e);

            if (e != null)
            {
                FCgDebug.LogError(this.GetType().Name + ".Create: Enum with name: " + name + " already exists. It is being defined in more than one place.");
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

            param[0] = (EnumType)Convert.ChangeType(Enums.Count + 1, typeof(EnumType));
            Max      = (EnumClass)constructor.Invoke(param);

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
                    FCgDebug.LogError(this.GetType().Name + ".Get: No enum created of type: " + typeof(EnumClass).Name + " and name: " + key);
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
                    FCgDebug.LogError(this.GetType().Name + ".Get: No enum created of type: " + typeof(EnumClass).Name + " and name: " + key);
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

    public class TCgEnumMaskMap<EnumClass, EnumType>
        where EnumClass : TCgEnum<EnumType>
        where EnumType : struct, IConvertible
    {
        protected sealed class FEnumTypeEqualityComparer : IEqualityComparer<EnumType>
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
        private Dictionary<int, EnumClass> MaskMap;
        private EnumClass None;

        public int Count
        {
            get { return Enums.Count; }
        }

        public TCgEnumMaskMap()
        {
            Enums = new List<EnumClass>();
            StringMap = new Dictionary<string, EnumClass>();
            TypeMap = new Dictionary<EnumType, EnumClass>(new FEnumTypeEqualityComparer());
            MaskMap = new Dictionary<int, EnumClass>();

            Type type = typeof(EnumClass);
            // Get Constructor
            Type[] types = new Type[2];
            types[0] = typeof(EnumType);
            types[1] = typeof(string);
            ConstructorInfo constructor = type.GetConstructor(types);

            // Get Params for Constructor and create EnumClass
            object[] param = new object[2];
            param[0] = (EnumType)Convert.ChangeType(0, typeof(EnumType));
            param[1] = "None";

            None = (EnumClass)constructor.Invoke(param);
        }

        public EnumClass Create(string name)
        {
            EnumClass e = null;

            StringMap.TryGetValue(name, out e);

            if (e != null)
            {
                FCgDebug.LogError(this.GetType().Name + ".Create: Enum with name: " + name + " already exists. It is being defined in more than one place.");
                return e;
            }

            if (name == "None")
            {
                FCgDebug.LogError(this.GetType().Name + ".Create: Enum with name: None is reserved and already exists.");
                return None;
            }

            Type type = typeof(EnumClass);
            // Get Constructor
            Type[] types = new Type[2];
            types[0] = typeof(EnumType);
            types[1] = typeof(string);
            ConstructorInfo constructor = type.GetConstructor(types);

            // Get Params for Constructor and create EnumClass
            object[] param = new object[2];
            int mask = 1 << Enums.Count;
            param[0] = (EnumType)Convert.ChangeType(mask, typeof(EnumType));
            param[1] = name;
            e = (EnumClass)constructor.Invoke(param);

            // Add to List and Maps
            EnumType index = (EnumType)Convert.ChangeType(Enums.Count, typeof(EnumType));

            Enums.Add(e);
            StringMap.Add(name, e);
            TypeMap.Add(index, e);
            MaskMap.Add(mask, e);

            return e;
        }

        public EnumClass this[string key]
        {
            get
            {
                EnumClass e = null;
                StringMap.TryGetValue(key, out e);

                if (e == null)
                    FCgDebug.LogError(this.GetType().Name + ".Get: No enum created of type: " + typeof(EnumClass).Name + " and name: " + key);
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
                    FCgDebug.LogError(this.GetType().Name + ".Get: No enum created of type: " + typeof(EnumClass).Name + " and name: " + key);
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
            return index < Count ? Enums[index] : None;
        }

        public EnumClass GetEnum(string name)
        {
            return StringMap[name];
        }

        public EnumClass GetSafeEnum(string name)
        {
            return IsValidEnum(name) ? StringMap[name] : None;
        }

        public EnumClass GetEnum(EnumType type)
        {
            return TypeMap[type];
        }

        public bool IsValidMask(int mask)
        {
            return MaskMap.ContainsKey(mask);
        }

        public EnumClass GetEnumByMask(int mask)
        {
            return MaskMap[mask];
        }

        public EnumClass GetSafeEnumByMask(int mask)
        {
            return IsValidMask(mask) ? MaskMap[mask] : None;
        }

        public EnumClass GetNone()
        {
            return None;
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

    #region "Property"

        #region "Default"

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

    public class TCgProperty<ValueType> : CgProperty 
        where ValueType : struct
    {
        public sealed class OnChange : TCgMulticastDelegate_OneParam<ValueType> { }

        #region "Data Members"

        public ValueType DefaultValue;
        public ValueType Value;
        public ValueType Last_Value;

        protected bool IsDirty;

        public OnChange OnChange_Event;

        #endregion // Data Members

        public TCgProperty()
        {
            DefaultValue = default(ValueType);
            Value = DefaultValue;
            Last_Value = Value;

            IsDirty = false;

            OnChange_Event = new OnChange();
        }

        #region "Operators"

        public static bool operator ==(TCgProperty<ValueType> lhs, TCgProperty<ValueType> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Value.Equals(rhs.Value);
        }

        public static bool operator !=(TCgProperty<ValueType> lhs, TCgProperty<ValueType> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgProperty<ValueType> lhs, ValueType rhs)
        {
            return lhs.Value.Equals(rhs);
        }

        public static bool operator !=(TCgProperty<ValueType> lhs, ValueType rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(ValueType lhs, TCgProperty<ValueType> rhs)
        {
            return lhs.Equals(rhs.Value);
        }

        public static bool operator !=(ValueType lhs, TCgProperty<ValueType> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgProperty<ValueType>))
                return false;

            TCgProperty<ValueType> rhs = (TCgProperty<ValueType>)obj;

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
            IsDirty    = !Value.Equals(Last_Value);
            Last_Value = Value;

            if (IsDirty)
                OnChange_Event.Broadcast(Value);
        }

        public void Set(ValueType inValue)
        {
            Value = inValue;
            UpdateIsDirty();
        }

        public ValueType Get() { return Value; }

        public override void Clear()
        {
            IsDirty = false;
        }

        public override void ResetValue()
        {
            Value = DefaultValue;
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

    public class FCgProperty_float : TCgProperty<float>
    {
        public FCgProperty_float() : base()
        {
            DefaultValue = 0.0f;
        }

        public static bool operator <(FCgProperty_float lhs, FCgProperty_float rhs)
	    {
		    return lhs.Value < rhs.Value;
	    }

        public static bool operator <(FCgProperty_float lhs, float rhs)
        {
            return lhs.Value < rhs;
        }

        public static bool operator <(float lhs, FCgProperty_float rhs)
        {
            return lhs < rhs.Value;
        }

        public static bool operator <=(FCgProperty_float lhs, FCgProperty_float rhs)
        {
            return lhs.Value <= rhs.Value;
        }

        public static bool operator <=(FCgProperty_float lhs, float rhs)
        {
            return lhs.Value <= rhs;
        }

        public static bool operator <=(float lhs, FCgProperty_float rhs)
        {
            return lhs <= rhs.Value;
        }

        public static bool operator >(FCgProperty_float lhs, FCgProperty_float rhs)
        {
            return lhs.Value > rhs.Value;
        }

        public static bool operator >(FCgProperty_float lhs, float rhs)
        {
            return lhs.Value > rhs;
        }

        public static bool operator >(float lhs, FCgProperty_float rhs)
        {
            return lhs > rhs.Value;
        }

        public static bool operator >=(FCgProperty_float lhs, FCgProperty_float rhs)
        {
            return lhs.Value >= rhs.Value;
        }

        public static bool operator >=(FCgProperty_float lhs, float rhs)
        {
            return lhs.Value >= rhs;
        }

        public static bool operator >=(float lhs, FCgProperty_float rhs)
        {
            return lhs >= rhs.Value;
        }

        public static float operator /(FCgProperty_float lhs, float rhs)
        {
            return lhs.Value / rhs;
        }

        public static float operator /(float lhs, FCgProperty_float rhs)
        {
            return lhs / rhs.Value;
        }

        public static float operator *(FCgProperty_float lhs, float rhs)
        {
            return lhs.Value * rhs;
        }

        public static float operator *(float lhs, FCgProperty_float rhs)
        {
            return lhs * rhs.Value;
        }
    }

        #endregion // Default

        #region "Ref"

    public class TCgProperty_Ref<ValueType> : CgProperty 
        where ValueType : struct
    {
        public sealed class FOnChange : TCgMulticastDelegate_OneParam<ValueType> { }

        #region "Data Members"

        public object Object;
        public PropertyInfo Info;
        public ValueType Last_Value;

        protected bool IsDirty;

        public FOnChange OnChange_Event;

        #endregion // Data Members

        public TCgProperty_Ref()
        {
            Object = null;
            Info = null;
            Last_Value = default(ValueType);

            IsDirty = false;

            OnChange_Event = new FOnChange();
        }

        #region "Operators"

        public static bool operator ==(TCgProperty_Ref<ValueType> lhs, TCgProperty_Ref<ValueType> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Get().Equals(rhs.Get());
        }

        public static bool operator !=(TCgProperty_Ref<ValueType> lhs, TCgProperty_Ref<ValueType> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgProperty_Ref<ValueType> lhs, ValueType rhs)
        {
            return lhs.Get().Equals(rhs);
        }

        public static bool operator !=(TCgProperty_Ref<ValueType> lhs, ValueType rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(ValueType lhs, TCgProperty_Ref<ValueType> rhs)
        {
            return lhs.Equals(rhs.Get());
        }

        public static bool operator !=(ValueType lhs, TCgProperty_Ref<ValueType> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgProperty_Ref<ValueType>))
                return false;

            TCgProperty_Ref<ValueType> rhs = (TCgProperty_Ref<ValueType>)obj;

            if (!Get().Equals(rhs.Get())) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Get().GetHashCode();
        }

        #endregion // Operators

        public override void UpdateIsDirty()
        {
            ValueType value = (ValueType)Info.GetValue(Object, null);
            IsDirty         = !value.Equals(Last_Value);
            Last_Value      = value;

            if (IsDirty)
                OnChange_Event.Broadcast(value);
        }

        public void Set(Object o, string propertyName)
        {
            Object = o;
            Info = o.GetType().GetProperty(propertyName);
            UpdateIsDirty();
        }

        public void Set(ValueType value)
        {
            Info.SetValue(Object, value, null);
            UpdateIsDirty();
        }

        public ValueType Get() { return (ValueType)Info.GetValue(Object, null); }

        public override void Clear()
        {
            IsDirty = false;
        }

        public override void ResetValue()
        {
            Object = null;
            Info = null;
            Last_Value = default(ValueType);
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

    public class FCgProperty_Ref_bool : TCgProperty_Ref<bool>
    {
        public FCgProperty_Ref_bool() : base() { }
    }

    // Short hand to mimic typedef
    public sealed class FCgBool_Ref : FCgProperty_Ref_bool { }

    public class FCgProperty_Ref_int : TCgProperty_Ref<int>
    {
        public FCgProperty_Ref_int() : base() { }

        public static bool operator <(FCgProperty_Ref_int lhs, FCgProperty_Ref_int rhs)
        {
            return lhs.Get() < rhs.Get();
        }

        public static bool operator >(FCgProperty_Ref_int lhs, FCgProperty_Ref_int rhs)
        {
            return lhs.Get() > rhs.Get();
        }

        public static bool operator >(FCgProperty_Ref_int lhs, int rhs)
        {
            return lhs.Get() > rhs;
        }

        public static bool operator <(FCgProperty_Ref_int lhs, int rhs)
        {
            return lhs.Get() < rhs;
        }

        public static bool operator >(int lhs, FCgProperty_Ref_int rhs)
        {
            return lhs > rhs.Get();
        }

        public static bool operator <(int lhs, FCgProperty_Ref_int rhs)
        {
            return lhs < rhs.Get();
        }
    }

    public class FCgProperty_Ref_float : TCgProperty_Ref<float>
    {
        public FCgProperty_Ref_float() : base() { }

        public static bool operator <(FCgProperty_Ref_float lhs, FCgProperty_Ref_float rhs)
        {
            return lhs.Get() < rhs.Get();
        }

        public static bool operator >(FCgProperty_Ref_float lhs, FCgProperty_Ref_float rhs)
        {
            return lhs.Get() > rhs.Get();
        }

        public static bool operator >(FCgProperty_Ref_float lhs, float rhs)
        {
            return lhs.Get() > rhs;
        }

        public static bool operator <(FCgProperty_Ref_float lhs, float rhs)
        {
            return lhs.Get() < rhs;
        }

        public static bool operator >(float lhs, FCgProperty_Ref_float rhs)
        {
            return lhs > rhs.Get();
        }

        public static bool operator <(float lhs, FCgProperty_Ref_float rhs)
        {
            return lhs < rhs.Get();
        }
    }

        #endregion // Ref

        #region "List"

    public class TCgProperty_TList<ValueType>
       where ValueType : struct, IConvertible
    {
        public sealed class FGet : TCgDelegate_Ret_OneParam<ValueType, int> { }
        public sealed class FOverride_Get : TCgDelegate_Ret_OneParam<ValueType, int> { }
        public sealed class FOverride_Subscript : TCgDelegate_Ret_OneParam<ValueType, int> { }
        public sealed class FOnChange : TCgMulticastDelegate_OneParam<ValueType> { }
        public sealed class FOnChangeList : TCgMulticastDelegate_TwoParams<int, ValueType> { }

        public ValueType DefaultValue;
        public ValueType Value;
        public ValueType Last_Value;

        public List<ValueType> Values;
        public List<ValueType> Last_Values;

        protected byte SIZE;
        protected bool IsDirty;

        protected List<bool> IsDirtys;

        public FGet Get_Call;
        public FOverride_Get Override_Get;
        public FOverride_Subscript Override_Subscript;
        public FOnChange OnChange_Event;
        public FOnChangeList OnChangeList_Event;

        public TCgProperty_TList()
        {
            DefaultValue = default(ValueType);
            Value = DefaultValue;
            Last_Value = Value;

            Values = new List<ValueType>();
            Last_Values = new List<ValueType>();

            IsDirtys = new List<bool>();

            Get_Call = new FGet();
            Override_Get = new FOverride_Get();
            Override_Subscript = new FOverride_Subscript();
            OnChange_Event = new FOnChange();
            OnChangeList_Event = new FOnChangeList();
        }

        public void SetDefaultValue(ValueType defaultValue)
        {
            DefaultValue = defaultValue;
        }

        public void Init(byte size)
        {
            for (int i = 0; i < size; ++i)
            {
                Values.Add(DefaultValue);
                Last_Values.Add(DefaultValue);
                IsDirtys.Add(false);
            }
        }

        public virtual void UpdateIsDirty()
        {
            IsDirty = !Value.Equals(Last_Value);
            Last_Value = Value;

            if (IsDirty)
                OnChange_Event.Broadcast(Value);
        }

        public virtual void UpdateIsDirtys(int index)
        {
            IsDirtys[index] = !Values[index].Equals(Last_Values[index]);
            Last_Values[index] = Values[index];

            if (IsDirtys[index])
                OnChangeList_Event.Broadcast(index, Values[index]);
        }
        /*
        bool operator ==(const TCsProperty_TMap& B) const
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

	     bool operator !=(const TCsProperty_TMap& B) const
	    {
		    return !(*this == B);
        }
        */

        public void Set(ValueType value)
        {
            Value = value;
            UpdateIsDirty();
        }

        public void Set(int index, ValueType value)
        {
            Values[index] = value;
            UpdateIsDirtys(index);
        }

        public ValueType this[int index]
        {
            get
            {
                if (Override_Subscript.IsBound())
                    return Override_Subscript.Execute(index);
                return Values[index];
            }
            set
            {
                Values[index] = value;
                UpdateIsDirtys(index);
            }
        }

        public ValueType Get() { return Value; }
        public ValueType Get(int index)
        {
            if (Override_Get.IsBound())
                return Override_Get.Execute(index);
            return Values[index];
        }

        public ValueType GetEX(int index) { return Get_Call.Execute(index); }

        public void Clear()
        {
            IsDirty = false;

            for (int i = 0; i < SIZE; ++i)
            {
                IsDirtys[i] = false;
            }
        }

        public void ResetValues()
        {
            Value = DefaultValue;
            Last_Value = Value;
            IsDirty = false;

            for (int i = 0; i < SIZE; ++i)
            {
                Values[i] = Value;
                Last_Values[i] = Value;
                IsDirtys[i] = false;
            }
        }

        public void Reset()
        {
            ResetValues();

            Get_Call.Unbind();
            Override_Get.Unbind();
            Override_Subscript.Unbind();
            OnChange_Event.Clear();
            OnChangeList_Event.Clear();
        }

        public bool HasChanged() { return IsDirty; }
        public bool HasChanged(int index) { return IsDirtys[index]; }

        public void Resolve()
        {
            UpdateIsDirty();

            for (int i = 0; i < SIZE; ++i)
            {
                UpdateIsDirtys(i);
            }
            Clear();
        }
    }

        #endregion // List

        #region "List Ref"

    public class TCgProperty_TListRef<ValueType>
        where ValueType : struct, IConvertible
    {
        public sealed class FGet : TCgDelegate_Ret_OneParam<ValueType, int> { }
        public sealed class FOverride_Get : TCgDelegate_Ret_OneParam<ValueType, int> { }
        public sealed class FOverride_Subscript : TCgDelegate_Ret_OneParam<ValueType, int> { }
        public sealed class FOnChange : TCgMulticastDelegate_OneParam<ValueType> { }
        public sealed class FOnChangeList : TCgMulticastDelegate_TwoParams<int, ValueType> { }

        public ValueType DefaultValue;
        public ValueType Value;
        public ValueType Last_Value;

        public List<object> Objects;
        public List<PropertyInfo> PropertyInfos;
        public List<ValueType> Last_Values;

        protected byte SIZE;
	    protected bool IsDirty;

        protected List<bool> IsDirtys;

	    public FGet Get_Call;
        public FOverride_Get Override_Get;
        public FOverride_Subscript Override_Subscript;
	    public FOnChange OnChange_Event;
	    public FOnChangeList OnChangeList_Event;

	    public TCgProperty_TListRef()
        {
            DefaultValue = default(ValueType);
            Value = DefaultValue;
            Last_Value = Value;

            Objects = new List<object>();
            PropertyInfos = new List<PropertyInfo>();
            Last_Values = new List<ValueType>();

            IsDirtys = new List<bool>();

            Get_Call = new FGet();
            Override_Get = new FOverride_Get();
            Override_Subscript = new FOverride_Subscript();
            OnChange_Event = new FOnChange();
            OnChangeList_Event = new FOnChangeList();
        }

        public void SetDefaultValue(ValueType defaultValue)
        {
            DefaultValue = defaultValue;
        }

        public void Init(byte size)
        {
            for (int i = 0; i < size; ++i)
            {
                Objects.Add(null);
                PropertyInfos.Add(null);
                Last_Values.Add(DefaultValue);
                IsDirtys.Add(false);
            }
        }

        public virtual void UpdateIsDirty()
        {
            IsDirty    = !Value.Equals(Last_Value);
            Last_Value = Value;

            if (IsDirty)
                OnChange_Event.Broadcast(Value);
        }

        public virtual void UpdateIsDirtys(int index)
        {
            ValueType value     = (ValueType)PropertyInfos[index].GetValue(Objects[index], null);
            IsDirtys[index]     = !value.Equals(Last_Values[index]);
            Last_Values[index]  = value;

            if (IsDirtys[index])
                OnChangeList_Event.Broadcast(index, value);
        }
        /*
        bool operator ==(const TCsProperty_TMap& B) const
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

	     bool operator !=(const TCsProperty_TMap& B) const
	    {
		    return !(*this == B);
        }
        */

        public void Set(ValueType value)
        {
            Value = value;
            UpdateIsDirty();
        }

        public void Set(int index, object o, string propertyName)
        {
            Objects[index] = o;
            PropertyInfos[index] = o.GetType().GetProperty(propertyName);
            UpdateIsDirtys(index);
        }

        public ValueType this[int index]
        {
            get
            {
                if (Override_Subscript.IsBound())
                    return Override_Subscript.Execute(index);
                return (ValueType)PropertyInfos[index].GetValue(Objects[index], null);
            }
        }

        public ValueType Get() { return Value; }
        public ValueType Get(int index)
        {
            if (Override_Get.IsBound())
                return Override_Get.Execute(index);
            return (ValueType)PropertyInfos[index].GetValue(Objects[index], null);
        }

        public ValueType GetEX(int index) { return Get_Call.Execute(index); }

        public void Clear()
        {
            IsDirty = false;

            for(int i = 0; i < SIZE; ++i)
		    {
                IsDirtys[i] = false;
            }
        }

        public void ResetValues()
        {
            Value = DefaultValue;
            Last_Value = Value;
            IsDirty = false;

            for (int i = 0; i < SIZE; ++i)
            {
                Objects[i] = null;
                PropertyInfos[i] = null;
                Last_Values[i] = Value;
                IsDirtys[i] = false;
            }
        }

        public void Reset()
        {
            ResetValues();

            Get_Call.Unbind();
            Override_Get.Unbind();
            Override_Subscript.Unbind();
            OnChange_Event.Clear();
            OnChangeList_Event.Clear();
        }

        public bool HasChanged() { return IsDirty; }
        public bool HasChanged(int index) { return IsDirtys[index]; }

        public void Resolve()
        {
            UpdateIsDirty();

            for (int i = 0; i < SIZE; ++i)
            {
                UpdateIsDirtys(i);
            }
            Clear();
        }
     }

    public class TCgIntegralType_TListRef<ValueType> : TCgProperty_TListRef<ValueType>
        where ValueType : struct, IConvertible
    {
        public TCgIntegralType_TListRef() : base() { }
    }

    public class TCgIntegralType_TListRef_int : TCgIntegralType_TListRef<int>
    {
        public TCgIntegralType_TListRef_int() : base() { }
    }

    public class TCgIntegralType_TListRef_float : TCgIntegralType_TListRef<float>
    {
        public TCgIntegralType_TListRef_float() : base() { }
    }

    public class TCgProperty_TListRef_bool : TCgProperty_TListRef<bool>
    {
        public TCgProperty_TListRef_bool() : base() { }
    }

    #endregion // List

        #region "Map"

    public class TCgProperty_TMap<KeyType, ValueType>
        where ValueType : struct, IConvertible
    {
        public sealed class FGet : TCgDelegate_Ret_OneParam<ValueType, KeyType> { }
        public sealed class FOnChange : TCgMulticastDelegate_OneParam<ValueType> { }
        public sealed class FOnChangeMap : TCgMulticastDelegate_TwoParams<KeyType, ValueType> { }

        public sealed class FKeyTypeEqualityComparer : IEqualityComparer<KeyType>
        {
            public bool Equals(KeyType lhs, KeyType rhs)
            {
                return lhs.Equals(rhs);
            }

            public int GetHashCode(KeyType x)
            {
                return x.GetHashCode();
            }
        }

        public ValueType DefaultValue;
        public ValueType Value;
        public ValueType Last_Value;

        public Dictionary<KeyType, ValueType> Values;
        public Dictionary<KeyType, ValueType> Last_Values;

	    protected bool IsDirty;

        protected Dictionary<KeyType, bool> IsDirtys;

	    public FGet Get_Call;
	    public FOnChange OnChange_Event;
	    public FOnChangeMap OnChangeMap_Event;

	    public TCgProperty_TMap()
        {
            Values = new Dictionary<KeyType, ValueType>(new FKeyTypeEqualityComparer());
            Last_Values = new Dictionary<KeyType, ValueType>(new FKeyTypeEqualityComparer());

            IsDirtys = new Dictionary<KeyType, bool>(new FKeyTypeEqualityComparer());

            Get_Call = new FGet();
            OnChange_Event = new FOnChange();
            OnChangeMap_Event = new FOnChangeMap();
        }

        public void SetDefaultValue(ValueType defaultValue)
        {
            DefaultValue = defaultValue;
        }

        public void Init(KeyType key)
        {
            Values.Add(key, DefaultValue);
            Last_Values.Add(key, DefaultValue);
            IsDirtys.Add(key, false);
        }

        public virtual void UpdateIsDirty()
        {
            IsDirty    = !Value.Equals(Last_Value);
            Last_Value = Value;

            if (IsDirty)
                OnChange_Event.Broadcast(Value);
        }

        public virtual void UpdateIsDirtys(KeyType key)
        {
            IsDirtys[key]     = !Values[key].Equals(Last_Values[key]);
            Last_Values[key] = Values[key];

            if (IsDirtys[key])
                OnChangeMap_Event.Broadcast(key, Values[key]);
        }
        /*
        bool operator ==(const TCsProperty_TMap& B) const
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

	     bool operator !=(const TCsProperty_TMap& B) const
	    {
		    return !(*this == B);
        }
        */

        public void Set(ValueType value)
        {
            Value = value;
            UpdateIsDirty();
        }

        public void Set(KeyType key, ValueType value)
        {
            Values[key] = value;
            UpdateIsDirtys(key);
        }

        public ValueType this[KeyType key]
        {
            get
            {
                return Values[key];
            }
            set
            {
                Values[key] = value;
                UpdateIsDirtys(key);
            }
        }

        public ValueType Get() { return Value; }
        public ValueType Get(KeyType key) { return Values[key]; }

        public ValueType GetEX(KeyType key) { return Get_Call.Execute(key); }

        public void Clear()
        {
            IsDirty = false;

            Dictionary<KeyType, ValueType>.KeyCollection keys = Values.Keys;

            foreach (KeyType key in keys)
		    {
                IsDirtys[key] = false;
            }
        }

        public void ResetValues()
        {
            Value = DefaultValue;
            Last_Value = Value;
            IsDirty = false;

            Dictionary<KeyType, ValueType>.KeyCollection keys = Values.Keys;

            foreach (KeyType key in keys)
            {
                Values[key] = Value;
                Last_Values[key] = Value;
                IsDirtys[key] = false;
            }
        }

        public void Reset()
        {
            ResetValues();

            Get_Call.Unbind();
            OnChange_Event.Clear();
            OnChangeMap_Event.Clear();
        }

        public bool HasChanged() { return IsDirty; }
        public bool HasChanged(KeyType key) { return IsDirtys[key]; }

        public void Resolve()
        {
            UpdateIsDirty();

            Dictionary<KeyType, ValueType>.KeyCollection keys = Values.Keys;

            foreach (KeyType key in keys)
            {
                UpdateIsDirtys(key);
            }
            Clear();
        }

        public void Copy(TCgProperty_TMap<KeyType, ValueType> from)
        {
            Value = from.Value;
            UpdateIsDirty();

            Dictionary<KeyType, ValueType>.KeyCollection keys = Values.Keys;

            foreach (KeyType key in keys)
            {
                Values[key] = from.Values[key];
                UpdateIsDirtys(key);
            }
        }
    }

    public class TCgIntegralType_TMap<KeyType, ValueType> : TCgProperty_TMap<KeyType, ValueType>
        where ValueType : struct, IConvertible
    {
        public TCgIntegralType_TMap() { }
        /*
        public void Add(ValueType value)
        {
            Value += value;
            UpdateIsDirty();
        }

        void Add(KeyType key, ValueType value)
        {
            Values[key] += value;
            UpdateIsDirtys(key);
        }
        
        void Subtract(ValueType value)
        {
            Value -= value;
            UpdateIsDirty();
        }

        void Subtract(KeyType key, ValueType value)
        {
            Values[key] -= value;
            UpdateIsDirtys(key);
        }

        ValueType Max()
        {
            Dictionary<KeyType, ValueType>.KeyCollection keys = Values.Keys;

            ValueType max = DefaultValue;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    max = Values[key];
                else
                  max = (ValueType)Math.Max(max, Values[key]);
                ++i;
            }
            return max;
        }

        ValueType Min()
        {
            Dictionary<KeyType, ValueType>.KeyCollection keys = Values.Keys;

            ValueType min = DefaultValue;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    min = Values[key];
                else
                    min = (ValueType)Math.Max(min, Values[key]);
                ++i;
            }
            return min;
        }
        */
    }

    public class TCgIntegralType_TMap_byte<KeyType> : TCgIntegralType_TMap<KeyType, byte>
    {
	    public TCgIntegralType_TMap_byte()
        {
            DefaultValue = 0;
        }

        public void Add(byte value)
        {
            Value += value;
            UpdateIsDirty();
        }

        public void Add(KeyType key, byte value)
        {
            Values[key] += value;
            UpdateIsDirtys(key);
        }
    }

    public class TCgIntegralType_TMap_float<KeyType> : TCgIntegralType_TMap<KeyType, float>
    {
	    public TCgIntegralType_TMap_float()
        {
            DefaultValue = 0.0f;
        }

        public float Max()
        {
            Dictionary<KeyType, float>.KeyCollection keys = Values.Keys;

            float max = DefaultValue;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    max = Values[key];
                else
                    max = (float)Math.Max(max, Values[key]);
                ++i;
            }
            return max;
        }

        public float Min()
        {
            Dictionary<KeyType, float>.KeyCollection keys = Values.Keys;

            float min = DefaultValue;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    min = Values[key];
                else
                    min = (float)Math.Max(min, Values[key]);
                ++i;
            }
            return min;
        }
    }

    public class TCgProperty_TMap_bool<KeyType> : TCgProperty_TMap<KeyType, bool>
    {
	    public TCgProperty_TMap_bool()
        {
            DefaultValue = false;
        }

        bool Or()
        {
            Dictionary<KeyType, bool>.KeyCollection keys = Values.Keys;

            bool or = false;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    or = Values[key];
                else
                   or |= Values[key];
                ++i;
            }
            return or;
        }

        bool And()
        {
            Dictionary<KeyType, bool>.KeyCollection keys = Values.Keys;

            bool and = false;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    and = Values[key];
                else
                    and &= Values[key];
                ++i;
            }
            return and;
        }
    }

        #endregion // Map

        #region "Map Ref"

    public class TCgProperty_TMapRef<KeyType, ValueType>
        where ValueType : struct, IConvertible
    {
        public sealed class FGet : TCgDelegate_Ret_OneParam<ValueType, KeyType> { }
        public sealed class FOverride_Get : TCgDelegate_Ret_OneParam<ValueType, KeyType> { }
        public sealed class FOverride_Subscript : TCgDelegate_Ret_OneParam<ValueType, KeyType> { }
        public sealed class FOnChange : TCgMulticastDelegate_OneParam<ValueType> { }
        public sealed class FOnChangeMap : TCgMulticastDelegate_TwoParams<KeyType, ValueType> { }

        public sealed class FKeyTypeEqualityComparer : IEqualityComparer<KeyType>
        {
            public bool Equals(KeyType lhs, KeyType rhs)
            {
                return lhs.Equals(rhs);
            }

            public int GetHashCode(KeyType x)
            {
                return x.GetHashCode();
            }
        }

        public ValueType DefaultValue;
        public ValueType Value;
        public ValueType Last_Value;

        public Dictionary<KeyType, object> Objects;
        public Dictionary<KeyType, PropertyInfo> PropertyInfos;
        public Dictionary<KeyType, ValueType> Last_Values;

	    protected bool IsDirty;

        protected Dictionary<KeyType, bool> IsDirtys;

	    public FGet Get_Call;
        public FOverride_Get Override_Get;
        public FOverride_Subscript Override_Subscript;
	    public FOnChange OnChange_Event;
	    public FOnChangeMap OnChangeMap_Event;

	    public TCgProperty_TMapRef()
        {
            Objects = new Dictionary<KeyType, object>(new FKeyTypeEqualityComparer());
            PropertyInfos = new Dictionary<KeyType, PropertyInfo>(new FKeyTypeEqualityComparer());
            Last_Values = new Dictionary<KeyType, ValueType>(new FKeyTypeEqualityComparer());

            IsDirtys = new Dictionary<KeyType, bool>(new FKeyTypeEqualityComparer());

            Get_Call = new FGet();
            Override_Get = new FOverride_Get();
            Override_Subscript = new FOverride_Subscript();
            OnChange_Event = new FOnChange();
            OnChangeMap_Event = new FOnChangeMap();
        }

        public void SetDefaultValue(ValueType defaultValue)
        {
            DefaultValue = defaultValue;
        }

        public void Init(KeyType key)
        {
            Objects.Add(key, null);
            PropertyInfos.Add(key, null);
            Last_Values.Add(key, DefaultValue);
            IsDirtys.Add(key, false);
        }

        public virtual void UpdateIsDirty()
        {
            IsDirty    = !Value.Equals(Last_Value);
            Last_Value = Value;

            if (IsDirty)
                OnChange_Event.Broadcast(Value);
        }

        public virtual void UpdateIsDirtys(KeyType key)
        {
            ValueType value = (ValueType)PropertyInfos[key].GetValue(Objects[key], null);
            IsDirtys[key]    = !value.Equals(Last_Values[key]);
            Last_Values[key] = value;

            if (IsDirtys[key])
                OnChangeMap_Event.Broadcast(key, value);
        }
        /*
        bool operator ==(const TCsProperty_TMap& B) const
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

	     bool operator !=(const TCsProperty_TMap& B) const
	    {
		    return !(*this == B);
        }
        */

        public void Set(ValueType value)
        {
            Value = value;
            UpdateIsDirty();
        }

        public void Set(KeyType key, object o, string propertyName)
        {
            Objects[key] = o;
            PropertyInfos[key] = o.GetType().GetProperty(propertyName);
            UpdateIsDirtys(key);
        }

        public ValueType this[KeyType key]
        {
            get
            {
                if (Override_Subscript.IsBound())
                    return Override_Subscript.Execute(key);
                return (ValueType)PropertyInfos[key].GetValue(Objects[key], null);
            }
        }

        public ValueType Get() { return Value; }
        public ValueType Get(KeyType key)
        {
            if (Override_Get.IsBound())
                return Override_Get.Execute(key);
            return (ValueType)PropertyInfos[key].GetValue(Objects[key], null);
        }

        public ValueType GetEX(KeyType key) { return Get_Call.Execute(key); }

        public void Clear()
        {
            IsDirty = false;

            Dictionary<KeyType, object>.KeyCollection keys = Objects.Keys;

            foreach (KeyType key in keys)
		    {
                IsDirtys[key] = false;
            }
        }

        public void ResetValues()
        {
            Value = DefaultValue;
            Last_Value = Value;
            IsDirty = false;

            Dictionary<KeyType, object>.KeyCollection keys = Objects.Keys;

            foreach (KeyType key in keys)
            {
                Objects[key] = null;
                PropertyInfos[key] = null;
                Last_Values[key] = Value;
                IsDirtys[key] = false;
            }
        }

        public void Reset()
        {
            ResetValues();

            Get_Call.Unbind();
            OnChange_Event.Clear();
            OnChangeMap_Event.Clear();
        }

        public bool HasChanged() { return IsDirty; }
        public bool HasChanged(KeyType key) { return IsDirtys[key]; }

        public void Resolve()
        {
            UpdateIsDirty();

            Dictionary<KeyType, object>.KeyCollection keys = Objects.Keys;

            foreach (KeyType key in keys)
            {
                UpdateIsDirtys(key);
            }
            Clear();
        }
    }

    public class TCgIntegralType_TMapRef<KeyType, ValueType> : TCgProperty_TMapRef<KeyType, ValueType>
    where ValueType : struct, IConvertible
    {
        public TCgIntegralType_TMapRef() : base(){ }
    }

    public class TCgIntegralType_TMapRef_byte<KeyType> : TCgIntegralType_TMapRef<KeyType, byte>
    {
        public TCgIntegralType_TMapRef_byte() : base()
        {
            DefaultValue = 0;
        }

        public byte Max()
        {
            Dictionary<KeyType, object>.KeyCollection keys = Objects.Keys;

            byte max = DefaultValue;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    max = (byte)PropertyInfos[key].GetValue(Objects[key], null);
                else
                    max = (byte)Math.Max(max, (byte)PropertyInfos[key].GetValue(Objects[key], null));
                ++i;
            }
            return max;
        }

        public byte Min()
        {
            Dictionary<KeyType, object>.KeyCollection keys = Objects.Keys;

            byte min = DefaultValue;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    min = (byte)PropertyInfos[key].GetValue(Objects[key], null);
                else
                    min = (byte)Math.Max(min, (byte)PropertyInfos[key].GetValue(Objects[key], null));
                ++i;
            }
            return min;
        }
    }

    public class TCgIntegralType_TMapRef_int<KeyType> : TCgIntegralType_TMapRef<KeyType, int>
    {
        public TCgIntegralType_TMapRef_int() : base()
        {
            DefaultValue = 0;
        }

        public int Max()
        {
            Dictionary<KeyType, object>.KeyCollection keys = Objects.Keys;

            int max = DefaultValue;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    max = (int)PropertyInfos[key].GetValue(Objects[key], null);
                else
                    max = (int)Math.Max(max, (int)PropertyInfos[key].GetValue(Objects[key], null));
                ++i;
            }
            return max;
        }

        public int Min()
        {
            Dictionary<KeyType, object>.KeyCollection keys = Objects.Keys;

            int min = DefaultValue;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    min = (int)PropertyInfos[key].GetValue(Objects[key], null);
                else
                    min = (int)Math.Max(min, (int)PropertyInfos[key].GetValue(Objects[key], null));
                ++i;
            }
            return min;
        }
    }

    public class TCgIntegralType_TMapRef_float<KeyType> : TCgIntegralType_TMapRef<KeyType, float>
    {
        public TCgIntegralType_TMapRef_float() : base()
        {
            DefaultValue = 0.0f;
        }

        public float Max()
        {
            Dictionary<KeyType, object>.KeyCollection keys = Objects.Keys;

            float max = DefaultValue;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    max = (float)PropertyInfos[key].GetValue(Objects[key], null);
                else
                    max = (float)Math.Max(max, (float)PropertyInfos[key].GetValue(Objects[key], null));
                ++i;
            }
            return max;
        }

        public float Min()
        {
            Dictionary<KeyType, object>.KeyCollection keys = Objects.Keys;

            float min = DefaultValue;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    min = (float)PropertyInfos[key].GetValue(Objects[key], null);
                else
                    min = (float)Math.Max(min, (float)PropertyInfos[key].GetValue(Objects[key], null));
                ++i;
            }
            return min;
        }
    }

    public class TCgProperty_TMapRef_bool<KeyType> : TCgProperty_TMapRef<KeyType, bool>
    {
        public TCgProperty_TMapRef_bool() : base()
        {
            DefaultValue = false;
        }

        bool Or()
        {
            Dictionary<KeyType, object>.KeyCollection keys = Objects.Keys;

            bool or = false;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    or = (bool)PropertyInfos[key].GetValue(Objects[key], null);
                else
                    or |= (bool)PropertyInfos[key].GetValue(Objects[key], null);
                ++i;
            }
            return or;
        }

        bool And()
        {
            Dictionary<KeyType, object>.KeyCollection keys = Objects.Keys;

            bool and = false;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    and = (bool)PropertyInfos[key].GetValue(Objects[key], null);
                else
                    and &= (bool)PropertyInfos[key].GetValue(Objects[key], null);
                ++i;
            }
            return and;
        }
    }

        #endregion // Map Ref

        #region "Class"

    public class TCgPropertyClass<ClassType> : CgProperty 
        where ClassType : class
    {
        public sealed class FOnChange : TCgMulticastDelegate_OneParam<ClassType> { }

        #region "Data Members"

        public ClassType Value;
        public ClassType Last_Value;

        protected bool IsDirty;

        public FOnChange OnChange_Event;

        #endregion // Data Members

        public TCgPropertyClass()
        {
            OnChange_Event = new FOnChange();
        }

        #region "Operators"

        public static bool operator ==(TCgPropertyClass<ClassType> lhs, TCgPropertyClass<ClassType> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Value.Equals(rhs.Value);
        }

        public static bool operator !=(TCgPropertyClass<ClassType> lhs, TCgPropertyClass<ClassType> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgPropertyClass<ClassType> lhs, ClassType rhs)
        {
            return lhs.Value.Equals(rhs);
        }

        public static bool operator !=(TCgPropertyClass<ClassType> lhs, ClassType rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(ClassType lhs, TCgPropertyClass<ClassType> rhs)
        {
            return lhs.Equals(rhs.Value);
        }

        public static bool operator !=(ClassType lhs, TCgPropertyClass<ClassType> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgPropertyClass<ClassType>))
                return false;

            TCgPropertyClass<ClassType> rhs = (TCgPropertyClass<ClassType>)obj;

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
            IsDirty    = !Value.Equals(Last_Value);
            Last_Value = Value;

            if (IsDirty)
                OnChange_Event.Broadcast(Value);
        }

        public void Set(ClassType inValue)
        {
            Value = inValue;
            UpdateIsDirty();
        }

        public ClassType Get() { return Value; }

        public override void Clear()
        {
            Last_Value = Value;
            IsDirty = false;
        }

        public override void ResetValue()
        {
            Value = null;
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

        #endregion // Class

        #region "Class Ref"

    public class TCgPropertyClass_Ref<ClassType> : CgProperty 
        where ClassType : class
    {
        public sealed class FOnChange : TCgMulticastDelegate_OneParam<ClassType> { }

        #region "Data Members"

        public object Object;
        public PropertyInfo Info;
        public ClassType Last_Value;

        protected bool IsDirty;

        public FOnChange OnChange_Event;

        #endregion // Data Members

        public TCgPropertyClass_Ref()
        {
            Object = null;
            Info = null;
            Last_Value = null;

            IsDirty = false;

            OnChange_Event = new FOnChange();
        }

        #region "Operators"

        public static bool operator ==(TCgPropertyClass_Ref<ClassType> lhs, TCgPropertyClass_Ref<ClassType> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Get().Equals(rhs.Get());
        }

        public static bool operator !=(TCgPropertyClass_Ref<ClassType> lhs, TCgPropertyClass_Ref<ClassType> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgPropertyClass_Ref<ClassType> lhs, ClassType rhs)
        {
            return lhs.Get().Equals(rhs);
        }

        public static bool operator !=(TCgPropertyClass_Ref<ClassType> lhs, ClassType rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(ClassType lhs, TCgPropertyClass_Ref<ClassType> rhs)
        {
            return lhs.Equals(rhs.Get());
        }

        public static bool operator !=(ClassType lhs, TCgPropertyClass_Ref<ClassType> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgPropertyClass_Ref<ClassType>))
                return false;

            TCgPropertyClass_Ref<ClassType> rhs = (TCgPropertyClass_Ref<ClassType>)obj;

            if (!Get().Equals(rhs.Get())) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Get().GetHashCode();
        }

        #endregion // Operators

        public override void UpdateIsDirty()
        {
            ClassType value = (ClassType)Info.GetValue(Object, null);
            IsDirty         = !value.Equals(Last_Value);
            Last_Value      = value;

            if (IsDirty)
                OnChange_Event.Broadcast(value);
        }

        public void Set(Object o, string propertyName)
        {
            Object = o;
            Info = o.GetType().GetProperty(propertyName);
            UpdateIsDirty();
        }

        public ClassType Get() { return (ClassType)Info.GetValue(Object, null); }

        public override void Clear()
        {
            IsDirty = false;
        }

        public override void ResetValue()
        {
            Object = null;
            Info = null;
            Last_Value = null;
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
        #endregion // Class Ref

    #endregion // Property

    #region "Flags"

    public interface ICgFlag
    {
        bool IsEqual();
    }

    public abstract class FCgFlag : ICgFlag
    {
        public abstract bool IsEqual();
    }

    public class TCgFlag<T> : FCgFlag where T : struct
    {
        public sealed class FOnEqual : FCgMulticastDelegate { }

        #region "Data Members"

        public T StartValue;
        public T EndValue;

        public FOnEqual OnEqual_Event;

        #endregion // Data Members

        public TCgFlag(T startValue, T endValue)
        {
            StartValue    = startValue;
            EndValue      = endValue;
            OnEqual_Event = new FOnEqual();
        }

        #region "Operators"

        public static bool operator ==(TCgFlag<T> lhs, TCgFlag<T> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.StartValue.Equals(rhs.StartValue);
        }

        public static bool operator !=(TCgFlag<T> lhs, TCgFlag<T> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgFlag<T> lhs, T rhs)
        {
            return lhs.StartValue.Equals(rhs);
        }

        public static bool operator !=(TCgFlag<T> lhs, T rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(T lhs, TCgFlag<T> rhs)
        {
            return lhs.Equals(rhs.StartValue);
        }

        public static bool operator !=(T lhs, TCgFlag<T> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgFlag<T>))
                return false;

            TCgFlag<T> rhs = (TCgFlag<T>)obj;

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

            if (StartValue.Equals(EndValue))
                OnEqual_Event.Broadcast();
        }

        public void SetEnd(T endValue)
        {
            EndValue = endValue;
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

    public class FCgFlag_bool : TCgFlag<bool>
    {
        public FCgFlag_bool(bool startValue, bool endValue) : base(startValue, endValue) { }
    }

    public class FCgFlag_int : TCgFlag<int>
    {
        public FCgFlag_int(int startValue, int endValue) : base(startValue, endValue) { }

        #region "Operators"

        public static FCgFlag_int operator ++(FCgFlag_int f)
        {
            ++(f.StartValue);

            if (f.StartValue.Equals(f.EndValue))
                f.OnEqual_Event.Broadcast();
            return f;
        }

        public static FCgFlag_int operator --(FCgFlag_int f)
        {
            --(f.StartValue);

            if (f.StartValue.Equals(f.EndValue))
                f.OnEqual_Event.Broadcast();
            return f;
        }

        #endregion // Operators
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
    
    public sealed class FCgAttribute
    {
        private Type ValueType;
        private object Value;
        private object UnSetValue;
        private bool IsSet;

        public FCgAttribute()
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

        public T Get<T>()
        {
            return (T)Get();
        }
    }

    #endregion // Attribute
}
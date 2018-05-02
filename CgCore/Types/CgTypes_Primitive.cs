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

    public interface ICgPrimitive
    {
        void UpdateIsDirty();
        void Clear();
        void ResetValue();
        void Reset();
        bool HasChanged();
        void MarkDirty();
        void Resolve();
    }

    public abstract class CgPrimitive : ICgPrimitive
    {
        public abstract void UpdateIsDirty();
        public abstract void Clear();
        public abstract void ResetValue();
        public abstract void Reset();
        public abstract bool HasChanged();
        public abstract void MarkDirty();
        public abstract void Resolve();
    }

    public class TCgPrimitiveType<T> : CgPrimitive where T : struct
    {
        public sealed class OnChange : TCgMulticastDelegate_OneParam<T> { }

        #region "Data Members"

        public T Value;
        public T Last_Value;

        protected bool IsDirty;

        public OnChange OnChange_Event;

        #endregion // Data Members

        public TCgPrimitiveType()
        {
            OnChange_Event = new OnChange();
        }

        #region "Operators"

        public static bool operator ==(TCgPrimitiveType<T> lhs, TCgPrimitiveType<T> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Value.Equals(rhs.Value);
        }

        public static bool operator !=(TCgPrimitiveType<T> lhs, TCgPrimitiveType<T> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgPrimitiveType<T> lhs, T rhs)
        {
            return lhs.Value.Equals(rhs);
        }

        public static bool operator !=(TCgPrimitiveType<T> lhs, T rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(T lhs, TCgPrimitiveType<T> rhs)
        {
            return lhs.Equals(rhs.Value);
        }

        public static bool operator !=(T lhs, TCgPrimitiveType<T> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgPrimitiveType<T>))
                return false;

            TCgPrimitiveType<T> rhs = (TCgPrimitiveType<T>)obj;

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

    #endregion // Primitive Types

    #region "Primitive Classes"

    public class TCgPrimitiveClass<T> : CgPrimitive where T : class
    {
        public sealed class OnChange : TCgMulticastDelegate_OneParam<T> { }

        #region "Data Members"

        public T Value;
        public T Last_Value;

        protected bool IsDirty;

        public OnChange OnChange_Event;

        #endregion // Data Members

        public TCgPrimitiveClass()
        {
            OnChange_Event = new OnChange();
        }

        #region "Operators"

        public static bool operator ==(TCgPrimitiveClass<T> lhs, TCgPrimitiveClass<T> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Value.Equals(rhs.Value);
        }

        public static bool operator !=(TCgPrimitiveClass<T> lhs, TCgPrimitiveClass<T> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgPrimitiveClass<T> lhs, T rhs)
        {
            return lhs.Value.Equals(rhs);
        }

        public static bool operator !=(TCgPrimitiveClass<T> lhs, T rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(T lhs, TCgPrimitiveClass<T> rhs)
        {
            return lhs.Equals(rhs.Value);
        }

        public static bool operator !=(T lhs, TCgPrimitiveClass<T> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgPrimitiveClass<T>))
                return false;

            TCgPrimitiveClass<T> rhs = (TCgPrimitiveClass<T>)obj;

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
namespace CgCore
{
    using System.Collections.Generic;

    public abstract class TCgEnum<T>
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

        public static implicit operator T(TCgEnum<T> e)
        {
            return e.Value;
        }
    }

    public class ECgEnum_Byte : TCgEnum<byte>
    {
        public ECgEnum_Byte() : base() { }
        public ECgEnum_Byte(byte value) : base(value) { }
        public ECgEnum_Byte(byte value, string name) : base(value, name) { }

        public static bool operator ==(ECgEnum_Byte lhs, ECgEnum_Byte rhs)
        {
            return lhs.Value == rhs.Value && lhs.Name == rhs.Name;
        }

        public static bool operator !=(ECgEnum_Byte lhs, ECgEnum_Byte rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(ECgEnum_Byte lhs, byte rhs)
        {
            return lhs.Value == rhs;
        }

        public static bool operator !=(ECgEnum_Byte lhs, byte rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is ECgEnum_Byte))
                return false;

            ECgEnum_Byte rhs = (ECgEnum_Byte)obj;

            if (Value != rhs.Value) return false;
            if (Name != rhs.Name) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Value.GetHashCode() ^ Name.GetHashCode();
        }
    }
}
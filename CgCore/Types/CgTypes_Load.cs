namespace CgCore
{
    using System.Collections.Generic;

    public sealed class ECgAssetType : ECgEnum_byte
    {
        public ECgAssetType(byte value, string name) : base(value, name) { }
    }

    public sealed class ECgAssetTypeEqualityComparer : IEqualityComparer<ECgAssetType>
    {
        public bool Equals(ECgAssetType lhs, ECgAssetType rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgAssetType x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgAssetType : ECgEnumMap<ECgAssetType, byte>
    {
        private static EMCgAssetType _Instance;
        public static EMCgAssetType Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgAssetType();
                }
                return _Instance;
            }
        }

        public static EMCgAssetType Get()
        {
            return Instance;
        }
    }
}

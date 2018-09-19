namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    #region "CharacterAnim"

    public sealed class FECgCharacterAnim : FECgEnum_byte
    {
        public FECgCharacterAnim(byte value, string name) : base(value, name) { }
    }

    public class EMCgCharacterAnim : TCgEnumMap<FECgCharacterAnim, byte>
    {
        private static EMCgCharacterAnim _Instance;
        public static EMCgCharacterAnim Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgCharacterAnim();
                }
                return _Instance;
            }
        }

        public static EMCgCharacterAnim Get()
        {
            return Instance;
        }
    }

    public sealed class FECgCharacterAnimEqualityComparer : IEqualityComparer<FECgCharacterAnim>
    {
        public bool Equals(FECgCharacterAnim lhs, FECgCharacterAnim rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgCharacterAnim x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // CharacterAnim

    #region "CharacterBlendSpace"

    public sealed class FECgCharacterBlendSpace : FECgEnum_byte
    {
        public FECgCharacterBlendSpace(byte value, string name) : base(value, name) { }
    }

    public class EMCgCharacterBlendSpace : TCgEnumMap<FECgCharacterBlendSpace, byte>
    {
        private static EMCgCharacterBlendSpace _Instance;
        public static EMCgCharacterBlendSpace Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgCharacterBlendSpace();
                }
                return _Instance;
            }
        }

        public static EMCgCharacterBlendSpace Get()
        {
            return Instance;
        }
    }

    public sealed class FECgCharacterBlendSpaceEqualityComparer : IEqualityComparer<FECgCharacterBlendSpace>
    {
        public bool Equals(FECgCharacterBlendSpace lhs, FECgCharacterBlendSpace rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgCharacterBlendSpace x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // CharacterAnim

    #region "CharacterAnimBlueprint"

    public sealed class FECgCharacterAnimBlueprint : FECgEnum_byte
    {
        public FECgCharacterAnimBlueprint(byte value, string name) : base(value, name) { }
    }

    public class EMCgCharacterAnimBlueprint : TCgEnumMap<FECgCharacterAnimBlueprint, byte>
    {
        private static EMCgCharacterAnimBlueprint _Instance;
        public static EMCgCharacterAnimBlueprint Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgCharacterAnimBlueprint();
                }
                return _Instance;
            }
        }

        public static EMCgCharacterAnimBlueprint Get()
        {
            return Instance;
        }
    }

    public sealed class FECgCharacterAnimBlueprintEqualityComparer : IEqualityComparer<FECgCharacterAnimBlueprint>
    {
        public bool Equals(FECgCharacterAnimBlueprint lhs, FECgCharacterAnimBlueprint rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgCharacterAnimBlueprint x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // CharacterAnim

    #region "CharacterAnimVariation"

    public sealed class FECgCharacterAnimVariation : FECgEnum_byte
    {
        public FECgCharacterAnimVariation(byte value, string name) : base(value, name) { }
    }

    public class EMCgCharacterAnimVariation : TCgEnumMap<FECgCharacterAnimVariation, byte>
    {
        private static EMCgCharacterAnimVariation _Instance;
        public static EMCgCharacterAnimVariation Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgCharacterAnimVariation();
                }
                return _Instance;
            }
        }

        public static EMCgCharacterAnimVariation Get()
        {
            return Instance;
        }
    }

    public sealed class FECgCharacterAnimVariationEqualityComparer : IEqualityComparer<FECgCharacterAnimVariation>
    {
        public bool Equals(FECgCharacterAnimVariation lhs, FECgCharacterAnimVariation rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgCharacterAnimVariation x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // CharacterAnim

    public class FCgHeadCollision
    {
        public float Radius;

        public string Bone;

        public Vector3 Offset;

        public FCgHeadCollision() { }
    }

    #region "CharacterState"

    public sealed class FECgCharacterState : FECgEnum_byte
    {
        public FECgCharacterState(byte value, string name) : base(value, name) { }
    }

    public class EMCgCharacterState : TCgEnumMap<FECgCharacterState, byte>
    {
        private static EMCgCharacterState _Instance;
        public static EMCgCharacterState Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgCharacterState();
                }
                return _Instance;
            }
        }

        public static EMCgCharacterState Get()
        {
            return Instance;
        }
    }

    public sealed class FECgCharacterStateEqualityComparer : IEqualityComparer<FECgCharacterState>
    {
        public bool Equals(FECgCharacterState lhs, FECgCharacterState rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgCharacterState x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // CharacterState

    #region "CharacterSetup"

    public sealed class FECgCharacterSetup : FECgEnum_byte
    {
        public FECgCharacterSetup(byte value, string name) : base(value, name) { }
    }

    public class EMCgCharacterSetup : TCgEnumMap<FECgCharacterSetup, byte>
    {
        private static EMCgCharacterSetup _Instance;
        public static EMCgCharacterSetup Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgCharacterSetup();
                }
                return _Instance;
            }
        }

        public static EMCgCharacterSetup Get()
        {
            return Instance;
        }
    }

    public sealed class FECgCharacterSetupEqualityComparer : IEqualityComparer<FECgCharacterSetup>
    {
        public bool Equals(FECgCharacterSetup lhs, FECgCharacterSetup rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(FECgCharacterSetup x)
        {
            return x.GetHashCode();
        }
    }

    #endregion // CharacterSetup
}

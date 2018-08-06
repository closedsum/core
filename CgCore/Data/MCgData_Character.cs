namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class MCgData_Character : MCgData
    {
        #region "Stats"

        public virtual int GetHealth()
        {
            return 0;
        }

        public virtual float GetRespawnTime()
        {
            return 0.0f;
        }

        #endregion // Stats

        #region "Inventory"

        #endregion // Inventory

        #region "Collision"

        public virtual float GetCapsuleRadius()
        {
            return 0.0f;
        }

        public virtual float GetCapsuleHalfHeight()
        {
            return 0.0f;
        }

        public virtual FCgHeadCollision GetHeadCollision()
        {
            return null;
        }

        #endregion // Collision

        #region "Movement"

        public virtual float GetMaxWalkSpeed()
        {
            return 0.0f;
        }

        public virtual float GetMaxAcceleration()
        {
            return 0.0f;
        }

        public virtual float GetJumpZVelocity()
        {
            return 0.0f;
        }

        public virtual float GetGravityScale()
        {
            return 0.0f;
        }

        public virtual float GetAirControl()
        {
            return 0.0f;
        }

        #endregion // Movement

        #region "Weapon"

        public virtual string GetBoneToAttachWeaponTo()
        {
            return ECgCached.Str.NAME_None;
        }

        #endregion // Weapon

        #region "Animation"

            #region "Sequence"
            #endregion // Sequence

            #region "Montage"
            #endregion // Montage

            #region BlendSpace1D
            #endregion // BlendSpace1D

            #region "BlendSpace"
            #endregion // BlendSpace

            #region AimOffset
            #endregion // AimOffset

            #region AnimBlueprint
            #endregion // AnimBlueprint

            #region Play
            #endregion // Play

            #region JumpTo
            #endregion // JumpTo

            #region Stop
            #endregion // Stop

        #endregion // Animation

        #region "Sense"

        public virtual bool GetUseSenseRadus()
        {
            return false;
        }

        public virtual float GetSenseRadius()
        {
            return 0.0f;
        }

        public virtual float GetSenseRadiusSq()
        {
            return 0.0f;
        }

        public virtual float GetSenseViewMinAngle()
        {
            return 0.0f;
        }

        public virtual float GetSenseViewMinDot()
        {
            return 0.0f;
        }

        #endregion // Sense
    }
}

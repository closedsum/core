namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgAnimClip
    {
        #region "Data Members"

        public TCgAssetRef<AnimationClip> Anim;

        public int Anim_LoadFlags;

        private AnimationClip Anim_Internal;

        #endregion // Data Members

        public FCgAnimClip()
        {

        }

        public AnimationClip Get()
        {
            return Anim_Internal;
        }

        // TODO: HACK: used to temporarily stop warnings
        public void TempAssign()
        {
            Anim_Internal = Anim.Get();
        }
    }

    public class FCgFpvAnimClip
    {
        #region "Data Members"

        public TCgAssetRef<AnimationClip> Anim1P;

        public TCgAssetRef<AnimationClip> Anim3P;

        public TCgAssetRef<AnimationClip> Anim3P_Low;

        public TCgAssetRef<AnimationClip> AnimVR;

        public int Anim1P_LoadFlags;

        public int Anim3P_LoadFlags;

        public int Anim3P_Low_LoadFlags;

        public int AnimVR_LoadFlags;

        public AnimationClip Anim1P_Internal;

        public AnimationClip Anim3P_Internal;

        public AnimationClip Anim3P_Low_Internal;

        public AnimationClip AnimVR_Internal;

        #endregion // Data Members

        public FCgFpvAnimClip()
        {

        }

        public AnimationClip Get(ECgViewType viewType, bool isLow = false)
        {
            if (viewType == ECgViewType.FirstPerson)
                return Anim1P_Internal;
            if (viewType == ECgViewType.ThirdPerson)
                return isLow ? Anim3P_Low_Internal : Anim3P_Internal;
            if (viewType == ECgViewType.VR)
                return AnimVR_Internal;
            return Anim3P_Internal;
        }
    }
}
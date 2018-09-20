namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    #region "Enums"

    public enum ECgBoneSpaces : byte
    {
        World,
        Local,
        MAX,
    }

    #endregion // Enums

    public class MCgSkeleton : MonoBehaviour
    {
        #region "Data Members"

        [FCgReadOnly]
        public List<Transform> Bones;
        public Dictionary<int, string> BoneIndexNameMap;
        public Dictionary<string, Transform> BoneNameMap;

        [NonSerialized]
        public Transform Root;

        #endregion // Data Members

        public void Init()
        {
            Bones = new List<Transform>();
            BoneIndexNameMap = new Dictionary<int, string>();
            BoneNameMap = new Dictionary<string, Transform>();

            Root = transform;

            Bones.Add(Root);
            BoneIndexNameMap.Add(0, Root.name);
            BoneNameMap.Add(Root.name, Root);

            Build(Root);
        }

        public void Reset()
        {
            Bones.Clear();
            BoneIndexNameMap.Clear();
            BoneNameMap.Clear();

            Root = null;
        }

        public void Build(Transform bone)
        {
            int count = bone.childCount;

            for (int i = 0; i < count; ++i)
            {
                Transform child = bone.GetChild(i);

                Bones.Add(child);
                BoneIndexNameMap.Add(Bones.Count - 1, child.name);
                BoneNameMap.Add(child.name, child);

                Build(child);
            }
        }

        public Vector3 GetBoneLocation(string name, ECgBoneSpaces space = ECgBoneSpaces.World)
        {
            Transform bone;
            BoneNameMap.TryGetValue(name, out bone);

            if (bone != null)
                return space == ECgBoneSpaces.World ? bone.position : bone.localPosition;
            return Vector3.zero;
        }

        public Vector3 GetBoneLocation(int index, ECgBoneSpaces space = ECgBoneSpaces.World)
        {
            if (index >= Bones.Count)
                return Vector3.zero;

            return space == ECgBoneSpaces.World ? Bones[index].position : Bones[index].localPosition;
        }
    }
}

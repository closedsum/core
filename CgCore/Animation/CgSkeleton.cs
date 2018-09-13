namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgSkeleton
    {
        #region "Data Members"

        public List<Transform> Bones;
        public Dictionary<int, string> BoneIndexNameMap;
        public Dictionary<string, Transform> BoneNameMap;

        public Transform Root;

        #endregion // Data Members

        public FCgSkeleton()
        {
            Bones = new List<Transform>();
            BoneIndexNameMap = new Dictionary<int, string>();
            BoneNameMap = new Dictionary<string, Transform>();
        }

        public void Init(Transform root)
        {
            Bones.Add(root);
            BoneIndexNameMap.Add(0, root.name);
            BoneNameMap.Add(root.name, root);

            Build(root);
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
    }
}

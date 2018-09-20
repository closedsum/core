namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    [RequireComponent(typeof(SkinnedMeshRenderer))]
    public class MCgSkinnedMeshComponent : MonoBehaviour
    {
        #region "Data Members"

        public SkinnedMeshRenderer MyMeshRenderer;
        public Mesh MyMesh;

        public MCgSkeleton Skeleton;

        #endregion // Data Members

        // Use this for initialization
        void Start()
        {

        }

        // Update is called once per frame
        void Update()
        {

        }

        public virtual void Init()
        {
            MyMeshRenderer = transform.GetComponent<SkinnedMeshRenderer>();
            MyMesh         = MyMeshRenderer.sharedMesh;
        }

        public void SetMesh(Mesh mesh)
        {
            MyMesh                    = mesh;
            MyMeshRenderer.sharedMesh = mesh;

        }

        public virtual void BuildSkeleton()
        {

        }
    }
}
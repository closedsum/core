namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;

    using UnityEngine;

    public enum ECgFxPriority : byte
    {
        Low,
        Medium,
        High,
        MAX
    }

    [Serializable]
    public struct S_FCgFxElement
    {
        [SerializeField]
        public ParticleSystem Particle;
        [SerializeField]
        public int Particle_LoadFlags;
        [SerializeField]
        public ECgFxPriority Priority;
        [SerializeField]
        public float LifeTime;
        [SerializeField]
        public float DeathTime;
        [SerializeField]
        public float Scale;
        [SerializeField]
        public S_FCgFpvDrawDistance DrawDistances;
        [SerializeField]
        public string Bone;
        [SerializeField]
        public Vector3 Location;
        [SerializeField]
        public Vector3 Rotation;
    }

    public class FCgFxElement
    {        
        public ParticleSystem Particle;
        
        public int Particle_LoadFlags;

        public ECgFxPriority Priority;

        public float LifeTime;

        public float DeathTime;

        public float Scale;

        public FCgFpvDrawDistance DrawDistances;

        public string Bone;

        public Vector3 Location;

        public Vector3 Rotation;

        private ParticleSystem Particle_Internal;

        public FCgFxElement()
        {
            //CS_SET_BLUEPRINT_BITFLAG(Particle_LoadFlags, ECsLoadFlags::Game);

            DeathTime = 1.0f;
            Scale = 1.0f;
            Priority = ECgFxPriority.Medium;
        }
        
        public void Set(ParticleSystem particle)
	    {
		    //Particle		  = TSoftObjectPtr<UParticleSystem>(InParticle);
		    Particle_Internal = particle;
	    }

	    public ParticleSystem Get()
	    {
		    return Particle_Internal;
	    }

        public void Reset()
        {
            Particle = null;
            Particle_LoadFlags = 0;

            //CS_SET_BLUEPRINT_BITFLAG(Particle_LoadFlags, ECsLoadFlags::Game);

            LifeTime = 0.0f;
            DeathTime = 1.0f;
            Scale = 1.0f;
            Priority = ECgFxPriority.Medium;
            DrawDistances.Reset();
            Bone = ECgCached.Str.NAME_None;
            Location = Vector3.zero;
            Rotation = Vector3.zero;

            Particle_Internal = null;
        }
    }

    public class FCgFpvFxElement
    {
        public FCgFxElement Effect1P;

        public FCgFxElement Effect3P;

        public FCgFpvFxElement()
        {
            //CS_SET_BLUEPRINT_BITFLAG(Effect1P.Particle_LoadFlags, ECsLoadFlags::Game1P);
            //CS_SET_BLUEPRINT_BITFLAG(Effect3P.Particle_LoadFlags, ECsLoadFlags::Game3P);
        }

        public FCgFxElement Get(ECgViewType viewType)
        {
            if (viewType == ECgViewType.FirstPerson)
                return Effect1P;
            if (viewType == ECgViewType.ThirdPerson)
                return Effect3P;
            if (viewType == ECgViewType.VR)
                return Effect1P;
            return Effect3P;
        }

        public string GetBone(ECgViewType viewType)
        {
            if (viewType == ECgViewType.FirstPerson)
                return Effect1P.Bone;
            if (viewType == ECgViewType.ThirdPerson)
                return Effect3P.Bone;
            return ECgCached.Str.NAME_None;
        }
    }

    public class FCgFxPayload : FCgPooledObjectPayload
    {
        public ParticleSystem Particle;

        public ECgFxPriority Priority;

        public float LifeTime;

        public float DeathTime;

        public float Scale;

        public FCgFpvDrawDistance DrawDistances;

        public string Bone;

        public Vector3 Location;

        public Vector3 Rotation;

        public FCgFxPayload() { }

        public void Set(FCgFxElement element)
        {
            Particle = element.Get();
            Priority = element.Priority;
            LifeTime = element.LifeTime;
            DeathTime = element.DeathTime;
            Scale = element.Scale;
            DrawDistances = element.DrawDistances;
            Bone = element.Bone;
            Location = element.Location;
            Rotation = element.Rotation;
        }

        public override void Reset()
	    {
		    base.Reset();

		    Particle = null;
		    Priority = ECgFxPriority.Medium;
		    LifeTime = 0.0f;
		    DeathTime = 0.0f;
		    Scale = 1.0f;
		    DrawDistances.Reset();
		    Bone = ECgCached.Str.NAME_None;
		    Location = Vector3.zero;
		    Rotation = Vector3.zero;
	    }

        public ParticleSystem GetParticle() { return Particle; }
    }
}

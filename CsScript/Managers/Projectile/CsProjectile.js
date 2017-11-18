/// <reference path="../../../typings/ue.d.ts">/>
// ; typing info for auto-completion in Visual Studio Code

"use strict"

var JsCsPooledActor = require('CsScript/Managers/CsPooledActor.js');

var me = [];

module.exports = class JsCsProjectile extends JsCsPooledActor
{
    constructor()
    {
        super();

        me.push(this);
    }

    Init(inPtr, inRoot)
    {
        super.Init(inPtr, inRoot);

        this.ptr = CsProjectile.C(inPtr);

        // Override Allocate Internal
        //this.ptr.Override_Allocate_Internal_ScriptEvent.Add(this.Allocate);
    }

    CleanUp()
    {
        this.ptr.Override_Allocate_Internal_ScriptEvent.Remove(this.Allocate)
    }

    static GetMeIndex(index)
    {
        const len = me.length;

        for (let i = 0; i < len; i++)
        {
            if (me[i].ptr.PoolIndex == index)
            {
                return i;
            }
        }
        return INDEX_NONE;
    }

    Allocate(poolIndex) { me[JsCsProjectile.GetMeIndex(poolIndex)].Allocate_Internal(); }
    Allocate_Internal()
    {
        let instigatingPawn     = CsPawn.C(this.ptr.Cache_GetInstigator());
        const isLocalClient = CsCommon.IsLocalPawn(this.root.MyWorld, instigatingPawn);
        const viewType      = isLocalClient ? ECsViewType.FirstPerson: ECsViewType.ThirdPerson;

        let ownerWeapon		= CsWeapon.C(this.ptr.Cache_GetOwner());
        let data_Weapon		= (ownerWeapon != null && typeof ownerWeapon === "object") ? ownerWeapon.GetMyData_Weapon() : null;
        let data_Projectile = CsData_Projectile.C(this.ptr.Cache_GetData());

        const relevance = this.ptr.Cache.Relevance;

        // Move

        // Real Invisible
        if (relevance === ECsProjectileRelevance.RealInvisible)
        {
            CsJavascriptLibrary.ComponentDetachFromComponent(this.ptr.MeshComponent, FCsDetachmentTransformRules.KeepRelativeTransform);
            this.ptr.MeshComponent.SetVisibility(false);

            this.ptr.MovementComponent.SetUpdatedComponent(this.ptr.CollisionComponent);
            this.ptr.MovementComponent.Activate();
            this.ptr.MovementComponent.SetComponentTickEnabled(true);
        }
        // Real Visible
        if (relevance === ECsProjectileRelevance.RealVisible)
        {
            this.ptr.MovementComponent.SetUpdatedComponent(this.ptr.CollisionComponent);
            this.ptr.MovementComponent.Activate();
            this.ptr.MovementComponent.SetComponentTickEnabled(true);
        }
        // Fake
        if (relevance === ECsProjectileRelevance.Fake)
        {
            CsJavascriptLibrary.ComponentDetachFromComponent(this.ptr.MeshComponent, FDetachmentTransformRules.KeepWorldTransform);
            this.ptr.SetRootComponent(this.ptr.MeshComponent);
            this.ptr.MovementComponent.SetUpdatedComponent(this.ptr.MeshComponent);
            this.ptr.MovementComponent.Activate();
            this.ptr.MovementComponent.SetComponentTickEnabled(true);
        }

        // Mesh / Visual

        // Real Visible | Fake
        if (relevance === ECsProjectileRelevance.RealVisible ||
            relevance === ECsProjectileRelevance.Fake)
        {
            // Mesh

            this.ptr.MeshComponent.SetStaticMesh(data_Projectile.GetMesh(viewType));
            CsJavascriptLibrary.SetComponentRelativeTransform(this.ptr.MeshComponent, data_Projectile.GetTransform());
            this.ptr.MeshComponent.Activate();
            this.ptr.MeshComponent.SetVisibility(true);
            this.ptr.MeshComponent.SetHiddenInGame(false);
            this.ptr.MeshComponent.SetComponentTickEnabled(true);
        }
        
        // Collision

        // Real Visible | Real Invisible
        if (relevance === ECsProjectileRelevance.RealVisible ||
            relevance === ECsProjectileRelevance.RealInvisible)
        {
            this.ptr.CollisionComponent.Activate();

            let myInstigator = Actor.C(this.ptr.Cache_GetInstigator());

            if (myInstigator != null && typeof myInstigator === "object")
                this.ptr.AddIgnoreActor(myInstigator);

            if (ownerWeapon != null && typeof ownerWeapon === "object")
                this.ptr.AddIgnoreActor(ownerWeapon);

            const count = this.ptr.IgnoreActors.length;

            for (let i = 0; i < count; i++)
            {
                let actor = this.ptr.GetIgnoreActor(i);

                if (actor == null && typeof actor != "object")
                    continue;

                CsJavascriptLibrary.AddMoveIngoreActor(this.ptr.CollisionComponent, actor);
            }

            this.ptr.CollisionComponent.SetCollisionObjectType(data_Projectile.GetCollisionObjectType());
            CsJavascriptLibrary.SetCollisionResponseToChannels(this.ptr.CollisionComponent, data_Projectile.GetCollisionResponseContainer());
            this.ptr.CollisionComponent.SetCollisionEnabled(data_Projectile.GetCollisionEnabled());
            this.ptr.CollisionComponent.SetNotifyRigidBodyCollision(true);

            this.ptr.CollisionComponent.SetComponentTickEnabled(true);

            this.ptr.CollisionComponent.SetSphereRadius(data_Projectile.GetSphereRadius());
        }
        // Fake
        if (relevance === ECsProjectileRelevance.Fake)
        {
            this.ptr.CollisionComponent.SetCollisionEnabled(ECollisionEnabled.NoCollision);
            this.ptr.CollisionComponent.SetCollisionObjectType(data_Projectile.GetCollisionObjectType());
            this.ptr.CollisionComponent.SetCollisionResponseToAllChannels(ECollisionResponse.ECR_Ignore);
            this.ptr.CollisionComponent.SetNotifyRigidBodyCollision(false);
        }

        // Homing
        /*
        if (Cache)
        {
            if (AActor* HomingTarget = Cast<AActor>(Cache->GetHomingTarget()))
            {
                SetHomingTarget(HomingTarget, Cache->HomingAccelerationMagnitude, Cache->HomingBoneName);
            }
        }
        */

        this.ptr.SetActorTickEnabled(true);
        CsJavascriptLibrary.TeleportTo(this.ptr, this.ptr.Cache.Location, CsJavascriptLibrary.Vector_Rotation(this.ptr.Cache.Direction), false, true);

        const drawDistanceSq = data_Projectile.GetDrawDistanceSq(viewType);

        if (drawDistanceSq > 0)
        {
            const distanceSq = CsCommon.GetSquaredDistanceToLocalControllerEye(this.root.MyWorld, CsJavascriptLibrary.GetActorLocation(this.ptr));
            const hide		 = distanceSq > drawDistanceSq;

            if (hide != this.ptr.bHidden)
                this.ptr.SetActorHiddenInGame(hide);
        }

        this.ptr.MovementComponent.InitialSpeed		      = this.ptr.Cache.Speed;
        this.ptr.MovementComponent.MaxSpeed               = data_Projectile.GetMaxSpeed();
        this.ptr.MovementComponent.Velocity               = KismetMathLibrary.Multiply_VectorFloat(this.ptr.Cache.Direction, this.ptr.MovementComponent.InitialSpeed);
        this.ptr.MovementComponent.ProjectileGravityScale = data_Projectile.GetGravityMultiplier();
    }
};
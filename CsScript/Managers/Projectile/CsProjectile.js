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
        this.ptr.Override_Allocate_Internal_ScriptEvent.Add(this.Allocate);
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
        let data_Projectile = CsProjectile.C(this.ptr.Cache_GetData());

        const relevance = this.ptr.Cache.Relevance;

        // Move

        // Real Invisible
        if (relevance == ECsProjectileRelevance.RealInvisible)
        {
            MeshComponent ->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
            MeshComponent ->SetVisibility(false);

            MovementComponent ->UpdatedComponent = CollisionComponent;
            MovementComponent ->Activate();
            MovementComponent ->SetComponentTickEnabled(true);
            //MovementComponent->MaxSimulationIterations = CVarSimulationIterationsProjectile->GetInt();
        }
        // Real Visible
        if (relevance == ECsProjectileRelevance::RealVisible)
        {
            MovementComponent ->UpdatedComponent = CollisionComponent;
            MovementComponent ->Activate();
            MovementComponent ->SetComponentTickEnabled(true);
        }
        // Fake
        if (relevance == ECsProjectileRelevance::Fake)
        {
            MeshComponent ->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
            RootComponent = MeshComponent;
            MovementComponent ->UpdatedComponent = MeshComponent;
            MovementComponent ->Activate();
            MovementComponent ->SetComponentTickEnabled(true);
        }

        // Mesh / Visual

        // Real Visible | Fake
        if (relevance == ECsProjectileRelevance::RealVisible ||
            relevance == ECsProjectileRelevance::Fake)
        {
            // Mesh

            MeshComponent ->SetStaticMesh(Data_Projectile ->GetMesh(ViewType));
            MeshComponent ->SetRelativeTransform(Data_Projectile ->GetTransform());
            MeshComponent ->Activate();
            MeshComponent ->SetVisibility(true);
            MeshComponent ->SetHiddenInGame(false);
            MeshComponent ->SetComponentTickEnabled(true);
        }

        // Collision

        // Real Visible | Real Invisible
        if (relevance == ECsProjectileRelevance::RealVisible ||
            relevance == ECsProjectileRelevance::RealInvisible)
        {
            CollisionComponent ->Activate();

            if (AActor * MyInstigator = Cast<AActor>(Cache.GetInstigator()))
            IgnoreActors.Add(MyInstigator);

            if (OwnerWeapon)
                IgnoreActors.Add(OwnerWeapon);

            const int32 Count = IgnoreActors.Num();

            for (int32 I = 0; I < Count; I++)
            {
                AActor * Actor = IgnoreActors[I].IsValid() ? IgnoreActors[I].Get() : nullptr;

                if (!Actor)
                    continue;

                CollisionComponent ->MoveIgnoreActors.Add(Actor);
            }

            //FCollisionResponseContainer CapsuleResponseContainer(ECR_Ignore);
            //CapsuleResponseContainer.SetResponse(ECC_Pawn, ECR_Block);
            //CapsuleResponseContainer.SetResponse(MBO_COLLISION_PROJECTILE, ECR_Ignore);

            CollisionComponent ->SetCollisionObjectType(Data_Projectile ->GetCollisionObjectType());
            CollisionComponent ->SetCollisionResponseToChannels(Data_Projectile ->GetCollisionResponseContainer());
            CollisionComponent ->SetCollisionEnabled(Data_Projectile ->GetCollisionEnabled());
            CollisionComponent ->SetNotifyRigidBodyCollision(true);

            CollisionComponent ->SetComponentTickEnabled(true);

            CollisionComponent ->SetSphereRadius(Data_Projectile ->GetSphereRadius());
        }
        // Fake
        if (Relevance == ECsProjectileRelevance::Fake)
        {
            CollisionComponent ->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            CollisionComponent ->SetCollisionObjectType(Data_Projectile ->GetCollisionObjectType());
            CollisionComponent ->SetCollisionResponseToAllChannels(ECR_Ignore);
            CollisionComponent ->SetNotifyRigidBodyCollision(false);
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

        SetActorTickEnabled(true);
        TeleportTo(Cache.Location, Cache.Direction.Rotation(), false, true);

        const float DrawDistanceSq = Data_Projectile ->GetDrawDistanceSq(ViewType);

        if (DrawDistanceSq > 0) {
            const float DistanceSq = UCsCommon::GetSquaredDistanceToLocalControllerEye(GetWorld(), GetActorLocation());
            const bool Hide		   = DistanceSq > DrawDistanceSq;

            if (Hide != bHidden)
                SetActorHiddenInGame(Hide);
        }

        MovementComponent ->InitialSpeed			  = Cache.Speed;
        MovementComponent ->MaxSpeed				  = Data_Projectile ->GetMaxSpeed();
        MovementComponent ->Velocity				  = MovementComponent ->InitialSpeed * Cache.Direction;
        MovementComponent ->ProjectileGravityScale = Data_Projectile ->GetGravityMultiplier();
    }
};
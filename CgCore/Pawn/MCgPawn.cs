namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgPawnViewTraceInfo
    {
        public static readonly byte INVALID_TRACE_REQUEST_ID = 255;

        public bool bAsync;
        public bool bForce;
        public byte RequestId;

        public float Range;
        public float RangeSq;

        public Vector3 HitLocation;

        public RaycastHit HitResult;

        public List<RaycastHit> OutHits;

        public FCgPawnViewTraceInfo()
        {
            RequestId = INVALID_TRACE_REQUEST_ID;
        }
    }

    public class MCgPawn : MonoBehaviour, ICgObject
    {
        #region "Constants

        public static readonly int AUTO_ASSIGN_CONTROLLER = -1;

        #endregion // Constants

        #region "Data Members"

            #region "Interface"

        private ulong _UniqueObjectId;
        public ulong UniqueObjectId
        {
            get { return _UniqueObjectId; }
            set { _UniqueObjectId = value; }
        }

            #endregion // Interface

        public MCgPlayerStateBase PlayerState;

            #region "Setup"

        public bool bAutoPossess;
        public int ControllerIndex = AUTO_ASSIGN_CONTROLLER;

        public sealed class FOnSetupFinished : TCgMulticastDelegate_OneParam<byte> { }
        public FOnSetupFinished OnSetupFinished_Event;

            #endregion // Setup

            #region "State"

                #region "Health"

        [Header("Health")]

        public float Health;

        public FCgProperty_Ref_float HealthHandle;

        public sealed class FOnChange_Health : TCgMulticastDelegate_ThreeParams<byte, float, float> { }
        public FOnChange_Health OnChange_Health_Event;

                #endregion // Health

        //public sealed class FOnApplyDamage_Result : TCgMulticastDelegate_TwoParams<byte, FCgDamageResult> { }
        //public FOnApplyDamage_Result OnApplyDamage_Result_Event;

                #region "Spawn"

        [Header("Spawn")]

        [FCgReadOnly]
        public bool bFirstSpawn;

        public sealed class FOnFirstSpawn : TCgMulticastDelegate_OneParam<MCgPawn> { }
        public FOnFirstSpawn OnFirstSpawn_Event;

        [FCgReadOnly]
        public int SpawnCount;

        public Vector3 SpawnLocation;
        public Vector3 SpawnRotation;

        public float RespawnTime;

        public FCgRoutine HandleRespawnTimer_Internal_Routine;

        public sealed class FOnHandleRespawnTimerFinished : TCgMulticastDelegate_OneParam<byte>{}
        public FOnHandleRespawnTimerFinished OnHandleRespawnTimerFinished_Event;

        [FCgReadOnly]
        public bool bSpawnedAndActive;

               #endregion // Spawn

            #endregion // State

            #region "View"

        [Header("View")]

        [FCgReadOnly]
        public ECgViewType CurrentViewType;

        [FCgReadOnly]
        public Vector3 CurrentViewRotation;
        [FCgReadOnly]
        public Vector3 CurrentViewRotationDelta;

        [FCgReadOnly]
        public Vector3 CurrentViewLocation;
        [FCgReadOnly]
        public Vector3 CurrentViewDir;
        [FCgReadOnly]
        public Vector3 CurrentViewDirXY;
        [FCgReadOnly]
        public Vector3 CurrentViewRight;
        [FCgReadOnly]
        public Vector3 CurrentViewRightXY;
        [FCgReadOnly]
        public Vector3 CurrentViewUp;

        [FCgReadOnly]
        public bool bPerformViewTrace;

        public FCgPawnViewTraceInfo ViewTraceInfo;

            #endregion // View

            #region "Body / Root"

        [Header("Body / Root")]

        [FCgReadOnly]
        public Vector3 CurrentRootRotation;
        [FCgReadOnly]
        public Vector3 CurrentRootLocation;
        [FCgReadOnly]
        public Vector3 CurrentBodyLocation;
        [FCgReadOnly]
        public Vector3 CurrentFeetLocation;
        [FCgReadOnly]
        public Vector3 CurrentRootDir;
        [FCgReadOnly]
        public Vector3 CurrentRootDirXY;
        [FCgReadOnly]
        public Vector3 CurrentRootRight;
        [FCgReadOnly]
        public Vector3 CurrentRootRightXY;

            #endregion // Body / Root

            #region "Movement"

        [Header("Movement")]

        private Transform MyTransform;

        [FCgReadOnly]
        public Vector3 CurrentVelocity;
        [FCgReadOnly]
        public Vector3 CurrentVelocityDir;
        [FCgReadOnly]
        public Vector3 CurrentVelocityXY;
        [FCgReadOnly]
        public Vector3 CurrentVelocityDirXY;
        [FCgReadOnly]
        public Vector3 CurrentVelocityZ;
        [FCgReadOnly]
        public Vector3 CurrentVelocityDirZ;

        [FCgReadOnly]
        public float CurrentSpeed;
        [FCgReadOnly]
        public float CurrentSpeedSq;
        [FCgReadOnly]
        public float CurrentSpeedXY;
        [FCgReadOnly]
        public float CurrentSpeedXYSq;
        [FCgReadOnly]
        public float CurrentSpeedZ;
        [FCgReadOnly]
        public float CurrentSpeedZSq;

        [FCgReadOnly]
        public Vector3 CurrentVelocityRight;
        [FCgReadOnly]
        public Vector3 CurrentVelocityRightXY;

        [FCgReadOnly]
        public Vector3 CurrentCapsuleVelocity;
        [FCgReadOnly]
        public Vector3 CurrentCapsuleVelocityDir;
        [FCgReadOnly]
        public Vector3 CurrentCapsuleVelocityXY;
        [FCgReadOnly]
        public Vector3 CurrentCapsuleVelocityDirXY;
        [FCgReadOnly]
        public Vector3 CurrentCapsuleVelocityZ;
        [FCgReadOnly]
        public Vector3 CurrentCapsuleVelocityDirZ;

        [FCgReadOnly]
        public float CurrentCapsuleSpeed;
        [FCgReadOnly]
        public float CurrentCapsuleSpeedSq;
        [FCgReadOnly]
        public float CurrentCapsuleSpeedXY;
        [FCgReadOnly]
        public float CurrentCapsuleSpeedXYSq;
        [FCgReadOnly]
        public float CurrentCapsuleSpeedZ;
        [FCgReadOnly]
        public float CurrentCapsuleSpeedZSq;

        [FCgReadOnly]
        public Vector3 CurrentCapsuleVelocityRight;
        [FCgReadOnly]
        public Vector3 CurrentCapsuleVelocityRightXY;

        [FCgReadOnly]
        public float CurrentMoveRightLeftValue;

            #endregion // Movement

            #region "Data"

        [Header("Data")]

        public bool bCacheData;

        [FCgReadOnly]
        public MCgData_Character MyData_Character;
        [FCgReadOnly]
        public MCgData_CharacterMeshSkin MyData_CharacterMeshSkin;
        [FCgReadOnly]
        public MCgData_CharacterMaterialSkin MyData_CharacterMaterialSkin;

            #endregion // Data

            #region "Weapons"

        [Header("Weapons")]

        public FECgWeaponSlot CurrentWeaponSlot;
        public TCgPropertyClass_Ref<FECgWeaponSlot> CurrentWeaponSlotHandle;

        public sealed class FOnChange_CurrentWeaponSlot : TCgMulticastDelegate_ThreeParams<byte, FECgWeaponSlot, FECgWeaponSlot> { }
        public FOnChange_CurrentWeaponSlot OnChange_CurrentWeaponSlot_Event;

        [FCgReadOnly]
        public byte CurrentWeaponIndex;
        public FECgWeaponSlot LastWeaponSlot;
        [FCgReadOnly]
        public byte LastWeaponIndex;
        [FCgReadOnly]
        public byte CurrentWeaponCount;
        [FCgReadOnly]
        public byte MaxWeaponCount;

        public List<MCgWeapon> Weapons;

        [FCgReadOnly]
        public List<MCgData_Weapon> Data_Weapons;
        [FCgReadOnly]
        public List<MCgData_WeaponMaterialSkin> Data_WeaponMaterialSkins;

             #endregion // Weapons

            #region Sense

        [Header("Sense")]

            #endregion Sense

            #region "Managers"

        [Header("Managers")]

        public FCgManager_Sense Manager_Sense;

            #endregion // Managers

        #endregion // Data Members

        public virtual void Init()
        {
            MCgGameInstance.Get().RegisterUniqueObject(this);

            MyTransform = GetComponent<Transform>();
        }

        public virtual void OnUpdate(float deltaTime)
        {
            OnUpdate_Handle_Movement(deltaTime);
        }

        #region "Setup"

        public virtual void OnUpdate_HandleSetup()
        {
        }

        #endregion // Setup

        #region "State"

            #region "Health

        public virtual void SetHealth(float health)
        {

        }

        public virtual void OnChange_Health(float value)
        {

        }

        public virtual void Die()
        {

        }

            #endregion // Health

        public virtual void ApplyDamage(FCgDamageEvent e)
        {

        }

        public virtual void OnApplyDamage_Result(FCgDamageResult r)
        {

        }

            #region "Spawn"

        public virtual void OnFirstSpawn()
        {

        }

        public void HandleRespawnTimer()
        {

        }

        public static IEnumerator HandleRespawnTimer_Internal(MCgPawn p)
        {
            yield return null;
        }

        public virtual void OnHandleRespawnTimerFinished(byte mappingId)
        {

        }

            #endregion Spawn

            #region "Routine"

        public virtual bool AddRoutine(FCgRoutine r)
        {
            return false;
        }

        public virtual bool RemoveRoutine(FCgRoutine r)
        {
            return false;
        }

            #endregion // Routine

            #region "View"

        public virtual ECgViewType GetCurrentViewType()
        {
            return ECgViewType.MAX;
        }

        public virtual void PerformViewTrace()
        {

        }

        public virtual void PerformViewTrace_Respone(byte requestId, FCgTraceResponse response)
        {

        }

        public virtual void RecordView()
        {

        }

            #endregion // View

            #region "Body / Root"

        public virtual void RecordRoot()
        {

        }

            #endregion // Body / Root

            #region "Movement"

        public virtual void RecordVelocityAndSpeed()
        {

        }

            #endregion // Movement

            #region "Data"

        public MCgDataMapping GetDataMapping()
        {
            return null;
        }

        public T GetDataMapping<T>() where T : MCgDataMapping
        {
            return (T)GetDataMapping();
        }

        public MCgData_Character GetMyData_Character()
        {
            return MyData_Character;
        }

        public T GetMyData_Character<T>() where T : MCgData_Character
        {
            return (T)GetMyData_Character();
        }

        public MCgData_CharacterMeshSkin GetMyData_CharacterMeshSkin()
        {
            return MyData_CharacterMeshSkin;
        }

        public T GetMyData_CharacterMeshSkin<T>() where T : MCgData_CharacterMeshSkin
        {
            return (T)GetMyData_CharacterMeshSkin();
        }

        public MCgData_CharacterMaterialSkin GetMyData_CharacterMaterialSkin()
        {
            return MyData_CharacterMaterialSkin;
        }

        public T GetMyData_CharacterMaterialSkin<T>() where T : MCgData_CharacterMaterialSkin
        {
            return (T)GetMyData_CharacterMaterialSkin();
        }

        public virtual void SetDatas()
        {

        }

        public virtual void ApplyData_Character()
        {

        }

        public virtual void OnRespawn_ApplyData_Character()
        {

        }

            #endregion // data

            #region "Weapon"

        public MCgWeapon GetWeapon(FECgWeaponSlot slot)
        {
            return Weapons[slot.Value];
        }

        public T GetWeapon<T>(FECgWeaponSlot slot) where T : MCgWeapon
        {
            return (T)GetWeapon(slot);
        }

        public MCgWeapon GetCurrentWeapon()
        {
            return GetWeapon(CurrentWeaponSlot);
        }

        public T GetCurrentWeapon<T>() where T : MCgWeapon
        {
            return (T)GetCurrentWeapon();
        }

        public MCgData_Weapon GetData_Weapon(FECgWeaponSlot slot)
        {
            return Data_Weapons[slot.Value];
        }

        public T GetData_Weapon<T>(FECgWeaponSlot slot) where T : MCgData_Weapon
        {
            return (T)GetData_Weapon(slot);
        }

            #endregion // Weapon

        #endregion // State

        public virtual void OnUpdate_Handle_Movement(float deltaTime)
        {
            MyTransform.position += deltaTime * CurrentVelocity;
        }

        public void SetSpeed(float speed)
        {
            CurrentSpeed = speed;
            //CurrentVelocity = speed * CurrentDirection;
        }

        #region "Managers"

        public virtual FCgManager_Inventory GetMyManager_Inventory()
        {
            return null;
        }

        #endregion // Managers
    }
}

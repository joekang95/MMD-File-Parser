#pragma once

#include "PmxType.h"
#include "PmxResult.h"

#include <vector>

enum class ESoftShapeType : uint8_t
{
    TriMesh, // v2.1
    Rope     // v2.1   
};

enum class ESoftFlag : uint8_t
{
    BLink           = 0x01, // v2.1
    ClusterCreation = 0x02, // v2.1
    LinkCrossing    = 0x04  // v2.1
};

enum class EAerodynamicsModel : int32_t
{
    VPoint,     // v2.1
    VTwoSided,  // v2.1
    VOneSided,  // v2.1
    FTwoSided,  // v2.1
    FOneSided   // v2.1
};

class CPmxSoftConfig
{
public:
    const float& VelocityCorrectionFactor() const { return m_fVelocityCorrectionFactor; }
    float& VelocityCorrectionFactor() { return m_fVelocityCorrectionFactor; }

    const float& Damping() const { return m_fDamping; }
    float& Damping() { return m_fDamping; }

    const float& Drag() const { return m_fDrag; }
    float& Drag() { return m_fDrag; }

    const float& Lift() const { return m_fLift; }
    float& Lift() { return m_fLift; }

    const float& Pressure() const { return m_fPressure; }
    float& Pressure() { return m_fPressure; }

    const float& VolumeConversation() const { return m_fVolumeConversation; }
    float& VolumeConversation() { return m_fVolumeConversation; }

    const float& DynamicFriction() const { return m_fDynamicFriction; }
    float& DynamicFriction() { return m_fDynamicFriction; }

    const float& PoseMatching() const { return m_fPoseMatching; }
    float& PoseMatching() { return m_fPoseMatching; }

    const float& RigidContactsHardness() const { return m_fRigidContactsHardness; }
    float& RigidContactsHardness() { return m_fRigidContactsHardness; }

    const float& KineticContactsHardness() const { return m_fKineticContactsHardness; }
    float& KineticContactsHardness() { return m_fKineticContactsHardness; }

    const float& SoftContactsHardness() const { return m_fSoftContactsHardness; }
    float& SoftContactsHardness() { return m_fSoftContactsHardness; }

    const float& AnchorsHardness() const { return m_fAnchorsHardness; }
    float& AnchorsHardness() { return m_fAnchorsHardness; }

private:
    float m_fVelocityCorrectionFactor = 0.0f;
    float m_fDamping                  = 0.0f;
    float m_fDrag                     = 0.0f;
    float m_fLift                     = 0.0f;
    float m_fPressure                 = 0.0f;
    float m_fVolumeConversation       = 0.0f;
    float m_fDynamicFriction          = 0.0f;
    float m_fPoseMatching             = 0.0f;
    float m_fRigidContactsHardness    = 0.0f;
    float m_fKineticContactsHardness  = 0.0f;
    float m_fSoftContactsHardness     = 0.0f;
    float m_fAnchorsHardness          = 0.0f;
};

class CPmxClusterConfig
{
public:
    const float& SoftVsRigidHardness() const { return m_fSoftVsRigidHardness; }
    float& SoftVsRigidHardness() { return m_fSoftVsRigidHardness; }

    const float& SoftVsKineticHardness() const { return m_fSoftVsKineticHardness; }
    float& SoftVsKineticHardness() { return m_fSoftVsKineticHardness; }

    const float& SoftVsSoftHardness() const { return m_fSoftVsSoftHardness; }
    float& SoftVsSoftHardness() { return m_fSoftVsSoftHardness; }

    const float& SoftVsRigidImpulseHardness() const { return m_fSoftVsRigidImpulseHardness; }
    float& SoftVsRigidImpulseHardness() { return m_fSoftVsRigidImpulseHardness; }

    const float& SoftVsKineticImpulseHardness() const { return m_fSoftVsKineticImpulseHardness; }
    float& SoftVsKineticImpulseHardness() { return m_fSoftVsKineticImpulseHardness; }

    const float& SoftVsSoftImpulseHardness() const { return m_fSoftVsSoftImpulseHardness; }
    float& SoftVsSoftImpulseHardness() { return m_fSoftVsSoftImpulseHardness; }

private:
    float m_fSoftVsRigidHardness          = 0.0f;
    float m_fSoftVsKineticHardness        = 0.0f;
    float m_fSoftVsSoftHardness           = 0.0f;
    float m_fSoftVsRigidImpulseHardness   = 0.0f;
    float m_fSoftVsKineticImpulseHardness = 0.0f;
    float m_fSoftVsSoftImpulseHardness    = 0.0f;
};

class CPmxInterationConfig
{
public:
    const int32_t& VelocitySolver() const { return m_nVelocitySolver; }
    int32_t& VelocitySolver() { return m_nVelocitySolver; }

    const int32_t& PositionSolver() const { return m_nPositionSolver; }
    int32_t& PositionSolver() { return m_nPositionSolver; }

    const int32_t& DriftSolver() const { return m_nDriftSolver; }
    int32_t& DriftSolver() { return m_nDriftSolver; }

    const int32_t& ClusterSolver() const { return m_nClusterSolver; }
    int32_t& ClusterSolver() { return m_nClusterSolver; }

private:
    int32_t m_nVelocitySolver = 0;
    int32_t m_nPositionSolver = 0;
    int32_t m_nDriftSolver    = 0;
    int32_t m_nClusterSolver  = 0;
};

class CPmxMaterialConfig
{
public:
    const int32_t& LinearStiffness() const { return m_nLinearStiffness; }
    int32_t& LinearStiffness() { return m_nLinearStiffness; }

    const int32_t& AreaStiffness() const { return m_nAreaStiffness; }
    int32_t& AreaStiffness() { return m_nAreaStiffness; }

    const int32_t& VolumeStiffness() const { return m_nVolumeStiffness; }
    int32_t& VolumeStiffness() { return m_nVolumeStiffness; }

private:
    int32_t m_nLinearStiffness = 0;
    int32_t m_nAreaStiffness   = 0;
    int32_t m_nVolumeStiffness = 0;
};

class CPmxAnchorRigidBody
{
public:
    const int32_t& RigidBodyIndex() const { return m_nRigidBodyIndex; }
    int32_t& RigidBodyIndex() { return m_nRigidBodyIndex; }

    const int32_t& VertexIndex() const { return m_nVertexIndex; }
    int32_t& VertexIndex() { return m_nVertexIndex; }

    const bool& IsNear() const { return m_bNear; }
    bool& IsNear() { return m_bNear; }

private:
    int32_t m_nRigidBodyIndex = 0;
    int32_t m_nVertexIndex = 0;
    bool    m_bNear = false;
};

class CPmxSoftBody
{
public:
    const std::wstring& LocalName() const { return m_strLocalName; }
    std::wstring& LocalName() { return m_strLocalName; }

    const std::wstring& GlobalName() const { return m_strGlobalName; }
    std::wstring& GlobalName() { return m_strGlobalName; }

    const ESoftShapeType& ShapeType() const { return m_eShapeType; }
    ESoftShapeType& ShapeType() { return m_eShapeType; }

    const int32_t& MaterialIndex() const { return m_nMaterialIndex; }
    int32_t& MaterialIndex() { return m_nMaterialIndex; }

    const uint8_t& GroupId() const { return m_uGroupId; }
    uint8_t& GroupId() { return m_uGroupId; }

    const uint16_t& NonCollisionMask() const { return m_uNonCollisionMask; }
    uint16_t& NonCollisionMask() { return m_uNonCollisionMask; }

    const ESoftFlag& Flags() const { return m_eSoftFlags; }
    ESoftFlag& Flags() { return m_eSoftFlags; }

    const int32_t& BLinkDistance() const { return m_nBLinkDistance; }
    int32_t& BLinkDistance() { return m_nBLinkDistance; }

    const int32_t& ClusterCount() const { return m_nClusterCount; }
    int32_t& ClusterCount() { return m_nClusterCount; }

    const float& Mass() const { return m_fMass; }
    float& Mass() { return m_fMass; }

    const float& CollisionMargin() const { return m_fCollisionMargin; }
    float& CollisionMargin() { return m_fCollisionMargin; }

    const EAerodynamicsModel& AerodynamicsModel() const { return m_eAerodynamicsModel; }
    EAerodynamicsModel& AerodynamicsModel() { return m_eAerodynamicsModel; }

    const CPmxSoftConfig& SoftConfig() const { return m_kSoftConfig; }
    CPmxSoftConfig& SoftConfig() { return m_kSoftConfig; }

    const CPmxClusterConfig& ClusterConfig() const { return m_kClusterConfig; }
    CPmxClusterConfig& ClusterConfig() { return m_kClusterConfig; }

    const CPmxInterationConfig& InterationConfig() const { return m_kInterationConfig; }
    CPmxInterationConfig& InterationConfig() { return m_kInterationConfig; }

    const CPmxMaterialConfig& MaterialConfig() const { return m_kMaterialConfig; }
    CPmxMaterialConfig& MaterialConfig() { return m_kMaterialConfig; }

    const int32_t& AnchorRigidBodyCount() const { return m_nAnchorRigidBodyCount; }
    int32_t& AnchorRigidBodyCount() { return m_nAnchorRigidBodyCount; }

    const std::vector< CPmxAnchorRigidBody >& AnchorRigidBodys() const { return m_kAnchorRigidBodys; }
    std::vector< CPmxAnchorRigidBody >& AnchorRigidBodys() { return m_kAnchorRigidBodys; }

    const int32_t& VertexPinCount() const { return m_nVertexPinCount; }
    int32_t& VertexPinCount() { return m_nVertexPinCount; }

    const std::vector< int32_t >& VertexPins() const { return m_kVertexPins; }
    std::vector< int32_t >& VertexPins() { return m_kVertexPins; }

private:
    std::wstring m_strLocalName  = L""; // Usually in Japanese
    std::wstring m_strGlobalName = L""; // Usually in English 

    ESoftShapeType m_eShapeType;
    int32_t m_nMaterialIndex = 0;
    uint8_t m_uGroupId = 0;
    uint16_t m_uNonCollisionMask = 0;

    ESoftFlag m_eSoftFlags;

    int32_t m_nBLinkDistance = 0;
    int32_t m_nClusterCount  = 0;

    float m_fMass = 0;
    float m_fCollisionMargin = 0;

    EAerodynamicsModel m_eAerodynamicsModel;

    CPmxSoftConfig m_kSoftConfig;

    CPmxClusterConfig m_kClusterConfig;

    CPmxInterationConfig m_kInterationConfig;

    CPmxMaterialConfig m_kMaterialConfig;

    int32_t m_nAnchorRigidBodyCount = 0;
    std::vector< CPmxAnchorRigidBody > m_kAnchorRigidBodys;

    int32_t m_nVertexPinCount = 0;
    std::vector< int32_t > m_kVertexPins;
};

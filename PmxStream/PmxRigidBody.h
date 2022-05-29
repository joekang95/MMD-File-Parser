#pragma once

#include "PmxType.h"
#include "PmxResult.h"

enum class ERigidShapeType : uint8_t
{
    Sphere,         // v2.0
    Box,            // v2.0
    Capsule         // v2.0
};

enum class EPhysicsMode : uint8_t
{
    Bone,           // Stick to bone                v2.0
    Physics,        // Use gravity                  v2.0
    PhysicsAndBone  // Use gravity pivoted to bone  v2.0
};

class CPmxRigidBody
{

public:
    const std::wstring& LocalName() const { return m_strLocalName; }
    std::wstring& LocalName() { return m_strLocalName; }

    const std::wstring& GlobalName() const { return m_strGlobalName; }
    std::wstring& GlobalName() { return m_strGlobalName; }

    const int32_t& TargetBoneIndex() const { return m_nTargetBoneIndex; }
    int32_t& TargetBoneIndex() { return m_nTargetBoneIndex; }

    const uint8_t& GroupId() const { return m_uGroupId; }
    uint8_t& GroupId() { return m_uGroupId; }

    const uint16_t& NonCollisionMask() const { return m_uNonCollisionMask; }
    uint16_t& NonCollisionMask() { return m_uNonCollisionMask; }

    const ERigidShapeType& ShapeType() const { return m_eShapeType; }
    ERigidShapeType& ShapeType() { return m_eShapeType; }

    const CVector3f& ShapeSize() const { return m_vShapeSize; }
    CVector3f& ShapeSize() { return m_vShapeSize; }

    const CVector3f& ShapePosition() const { return m_vShapePosition; }
    CVector3f& ShapePosition() { return m_vShapePosition; }

    const CVector3f& ShapeRotation() const { return m_vShapeRotation; }
    CVector3f& ShapeRotation() { return m_vShapeRotation; }

    const float& Mass() const { return m_fMass; }
    float& Mass() { return m_fMass; }

    const float& MoveAttenuation() const { return m_fMoveAttenuation; }
    float& MoveAttenuation() { return m_fMoveAttenuation; }

    const float& RotateDamping() const { return m_fRotateDamping; }
    float& RotateDamping() { return m_fRotateDamping; }

    const float& Repulsion() const { return m_fRepulsion; }
    float& Repulsion() { return m_fRepulsion; }

    const float& Friction() const { return m_fFriction; }
    float& Friction() { return m_fFriction; }

    const EPhysicsMode& PhysicsMode() const { return m_ePhysicsMode; }
    EPhysicsMode& PhysicsMode() { return m_ePhysicsMode; }

private:
    std::wstring m_strLocalName  = L""; // Usually in Japanese
    std::wstring m_strGlobalName = L""; // Usually in English 

    int32_t m_nTargetBoneIndex = 0;
    uint8_t m_uGroupId = 0;

    uint16_t m_uNonCollisionMask = 0;
    ERigidShapeType m_eShapeType;

    CVector3f m_vShapeSize;
    CVector3f m_vShapePosition;
    CVector3f m_vShapeRotation;

    float m_fMass            = 0.0f;
    float m_fMoveAttenuation = 0.0f;
    float m_fRotateDamping   = 0.0f;
    float m_fRepulsion       = 0.0f;
    float m_fFriction        = 0.0f;

    EPhysicsMode m_ePhysicsMode;

};

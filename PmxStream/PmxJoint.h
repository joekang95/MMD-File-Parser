#pragma once

#include "PmxType.h"
#include "PmxResult.h"

enum class EJointType : uint8_t
{
    Generic6DofSpring, // v2.0
    Generic6Dof,       // v2.1
    Point2Point,       // v2.1
    ConeTwist,         // v2.1
    Slider,            // v2.1
    Hinge              // v2.1
};                     // v2.1

class CPmxJoint
{
public:
    const std::wstring& LocalName() const { return m_strLocalName; }
    std::wstring& LocalName() { return m_strLocalName; }

    const std::wstring& GlobalName() const { return m_strGlobalName; }
    std::wstring& GlobalName() { return m_strGlobalName; }

    const EJointType& JointType() const { return m_eJointType; }
    EJointType& JointType() { return m_eJointType; }

    const int32_t& RigidBodyIndexA() const { return m_nRigidBodyIndexA; }
    int32_t& RigidBodyIndexA() { return m_nRigidBodyIndexA; }

    const int32_t& RigidBodyIndexB() const { return m_nRigidBodyIndexB; }
    int32_t& RigidBodyIndexB() { return m_nRigidBodyIndexB; }

    const CVector3f& Position() const { return m_vPosition; }
    CVector3f& Position() { return m_vPosition; }

    const CVector3f& Rotation() const { return m_vRotation; }
    CVector3f& Rotation() { return m_vRotation; }

    const CVector3f& MinPosition() const { return m_vMinPosition; }
    CVector3f& MinPosition() { return m_vMinPosition; }

    const CVector3f& MaxPosition() const { return m_vMaxPosition; }
    CVector3f& MaxPosition() { return m_vMaxPosition; }

    const CVector3f& MinRotation() const { return m_vMinRotation; }
    CVector3f& MinRotation() { return m_vMinRotation; }

    const CVector3f& MaxRotation() const { return m_vMaxRotation; }
    CVector3f& MaxRotation() { return m_vMaxRotation; }

    const CVector3f& SpringPosition() const { return m_vSpringPosition; }
    CVector3f& SpringPosition() { return m_vPosition; }

    const CVector3f& SpringRotation() const { return m_vSpringRotation; }
    CVector3f& SpringRotation() { return m_vSpringRotation; }

private:
    std::wstring m_strLocalName  = L""; // Usually in Japanese
    std::wstring m_strGlobalName = L""; // Usually in English 

    EJointType m_eJointType;

    int32_t m_nRigidBodyIndexA = 0;
    int32_t m_nRigidBodyIndexB = 0;

    CVector3f m_vPosition;
    CVector3f m_vRotation;

    CVector3f m_vMinPosition;
    CVector3f m_vMaxPosition;

    CVector3f m_vMinRotation;
    CVector3f m_vMaxRotation;

    CVector3f m_vSpringPosition;
    CVector3f m_vSpringRotation;
};
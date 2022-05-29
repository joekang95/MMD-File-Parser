#pragma once

#include "PmxType.h"
#include "PmxResult.h"

#include <vector>

enum class EBoneFlag : uint16_t
{
    Empty                = 0x0000,
    IndexedTailPosition  = 0x0001,
    Rotatable            = 0x0002,
    Translatable         = 0x0004,
    Visible              = 0x0008,
    Enabled              = 0x0010,
    IK                   = 0x0020,
    InheritRotation      = 0x0100,
    InheritTranslation   = 0x0200,
    FixedAxis            = 0x0400,
    LocalCoordinate      = 0x0800,
    PhysicsAfterDeform   = 0x1000,
    ExternalParentDeform = 0x2000
};

class CPmxIkLink
{
public:
    const int32_t& BoneIndex() const { return m_nBoneIndex; }
    int32_t& BoneIndex() { return m_nBoneIndex; }

    const bool& Limit() const { return m_bLimit; }
    bool& Limit() { return m_bLimit; }

    const CVector3f& MinAngle() const { return m_vMinAngle; }
    CVector3f& MinAngle() { return m_vMinAngle; }

    const CVector3f& MaxAngle() const { return m_vMaxAngle; }
    CVector3f& MaxAngle() { return m_vMaxAngle; }

private:
    int32_t m_nBoneIndex = 0;
    bool    m_bLimit = false;

    CVector3f m_vMinAngle;
    CVector3f m_vMaxAngle;
};

class CPmxIkBone
{
public:
    const int32_t& TargetIndex() const { return m_nTargetIndex; }
    int32_t& TargetIndex() { return m_nTargetIndex; }

    const int32_t& LoopCount() const { return m_nLoopCount; }
    int32_t& LoopCount() { return m_nLoopCount; }

    const float& LimitRadian() const { return m_fLimitRadian; }
    float& LimitRadian() { return m_fLimitRadian; }

    const int32_t& LinkCount() const { return m_nLinkCount; }
    int32_t& LinkCount() { return m_nLinkCount; }

    const std::vector< CPmxIkLink >& IkLinks() const { return m_kIkLinks; }
    std::vector< CPmxIkLink >& IkLinks() { return m_kIkLinks; }

private:
    int32_t m_nTargetIndex = 0;
    int32_t m_nLoopCount   = 0;
    float   m_fLimitRadian = 0.0f;
    int32_t m_nLinkCount   = 0;

    std::vector< CPmxIkLink > m_kIkLinks;
};

class CPmxBone
{
public:
    const std::wstring& LocalName() const { return m_strLocalName; }
    std::wstring& LocalName() { return m_strLocalName; }

    const std::wstring& GlobalName() const { return m_strGlobalName; }
    std::wstring& GlobalName() { return m_strGlobalName; }

    const CVector3f& Position() const { return m_vPosition; }
    CVector3f& Position() { return m_vPosition; }

    const int32_t& ParentIndex() const { return m_nParentIndex; }
    int32_t& ParentIndex() { return m_nParentIndex; }

    const int32_t& Layer() const { return m_nLayer; }
    int32_t& Layer() { return m_nLayer; }

    const EBoneFlag& BoneFlag() const { return m_eBoneFlag; }
    EBoneFlag& BoneFlag() { return m_eBoneFlag; }

    const CVector3f& TailPositionVec() const { return m_vTailPosition; }
    CVector3f& TailPositionVec() { return m_vTailPosition; }

    const int32_t& TailPosition() const { return m_nTailPosition; }
    int32_t& TailPosition() { return m_nTailPosition; }

    const int32_t& InheritParentIndex() const { return m_nInheritParentIndex; }
    int32_t& InheritParentIndex() { return m_nInheritParentIndex; }

    const float& InheritParentWeight() const { return m_fInheritParentWeight; }
    float& InheritParentWeight() { return m_fInheritParentWeight; }

    const CVector3f& AxisDirection() const { return m_vAxisDirection; }
    CVector3f& AxisDirection() { return m_vAxisDirection; }

    const CVector3f& LocalX() const { return m_vLocalX; }
    CVector3f& LocalX() { return m_vLocalX; }

    const CVector3f& LocalZ() const { return m_vLocalZ; }
    CVector3f& LocalZ() { return m_vLocalZ; }

    const int32_t& ExternalParentIndex() const { return m_nExternalParentIndex; }
    int32_t& ExternalParentIndex() { return m_nExternalParentIndex; }

    const CPmxIkBone& IkBone() const { return m_kIkBone; }
    CPmxIkBone& IkBone() { return m_kIkBone; }

private:
    std::wstring m_strLocalName  = L""; // Usually in Japanese
    std::wstring m_strGlobalName = L""; // Usually in English 

    CVector3f m_vPosition;

    int32_t m_nParentIndex = 0;
    int32_t m_nLayer = 0;

    EBoneFlag m_eBoneFlag = EBoneFlag::Empty;

    // EBoneFlag::IndexedTailPosition
    CVector3f m_vTailPosition;      // If not set
    int32_t   m_nTailPosition = 0;  // If set

    // EBoneFlag::InheritRotation or EBoneFlag::InheritTranslation
    int32_t m_nInheritParentIndex  = 0; 
    float   m_fInheritParentWeight = 0.0f;

    // EBoneFlag::FixedAxis
    CVector3f m_vAxisDirection;

    // EBoneFlag::LocalCoordinate
    CVector3f m_vLocalX;
    CVector3f m_vLocalZ;

    // EBoneFlag::ExternalParentDeform
    int32_t m_nExternalParentIndex = 0;

    // EBoneFlag::IK
    CPmxIkBone m_kIkBone;
};
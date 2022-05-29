#pragma once
#include "PmxType.h"
#include "PmxResult.h"

#include <memory>
#include <vector>

enum class ESkinningType : int8_t
{
    INVALID = -1,
    BDEF1,  // Linear Blend Skinning
    BDEF2,  // Linear Blend Skinning
    BDEF4,  // Linear Blend Skinning
    SDEF,   // Spherical Blend Skinning
    QDEF    // Dual Quaternion Skinning
};

class CPmxSkinningBase
{
public:
    virtual PmxResult Read( std::istream* pStream, const int32_t& nSize ) = 0;
};

class CPmxSkinningBDEF1 : public CPmxSkinningBase
{
public:
    virtual PmxResult Read( std::istream* pStream, const int32_t& nSize ) override;

private:
    int32_t m_nBoneIndex = -1;
};

class CPmxSkinningBDEF2 : public CPmxSkinningBase
{
public:
    virtual PmxResult Read( std::istream* pStream, const int32_t& nSize ) override;

private:
    int32_t m_nBoneIndex1 = -1;
    int32_t m_nBoneIndex2 = -1;
    float   m_fBone1Weight = 0.0f;
};

class CPmxSkinningBDEF4 : public CPmxSkinningBase
{
public:
    virtual PmxResult Read( std::istream* pStream, const int32_t& nSize ) override;

private:
    int32_t m_nBoneIndex1 = -1;
    int32_t m_nBoneIndex2 = -1;
    int32_t m_nBoneIndex3 = -1;
    int32_t m_nBoneIndex4 = -1;
    float   m_fBone1Weight = 0.0f; 
    float   m_fBone2Weight = 0.0f;
    float   m_fBone3Weight = 0.0f;
    float   m_fBone4Weight = 0.0f;
};

class CPmxSkinningSDEF : public CPmxSkinningBase
{
public:
    virtual PmxResult Read( std::istream* pStream, const int32_t& nSize ) override;

private:
    int32_t m_nBoneIndex1 = -1;
    int32_t m_nBoneIndex2 = -1;
    float   m_fBone1Weight = 0.0f;

    CVector3f m_vC;
    CVector3f m_vR0;
    CVector3f m_vR1;
};

class CPmxSkinningQDEF : public CPmxSkinningBase
{
public:
    virtual PmxResult Read( std::istream* pStream, const int32_t& nSize ) override;

private:
    int32_t m_nBoneIndex1 = -1;
    int32_t m_nBoneIndex2 = -1;
    int32_t m_nBoneIndex3 = -1;
    int32_t m_nBoneIndex4 = -1;
    float   m_fBone1Weight = 0.0f;
    float   m_fBone2Weight = 0.0f;
    float   m_fBone3Weight = 0.0f;
    float   m_fBone4Weight = 0.0f;
};


class CPmxVertex
{
public:
    CPmxVertex() {};

    const CVector3f& Position() const { return m_vPosition; }
    CVector3f& Position()             { return m_vPosition; }

    const CVector3f& Normal() const { return m_vNorlmal; }
    CVector3f& Normal()             { return m_vNorlmal; }

    const CVector2f& Uv() const { return m_vUV; }
    CVector2f& Uv()             { return m_vUV; }

    const std::vector< CVector4f >& Additionals() const { return m_kAddtionals; }
    std::vector< CVector4f >& Additionals()             { return m_kAddtionals; }

    const ESkinningType& SkinningType() const { return m_eSkinningType; }
    ESkinningType& SkinningType()             { return m_eSkinningType; }

    const std::unique_ptr< CPmxSkinningBase >& SkinningData() const { return m_pSkinning; }
    std::unique_ptr< CPmxSkinningBase >& SkinningData()             { return m_pSkinning; }

    const float& EdgeScale() const { return m_fEdgeScale; }
    float& EdgeScale() { return m_fEdgeScale; }

private:
    CVector3f m_vPosition;
    CVector3f m_vNorlmal;
    CVector2f m_vUV;
    std::vector< CVector4f > m_kAddtionals;

    ESkinningType m_eSkinningType = ESkinningType::INVALID;

    std::unique_ptr< CPmxSkinningBase > m_pSkinning;
    
    float m_fEdgeScale = 0.0f;
};
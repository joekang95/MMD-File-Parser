#pragma once

#include "PmxType.h"
#include "PmxResult.h"

#include <vector>
#include <memory>

enum class EMorphPanel : uint8_t
{
    Hidden,     // None
    Eyebrows,   // Bottom Left
    Eyes,       // Top Left
    Mouth,      // Top Right
    Other       // Bottom Right
};

enum class EMorphType : uint8_t
{
    Group,      // v2.0
    Vertex,     // v2.0
    Bone,       // v2.0
    Uv,         // v2.0
    UvExt1,     // v2.0
    UvExt2,     // v2.0
    UvExt3,     // v2.0
    UvExt4,     // v2.0
    Material,   // v2.0
    Flip,       // v2.1
    Impulse     // v2.1
};

class CPmxMorphOffsetData
{
public:
    virtual PmxResult Read( std::istream* pStream, const int32_t& nSize ) = 0;
};

class CPmxGroupOffsetData : public CPmxMorphOffsetData
{
public:
    virtual PmxResult Read( std::istream* pStream, const int32_t& nMorphIndexSize ) override;

    const int32_t& MorphIndex() const { return m_nMorphIndex; }
    int32_t& MorphIndex() { return m_nMorphIndex; }

    const float& Weight() const { return m_fWeight; }
    float& Weight() { return m_fWeight; }

private:
    int32_t m_nMorphIndex = 0;
    float   m_fWeight = 0.0f;
};

class CPmxVertexOffsetData : public CPmxMorphOffsetData
{
public:
    virtual PmxResult Read( std::istream* pStream, const int32_t& nVertexIndexSize ) override;

    const int32_t& VertexIndex() const { return m_nVertexIndex; }
    int32_t& VertexIndex() { return m_nVertexIndex; }

    const CVector3f& Offset() const { return m_vOffset; }
    CVector3f& Offset() { return m_vOffset; }

private:
    int32_t   m_nVertexIndex = 0;
    CVector3f m_vOffset;
};

class CPmxBoneOffsetData : public CPmxMorphOffsetData
{
public:
    virtual PmxResult Read( std::istream* pStream, const int32_t& nBoneIndexSize ) override;

    const int32_t& BoneIndex() const { return m_nBoneIndex; }
    int32_t& BoneIndex() { return m_nBoneIndex; }

    const CVector3f& Translate() const { return m_vTranslate; }
    CVector3f& Translate() { return m_vTranslate; }

    const CVector4f& Rotate() const { return m_vRotate; }
    CVector4f& Rotates() { return m_vRotate; }

private:
    int32_t   m_nBoneIndex = 0;
    CVector3f m_vTranslate;
    CVector4f m_vRotate;
};

class CPmxUvOffsetData : public CPmxMorphOffsetData
{
public:
    virtual PmxResult Read( std::istream* pStream, const int32_t& nVertexIndexSize ) override;

    const int32_t& VertexIndex() const { return m_nVertexIndex; }
    int32_t& VertexIndex() { return m_nVertexIndex; }

    const CVector4f& Offset() const { return m_vOffset; }
    CVector4f& Offset() { return m_vOffset; }

private:
    int32_t   m_nVertexIndex = 0;
    CVector4f m_vOffset;
};

class CPmxMaterialOffsetData : public CPmxMorphOffsetData
{
public:
    virtual PmxResult Read( std::istream* pStream, const int32_t& nMaterialIndexSize ) override;

    const int32_t& MaterialIndex() const { return m_nMaterialIndex; }
    int32_t& MaterialIndex() { return m_nMaterialIndex; }

    const uint8_t& OffsetOperation() const { return m_uOffsetOperation; }
    uint8_t& OffsetOperation() { return m_uOffsetOperation; }

    const CVector4f& DiffuseColor() const { return m_vDiffuseColor; }
    CVector4f& DiffuseColor() { return m_vDiffuseColor; }

    const CVector3f& SpecularColor() const { return m_vSpecularColor; }
    CVector3f& SpecularColor() { return m_vSpecularColor; }

    const float& Specularity() const { return m_fSpecularity; }
    float& Specularity() { return m_fSpecularity; }

    const CVector3f& AmbientColor() const { return m_vAmbientColor; }
    CVector3f& AmbientColor() { return m_vAmbientColor; }

    const CVector4f& EdgeColor() const { return m_vEdgeColor; }
    CVector4f& EdgeColor() { return m_vEdgeColor; }

    const CVector4f& TextureTint() const { return m_vTextureTint; }
    CVector4f& TextureTint() { return m_vTextureTint; }

    const CVector4f& EnvironmentTint() const { return m_vEnvironmentTint; }
    CVector4f& EnvironmentTint() { return m_vEnvironmentTint; }

    const CVector4f& ToonTint() const { return m_vToonTint; }
    CVector4f& ToonTint() { return m_vToonTint; }

private:
    int32_t   m_nMaterialIndex = 0;
    uint8_t   m_uOffsetOperation = 0;
    CVector4f m_vDiffuseColor;
    CVector3f m_vSpecularColor;
    float     m_fSpecularity = 0.0f;
    CVector3f m_vAmbientColor;
    CVector4f m_vEdgeColor;
    float     m_fEdgeScale = 0.0f;
    CVector4f m_vTextureTint;      // ARGB
    CVector4f m_vEnvironmentTint;  // ARGB
    CVector4f m_vToonTint;         // ARGB
};

class CPmxFlipOffsetData : public CPmxMorphOffsetData
{
public:
    virtual PmxResult Read( std::istream* pStream, const int32_t& nMorphIndexSize ) override;

    const int32_t& MorphIndex() const { return m_nMorphIndex; }
    int32_t& MorphIndex() { return m_nMorphIndex; }

    const float& Weight() const { return m_fWeight; }
    float& Weight() { return m_fWeight; }

private:
    int32_t m_nMorphIndex = 0;
    float   m_fWeight = 0.0f;
};

class CPmxImpulseOffsetData : public CPmxMorphOffsetData
{
public:
    virtual PmxResult Read( std::istream* pStream, const int32_t& nRigidBodyIndexSize ) override;

    const int32_t& RigidBodyIndex() const { return m_nRigidBodyIndex; }
    int32_t& RigidBodyIndex() { return m_nRigidBodyIndex; }

    const bool& IsLocal() const { return m_bLocal; }
    bool& IsLocal() { return m_bLocal; }

    const CVector3f& Velocity() const { return m_vVelocity; }
    CVector3f& Velocity() { return m_vVelocity; }

    const CVector3f& Torque() const { return m_vTorque; }
    CVector3f& Torque() { return m_vTorque; }

private:
    int32_t   m_nRigidBodyIndex = 0;
    bool      m_bLocal = false;
    CVector3f m_vVelocity;
    CVector3f m_vTorque;
};

class CPmxMorph
{
public:
    const std::wstring& LocalName() const { return m_strLocalName; }
    std::wstring& LocalName() { return m_strLocalName; }

    const std::wstring& GlobalName() const { return m_strGlobalName; }
    std::wstring& GlobalName() { return m_strGlobalName; }

    const EMorphPanel& MorphPanel() const { return m_ePanel; }
    EMorphPanel& MorphPanel() { return m_ePanel; }

    const EMorphType& MorphType() const { return m_eType; }
    EMorphType& MorphType() { return m_eType; }

    const int32_t& OffsetCount() const { return m_nOffsetCount; }
    int32_t& OffsetCount() { return m_nOffsetCount; }

    const std::vector< std::unique_ptr< CPmxMorphOffsetData > >& MorphOffsets() const { return m_kMorphOffsets; }
    std::vector< std::unique_ptr< CPmxMorphOffsetData > >& MorphOffsets() { return m_kMorphOffsets; }

private:
    std::wstring m_strLocalName  = L""; // Usually in Japanese
    std::wstring m_strGlobalName = L""; // Usually in English 

    EMorphPanel m_ePanel; // Morph Panel Type
    EMorphType  m_eType;

    int32_t m_nOffsetCount = 0;

    std::vector< std::unique_ptr< CPmxMorphOffsetData > > m_kMorphOffsets;
};
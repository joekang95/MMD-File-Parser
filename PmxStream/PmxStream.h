#pragma once
#include "PmxResult.h"
#include "PmxVertex.h"
#include "PmxMaterial.h"
#include "PmxBone.h"
#include "PmxMorph.h"
#include "PmxFrame.h"
#include "PmxRigidBody.h"
#include "PmxJoint.h"
#include "PmxSoftBody.h"

#include <vector>
#include <string>
#include <fstream>
#include <memory>

enum EGlobalSetting
{
    TextEncoding,
    AddtionalVec4Count,
    VertexIndexSize,
    TextureIndexSize,
    MaterialIndexSize,
    BoneIndexSize,
    MorphIndexSize,
    RigidBodyIndexSize,
};

class CPmxStream
{
public:
    CPmxStream() {};
    PmxResult Load( const std::wstring& strFilePath );

protected:
    bool FloatEqual( const float& fA, const float& fB );

    PmxResult ReadHeader();
    PmxResult ReadVertex();
    PmxResult ReadFace();
    PmxResult ReadTexture();
    PmxResult ReadMaterial();
    PmxResult ReadBone();
    PmxResult ReadMorph();
    PmxResult ReadFrame();
    PmxResult ReadRigidBody();
    PmxResult ReadJoint();
    PmxResult ReadSoftBody();

private:
    std::ifstream m_kStream;

    float m_fVersion = 0.0f;

    std::vector< uint8_t > m_kGlobalSettings;

    std::wstring m_strModelNameLocal  = L"";  // Usually in Japanese
    std::wstring m_strModelNameGlobal = L"";  // Usually in English 
    std::wstring m_strCommentsLocal   = L"";  // Usually in Japanese
    std::wstring m_strCommentsGlobal  = L"";  // Usually in English

    // Vertex
    int32_t m_nVertexCount = 0;
    std::vector< CPmxVertex > m_kVertices;

    // Surface ( Clockwise )
    int32_t m_nIndexCount = 0;
    std::vector< int32_t > m_kIndices;

    // Texture
    int32_t m_nTextureCount = 0;
    std::vector< std::wstring > m_kTextures;

    // Material
    int32_t m_nMaterialCount = 0;
    std::vector< CPmxMaterial > m_kMaterials;

    // Bone
    int32_t m_nBoneCount = 0;
    std::vector< CPmxBone > m_kBones;

    // Morph
    int32_t m_nMorphCount = 0;
    std::vector< CPmxMorph > m_kMorphs;

    // Frame
    int32_t m_nFrameCount = 0;
    std::vector< CPmxFrame > m_kFrames;

    // Rigid Body
    int32_t m_nRigidBodyCount = 0;
    std::vector< CPmxRigidBody > m_kRigidBodys;

    // Joint
    int32_t m_nJointCount = 0;
    std::vector< CPmxJoint > m_kJoints;

    // Soft Body
    int32_t m_nSoftBodyCount = 0;
    std::vector< CPmxSoftBody > m_kSoftBodys;
};
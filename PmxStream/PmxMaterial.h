#pragma once

#include "PmxType.h"
#include "PmxResult.h"

enum class EMaterialFlag : uint8_t
{
    NoCull        = 0x01,  // Disables Back-Face Culling                v2.0
    GroundShadow  = 0x02,  // Projects shadow onto geometry             v2.0
    DrawShadow    = 0x04,  // Renders to the shadow map                 v2.0
    ReceiveShadow = 0x08,  // Receives a shadow from the shadow map     v2.0
    HasEdge       = 0x10,  // Has "pencil" outline                      v2.0
    VertexColor   = 0x20,  // Uses additional vec4 1 for vertex color   v2.1
    PointDrawing  = 0x40,  // Each of the 3 vertices are points         v2.1
    LineDrawing   = 0x80   // The triangle is rendered as lines         v2.1
};

class CPmxMaterial
{
public:
    const std::wstring& LocalName() const { return m_strLocalName; }
    std::wstring& LocalName() { return m_strLocalName; }

    const std::wstring& GlobalName() const { return m_strGlobalName; }
    std::wstring& GlobalName() { return m_strGlobalName; }

    const CVector4f& DiffuseColor() const { return m_vDiffuseColor; }
    CVector4f& DiffuseColor() { return m_vDiffuseColor; }

    const CVector3f& Specular() const { return m_vSpecularColor; }
    CVector3f& SpecularColor() { return m_vSpecularColor; }

    const float& Specularity() const { return m_fSpecularity; }
    float& Specularity() { return m_fSpecularity; }

    const CVector3f& AmbientColor() const { return m_vAmbientColor; }
    CVector3f& AmbientColor() { return m_vAmbientColor; }

    const EMaterialFlag& DrawingFlag() const { return m_eDrawingFlag; }
    EMaterialFlag& DrawingFlag() { return m_eDrawingFlag; }

    const CVector4f& EdgeColor() const { return m_vEdgeColor; }
    CVector4f& EdgeColor() { return m_vEdgeColor; }

    const float& EdgeScale() const { return m_fEdgeScale; }
    float& EdgeScale() { return m_fEdgeScale; }

    const int32_t& TextureIndex() const { return m_nTextureIndex; }
    int32_t& TextureIndex() { return m_nTextureIndex; }

    const int32_t& EnvironmentIndex() const { return m_nEnvironmentIndex; }
    int32_t& EnvironmentIndex() { return m_nEnvironmentIndex; }

    const uint8_t& EnvironmentBlendMode() const { return m_uEnvironmentBlendMode; }
    uint8_t& EnvironmentBlendMode() { return m_uEnvironmentBlendMode; }

    const uint8_t& ToonReference() const { return m_uToonReference; }
    uint8_t& ToonReference() { return m_uToonReference; }

    const int32_t& ToonValue() const { return m_nToonValue; }
    int32_t& ToonValue() { return m_nToonValue; }

    const std::wstring& MetaData() const { return m_strMetaData; }
    std::wstring& MetaData() { return m_strMetaData; }

    const int32_t& SurfaceCount() const { return m_nSurfaceCount; }
    int32_t& SurfaceCount() { return m_nSurfaceCount; }

private:
    std::wstring m_strLocalName  = L""; // Usually in Japanese
    std::wstring m_strGlobalName = L""; // Usually in English 

    CVector4f m_vDiffuseColor;                  // RGBA
    CVector3f m_vSpecularColor;                 // RGB
    float     m_fSpecularity = 0.0f;            // alpha
    CVector3f m_vAmbientColor;                  // RGB

    EMaterialFlag m_eDrawingFlag;

    CVector4f m_vEdgeColor;                     // RGBA of pencil-outline edge
    float m_fEdgeScale = 0.0f;

    int32_t m_nTextureIndex = -1;
    int32_t m_nEnvironmentIndex = -1;

    /*
    * Environment blend mode 3 will use the first additional vec4 to map the environment texture
    * using just the X and Y values as the texture UV. It is mapped as an additional texture layer.
    * This may conflict with other uses for the first additional vec4.
    */
    uint8_t m_uEnvironmentBlendMode = 0;        // 0 = disabled, 1 = multiply, 2 = additive, 3 = additional vec4

    uint8_t m_uToonReference = 0;               // 0 = Texture reference, 1 = internal reference
    /*
    * Toon value will be a texture index much like the standard texture and environment texture indexes
    * unless the Toon reference byte is equal to 1,
    * in which case Toon value will be a byte that references a set of 10 internal toon textures
    * Most implementations will use "toon01.bmp" to "toon10.bmp" as the internal textures.
    */
    int32_t m_nToonValue = -1;

    std::wstring m_strMetaData = L"";           // This is used for scripting or additional data

    /*
    * Always be a multiple of 3. 
    * It is based on the offset of the previous material through to the size of the current material.
    * If you add up all the surface counts for all materials you should end up with the total number of surfaces.
    */
    int32_t m_nSurfaceCount = -1;               // How many surfaces this material affects
};
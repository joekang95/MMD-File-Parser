#include "PmxMorph.h"
#include "StreamTool.h"

PmxResult CPmxGroupOffsetData::Read( std::istream* pStream, const int32_t& nMorphIndexSize )
{
    ReadIndex( pStream, nMorphIndexSize, m_nMorphIndex );
    ReadStream( pStream, m_fWeight );
    return PMX_SUCCESS;
}

PmxResult CPmxVertexOffsetData::Read( std::istream* pStream, const int32_t& nVertexIndexSize )
{
    ReadIndex( pStream, nVertexIndexSize, m_nVertexIndex );
    ReadStream( pStream, m_vOffset );
    return PMX_SUCCESS;
}

PmxResult CPmxBoneOffsetData::Read( std::istream* pStream, const int32_t& nBoneIndexSize )
{
    ReadIndex( pStream, nBoneIndexSize, m_nBoneIndex );
    ReadStream( pStream, m_vTranslate );
    ReadStream( pStream, m_vRotate    );
    return PMX_SUCCESS;
}

PmxResult CPmxUvOffsetData::Read( std::istream* pStream, const int32_t& nVertexIndexSize )
{
    ReadIndex( pStream, nVertexIndexSize, m_nVertexIndex );
    ReadStream( pStream, m_vOffset );
    return PMX_SUCCESS;
}

PmxResult CPmxMaterialOffsetData::Read( std::istream* pStream, const int32_t& nMaterialIndexSize )
{
    ReadIndex( pStream, nMaterialIndexSize, m_nMaterialIndex );
    ReadStream( pStream, m_uOffsetOperation );
    ReadStream( pStream, m_vDiffuseColor    );
    ReadStream( pStream, m_vSpecularColor   );
    ReadStream( pStream, m_fSpecularity     );
    ReadStream( pStream, m_vAmbientColor    );
    ReadStream( pStream, m_vEdgeColor       );
    ReadStream( pStream, m_vTextureTint     );
    ReadStream( pStream, m_vEnvironmentTint );
    ReadStream( pStream, m_vToonTint        );
    return PMX_SUCCESS;
}

PmxResult CPmxFlipOffsetData::Read( std::istream* pStream, const int32_t& nMorphIndexSize )
{
    ReadIndex( pStream, nMorphIndexSize, m_nMorphIndex );
    ReadStream( pStream, m_fWeight );
    return PMX_SUCCESS;
}

PmxResult CPmxImpulseOffsetData::Read( std::istream* pStream, const int32_t& nRigidBodyIndexSize )
{
    ReadIndex( pStream, nRigidBodyIndexSize, m_nRigidBodyIndex );
    ReadStream( pStream, m_bLocal    );
    ReadStream( pStream, m_vVelocity );
    ReadStream( pStream, m_vTorque   );
    return PMX_SUCCESS;
}
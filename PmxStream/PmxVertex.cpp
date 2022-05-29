#include "PmxVertex.h"
#include "StreamTool.h"

PmxResult CPmxSkinningBDEF1::Read( std::istream* pStream, const int32_t& nSize )
{
    PmxInvalidCall( pStream );
    ReadIndex( pStream, nSize, m_nBoneIndex );
    return PMX_SUCCESS;
}

PmxResult CPmxSkinningBDEF2::Read( std::istream* pStream, const int32_t& nSize )
{
    PmxInvalidCall( pStream );
    ReadIndex( pStream, nSize, m_nBoneIndex1 );
    ReadIndex( pStream, nSize, m_nBoneIndex2 );

    ReadStream( pStream, m_fBone1Weight );

    return PMX_SUCCESS;
}

PmxResult CPmxSkinningBDEF4::Read( std::istream* pStream, const int32_t& nSize )
{
    PmxInvalidCall( pStream );
    ReadIndex( pStream, nSize, m_nBoneIndex1 );
    ReadIndex( pStream, nSize, m_nBoneIndex2 );
    ReadIndex( pStream, nSize, m_nBoneIndex3 );
    ReadIndex( pStream, nSize, m_nBoneIndex4 );

    ReadStream( pStream, m_fBone1Weight );
    ReadStream( pStream, m_fBone2Weight );
    ReadStream( pStream, m_fBone3Weight );
    ReadStream( pStream, m_fBone4Weight );

    return PMX_SUCCESS;
}

PmxResult CPmxSkinningSDEF::Read( std::istream* pStream, const int32_t& nSize )
{
    PmxInvalidCall( pStream );
    ReadIndex( pStream, nSize, m_nBoneIndex1 );
    ReadIndex( pStream, nSize, m_nBoneIndex2 );

    ReadStream( pStream, m_fBone1Weight );
    ReadStream( pStream, m_vC );
    ReadStream( pStream, m_vR0 );
    ReadStream( pStream, m_vR1 );

    return PMX_SUCCESS;
}

PmxResult CPmxSkinningQDEF::Read( std::istream* pStream, const int32_t& nSize )
{
    PmxInvalidCall( pStream );
    ReadIndex( pStream, nSize, m_nBoneIndex1 );
    ReadIndex( pStream, nSize, m_nBoneIndex2 );
    ReadIndex( pStream, nSize, m_nBoneIndex3 );
    ReadIndex( pStream, nSize, m_nBoneIndex4 );

    ReadStream( pStream, m_fBone1Weight );
    ReadStream( pStream, m_fBone2Weight );
    ReadStream( pStream, m_fBone3Weight );
    ReadStream( pStream, m_fBone4Weight );

    return PMX_SUCCESS;
}
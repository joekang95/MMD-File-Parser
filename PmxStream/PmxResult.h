#pragma once
#include <assert.h>
struct PmxResult
{
    PmxResult() : m_nResult( 0 ) {};
    explicit PmxResult( int nResult ) : m_nResult( nResult ) {};

    bool operator<( const PmxResult& kResult ) const { return m_nResult < kResult.m_nResult; }

    int m_nResult;
};

#define PMX_NOT_IMPLEMENTED PmxResult( -3 )
#define PMX_INVAILD         PmxResult( -2 )
#define PMX_ERROR           PmxResult( -1 )
#define PMX_SUCCESS         PmxResult( 0 )
#define PMX_SAFE            PmxResult( 1 )

#define PmxFailReturn( Func ) \
{\
    PmxResult kResult = Func;\
    if ( kResult < PMX_SUCCESS )\
    {\
        return kResult;\
    }\
}

#define PmxFailReturnAssert( Func ) \
{\
    PmxResult kResult = Func;\
    if ( kResult < PMX_SUCCESS )\
    {\
        assert( 0 );\
        return kResult;\
    }\
}

#define PmxInvalidCall( ptr ) \
if ( !ptr ) \
{ \
    return PMX_INVAILD; \
}
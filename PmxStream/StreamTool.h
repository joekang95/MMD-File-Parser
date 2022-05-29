#pragma once
#include "PmxType.h"
#include <string>
#include <iostream>
#include <windows.h>

#pragma region ReadStream

template< typename T >
inline void ReadStream( std::istream* pStream, T& tValue )
{
    pStream->read( ( char* )&tValue, sizeof( T ) );
}

inline void ReadStream( std::istream* pStream, std::string& strValue, const int32_t& nLength )
{
    strValue.resize( nLength );
    pStream->read( &strValue[ 0 ], nLength );
}

inline PmxResult ReadString( std::istream* pStream, const uint8_t& uEncoding, std::wstring& strText )
{
    int32_t nLength = 0;
    ReadStream( pStream, nLength );
    if( nLength == 0 )
    {
        return PMX_SAFE;
    }
    else if( nLength < 0 )
    {
        assert( 0 );
        return PMX_ERROR;
    }

    std::string strSrcText = "";
    ReadStream( pStream, strSrcText, nLength );

    strText = L"";
    switch( uEncoding )
    {
        case 0:
        {
            // UTF16LE
            strText = std::wstring( ( wchar_t* )&strSrcText[ 0 ], nLength / 2 );
            break;
        }
        case 1:
        {
            // UTF8
            int32_t nSize = MultiByteToWideChar( CP_UTF8, 0, strSrcText.c_str(), nLength, NULL, NULL );
            strText.resize( nSize );
            MultiByteToWideChar( CP_UTF8, 0, strSrcText.c_str(), nLength, &strText[ 0 ], nSize );
            break;
        }
        default:
            return PMX_ERROR;
    }
    return PMX_SUCCESS;
}

inline void ReadIndex( std::istream* pStream, const int32_t& nSize, int32_t& nIndex )
{
    switch( nSize )
    {
        case 1:
        {
            uint8_t uIndex = 0;
            pStream->read( ( char* )&uIndex, nSize );
            nIndex = ( uIndex == 255 ) ? -1 : static_cast< int32_t >( uIndex );
            break;
        }
        case 2:
        {
            uint16_t uIndex = 0;
            pStream->read( ( char* )&uIndex, nSize );
            nIndex = ( uIndex == 65535 ) ? -1 : static_cast< int32_t >( uIndex );
            break;
        }
        case 4:
        {
            pStream->read( ( char* )&nIndex, nSize );
            break;
        }
    }
}
#pragma endregion
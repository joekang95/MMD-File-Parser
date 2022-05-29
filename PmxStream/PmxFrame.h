#pragma once
#include "PmxType.h"
#include "PmxResult.h"

#include <vector>

enum class EFrameType : uint8_t
{
    Bone, // v2.0
    Morph // v2.0
};

class CPmxFrameData
{
public:
    const EFrameType& FrameType() const { return m_eFrameType; }
    EFrameType& FrameType() { return m_eFrameType; }

    const int32_t& FrameIndex() const { return m_nFrameIndex; }
    int32_t& FrameIndex() { return m_nFrameIndex; }

protected:
    EFrameType m_eFrameType;
    int32_t    m_nFrameIndex;
};

class CPmxFrame
{
public:
    const std::wstring& LocalName() const { return m_strLocalName; }
    std::wstring& LocalName() { return m_strLocalName; }

    const std::wstring& GlobalName() const { return m_strGlobalName; }
    std::wstring& GlobalName() { return m_strGlobalName; }

    const bool& IsSpecialFrame() const { return m_bSpecialFrame; }
    bool& IsSpecialFrame() { return m_bSpecialFrame; }

    const int32_t& FrameCount() const { return m_nFrameCount; }
    int32_t& FrameCount() { return m_nFrameCount; }

    const std::vector< CPmxFrameData >& FrameData() const { return m_kFrameData; }
    std::vector< CPmxFrameData >& FrameData() { return m_kFrameData; }

private:
    std::wstring m_strLocalName  = L""; // Usually in Japanese
    std::wstring m_strGlobalName = L""; // Usually in English 

    bool m_bSpecialFrame = false;

    int32_t m_nFrameCount = 0;

    std::vector< CPmxFrameData > m_kFrameData;
};
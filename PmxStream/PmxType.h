#pragma once

#include <string>

class CVector2f
{
public:
    CVector2f() {};
    CVector2f( const float& fX, const float& fY ) : fX( fX ), fY( fY ) {};

    const float& X() const { return fX; }
    float& X() { return fX; }

    const float& Y() const { return fY; }
    float& Y() { return fY; }

private:
    float fX = 0.0f;
    float fY = 0.0f;
};

class CVector3f
{
public:
    CVector3f() {};
    CVector3f( const float& fX, const float& fY, const float& fZ ) : fX( fX ), fY( fY ), fZ( fZ ) {};

    const float& X() const { return fX; }
    float& X() { return fX; }

    const float& Y() const { return fY; }
    float& Y() { return fY; }

    const float& Z() const { return fZ; }
    float& Z() { return fZ; }

private:
    float fX = 0.0f;
    float fY = 0.0f;
    float fZ = 0.0f;
};

class CVector4f
{
public:
    CVector4f() {};
    CVector4f( const float& fX, const float& fY, const float& fZ, const float& fW ) : fX( fX ), fY( fY ), fZ( fZ ), fW( fW ) {};

    const float& X() const { return fX; }
    float& X() { return fX; }

    const float& Y() const { return fY; }
    float& Y() { return fY; }

    const float& Z() const { return fZ; }
    float& Z() { return fZ; }

    const float& W() const { return fW; }
    float& W() { return fW; }

private:
    float fX = 0.0f;
    float fY = 0.0f;
    float fZ = 0.0f;
    float fW = 0.0f;
};
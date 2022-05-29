#include "PmxStream.h"
#include "StreamTool.h"

#include <cmath>

#define FLOAT_CONST_ALMOST_ZERO 0.00001f
#define SIGNATURE_LENGTH 4

bool CPmxStream::FloatEqual( const float& fA, const float& fB )
{
    return std::abs( fA - fB ) < FLOAT_CONST_ALMOST_ZERO;
}

PmxResult CPmxStream::Load( const std::wstring& strFilePath )
{
    m_kStream = std::ifstream( strFilePath, std::ios_base::binary );
    PmxFailReturnAssert( ReadHeader() );
    PmxFailReturnAssert( ReadVertex() );
    PmxFailReturnAssert( ReadFace() );
    PmxFailReturnAssert( ReadTexture() );
    PmxFailReturnAssert( ReadMaterial() );
    PmxFailReturnAssert( ReadBone() );
    PmxFailReturnAssert( ReadMorph() );
    PmxFailReturnAssert( ReadFrame() );
    PmxFailReturnAssert( ReadRigidBody() );
    PmxFailReturnAssert( ReadJoint() );
    PmxFailReturnAssert( ReadSoftBody() );
    if( !m_kStream.eof() )
    {
        assert( 0 );
    }
    return PMX_SUCCESS;
}

PmxResult CPmxStream::ReadHeader()
{
    // Signature
    std::string strSignature = "";
    ReadStream( &m_kStream, strSignature, SIGNATURE_LENGTH );
    if( strSignature != "PMX " ) // Space at end
    {
        return PMX_ERROR;
    }

    // Version
    ReadStream( &m_kStream, m_fVersion );
    if( !FloatEqual( m_fVersion, 2.0f ) && !FloatEqual( m_fVersion, 2.1f ) )
    {
        return PMX_ERROR;
    }

    // Globals
    {
        // Global Count
        uint8_t uCount;
        ReadStream( &m_kStream, uCount );
        if( uCount == 0 )
        {
            return PMX_ERROR;
        }

        // Global Variables
        m_kGlobalSettings.resize( uCount );
        for( int32_t i = 0; i < uCount; ++i )
        {
            ReadStream( &m_kStream, m_kGlobalSettings[ i ] );
        }
    }

    // Model Name and Comments
    const uint8_t& uEncoding = m_kGlobalSettings[ EGlobalSetting::TextEncoding ];
    PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, m_strModelNameLocal  ) );
    PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, m_strModelNameGlobal ) );
    PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, m_strCommentsLocal   ) );
    PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, m_strCommentsGlobal  ) );
    return PMX_SUCCESS;
}

PmxResult CPmxStream::ReadVertex()
{
    ReadStream( &m_kStream, m_nVertexCount );

    m_kVertices.resize( m_nVertexCount );
    const uint8_t& uBoneIndexSize  = m_kGlobalSettings[ EGlobalSetting::BoneIndexSize      ];
    const uint8_t& uAddtionalCount = m_kGlobalSettings[ EGlobalSetting::AddtionalVec4Count ];
    for( auto& kVertex : m_kVertices )
    {
        ReadStream( &m_kStream, kVertex.Position() );
        ReadStream( &m_kStream, kVertex.Normal() );
        ReadStream( &m_kStream, kVertex.Uv() );

        auto& kAdditionals = kVertex.Additionals();
        kAdditionals.resize( uAddtionalCount );
        for( uint8_t i = 0; i < uAddtionalCount; ++i )
        {
            ReadStream( &m_kStream, kAdditionals[ i ] );
        }

        ReadStream( &m_kStream, kVertex.SkinningType() );
        switch( kVertex.SkinningType() )
        {
            case ESkinningType::BDEF1: kVertex.SkinningData() = std::make_unique< CPmxSkinningBDEF1 >();    break;
            case ESkinningType::BDEF2: kVertex.SkinningData() = std::make_unique< CPmxSkinningBDEF2 >();    break;
            case ESkinningType::BDEF4: kVertex.SkinningData() = std::make_unique< CPmxSkinningBDEF4 >();    break;
            case ESkinningType::SDEF:  kVertex.SkinningData() = std::make_unique< CPmxSkinningSDEF >();     break;
            case ESkinningType::QDEF:  kVertex.SkinningData() = std::make_unique< CPmxSkinningQDEF >();     break;
            default: return PMX_ERROR;
        }
        kVertex.SkinningData()->Read( &m_kStream, uBoneIndexSize );

        ReadStream( &m_kStream, kVertex.EdgeScale() );
    }
    return PMX_SUCCESS;
}

PmxResult CPmxStream::ReadFace()
{
    ReadStream( &m_kStream, m_nIndexCount );

    m_kIndices.resize( m_nIndexCount );
    const uint8_t& uVertexIndexSize = m_kGlobalSettings[ EGlobalSetting::VertexIndexSize ];
    for( int32_t i = 0; i < m_nIndexCount; ++i )
    {
        ReadIndex( &m_kStream, uVertexIndexSize, m_kIndices[ i ] );
    }

    return PMX_SUCCESS;
}

PmxResult CPmxStream::ReadTexture()
{
    ReadStream( &m_kStream, m_nTextureCount );

    m_kTextures.resize( m_nTextureCount );
    const uint8_t& uEncoding = m_kGlobalSettings[ EGlobalSetting::TextEncoding ];
    for( int32_t i = 0; i < m_nTextureCount; ++i )
    {
        ReadString( &m_kStream, uEncoding, m_kTextures[ i ] );
    }
    return PMX_SUCCESS;
}

PmxResult CPmxStream::ReadMaterial()
{
    ReadStream( &m_kStream, m_nMaterialCount );

    m_kMaterials.resize( m_nMaterialCount );
    const uint8_t& uEncoding         = m_kGlobalSettings[ EGlobalSetting::TextEncoding     ];
    const uint8_t& uTextureIndexSize = m_kGlobalSettings[ EGlobalSetting::TextureIndexSize ];
    for( auto& kMaterial : m_kMaterials )
    {
        PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, kMaterial.LocalName()  ) );
        PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, kMaterial.GlobalName() ) );

        ReadStream( &m_kStream, kMaterial.DiffuseColor()     );
        ReadStream( &m_kStream, kMaterial.SpecularColor()    );
        ReadStream( &m_kStream, kMaterial.Specularity()      );
        ReadStream( &m_kStream, kMaterial.AmbientColor()     );
        ReadStream( &m_kStream, kMaterial.DrawingFlag()      );
        ReadStream( &m_kStream, kMaterial.EdgeColor()        );
        ReadStream( &m_kStream, kMaterial.EdgeScale()        );

        ReadIndex( &m_kStream, uTextureIndexSize, kMaterial.TextureIndex() );
        ReadIndex( &m_kStream, uTextureIndexSize, kMaterial.EnvironmentIndex() );

        ReadStream( &m_kStream, kMaterial.EnvironmentBlendMode() );
        ReadStream( &m_kStream, kMaterial.ToonReference() );

        if( kMaterial.ToonReference() == 1 )
        {
            // Internal Reference - uint8_t
            ReadIndex( &m_kStream, 1, kMaterial.ToonValue() );
        }
        else
        {
            // Texture Reference
            ReadIndex( &m_kStream, uTextureIndexSize, kMaterial.ToonValue() );
        }

        ReadString( &m_kStream, uEncoding, kMaterial.MetaData() );
        ReadStream( &m_kStream, kMaterial.SurfaceCount() );
    }
    return PMX_SUCCESS;
}

PmxResult CPmxStream::ReadBone()
{
    ReadStream( &m_kStream, m_nBoneCount );

    m_kBones.resize( m_nBoneCount );
    const uint8_t& uEncoding      = m_kGlobalSettings[ EGlobalSetting::TextEncoding  ];
    const uint8_t& uBoneIndexSize = m_kGlobalSettings[ EGlobalSetting::BoneIndexSize ];
    for( auto& kBone : m_kBones )
    {
        PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, kBone.LocalName()  ) );
        PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, kBone.GlobalName() ) );

        ReadStream( &m_kStream, kBone.Position() );

        ReadIndex( &m_kStream, uBoneIndexSize, kBone.ParentIndex() );

        ReadStream( &m_kStream, kBone.Layer() );
        ReadStream( &m_kStream, kBone.BoneFlag() );

        const auto uFlag = ( uint16_t )kBone.BoneFlag();
        if( uFlag & ( uint16_t )EBoneFlag::IndexedTailPosition )
        {
            ReadIndex( &m_kStream, uBoneIndexSize, kBone.TailPosition() );
        }
        else
        {
            ReadStream( &m_kStream, kBone.TailPositionVec() );
        }

        if( uFlag & ( ( uint16_t ) EBoneFlag::InheritRotation | ( uint16_t )EBoneFlag::InheritTranslation ) )
        {
            ReadIndex( &m_kStream, uBoneIndexSize, kBone.InheritParentIndex() );
            ReadStream( &m_kStream, kBone.InheritParentWeight() );
        }

        if( uFlag & ( uint16_t )EBoneFlag::FixedAxis )
        {
            ReadStream( &m_kStream, kBone.AxisDirection() );
        }

        if( uFlag & ( uint16_t )EBoneFlag::LocalCoordinate )
        {
            ReadStream( &m_kStream, kBone.LocalX() );
            ReadStream( &m_kStream, kBone.LocalZ() );
        }

        if( uFlag & ( uint16_t )EBoneFlag::ExternalParentDeform )
        {
            ReadIndex( &m_kStream, uBoneIndexSize, kBone.ExternalParentIndex() );
        }

        if( uFlag & ( uint16_t )EBoneFlag::IK )
        {
            auto& kIkBone = kBone.IkBone();
            ReadIndex( &m_kStream, uBoneIndexSize, kIkBone.TargetIndex() );
            ReadStream( &m_kStream, kIkBone.LoopCount() );
            ReadStream( &m_kStream, kIkBone.LimitRadian() );

            int32_t nLinkCount = 0;
            ReadStream( &m_kStream, nLinkCount );
            kIkBone.LinkCount() = nLinkCount;

            auto& kIkLinks = kIkBone.IkLinks();
            kIkLinks.resize( nLinkCount );
            for( auto& kIkLink : kIkLinks )
            {
                ReadIndex( &m_kStream, uBoneIndexSize, kIkLink.BoneIndex() );
                ReadStream( &m_kStream, kIkLink.Limit() );
                if( kIkLink.Limit() )
                {
                    ReadStream( &m_kStream, kIkLink.MinAngle() );
                    ReadStream( &m_kStream, kIkLink.MaxAngle() );
                }
            }
        }
    }
    return PMX_SUCCESS;
}

PmxResult CPmxStream::ReadMorph()
{
    ReadStream( &m_kStream, m_nMorphCount );

    m_kMorphs.resize( m_nMorphCount );
    const uint8_t& uEncoding           = m_kGlobalSettings[ EGlobalSetting::TextEncoding       ];
    const uint8_t& uMorphIndexSize     = m_kGlobalSettings[ EGlobalSetting::MorphIndexSize     ];
    const uint8_t& uVertexIndexSize    = m_kGlobalSettings[ EGlobalSetting::VertexIndexSize    ];
    const uint8_t& uBoneIndexSize      = m_kGlobalSettings[ EGlobalSetting::BoneIndexSize      ];
    const uint8_t& uMaterialIndexSize  = m_kGlobalSettings[ EGlobalSetting::MaterialIndexSize  ];
    const uint8_t& uRigidBodyIndexSize = m_kGlobalSettings[ EGlobalSetting::RigidBodyIndexSize ];
    for( auto& kMorph : m_kMorphs )
    {
        PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, kMorph.LocalName()  ) );
        PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, kMorph.GlobalName() ) );

        ReadStream( &m_kStream, kMorph.MorphPanel() );
        ReadStream( &m_kStream, kMorph.MorphType()     );
        ReadStream( &m_kStream, kMorph.OffsetCount()   );

        auto& kMorphOffsets = kMorph.MorphOffsets();
        kMorphOffsets.resize( kMorph.OffsetCount() );
        for( auto& kOffset : kMorphOffsets )
        {
            switch( kMorph.MorphType() )
            {
                case EMorphType::Group:
                {
                    kOffset = std::make_unique< CPmxGroupOffsetData >();
                    kOffset->Read( &m_kStream, uMorphIndexSize );
                    break;
                }
                case EMorphType::Vertex:
                {
                    kOffset = std::make_unique< CPmxVertexOffsetData >();
                    kOffset->Read( &m_kStream, uVertexIndexSize );
                    break;
                }
                case EMorphType::Bone:
                {
                    kOffset = std::make_unique< CPmxBoneOffsetData >();
                    kOffset->Read( &m_kStream, uBoneIndexSize );
                    break;
                }
                case EMorphType::Uv:
                case EMorphType::UvExt1:
                case EMorphType::UvExt2:
                case EMorphType::UvExt3:
                case EMorphType::UvExt4:
                {
                    kOffset = std::make_unique< CPmxUvOffsetData >();
                    kOffset->Read( &m_kStream, uVertexIndexSize );
                    break;
                }
                case EMorphType::Material:
                {
                    kOffset = std::make_unique< CPmxMaterialOffsetData >();;
                    kOffset->Read( &m_kStream, uMaterialIndexSize );
                    break;
                }
                case EMorphType::Flip:
                {
                    kOffset = std::make_unique< CPmxFlipOffsetData >();
                    kOffset->Read( &m_kStream, uMorphIndexSize );
                    break;
                }
                case EMorphType::Impulse:
                {
                    kOffset = std::make_unique< CPmxImpulseOffsetData >();
                    kOffset->Read( &m_kStream, uRigidBodyIndexSize );
                    break;
                }
                default:
                    return PMX_ERROR;
            }
        }
    }
    return PMX_SUCCESS;
}

PmxResult CPmxStream::ReadFrame()
{
    ReadStream( &m_kStream, m_nFrameCount );

    m_kFrames.resize( m_nFrameCount );
    const uint8_t& uEncoding       = m_kGlobalSettings[ EGlobalSetting::TextEncoding   ];
    const uint8_t& uMorphIndexSize = m_kGlobalSettings[ EGlobalSetting::MorphIndexSize ];
    const uint8_t& uBoneIndexSize  = m_kGlobalSettings[ EGlobalSetting::BoneIndexSize  ];
    for( auto& kFrame : m_kFrames )
    {
        PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, kFrame.LocalName()  ) );
        PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, kFrame.GlobalName() ) );

        ReadStream( &m_kStream, kFrame.IsSpecialFrame() );
        ReadStream( &m_kStream, kFrame.FrameCount()     );

        auto& kFrameData = kFrame.FrameData();
        kFrameData.resize( kFrame.FrameCount() );
        for( auto& kData : kFrameData )
        {
            ReadStream( &m_kStream, kData.FrameType() );
            switch( kData.FrameType() )
            {
                case EFrameType::Bone:  ReadIndex( &m_kStream, uBoneIndexSize,  kData.FrameIndex() ); break;
                case EFrameType::Morph: ReadIndex( &m_kStream, uMorphIndexSize, kData.FrameIndex() ); break;
                default: return PMX_ERROR;
            }
        }
    }
    return PMX_SUCCESS;
}

PmxResult CPmxStream::ReadRigidBody()
{
    ReadStream( &m_kStream, m_nRigidBodyCount );

    m_kRigidBodys.resize( m_nRigidBodyCount );
    const uint8_t& uEncoding      = m_kGlobalSettings[ EGlobalSetting::TextEncoding  ];
    const uint8_t& uBoneIndexSize = m_kGlobalSettings[ EGlobalSetting::BoneIndexSize ];
    for( auto& kRigidBody : m_kRigidBodys )
    {
        PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, kRigidBody.LocalName()  ) );
        PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, kRigidBody.GlobalName() ) );

        ReadIndex( &m_kStream, uBoneIndexSize, kRigidBody.TargetBoneIndex() );

        ReadStream( &m_kStream, kRigidBody.GroupId()          );
        ReadStream( &m_kStream, kRigidBody.NonCollisionMask() );
        ReadStream( &m_kStream, kRigidBody.ShapeType()        );
        ReadStream( &m_kStream, kRigidBody.ShapeSize()        );
        ReadStream( &m_kStream, kRigidBody.ShapePosition()    );
        ReadStream( &m_kStream, kRigidBody.ShapeRotation()    );
        ReadStream( &m_kStream, kRigidBody.Mass()             );
        ReadStream( &m_kStream, kRigidBody.MoveAttenuation()  );
        ReadStream( &m_kStream, kRigidBody.RotateDamping()    );
        ReadStream( &m_kStream, kRigidBody.Repulsion()        );
        ReadStream( &m_kStream, kRigidBody.Friction()         );
        ReadStream( &m_kStream, kRigidBody.PhysicsMode()      );
    }
    return PMX_SUCCESS;
}

PmxResult CPmxStream::ReadJoint()
{
    ReadStream( &m_kStream, m_nJointCount );

    m_kJoints.resize( m_nJointCount );
    const uint8_t& uEncoding = m_kGlobalSettings[ EGlobalSetting::TextEncoding ];
    const uint8_t& uRigidBodyIndexSize = m_kGlobalSettings[ EGlobalSetting::RigidBodyIndexSize ];
    for( auto& kJoint : m_kJoints )
    {
        PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, kJoint.LocalName()  ) );
        PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, kJoint.GlobalName() ) );

        ReadStream( &m_kStream, kJoint.JointType() );

        ReadIndex( &m_kStream, uRigidBodyIndexSize, kJoint.RigidBodyIndexA() );
        ReadIndex( &m_kStream, uRigidBodyIndexSize, kJoint.RigidBodyIndexB() );

        ReadStream( &m_kStream, kJoint.Position()       );
        ReadStream( &m_kStream, kJoint.Rotation()       );
        ReadStream( &m_kStream, kJoint.MinPosition()    );
        ReadStream( &m_kStream, kJoint.MaxPosition()    );
        ReadStream( &m_kStream, kJoint.MinRotation()    );
        ReadStream( &m_kStream, kJoint.MaxRotation()    );
        ReadStream( &m_kStream, kJoint.SpringPosition() );
        ReadStream( &m_kStream, kJoint.SpringRotation() );
    }
    return PMX_SUCCESS;
}

PmxResult CPmxStream::ReadSoftBody()
{
    if( !FloatEqual( m_fVersion, 2.1f ) )
    {
        return PMX_SAFE;
    }

    ReadStream( &m_kStream, m_nSoftBodyCount );

    m_kSoftBodys.resize( m_nSoftBodyCount );
    const uint8_t& uEncoding           = m_kGlobalSettings[ EGlobalSetting::TextEncoding       ];
    const uint8_t& uMaterialIndexSize  = m_kGlobalSettings[ EGlobalSetting::MaterialIndexSize  ];
    const uint8_t& uRigidBodyIndexSize = m_kGlobalSettings[ EGlobalSetting::RigidBodyIndexSize ];
    const uint8_t& uVertexIndexSize    = m_kGlobalSettings[ EGlobalSetting::VertexIndexSize    ];

    for( auto& kSoftBody : m_kSoftBodys )
    {
        PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, kSoftBody.LocalName()  ) );
        PmxFailReturnAssert( ReadString( &m_kStream, uEncoding, kSoftBody.GlobalName() ) );

        ReadStream( &m_kStream, kSoftBody.ShapeType() );

        ReadIndex( &m_kStream, uMaterialIndexSize, kSoftBody.MaterialIndex() );

        ReadStream( &m_kStream, kSoftBody.GroupId()           );
        ReadStream( &m_kStream, kSoftBody.NonCollisionMask()  );
        ReadStream( &m_kStream, kSoftBody.Flags()             );
        ReadStream( &m_kStream, kSoftBody.BLinkDistance()     );
        ReadStream( &m_kStream, kSoftBody.ClusterCount()      );
        ReadStream( &m_kStream, kSoftBody.Mass()              );
        ReadStream( &m_kStream, kSoftBody.CollisionMargin()   );
        ReadStream( &m_kStream, kSoftBody.AerodynamicsModel() );
        ReadStream( &m_kStream, kSoftBody.SoftConfig()        );
        ReadStream( &m_kStream, kSoftBody.ClusterConfig()     );
        ReadStream( &m_kStream, kSoftBody.InterationConfig()  );
        ReadStream( &m_kStream, kSoftBody.MaterialConfig()    );

        ReadStream( &m_kStream, kSoftBody.AnchorRigidBodyCount() );
        auto& kAnchorRigidyBodys = kSoftBody.AnchorRigidBodys();
        kAnchorRigidyBodys.resize( kSoftBody.AnchorRigidBodyCount() );
        for( auto& kAnchorRigidBody : kAnchorRigidyBodys )
        {
            ReadIndex( &m_kStream, uRigidBodyIndexSize, kAnchorRigidBody.RigidBodyIndex() );
            ReadIndex( &m_kStream, uVertexIndexSize,    kAnchorRigidBody.VertexIndex()    );
            ReadStream( &m_kStream, kAnchorRigidBody.IsNear() );
        }

        ReadStream( &m_kStream, kSoftBody.VertexPinCount() );
        auto& kVertexPins = kSoftBody.VertexPins();
        kVertexPins.resize( kSoftBody.VertexPinCount() );
        for( auto& nVertexPin : kVertexPins )
        {
            ReadIndex( &m_kStream, uVertexIndexSize, nVertexPin );
        }
    }
    return PMX_SUCCESS;
}
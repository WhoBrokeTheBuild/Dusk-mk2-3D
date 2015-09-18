#ifndef DUSK_MESH_H
#define DUSK_MESH_H

#include <Tracking/ITrackedObject.h>
#include <Graphics/Graphics.h>
#include <Graphics/Material.h>
#include <Math/Math.h>
#include <Collections/ArrayList.h>

using Dusk::Collections::ArrayList;
using namespace Dusk::Math;

namespace Dusk
{

namespace Graphics
{

class Mesh :
	public Tracking::ITrackedObject
{
public:

    static const GLAttribute ATTR_VERTEX;
    static const GLAttribute ATTR_NORMAL;
    static const GLAttribute ATTR_TEX_COORD;

    inline Mesh( void ) :
        m_Name(),
        m_VertexBuffer(0),
        m_NormalBuffer(0),
        m_TexCoordBuffer(0),
        m_VertexArray(0)
    { }

    virtual inline string GetClassName( void ) const { return "Mesh"; }

    bool Init( const string& name, const GLPrimitiveType& primitiveType, 
			   const ArrayList<vec3>& vertexes, 
			   const ArrayList<vec3>& normals = ArrayList<vec3>(),
		       const ArrayList<vec2>& texCoords = ArrayList<vec2>() );

    bool Init( const string& name, const GLPrimitiveType& primitiveType, 
			   const unsigned int& vertexCount, const vec3* pVertexes, 
		       const vec3* pNormals = nullptr, const vec2* pTexCoords = nullptr );

    bool Init( const string& name, const GLPrimitiveType& primitiveType, 
		       const unsigned int& vertexCount, const float* pVertexes, 
		       const float* pNormals = nullptr, const float* pTexCoords = nullptr );

    virtual inline ~Mesh( void ) { Term(); }

    void Render( void );

    bool HasMaterial( void ) const { return mp_Material; }
    Material* GetMaterial( void ) { return mp_Material; }
    void SetMaterial( Material* pMaterial ) { mp_Material = pMaterial; }

private:

    Mesh( const Mesh& rhs );
    void operator=( const Mesh& rhs );

    void Term( void );

    string          m_Name;

    unsigned int    m_VertexCount;

    GLPrimitiveType m_PrimitiveType;

    GLBuffer        m_VertexBuffer,
                    m_NormalBuffer,
                    m_TexCoordBuffer;

    GLVertexArray   m_VertexArray;

    Material*       mp_Material;

}; // class Mesh

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_MESH_H

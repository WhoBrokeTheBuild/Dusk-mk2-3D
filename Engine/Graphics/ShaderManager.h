#pragma once

#ifndef DUSK_SHADER_MANAGER_H
#define DUSK_SHADER_MANAGER_H

#include <Scripting/Scripting.h>
#include <Graphics/Graphics.h>
#include <Tracking/ITrackedObject.h>
#include <Collections/ArrayList.h>
#include <Collections/Map.h>
#include <Utility/Types.h>

namespace Dusk
{

namespace Graphics
{

using Collections::ArrayList;
using Collections::Map;

struct ShaderInfo :
	public Tracking::ITrackedObject
{
public:

	ShaderInfo( const GLenum& type, const string& filename ) :
		Type(type),
		Filename(filename)
	{ }

	ShaderInfo( const ShaderInfo& rhs ) :
		Type(rhs.Type),
		Filename(rhs.Filename)
	{ }

	void operator=( const ShaderInfo& rhs )
	{
		Type = rhs.Type;
		Filename = rhs.Filename;
	}

	virtual inline string GetClassName( void ) const { return "Shader Info"; }

	GLenum Type;
	string Filename;

}; // struct ShaderInfo

class ShaderManager :
	public Tracking::ITrackedObject
{
public:

	inline ShaderManager( void ) :
        m_Programs(),
		m_UniformLocations(),
		m_CurrProg()
	{ }

	inline ~ShaderManager( void ) { Term(); }

	virtual inline string GetClassName( void ) const { return "Shader Manager"; }

	bool Init( void );
	void Term( void );

	bool LoadProgram( const string& name, const ArrayList<ShaderInfo>& shaders );
	bool UseProgram( const string& name );

	static void InitScripting( void );
	static int Script_LoadProgram( lua_State* L );

private:

	void PrintShaderLog( const GLShader& shader );
	void PrintProgramLog( const GLProgram& program );

	GLShader LoadShaderFromFile( const string& filename, const GLenum& shaderType );

	Map<string, GLProgram> m_Programs;
	Map<string, Map<string, GLUniformLocation>> m_UniformLocations;

	GLProgram m_CurrProg;
	string m_CurrProgName;

}; // class ShaderManager

} // namespace Graphics

} // namespace Dusk

#endif // DUSK_SHADER_MANAGER_H
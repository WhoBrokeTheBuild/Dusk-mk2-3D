#include "ShaderManager.h"
#include <Logging/LoggingSystem.h>
#include <Scripting/ScriptingSystem.h>
#include <Utility/Benchmark.h>

using namespace Dusk::Logging;
using namespace Dusk::Graphics;
using namespace Dusk::Scripting;

bool ShaderManager::
Init( void )
{
	return true;
}

void ShaderManager::
Term( void )
{
	for (auto it : m_Programs)
	{
		glDeleteProgram(it.second);
	}

	m_Programs.Clear();
	m_UniformLocations.Clear();
}

bool ShaderManager::
LoadProgram( const string& name, const ArrayList<ShaderInfo>& shaders )
{
	DuskBenchStart();

	DuskExtLog("verbose", "Loading Shader Program: %s", name.c_str());

	GLProgram program = glCreateProgram();

	ArrayList<GLShader> shaderIDs;
	for (auto shader : shaders)
	{
		shaderIDs.Add(LoadShaderFromFile(shader.Filename, shader.Type));
	}

	for (auto shaderId : shaderIDs)
	{
		glAttachShader(program, shaderId);
	}

	glLinkProgram(program);

	GLint programLinked = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &programLinked);

	if (programLinked != GL_TRUE)
	{
		DuskExtLog("error", "Failed to link program %d\n", program);
		PrintProgramLog(program);
		glDeleteProgram(program);
		program = 0;
	}

	for (auto shaderId : shaderIDs)
	{
		glDeleteShader(shaderId);
	}

	if (program == 0)
		return false;

	m_Programs.Add(name, program);
	m_UniformLocations.Add(name, Map<string, GLUniformLocation>());

	int uniformCount = -1;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniformCount);

	for (GLuint i = 0; i < (unsigned)uniformCount; ++i)
	{
		int nameLength;
		int num;
		GLenum uniformType = GL_ZERO;
		char uniformName[100];

		glGetActiveUniform(program, i, sizeof(uniformName) - 1, &nameLength, &num, &uniformType, uniformName);

		uniformName[nameLength] = '\0';
		GLuint location = i;
		//GLuint location = glGetUniformLocation(program, uniformName);

		m_UniformLocations[name].Add(uniformName, location);
	}

	DuskBenchEnd("ShaderManager::LoadProgram");
	return true;
}

bool ShaderManager::
UseProgram( const string& name )
{
	if ( ! m_Programs.ContainsKey(name) )
	{
		glUseProgram(0);
		return false;
	}

	if ( m_CurrProg == m_Programs[name] )
		return true;

	glUseProgram(0);
	m_CurrProg = m_Programs[name];
	m_CurrProgName = name;
	glUseProgram(m_CurrProg);

	return true;
}

void ShaderManager::
InitScripting( void )
{
	ScriptingSystem::RegisterFunction("dusk_shader_manager_load_program", &ShaderManager::Script_LoadProgram);
}

int ShaderManager::
Script_LoadProgram( lua_State* L )
{
	ShaderManager* pShaderManager = (ShaderManager*)lua_tointeger(L, 1);
	string name = lua_tostring(L, 2);

	ArrayList<ShaderInfo> shaders;

	if ( lua_istable(L, 3) )
	{
		// TODO: Implement multiple shader loading at once
	}
	else
	{
		shaders.Add(ShaderInfo(GL_FRAGMENT_SHADER, lua_tostring(L, 3)));
		shaders.Add(ShaderInfo(GL_VERTEX_SHADER, lua_tostring(L, 4)));
	}

	pShaderManager->LoadProgram(name, shaders);
	return 0;
}

void ShaderManager::
PrintShaderLog( const GLShader& shader )
{
	if ( glIsShader(shader) )
	{
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

		char* infoLog = new char[maxLength];

		glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
		if ( infoLogLength > 0 )
		{
			DuskExtLog("info", "Log for Shader %d:\n%s", shader, infoLog);
		}

		delete[] infoLog;
	}
	else
	{
		DuskExtLog("error", "Cannot print shader log, %d is not a shader", shader);
	}
}

void ShaderManager::
PrintProgramLog( const GLProgram& program )
{
	if ( glIsProgram(program) )
	{
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

		char* infoLog = new char[maxLength];

		glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
		if ( infoLogLength > 0 )
		{
			DuskExtLog("info", "Log for Program %d:\n%s", program, infoLog);
		}

		delete[] infoLog;
	}
	else
	{
		DuskExtLog("error", "Cannot print program log, %d is not a program", program);
	}
}

GLShader ShaderManager::LoadShaderFromFile(const string& filename, const GLenum& shaderType)
{
	DuskExtLog("verbose", "Load from file \"%s\"", filename.c_str());
	GLuint shader = 0;	string shaderString;
	std::ifstream file(filename);

	if ( file )
	{
		shaderString.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		shader = glCreateShader(shaderType);

		const GLchar* shaderSource = shaderString.c_str();
		glShaderSource(shader, 1, (const GLchar**)&shaderSource, NULL);
		glCompileShader(shader);

		GLint shaderCompiled = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);

		if ( shaderCompiled != GL_TRUE )
		{
			DuskExtLog("error", "Failed to compile shader %d \"%s", shader, filename.c_str());
			PrintShaderLog(shader);
			glDeleteShader(shader);
			shader = 0;
		}
	}
	else
	{
		DuskExtLog("error", "Unable to open file \"%s\"", filename.c_str());
		return 0;
	}

	return shader;
}


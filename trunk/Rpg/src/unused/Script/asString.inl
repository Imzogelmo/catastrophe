// catastrophe rpg engine
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include <fc/string.h>
#include <angelscript.h>

#include "asBindUtil.h"
#include "ScriptEngine.h"


namespace script
{
	// string bounds checking
	void StringOutOfBounds( int index, bool throwException = false )
	{
		if( throwException )
		{
			// Set a script exception
			asIScriptContext *ctx = asGetActiveContext();
			ctx->SetException("string index out of range.");
		}
		else
		{
			Log("Warning: string index (%i) out of range.", index);
		}
	}

	fc::string StringFactory(asUINT length, const char *s)
	{
		return fc::string(s, length);
	}

	fc::string AddIntString(int i, fc::string& str)
	{
		return fc::to_string(i) + str;
	}

	fc::string& AssignIntToString(int i, fc::string& dest)
	{
		dest = fc::to_string(i);
		return dest;
	}

	fc::string& AddAssignIntToString(int i, fc::string& dest)
	{
		dest.insert(0, fc::to_string(i));
		return dest;
	}

	fc::string AddStringInt(fc::string& str, int i)
	{
		return fc::string(str).append(fc::to_string(i));
	}

	fc::string& AssignFloatToString(float f, fc::string& dest)
	{
		dest = fc::to_string(f);
		return dest;
	}

	fc::string& AddAssignFloatToString(float f, fc::string& dest)
	{
		dest += fc::to_string(f);
		return dest;
	}

	fc::string AddStringFloat(fc::string& str, float f)
	{
		return str + fc::to_string(f);
	}

	fc::string AddFloatString(float f, fc::string& str)
	{
		return fc::to_string(f) + str;
	}

	char* StringCharAt(int i, fc::string& str)
	{
		if( size_t(i) >= str.size() )
		{
			StringOutOfBounds(i);
			return 0;
		}

		return &str[i];
	}

	//int StringCmp(const fc::string& a, const fc::string& b)
	//{
	//	return a.compare(b);
	//}

	bool StringEquals( fc::string* self, const fc::string& str )
	{
		return *self == str;
	}

	fc::string StringAddString( fc::string* self, const fc::string& str )
	{
		return *self + str;
	}

	//void StringResize( fc::string* self, int size )
	//{
	//	return self->resize(size_t(size));
	//}

	void StringPopBack( fc::string* self )
	{
		if( !self->empty() )
			self->pop_back();
	}

	fc::string& StringInsert1( fc::string* self, int pos, const fc::string& str )
	{
		if( size_t(pos) >= self->size() )
		{
			StringOutOfBounds(pos);
			return *self;
		}

		self->insert( pos, str );
		return *self;
	}

	fc::string& StringInsert2( fc::string* self, int pos, const fc::string& str, int start, int n )
	{
		if( size_t(pos) >= self->size() )
		{
			StringOutOfBounds(pos);
			return *self;
		}

		if( size_t(start + n) >= str.size() )
		{
			StringOutOfBounds(start + n);
			return *self;
		}

		self->insert( pos, str, start, n );
		return *self;
	}

	fc::string& StringErase1( fc::string* self, int pos )
	{
		if( size_t(pos) >= self->size() )
		{
			StringOutOfBounds(pos);
			return *self;
		}

		self->erase( pos, 1 );
		return *self;
	}

	fc::string& StringErase2( fc::string* self, int pos, int amount )
	{
		if( size_t(pos + amount) >= self->size() )
		{
			StringOutOfBounds(pos + amount);
			return *self;
		}

		self->erase( pos, amount );
		return *self;
	}

	fc::string& StringReplace1( fc::string* self, int pos, int n, const fc::string& str )
	{
		if( size_t(pos + n) >= self->size() )
		{
			StringOutOfBounds(pos + n);
			return *self;
		}

		self->replace( pos, n, str );
		return *self;
	}

	fc::string& StringReplace2( fc::string* self, int pos, int n, const fc::string& str, int str_pos, int str_size )
	{
		if( size_t(pos + n) >= self->size() )
		{
			StringOutOfBounds(pos + n);
			return *self;
		}

		if( size_t(str_pos + str_size) >= str.size() )
		{
			StringOutOfBounds(str_pos + str_size);
			return *self;
		}

		self->replace( pos, n, str, str_pos, str_size );
		return *self;
	}

	int StringFind1( const fc::string* self, const fc::string& str )
	{
		return (int)self->find( str );
	}

	int StringFind2( const fc::string* self, const fc::string& str, int pos, int amount )
	{
		if( size_t(pos + amount) >= str.size() )
		{
			StringOutOfBounds(pos + amount);
			return -1;
		}

		return (int)self->find( str.c_str(), pos, amount );
	}

	int StringReverseFind1( const fc::string* self, const fc::string& str )
	{
		return (int)self->rfind( str );
	}

	int StringReverseFind2( const fc::string* self, const fc::string& str, int pos, int amount )
	{
		if( size_t(pos + amount) >= str.size() )
		{
			StringOutOfBounds(pos + amount);
			return -1;
		}

		return (int)self->rfind( str.c_str(), pos, amount );
	}

	int StringFindFirstOf1( const fc::string* self, const fc::string& str )
	{
		return (int)self->find_first_of( str );
	}

	int StringFindFirstOf2( const fc::string* self, const fc::string& str, int pos, int amount )
	{
		if( size_t(pos + amount) >= str.size() )
		{
			StringOutOfBounds(pos + amount);
			return -1;
		}

		return (int)self->find_first_of( str.c_str(), pos, amount );
	}

	int StringFindLastOf1( const fc::string* self, const fc::string& str )
	{
		return (int)self->find_last_of( str );
	}

	int StringFindLastOf2( const fc::string* self, const fc::string& str, int pos, int amount )
	{
		if( size_t(pos + amount) >= str.size() )
		{
			StringOutOfBounds(pos + amount);
			return -1;
		}

		return (int)self->find_last_of( str.c_str(), pos, amount );
	}

	int StringFindFirstNotOf1( const fc::string* self, const fc::string& str )
	{
		return (int)self->find_first_not_of( str );
	}

	int StringFindFirstNotOf2( const fc::string* self, const fc::string& str, int pos, int amount )
	{
		if( size_t(pos + amount) >= str.size() )
		{
			StringOutOfBounds(pos + amount);
			return -1;
		}

		return (int)self->find_first_not_of( str.c_str(), pos, amount );
	}

	int StringFindLastNotOf1( const fc::string* self, const fc::string& str )
	{
		return (int)self->find_last_not_of( str );
	}

	int StringFindLastNotOf2( const fc::string* self, const fc::string& str, int pos, int amount )
	{
		if( size_t(pos + amount) >= str.size() )
		{
			StringOutOfBounds(pos + amount);
			return -1;
		}

		return (int)self->find_last_not_of( str.c_str(), pos, amount );
	}

	fc::string Substring( const fc::string* self, int pos, int amount )
	{
		if( size_t(pos + amount) >= self->size() )
		{
			StringOutOfBounds(pos + amount);
			return fc::string();
		}

		return self->substr( pos, amount );
	}

	int StringToInt( const fc::string* self )
	{
		return self->to_int();
	}

	float StringToFloat( const fc::string* self )
	{
		return self->to_float();
	}

	fc::string& StringToUpper1( fc::string* self )
	{
		self->make_upper();
		return *self;
	}

	fc::string& StringToUpper2( fc::string* self, int loc, int amount )
	{
		if( size_t(loc + amount) >= self->size() )
		{
			StringOutOfBounds(loc + amount);
			return *self;
		}

		self->make_upper( size_t(loc), size_t(amount) );
		return *self;
	}

	fc::string& StringToLower1( fc::string* self )
	{
		self->make_lower();
		return *self;
	}

	fc::string& StringToLower2( fc::string* self, int loc, int amount )
	{
		if( size_t(loc + amount) >= self->size() )
		{
			StringOutOfBounds(loc + amount);
			return *self;
		}

		self->make_lower( size_t(loc), size_t(amount) );
		return *self;
	}

} //namespace script



void ScriptEngine::RegisterString()
{
	int r;
	using namespace script;
	r = engine->RegisterObjectType("string", sizeof(fc::string), asOBJ_VALUE | asOBJ_APP_CLASS_CDA); assert( r >= 0 );

	// Register the string factory
	r = engine->RegisterStringFactory("string", asFUNCTION(StringFactory), asCALL_CDECL); assert( r >= 0 );

	// Register the object operator overloads
	r = engine->RegisterObjectBehaviour("string", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ValueConstruct<fc::string>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("string", asBEHAVE_CONSTRUCT, "void f(const string& in)", asFUNCTION(ValueCopyConstruct<fc::string>), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectBehaviour("string", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(ValueDestruct<fc::string>),  asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod("string", "bool opEquals(const string& in) const", asFUNCTION(StringEquals), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	//r = engine->RegisterObjectMethod("string", "int opCmp(const string& in) const", asFUNCTION(StringCmp), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

	r = engine->RegisterObjectMethod("string", "bool empty() const", asMETHOD(fc::string, empty), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "int size() const", asMETHOD(fc::string, size), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "int length() const", asMETHOD(fc::string, size), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod("string", "void resize(int)", asFUNCTION(StringResize), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "void resize(int)", asMETHOD(fc::string, resize), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "void clear()", asMETHOD(fc::string, clear), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "void swap(string& out)", asMETHOD(fc::string, swap), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "void push_back(int8)", asMETHOD(fc::string, push_back), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "void pop_back()", asFUNCTION(StringPopBack), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

	//r = engine->RegisterObjectMethod("string", "string& append(const string& in)", asMETHODPR(fc::string, append, (const fc::string&), fc::string&), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod("string", "string& append(const string& in, int, int)", asMETHODPR(fc::string, append, (const fc::string&, size_t, size_t), fc::string&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string& append(int, int8)", asMETHODPR(fc::string, append, (size_t, char), fc::string&), asCALL_THISCALL); assert( r >= 0 );

	//r = engine->RegisterObjectMethod("string", "string& assign(const string& in)", asMETHODPR(fc::string, assign, (const fc::string&), fc::string&), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod("string", "string& assign(const string& in, int, int)", asMETHODPR(fc::string, assign, (const fc::string&, size_t, size_t), fc::string&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string& assign(int, int8)", asMETHODPR(fc::string, assign, (size_t, char), fc::string&), asCALL_THISCALL); assert( r >= 0 );

	r = engine->RegisterObjectMethod("string", "string& insert(int, const string& in)", asFUNCTION(StringInsert1), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string& insert(int, const string& in, int, int)", asFUNCTION(StringInsert2), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string& erase(int)", asFUNCTION(StringErase1), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string& erase(int, int)", asFUNCTION(StringErase2), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string& replace(int, int, const string& in)", asFUNCTION(StringReplace1), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string& replace(int, int, const string& in, int, int)", asFUNCTION(StringReplace2), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

	r = engine->RegisterObjectMethod("string", "int find(const string& in) const", asFUNCTION(StringFind1), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "int find(const string& in, int, int) const", asFUNCTION(StringFind2), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "int reverse_find(const string& in) const", asFUNCTION(StringReverseFind1), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "int reverse_find(const string& in, int, int) const", asFUNCTION(StringReverseFind2), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "int find_first_of(const string& in) const", asFUNCTION(StringFindFirstOf1), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "int find_first_of(const string& in, int, int) const", asFUNCTION(StringFindFirstOf2), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "int find_last_of(const string& in) const", asFUNCTION(StringFindLastOf1), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "int find_last_of(const string& in, int, int) const", asFUNCTION(StringFindLastOf2), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "int find_first_not_of(const string& in) const", asFUNCTION(StringFindFirstNotOf1), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "int find_first_not_of(const string& in, int, int) const", asFUNCTION(StringFindFirstNotOf2), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "int find_last_not_of(const string& in) const", asFUNCTION(StringFindLastNotOf1), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "int find_last_not_of(const string& in, int, int) const", asFUNCTION(StringFindLastNotOf2), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

	r = engine->RegisterObjectMethod("string", "string substring(int, int) const", asFUNCTION(Substring), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

	r = engine->RegisterObjectMethod("string", "string& to_upper()", asFUNCTION(StringToUpper1), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string& to_upper(int, int)", asFUNCTION(StringToUpper2), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string& to_lower()", asFUNCTION(StringToLower1), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string& to_lower(int, int)", asFUNCTION(StringToLower2), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "int to_int() const", asFUNCTION(StringToInt), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "float to_float() const", asFUNCTION(StringToFloat), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

	// string operators
	r = engine->RegisterObjectMethod("string", "int8 &opIndex(int)", asFUNCTION(StringCharAt), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "const int8 &opIndex(int) const", asFUNCTION(StringCharAt), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string& opAssign(const string& in)", asMETHODPR(fc::string, operator =, (const fc::string&), fc::string&), asCALL_THISCALL); assert( r >= 0 );
	//r = engine->RegisterObjectMethod("string", "string& opAddAssign(const string& in)", asMETHODPR(fc::string, operator+=, (const fc::string&), fc::string&), asCALL_THISCALL); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string opAdd(const string& in) const", asFUNCTION(StringAddString), asCALL_CDECL_OBJFIRST); assert( r >= 0 );

	r = engine->RegisterObjectMethod("string", "string& opAssign(float)", asFUNCTION(AssignFloatToString), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string& opAddAssign(float)", asFUNCTION(AddAssignFloatToString), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string opAdd(float) const", asFUNCTION(AddStringFloat), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string opAdd_r(float) const", asFUNCTION(AddFloatString), asCALL_CDECL_OBJLAST); assert( r >= 0 );

	r = engine->RegisterObjectMethod("string", "string& opAssign(int)", asFUNCTION(AssignIntToString), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string& opAddAssign(int)", asFUNCTION(AddAssignIntToString), asCALL_CDECL_OBJLAST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string opAdd(int) const", asFUNCTION(AddStringInt), asCALL_CDECL_OBJFIRST); assert( r >= 0 );
	r = engine->RegisterObjectMethod("string", "string opAdd_r(int) const", asFUNCTION(AddIntString), asCALL_CDECL_OBJLAST); assert( r >= 0 );

}






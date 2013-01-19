
#pragma once

#include <fc/vector.h>


class GarbageCollector
{
private:
	class __gcAny
	{
	private:
		class __gcBase
		{
		public:
			virtual ~__gcBase() {}
		};

		template<class T>
		class __gcType : public __gcBase
		{
		public:
			__gcType( const T& type, bool a = false ) : p(type), is_array(a) {}
			~__gcType()
			{
				if(p)
				{
					if( is_array )
						delete [] p;
					else
						delete p;
					p = 0;
				}
			}

		private:
			T p;
			bool is_array;
		};

	public:
		template<class T>
		__gcAny( const T& ptr, bool is_array = false ) : p( new __gcType<T>(ptr, is_array) ) {}
		__gcAny( const __gcAny& a ) : p( a.p ) {}
		~__gcAny()
		{
			if(p) 
				delete p, p = 0;
		}

	private:
		__gcAny &operator = ( const __gcAny& a );
		__gcBase* p;
	};

	fc::vector<__gcAny*> m_garbage_bin;

public:
	GarbageCollector() {}
	~GarbageCollector()
	{
		destroy_garbage();
	}

	void destroy_garbage()
	{
		// lifo deletion
		for( fc::vector<__gcAny*>::iterator it = m_garbage_bin.end(); it != m_garbage_bin.begin(); )
			delete (*--it);
	}

	template<class T>
	T operator () ( const T& mem )
	{
		return collect( mem, false );
	}

	template<class T>
	T operator [] ( const T& mem )
	{
		return collect( mem, true );
	}

	template<class T>
	T collect( const T& mem, bool isArray )
	{
		T ptr = mem;
		m_garbage_bin.push_back( new __gcAny(mem, isArray) );
		return ptr;
	}

};




#ifndef persist_h
#define persist_h
#include <istream>
#include <ostream>
#include <typeinfo>
#include <vector>
namespace vcell_persist {
	/**
	* traits base class. Indicates derived class T implements
	* void persist(std::ostream &s, const T &) const
	* T(std::istream &)
	*/
	struct Persistent{};

	class Registrar {
		static void registerTypeToken(const char *token,const std::type_info &);
		static void registerTypeToken(const char *token, const std::type_info & primaryType, int dim); 
		static void registerTypeToken(const char *token, const std::type_info & primaryType, const std::type_info &templateParameter, int dim); 
		static void registerTypeToken(const char *token, const std::type_info & primaryType, const std::type_info &templateParameterA, const std::type_info &templateParameterB, int dim); 
	public:
		template <class T>
		static void reg(const char *token) {
			registerTypeToken(token,typeid(T));
		}
		template <class P, typename T, int N>
		static void reg(const char *token) {
			registerTypeToken(token,typeid(P),typeid(T),N);
		}

		template <class P, int N>
		static void reg(const char *token) {
			registerTypeToken(token,typeid(P),N);
		}

		template <class P, typename A, typename B, int N>
		static void reg(const char *token) {
			registerTypeToken(token,typeid(P),typeid(A),typeid(B),N);
		}
	};

	/**
	* writes validation to stream. Optionally compacts token keys. 
	* sets stream to throw exceptions on ios errors
	* Object should exist during streaming and be destroyed afterwards
	*/
	struct WriteFormatter {
		WriteFormatter(std::ostream &is,unsigned short version, bool dictionary = false);
		~WriteFormatter( );
	};
	/**
	* does some basic validation.
	* sets stream to throw exceptions on ios errors
	* Object should exist during streaming and be destroyed afterwards
	*/
	struct ReadFormatter {
		ReadFormatter(std::istream &os, unsigned short version);
		~ReadFormatter( );
	};

	const std::string & getTypeToken(const std::type_info &); 
	//const std::string typeNameFor(const char *classname, const std::type_info &templateParameter, int dim); 

	template <typename E> struct TokenT;

	/**
	* typedef to control token usage; tokens used if and only if parameter type is "bool"
	*/
	typedef TokenT<bool> Token;		//tokens on
	//typedef TokenT<int> Token;			//tokens off

	/**
	* insert/read check tokens into persistence streams
	* @tparam E conditionally include / exclude checks
	*/
	template <typename E>
	struct TokenT {
		template<typename C>
		static void insert(std::ostream &os) { }
		template<typename C>
		static void check(std::istream &is) { }
		static void insert(std::ostream &os,const std::type_info &) {}
		static void check(std::istream &os, const std::type_info &) {}
	};

	template <>
	struct TokenT<bool> {
		template<typename C>
		static void insert(std::ostream &os) {
			insert(os,typeid(C));
		}
		template<typename C>
		static void check(std::istream &is) {
			check(is,typeid(C));
		}
		static void insert(std::ostream &os,const std::type_info &);
		static void check(std::istream &os, const std::type_info &);
		
	};

	/**
	* binary write single value to stream
	* @param os output stream -- must be ios::binary
	*/
	template<typename T>
	inline void binaryWrite(std::ostream &os, const T & t)  {
		std::streamsize s = sizeof(T);
		const char * const location = reinterpret_cast<const char *>(&t);
		os.write(location,s);
	}

	/**
	* binary read single value form stream
	* @param is input stream -- must be ios::binary
	* @param t destination to set 
	*/
	template<typename T>
	inline void binaryRead(std::istream &is, T & t)  {
		std::streamsize s = sizeof(T);
		char * const location = reinterpret_cast<char *>(&t);
		is.read(location,s);
	}
	

	/**
	* functor to write binary data
	*/
	template<typename T>
	struct binaryWriter {
		std::ostream &os;
		/**
		* @param os_ output stream -- must be ios::binary
		*/
		binaryWriter(std::ostream &os_) 
			:os(os_) {}
		void operator( )(const T  &t) {
			binaryWrite(os,t);
		}
	};

	/**
	* functor to read binary data
	*/
	template<typename T>
	struct binaryReader {
		std::istream &is;
		/**
		* @param is_ input stream -- must be ios::binary
		*/
		binaryReader(std::istream &is_) 
			:is(is_) {}
		void operator( )(T &in) {
			binaryRead(is,in);
		}
	};
}	
#endif

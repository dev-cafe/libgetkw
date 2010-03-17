/** \file Keyword.h
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief
 */

#ifndef KEYWORD_H_
#define KEYWORD_H_

#include <string>
#include <vector>
#include <fstream>
//#include <boost/any.hpp>

#include "GetkwError.h"

namespace KeyType {
	enum KeyKinds {
		Unknown = -1,
		Undefined,
		Int,
		Dbl,
		Bool,
		Str,
		IntArray,
		DblArray,
		BoolArray,
		StrArray,
		Data
	};
};


template <class T>
class Keyword {
public:
	Keyword(const std::string _name, const T &_val, bool _isDefd = false):
			name(_name), val(_val), isDefd(_isDefd) {
		if (not setKind(_val)) {
			throw "Invalid key type!";
		}
	}

	virtual ~Keyword() {
	}
//	boost::any any_clone(const boost::any &akey) {
//		if (akey.type() != typeid(T)) {
//			throw "Error! Type mismatch!";
//		}
//		Keyword<T> &key = *boost::any_cast<Keyword<T> *>(akey);
//		return boost::any(new Keyword<T>(key));
//	}

	const T &get() const {
		return val;
	}
	void set(T &t) {
		val = t;
	}

	bool isDefined() const {
		return isDefd;
	}

	const std::string &getName() const {
		return name;
	}

	int getKind() const {
		return kind;
	}
	void setDefined(bool _isDefd) {
		isDefd = _isDefd;
	}

	void setName(const std::string &_name) {
		name = name;
	}


	template <typename X>
	std::ostream &repr(std::ostream &o, X v) const {
		if (kind == KeyType::Str) {
			o << "  " + name << " = " << "\"" << val << "\"";
		} else {
			o << "  " + name << " = " << val;
		}
		return o;
	}
	template <typename X>
			std::ostream &repr(std::ostream &o, const std::vector<X> &v) const {
		o << "  " << name << " = [ ";
		if (kind == KeyType::StrArray) {
			o << std::endl;
			o << "\"" << v[0] << "\"";
		} else {
			o << val[0];
		}

		for (unsigned int i = 1; i < val.size(); i++) {
			if (kind == KeyType::StrArray) {
				o << ", " << std::endl << "\"" << v[i] << "\"";
			} else {
				o << ", " << v[i];
			}
		}
		o << " ]";
		return o;
	}
	friend std::ostream& operator <<(std::ostream& o, const Keyword<T> &key) {
		return key.repr(o, key.get());
	}

	virtual void print() const {
		std::cout << repr(std::cout, val) << std::endl;
	}


	static const string &getNamedKind(int i) {
		static const string INT = "Int";
		static const string DBL = "Dbl";
		static const string BOOL = "Bool";
		static const string STR = "Str";
		static const string INT_ARRAY = "IntArray";
		static const string DBL_ARRAY = "DblArray";
		static const string BOOL_ARRAY = "BoolArray";
		static const string STR_ARRAY = "StrArray";
		static const string UNDEF = "Undefined";
		static const string UNKN = "Unknown";

		switch (i) {
		case (KeyType::Int):
			return INT;
		case (KeyType::Dbl):
			return DBL;
		case (KeyType::Bool):
			return BOOL;
		case (KeyType::Str):
			return STR;
		case (KeyType::IntArray):
			return INT_ARRAY;
		case (KeyType::DblArray):
			return DBL_ARRAY;
		case (KeyType::BoolArray):
			return BOOL_ARRAY;
		case (KeyType::StrArray):
			return STR_ARRAY;
		case (KeyType::Undefined):
			return UNDEF;
		}
		return UNKN;
	}
protected:
	std::string name;
	T val;
	bool isDefd;
	bool isArray;
	int kind;

	bool setKind(int t) {
		isArray = false;
		kind = KeyType::Int;
		return true;
	}
	bool setKind(double t) {
		isArray = false;
		kind = KeyType::Dbl;
		return true;
	}
	bool setKind(bool t) {
		isArray = false;
		kind = KeyType::Bool;
		return true;
	}
	bool setKind(const std::string &t) {
		isArray = false;
		kind = KeyType::Str;
		return true;
	}

	bool setKind(const std::vector<int> &t) {
		isArray = true;
		kind = KeyType::IntArray;
		return true;
	}
	bool setKind(const std::vector<double> &t) {
		isArray = true;
		kind = KeyType::DblArray;
		return true;
	}
	bool setKind(const std::vector<bool> &t) {
		isArray = true;
		kind = KeyType::BoolArray;
		return true;
	}
	bool setKind(const std::vector<std::string> &t) {
		isArray = true;
		kind = KeyType::StrArray;
		return true;
	}
	template<class X> bool setKind(const X &t) {
		std::cout << "Warning! Unknown kind:" << t << std::endl;
		kind = KeyType::Unknown;
		return false;
	}

};

#endif /* KEYWORD_H_ */

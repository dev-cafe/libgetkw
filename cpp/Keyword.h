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

#include "GetkwError.h"

class Keyword {
public:
	Keyword(const std::string name, bool isDefd = false);
	virtual ~Keyword();

	virtual Keyword *clone() const {
		return 0;
	}

	int getInt() const;
	double getDbl() const;
	bool getBool() const;
	std::string getStr() const;

	std::vector<int> getIntVec() const;
	std::vector<double> getDblVec() const;
	std::vector<bool> getBoolVec() const;
	std::vector<std::string> getStrVec() const;
	std::vector<std::string> getData() const {
		return getStrVec();
	}

	virtual bool get(const int &t) const {
		throwErrorWrongKind(t);
		return false;
	}

	virtual bool get(const double &t) const {
		throwErrorWrongKind(t);
		return false;
	}

	virtual bool get(const bool &t) const {
		throwErrorWrongKind(t);
		return false;
	}

	virtual bool get(const std::string &t) const {
		throwErrorWrongKind(t);
		return false;
	}

	virtual bool get(const std::vector<int> &t) const {
		throwErrorWrongKind(t);
		return false;
	}

	virtual bool get(const std::vector<double> &t) const {
		throwErrorWrongKind(t);
		return false;
	}

	virtual bool get(const std::vector<bool> &t) const {
		throwErrorWrongKind(t);
		return false;
	}

	virtual bool get(const std::vector<std::string> &t) const {
		throwErrorWrongKind(t);
		return false;
	}

	virtual void set(int &t) {
	}

	virtual void set(double &t) {
	}

	virtual void set(bool &t) {
	}

	virtual void set(std::string &t) {
	}

	virtual void set(std::vector<int> &t) {
	}

	virtual void set(std::vector<double> &t) {
	}

	virtual void set(std::vector<bool> &t) {
	}

	virtual void set(std::vector<std::string> &t) {
	}

	bool isDefined() const {
		return isDefd;
	}

	std::string getName() const {
		return name;
	}

	int getKind() const {
		return kind;
	}
	void setDefined(bool isDefd) {
		this->isDefd = isDefd;
	}

	void setName(std::string name) {
		this->name = name;
	}

	friend std::ostream& operator <<(std::ostream& o, const Keyword &key) {
		return key.repr(o);
	}

	virtual void print() const {
		std::cout << repr(std::cout) << std::endl;
	}

	virtual std::ostream &repr(std::ostream &o) const {
		return o << "Warning! Keyword: Unknown key type.";
	}

	enum KeyType {
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

	const static std::string &getNamedKind(int i);
	template<class T> void throwErrorWrongKind(T &t) const;
protected:
	int isKind(const int &t) const {
		return Int;
	}
	int isKind(const double &t) const {
		return Dbl;
	}
	int isKind(const bool &t) const {
		return Bool;
	}
	int isKind(const std::string &t) const {
		return Str;
	}
	int isKind(const std::vector<int> &t) const {
		return IntArray;
	}
	int isKind(const std::vector<double> &t) const {
		return DblArray;
	}
	int isKind(const std::vector<bool> &) const {
		return BoolArray;
	}
	int isKind(const std::vector<std::string> &t) const {
		return StrArray;
	}
	template<class T> int setKind(T &t) {
		std::cout << "Warning! Unknown kind:" << t << std::endl;
		return Unknown;
	}
	std::string name;
	bool isDefd;
	int kind;
};

#endif /* KEYWORD_H_ */

/** \file Getkw.h
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief
 */

#ifndef GETKW_H_
#define GETKW_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

#include "Section.h"
#include "Keyword.h"
#include "Keyval.h"
#include "Keyvec.h"
#include "GetkwError.h"

class Getkw {
public:
	Getkw(std::string file, bool _verbose = false, bool _strict = false);
	virtual ~Getkw();
	void setStrict(bool flag);
	void setVerbose(bool flag);
	void pushSection(const std::string &path);
	void popSection();
	const Section &getSect(const std::string &path) const;
	const Keyword &getKey(const std::string &path) const;
	template<class T> void get(const std::string &path, const T &val) const;

	int getInt(const std::string &path) const {
		return getKey(path).getInt();
	}
	double getDbl(const std::string &path) {
		return getKey(path).getDbl();
	}
	bool getBool(const std::string &path) {
		return getKey(path).getBool();
	}
	std::string getStr(const std::string &path) {
		return getKey(path).getStr();
	}
	std::vector<int> getIntVec(const std::string &path) {
		return getKey(path).getIntVec();
	}
	std::vector<double> getDblVec(const std::string &path) {
		return getKey(path).getDblVec();
	}
	std::vector<bool> getBoolVec(const std::string &path) {
		return getKey(path).getBoolVec();
	}
	std::vector<std::string> getStrVec(const std::string &path) {
		return getKey(path).getStrVec();
	}
	std::vector<std::string> getData(const std::string &path) {
		return getKey(path).getData();
	}

	void print() const;
	std::ostream &repr(std::ostream &o) const;
	friend std::ostream &operator<<(std::ostream &o, const Getkw &gkw) {
		return gkw.repr(o);
	}
protected:
	static Section *readSect(std::istream &fis);
	static Keyword *readKey(std::istream &fis);
	static void readline(std::istream &fis, std::istringstream &isi);
	static bool convBool(const std::string &val);
	static int convKind(const std::string &typ);
private:
	bool verbose;
	bool strict;
	std::string file;
	Section *toplevel;
	const Section *cur;
	std::stack<const Section *> sstack;
};

#endif /* GETKW_H_ */

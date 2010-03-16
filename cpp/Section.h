/** \file Section.h
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief Container for Sections and Keywords
 */

#ifndef SECTION_H_
#define SECTION_H_

#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "Keyword.h"
#include "Keyval.h"
#include "Keyvec.h"
#include "GetkwError.h"

class Section {
public:
	Section(const std::string &name, const std::string &tag = "");
	Section(const Section &s);
	Section &operator=(const Section &s);
	virtual ~Section();
	const Section &getSect(const std::string &path) const;
	const Keyword &getKey(const std::string &path) const;
	void addSect(Section &sect);
	void addSect(Section *);
	template <class T> void addKeyword(T &key);
	void addKey(Keyword *key);
	static Section *readSect(ifstream &fis);
	void print() const;
	std::ostream &repr(ostream &o) const;
	friend ostream& operator <<(ostream& o, const Section &s) {
		return s.repr(o);
	}

	const std::string &getTag() const {
		return tag;
	}

	int getNkeys() const {
		return nkeys;
	}

	int getNsect() const {
		return nsect;
	}

	void setTag(const std::string tag) {
		this->tag = tag;
	}

	void setNkeys(int nkeys) {
		this->nkeys = nkeys;
	}

	void setNsect(int nsect) {
		this->nsect = nsect;
	}

	bool isDefined() const {
		return isDefd;
	}

	std::string getName() const {
		return name;
	}

	void setDefined(bool isDefd) {
		this->isDefd = isDefd;
	}

	void setName(std::string name) {
		this->name = name;
	}
protected:
	std::string name;
	std::string tag;
	int nkeys;
	int nsect;
	bool isDefd;
	map<std::string, const Section *> sects;
	map<std::string, const Keyword *> keys;
	map<std::string, const Section *> tags;

	const Section *findSect(const std::string &pathspec) const;
	const Section *traversePath(std::vector<std::string> &path,
						  const std::string &pathspec) const;
	void splitPath(const std::string &pathspec,
				   std::vector<std::string> &path) const;
	int splitTag(const std::string &path, std::string &tag) const;
	bool has_key(const std::string &name) const;
	bool has_sect(const std::string &name) const;
	bool has_tag(const std::string &name) const;
};

#endif /* SECTION_H_ */

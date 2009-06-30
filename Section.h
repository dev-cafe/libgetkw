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

using namespace std;
#include <fstream>
#include <string>
#include <map>
#include <vector>

//#include "Envelope.h"
#include "Keyword.h"

class Section {
public:
	Section(const string &name, const string &tag = "");
	Section(const Section &s);
	Section &operator=(const Section &s);
	virtual ~Section();
	Section &getSect(const string &path);
	Keyword &getKey(const string &path);
	void addSect(Section &sect);
	template <class T> void addKey(T &key);
	static Section *readSect(ifstream &fis);

	string &getTag() {
		return tag;
	}

	int getNkeys() const {
		return nkeys;
	}

	int getNsect() const {
		return nsect;
	}

	void setTag(const string tag) {
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

	string getName() const {
		return name;
	}

	void setDefined(bool isDefd) {
		this->isDefd = isDefd;
	}

	void setName(string name) {
		this->name = name;
	}

protected:
	string name;
	string tag;
	int nkeys;
	int nsect;
	bool isDefd;
	map<string, Section *> sects;
	map<string, Keyword *> keys;
	map<string, Section *> tags;

	Section *findSect(const string &pathspec);
	Section *traversePath(vector<string> &path, const string &pathspec);
	void splitPath(const string &pathspec, vector<string> &path);
	int splitTag(const string &path, string &tag);
	bool has_key(const string &name);
	bool has_sect(const string &name);
	bool has_tag(const string &name);
	void print_sects();
	void print_keys();
	void print_tags();
};

#endif /* SECTION_H_ */

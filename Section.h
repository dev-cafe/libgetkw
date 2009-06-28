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

#include "Envelope.h"
#include "Keyword.h"

class Section: public Envelope {
public:
	Section(const string name, const string tag = "");
	//Section(const Section &s);
	virtual ~Section();
	Section &getSect(string path);
	Keyword &getKey(string path);
	void add(Section &sect);
	void add(Keyword &key);
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

protected:
	string tag;
	int nkeys;
	int nsect;
	map<string, Section *> tags;
	map<string, Section *> sects;
	map<string, Keyword *> keys;

	Envelope &find(string pathspec);
	Envelope *traversePath(vector<string> path, const string pathspec);
	void splitPath(const string pathspec, vector<string> &path);
	int splitTag(const string path, string &tag);
	bool has_key(const string name);
	bool has_sect(const string name);
	bool has_tag(const string name);
};

#endif /* SECTION_H_ */

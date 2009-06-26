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
	Section(const string name, const string tag="", bool isDefined);
	virtual ~Section();
	Section *getSect(string path);
	Keyword *getKey(string path);
	void add(Section &sect);
	void add(Keyword &key);
	static Section *readSect(ifstream &fis);

    int getNkeys() const
    {
        return nkeys;
    }

    int getNsect() const
    {
        return nsect;
    }

    void setNkeys(int nkeys)
    {
        this->nkeys = nkeys;
    }

    void setNsect(int nsect)
    {
        this->nsect = nsect;
    }

protected:
	string tag;
	int nkeys;
	int nsect;
//	map<string, Section> sects;
//	map<string, Keyword> keys;

	struct Bin {
		enum KwType {Key, Sect, TagSect};
		int type;
		Keyword *key;
		Section *sect;
		map<string,Section *> tsect;
	};
	map<string, Envelope> bin;
	Section *findsect(string path);
	Keyword *findkw(string path);
	static vector<string> *splitPath(const string path);
	static string *getTag(const string path);
};


#endif /* SECTION_H_ */

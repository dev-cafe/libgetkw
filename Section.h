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

#include "Keyword.h"

class Section {
public:
	Section(const string name, int nkeys, int nsect);
	virtual ~Section();
	static Section *readSection(ifstream &fis);
protected:
	string name;
	int isset;
	int nkeys;
	int nsect;
	Section *sect;
	Keyword *kw;
};

#endif /* SECTION_H_ */

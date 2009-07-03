/** \file Section.cpp
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief  Container for Sections and Keywords
 */

using namespace std;
#include <iostream>

#include "Section.h"
#include "GetkwError.h"

#define PRINT_FUNC_NAME cout << "@ Section::" << __func__ << endl;

Section::Section(const string &name, const string &tag) :
	name(name) {
	isDefd = false;
	nsect = 0;
	nkeys = 0;
	if (tag.empty()) {
		this->tag = name;
	} else {
		this->tag = tag;
	}
}

Section::Section(const Section &s) {
	tag = s.tag;
	nkeys = s.nkeys;
	nsect = s.nsect;

	map<string, Section *>::const_iterator sit;
	map<string, Keyword *>::const_iterator kit;
	for (sit = s.sects.begin(); sit != s.sects.end(); ++sit) {
		sects[sit->first] = new Section(*sit->second);
		tags[(*sit->second).tag] = sects[sit->first];
	}
	for (kit = s.keys.begin(); kit != s.keys.end(); ++kit) {
		keys[kit->first] = kit->second->clone();
	}

}

Section &Section::operator=(const Section &s) {
	name = s.name;
	tag = s.tag;
	nkeys = s.nkeys;
	nsect = s.nsect;

	map<string, Section *>::const_iterator sit;
	map<string, Keyword *>::const_iterator kit;
	for (sit = s.sects.begin(); sit != s.sects.end(); ++sit) {
		sects[sit->first] = new Section(*sit->second);
		tags[(*sit->second).tag] = sects[sit->first];
	}
	for (kit = s.keys.begin(); kit != s.keys.end(); ++kit) {
		keys[kit->first] = new Keyword(*kit->second);
	}

	return *this;
}

Section::~Section() {
	map<string, Section *>::iterator sit;
	map<string, Keyword *>::iterator kit;
	for (sit = sects.begin(); sit != sects.end(); ++sit) {
		delete sects[sit->first];
	}
	for (kit = keys.begin(); kit != keys.end(); ++kit) {
		delete keys[kit->first];
	}
}

Section &Section::getSect(const string &pathspec) {
	vector<string> path;
	splitPath(pathspec, path);

	Section *sect = traversePath(path, pathspec);
	return *sect;
}

Keyword &Section::getKey(const string &pathspec) {
	vector<string> path;
	splitPath(pathspec, path);

	string name = path.back();
	Section *sect = traversePath(path, pathspec);
	if (!sect->has_key(name)) {
		string err = "Invalid keyword, " + pathspec;
		throw GetkwError(err);
	}
	return *sect->keys[name];
}

Section *Section::readSect(ifstream &fis) {
	return 0;
}

/* Sections can be multiply defined, provided they have different tags.
 * The first section section is added to the box, as well as to the tags
 * map if applicable. The following sections with the same name are added
 * to the tags map.
 */
void Section::addSect(Section *sect) {
	string name = sect->name + "<" + sect->tag + ">";
	if (has_key(name)) {
		string err = "Error! Section::add: Section already defined, " + name;
		throw GetkwError(err);
	}

	sects[name] = sect;
	tags[sect->tag] = sects[name];
	nsect++;
}

void Section::addSect(Section &sect) {
	string name = sect.name + "<" + sect.tag + ">";
	if (has_key(name)) {
		string err = "Error! Section::add: Section already defined, " + name;
		throw GetkwError(err);
	}

	sects[name] = new Section(sect);
	tags[sect.tag] = sects[name];
	nsect++;
}
//! Add an allocated key to a section
void Section::addKey(Keyword *key) {
	string name = key->getName();

	if (has_key(name)) {
		string err = "Error Section::add: Key already defined, " + name;
		throw GetkwError(err);
	}

	keys[name] = key;
	nkeys++;
}

//! Copy and and add a keyword to a section
template<class T> void Section::addKeyword(T &key) {
	string name = key.getName();

	if (has_key(name)) {
		string err = "Error Section::add: Key already defined, " + name;
		throw GetkwError(err);
	}

	keys[name] = new T(key);
	nkeys++;
}

template void Section::addKeyword(Keyval<int> &);
template void Section::addKeyword(Keyval<double> &);
template void Section::addKeyword(Keyval<bool> &);
template void Section::addKeyword(Keyval<string> &);

Section *Section::traversePath(vector<string> &path, const string &pathspec) {
	string cur = path[0];

	if (path.size() == 1) {
		if (has_key(cur))
			return this;
		if (!has_sect(cur)) {
			cur = cur + "<" + cur + ">";
		}
		if (has_sect(cur))
			return sects[cur];
		string err = "Error! traversePath: Invalid path, " + pathspec;
		throw GetkwError(err);
	}

	if (!has_sect(cur))
		cur = cur + "<" + cur + ">";
	if (!has_sect(cur)) {
		string err = "Error! traversePath: Invalid path, " + pathspec;
		throw GetkwError(err);
	}

	path.erase(path.begin());
	Section *sect = sects[cur]->traversePath(path, pathspec);
	return sect;
}

void Section::splitPath(const string &pathspec, vector<string> &path) {
	string str = pathspec;
	string::size_type m = 0;
	while (true) {
		m = str.find('.', m);
		if (m == string::npos) {
			path.push_back(str);
			break;
		} else {
			path.push_back(str.substr(0, m));
		}
		m++;
		str = str.substr(m);
	}
}

int Section::splitTag(const string &path, string &tag) {
	string::size_type m, n = 0;
	m = path.find('<');
	if (m == string::npos)
		return 0;
	n = path.find('>');
	if (n == string::npos or n - m - 1 < 1)
		return 0;
	tag.clear();
	tag.append(path.substr(m + 1, n - m - 1));
	return m;
}

void Section::print_sects() {
	map<string, Section *>::const_iterator it;
	for (it = sects.begin(); it != sects.end(); ++it) {
		cout << " * " << it->first << endl;
	}
}

void Section::print_keys() {
	map<string, Keyword *>::const_iterator it;
	for (it = keys.begin(); it != keys.end(); ++it) {
		cout << " * " << it->first << endl;
	}
}

void Section::print_tags() {
	map<string, Section *>::const_iterator it;
	for (it = tags.begin(); it != tags.end(); ++it) {
		cout << " * " << it->first << endl;
	}
}

bool Section::has_key(const string &b) {
	if (keys.find(b) == keys.end())
		return false;
	return true;

}

bool Section::has_sect(const string &b) {
	if (sects.find(b) == sects.end())
		return false;
	return true;

}

bool Section::has_tag(const string &b) {
	if (tags.find(b) == tags.end())
		return false;
	return true;

}

void Section::print()
{
	cout << repr(cout) << endl;
}

ostream &Section::repr(ostream &o)
{
	o << name;
	if (name.compare(tag) != 0) {
		o << "<" + tag + ">";
	}
	o << " {" << endl;

	map<string, Keyword *>::const_iterator kit;
	for (kit = keys.begin(); kit != keys.end(); ++kit) {
		o << *kit->second << endl;
	}

	map<string, Section *>::const_iterator sit;
	for (sit = sects.begin(); sit != sects.end(); ++sit) {
		o << *sit->second << endl;
	}

	return o << "}";
}

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

#define IF_ANY_KEYTYPE_IS(A, T) \
if (A.type() == typeid(const Keyword< T > *))

#define ANY_TO_CONST_KEY_PTR(A, T) \
boost::any_cast<const Keyword< T > *>(A)

#define PRINT_FUNC_NAME cout << "@ Section::" << __func__ << endl;

Section::Section(const string &_name, const string &_tag) :
	name(_name) {
	isDefd = false;
	nsect = 0;
	nkeys = 0;
	if (tag.empty()) {
		this->tag = _name;
	} else {
		this->tag = _tag;
	}
}

Section::Section(const Section &s) {
	tag = s.tag;
	nkeys = s.nkeys;
	nsect = s.nsect;

	map<string, Section *>::const_iterator sit;
	map<string, boost::any>::const_iterator kit;
	for (sit = s.sects.begin(); sit != s.sects.end(); ++sit) {
		sects[sit->first] = new Section(*sit->second);
		tags[(*sit->second).tag] = sects[sit->first];
	}
	for (kit = s.keys.begin(); kit != s.keys.end(); ++kit) {
		keys[kit->first] = kit->second;
	}

}

Section &Section::operator=(const Section &s) {
	name = s.name;
	tag = s.tag;
	nkeys = s.nkeys;
	nsect = s.nsect;

	map<string, Section *>::const_iterator sit;
	map<string, boost::any>::const_iterator kit;
	for (sit = s.sects.begin(); sit != s.sects.end(); ++sit) {
		sects[sit->first] = new Section(*sit->second);
		tags[(*sit->second).tag] = sects[sit->first];
	}
	for (kit = s.keys.begin(); kit != s.keys.end(); ++kit) {
		keys[kit->first] = kit->second;
	}

	return *this;
}

Section::~Section() {
	map<string, Section *>::iterator sit;
	map<string, boost::any>::iterator kit;
	for (sit = sects.begin(); sit != sects.end(); ++sit) {
		delete sects[sit->first];
	}
	for (kit = keys.begin(); kit != keys.end(); ++kit) {

		IF_ANY_KEYTYPE_IS(kit->second, int) {
			const Keyword<int> *key = ANY_TO_CONST_KEY_PTR(kit->second, int);
			delete key;
			continue;
		}
		IF_ANY_KEYTYPE_IS(kit->second, bool) {
			const Keyword<bool> *key = ANY_TO_CONST_KEY_PTR(kit->second, bool);
			delete key;
			continue;
		}
		IF_ANY_KEYTYPE_IS(kit->second, double) {
			const Keyword<double> *key = ANY_TO_CONST_KEY_PTR(kit->second, double);
			delete key;
			continue;
		}
		IF_ANY_KEYTYPE_IS(kit->second, string) {
			const Keyword<string> *key = ANY_TO_CONST_KEY_PTR(kit->second, string);
			delete key;
			continue;
		}
		IF_ANY_KEYTYPE_IS(kit->second, vector<int>) {
			const Keyword<vector<int> > *key = ANY_TO_CONST_KEY_PTR(kit->second, vector<int>);
			delete key;
			continue;
		}
		IF_ANY_KEYTYPE_IS(kit->second, vector<bool>) {
			const Keyword<vector<bool> > *key = ANY_TO_CONST_KEY_PTR(kit->second, vector<bool>);
			delete key;
			continue;
		}
		IF_ANY_KEYTYPE_IS(kit->second, vector<double>) {
			const Keyword<vector<double> > *key = ANY_TO_CONST_KEY_PTR(kit->second, vector<double>);
			delete key;
			continue;
		}
		IF_ANY_KEYTYPE_IS(kit->second, vector<string>) {
			const Keyword<vector<string> > *key = ANY_TO_CONST_KEY_PTR(kit->second, vector<string>);
			delete key;
			continue;
		}
		THROW_GETKW("Error! Unknown key type!");
	}
}

const Section &Section::getSect(const string &pathspec) const {
	vector<string> path;
	splitPath(pathspec, path);

	const Section *sect = traversePath(path, pathspec);
	return *sect;
}

template<typename T>
const Keyword<T> &Section::getKey(const string &pathspec) const {
	vector<string> path;
	splitPath(pathspec, path);

	string name = path.back();
	const Section *sect = traversePath(path, pathspec);
	if (!sect->has_key(name)) {
		THROW_GETKW("Invalid keyword, " + pathspec);
	}
	map<string, boost::any>::const_iterator iter = sect->keys.find(name);
	return *ANY_TO_CONST_KEY_PTR(iter->second, T);
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
		THROW_GETKW("Section::add: Section already defined, " + name);
	}

	sects[name] = sect;
	tags[sect->tag] = sects[name];
	nsect++;
}

void Section::addSect(Section &sect) {
	string name = sect.name + "<" + sect.tag + ">";
	if (has_key(name)) {
		THROW_GETKW("Section::add: Section already defined, " + name);
	}

	sects[name] = new Section(sect);
	tags[sect.tag] = sects[name];
	nsect++;
}
//! Add an allocated key to a section
template<class T>
void Section::addKey(const Keyword<T> *key) {
	const string &name = key->getName();

	if (has_key(name)) {
		THROW_GETKW("Section::add: Key already defined, " + name);
	}

	keys[name] = boost::any(key);
	nkeys++;
}

//! Copy and and add a keyword to a section
template<class T> void Section::addKey(const Keyword<T> &key) {
	string name = key.getName();

	if (has_key(name)) {
		THROW_GETKW("Section::add: Key already defined, " + name);
	}

	keys[name] = boost::any(new Keyword<T>(key));
	nkeys++;
}

const Section *Section::traversePath(vector<string> &path,
									 const string &pathspec) const {
	string cur = path[0];

	if (path.size() == 1) {
		if (has_key(cur))
			return this;
		if (!has_sect(cur)) {
			cur = cur + "<" + cur + ">";
		}
		if (has_sect(cur)) {
			map<string, Section *>::const_iterator iter = sects.find(name);
			return iter->second;
		}
		THROW_GETKW("traversePath: Invalid path, " + pathspec);
	}

	if (!has_sect(cur))
		cur = cur + "<" + cur + ">";
	if (!has_sect(cur)) {
		THROW_GETKW("traversePath: Invalid path, " + pathspec);
	}

	path.erase(path.begin());
	map<string, Section *>::const_iterator iter = sects.find(cur);
	return iter->second->traversePath(path, pathspec);
}

void Section::splitPath(const string &pathspec, vector<string> &path) const {
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

int Section::splitTag(const string &path, string &tag) const {
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

bool Section::has_key(const string &b) const {
	if (keys.find(b) == keys.end())
		return false;
	return true;

}

bool Section::has_sect(const string &b) const {
	if (sects.find(b) == sects.end())
		return false;
	return true;

}

bool Section::has_tag(const string &b) const {
	if (tags.find(b) == tags.end())
		return false;
	return true;

}

void Section::print() const
{
	cout << repr(cout) << endl;
}

ostream &Section::repr(ostream &o) const
{
	o << endl << name;
	if (name.compare(tag) != 0) {
		o << "<" + tag + ">";
	}
	o << " {" << endl;

	map<string, boost::any>::const_iterator kit;
	for (kit = keys.begin(); kit != keys.end(); ++kit) {
		IF_ANY_KEYTYPE_IS(kit->second,int) {
			o << *ANY_TO_CONST_KEY_PTR(kit->second, int) << endl;
			continue;
		}
		IF_ANY_KEYTYPE_IS(kit->second,bool) {
			o << *ANY_TO_CONST_KEY_PTR(kit->second, bool) << endl;
			continue;
		}
		IF_ANY_KEYTYPE_IS(kit->second,double) {
			o << *ANY_TO_CONST_KEY_PTR(kit->second, double) << endl;
			continue;
		}
		IF_ANY_KEYTYPE_IS(kit->second, string) {
			o << *ANY_TO_CONST_KEY_PTR(kit->second, string) << endl;
			continue;
		}
		IF_ANY_KEYTYPE_IS(kit->second, vector<int>) {
			o << *ANY_TO_CONST_KEY_PTR(kit->second, vector<int>) << endl;
			continue;
		}
		IF_ANY_KEYTYPE_IS(kit->second, vector<bool>) {
			o << *ANY_TO_CONST_KEY_PTR(kit->second, vector<bool>) << endl;
			continue;
		}
		IF_ANY_KEYTYPE_IS(kit->second, vector<double>) {
			o << *ANY_TO_CONST_KEY_PTR(kit->second, vector<double>) << endl;
			continue;
		}
		IF_ANY_KEYTYPE_IS(kit->second, vector<string>) {
			o << *ANY_TO_CONST_KEY_PTR(kit->second, vector<string>) << endl;
			continue;
		}
		THROW_GETKW("Unknown key type!");
	}

	map<string, Section *>::const_iterator sit;
	for (sit = sects.begin(); sit != sects.end(); ++sit) {
		o << *sit->second << endl;
	}

	o << "}";
	return o;
}

template void Section::addKey(const Keyword<int> *);
template void Section::addKey(const Keyword<double> *);
template void Section::addKey(const Keyword<bool> *);
template void Section::addKey(const Keyword<string> *);
template void Section::addKey(const Keyword<vector<int> > *);
template void Section::addKey(const Keyword<vector<double> > *);
template void Section::addKey(const Keyword<vector<bool> > *);
template void Section::addKey(const Keyword<vector<string> > *);

template void Section::addKey(const Keyword<int> &);
template void Section::addKey(const Keyword<double> &);
template void Section::addKey(const Keyword<bool> &);
template void Section::addKey(const Keyword<string> &);
template void Section::addKey(const Keyword<vector<int> > &);
template void Section::addKey(const Keyword<vector<double> > &);
template void Section::addKey(const Keyword<vector<bool> > &);
template void Section::addKey(const Keyword<vector<string> > &);

template const Keyword<int> &Section::getKey(const string &) const;
template const Keyword<double> &Section::getKey(const string &) const;
template const Keyword<bool> &Section::getKey(const string &) const;
template const Keyword<string> &Section::getKey(const string &) const;
template const Keyword<vector<int> > &Section::getKey(const string &) const;
template const Keyword<vector<double> > &Section::getKey(const string &) const;
template const Keyword<vector<bool> > &Section::getKey(const string &) const;
template const Keyword<vector<string> > &Section::getKey(const string &) const;


/** \file Section.cpp
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Troms√∏
 *
 * \brief  Container for Sections and Keywords
 */

using namespace std;
#include <iostream>

#include "Section.h"
#include "Keyval.h"
#include "Keyvec.h"

#define PRINT_FUNC_NAME cout << "@ Section::" << __func__ << endl;

Section::Section(const string &name, const string &tag) :
	Envelope(name, false) {
	type = Sect;
	nsect = 0;
	nkeys = 0;
	if (tag.empty()) {
		this->tag = name;
	} else {
		this->tag = tag;
	}
}

Section::Section(const Section &s) :
	Envelope(s) {
	tag = s.tag;
	nkeys = s.nkeys;
	nsect = s.nsect;
	sects = s.sects;
	keys = s.keys;
	tags = s.tags;
}

Section &Section::operator=(const Section &s) {
	type = s.type;
	name = s.name;
	tag = s.tag;
	nkeys = s.nkeys;
	nsect = s.nsect;
	sects = s.sects;
	keys = s.keys;
	tags = s.tags;
	return *this;
}

Section::~Section() {
}

Keyword &Section::getKey(const string &path) {
	Keyword *key = findKey(path);
//	if (key->getType() != Key) {
//		string err = "Error! Section::getKey(): Not a keyword, " + path;
//		throw err;
//	}
//	Keyword *kw;
//	Keyval<int> *ikw = static_cast<Keyval<int> *> (key);
//	cout << "apa"  << *ikw << endl;
//
//	cout << ".......kusss "  << endl;
//	switch (123123) {
//	case Keyword::Int:
//		cout << "int .......kusss" << endl;
//		kw = static_cast<Keyval<int> *> (key);
//		break;
//	case Keyword::Dbl:
//		kw = static_cast<Keyval<double> *> (key);
//		break;
//	case Keyword::Bool:
//		kw = static_cast<Keyval<bool> *> (key);
//		break;
//	case Keyword::Str:
//		cout << "int .......kusss" << endl;
//		kw = static_cast<Keyval<string> *> (key);
//		break;
//	default:
//		cout << "default .......kusss" << endl;
//		break;
//	}

	//	Keyword &kw = dynamic_cast<Keyword &> (*key);
	return *key;
}

Section *Section::readSect(ifstream &fis) {
	return 0;
}

Section &Section::getSect(const string &path) {
	Envelope *key = find(path);
	if (key->getType() != Sect) {
		string err = "Error! Section::getSect(): Not a section, " + path;
		throw err;
	}
	Section &sect = static_cast<Section &> (*key);
	return sect;

}

/* Sections can be multiply defined, provided they have different tags.
 * The first section section is added to the box, as well as to the tags
 * map if applicable. The following sections with the same name are added
 * to the tags map.
 */
void Section::addSect(Section &sect) {
	string name = sect.name + "<" + sect.tag + ">";
	if (has_key(name)) {
		string err = "Error! Section::add: Section already defined, " + name;
		throw err;
	}

	sects[name] = sect;
	tags[sect.tag] = &sects[name];
	nsect++;
}

template <class T> void Section::addKey(T &key) {
	string name = key.getName();

	if (has_key(name)) {
		string err = "Error Section::add: Key already defined, " + name;
		throw err;
	}
//	cout << "adding " << key;

	map<string, Keyword *> kuk;
	T *apa = new T(key);
	cout << "adding " << *apa;
	keys[name] = key;
	kuk[name] = apa;
	nkeys++;
//	cout << " -> " << keys[name] <<endl;
	cout << " -> " << *kuk[name] <<endl;
	delete apa;
}

template void Section::addKey(Keyval<int> &);
template void Section::addKey(Keyval<double> &);
template void Section::addKey(Keyval<bool> &);
template void Section::addKey(Keyval<string> &);

Envelope *Section::find(const string &pathspec) {
	vector<string> path;
	splitPath(pathspec, path);

	Envelope *key = traversePath(path, pathspec);
	return key;
}


Keyword *Section::findKey(const string &pathspec) {
	vector<string> path;
	splitPath(pathspec, path);

	Keyword *key = traversePathKey(path, pathspec);
	return key;
}

Keyword *Section::traversePathKey(vector<string> &path, const string &pathspec) {
	string cur = path[0];

	if (path.size() == 1) {
		if (has_key(cur)) {
			cout << "found " << cur << " = " << keys[cur] << endl;
			return &keys[cur];
		}
		string err = "Error! traversePathKey: Invalid path, " + pathspec;
		throw err;
	}

	if (!has_sect(cur))
		cur = cur + "<" + cur + ">";
	if (!has_sect(cur)) {
		string err = "Error! traversePath: Invalid path, " + pathspec;
		throw err;
	}

	path.erase(path.begin());
	Keyword *key = sects[cur].traversePathKey(path, pathspec);
	return key;
}

Envelope *Section::traversePath(vector<string> &path, const string &pathspec) {
	string cur = path[0];

	if (path.size() == 1) {
		if (has_key(cur))
			return &keys[cur];
		if (!has_sect(cur)) {
			cur = cur + "<" + cur + ">";
		}
		if (has_sect(cur))
			return &sects[cur];
		string err = "Error! traversePath: Invalid path, " + pathspec;
		throw err;
	}

	if (!has_sect(cur))
		cur = cur + "<" + cur + ">";
	if (!has_sect(cur)) {
		string err = "Error! traversePath: Invalid path, " + pathspec;
		throw err;
	}

	path.erase(path.begin());
	Envelope *key = sects[cur].traversePath(path, pathspec);
	return key;
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
	map<string, Section>::const_iterator it;
	for (it = sects.begin(); it != sects.end(); ++it) {
		cout << " * " << it->first << endl;
	}
}

void Section::print_keys() {
	map<string, Keyword>::const_iterator it;
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

//
//static Section_t *read_sect(FILE *fd)
//{
//	Section_t *sect;
//	char name[MAX_KEYLEN];
//	char tagname[2*MAX_KEYLEN+2];
//	char tag[MAX_KEYLEN];
//	int nsect, nkeys, i;
//	char set[6];
//
//	i=fscanf(fd, "%*s %s %d %s\n", name, &nsect, set);
//	i=fscanf(fd, "%*s %1c %*s %d\n", tag, &nkeys);
///*    printf("SECT: %s %c %d %d %c \n", name, tag[0], nsect, nkeys, set[0]);*/
//	if (tag[0] == 'T') {
//		i=fscanf(fd, "%s\n", tag);
//		sprintf(tagname, "%s(%s)", name, tag);
///*        printf("TAG: %s -> %s\n", tag, tagname);*/
//		sect=new_section(tagname, nkeys, nsect);
//	} else {
//		sect=new_section(name, nkeys, nsect);
//	}
//
//	sect->set=conv_bool(set[0]);
//
//	for (i=0; i < nkeys; i++) {
//		sect->kw[i]=read_key(fd);
//	}
//	for (i=0; i < nsect; i++) {
//		sect->sect[i]=read_sect(fd);
//	}
//
//	return sect;
//}
//

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

#define PRINT_FUNC_NAME cout << "@ Section::" << __func__ << endl;

Section::Section(const string &name, const string &tag) :
	Envelope(name, false) {
	PRINT_FUNC_NAME;
	type = Sect;
	if (tag.empty()) {
		this->tag = name;
	} else {
		this->tag = tag;
	}
}
//
//Section::Section(const Section &s): Envelope(s) {
//	tag = s.tag;
//	nkeys = s.nkeys;
//	nsect = s.nsect;
//	map<string, Section *>::iterator siter;
//	map<string, Keyword *>::iterator siter;
//	for (siter = s.sects.begin(); siter != s.sects.end(); ++siter) {
//		sects[siter->first]= new Section(*siter->second);
//	}
//	for (iter = s.tags.begin(); iter != s.box.end(); ++iter) {
//		tags[iter->first]= new Section(*iter->second);
//	}
//}

//Section::~Section() {
//	map<string, Section *>::iterator sit;
//	map<string, Keyword *>::iterator kit;
//	for (sit = sects.begin(); sit != sects.end(); ++sit) {
//		delete sects[sit->first];
//	}
//	for (kit = keys.begin(); kit != keys.end(); ++kit) {
//		delete keys[kit->first];
//	}
//}

Keyword &Section::getKey(const string &path) {
	PRINT_FUNC_NAME;
	Envelope &key = find(path);
	if (key.getType() != Key) {
		string err = "Error! Section::getKey(): Not a keyword, " + path;
		throw err;
	}
	Keyword &kw = static_cast<Keyword &> (key);
	return kw;
}

Section *Section::readSect(ifstream &fis) {
	return 0;
}

Section &Section::getSect(const string &path) {
	PRINT_FUNC_NAME;
	Envelope &key = find(path);
	cout << "ok? " << endl;
	if (key.getType() != Sect) {
		string err = "Error! Section::getSect(): Not a section, " + path;
		throw err;
	}
	cout << "ok!";
	Section &sect = static_cast<Section &> (key);
	return sect;

}

/* Sections can be multiply defined, provided they have different tags.
 * The first section section is added to the box, as well as to the tags
 * map if applicable. The following sections with the same name are added
 * to the tags map.
 */
void Section::add(Section &sect) {
	PRINT_FUNC_NAME;

	string name = sect.name + "<" + sect.tag + ">";
	if (has_sect(name)) {
		string err = "Error! Section::add: Section already defined, " + name;
		throw err;
	}
	sects[name] = Section(sect);
	tags[sect.tag] = &sects[name];
}

void Section::add(Keyword &key) {
	PRINT_FUNC_NAME;
	string name = key.getName();

	if (has_key(name)) {
		string err = "Error Section::add: Key already defined, " + name;
		throw err;
	}

	keys[name] = Keyword(key);
}

Envelope &Section::find(const string &pathspec) {
	PRINT_FUNC_NAME;
	vector<string> path;
	splitPath(pathspec, path);

	Envelope &key = traversePath(path, pathspec);
	return key;
}

Envelope &Section::traversePath(vector<string> &path, const string &pathspec) {
	PRINT_FUNC_NAME;
	string cur = string(path[0]);

	if (path.size() == 1) {
		if (has_key(cur))
			return keys[cur];
		if (has_sect(cur))
			return sects[cur];
		cur = cur + "<" + cur + ">";
		if (has_sect(cur))
			return sects[cur];
		string err = "Error! traversePath: Invalid path, " + pathspec;
		throw err;
	}

	path.erase(path.begin());
	Envelope &key = sects[cur].traversePath(path, pathspec);
	return key;

}

void Section::splitPath(const string &pathspec, vector<string> &path) {
	PRINT_FUNC_NAME;
	string str = pathspec;
	unsigned int m = 0;
	while (true) {
		m = str.find('.');
		if (m == string::npos) {
			path.push_back(str);
			break;
		} else {
			path.push_back(str.substr(0, m));
		}
		str = str.substr(m + 1);
	}
}

int Section::splitTag(const string &path, string &tag) {
	PRINT_FUNC_NAME;
	unsigned int m, n = 0;
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
/* recursively delete current section and all its subsections */
//static void del_section(Section_t *self)
//{
//	int i;
//
//	for (i=0; i < self->nkeys; i++) {
//		del_keyword(self->kw[i]);
//	}
//	for (i=0; i < self->nsect; i++) {
//		del_section(self->sect[i]);
//	}
//	free(self->name);
//	free(self->kw);
//	free(self->sect);
//	free(self);
//}
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
//static Section_t *getsect(Section_t *self, const char *name)
//{
//	int i, len;
//
//	for (i=0; i < self->nsect; i++) {
///*        printf("kuk %d %p %s\n", i, self->sect[i], self->sect[i]->name);*/
///*        printf("name=%s\n", name);*/
//		len=strlen(self->sect[i]->name);
//		if (strncmp(self->sect[i]->name, name, len) == 0 ) {
///*            printf("foundit!\n");*/
//			return self->sect[i];
//		}
//	}
//	return NULL;
//}
//
//static Section_t *findsect(Section_t *self, const char *path)
//{
//	const char *name;
//	char tmp[MAX_PATH];
//	Section_t *sect;
//	int len, i;
//
//	name=index(path, '.');
//	if (name == NULL) {
//		if (strcmp(path, self->name) == 0) {
//			return self;
//		}
//		for (i=0; i < self->nsect; i++) {
//			if (strcmp(path, self->sect[i]->name) == 0) {
//				return self->sect[i];
//			}
//		}
//		return self;
//	}
//
//	len=(name-path)/sizeof(char);
//	if (len > MAX_PATH-1) {
//		MSG_ERROR("Too long path name");
//		return NULL;
//	}
//	strncpy(tmp, path, len);
//	tmp[len]='\0';
//
//	sect=getsect(self, tmp);
//	if (sect == NULL) {
//		MSG_ERROR("Invalid section");
//		return NULL;
//	}
//
//	return findsect(sect, name+1);
//}

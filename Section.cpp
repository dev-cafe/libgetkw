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

Section::Section(const string name, const string tag) {
	this->name = name;
	this->tag = tag;
	vector<string> *apa;
	apa = splitPath("jonas.heter.jag");
	for (unsigned int i = 0; i < apa->size(); i++) {
		cout << apa->at(i) << " ";
	}
	cout << endl;
	delete apa;
	cout << "raboof" << endl;
}

Section::~Section() {
	// TODO Auto-generated destructor stub
}

Keyword *Section::getKey(string path) {
	return 0;
}

Section *Section::readSect(ifstream & fis) {
	return 0;
}

Section *Section::getSect(string path) {


	if (bin.find(path) == bin.end()) {
		cout << "Error -> getSect(): no souch section: " << path << endl;
		return 0;
	}
	switch (bin[path].type) {
	case (Bin::Sect):
		return bin[path].sect;
	case (Bin::TagSect):
		string *tag=getTag(path);
		Section *s=bin[path].tsect[*tag];
		delete tag;
		return s;
	default:
		cout << "Error -> getSect(): not a section: " << path << endl;
		return 0;
	}

}

void Section::add(Section &sect) {
	bool hasSect = bin.find(sect.name) != bin.end();

	if (hasSect) {
		if (sect.tag.empty() == true) {
			string err = "Error Section::add: Section already defined ";
			err.append(sect.name);
			throw err;
		}
		bool hasTag = bin[sect.name].tsect.find(sect.tag)
				!= bin[sect.name].tsect.end();
		if (hasTag) {
			string err = "Error Section::add: Section already defined ";
			err.append(sect.name).append(sect.tag);
			throw err;
		}
		bin[sect.name].tsect[sect.tag] = &sect;
		bin[sect.name].type = Bin::TagSect;
	} else {
		bin[sect.name].sect = &sect;
		bin[sect.name].type = Bin::Sect;
	}

}

void Section::add(Keyword &key) {
	string name = key.getName();
	bool hasKey = bin.find(name) != bin.end();

	if (hasKey) {
		string err = "Error Section::add: Key already defined ";
		err.append(name);
		throw err;
	} else {
		bin[name].key = &key;
		bin[name].type = Bin::Key;
	}
}

Section *Section::findsect(string path) {
	return 0;
}

Keyword *Section::findkw(string path) {
	return 0;
}

vector<string> *Section::splitPath(const string path) {
	vector<string> *elem = new vector<string> ();
	string str = path;
	unsigned int m = 0;
	while (true) {
		m = str.find('.');
		if (m == string::npos) {
			elem->push_back(str);
			break;
		} else {
			elem->push_back(str.substr(0, m));
		}
		str = str.substr(m + 1);
	}

	return elem;
}

// check for ()
string *Section::getTag(const string path) {
	string *tag = new string();
	unsigned int m, n = 0;
	m = path.find('(');
	if (m == string::npos) {
		return 0;
	} else {
		n = path.find(')');
	}
	tag->append(path.substr(m+1,n-m-1));

	return tag;
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

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
#include <string>

#include "Section.h"

Section::Section(const string name, int nkeys, int nsect) {

	this->name=name;

	if (nkeys > 0) {
		this.nkeys=nkeys;
	}
	if (nsect > 0) {
		self->sect=(Section_t **) calloc(nsect,sizeof(Section_t *));
		ASSERT_MEM(self->sect);
		self->nsect=nsect;
	}
	return self;

}

Section::~Section() {
	// TODO Auto-generated destructor stub
}



/* recursively delete current section and all its subsections */
static void del_section(Section_t *self)
{
	int i;

	for (i=0; i < self->nkeys; i++) {
		del_keyword(self->kw[i]);
	}
	for (i=0; i < self->nsect; i++) {
		del_section(self->sect[i]);
	}
	free(self->name);
	free(self->kw);
	free(self->sect);
	free(self);
}

static Section_t *read_sect(FILE *fd)
{
	Section_t *sect;
	char name[MAX_KEYLEN];
	char tagname[2*MAX_KEYLEN+2];
	char tag[MAX_KEYLEN];
	int nsect, nkeys, i;
	char set[6];

	i=fscanf(fd, "%*s %s %d %s\n", name, &nsect, set);
	i=fscanf(fd, "%*s %1c %*s %d\n", tag, &nkeys);
/*    printf("SECT: %s %c %d %d %c \n", name, tag[0], nsect, nkeys, set[0]);*/
	if (tag[0] == 'T') {
		i=fscanf(fd, "%s\n", tag);
		sprintf(tagname, "%s(%s)", name, tag);
/*        printf("TAG: %s -> %s\n", tag, tagname);*/
		sect=new_section(tagname, nkeys, nsect);
	} else {
		sect=new_section(name, nkeys, nsect);
	}

	sect->set=conv_bool(set[0]);

	for (i=0; i < nkeys; i++) {
		sect->kw[i]=read_key(fd);
	}
	for (i=0; i < nsect; i++) {
		sect->sect[i]=read_sect(fd);
	}

	return sect;
}

static Section_t *getsect(Section_t *self, const char *name)
{
	int i, len;

	for (i=0; i < self->nsect; i++) {
/*        printf("kuk %d %p %s\n", i, self->sect[i], self->sect[i]->name);*/
/*        printf("name=%s\n", name);*/
		len=strlen(self->sect[i]->name);
		if (strncmp(self->sect[i]->name, name, len) == 0 ) {
/*            printf("foundit!\n");*/
			return self->sect[i];
		}
	}
	return NULL;
}

static Section_t *findsect(Section_t *self, const char *path)
{
	const char *name;
	char tmp[MAX_PATH];
	Section_t *sect;
	int len, i;

	name=index(path, '.');
	if (name == NULL) {
		if (strcmp(path, self->name) == 0) {
			return self;
		}
		for (i=0; i < self->nsect; i++) {
			if (strcmp(path, self->sect[i]->name) == 0) {
				return self->sect[i];
			}
		}
		return self;
	}

	len=(name-path)/sizeof(char);
	if (len > MAX_PATH-1) {
		MSG_ERROR("Too long path name");
		return NULL;
	}
	strncpy(tmp, path, len);
	tmp[len]='\0';

	sect=getsect(self, tmp);
	if (sect == NULL) {
		MSG_ERROR("Invalid section");
		return NULL;
	}

	return findsect(sect, name+1);
}

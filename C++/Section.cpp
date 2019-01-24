/*
 * getkw -- a simple input parser
 * Copyright (C) 2019 Jonas Juselius and contributors.
 *
 * This file is part of getkw.

 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on the complete list of contributors to the
 * getkw library, see: <http://getkw.readthedocs.io/>
 */

/** \file Section.cpp
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief  Container for Sections and Keywords
 */

#include "Section.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "GetkwError.hpp"
#include "Keyword.hpp"

#define IF_ANY_KEYTYPE_IS(A, T) if (A.type() == typeid(const Keyword<T> *))

#define ANY_TO_CONST_KEY_PTR(A, T) boost::any_cast<const Keyword<T> *>(A)

#define PRINT_FUNC_NAME std::cout << "@ Section::" << __func__ << std::endl;

using namespace std;

Section::Section(const std::string & _name, const std::string & _tag) : name(_name) {
  isDefd = false;
  nsect = 0;
  nkeys = 0;
  if (tag.empty()) {
    this->tag = _name;
  } else {
    this->tag = _tag;
  }
}

Section::Section(const Section & s) {
  tag = s.tag;
  nkeys = s.nkeys;
  nsect = s.nsect;

  copySects(s);
  copyKeys(s);
}

Section & Section::operator=(const Section & s) {
  if (&s == this) {
    return *this;
  }
  name = s.name;
  tag = s.tag;
  nkeys = s.nkeys;
  nsect = s.nsect;

  copySects(s);
  copyKeys(s);

  return *this;
}

Section::~Section() {
  std::map<std::string, Section *>::iterator sit;
  std::map<std::string, boost::any>::iterator kit;
  for (sit = sects.begin(); sit != sects.end(); ++sit) {
    delete sects[sit->first];
  }
  for (kit = keys.begin(); kit != keys.end(); ++kit) {

    IF_ANY_KEYTYPE_IS(kit->second, int) {
      const Keyword<int> * key = ANY_TO_CONST_KEY_PTR(kit->second, int);
      delete key;
      continue;
    }
    IF_ANY_KEYTYPE_IS(kit->second, bool) {
      const Keyword<bool> * key = ANY_TO_CONST_KEY_PTR(kit->second, bool);
      delete key;
      continue;
    }
    IF_ANY_KEYTYPE_IS(kit->second, double) {
      const Keyword<double> * key = ANY_TO_CONST_KEY_PTR(kit->second, double);
      delete key;
      continue;
    }
    IF_ANY_KEYTYPE_IS(kit->second, std::string) {
      const Keyword<std::string> * key =
          ANY_TO_CONST_KEY_PTR(kit->second, std::string);
      delete key;
      continue;
    }
    IF_ANY_KEYTYPE_IS(kit->second, std::vector<int>) {
      const Keyword<std::vector<int>> * key =
          ANY_TO_CONST_KEY_PTR(kit->second, std::vector<int>);
      delete key;
      continue;
    }
    IF_ANY_KEYTYPE_IS(kit->second, std::vector<bool>) {
      const Keyword<std::vector<bool>> * key =
          ANY_TO_CONST_KEY_PTR(kit->second, std::vector<bool>);
      delete key;
      continue;
    }
    IF_ANY_KEYTYPE_IS(kit->second, std::vector<double>) {
      const Keyword<std::vector<double>> * key =
          ANY_TO_CONST_KEY_PTR(kit->second, std::vector<double>);
      delete key;
      continue;
    }
    IF_ANY_KEYTYPE_IS(kit->second, std::vector<std::string>) {
      const Keyword<std::vector<std::string>> * key =
          ANY_TO_CONST_KEY_PTR(kit->second, std::vector<std::string>);
      delete key;
      continue;
    }
    GETKW_ERROR("Error! Unknown key type!");
  }
}

void Section::copySects(const Section & s) {
  std::map<std::string, Section *>::const_iterator iter;
  for (iter = s.sects.begin(); iter != s.sects.end(); ++iter) {
    sects[iter->first] = new Section(*iter->second);
    tags[(*iter->second).tag] = sects[iter->first];
  }
}

void Section::copyKeys(const Section & s) {
  std::map<std::string, boost::any>::const_iterator iter;

  for (iter = s.keys.begin(); iter != s.keys.end(); ++iter) {
    IF_ANY_KEYTYPE_IS(iter->second, int) {
      const Keyword<int> * key = ANY_TO_CONST_KEY_PTR(iter->second, int);
      keys[iter->first] = boost::any(new const Keyword<int>(*key));
      continue;
    }
    IF_ANY_KEYTYPE_IS(iter->second, bool) {
      const Keyword<bool> * key = ANY_TO_CONST_KEY_PTR(iter->second, bool);
      keys[iter->first] = boost::any(new const Keyword<bool>(*key));
      continue;
    }
    IF_ANY_KEYTYPE_IS(iter->second, double) {
      const Keyword<double> * key = ANY_TO_CONST_KEY_PTR(iter->second, double);
      keys[iter->first] = boost::any(new const Keyword<double>(*key));
      continue;
    }
    IF_ANY_KEYTYPE_IS(iter->second, std::string) {
      const Keyword<std::string> * key =
          ANY_TO_CONST_KEY_PTR(iter->second, std::string);
      keys[iter->first] = boost::any(new const Keyword<std::string>(*key));
      continue;
    }
    IF_ANY_KEYTYPE_IS(iter->second, std::vector<int>) {
      const Keyword<std::vector<int>> * key =
          ANY_TO_CONST_KEY_PTR(iter->second, std::vector<int>);
      keys[iter->first] = boost::any(new const Keyword<std::vector<int>>(*key));
      continue;
    }
    IF_ANY_KEYTYPE_IS(iter->second, std::vector<bool>) {
      const Keyword<std::vector<bool>> * key =
          ANY_TO_CONST_KEY_PTR(iter->second, std::vector<bool>);
      keys[iter->first] = boost::any(new const Keyword<std::vector<bool>>(*key));
      continue;
    }
    IF_ANY_KEYTYPE_IS(iter->second, std::vector<double>) {
      const Keyword<std::vector<double>> * key =
          ANY_TO_CONST_KEY_PTR(iter->second, std::vector<double>);
      keys[iter->first] = boost::any(new const Keyword<std::vector<double>>(*key));
      continue;
    }
    IF_ANY_KEYTYPE_IS(iter->second, std::vector<std::string>) {
      const Keyword<std::vector<std::string>> * key =
          ANY_TO_CONST_KEY_PTR(iter->second, std::vector<std::string>);
      keys[iter->first] =
          boost::any(new const Keyword<std::vector<std::string>>(*key));
      continue;
    }
    GETKW_ERROR("Error! Unknown key type!");
  }
}

const Section & Section::getSect(const std::string & pathspec) const {
  std::vector<std::string> path;
  splitPath(pathspec, path);
  const Section * sect = traversePath(path, pathspec);
  return *sect;
}

template <typename T>
const Keyword<T> & Section::getKey(const std::string & pathspec) const {
  std::vector<std::string> path;
  splitPath(pathspec, path);

  std::string name = path.back();
  const Section * sect = traversePath(path, pathspec);
  if (!sect->has_key(name)) {
    GETKW_ERROR("Invalid keyword, " + pathspec);
  }
  std::map<std::string, boost::any>::const_iterator iter = sect->keys.find(name);
  return *ANY_TO_CONST_KEY_PTR(iter->second, T);
}

template <class T> const T & Section::get(const std::string & path) const {
  const Keyword<T> & key = this->getKey<T>(path);
  return key.get();
}

Section * Section::readSect(std::ifstream & /* fis */) { return 0; }

/* Sections can be multiply defined, provided they have different tags.
 * The first section section is added to the box, as well as to the tags
 * map if applicable. The following sections with the same name are added
 * to the tags map.
 */
void Section::addSect(Section * sect) {
  std::string name = sect->name + "<" + sect->tag + ">";
  if (has_key(name)) {
    GETKW_ERROR("Section::add: Section already defined, " + name);
  }

  sects[name] = sect;
  tags[sect->tag] = sects[name];
  nsect++;
}

void Section::addSect(Section & sect) {
  std::string name = sect.name + "<" + sect.tag + ">";
  if (has_key(name)) {
    GETKW_ERROR("Section::add: Section already defined, " + name);
  }

  sects[name] = new Section(sect);
  tags[sect.tag] = sects[name];
  nsect++;
}
//! Add an allocated key to a section
template <class T> void Section::addKey(const Keyword<T> * key) {
  const std::string & name = key->getName();

  if (has_key(name)) {
    GETKW_ERROR("Section::add: Key already defined, " + name);
  }

  keys[name] = boost::any(key);
  nkeys++;
}

//! Copy and and add a keyword to a section
template <class T> void Section::addKey(const Keyword<T> & key) {
  std::string name = key.getName();

  if (has_key(name)) {
    GETKW_ERROR("Section::add: Key already defined, " + name);
  }

  keys[name] = boost::any(new Keyword<T>(key));
  nkeys++;
}

const Section * Section::traversePath(std::vector<std::string> & path,
                                      const std::string & pathspec) const {
  std::string cur = path[0];

  if (path.size() == 1) {
    if (has_key(cur))
      return this;
    if (!has_sect(cur)) {
      cur = cur + "<" + cur + ">";
    }
    if (has_sect(cur)) {
      std::map<std::string, Section *>::const_iterator iter = sects.find(cur);
      return iter->second;
    }
    GETKW_ERROR("traversePath: Invalid path, " + pathspec);
  }

  if (!has_sect(cur))
    cur = cur + "<" + cur + ">";
  if (!has_sect(cur)) {
    GETKW_ERROR("traversePath: Invalid path, " + pathspec);
  }

  path.erase(path.begin());
  std::map<std::string, Section *>::const_iterator iter = sects.find(cur);
  return iter->second->traversePath(path, pathspec);
}

void Section::splitPath(const std::string & pathspec,
                        std::vector<std::string> & path) const {
  std::string str = pathspec;
  std::string::size_type m = 0;
  while (true) {
    m = str.find('.', m);
    if (m == std::string::npos) {
      path.push_back(str);
      break;
    } else {
      path.push_back(str.substr(0, m));
    }
    m++;
    str = str.substr(m);
  }
}

int Section::splitTag(const std::string & path, std::string & tag) const {
  std::string::size_type m, n = 0;
  m = path.find('<');
  if (m == std::string::npos)
    return 0;
  n = path.find('>');
  if (n == std::string::npos || n - m - 1 < 1)
    return 0;
  tag.clear();
  tag.append(path.substr(m + 1, n - m - 1));
  return m;
}

bool Section::has_key(const std::string & b) const {
  if (keys.find(b) == keys.end())
    return false;
  return true;
}

bool Section::has_sect(const std::string & b) const {
  if (sects.find(b) == sects.end())
    return false;
  return true;
}

bool Section::has_tag(const std::string & b) const {
  if (tags.find(b) == tags.end())
    return false;
  return true;
}

void Section::print() const { std::cout << &repr(std::cout) << std::endl; }

std::ostream & Section::repr(std::ostream & o) const {
  o << std::endl << name;
  if (name.compare(tag) != 0) {
    o << "<" + tag + ">";
  }
  o << " {" << std::endl;

  std::map<std::string, boost::any>::const_iterator iter;
  for (iter = keys.begin(); iter != keys.end(); ++iter) {
    IF_ANY_KEYTYPE_IS(iter->second, int) {
      o << *ANY_TO_CONST_KEY_PTR(iter->second, int) << std::endl;
      continue;
    }
    IF_ANY_KEYTYPE_IS(iter->second, bool) {
      o << *ANY_TO_CONST_KEY_PTR(iter->second, bool) << std::endl;
      continue;
    }
    IF_ANY_KEYTYPE_IS(iter->second, double) {
      o << *ANY_TO_CONST_KEY_PTR(iter->second, double) << std::endl;
      continue;
    }
    IF_ANY_KEYTYPE_IS(iter->second, std::string) {
      o << *ANY_TO_CONST_KEY_PTR(iter->second, std::string) << std::endl;
      continue;
    }
    IF_ANY_KEYTYPE_IS(iter->second, std::vector<int>) {
      o << *ANY_TO_CONST_KEY_PTR(iter->second, std::vector<int>) << std::endl;
      continue;
    }
    IF_ANY_KEYTYPE_IS(iter->second, std::vector<bool>) {
      o << *ANY_TO_CONST_KEY_PTR(iter->second, std::vector<bool>) << std::endl;
      continue;
    }
    IF_ANY_KEYTYPE_IS(iter->second, std::vector<double>) {
      o << *ANY_TO_CONST_KEY_PTR(iter->second, std::vector<double>) << std::endl;
      continue;
    }
    IF_ANY_KEYTYPE_IS(iter->second, std::vector<std::string>) {
      o << *ANY_TO_CONST_KEY_PTR(iter->second, std::vector<std::string>)
        << std::endl;
      continue;
    }
    GETKW_ERROR("Unknown key type!");
  }

  std::map<std::string, Section *>::const_iterator s_it;
  for (s_it = sects.begin(); s_it != sects.end(); ++s_it) {
    o << *s_it->second << std::endl;
  }

  o << "}";
  return o;
}

template void Section::addKey(const Keyword<int> *);
template void Section::addKey(const Keyword<double> *);
template void Section::addKey(const Keyword<bool> *);
template void Section::addKey(const Keyword<std::string> *);
template void Section::addKey(const Keyword<std::vector<int>> *);
template void Section::addKey(const Keyword<std::vector<double>> *);
template void Section::addKey(const Keyword<std::vector<bool>> *);
template void Section::addKey(const Keyword<std::vector<std::string>> *);

template void Section::addKey(const Keyword<int> &);
template void Section::addKey(const Keyword<double> &);
template void Section::addKey(const Keyword<bool> &);
template void Section::addKey(const Keyword<std::string> &);
template void Section::addKey(const Keyword<std::vector<int>> &);
template void Section::addKey(const Keyword<std::vector<double>> &);
template void Section::addKey(const Keyword<std::vector<bool>> &);
template void Section::addKey(const Keyword<std::vector<std::string>> &);

template const Keyword<int> & Section::getKey(const std::string &) const;
template const Keyword<double> & Section::getKey(const std::string &) const;
template const Keyword<bool> & Section::getKey(const std::string &) const;
template const Keyword<std::string> & Section::getKey(const std::string &) const;
template const Keyword<std::vector<int>> & Section::getKey(
    const std::string &) const;
template const Keyword<std::vector<double>> & Section::getKey(
    const std::string &) const;
template const Keyword<std::vector<bool>> & Section::getKey(
    const std::string &) const;
template const Keyword<std::vector<std::string>> & Section::getKey(
    const std::string &) const;

template const int & Section::get<int>(const std::string &) const;
template const bool & Section::get<bool>(const std::string &) const;
template const double & Section::get<double>(const std::string &) const;
template const std::string & Section::get<std::string>(const std::string &) const;
template const std::vector<int> & Section::get<std::vector<int>>(
    const std::string &) const;
template const std::vector<double> & Section::get<std::vector<double>>(
    const std::string &) const;
template const std::vector<bool> & Section::get<std::vector<bool>>(
    const std::string &) const;
template const std::vector<std::string> & Section::get<std::vector<std::string>>(
    const std::string &) const;

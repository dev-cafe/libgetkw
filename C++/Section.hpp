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

/*! \file Section.hpp
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief Container for Sections and Keywords
 */

#pragma once

#include <iosfwd>
#include <map>
#include <string>
#include <vector>

#include <boost/any.hpp>

template <typename T> class Keyword;

class Section final {
public:
  Section(const std::string & name, const std::string & tag = "");
  Section(const Section & s);
  Section & operator=(const Section & s);
  ~Section();
  const Section & getSect(const std::string & path) const;
  template <typename T> const Keyword<T> & getKey(const std::string & path) const;
  template <typename T> const T & get(const std::string & path) const;
  void addSect(Section & sect);
  void addSect(Section *);
  template <typename T> void addKey(const Keyword<T> & key);
  template <typename T> void addKey(const Keyword<T> * key);
  static Section * readSect(std::ifstream & fis);
  void print() const;
  std::ostream & repr(std::ostream & o) const;

  friend std::ostream & operator<<(std::ostream & o, const Section & s) {
    return s.repr(o);
  }
  const std::string & getTag() const { return tag; }
  int getNkeys() const { return nkeys; }
  int getNsect() const { return nsect; }
  void setTag(const std::string tag) { this->tag = tag; }
  void setNkeys(int nkeys) { this->nkeys = nkeys; }
  void setNsect(int nsect) { this->nsect = nsect; }
  bool isDefined() const { return isDefd; }
  std::string getName() const { return name; }
  void setDefined(bool isDefd) { this->isDefd = isDefd; }
  void setName(std::string name) { this->name = name; }

  int getInt(const std::string & path) const { return get<int>(path); }
  double getDbl(const std::string & path) const { return get<double>(path); }
  bool getBool(const std::string & path) const { return get<bool>(path); }
  const std::string & getStr(const std::string & path) const {
    return get<std::string>(path);
  }
  const std::vector<int> getIntVec(const std::string & path) const {
    return get<std::vector<int>>(path);
  }
  const std::vector<double> getDblVec(const std::string & path) const {
    return get<std::vector<double>>(path);
  }
  const std::vector<bool> getBoolVec(const std::string & path) const {
    return get<std::vector<bool>>(path);
  }
  const std::vector<std::string> getStrVec(const std::string & path) const {
    return get<std::vector<std::string>>(path);
  }
  const std::vector<std::string> getData(const std::string & path) const {
    return getStrVec(path);
  }

protected:
  std::string name;
  std::string tag;
  int nkeys;
  int nsect;
  bool isDefd;
  std::map<std::string, Section *> sects;
  std::map<std::string, boost::any> keys;
  std::map<std::string, Section *> tags;

  void copySects(const Section & s);
  void copyKeys(const Section & s);
  const Section * findSect(const std::string & pathspec) const;
  const Section * traversePath(std::vector<std::string> & path,
                               const std::string & pathspec) const;
  void splitPath(const std::string & pathspec,
                 std::vector<std::string> & path) const;
  int splitTag(const std::string & path, std::string & tag) const;
  bool has_key(const std::string & name) const;
  bool has_sect(const std::string & name) const;
  bool has_tag(const std::string & name) const;
};

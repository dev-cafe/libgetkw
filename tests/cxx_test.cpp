/*
 * getkw -- a simple input parser
 * Copyright (C) 2018 Jonas Juselius and contributors.
 *
 * This file is part of getkw.

 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on the complete list of contributors to the
 * getkw library, see: <http://getkw.readthedocs.io/>
 */

#include "Getkw.hpp"
#include "Keyword.hpp"
#include "Section.hpp"

int main() {
  auto parsed_fname = "@pcmsolver.inp";

  Getkw input(parsed_fname, false, true);

  auto units = input.getStr("UNITS");
  auto CODATAyear = input.getInt("CODATA");

  auto mol = input.getSect("MOLECULE");
  auto MEPfromMolecule = true;
  if (mol.isDefined()) {
    auto geometry_ = mol.getDblVec("GEOMETRY");
    MEPfromMolecule = mol.getBool("MEP");
  }

  auto cavity = input.getSect("CAVITY");
  auto cavityType = cavity.getStr("TYPE");
  auto area = cavity.getDbl("AREA");
  if (cavityType == "RESTART") {
    auto cavFilename = cavity.getStr("NPZFILE");
  }
  auto scaling = cavity.getBool("SCALING");
  auto radiiSet = cavity.getStr("RADIISET");
  auto minimalRadius = cavity.getDbl("MINRADIUS");
  auto mode = cavity.getStr("MODE");
  if (mode == "EXPLICIT") {
    auto spheresInput = cavity.getDblVec("SPHERES");
  } else if (mode == "ATOMS") {
    auto atoms = cavity.getIntVec("ATOMS");
    auto radii = cavity.getDblVec("RADII");
  }

  // Get the contents of the Medium section
  auto medium = input.getSect("MEDIUM");
  // Get the name of the solvent
  auto name = medium.getStr("SOLVENT");
  if (name == "EXPLICIT") {
    auto hasSolvent = false;
    // Get the probe radius
    auto probeRadius = medium.getDbl("PROBERADIUS");
    // Get the contents of the Green<inside> section...
    auto inside = medium.getSect("GREEN<INSIDE>");
    // ...and initialize the data members
    auto greenInsideType = inside.getStr("TYPE") + "_" + inside.getStr("DER");
    auto epsilonInside = inside.getDbl("EPS");
    // Get the contents of the Green<outside> section...
    auto outside = medium.getSect("GREEN<OUTSIDE>");
    // ...and initialize the data members
    auto greenOutsideType = outside.getStr("TYPE") + "_" + outside.getStr("DER");
    auto epsilonStaticOutside = outside.getDbl("EPS");
    auto epsilonDynamicOutside = outside.getDbl("EPSDYN");
    auto epsilonStatic1 = outside.getDbl("EPS1");
    auto epsilonDynamic1 = outside.getDbl("EPSDYN1");
    auto epsilonStatic2 = outside.getDbl("EPS2");
    auto epsilonDynamic2 = outside.getDbl("EPSDYN2");
    auto center = outside.getDbl("CENTER");
    auto width = outside.getDbl("WIDTH");
    auto origin = outside.getDblVec("INTERFACEORIGIN");
    if (outside.getStr("TYPE") == "SPHERICALDIFFUSE") {
      greenOutsideType += "_" + outside.getStr("PROFILE");
    }
    auto maxL = outside.getInt("MAXL");
  } else {
    // This part must be reviewed!! Some data members are not initialized...
  }
  auto integratorType = medium.getStr("DIAGONALINTEGRATOR");
  auto integratorScaling = medium.getDbl("DIAGONALSCALING");

  auto solverType = medium.getStr("SOLVERTYPE");
  auto correction = medium.getDbl("CORRECTION");
  auto hermitivitize = medium.getBool("MATRIXSYMM");
  auto isDynamic = medium.getBool("NONEQUILIBRIUM");
}

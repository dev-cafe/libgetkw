#!/usr/bin/env python

from distutils.core import setup, Extension
import posix


module1 = Extension('mrchem',
#        define_macros=[('FOO', '1')],
		include_dirs=['../include', '.'],
		library_dirs=['../lib'],
		libraries=['mrc', 'mrchem', 'cblas', 'f77blas', 'atlas'],
		sources=['mrchemmod.c', 'pygetkw.c'])

setup(name='MRChem',
		version='0.1',
		description='This is the MRChem program',
		author='Jonas Juselius',
		author_email='jonas.juselius@chem.uit.no',
		url='http://jonas.iki.fi',
		long_description="""
No description available.
""",
		ext_modules=[module1])


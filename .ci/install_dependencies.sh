#!/usr/bin/env bash

# https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/
set -euo pipefail

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  pip install --user pipenv --upgrade
elif [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
  brew update &> /dev/null
  brew cask uninstall --force oclint
  brew uninstall --force --ignore-dependencies boost
  brew upgrade python
  brew install pipenv
  brew install gcc
  brew install boost@1.59
  brew install boost-python@1.59
  # Symlink the installed Boost.Python to where all the rest of Boost resides
  ln -sf /usr/local/opt/boost-python@1.59/lib/* /usr/local/opt/boost@1.59/lib
fi

#!/usr/bin/env bash

if [ ! -d "./.venv/" ]; then
    python3 -m venv ./.venv

    source ./.venv/bin/activate

    pip install --upgrade pip
    pip --version

    pip install requests

    pip install -U pandas numpy seaborn matplotlib
    pip install scikit-learn
    pip install jupyterlab
    pip install jupyterlab-requirements

else

    source ./.venv/bin/activate

fi

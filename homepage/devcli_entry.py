"""Entry-point wrapper that runs the top-level devcli.py script without modifying it.

This lets the setuptools console_scripts entry point call a stable callable while executing
the original script as-is (so we don't change your `devcli.py`).
"""
import runpy
import os
import sys


def main():
    # determine path to the top-level devcli.py next to this file
    script_path = os.path.join(os.path.dirname(__file__), 'devcli.py')
    if not os.path.exists(script_path):
        print('devcli.py not found at', script_path, file=sys.stderr)
        return 1
    # Execute the script as __main__ so it behaves like running the file directly
    runpy.run_path(script_path, run_name='__main__')


if __name__ == '__main__':
    raise SystemExit(main())

from setuptools import setup, find_packages

setup(
    name="devcli",
    version="0.1.0",
    description="Developer project generator CLI",
    packages=find_packages(exclude=("tests", "docs")),
    # Include top-level single-file modules so devcli.py and devcli_entry.py are importable
    py_modules=["devcli", "devcli_entry"],
    include_package_data=True,
    install_requires=["inquirer"],
    entry_points={
        "console_scripts": [
            "devcli=devcli_entry:main",
        ],
    },
    python_requires=">=3.8",
)

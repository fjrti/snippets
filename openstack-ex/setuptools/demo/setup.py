from setuptools import setup, find_packages
setup(
    name = "demo",
    version = "0.1",
    packages = find_packages(),

    # optional
    # define foo and bar
    entry_points = {
        'console_scripts': [
            'foo = demo:test',
            'bar = demo:test',
        ],
        'gui_scripts': [
            'baz = demo:test',
        ]

        # optional
        # define ep, make egg file exec
        #'setuptools.installation': [
        #    'eggsecutable = demo:test',
        #]
    }

)

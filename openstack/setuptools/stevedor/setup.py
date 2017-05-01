from setuptools import setup, find_packages

setup(
    name='stevedoretest1',
    version='1.0',

    packages=find_packages(),

    entry_points={
        'stevedoretest.formatter': [
            'simple = example.simple:Simple',
            'plain = example.simple:Simple',
        ],
    },
)



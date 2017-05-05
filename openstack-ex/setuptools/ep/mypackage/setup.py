import setuptools

# In python < 2.7.4, a lazy loading of package `pbr` will break
# setuptools if some other modules registered functions in `atexit`.
# solution from: http://bugs.python.org/issue15881#msg170215

setuptools.setup(
    name='mypackage',
    packages=['mypackage'],
    package_dir={'mypackage': 'mypackage'},
    setup_requires=['pbr'],
    pbr=True,
    entry_points={
        'mypackage.api.v1':[
            'databases=mypackage.api.v1.databases:main',
            'hello=mypackage.api.v1.hello:main',
            ],
    }
)

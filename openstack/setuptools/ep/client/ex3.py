from pkg_resources import load_entry_point
load_entry_point('mypackage', 'mypackage.api.v1', 'database')()

import pkg_resources

def run_entry_point(*argv):
    group = 'mypackage.api.v1'
    for entrypoint in pkg_resources.iter_entry_points(group=group):
        # Grab the function that is the actual plugin.
        plugin = entrypoint.load()
        print plugin
        type(plugin)
        plugin(*argv)

from stevedore import extension

def test_detect_plugins():
    em = extension.ExtensionManager('mypackage.api.v1')
    names = sorted(em.names())
    print names
    em1 = extension.ExtensionManager('mypackage.api.v1')
    eps1 = [ext.plugin for ext in em1]
    em1 = extension.ExtensionManager('mypackage.api.v1')
    eps1 = [ext.entry_point for ext in em1]


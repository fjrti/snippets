import ConfigParser
 
config = ConfigParser.ConfigParser()
config.readfp(open(raw_input("input file name:"), "rb"))
print config.get("global", "ip")
　　

config.ini

[global]
ip = 192.168.1.100 ;ip地址
port = 3306
password = 123456


# python-network-programming-cookbook
this repo is 《Python Network Programming Cookbook》's code

Chapter 1: Sockets, IPv4, and Simple Client/Server Programming	p19
	Introduction	p20
	Printing your machine's name and IPv4 address	p20
	Retrieving a remote machine's IP address	p22
	Converting an IPv4 address to different formats	p24
	Finding a service name, given the port and protocol	p25
	Converting integers to and from host to network byte order	p26
	Setting and getting the default socket timeout	p27
	Handling socket errors gracefully	p28
	Modifying socket's send/receive buffer sizes	p32
	Changing a socket to the blocking/ non-blocking mode	p33
	Reusing socket addresses	p35
	Printing the current time from the Internet time server	p37
	Writing a SNTP client	p38
	Writing a simple echo client/server application	p39
Chapter 2: Multiplexing Socket I/O for Better Performance	p43
	Introduction	p43
	Using ForkingMixIn in your socket server applications	p44
	Using ThreadingMixIn in your socket server applications	p47
	Writing a chat server using select.select	p50
	Multiplexing a web server using select.epoll	p57
	Multiplexing an echo server using Diesel concurrent library	p61
Chapter 3: IPv6, Unix Domain Sockets, and Network Interfaces	p65
	Introduction	p66
	Forwarding a local port to a remote host	p66
	Pinging hosts on the network with ICMP	p70
	Waiting for a remote network service	p74
	Enumerating interfaces on your machine	p77
	Finding the IP address for a specific interface on your machine	p79
	Finding whether an interface is up on your machine	p81
	Detecting inactive machines on your network	p82
	Performing a basic IPC using connected sockets (socketpair)	p85
	Performing IPC using Unix domain sockets	p86
	Finding out if your Python supports IPv6 sockets	p89
	Extracting an IPv6 prefix from an IPv6 address	p92
	Writing an IPv6 echo client/server	p94
Chapter 4: Programming with HTTP for the Internet	p97
	Introduction	p97
	Downloading data from an HTTP server	p98
	Serving HTTP requests from your machine	p100
	Extracting cookie information after visiting a website	p103
	Submitting web forms	p106
	Sending web requests through a proxy server	p108
	Checking whether a web page exists with the HEAD request	p109
	Spoofing Mozilla Firefox in your client code	p111
	Saving bandwidth in web requests with the HTTP compression	p112
	Writing an HTTP fail-over client with resume and partial downloading	p115
	Writing a simple HTTPS server code with Python and OpenSSL	p117
Chapter 5: E-mail protocols, FTP, and CGI programming	p119
	Introduction	p119
	Listing the files in a remote FTP server	p120
	Uploading a local file to a remote FTP server	p121
	E-mailing your current working directory as a compressed ZIP file	p123
	Downloading your Google e-mail with POP3	p127
	Checking your remote e-mail with IMAP	p129
	Sending an e-mail with an attachment via Gmail SMTP server	p131
	Writing a guestbook for your (Python-based) web server with CGI	p133
Chapter 6: Screen-scraping and Other Practical Applications	p139
	Introduction	p139
	Searching for business addresses using the Google Maps API	p140
	Searching for geographic coordinates using the Google Maps URL	p141
	Searching for an article in Wikipedia	p143
	Searching for Google stock quote	p147
	Searching for a source code repository at GitHub	p149
	Reading news feed from BBC	p152
	Crawling links present in a web page	p155
Chapter 7: Programming Across Machine Boundaries	p159
	Introduction	p159
	Executing a remote shell command using telnet	p160
	Copying a file to a remote machine by SFTP	p162
	Printing a remote machine's CPU information	p164
	Installing a Python package remotely	p167
	Running a MySQL command remotely	p170
	Transferring files to a remote machine over SSH	p174
	Configuring Apache remotely to host a website	p177
Chapter 8: Working with Web Services – XML-RPC, SOAP, and REST	p181
	Introduction	p181
	Querying a local XML-RPC server	p182
	Writing a multithreaded multicall XML-RPC server	p185
	Running an XML-RPC server with a basic HTTP authentication	p187
	Collecting some photo information from Flickr using REST	p191
	Searching for SOAP methods from an Amazon S3 web service	p196
	Searching Google for custom information	p198
	Searching Amazon for books through product search API	p200
Chapter 9: Network Monitoring and Security	p203
	Introduction	p203
	Sniffing packets on your network	p204
	Saving packets in the pcap format using the pcap dumper	p207
	Adding an extra header in HTTP packets	p211
	Scanning the ports of a remote host	p213
	Customizing the IP address of a packet	p215
	Replaying traffic by reading from a saved pcap file	p217
	Scanning the broadcast of packets	p220
Index	p223


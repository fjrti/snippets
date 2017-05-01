#include <stdio.h>

void str2mac(unsigned char *mac_addr, const unsigned char *mac)
{
	int i;
	unsigned char mac1[12];

	for (i = 0; i < 12; i++) {
		if (isdigit(mac[i]))
			mac1[i] = mac[i] - 0x30;
		else if (isupper(mac[i]))
			mac1[i] = mac[i] - 0x37;
		else
			mac1[i] = mac[i] - 0x57;

		printf("%x\n", mac1[i]);
		//printf("%x\n", mac1[i] << 4);
	}

	mac_addr[0] = (mac1[0] << 4) | mac1[1];
	mac_addr[1] = (mac1[2] << 4) | mac1[3];
	mac_addr[2] = (mac1[4] << 4) | mac1[5];
	mac_addr[3] = (mac1[6] << 4) | mac1[7];
	mac_addr[4] = (mac1[8] << 4) | mac1[9];
	mac_addr[5] = (mac1[10] << 4) | mac1[11];
}

int main()
{
	//unsigned char *mac = "031987072715";
	unsigned char *mac = "03BAbe072715";
	const char *mac1 = "03:19:87:07:27:15";
	unsigned char mac_addr[6];

	str2mac(mac_addr, mac);

	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
			mac_addr[0], mac_addr[1],
			mac_addr[2], mac_addr[3],
			mac_addr[4], mac_addr[5]);
	//printf("%s\n", mac1);

	sscanf(mac1, "%02x:%02x:%02x:%02x:%02x:%02x",
			(unsigned int *)&mac_addr[0],
			(unsigned int *)&mac_addr[1],
			(unsigned int *)&mac_addr[2],
			(unsigned int *)&mac_addr[3],
			(unsigned int *)&mac_addr[4],
			(unsigned int *)&mac_addr[5]);

	printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
			mac_addr[0], mac_addr[1],
			mac_addr[2], mac_addr[3],
			mac_addr[4], mac_addr[5]);

	return 0;
}

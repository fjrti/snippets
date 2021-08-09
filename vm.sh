#!/bin/bash

# Reference
#
# https://libvirt.org/formatdomain.html
# https://libvirt.org/formatnetwork.html
# https://libvirt.org/hooks.html
# TODO 
# param, ssh certfile
# vncdisplay
# br001
# option has error
# rm protect
# console with root

# archlinux image
# https://gitlab.archlinux.org/archlinux/arch-boxes/-/jobs/artifacts/master/browse/output?job=build:secure

# raw   -> qcow2 : qemu-img convert -f qcow2 -O raw CentOS-6.9.qcow2 CentOS-6.9.raw
# qcow2 -> raw : qemu-img convert -f raw -O qcow2 CentOS-6.9.raw CentOS-6.9.qcow2

# sudo virsh list --all --name
# hy149372 ALL=(ALL) NOPASSWD:/usr/bin/virsh

#/ Usage:
#/   vm addbat $num
#/   vm add [ $vmname ]
#/   vm rm $vmname 
#/   vm ls
#/   vm { shutdown | start | destroy } $vmname
#/   vm { mknet | rmnet }
#/ Option:
#/   -c|--cpu  num        - vcpu number
#/   -m|--mem  num        - vm memory (GB)
#/   -i|--image name      - base image

WORKDIR=$(cd $(dirname $0); pwd)
VIRSH="sudo virsh"
RM="/bin/rm -f"
CP="/bin/cp"

# default parameter
MEM=8
CPU=8
DIR="$HOME/.vm"
BASE_IMAGE="$DIR/centos7-base.qcow2"
BASE="bat1"
BR="br001"

usage()
{
    grep '^#/' "$0" | cut -c4- ; exit 0 ;
}

gen_domain_xml()
{
    local name=$1
    local cpu=$2
    local mem=$3
    local image=$4
    local mac=$5
    local uuid=$(uuidgen)
    local file="_domain.xml"

cat  > $file << EOF
<domain type='kvm' id='12'>
  <name>$name</name>
  <uuid>$uuid</uuid>
  <memory unit='GiB'>$mem</memory>
  <vcpu placement='static'>$cpu</vcpu>
  <resource>
    <partition>/machine</partition>
  </resource>
  <os>
    <type arch='x86_64' machine='pc-i440fx-rhel7.0.0'>hvm</type>
    <boot dev='hd'/>
  </os>
  <features>
    <acpi/>
    <apic/>
  </features>
  <cpu mode='custom' match='exact'>
    <model fallback='allow'>IvyBridge</model>
  </cpu>
  <clock offset='utc'>
    <timer name='rtc' tickpolicy='catchup'/>
    <timer name='pit' tickpolicy='delay'/>
    <timer name='hpet' present='no'/>
  </clock>
  <on_poweroff>destroy</on_poweroff>
  <on_reboot>restart</on_reboot>
  <on_crash>restart</on_crash>
  <pm>
    <suspend-to-mem enabled='no'/>
    <suspend-to-disk enabled='no'/>
  </pm>
  <devices>
    <emulator>/usr/libexec/qemu-kvm</emulator>
    <disk type='file' device='disk'>
      <driver name='qemu' type='qcow2'/>
      <source file='$image'/>
      <backingStore/>
      <target dev='sda' bus='sata'/>
      <alias name='sata0-0-0'/>
      <address type='drive' controller='0' bus='0' target='0' unit='0'/>
    </disk>
    <controller type='usb' index='0' model='ich9-ehci1'>
      <alias name='usb'/>
      <address type='pci' domain='0x0000' bus='0x00' slot='0x05' function='0x7'/>
    </controller>
    <controller type='usb' index='0' model='ich9-uhci1'>
      <alias name='usb'/>
      <master startport='0'/>
      <address type='pci' domain='0x0000' bus='0x00' slot='0x05' function='0x0' multifunction='on'/>
    </controller>
    <controller type='usb' index='0' model='ich9-uhci2'>
      <alias name='usb'/>
      <master startport='2'/>
      <address type='pci' domain='0x0000' bus='0x00' slot='0x05' function='0x1'/>
    </controller>
    <controller type='usb' index='0' model='ich9-uhci3'>
      <alias name='usb'/>
      <master startport='4'/>
      <address type='pci' domain='0x0000' bus='0x00' slot='0x05' function='0x2'/>
    </controller>
    <controller type='pci' index='0' model='pci-root'>
      <alias name='pci.0'/>
    </controller>
    <controller type='sata' index='0'>
      <alias name='sata0'/>
      <address type='pci' domain='0x0000' bus='0x00' slot='0x04' function='0x0'/>
    </controller>
    <controller type='virtio-serial' index='0'>
      <alias name='virtio-serial0'/>
      <address type='pci' domain='0x0000' bus='0x00' slot='0x06' function='0x0'/>
    </controller>
    <interface type='bridge'>
      <mac address='$mac'/>
      <source bridge='$BR'/>
      <target dev='vnet8'/>
      <model type='virtio'/>
      <alias name='net0'/>
      <address type='pci' domain='0x0000' bus='0x00' slot='0x03' function='0x0'/>
    </interface>
    <serial type='pty'>
      <source path='/dev/pts/3'/>
      <target type='isa-serial' port='0'/>
      <alias name='serial0'/>
    </serial>
    <console type='pty' tty='/dev/pts/3'>
      <source path='/dev/pts/3'/>
      <target type='serial' port='0'/>
      <alias name='serial0'/>
    </console>
    <input type='tablet' bus='usb'>
      <alias name='input0'/>
    </input>
    <memballoon model='virtio'>
      <alias name='balloon0'/>
      <address type='pci' domain='0x0000' bus='0x00' slot='0x07' function='0x0'/>
    </memballoon>
    <graphics type='vnc' port='-1' listen='0.0.0.0' keymap='en-us'/>
  </devices>
</domain>
EOF

echo $file
}

gen_network_xml()
{
    local file="_network.xml"
    local name="net001"


cat  > $file << EOF
<network>
  <name>$name</name>
  <uuid>6e687615-6130-463c-9df6-efbff07f881e</uuid>
  <forward mode='nat'>
    <nat>
      <port start='1024' end='65535'/>
    </nat>
  </forward>
  <bridge name='br001' stp='on' delay='0'/>
  <mac address='00:00:01:00:00:ff'/>
  <dns>
    <host ip='192.168.200.11'>
      <hostname>bat11</hostname>
    </host>
    <host ip='192.168.200.12'>
      <hostname>bat12</hostname>
    </host>
    <host ip='192.168.200.13'>
      <hostname>bat13</hostname>
    </host>
    <host ip='192.168.200.14'>
      <hostname>bat14</hostname>
    </host>
    <host ip='192.168.200.15'>
      <hostname>bat15</hostname>
    </host>
    <host ip='192.168.200.16'>
      <hostname>bat16</hostname>
    </host>
    <host ip='192.168.200.17'>
      <hostname>bat17</hostname>
    </host>
    <host ip='192.168.200.18'>
      <hostname>bat18</hostname>
    </host>
    <host ip='192.168.200.19'>
      <hostname>bat19</hostname>
    </host>
  </dns>
  <ip address='192.168.200.1' netmask='255.255.255.0'>
    <dhcp>
      <range start='192.168.200.2' end='192.168.200.254'/>
      <host mac="00:00:01:00:00:11" ip="192.168.200.11"/>
      <host mac="00:00:01:00:00:12" ip="192.168.200.12"/>
      <host mac="00:00:01:00:00:13" ip="192.168.200.13"/>
      <host mac="00:00:01:00:00:14" ip="192.168.200.14"/>
      <host mac="00:00:01:00:00:15" ip="192.168.200.15"/>
      <host mac="00:00:01:00:00:16" ip="192.168.200.16"/>
      <host mac="00:00:01:00:00:17" ip="192.168.200.17"/>
      <host mac="00:00:01:00:00:18" ip="192.168.200.18"/>
      <host mac="00:00:01:00:00:19" ip="192.168.200.19"/>
    </dhcp>
  </ip>
</network>
EOF

echo $file

}

mk_net()
{
    local name="net001"
    local file=$(gen_network_xml)

    $VIRSH net-define $file
    $VIRSH net-start $name
    $VIRSH net-autostart $name
    $RM $file
}

rm_net()
{
    local name="net001"
    $VIRSH net-destroy $name
    $VIRSH net-undefine $name
}

rm_net()
{
    local name="net001"

    $VIRSH net-destroy $name
    $VIRSH net-undefine $name
    $VIRSH net-list
}

restart_net()
{
	# issues all VMs to shutdown
	echo "issuing command to shut down all VMs..."
	for i in $($VIRSH list --name --state-running); do $VIRSH shutdown $i; done

	# sleep until all of the VMs have successfully shutdown
	while true; do
		RESULT=$($VIRSH list --state-running | wc -l)
		# the command output will still have 3 lines when all VMs are offline
		if [[ "$RESULT" -ne "3" ]]; then
			echo "waiting for VMs to shut down, still $((RESULT - 3)) online..."
			sleep 2
		else
			break
		fi
	done

	# destroys and rebuilds the default network
	echo "destroying and rebuilding virtual network..."
	$VIRSH net-destroy net001
	$VIRSH net-start net001

	# bring all of the VMs back up
	echo "bringing all the VMs back online..."
	for i in $($VIRSH list --name --state-shutoff); do $VIRSH start $i; done
}

add_vm_one()
{
    # if [ "$#" -ne 1 ]; then
    #     echo "vm num $#"
    #     exit 1
    # fi

    local name=$1
    if [ -z $name ]; then
        name="hy-"$(uuidgen | awk -F - '{print $1}')
    fi

    local mac=$(printf '00:00:02:%02X:%02X:%02X\n' $[RANDOM%256] $[RANDOM%256] $[RANDOM%256])
    local image="$DIR/$name.qcow2"
    local file=$(gen_domain_xml $name $CPU $MEM $image $mac)
    $CP $BASE_IMAGE $image
    echo -e "Base image [$BASE_IMAGE] \n"
    $VIRSH define $file
    $VIRSH start $name
    $RM $file
}

add_vm()
{
    if [ "$#" -ne 1 ]; then
        echo "vm num $#"
        exit 1
    fi

    local num=$1
    local re='^[0-9]+$'
    if ! [[ $num =~ $re ]] ; then
        echo "Error: not a number" >&2; exit 1
    fi

    if ((num > 9)); then
        echo "Error: max num is 9"
        exit 1
    fi

    echo -e "Base image [$BASE_IMAGE] \n"
    for (( c = 1; c <= $num; c++ )); do
        local name=$BASE$c
        local image="$DIR/$name.qcow2"
        local mac="00:00:01:00:00:1"$c
        local file=$(gen_domain_xml $name $CPU $MEM $image $mac)
        $CP $BASE_IMAGE $image
        $VIRSH define $file
        $VIRSH start $name
        $RM $file
    done
}

rm_vm()
{
    [ "$#" -ne 1 ] && echo "Error: need vmname" && exit 1

    local name=$1
    $VIRSH destroy $name
    $VIRSH undefine $name
    $RM "$DIR/$name.qcow2"
}

ssh_vm()
{
    local vm=$1
    local mac=$($VIRSH dumpxml $vm  | grep 'mac address' | cut -b 21-37)
    local ip=$(cat /proc/net/arp | grep "$mac" | awk '{print $1}')
    ssh root@$ip
}

ls_vm()
{
    local mac
    local ip
    local vm
    local vcpu
    local mem
    local spec
    local vnc

    $VIRSH list --all
    echo "----------------------------------------------------"
    for vm in $($VIRSH list --all --name); do
        mac=$($VIRSH dumpxml $vm  | grep 'mac address' | cut -b 21-37)
        ip=$(cat /proc/net/arp | grep "$mac" | awk '{print $1}')
        vcpu=$($VIRSH dumpxml $vm | grep vcpu | grep -o "[0-9]*")
        mem=$($VIRSH dumpxml $vm | grep memory | grep -o "[0-9]*")
        mem=$(((mem/1024/1024)))
        spec="$vcpu"C"$mem"G
        vnc=$($VIRSH vncdisplay $vm 2>/dev/null)
        printf '%-12s %-6s %-15s  %s  %s\n' $vm $spec ${ip:-'* * *'} $mac $vnc
    done
}

op_vm()
{
    $VIRSH $1 $2
}

process_option()
{
    local key

    while [ "$#" -ge 1 ]; do
        key="$1"

        case $key in
            -c|--cpu)
                CPU="$2"
                shift
                ;;
            -m|--mem)
                MEM="$2"
                shift
                ;;
            -i|--image)
                BASE_IMAGE=$(readlink -f $2) 
                shift
                ;;
        esac
        shift
    done
}

main()
{
    local key
    [ $# -eq 0 ] && usage && exit 1
    process_option $@

    while [ "$#" -ge 1 ]; do
        key="$1"
        case $key in
            addbat)
                add_vm $2
                shift
                ;;
            add)
                if [[ $2 =~ ^- ]] || [[ -z $2 ]]; then
                    add_vm_one
                else
                    add_vm_one $2
                    shift
                fi
                ;;
            rm|del|delete)
                rm_vm $2
                shift
                ;;
            mknet)
                mk_net
                ;;
            rmnet)
                rm_net
                ;;
            ls|list)
                ls_vm
                ;;
            ssh)
                ssh_vm $2
                shift
                ;;
            shutdown|start|destroy)
                op_vm $1 $2
                shift
                ;;
            -c|--cpu)
                shift
                ;;
            -m|--mem)
                shift
                ;;
            -i|--image)
                shift
                ;;
            *)
                usage
                ;;
        esac
        shift
    done
}

main $@
SAVE TO CACHER

#!/bin/bash
echo "Check disk usage in Linux System"
disk_size = `df -h | grep "/dev/disk3s6" | awk '{print $5}' | cut -d '%' -f 1`
echo "$disk_size %  of disk is filled"
if [ $disk_size -gt 80 ];
then
	echo "disk is utilized more than 80%, exapnd disk or deletes files soon"
else
	echo "enough disk is available"
fi

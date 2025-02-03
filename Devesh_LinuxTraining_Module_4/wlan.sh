#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Invalid Number of Arguments"
	exit 1
fi

input="$1"
output="output.txt"

>"$output"

while IFS= read -r line; do
	frame_time=$(echo "$line" |grep "frame.time\":"| xargs)
	if [[ -n "$frame_time" ]]; then
		echo "$frame_time">>"$output"
	fi
	wlan_fc_type=$(echo "$line" |grep "wlan.fc.type\":"| xargs)
	if [[ -n "$wlan_fc_type" ]]; then
                echo "$wlan_fc_type">>"$output"
        fi
	wlan_fc_subtype=$(echo "$line" |grep "wlan.fc.subtype\":"| xargs)
        if [[ -n "$wlan_fc_subtype" ]]; then
                echo "$wlan_fc_subtype">>"$output"
        fi

done<"$input"

echo "Done..output is saved to $output"

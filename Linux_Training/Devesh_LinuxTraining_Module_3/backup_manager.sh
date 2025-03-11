#!/bin/bash

if [ "$#" -ne 3 ];then
	exit 1
fi

#echo "First part success"

src_dir="$1"
back_dir="$2"
file_type="$3"

if [ ! -d "$src_dir" ];then
	echo "Source Directory does not exist"
	exit 1
fi

if [ ! -d "$back_dir" ];then
        echo "Backup Directory does not exist..creating it"
        mkdir -p "$back_dir"
fi

files=("$src_dir"/*"$file_type")

echo "${files[@]}"

if [ "${#files[@]}" -eq 0 ] ||  [ ! -e "${files[0]}" ]; then
	echo "Source directory does not contain any matching files"
	exit 1
fi

export BACKUP_COUNT=0
total_size=0

for file in "${files[@]}";do
	File=$(basename "$file")
	dest="$back_dir"/"$File"
	file_size=$(stat -c%s "$file")
	if [ -e "$dest" ];then
		if [ "$file" -nt "$dest" ];then
			echo "File: $File exists....but backup is newer..so backup is processing\n File=$File Size=$file_size"
			cp --preserve=all "$file" "$dest"
			echo "Backup done for $File"
		else
			echo "Backup file:$File  exists and is newer"
		fi
	else
		echo "Backup file:$File Size=$file_size"
		cp --preserve=all "$file" "$dest"
		echo "Backup done for $File"
	fi
	BACKUP_COUNT=$((BACKUP_COUNT+1))
	file_size=$(stat -c%s "$file")
	total_size=$((total_size+file_size))
done
	
report_file="$back_dir"/backup_report.log
{
	echo "Total files processed:$BACKUP_COUNT"
	echo "Total size of Files backed up:$total_size"
	echo "Backup Directory path:$back_dir"
} > "$report_file"

echo "Backup complete report stored in $report_file"

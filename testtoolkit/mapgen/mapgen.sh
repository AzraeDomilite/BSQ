#!/bin/bash

if [ "$#" -ne 2 ]; then
	echo "expect = $0 size density"
	exit 1
fi

size=$1
numbers_files=100
density=$2
map_files=""

generate_char() {
	local rand_char
	rand_char=$(printf "\\$(printf '%03o' $((RANDOM % 94 + 33)))")
	echo "$rand_char"
}

generate_unique_chars() {
	local char1 char2 char3
	while true; do
		char1=$(generate_char)
		char2=$(generate_char)
		char3=$(generate_char)
		if [[ "$char1" != "$char2" && "$char2" != "$char3" && "$char1" != "$char3" ]]; then
			echo "$char1 $char2 $char3"
			break
		fi
	done
}

for i in $(seq 1 $numbers_files); do
	num1=$((RANDOM % 9 + $size))
	num2=$((RANDOM % 9 + $size))
	num3=$density

	read -r char1 char2 char3 <<< "$(generate_unique_chars)"

	file_number=$(printf "%03d" $i)
	filename="test${file_number}.map"

	./a.out "$num1" "$num2" "$num3" "$char1" "$char2" "$char3" "$filename"
done

for i in $(seq -w 1 $numbers_files); do
	map_file="test$i.map"
	map_files="$map_files $map_file"
done

echo "Executing ./bsq $map_files"
time ../../bsq $map_files

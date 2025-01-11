#!/bin/bash

cd src && make
cd ..

input=""
output="output.dot"

function display_help {
    echo "Usage: $0 -input <input_file_name> -output <outputt_file_name> "
    echo "Options:"
    echo "  -input or -i <inputt_file_name>: Specify the input file path (required)"
    echo "  -output or -o <outputt_file_name>: Specify the output file path (required)"
    echo "  -help or -h to display this help message"
}

function all_input_files {
  for file in tests/*.py; do
    [ -f "$file" ] || continue
    filename=$(basename -- "$file")
    filename="${filename%.*}"
    printf '%.s─' $(seq 1 $(tput cols))
    echo $filename.py
    ./src/frontend < $file >  outputs/output_$filename".dot"
    if [ $? == 1 ]; then
      echo ""
      echo "ERROR PRESENT in file $filename.py"
    else
      dot -Tpdf outputs/output_$filename".dot" -o outputs/output_$filename".pdf"
      echo ""
      echo "NO ERRORS in $filename.py"
    fi
    printf '%.s─' $(seq 1 $(tput cols))
  done
  exit 1
}

if [ $# == 0 ];
then
  all_input_files
fi

while [[ $# -gt 0 ]]; do
    case "$1" in
        -i|-input)
            input=$2
            shift 2
            ;;
        -o|-output)
            output=$2
            shift 2
            ;;
        -h|-help)
            display_help
            exit 0
            ;;
        *)
            echo "Error: Invalid option $1"
            display_help
            exit 1
            ;;
    esac
done


printf '%.s─' $(seq 1 $(tput cols))
echo $input
./src/frontend < tests/$input >  outputs/$output
if [ $? == 1 ]; then
  echo ""
  echo "ERROR PRESENT in file $input"
else
  echo ""
  filename=$(basename -- "$output")
  filename="${filename%.*}"
  dot -Tpdf outputs/$output -o outputs/$filename".pdf"
  echo "NO ERRORS in $input"
fi
printf '%.s─' $(seq 1 $(tput cols))

#!/bin/bash

cd src && make
cd ..

input="input.py"
output="outputs/output.s"

function display_help {
    echo "Usage: $0 -input <input_file_path> -output <outputt_file_name> "
    echo "Options:"
    echo "  -input or -i <input_file_path>: Specify the input file path (required)"
    echo "  -output or -o <output_file_path>: Specify the output file path (required)"
    echo "  -help or -h to display this help message"
}



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
./src/exec < $input > $output
if [ $? == 1 ]; then
  echo ""
  echo "ERROR PRESENT in file $input"
else
  echo ""
  filename=$(basename -- "$output")
  filename="${filename%.*}"
  echo "NO ERRORS in $input"
  dot -Tpdf outputs/output.dot -o outputs/output.pdf
fi
printf '%.s─' $(seq 1 $(tput cols))

#Colors for pass/fail messages
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
NORMAL=$(tput sgr0)

#Checks for -h flag and prints help message if issued
while getopts h flag; do
    case "${flag}" in
    h)
        printf "Usage: ./test_xml.sh [XML FILE] [COMMAND FILES...]\n"
        printf "Function: Runs the Zork Project with the desired XML generated dungeon.\n"
        exit 0
        ;;
    esac
done

#TODO: Move build command into script
make rebuild_command_file

#Sets number of columns to move the pass/fail messages to the number supported columns in the terminal
col=$(tput cols)

#Sets the folder for all XML files, command files, and output files
file_path="sample_xml/"

#Sets the temporary file where the output of the Zork game will be stored before being compared to a predetermined output
temp_output_file="zork.txt"

#Sets the file extension for the XML files
xml_file_extension=".xml"

#Sets the file extension for the command files
command_file_extension=".txt"

#Sets the file extension for the output files
output_file_extension=".out"

#Sets a default value for the XML file
xml_file=""

#Sets i to be 1 (pointing to the first argument) and j to be the number of arguments
i="1"
j=$#

#Loops through all of the command line arguments
while [ $i -le $j ]; do
    #If statement is true if we are looking at the first argument, which is the XML file name
    if [ $i -eq "1" ]; then
        #Gets the XML file name without the file extension
        xml_file="${1%%.*}"

        #Prints a title for the output
        printf "Testing ${xml_file}:\n"

        #If statement is true if there is only one command line argument, meaning that the XML file name and the command file name are the same
        if [ $j -eq "1" ]; then
            #Loops through all command files with the same beginning of the file name
            for test_case_full in "${file_path}${xml_file}"*"${command_file_extension}"; do
                #Gets the command file name without the full path or file extension
                test_case="${test_case_full##*/}"
                test_case="${test_case%%.*}"

                #Gets the number of columns to push the pass/fail message over based on the command file name size
                col=$(($(tput cols) - ${#test_case}))

                #Executes the Zork game with the XML file and command file passed on the command line
                ./ZorkProject $file_path$xml_file$xml_file_extension $file_path$test_case$command_file_extension >$temp_output_file

                #If statement is true if the temporary output file and the predetermined output file are the same
                if cmp -s $temp_output_file $file_path$test_case$output_file_extension; then
                    #Prints that the command file test case passed
                    printf "%s%s%*s%s\n" "${test_case}" "$GREEN" $col "[PASS]" "$NORMAL"
                else
                    #Prints that the command file test case failed
                    printf "%s%s%*s%s\n" "${test_case}" "$RED" $col "[FAIL]" "$NORMAL"
                    diff $temp_output_file $file_path$test_case$output_file_extension
                fi

                #Removes the temporary output file
                rm $temp_output_file
            done
        fi
    else
        #Gets the command file name without the file extension
        command_file="${1%%.*}"

        #Loops through all command files with the same beginning of the file name
        for test_case_full in "${file_path}${command_file}"*"${command_file_extension}"; do
            #Gets the command file name without the full path or file extension
            test_case="${test_case_full##*/}"
            test_case="${test_case%%.*}"

            #Gets the number of columns to push the pass/fail message over based on the command file name size
            col=$(($(tput cols) - ${#test_case}))

            #Executes the Zork game with the XML file and command file passed on the command line
            ./ZorkProject $file_path$xml_file$xml_file_extension $file_path$test_case$command_file_extension >$temp_output_file

            #If statement is true if the temporary output file and the predetermined output file are the same
            if cmp -s $temp_output_file $file_path$test_case$output_file_extension; then
                #Prints that the command file test case passed
                printf "%s%s%*s%s\n" "${test_case}" "$GREEN" $col "[PASS]" "$NORMAL"
            else
                #Prints that the command file test case failed
                printf "%s%s%*s%s\n" "${test_case}" "$RED" $col "[FAIL]" "$NORMAL"
                diff $temp_output_file $file_path$test_case$output_file_extension
            fi

            #Removes the temporary output file
            rm $temp_output_file
        done
    fi

    #Increments the i variable (the current command line argument we are looking at)
    i=$((i + 1))

    #Shifts the command line arguments to the left by one position so that the next argument is in position 1
    shift 1
done
cmake_minimum_required(VERSION 3.9)

include (CMakeParseArguments)

# Determine the absolute path of a file
function(estp_realpath filename output_var_name)
	get_filename_component(filename_abs ${filename} ABSOLUTE)
	set(${output_var_name} ${filename_abs} PARENT_SCOPE)
endfunction()

# Determine just the path portion of a file
function(estp_dirname filename output_var_name)
	get_filename_component(dirname ${filename} DIRECTORY)
	set(${output_var_name} ${dirname} PARENT_SCOPE)
endfunction()

# More convenient function for parsing arguments
function(estp_parse_args input_text)
	# First we need to parse our optional arguments into three lists, only one of which we care about
	set(options )
    set(oneValueArgs )
    set(multiValueArgs FLAG_ARGS, VALUE_ARGS, LIST_ARGS, REQUIRED_ARGS)
    cmake_parse_arguments(NAMES_OF "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if("${NAMES_OF_UNPARSED_ARGUMENTS}")
        message(FATAL_ERROR "Failed to parse arguments: ${NAMES_OF_UNPARSED_ARGUMENTS}")
    endif()

    # Clear any existing variables in parent scope
	set(output_prefix, "ARG")
    foreach(argname ${NAMES_OF_FLAG_ARGS} ${NAMES_OF_VALUE_ARGS} ${NAMES_OF_LIST_ARGS})
        unset("${output_prefix}_${argname}" PARENT_SCOPE)
    endforeach()

    # Now parse input text looking for specified arguments
    cmake_parse_arguments(
    	${output_prefix}
    	"${NAMES_OF_FLAG_ARGS}"
    	"${NAMES_OF_VALUE_ARGS}"
    	"${NAMES_OF_LIST_ARGS}"
    	"${input_text}"
    	)

	set(unparsed_args_var_name "${output_prefix}_UNPARSED_ARGUMENTS")
    if("${${unparsed_args_var_name}}")
        message(FATAL_ERROR "Failed to parse arguments: ${${unparsed_args_var_name}}")
    endif()

    # Check all required arguments were passed
    foreach (required_arg ${NAMES_OF_REQUIRED_ARGS})
        if(NOT ${output_prefix}_${required_arg})
            message(FATAL_ERROR "Required argument not provided: ${required_arg}")
        endif()
    endforeach()

    # Set argument variables in parent scope
    foreach(argname ${NAMES_OF_FLAG_ARGS} ${NAMES_OF_VALUE_ARGS} ${NAMES_OF_LIST_ARGS})
        set(varname "${output_prefix}_${arg_name}")
        set(${varname} ${${varname}} PARENT_SCOPE)
    endforeach()
endfunction()



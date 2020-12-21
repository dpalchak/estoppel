#!/bin/bash

JLINK_DEVICE="$1"
JLINK_ACTION="$2"
shift 2

SYSTEM_NAME="$(uname -s | tr '[:upper:]' '[:lower:]')"

SCRIPT_PATH="$( cd $(dirname "${BASH_SOURCE[0]}") >/dev/null 2>&1 ; pwd -P )"
JLINK_TOOLS_PATH="${SCRIPT_PATH}/../../third_party/segger/jlink/${SYSTEM_NAME}/latest"

JLINK_SPEED=4000
JLINK_INTERFACE="swd"

JLINK_COMMANDER="${JLINK_TOOLS_PATH}/JLinkExe "\
"-Device ${JLINK_DEVICE} -If ${JLINK_INTERFACE} -Speed ${JLINK_SPEED} -AutoConnect 1"

JLINK_GDBSERVER="${JLINK_TOOLS_PATH}/JLinkGDBServer "\
"-select USB -device ${JLINK_DEVICE} -endian little "\
"-if ${JLINK_INTERFACE} -speed ${JLINK_SPEED} -ir -noLocalhostOnly -nohalt"

JLINK_RTTCLIENT="${JLINK_TOOLS_PATH}/JLinkRTTClientExe "

JLINK_HALT_CMD="h \n"
JLINK_GO_CMD="g \n"
JLINK_RESET_CMD="r \n"
JLINK_QUIT_CMD="q \n"
JLINK_ERASE_CMD="erase \n"

show_help(){
    echo "Usage: $(basename "${BASH_SOURCE[0]}") <DEVICE> <ACTION> [...]"
    echo ""
    echo "Actions:"
    echo "    info              Show J-Link tool help"
    echo "    reset             Reset the target. Target will automatically resume."
    echo "    erase             Erase the flash memory"
    echo "    flash <HEXFILE>    Load a file into flash. Target will automatically reset and resume."
    echo "    gdbserver         Start a GDB server in the background"
    echo "    killserver        Kill all background GDB servers"
    echo "    rttclient         Start an RTT client"
    echo ""
}

cmd_info(){
    ${JLINK_COMMANDER} --help
}
cmd_reset(){
    printf "$JLINK_HALT_CMD $JLINK_RESET_CMD $JLINK_QUIT_CMD" | $JLINK_COMMANDER
}

cmd_erase(){
    printf "$JLINK_HALT_CMD $JLINK_ERASE_CMD $JLINK_QUIT_CMD" | $JLINK_COMMANDER
}

cmd_flash(){
    HEX_FILE=$1
    JLINK_LOAD_CMD="loadfile ${HEX_FILE} \n"
    printf "$JLINK_HALT_CMD $JLINK_LOAD_CMD $JLINK_RESET_CMD $JLINK_QUIT_CMD" | \
        $JLINK_COMMANDER
}

# Synonym for `flash`
cmd_load() {
    cmd_flash $@
}

cmd_gdbserver(){
    $JLINK_GDBSERVER &
}

cmd_killserver(){
    killall JLinkGDBServer
}

cmd_rttclient(){
    $JLINK_RTTCLIENT
}

case $JLINK_DEVICE in
    "")
        show_help
        ;;
    "help")
        show_help
        ;;
    *)
        cmd_${JLINK_ACTION} $@
        if [ $? = 127 ]; then
            echo "Error: unknown action '${JLINK_ACTION}' " >&2
            echo ""
            show_help
            exit 1
        fi
        ;;
esac

  
#!/bin/bash -e

export PULPRT_TARGET=pulp
export PULPRUN_TARGET=pulp

if [  -n "${ZSH_VERSION:-}" ]; then 
    DIR="$(readlink -f -- "${(%):-%x}")"
    scriptDir="$(dirname $DIR)"
else

    scriptDir="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"

fi

source $scriptDir/../../common.sh

export PULPRUN_PLATFORM=fpga

#Virtex7 uses 50MHz SoC Frequency
export PULPRT_CONFIG_CFLAGS='-DARCHI_FPGA_FREQUENCY=50000000'

export io=uart
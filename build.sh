#!/bin/sh

function print_help() {
cat << EOF
Usage: ./build.sh [options]

Options:
  -h, --help                  Display this help message and exit.
  -c[C], --compiler[=C]       Specify the compiler to use. 
                              Possible values for C: 
                                gcc   - GNU Compiler Collection.
                                clang - LLVM Clang Compiler.
  -d, --debug                 Set the build type to Debug
  -s[S], --sanitizer[=S]      Enable sanitizers for detecting runtime issues.
                              Possible values for S:
                                address - Enable Address Sanitizer
                                ub     - Enable Undefined Behavior Sanitizer
EOF
}

DEBUG_MODE=false
COMPILER=""
SANITIZER=""

if [[ -z "$1" ]]; then
    echo "Error: no parameters. Use --help for help"
    exit 1
fi

while [[ -n "$1" ]]; do
    case "$1" in
        -h|--help)
            print_help
            exit 0
            ;;
        -c)
            if [[ -n "$2" && "$2" != -* ]]; then
                COMPILER="$2"
                echo $COMPILER
                shift 2
            else
                echo "Error: option --COMPILER requires arguments."
                exit 1
            fi
            ;;
        --compiler=*)
            COMPILER="${1#*=}"
            echo $COMPILER
            shift
            ;;
        -d|--debug)
            DEBUG_MODE=true
            shift
            ;;
        -s)
            if [[ -n "$2" && "$2" != -* ]]; then
                SANITIZER="$2"
                echo $SANITIZER
                shift 2
            else
                echo "Error: option --SANITIZER requires arguments."
                exit 1
            fi
            ;;
        --sanitizer=*)
            SANITIZER="${1#*=}"
            echo $SANITIZER
            shift
            ;;
        --)
            shift
            echo "End of options"
            break
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

if { $DEBUG_MODE || [[ -n "$SANITIZER" ]]; } && [[ -z "$COMPILER" ]]; then
  echo "Error: option --compiler is necessarily for others."
  exit 1
fi

mkdir -p build
cd build

BUILD_TYPE="Release"
if $DEBUG_MODE; then
  BUILDE_TYPE="Debug"
fi

CMAKE_ARGS=(
    "-DCMAKE_BUILD_TYPE=$BUILD_TYPE"
    "-DCOMPILER=$COMPILER"
)

if [[ $DEBUG_MODE == true ]]; then
    CMAKE_ARGS+=("-DENABLE_DEBUG=ON")
fi

CMAKE_ARGS+=(
    "-DENABLE_SANITIZER_ADDRESS=$( [[ $SANITIZER == "address" ]] && echo ON || echo OFF )"
    "-DENABLE_SANITIZER_UB=$( [[ $SANITIZER == "ub" ]] && echo ON || echo OFF )"
)

cmake "${CMAKE_ARGS[@]}" ..
make

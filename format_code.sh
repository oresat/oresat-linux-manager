# Format all of OLM source code
# NOTE: src/CANopenNode and src/socketCAN_mod should not be formatted

DIRS="
src
src/boards/gps
src/boards/dxwifi
src/boards/generic
src/boards/star_tracker
src/boards/cirrus_flux_camera
src/common
src/core
src/daemons
src/manitory_apps
"

for val in $DIRS; do
    clang-format -i $val/*.[ch]
    echo "formatting $val/"
done

echo 'done'

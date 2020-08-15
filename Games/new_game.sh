#!/usr/bin/env bash
# 8bpl

file_exist() {
    if [[ -e "$1" ]]; then
        echo "[e] A project already exists!."
        return 1
    fi

    return 0
}

if_file_exist_exit() {
    file_exist "$NAME_PROJECT"

    if [[ $? -eq 1 ]]; then
        exit
    fi
}

function build_libs()
{
	echo "[i] Build/update 8bpl if necesary ..."

	cd ../Libraries/8bpl
	./build.sh || exit
	cd -

	echo "[i] Build/update Tilengine if necesary ..."

	cd ../Libraries/Tilengine
	./build.sh || exit
	cd -
}

function help()
{
	echo "Usage: $0 <name project>"
	echo "Usage: $0 --build-libs"
	echo
}
######################################################

if [[ $# -eq 1 ]]; then
	if [[ "$1" == "--build-libs" ]]; then
		build_all
		exit
	fi
	if [[ "$1" == "--help" ]]; then
		help
		exit
	fi
    NAME_PROJECT="$1"
else
    echo "[i] The name of the new project is needed."
    while [ 1 ]
    do
        echo -n "Name of proyect:"
        read NAME_PROJECT
        if [[ ! -z "$NAME_PROJECT" ]]; then
            file_exist "$NAME_PROJECT"
            if [[ $? -eq 0 ]]; then
                break
            fi
        fi
    done
fi

if_file_exist_exit

while [ 1 ]
do
    echo -n "Title of the game (eg. PacTux):"
    read GAME_NAME
    if [[ ! -z "$GAME_NAME" ]]; then
        while [ 1 ]
        do
            echo -n "Executable name:"
            read GAME_EXE
            if [[ ! -z "$GAME_EXE" ]]; then
                break
            fi
        done
        break
    fi
done

echo "[i] Copying templates ..."

mkdir -p "$NAME_PROJECT"/{data,include,libs,src}

cp templates/Makefile.template "$NAME_PROJECT"/Makefile
cp templates/gitignore.template "$NAME_PROJECT"/.gitignore
cp templates/config.h.in.template "$NAME_PROJECT"/include/config.h.in
cp templates/main.c.template "$NAME_PROJECT"/src/main.c
cp -R templates/data/* "$NAME_PROJECT"/data/

GAME_VER=0.1

sed -e "s/@GAME_NAME@/$GAME_NAME/g" -e "s/@GAME_VER@/$GAME_VER/g" -e "s/@GAME_EXE@/$GAME_EXE/g" -i "$NAME_PROJECT"/Makefile
sed -e "s/@GAME_EXE@/$GAME_EXE/g" -i "$NAME_PROJECT"/.gitignore

build_libs

cd "$NAME_PROJECT" || exit

git init && git add -f * *.* #&& git commit -a -m 'First commit.' #optional: --no-gpg-sign

echo "**********************"
echo " Done."
echo " Change to directory '$NAME_PROJECT' and run 'make'"
echo "**********************"

exit

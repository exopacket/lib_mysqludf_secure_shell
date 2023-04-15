#!/bin/bash

function prompt {
    while true; do
        read -p "$* [y/n]: " yn
        case $yn in
            [Yy]*) return 0  ;;
            [Nn]*) echo "Aborted" ; return  1 ;;
        esac
    done
}

echo "Compiling the MySQL UDF"
CWD=$(pwd)
rm -rf "${CWD}/build"
mkdir "${CWD}/build"
cd "${CWD}/build" && cmake "${CWD}" && cmake --build "${CWD}/build" && cmake --install "${CWD}/build"

if test $? -ne 0; then
	echo "ERROR: Compilation error"
	exit 1
else
	echo "MySQL UDF compiled successfully"
fi

if [ prompt "The home directory and shell (/bin/rbash) must be set in /etc/passwd. Would you like to set that now?" -eq 0 ]; then
  printf "" > /etc/passwd.new
  while read line; do
    IFS=':' read -ra ADDR <<< "$line"
    if [[ "${ADDR[0]}" = "mysql" ]]; then
            echo "${ADDR[0]}:${ADDR[1]}:${ADDR[2]}:${ADDR[3]}:${ADDR[4]}:/mysql-scripts:/bin/rbash" >> /etc/passwd.new
    else
            echo "$line" >> /etc/passwd.new
    fi
  done < /etc/passwd
  cp /etc/passwd /etc/passwd.old
  mv /etc/passwd.new /etc/passwd
fi

echo -e "\nPlease provide your MySQL root password"

mysql -u root -p mysql < "${CWD}/lib_mysqludf_secure_shell.sql"

if test $? -ne 0; then
	echo "ERROR: unable to install the UDF"
	exit 1
else
	echo "MySQL UDF installed successfully"
fi

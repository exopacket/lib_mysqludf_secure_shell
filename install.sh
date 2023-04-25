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

DISABLE_SECURITY=false;

if prompt "Would you like to disable security features?"; then
  DISABLE_SECURITY=true;
fi

echo "Compiling the MySQL UDF"
CWD=$(pwd)
rm -rf "${CWD}/build"
mkdir "${CWD}/build"
if $DISABLE_SECURITY; then
  cd "${CWD}/build" && cmake "${CWD}" -DSECURE_INSTALL=OFF && cmake --build "${CWD}/build" && cmake --install "${CWD}/build"
else
  cd "${CWD}/build" && cmake "${CWD}" && cmake --build "${CWD}/build" && cmake --install "${CWD}/build"
fi
if test $? -ne 0; then
	echo "ERROR: Compilation error"
	exit 1
else
	echo "MySQL UDF compiled successfully"
fi

if prompt "The home directory for the mysql user must be set in /etc/passwd. Would you like to set that now?"; then
  printf "" > /etc/passwd.new
  while read line; do
    IFS=':' read -ra ADDR <<< "$line"
    if [[ "${ADDR[0]}" = "mysql" ]]; then
            echo "${ADDR[0]}:${ADDR[1]}:${ADDR[2]}:${ADDR[3]}:${ADDR[4]}:/home/mysql-scripts:/${ADDR[6]}" >> /etc/passwd.new
    else
            echo "$line" >> /etc/passwd.new
    fi
  done < /etc/passwd
  mkdir /home/mysql-scripts
  cp /etc/passwd /etc/passwd.old
  mv /etc/passwd.new /etc/passwd
fi

echo -e "\nPlease provide your MySQL root password"

if $DISABLE_SECURITY; then
  mysql -u root -p mysql < "${CWD}/lib_mysqludf_secure_shell_with_run.sql"
else
  mysql -u root -p mysql < "${CWD}/lib_mysqludf_secure_shell.sql"
fi

if test $? -ne 0; then
	echo "ERROR: unable to install the UDF"
	exit 1
else
	echo "MySQL UDF installed successfully"
fi

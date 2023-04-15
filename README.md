# lib_mysqludf_secure_shell

This library will allow mysql to run scripts on your system using a secure restricted shell.
<br><br><strong>Note</strong> If you can't get it working check system log for AppArmor or SELinux denials or switch to the less secure method by uncommenting the return value in the lib_mysqludf_secure_shell to return the `system(...)` function call result.

# Requirements
MySQL `>=8.0`<br>
libmysqlclient-dev `apt-get install default-libmysqlclient-dev`<br>
cmake `>=3.21`<br>


# Installation
 - Change to the source directory
 - run `./install.sh`

# lib_mysqludf_secure_shell

This library will allow mysql to run scripts on your system using a secure restricted shell (recommended/default).<br><br>
There is an option to disable security features which adds the `sys_run` function to MySQL and removes the use of `/bin/rbash` in Linux. This new function basically just lets you do what you want & takes two arguments: the executable and the arguments. By default, you will have one function: `sys_shell`. `sys_shell` will run any shell command. All functions return the exit status. Keep in mind that by using the restricted shell and .bash_profile you'll need to have your shell scripts installed in the mysql user's home directory (`/home/mysql-client` if using the install script) <br><br>  
<strong>Note</strong> If you can't get it working check system log for AppArmor or SELinux denials or switch to the less secure method by uncommenting the return value in the `lib_mysqludf_secure_shell.cc` file to return the `system(...)` function call result.<br><br>
This is completely untested on Windows and Fedora based distros. The code in general should work fine, but there may need to be minor modifications made to get it working for your use case.

# Requirements
MySQL `>=8.0`<br>
libmysqlclient-dev `apt-get install default-libmysqlclient-dev`<br>
cmake `>=3.21`<br>


# Installation
 - Change to the source directory
 - run `./install.sh`

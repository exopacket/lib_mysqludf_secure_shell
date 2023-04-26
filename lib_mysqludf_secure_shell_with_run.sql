DROP FUNCTION IF EXISTS sys_shell;
DROP FUNCTION IF EXISTS sys_run;

CREATE FUNCTION sys_shell RETURNS int SONAME 'lib_mysqludf_secure_shell.so';
CREATE FUNCTION sys_run RETURNS int SONAME 'lib_mysqludf_secure_shell.so';


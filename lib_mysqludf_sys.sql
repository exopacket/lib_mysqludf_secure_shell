DROP FUNCTION IF EXISTS sys_exec;

CREATE FUNCTION sys_exec RETURNS int SONAME 'lib_mysqludf_exec.so';

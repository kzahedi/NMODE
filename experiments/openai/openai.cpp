#include <Python.h>

int
main(int argc, char *argv[])
{
  Py_SetProgramName((wchar_t*)"openai");  /* optional but recommended */
  Py_Initialize();
  PyRun_SimpleString("exec(open('/Users/zahedi/projects/NMODE/experiments/openai/openai.py').read())");
  Py_Finalize();
  return 0;
}

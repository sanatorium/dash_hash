#include <Python.h>

#include "sanity.h"

static PyObject *sanity_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    sanity_hash((char *)PyBytes_AsString((PyObject*) input), (int)PyBytes_Size((PyObject*) input), output);
#else
    sanity_hash((char *)PyString_AsString((PyObject*) input), (int)PyString_Size((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef SanityMethods[] = {
    { "getPoWHash", sanity_getpowhash, METH_VARARGS, "Returns the proof of work hash using sanity hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef SanityModule = {
    PyModuleDef_HEAD_INIT,
    "sanity_hash",
    "...",
    -1,
    SanityMethods
};

PyMODINIT_FUNC PyInit_sanity_hash(void) {
    return PyModule_Create(&SanityModule);
}

#else

PyMODINIT_FUNC initsanity_hash(void) {
    (void) Py_InitModule("sanity_hash", SanityMethods);
}
#endif

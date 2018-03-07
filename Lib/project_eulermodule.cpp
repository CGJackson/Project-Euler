#include <Python.h>
#include <vector>
#include <limits>

#include "Project_Euler.h"

static PyObject *integer_sqrt(PyObject* self, PyObject *args){
    long long n;

    if(!PyArg_ParseTuple(args, "L", &n)) return NULL;

    if( n < 0 ){
        PyErr_SetString(PyExc_ValueError,
                        "Cannot take the square root of a negative number");
        return NULL;
    }

    long long sqrt = project_euler::isqrt(n);

    if( sqrt < 0){
        Py_RETURN_NONE;
    }
    else{
        return PyLong_FromLong(sqrt);
    }
}


// Sets up the python module 

static PyMethodDef project_eulerMethods[] = {
    {"integer_sqrt", integer_sqrt, METH_VARARGS, "Finds the integer square root of an integer or None is the number is not square"},
    //{primes_to_n, primes_to_n, METH_VARARGS, returns a list of the prime numbers up to a given integer, n"}
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef project_eulermodule = {
    PyModuleDef_HEAD_INIT,
    "project_euler",
    "A library of helper functions for Project Euler problems",
    -1,
    project_eulerMethods
};

PyMODINIT_FUNC PyInit_project_euler(void){
    return PyModule_Create(&project_eulermodule);
}
                                                

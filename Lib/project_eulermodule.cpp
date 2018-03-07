#include <Python.h>
#include <vector>
#include <limits>

#include "Project_Euler.h"

//Helper Functions

// Creates a python list from a vector. The python objects in the list are
// created from there Cpp counterparts by the function c_to_py_converter
template<class T>
static PyObject* PyList_FromVector(const std::vector<T> &vec,
                                      PyObject* (*c_to_py_converter)(T)
                                     ){
    PyObject* list = Py_BuildValue("[]");

    for(auto &e: vec){
        PyObject *py_e = c_to_py_converter(e);
        if(py_e == NULL){
            Py_DECREF(list);
            return NULL;
        }

        int failed_to_add = PyList_Append(list, py_e);
        Py_DECREF(py_e);
        if(failed_to_add){
            Py_DECREF(list);
            return NULL;
        }
    }
    return list;
}

// C++ functions called by module methods

static PyObject *primes_to_n(PyObject* self, PyObject* args){
    Py_ssize_t n;
    
    if(!PyArg_ParseTuple(args, "n", &n)) return NULL;

    if( n < 0 ){
        PyErr_SetString(PyExc_ValueError, "Cannot find primes less than 0");
        return NULL;
    }

    auto primes = project_euler::primes_to_n(n);

    return PyList_FromVector(primes, PyLong_FromSsize_t);
}

static PyObject *integer_sqrt(PyObject* self, PyObject* args){
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
    {"integer_sqrt", integer_sqrt, METH_VARARGS,
    "Finds the integer square root of an integer or None is the number is not square"},
    {"primes_to_n", primes_to_n, METH_VARARGS,
    "returns a list of the prime numbers up to a given integer, n"},
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
                                                

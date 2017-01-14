/**
* @file Constants.cpp
* @brief Provides contst expresions used in application.
*/

#include "Constants.h"


/*
* Id of main core.
*/
const long Constants::ROOT_CORE = 0;
/*
* Text describing upwind explicit schema.
*/
const std::string Constants::UPWIND_EXPLICIT = "upwind-explicit";
/*
* Text describing upwind implicit schema.
*/
const std::string Constants::UPWIND_IMPLICIT = "upwind-implicit";
/*
* Text describing Crank-Nicolson schema.
*/
const std::string Constants::CRANK_NICOLSON = "crank-nicolson";
/*
* Text describing parallel upwind implicit schema.
*/
const std::string Constants::UPWIND_EXPLICIT_PARALLEL = "upwind-explicit-parallel";
/*
* Text describing parallel upwind implicit schema.
*/
const std::string Constants::UPWIND_IMPLICIT_PARALLEL = "upwind-implicit-parallel";
/*
* Text describing parallel Crank-Nisolson schema.
*/
const std::string Constants::CRANK_NICOLSON_PARALLEL = "crank-nicolson-parallel";

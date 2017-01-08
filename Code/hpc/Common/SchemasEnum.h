/**
 * @file SchemasEnum.h
 * @brief Declaration of enumeration for schemes.
 */
#ifndef __H_SCHEMAS_ENUM
#define __H_SCHEMAS_ENUM

/**
 * @brief Enumeration for schemas used in disretization process.
 * Stores information about schema that should be applied.
 * @author Mateusz Gasior
 */
enum SchemasEnum
{
	UPWIND_EXPLICIT,
	UPWIND_IMPLICIT,
	CRANK_NICLOSON
};

#endif


#ifndef INFO_H
#define INFO_H

/*!
 * \file info.hpp
 * \brief Header containing templates for variable and function descriptors
 * \author Tahiraj Arian
 * \author Leroy Antoine
 * \version 0.1
 */

#include <vector>

/*! \class Info
 * \brief Class describing a viariable
 *
 * This class describes a variable, hence it contains a type field (type_),
 * a location field (location_) and an unsigned ield (ssaptr_) which correponds
 * to the register (llvm) containing a pointer to address containing the
 * variable on the stack.
 *
 * \tparam LocationT: type of the location variable.
 * \tparam TypeT: type of the type variable.
 */
template <class LocationT, class TypeT> class Info
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the Info class.
     *
     * \param location: The location of variable.
     * \param type: The type of the variable.
     */
    Info(LocationT &location, TypeT &type) : location_(location), type_(type) {}

    /*!
     * \brief Destructor
     *
     * Destructor of the Info class.
     */
    ~Info(void) {}

    /*!
     * \brief Getter for the ssaptr.
     *
     * Getter for ssaptr of the variable.
     *
     * \return ssaptr_: An unsigned corresponding to the ssaptr of the variable.
     * (unsigned).
     */
    unsigned int &ssaptr(void) { return this->ssaptr_; }

    /*!
     * \brief Getter for the location of the variable (in the source file).
     *
     * Getter for location of the variable.
     *
     * \return location_: A LocationT& corresponding to position of the
     * variable. (LocationT&).
     */
    LocationT &location(void) { return this->location_; }

    /*!
     * \brief Getter for type of the variable.
     *
     * Getter for type of the variable.
     *
     * \return type_: A TypeT& corresponding to type of the variable. (TypeT&).
     */
    TypeT &type(void) { return this->type_; }

  private:
    unsigned int ssaptr_ = 0; /*!< llvm register number of the stack allocation
                                 of this variable. */
    LocationT
        &location_; /*!< Location of this variable in the VSOP input file. */
    TypeT &type_;   /*!< Type of this variable. */
};

/*! \class FunctionInfo
 * \brief Class describing a function.
 *
 * This class describes a function. It inherits from class Info and also
 * contains fields for the method's name (name_), formals (formals_) and
 * a key corresponding to the class this methods belongs to.
 *
 * \tparam LocationT: type of the location variable.
 * \tparam TypeT: type of the type variable.
 * \tparam NameT: type of the name variable.
 * \tparam FormalT: type of the formals variable.
 * \tparam ClassKeT: type of the key of the class this method belongs to.
 */
template <class LocationT, class TypeT, class NameT, class FormalT,
          class ClassKeyT>
class FunctionInfo : public Info<LocationT, TypeT>
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the FunctionInfo class.
     *
     * \param location: The location of method.
     * \param type: The return type of the method.
     * \param name: The name of the method.
     * \param formals: The formals of the method.
     * \param classKey: Key of the class this method belongs to.
     */
    FunctionInfo(LocationT &location, TypeT &type, TypeT &name,
                 FormalT &formals, ClassKeyT &classKey)
        : Info<LocationT, TypeT>(location, type), name_(name),
          formals_(formals), classKey_(classKey)
    {
    }

    /*!
     * \brief Destructor
     *
     * Destructor of the FunctionInfo class.
     */
    ~FunctionInfo(void) {}

    /*!
     * \brief Getter for the name field.
     *
     * Getter for the field describing the name of the method.
     *
     * \return formals_: A NameT representing the name of the method. (NameT).
     */
    NameT &name(void) { return this->name_; }

    /*!
     * \brief Getter for the formals variable.
     *
     * Getter for the field describing the formals.
     *
     * \return formals_: A FormalT representing the formals. (FormalT).
     */
    FormalT &formals(void) { return this->formals_; }

    /*!
     * \brief Getter for the key class.
     *
     * Getter for the key of the class this method belongs to.
     *
     * \return classKey_: the key of the described class. (ClassKeyT&).
     */
    ClassKeyT &classKey(void) { return this->classKey_; }

  private:
    NameT &name_;         /*!< Name of the method.*/
    FormalT &formals_;    /*!< Formals of the method.*/
    ClassKeyT &classKey_; /*!< Class whose this methods belongs to (useful for
                             dynamic dispatch).*/
};

#endif
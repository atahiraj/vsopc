

#ifndef VARIABLE_TABLE_H
#define VARIABLE_TABLE_H

/*!
 * \file tableTree.hpp
 * \brief Header containing templates for the variable and function tables.
 * \author Tahiraj Arian
 * \author Leroy Antoine
 * \version 0.1
 */

#include <cstddef>
#include <unordered_map>
#include <vector>

/*! \class Table
 * \brief Template class for variable and function tables.
 *
 * This template class implements variable and function tables. It uses
 * a hashtable to associate keys to values. Note that only the reference to
 * the value is stored, which is not the best practice but has shown to be
 * useful in some cases.
 *
 * \tparam KeyT: type of the entries' keys.
 * \tparam ValueT: type of the entries' values.
 */
template <class KeyT, class ValueT> class Table
{
    typedef Table<KeyT, ValueT> TableT;

  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the Table class that sets its parent.
     *
     * \param parent: the parent table.
     */
    Table(TableT &parent) : parent_(parent) {}

    /*!
     * \brief Constructor
     *
     * Constructor of the Table class for the root table.
     */
    Table(void) : Table(*this) {}

    /*!
     * \brief Destructor
     *
     * Destructor of the Table class.
     */
    ~Table(void) {}

    /*!
     * \brief Checks whether the table contains an entry.
     *
     * Returns whether or not a given key corresponds to a value in the table.
     *
     * \param key: key query.
     *
     * \return true if the table contains a value with the query as its key
     * and false otherwise.
     */
    bool contains(const KeyT &key)
    {
        return this->table_.find(key) != this->table_.end();
    }

    /*!
     * \brief Inserts an entry in the table.
     *
     * Given a new entry, inserts in the hashtables.
     *
     * \param key: the entry's key.
     * \param value: the entry's value.
     */
    void insert(KeyT &key, ValueT &value)
    {
        this->table_[key] = &value;
        this->keys_.push_back(&key);
    }

    /*!
     * \brief Getter for a value.
     *
     * Given a key, returns the corresponding value (if any). Note that
     * this method is updwards recursive, which is done in order to handle
     * for inheritance and nested scopes.
     *
     * \param key: key query.
     *
     * \return the value associated to the parameter key or nullptr if there
     * is none.
     */
    ValueT *value(const KeyT &key)
    {
        if (!this->contains(key))
        {
            if (&this->parent_ != this)
                return this->parent_.value(key);

            return nullptr;
        }

        return this->table_[key];
    }

    /*!
     * \brief Getter for the parent table.
     *
     * Getter for the parent table.
     *
     *
     * \return parent_: A reference to this table's parent.
     */
    TableT &parent(void) { return this->parent_; }

    /*!
     * \brief Getter for the keys.
     *
     * Getter for the keys. Note that this returns a vector of pointers to
     * the keys used when the elements were added to the table (this has
     * proved to be useful in some contexts).
     *
     *
     * \return keys_: A vector of KeyT* pointers pointing to the keys used
     * when the elements were added.
     */
    std::vector<KeyT *> &keys(void) { return this->keys_; }

    /*!
     * \brief Recursive getter for the keys.
     *
     * Same as keys() but concatenates the keys of this table's parent
     * tables. This table's keys are inserted at the end of the vector.
     *
     *
     * \return keys_: A vector of KeyT* pointers pointing to the keys used
     * when the elements were added.
     */
    void allKeys(std::vector<KeyT *> &keys)
    {
        std::vector<KeyT *> keyBuf = this->keys_;
        keyBuf.insert(std::end(keyBuf), std::begin(keys), std::end(keys));
        keys = keyBuf;
        if (&this->parent_ != this)
            this->parent_.allKeys(keys);
    }

  private:
    TableT &parent_; /*!< Reference to the parent table */
    std::vector<KeyT *> keys_ =
        std::vector<KeyT *>(); /*!< Vector of pointer to the keys that were used
                                  to insert the corresponding elements. */
    std::unordered_map<KeyT, ValueT *> table_ =
        std::unordered_map<KeyT,
                           ValueT *>(); /*!< Hashtable that associates a key to
                                           a pointer to a ValueT object. */
};

/*! \class TableTree
 * \brief Template class for variable and function table trees.
 *
 * This class implements the trees of variable and function tables. The class
 * uses hashtables to associate keys to tables and implements a bunch of methods
 * to manipualte the tree.
 *
 * \tparam ClassKeyT: type of the keys used to associate a class to its variable
 * or function table.
 * \tparam OtherKeyT: type of the keys used to associate a scope to its
 * variable or function. These keys are used to implement scopes within methods,
 * hence they are not used in the case of the function table tree, although they
 * could.
 * \tparam KeyT: type of the tables' entries' keys.
 * \tparam ValueT: type of the tables' entries' values.
 */
template <class ClassKeyT, class OtherKeyT, class KeyT, class ValueT>
class TableTree
{
    typedef Table<KeyT, ValueT> TableT;

  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the TableTree class.
     */
    TableTree(void) {}

    /*!
     * \brief Destructor
     *
     * Destructor of the TableTree class.
     */
    ~TableTree(void)
    {

        for (auto x : this->classKeys_)
            delete this->classScopes_[*x];

        for (auto x : this->otherKeys_)
            delete this->otherScopes_[*x];
    }

    /*!
     * \brief Checks whether the tree contains a table.
     *
     * Returns whether the tree contains a table associated to a given
     * class key or not.
     *
     * \param classKey: class key query.
     *
     * \return true if the table contains a table associated to the query
     class key and false otherwise.
     */
    bool contains(const ClassKeyT &classKey)
    {
        return this->classScopes_.find(classKey) != this->classScopes_.end();
    }

    /*!
     * \brief Checks whether the tree contains a table.
     *
     * Returns whether the tree contains a table associated to a given
     * other key or not.
     *
     * \param otherKey: other key query.
     *
     * \return true if the table contains a table associated to the query
     other key and false otherwise.
     */
    bool contains(const OtherKeyT &otherKey)
    {
        return this->otherScopes_.find(otherKey) != this->otherScopes_.end();
    }

    /*!
     * \brief Inserts a root table.
     *
     * Inserts a root table given a class key.
     *
     * \param rootKey: the class key of the root table to be added.
     *
     * \return a pointer to the inserted root table.
     */
    TableT &insertRoot(ClassKeyT &rootKey)
    {
        TableT &newTable = *new TableT();

        this->classScopes_[rootKey] = &newTable;
        this->classKeys_.push_back(&rootKey);
        return newTable;
    }

    /*!
     * \brief Inserts a child table.
     *
     * Inserts a child table with a corresponding class key as the child
     * of a table that the tree already contains and that is associated
     * to a class key. The insertion fails if there is no table that
     * corresponds to the parent class key.
     *
     * \param classKey: the key of the child table.
     * \param superClassKey: the key of the parent table.
     *
     * \return a pointer to the inserted table if the insertion was
     * successful and nullptr otherwise.
     */
    TableT *insert(ClassKeyT &classKey, const ClassKeyT &superClassKey)
    {
        if (!this->contains(superClassKey))
            return nullptr;

        TableT &newTable = *new TableT(*this->classScopes_[superClassKey]);

        this->classScopes_[classKey] = &newTable;
        this->classKeys_.push_back(&classKey);

        return &newTable;
    }

    /*!
     * \brief Inserts a child table.
     *
     * Inserts a child table with a corresponding other key as the child
     * of a table that the tree already contains and that is associated
     * to a class key. The insertion fails if there is no table that
     * corresponds to the parent class key.
     *
     * \param otherKey: the key of the child table.
     * \param superClassKey: the key of the parent table.
     *
     * \return a pointer to the inserted table if the insertion was
     * successful and nullptr otherwise.
     */
    TableT *insert(OtherKeyT &otherKey, const ClassKeyT &classKey)
    {
        if (!this->contains(classKey))
            return nullptr;

        TableT &newTable = *new TableT(*this->classScopes_[classKey]);

        this->otherScopes_[otherKey] = &newTable;
        this->otherKeys_.push_back(&otherKey);

        return &newTable;
    }

    /*!
     * \brief Inserts a child table.
     *
     * Inserts a child table with a corresponding other key as the child
     * of a table that the tree already contains.
     *
     * \param otherKey: the key of the child table.
     * \param table: a reference to the parent table.
     *
     * \return a pointer to the inserted table.
     */
    TableT *insert(OtherKeyT &otherKey, TableT &table)
    {
        TableT &newTable = *new TableT(table);

        this->otherScopes_[otherKey] = &newTable;
        this->otherKeys_.push_back(&otherKey);

        return &newTable;
    }

    /*!
     * \brief Getter for a table.
     *
     * Getter for a table given a class key.
     *
     * \param classKey: the class key query.
     *
     * \return a pointer to the corresponding table if there is one or
     * nullptr is there is none.
     */
    TableT *table(const ClassKeyT &classKey)
    {
        if (!this->contains(classKey))
            return nullptr;

        return this->classScopes_[classKey];
    }

    /*!
     * \brief Getter for a table.
     *
     * Getter for a table given a other key.
     *
     * \param classKey: the other key query.
     *
     * \return a pointer to the corresponding table if there is one or
     * nullptr is there is none.
     */
    TableT *table(const OtherKeyT &otherKey)
    {
        if (!this->contains(otherKey))
            return nullptr;

        return this->otherScopes_[otherKey];
    }

    /*!
     * \brief Returns all the other keys.
     *
     * Returns a vector containing pointers to all the other keys. Note that
     * this returns a vector of pointers to the keys used when the tables
     * were added to the tree (this has proved to be useful in some
     * contexts).
     *
     *
     * \return a std::vector of pointer to all the other keys of the tree.
     */
    std::vector<OtherKeyT *> &otherKeys(void) { return this->otherKeys_; }

  private:
    std::vector<ClassKeyT *> classKeys_ =
        std::vector<ClassKeyT *>(); /*!< Vector of pointer to the class keys
                                       that were used to insert the
                                       corresponding elements. */
    std::vector<OtherKeyT *> otherKeys_ =
        std::vector<OtherKeyT *>(); /*!< Vector of pointer to the other keys
                                       that were used to insert the
                                       corresponding elements. */
    std::unordered_map<ClassKeyT, TableT *> classScopes_ =
        std::unordered_map<ClassKeyT,
                           TableT *>(); /*!< Hashtable that associates a class
                                           key to a table */
    std::unordered_map<OtherKeyT, TableT *> otherScopes_ =
        std::unordered_map<OtherKeyT,
                           TableT *>(); /*!< Hashtable that associates a other
                                           key to a table */
};

#endif
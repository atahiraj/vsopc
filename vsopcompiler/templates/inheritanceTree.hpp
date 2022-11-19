

#ifndef INHERITANCE_TREE_H
#define INHERITANCE_TREE_H

/*!
 * \file inheritanceTree.hpp
 * \brief Header containing templates for the inheritance tree.
 * \author Tahiraj Arian
 * \author Leroy Antoine
 * \version 0.1
 */

template <class ClassKeyT> class InheritanceNode;

#include <cstddef>
#include <unordered_map>
#include <vector>

/*! \class InheritanceTree
 * \brief Class representing the inheritance tree.
 *
 * This class represents the inheritance tree of the class defined in the input
 * file, it consists in a hashtable of pairs (std::string : InheritanceNode),
 * where an inheritance node represents a single class.
 *
 * \tparam ClassKeyT: type of the keys corresponding to classes.
 */
template <class ClassKeyT> class InheritanceTree
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the InheritanceTree class.
     */
    InheritanceTree() {}

    /*!
     * \brief Destructor
     *
     * Destructor of the InheritanceTree class.
     */
    ~InheritanceTree()
    {
        for (auto x : this->keys_)
            delete this->inheriMap_[*x];
    }

    /*!
     * \brief Checks whether the tree contains a class.
     *
     * Returns whether or not a given key corresponds to a class in the tree.
     *
     * \param key: key query.
     *
     * \return true if the tree contains a class with the query and false
     * otherwise.
     */
    bool contains(const ClassKeyT &key)
    {
        return this->inheriMap_.find(key) != this->inheriMap_.end();
    }

    /*!
     * \brief Inserts a node in the inheritance tree.
     *
     * Inserts a node in the inheritance given a key and the parent's key.
     *
     * \param childKey: the key of the child class to be added.
     * \param parentKey: the key of the parent class.
     */
    void insert(ClassKeyT &childKey, ClassKeyT &parentKey)
    {
        if (!this->contains(parentKey) || this->contains(childKey))
            return;

        this->inheriMap_[childKey] = new InheritanceNode<ClassKeyT>(
            childKey, *this->inheriMap_[parentKey]);
        this->keys_.push_back(&childKey);
    }

    /*!
     * \brief Inserts a root node in the inheritance tree.
     *
     * Inserts a node in the inheritance given a key and the parent's key.
     *
     * \param rootKey: the key of the root class to be added.
     */
    void insertRoot(ClassKeyT &rootKey)
    {
        if (this->contains(rootKey))
            return;

        this->inheriMap_[rootKey] = new InheritanceNode<ClassKeyT>(rootKey);
        this->keys_.push_back(&rootKey);
    }

    /*!
     * \brief Getter for the parent of a class.
     *
     * Getter for the key of the parent given the key of class.
     *
     * \param childKey: the key of the class whose parent's key is requested.
     *
     * \return the key of the parent or nullptr if childKey is not in the tree.
     */
    ClassKeyT *parent(ClassKeyT &childKey)
    {
        if (!this->contains(childKey))
            return nullptr;
        return &this->inheriMap_[childKey]->parent_.key_;
    }

    /*!
     * \brief Returns the common ancestor of 2 classes.
     *
     * Given 2 classes, returns their common ancestor.
     *
     * \param firstKey: key of the first class.
     * \parem secondKey: key of the second class.
     *
     * \return the key of their common ancestor or nullptr if they there is no
     * common ancestor
     */
    ClassKeyT *commonAncestor(ClassKeyT &firstKey, ClassKeyT &secondKey)
    {
        if (!this->contains(firstKey) || !this->contains(secondKey))
            return nullptr;

        this->lastMark_++;
        this->inheriMap_[firstKey]->traverse(this->lastMark_);
        return &this->inheriMap_[secondKey]->traverse(this->lastMark_);
    }

    /*!
     * \brief Returns all the class keys.
     *
     * Returns a vector containing pointers to all the class keys.
     *
     * \return a std::vector of pointer to all the keys of the classes in the
     * tree.
     */
    std::vector<ClassKeyT *> &keys(void) { return this->keys_; }

  private:
    int lastMark_ =
        0; /*!< Last mark used in the traversing of the inheritance tree. */
    std::unordered_map<ClassKeyT, InheritanceNode<ClassKeyT> *> inheriMap_ =
        std::unordered_map<ClassKeyT,
                           InheritanceNode<ClassKeyT>
                               *>(); /*!< Hashtable that associates a class key
                                        to an inheritance node */
    std::vector<ClassKeyT *> keys_ =
        std::vector<ClassKeyT *>(); /*!< Vector of pointer to the class keys
                                       that were used to insert the
                                       corresponding nodes. */
};

/*******************************************************************************
 *                              Class InheritanceNode *
 *******************************************************************************/
/*! \class InheritanceNode
 * \brief Class representing a node of the inheritance tree.
 *
 * This class represents and element of the inheritance node, that is a class.
 * \tparam ClassKeyT: type of the keys corresponding to classes.
 */
template <class ClassKeyT> class InheritanceNode
{
  public:
    /*!
     * \brief Constructor
     *
     * Constructor of the InheritanceNode class that sets its parent.
     *
     * \param parent: the parent Node.
     */
    InheritanceNode(ClassKeyT &key, InheritanceNode<ClassKeyT> &parent)
        : key_(key), parent_(parent)
    {
    }

    /*!
     * \brief Constructor
     *
     * Constructor of the InheritanceNode class for the root node.
     */
    InheritanceNode(ClassKeyT &key) : InheritanceNode(key, *this) {}

    /*!
     * \brief Destructor
     *
     * Destructor of the InheritanceNode class.
     */
    ~InheritanceNode() {}

    /*!
     * \brief Traverses the tree up until a marked node if found.
     *
     * Given an integer, traverses the tree upwards by marking all the nodes
     * up until a marked node if found, in which case that node is returned.
     *
     * \param mark: an integer corresponding to the mark (so that this method
     * is reusable without resetting all the marks of the tree).
     */
    ClassKeyT &traverse(int mark)
    {
        // Common ancestor found
        if (this->mark_ == mark)
            return this->key_;

        // Else go upwards
        this->mark_ = mark;
        if (&this->parent_ != this)
            return this->parent_.traverse(mark);

        // Else return pointer to "Object"
        return this->key_;
    }

  private:
    int mark_ = 0;   /*!< This node's mark (used for the traversing of the
                        inheritance tree). */
    ClassKeyT &key_; /*!< Key of the class this node represents. */
    InheritanceNode<ClassKeyT>
        &parent_; /*!< Reference to the parent node in the inheritance tree. */

    friend class InheritanceTree<ClassKeyT>;
};

#endif
#ifndef DEEPPTR_H
#define DEEPPTR_H

template <class T>
/**
 * @brief The DeepPtr class
 *
 * crea un puntatore profondo, a partire
 * da un puntatore.
 * Permette la la distruzione profonda,
 * la copia profonda e l'assegnazione profonda.
 * Inoltre sono ridefiniti gli operatori * e ->
 */
class DeepPtr{
public:

    typedef T value_type;
    typedef value_type& reference;
    typedef value_type* pointer;
private:
    /** Puntatore privato al tipo value_type */
    pointer p;

public:
    DeepPtr(pointer = nullptr);
    DeepPtr(const DeepPtr&);
    ~DeepPtr();
    DeepPtr& operator=(const DeepPtr&);
    pointer operator->() const;
    reference operator*() const;

};

/**
 * @brief DeepPtr(__q)
 *
 * costruttore che crea una copia profonda
 */
template<class T>
DeepPtr<T>::DeepPtr(pointer __q): p(__q!=nullptr?__q->clone():nullptr){}

/**
 * @brief DeepPtr(__deep)
 *
 * copia grazie alla clonazione polimorfa in value_type
 */
template<class T>
DeepPtr<T>::DeepPtr(const DeepPtr& __deep): p(__deep.p!=nullptr?(__deep.p)->clone():nullptr){}

/**
 * @brief ~DeepPtr()
 *
 * distruzione polimorfa grazie al distruttore virtuale in value_type
 */
template<class T>
DeepPtr<T>::~DeepPtr(){
    if(p)
        delete p;
}

/**
 * @brief operator=()
 *
 * ridefinizione del costruttore di assegnazione con clonazione polimorfa
 */
template<class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr& __deep){
    if(this!=&__deep){
        if(p) delete p;
        p = (__deep.p!=nullptr?(__deep.p)->clone():nullptr);
    }
    return *this;    
}

/**
 * @brief operator->()
 *
 * ridefinizione dell'operatore freccia, in modo che ritorni il puntatore a value_type
 */
template<class T>
typename DeepPtr<T>::pointer DeepPtr<T>::operator->() const{
    return p;
}

/**
 * @brief operator*()
 *
 * ridefinzione dell'operatore di dereferenziazione in modo che ritorni un riferimento di value_type
 */
template<class T>
typename DeepPtr<T>::reference DeepPtr<T>::operator*() const{
    return *p;
}

#endif // DEEPPTR_H

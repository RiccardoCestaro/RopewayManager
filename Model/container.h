#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <limits.h>
#include <algorithm>
#include <stdexcept>

template <class T>
/**
 * @brief The Container class
 *
 * gestisce un vettore di oggetti,
 * molto simile a std::vector
 */
class Container{

public:

    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef int difference_type;
    typedef unsigned size_type;
    class const_iterator;
    class iterator;

private:

    /** Campi dati */
    pointer P;
    static size_type _max_size;
    static std::string _length_exceeded;
    size_type _capacity;
    size_type _size;
    /** Metodo resize */
    pointer resize(size_type,size_type) const;
    /** Metodo destroy */
    static void destroy(pointer);

public:

    /** Costruttori */
    Container(size_type=1,size_type=0);
    Container(size_type,const_reference);
    /** Construttore di copia profondo */
    Container(const Container&);
    /** Assegnazione profonda */
    Container& operator=(const Container&);
    /** Distruzione profonda */
    ~Container();
    /** sostituisce un vettore con gli oggetti da parametro */
    void assign(size_type,const_reference);
    void assign(iterator,iterator);
    void assign(const_iterator,const_iterator);
    /** metodi begin e end di iteratori*/
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    /** Ritorna la dimensione massima del container */
    static size_type max_size();
    /** Ritorna la size del container */
    size_type size() const;
    /** Modifica la size del container */
    void resize(size_type) const;
    /** Imposta _capacity = _size */
    void shrink_to_fit();
    /** Ritorna la capacity del container */
    size_type capacity() const;
    /** Ritorna true se il container e' vuoto */
    bool empty() const;
    /** Ridefinizione di [] */
    reference operator[](size_type);
    const_reference operator[](size_type) const;
    /** Accesso sicuro all'elemento del container */
    reference at(size_type);
    const_reference at(size_type) const;
    /** elemento in testa */
    reference front();
    const_reference front() const;
    /** elemento in coda */
    reference back();
    const_reference back() const;
    /** aggiunge un elemento in coda */
    void push_back(const_reference);
    /** toglie un elemento in coda */
    void pop_back();
    /** inserisce un elemento in una posizione indicata */
    iterator insert(iterator,const_reference);
    void insert(iterator,size_type,const_reference);
    /** elimina un elemento in una posizione indicata*/
    iterator erase(iterator);
    iterator erase(iterator,iterator,bool=false);
    /** rimuove la prima occorrenza dell'elemento */
    bool erase(const_reference);
    /** rimuove tutte le occorrenze*/
    bool eraseAll(const_reference);
    /** pulisce il container */
    void clear();
    /** ritorna la posizione iterator di un elemento */
    iterator search(const_reference);
    const_iterator search(const_reference) const;
    /** ritorna la posizione size_type di un elemento */
    size_type indexOf(const_reference) const;
    /** operatori di confronto */
    bool operator==(const Container&) const;
    bool operator<(const Container&) const;
    bool operator>(const Container&) const;
    bool operator<=(const Container&) const;
    bool operator>=(const Container&) const;
    class iterator{
        friend class Container;
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef iterator self_type;
        typedef T value_type;
        typedef value_type& reference;
        typedef value_type* pointer;
        typedef int difference_type;
    private:
        pointer I;
        iterator(pointer =0);
    public:
        operator void*() const;
        reference operator*() const;
        reference operator[](unsigned) const;
        pointer operator->() const;
        iterator& operator+=(int);
        iterator& operator+=(const const_iterator&);
        iterator& operator-=(int);
        iterator& operator-=(const const_iterator&);
        iterator operator+(int) const;
        iterator operator+(const const_iterator&) const;
        iterator operator-(int) const;
        iterator operator-(const const_iterator&) const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        bool operator<(const const_iterator&) const;
        bool operator>(const const_iterator&) const;
        bool operator<=(const const_iterator&) const;
        bool operator>=(const const_iterator&) const;
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;
    };
    class const_iterator{
        friend class Container;
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef iterator self_type;
        typedef T value_type;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef int difference_type;
    private:
        const_pointer cI;
        const_iterator(const_pointer =0);
    public:
        const_iterator(const iterator&);
        operator void*() const;
        const_reference operator*() const;
        const_reference operator[](unsigned) const;
        const_pointer operator->() const;
        const_iterator& operator+=(int);
        const_iterator& operator-=(int);
        const_iterator operator+(int) const;
        const_iterator operator-(int) const;
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        bool operator<(const const_iterator&) const;
        bool operator>(const const_iterator&) const;
        bool operator<=(const const_iterator&) const;
        bool operator>=(const const_iterator&) const;
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;
    };
};

 /*********************
 *
 *     CONTAINER
 *
 **********************/

/**
 * @brief _max_size
 *
 * campo dati static uint contenente la massima
 * capacita' del container, fissata alla massima capacita' di
 * un uint.
 */
template <class T>
typename Container<T>::size_type Container<T>::_max_size = UINT_MAX;

/**
 * @brief _length_exceeded
 *
 * campo dati static std::string utilizzato
 * nelle sollevazioni di std::length_error come parametro.
 */
template <class T>
std::string Container<T>::_length_exceeded = "Length Exceeded";

/**
 * @brief resize(__offset,__new_capacity)
 *
 *  ritorna un nuovo array con stessi valori ma
 *  capacita' differenti.
 *  resized[0...__new_capacity]
 */
template <class T>
typename Container<T>::pointer Container<T>::resize(size_type __offset,size_type __new_capacity) const {
    if(__offset<=__new_capacity && __offset<=_size){
        pointer resized= new value_type[__new_capacity];
        std::copy(P,P+__offset,resized);
        return resized;
    } else return nullptr;
}

/**
 * @brief destroy(v)
 *
 * metodo statico che elimina la memoria puntata da v
 * !! non azzera _size e _container -> STATIC METHOD
 */
template<class T>
void Container<T>::destroy(pointer v){
    if(v) delete[] v;
}

/**
 * @brief Container(__capacity,__size)
 *
 * costruttore con parametri __capacity e __size
 */
template <class T>
Container<T>::Container(size_type __capacity,size_type __size): P(new value_type[__capacity]),_capacity(__capacity), _size(__size){}

/**
 * @brief Container(__capacity,__osbject)
 *
 * costruttore con parametri __capacity e __object
 */
template <class T>
Container<T>::Container(size_type __capacity,const_reference __object): P(new value_type[__capacity]),_capacity(__capacity), _size(__capacity){
    for (unsigned i=0;i<__capacity;++i)
        P[i]=__object;
}

/**
 * @brief Container(__q)
 *
 * costruttore di copia prodonda
 */
template <class T>
Container<T>::Container(const Container<T>& __q):P(__q.resize(__q._size, __q._capacity)),_size(__q._size),_capacity(__q._capacity){}

/**
 * @brief operator=(__q)
 *
 * ridefinizione dell'operatore di assegnazione profondo
 */
template <class T>
Container<T>& Container<T>::operator=(const Container<T>& __q){
    if(this!=&__q){
        destroy(P);
        _capacity=__q._capacity;
        _size=__q._size;
        P = __q.resize(_size, _capacity);
    }
    return *this;
}

/**
 * @brief ~Container()
 *
 * Ridefinizione del distruttore profondo
 */
template <class T>
Container<T>::~Container(){ destroy(P); }

/**
 * @brief assign(__n,__obj)
 *
 * assegna un nuovo array al container, con __n oggetti __object
 */
template <class T>
void Container<T>::assign(size_type __n,const_reference __object){
    if(P) destroy(P);
    _size=_capacity=__n;
    for(unsigned i=0;i<__n;++i)
        P[i]=__object;
    return;
}

/**
 * @brief assign(__begin,__end)
 *
 * assegna un nuovo array al container, contenente gli elementi tra __begin e __end
 */
template <class T>
void Container<T>::assign(iterator __begin,iterator __end){
    if(P) destroy(P);
    _size=_capacity = static_cast<difference_type>(__end.I-__begin.I);
    std::copy(__begin,__end,iterator(P));
    return;
}

/**
 * @brief begin()
 *
 * ritorna un const_iterator(P)
 */
template <class T>
typename Container<T>::const_iterator Container<T>::begin() const{
    return const_iterator(P);
}

/**
 * @brief end()
 *
 * ritorna un const_iterator(_size)
 */
template <class T>
typename Container<T>::const_iterator Container<T>::end() const{
    return const_iterator(P+_size);
}

/**
 * @brief cbegin()
 *
 * ritorna un const_iterator(P)
 */
template <class T>
typename Container<T>::const_iterator Container<T>::cbegin() const{
    return const_iterator(P);
}

/**
 * @brief cend()
 *
 * ritorna un const_iterator(_size)
 */
template <class T>
typename Container<T>::const_iterator Container<T>::cend() const{
    return const_iterator(P+_size);
}

/**
 * @brief begin()
 *
 * ritorna un iterator(P)
 */
template <class T>
typename Container<T>::iterator Container<T>::begin(){
    return iterator(P);
}

/**
 * @brief end()
 *
 * ritorna un iterator(_size)
 */
template <class T>
typename Container<T>::iterator Container<T>::end(){
    return iterator(P+_size);
}

/**
 * @brief max_size()
 *
 * ritorna la dimensione massima che puo' avere il container
 */
template <class T>
typename Container<T>::size_type Container<T>::max_size(){
    return _max_size;
}

/**
 * @brief size()
 *
 * ritorna size attuale
 */
template <class T>
typename Container<T>::size_type Container<T>::size() const{
    return _size;
}

/**
 * @brief resize()
 *
 * esegue una resize al container, con due casi possibili
 * 1) se la nuova capacita' e' maggiore all'attuale aumento la _capacity attuale
 * 2) se la nuova capacita' e' minore dell'attuale tronco l'array
 */
template<class T>
void Container<T>::resize(size_type __new_capacity) const{
    if(__new_capacity==_capacity) return;
    _capacity=__new_capacity;
    if(__new_capacity>_capacity)
        return resize(_size,__new_capacity);
    return resize(__new_capacity,__new_capacity);
}

/**
 * @brief shrink_to_fit()
 *
 * imposta la _capacity dell'array uguale alla _size
 */
template<class T>
void Container<T>::shrink_to_fit(){
    _capacity=_size;
    resize(_size,_size);
}

/**
 * @brief capacity()
 *
 * ritorna la capacity attuale
 */
template <class T>
typename Container<T>::size_type Container<T>::capacity() const{
    return _capacity;
}

/**
 * @brief empty()
 *
 * ritorna un valore booleano che verifica se il container e' vuoto
 */
template <class T>
bool Container<T>::empty() const{
    return !P;
}

/**
 * @brief operator[](__position)
 *
 * ridefinizione dell'operatore [], eredita dall'array la stessa funzionalita'
 * ritorna un riferimento costante a T
 */
template <class T>
typename Container<T>::const_reference Container<T>::operator[](size_type __position) const{
    return P[__position];
}

/**
 * @brief operator[](__position)
 *
 * ridefinizione dell'operatore [], eredita dall'array la stessa funzionalita'
 * ritorna un riferimento a T
 */
template <class T>
typename Container<T>::reference Container<T>::operator[](size_type __position){
    return P[__position];
}

/**
 * @brief at(__n)
 *
 * ritorna un riferimento a v[__n]
 */
template <class T>
typename Container<T>::reference Container<T>::at(size_type __n){
    if(__n>_size) throw std::length_error(_length_exceeded);
    return P[__n];
}

/**
 * @brief at(__n) const
 *
 * ritorna un riferimento costante a v[__n]
 */
template <class T>
typename Container<T>::const_reference Container<T>::at(size_type __n) const{
    if(__n>_size) throw std::length_error(_length_exceeded);
    return *(P+__n);
}

/**
 * @brief front()
 *
 * ritorna un riferimento al primo elemento
 */
template <class T>
typename Container<T>::reference Container<T>::front(){
    return *P;
}

/**
 * @brief front() const
 *
 * ritorna un riferimento costante al primo elemento
 */
template <class T>
typename Container<T>::const_reference Container<T>::front() const{
    return *P;
}

/**
 * @brief back()
 *
 * ritorna un riferimento al primo elemento
 */
template <class T>
typename Container<T>::reference Container<T>::back(){
    return *(P+_size-1);
}

/**
 * @brief back() const
 *
 * ritorna un riferimento costante al primo elemento
 */
template <class T>
typename Container<T>::const_reference Container<T>::back() const{
    return *P(_size-1);
}

/**
 * @brief push_back(__object)
 *
 * aggiunge alla coda dell'array l'oggetto __object
 */
template <class T>
void Container<T>::push_back(const_reference __object){
    if(_size>=_capacity){
        _capacity*=2;
        pointer temp = resize(_size, _capacity);
        destroy(P);
        P=temp;
    }
    P[_size++]=__object;
}

/**
 * @brief pop_back()
 *
 * elimina l'ultimo oggetto dell'array
 */
template <class T>
void Container<T>::pop_back(){
    if(!_size) return;
    _size-=1;
}

/**
 * @brief insert(__object)
 *
 * inserisce l'oggetto __object in __position
 */
template <class T>
typename Container<T>::iterator Container<T>::insert(iterator __position,const_reference __object){
    if(_size<_capacity){
        ++_size;
        std::copy_backward(__position, end()-1, end());
        *__position = __object;
        return __position;
    }
    difference_type offset = static_cast<difference_type>(__position.I-P);
    _capacity*=2;
    pointer temp = resize(offset, _capacity);
    temp[offset] = __object;
    std::copy(__position, end(), iterator(temp+offset+1));
    destroy(P);
    ++_size;
    P=temp;
    return iterator(temp+offset);
}

/**
 * @brief insert(__position,__n,__object)
 *
 * inserisce l'oggetto __object in __position
 */
template <class T>
void Container<T>::insert(iterator __position,size_type __n,const_reference __object){
    if(_size<=_capacity){
        _size+=__n;
        std::copy_backward(__position, end()-__n, end());
        for (int i=0;i<__n;++i)
            __position[i]=__object;
        return;
    }
    difference_type offset = static_cast<difference_type>(__position.I-P);
    _capacity = 2*(_size+__n);
    pointer temp = resize(offset, _capacity);
    for(unsigned i=0;i<__n;++i)
        temp[offset+i]=__object;
    std::copy(__position, end(), iterator(temp+offset+__n));
    destroy(P); _size+=__n; P=temp;

}

/**
 * @brief erase(__position)
 *
 * elimina l'oggetto in posizione __position
 */
template<class T>
typename Container<T>::iterator Container<T>::erase(iterator __position){
    return erase(__position, __position+1);
}

/**
 * @brief erase(__positionOne,__positionTwo)
 *
 * elimina gli oggetti tra le posizioni __positionOne e __positionTwo
 * se il parametro __fit e' true allora eseguo uno shrink_to_fit()
 * __fit di default == false
 */
template<class T>
typename Container<T>::iterator Container<T>::erase(iterator __positionOne,iterator __positionTwo,bool __fit){
    if(!_size) return iterator(0);
    if(__positionOne<begin()) return erase(begin(),__positionTwo);
    if(__positionTwo>end()) return erase(__positionOne,end());
    std::copy(__positionTwo,end(),__positionOne);
    difference_type offset = static_cast<difference_type>(__positionTwo.I-__positionOne.I);
    _size-=offset;
    if(__fit)shrink_to_fit(); /** esegue un resize(_size,_size) */
    return __positionOne;
}

/**
 * @brief erase(__object)
 *
 * rimuove l'oggetto __object dell'array
 * ritorna true se l'oggetto viene rimosso,
 * false in caso contrario
 */
template<class T>
bool Container<T>::erase(const_reference __object){
    size_type oldSize = _size;
    erase(search(__object));
    return (_size<oldSize)?true:false;
}

/**
 * @brief eraseAll(__object)
 *
 * rimuove tutti gli __object dall'array
 * ritorna true se viene rimosso almeno un oggetto
 * false in caso contrario
 */
template<class T>
bool Container<T>::eraseAll(const_reference t__object){
    size_type oldSize = _size;
    std::copy_if(search(t__object), end(), search(t__object), [&t__object,this](reference x)->bool{
        if(x!=t__object) return true;
        this->_size--; return false;
    });
    return (_size<oldSize)?true:false;
}

/**
 * @brief clear()
 *
 * elimina tutti gli oggetti dall'array
 * mantenendo la capacita'
 */
template <class T>
void Container<T>::clear(){
    erase(begin(), end());
}

/**
 * @brief search(__object)
 *
 * ritorna un iterator della posizione dell'oggetto __object dell'array
 * se l'oggetto non viene trovato ritorna iterator(0)
 */
template<class T>
typename Container<T>::iterator Container<T>::search(const_reference __object){
    iterator it = begin();
    for (;it!=end() && *it!=__object;++it);
    if(it==end())
        return iterator(0);
    return it;
}

/**
 * @brief search(__object)
 *
 * ritorna un const_iterator della posizione dell'oggetto __object dell'array
 * se l'oggetto non viene trovato ritorna un const_iterator(0)
 */
template<class T>
typename Container<T>::const_iterator Container<T>::search(const_reference __object) const{
    const_iterator cit = begin();
    for (;cit!=end() && *cit!=__object;++cit);
    if(cit==end())
        return const_iterator(0);
    return cit;
}

/**
 * @brief indexOf(__object)
 *
 * ritorna l'indice dell'elemento cercato
 */
template<class T>
typename Container<T>::size_type Container<T>::indexOf(const_reference __object) const{
    const_iterator it = search(__object);
    return static_cast<difference_type>(it.cI-cbegin());
}

/**
 * @brief operator==(__q)
 *
 * Ridefinizione dell'operatore di uguaglianza
 */
template<class T>
bool Container<T>::operator==(const Container& __q) const{
    if(_size!=__q._size) return false;
    unsigned i=0;
    for(;i<_size && P[i]==__q.P[i];++i);
    if(i==_size)
        return true;
    return false;
}

/**
 * @brief operator<(__q)
 *
 * Ridefinizione dell'operatore di confronto minore
 */
template<class T>
bool Container<T>::operator<(const Container& __q) const{

    unsigned int min=_size<__q._size?_size:__q._size;
    for(unsigned int i=0;i<min;++i)
        if(P[i]!=__q.P[i])
            return P[i]<__q.P[i];
    return _size<__q._size?true:false;
}

/**
 * @brief operator>(__q)
 *
 * Ridefinizione dell'operatore di confronto maggiore
 */
template<class T>
bool Container<T>::operator>(const Container& __q) const{
    unsigned int min=_size<__q._size?_size:__q._size;
    for(unsigned int i=0;i<min;++i)
        if(P[i]!=__q.P[i])
            return P[i]>__q.P[i];
    return _size>__q._size?true:false;
}

/**
 * @brief operator<=(__q)
 *
 * Ridefinizione dell'operatore di confronto minore uguale
 */
template<class T>
bool Container<T>::operator<=(const Container& __q) const{
    return *this<--__q || *this==--__q;
}

/**
 * @brief operator>=(__q)
 *
 * Ridefinizione dell'operatore di confronto maggiore uguale
 */
template<class T>
bool Container<T>::operator>=(const Container& __q) const{
    return *this>__q || *this==__q;
}


/***********************
 *
 *  ITERATOR
 *
 **********************/

/**
 * @brief iterator(__p)
 *
 * costruttore di iterator con puntatore __p
 */
template<class T>
Container<T>::iterator::iterator(pointer __p): I(__p){}

/**
 * @brief operator void*()
 *
 * ritorna P in void*
 */
template<class T>
Container<T>::iterator::operator void*() const {
    return I;
}

/**
 * @brief operator*()
 *
 * ridefinizione dell'operatore di dereferenziazione,
 * ritorna un riferimento all'oggetto
 */
template<class T>
typename Container<T>::iterator::reference Container<T>::iterator::operator*() const {
    return *I;
}

/**
 * @brief operator->()
 *
 * ridefinizione dell'operatore ->,
 * ritorna un puntatore
 */
template<class T>
typename Container<T>::iterator::pointer Container<T>::iterator::operator->() const {
    return &I;
}

/**
 * @brief operator[](__x)
 *
 * ridefinizione dell'operatore [],
 * ritorna un riferimento alla posizione __x
 */
template<class T>
typename Container<T>::iterator::reference Container<T>::iterator::operator[](unsigned __x) const {
    return *(I+__x);
}

/**
 * @brief operator+=(__it)
 *
 * ridefinizione dell'operatore +=,
 * ritorna un riferimento di iterator alla posizione __it
 */
template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator+=(const const_iterator& __it) {
    I+=__it.cI-I;
    return *this;
}

/**
 * @brief operator+=(__x)
 *
 * ridefinizione dell'operatore +=,
 * ritorna un riferimento di iterator alla posizione __x
 */
template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator+=(int __x) {
    I+=__x;
    return *this;
}

/**
 * @brief operator-=(__it)
 *
 * ridefinizione dell'operatore +=,
 * ritorna un riferimento di iterator alla posizione __it
 */
template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator-=(const const_iterator& __it) {
    I-=__it.cI-I;
    return *this;
}

/**
 * @brief operator-=(__x)
 *
 * ridefinizione dell'operatore -=,
 * ritorna un riferimento di iterator alla posizione __x
 */
template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator-=(int __x) {
    I-=__x;
    return *this;
}

/**
 * @brief operator+(x)
 *
 * ridefinizione dell'operatore +,
 * ritorna una copia di iterator alla posizione __x
 */
template<class T>
typename Container<T>::iterator Container<T>::iterator::operator+(int __x) const {
    return iterator(I+__x);
}

/**
 * @brief operator+(__it)
 *
 * ridefinizione dell'operatore +,
 * ritorna una copia di iterator alla posizione __it
 */
template<class T>
typename Container<T>::iterator Container<T>::iterator::operator+(const const_iterator& __it) const {
    return iterator(I+__it.cI);
}

/**
 * @brief operator-(__it)
 *
 * ridefinizione dell'operatore -,
 * ritorna una copia di iterator alla posizione __it
 */
template<class T>
typename Container<T>::iterator Container<T>::iterator::operator-(const const_iterator& __it) const {
    return iterator(I-__it.cI);
}

/**
 * @brief operator-(__x)
 *
 * ridefinizione dell'operatore -,
 * ritorna una copia di iterator alla posizione __x
 */
template<class T>
typename Container<T>::iterator Container<T>::iterator::operator-(int __x) const {
    return iterator(I-__x);
}

/**
 * @brief operator++()
 *
 * ridefinizione dell'operatore ++,
 * ritorna un riferimento di iterator
 */
template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator++() {
    ++I;
    return *this;
}

/**
 * @brief operator++(int)
 *
 * ridefinizione dell'operatore ++(int),
 * ritorna una copia di aux
 */
template<class T>
typename Container<T>::iterator Container<T>::iterator::operator++(int) {
    iterator aux=iterator(*this);
    ++I;
    return aux;
}

/**
 * @brief operator--()
 *
 * ridefinizione dell'operatore --,
 * ritorna un riferimento di iterator
 */
template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator--() {
    --I;
    return *this;
}

/**
 * @brief operator--(int)
 *
 * ridefinizione dell'operatore --(int),
 * ritorna una copia di aux
 */
template<class T>
typename Container<T>::iterator Container<T>::iterator::operator--(int) {
    iterator aux=iterator(*this);
    --I;
    return aux;
}

/**
 * @brief operator<(__it)
 *
 * ridefinizione dell'operatore <,
 * ritorna true o false
 */
template<class T>
bool Container<T>::iterator::operator<(const const_iterator& __it) const{
    return I<__it.cI;
}

/**
 * @brief operator>(__it)
 *
 * ridefinizione dell'operatore >,
 * ritorna true o false
 */
template<class T>
bool Container<T>::iterator::operator>(const const_iterator& __it) const{
    return I>__it.cI;
}

/**
 * @brief operator<=(__it)
 *
 * ridefinizione dell'operatore <=,
 * ritorna true o false
 */
template<class T>
bool Container<T>::iterator::operator<=(const const_iterator& __it) const{
    return I<=__it.cI;
}

/**
 * @brief operator>=(__it)
 *
 * ridefinizione dell'operatore >=,
 * ritorna true o false
 */
template<class T>
bool Container<T>::iterator::operator>=(const const_iterator& __it) const{
    return I>=__it.cI;
}

/**
 * @brief operator==(__it)
 *
 * ridefinizione dell'operatore ==,
 * ritorna true o false
 */
template<class T>
bool Container<T>::iterator::operator==(const const_iterator& __it) const{
    return I==__it.cI;
}

/**
 * @brief operator!=(__it)
 *
 * ridefinizione dell'operatore !=,
 * ritorna true o false
 */
template<class T>
bool Container<T>::iterator::operator!=(const const_iterator& __it) const{
    return I!=__it.cI;
}

/***********************
 *
 *  CONST_ITERATOR
 *
 **********************/

/**
 * @brief const_iterator(__p)
 *
 * costruttore di const_iterator con puntatore __p
 */
template<class T>
Container<T>::const_iterator::const_iterator(const T* __p): cI(__p){}

/**
 * @brief const_iterator(__it)
 *
 * costruttore di copia di const_iterator con
 * riferimento costante a iterator __it
 */
template<class T>
Container<T>::const_iterator::const_iterator(const iterator& __it): cI(__it.I){}

/**
 * @brief operator void*()
 *
 * ritorna P in void*
 */
template<class T>
Container<T>::const_iterator::operator void*() const {
    return cI;
}

/**
 * @brief operator*()
 *
 * ridefinizione dell'operatore di dereferenziazione,
 * ritorna un riferimento constante all'oggetto
 */
template<class T>
typename Container<T>::const_iterator::const_reference Container<T>::const_iterator::operator*() const {
    return *cI;
}

/**
 * @brief operator->()
 *
 * ridefinizione dell'operatore ->,
 * ritorna un puntatore constante
 */
template<class T>
typename Container<T>::const_iterator::const_pointer Container<T>::const_iterator::operator->() const {
    return &cI;
}

/**
 * @brief operator[](__x)
 *
 * ridefinizione dell'operatore [],
 * ritorna un riferimento alla posizione __x
 */
template<class T>
typename Container<T>::const_iterator::const_reference Container<T>::const_iterator::operator[](unsigned __x) const {
    return *(cI+__x);
}

/**
 * @brief operator+=(__it)
 *
 * ridefinizione dell'operatore +=,
 * ritorna un riferimento di const_iterator alla posizione __it
 */
template<class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator+=(int __x) {
    cI+=__x;
    return*this;
}

/**
 * @brief operator+=(__x)
 *
 * ridefinizione dell'operatore +=,
 * ritorna un riferimento di const_iterator alla posizione __x
 */
template<class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator-=(int __x) {
    cI-=__x;
    return *this;
}

/**
 * @brief operator+(__x)
 *
 * ridefinizione dell'operatore +,
 * ritorna una copia di const_iterator alla posizione __x
 */
template<class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator+(int __x) const {
    return const_iterator(cI+__x);
}

/**
 * @brief operator-(__x)
 *
 * ridefinizione dell'operatore -,
 * ritorna una copia di const_iterator alla posizione __x
 */
template<class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator-(int __x) const {
    return const_iterator(cI-__x);
}

/**
 * @brief operator++()
 *
 * ridefinizione dell'operatore ++,
 * ritorna un riferimento di const_iterator
 */
template<class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator++() {
    ++cI;
    return *this;
}

/**
 * @brief operator++(int)
 *
 * ridefinizione dell'operatore ++(int),
 * ritorna una copia di aux
 */
template<class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator++(int) {
    const_iterator aux=const_iterator(*this);
    ++cI;
    return aux;
}

/**
 * @brief operator--()
 *
 * ridefinizione dell'operatore --,
 * ritorna un riferimento di const_iterator
 */
template<class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator--() {
    --cI;
    return *this;
}

/**
 * @brief operator--(int)
 *
 * ridefinizione dell'operatore --(int),
 * ritorna una copia di aux
 */
template<class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator--(int) {
    const_iterator aux=const_iterator(*this);
    --cI;
    return aux;
}

/**
 * @brief operator<(__it)
 *
 * ridefinizione dell'operatore <,
 * ritorna true o false
 */
template<class T>
bool Container<T>::const_iterator::operator<(const const_iterator& __it) const{
    return cI<__it.cI;
}

/**
 * @brief operator>(__it)
 *
 * ridefinizione dell'operatore >,
 * ritorna true o false
 */
template<class T>
bool Container<T>::const_iterator::operator>(const const_iterator& __it) const{
    return cI>__it.cI;
}

/**
 * @brief operator<=(__it)
 *
 * ridefinizione dell'operatore <=,
 * ritorna true o false
 */
template<class T>
bool Container<T>::const_iterator::operator<=(const const_iterator& __it) const{
    return cI<=__it.cI;
}

/**
 * @brief operator>=(__it)
 *
 * ridefinizione dell'operatore >=,
 * ritorna true o false
 */
template<class T>
bool Container<T>::const_iterator::operator>=(const const_iterator& __it) const{
    return cI>=__it.cI;
}

/**
 * @brief operator==(__it)
 *
 * ridefinizione dell'operatore ==,
 * ritorna true o false
 */
template<class T>
bool Container<T>::const_iterator::operator==(const const_iterator& __it) const{
    return cI==__it.cI;
}

/**
 * @brief operator!=(__it)
 *
 * ridefinizione dell'operatore !=,
 * ritorna true o false
 */
template<class T>
bool Container<T>::const_iterator::operator!=(const const_iterator& __it) const{
    return cI!=__it.cI;
}




#endif /* CONTAINER_H */

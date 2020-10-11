#ifndef HASHMAP_H_INCLUDED
#define HASHMAP_H_INCLUDED

template <typename T>
class HashedCompare {
public:
    virtual unsigned int hashCode(T obj) = 0;
};

class IntergerHashed : public HashedCompare<int> {
public:
    unsigned int hashCode(int obj) {
        return obj;
    }
};

class StringHashed : public HashedCompare<string> {
public:
    unsigned int hashCode(string s) {
        unsigned int h = 0;
        for(unsigned int i = 0; i < s.length(); i++) {
            h = 31 * h + s.at(i);   /// 31作为不大不小的质数，作为进制位（31进制）
        }
        return h;
    }
};

template <typename K, typename V>
class LinkNode {
 public:
     K key;
     V value;
     LinkNode<K, V>* next;
     LinkNode(K key, V value) {
         this->key = key;
         this->value = value;
         this->next = NULL;
     }
};

template <typename K, typename V>
class Entry {
 public:
     K key;
     V value;
     Entry(K key, V value) {
         this->key = key;
         this->value = value;
     }
};

template <typename K, typename V>
class HashMap {
private:
    LinkNode<K, V>** table;
    int size;
    int capacityIndex;
    int capacity;
    const int maxCapacityIndex = 27;
    const int capacityContainer[27] = {31, 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
            49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469,
            12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};
    double loadFactor;
    HashedCompare<K>* hashedCompare;

    int hash(K key) {
        return hashedCompare->hashCode(key) % capacity;
    }

    LinkNode<K, V>*& getNode(K key) {
        int h = hash(key);
        LinkNode<K, V>* current = table[h];
        LinkNode<K, V>** prev = &current;
        while(current != NULL) {
            if(current->key == key) {
                return *prev;
            }
            prev = &(current->next);
            current = current->next;
        }
        return *prev;
    }

    void putNode(LinkNode<K, V>** table, LinkNode<K, V>* node) {
        int h = hash(node->key);
        LinkNode<K, V>* current = table[h];
        if(current == NULL) {
            table[h] = node;
        } else {
            node->next = current;
            table[h] = node;
        }
    }

    void resize(int newSize) {
        int oldCapacity = this->capacity;
        LinkNode<K, V>** newTable = new LinkNode<K, V>*[newSize];
        this->capacity = newSize;
        for(int i = 0; i < capacity; i++) {
            newTable[i] = NULL;
        }
        for(int index = 0; index <oldCapacity; index++) {
            LinkNode<K, V>* node = table[index];
            while(node != NULL) {
                LinkNode<K, V>*& current = table[index];
                current = current->next;
                node->next = NULL;
                putNode(newTable, node);
                node = current;
            }
        }
        delete this->table;
        this->table = newTable;
    }

public:
    HashMap(HashedCompare<K>* hashCompare, double loadFactor = 0.75f) {
        this->capacityIndex = 0;
        this->capacity = capacityContainer[capacityIndex];
        this->table = new LinkNode<K, V>*[capacity];
        this->size = 0;
        this->loadFactor = loadFactor;
        this->hashedCompare = hashCompare;
        for(int i = 0; i < capacity; i++) {
            table[i] = NULL;
        }
    }

    bool isEmpty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }

    void put(K key, V value) {
        LinkNode<K, V>* node = getNode(key);
        if(node != NULL) {
            node->value = value;
            return;
        }

        putNode(table, new LinkNode<K, V>(key, value));
        size++;
        if(size > capacity * loadFactor && capacityIndex < maxCapacityIndex) {
            resize(capacityContainer[++capacityIndex]);
        }
    }

    V get(K key) {
        LinkNode<K, V>* node = getNode(key);
        return node != NULL ? node->value : NULL;
    }

    bool contains(K key) {
        return getNode(key) != NULL;
    }

    V remove(K key) {
        LinkNode<K, V>*& node = getNode(key);
        if(node != NULL) {
            LinkNode<K, V>* delNode = node;
            V ret = delNode->value;
            node = node->next;
            return ret;
        }
        return NULL;
    }

    class iterator;

    HashMap<K, V>::iterator* newIterator() {
        return new HashMap<K, V>::iterator(capacity, 0, NULL, table);
    }

    class iterator {
    private:
        int capacity;
        int index;
        LinkNode<K, V>* node;
        LinkNode<K, V>** table;
    public:
        iterator(int capacity, int index, LinkNode<K, V>* node, LinkNode<K, V>** table) {
            this->capacity = capacity;
            this->table = table;
            while(node == NULL && index < capacity) {
                node = table[index++];
            }
            this->node = node;
            this->index = index;
        }
        bool hasNext() {
            return node != NULL;
        }
        Entry<K, V> next() {
            Entry<K, V> entry = Entry<K, V>(node->key, node->value);
            if(node != NULL) {
                node = node->next;
            }
            while(node == NULL && index < capacity) {
                node = table[index++];
            }
            return entry;
        }
    };

    ~HashMap() {
        for(int i = 0; i < capacity; i++) {
            LinkNode<K, V>*& current = table[i];
            while(current != NULL) {
                LinkNode<K, V>* ele = current;
                current = current->next;
                delete ele;
            }
        }
    }

};

#endif // HASHMAP_H_INCLUDED

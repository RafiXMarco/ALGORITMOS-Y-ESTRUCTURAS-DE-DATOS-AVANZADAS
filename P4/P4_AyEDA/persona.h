template<class Key>
class Persona {
 public:
    operator long() { 
        Persona aux;
        aux.id_ = Key;
        return aux;
    }
    operator ==() { 
        Persona aux;
        aux.id_ = Key;
        return aux;
    }
 private:
    long id_;
};
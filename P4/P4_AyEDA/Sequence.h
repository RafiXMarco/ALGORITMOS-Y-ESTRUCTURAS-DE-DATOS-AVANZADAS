// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Autor: Marco Napierski

#ifndef SEQUENCE
#define SEQUENCE

template<class Key>
class Sequence {
 public:
  virtual bool search(const Key&) const = 0;
  virtual bool insert(const Key&) = 0;
  virtual bool isFull() const = 0;
};

template<class Key>
class List : public Sequence<Key> {
 public:
  List() : listSize_(0), sequence_(NULL) {}
  ~List() {
    if (sequence_ != NULL) {
      delete[] sequence_;
      sequence_ = NULL;
      listSize_ = 0;
    }
  }
  Key operator[] (const unsigned i) { return sequence_[i]; }
  bool search(const Key& k) const override {
    // std::cout << "IN" << "\n";
    for (int i = 0; i < listSize_; ++i) {
      // std::cout << sequence_[i] << " = "  << k << "?\n";
      if (sequence_[i] == k) return true;
    }
    return false;
  }
  bool insert(const Key& k) override {
    if (!search(k)) {
      Key* aux = sequence_;
      sequence_ = new Key[listSize_ + 1];
      for (int i = 0; i < listSize_; ++i) {
        sequence_[i] = aux[i];
      }
      sequence_[listSize_] = k;
      // std::cout << sequence_[listSize_] << "\n";
      listSize_++;
      // std::cout << listSize_ << '\n';
      return true;
    } else {
      return false;
    }
  }
  bool isFull() const { return false; }
 private:
  int listSize_;
  Key* sequence_; // std::vector<Key>
};

template<class Key>
class Block : public Sequence<Key> {
 public:
  Block() : blockSize_(0), blockElements_(0), sequence_(NULL) {}
  Block(int size) : blockSize_(size), blockElements_(0) {
    sequence_ = new Key[size];
    for (int i = 0; i < blockSize_; ++i) sequence_[i] = NULL;
  }
  ~Block() { delete[] sequence_; }
  Key operator[] (const unsigned i) { return sequence_[i]; }
  bool search(const Key& k) const override {
    for (int i = 0; i < blockSize_; ++i) {
      if (sequence_[i] == k) return true;
    }
    return false;
  }
  bool insert(const Key& k) override {
    if (!isFull() && !search(k)) {
      sequence_[blockElements_++] = k;
      return true;
    } else {
      return false;
    }
  }
  bool isFull() const {
    if (blockSize_ == blockElements_) return true;
    return false;
  }
 private:
  int blockSize_;
  int blockElements_;
  Key* sequence_;
};

#endif
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stack>

// Base = 8
// N1 = 07563245624
// N2 = 3247125454
// N3 = 254565775
// E1 = N1 N2 *
// E2 = E1 N3 -
// E3 = E1 E2 N1 + *
// E4 = N2 N1 E2 * /

// Base = 2
// N1 = 10101110111000101
// N2 = 011011111101001
// E1 = N1 N2 OR
// E2 = E1 E1 AND










template <size_t Base> class BigInt;
template <size_t Base> bool operator==(const BigInt<Base>& numero1, const BigInt<Base> &numero2);
template <size_t Base> std::ostream& operator<<(std::ostream& out, const BigInt<Base>& numero);
template <size_t Base> std::istream& operator>>(std::istream& in, BigInt<Base>& numero);
template <size_t Base> bool operator>(const BigInt<Base>& numero1, const BigInt<Base> &numero2);
template <size_t Base> bool operator<(const BigInt<Base>& numero1, const BigInt<Base> &numero2);
template <size_t Base> BigInt<Base> operator+(const BigInt<Base>& numero1, const BigInt<Base>& numero2);
template <size_t Base> BigInt<Base> operator/(const BigInt<Base>& numero1, const BigInt<Base>& numero2);
template <size_t Base> BigInt<Base> pow(const BigInt<Base>& numero1, const BigInt<Base>& numero2);



std::map<char, int> hex_map = {{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, 
{'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}};

std::map<int, char> hex_map2= {{0, '0'}, {1 , '1'}, {2, '2'}, {3 , '3'}, {4 , '4'}, {5 , '5'}, 
{6, '6'}, {7, '7'}, {8, '8'}, {9, '9'}, {10, 'A'}, {11, 'B'}, {12 , 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}};


std::vector<char> reverse(std::vector<char> num) {
    reverse(num.begin(), num.end());
    return num;
}


template <size_t Base>
class BigInt{
  public:
    // Constructores:
    BigInt(long n = 0);
    BigInt(std::string&);
    BigInt(const char* );
    BigInt(const BigInt<Base>&);

    // Asignación:
    BigInt<Base>& operator=(const BigInt<Base>&);

    // Inserción y extracción en flujo:
    friend std::ostream& operator<<<Base>(std::ostream& out, const BigInt<Base>& numero);
    friend std::istream& operator>><Base>(std::istream& in, BigInt<Base>& numero);

    // Accesor:
    int sign() const { return sign_; } // Signo: 1 o -1
    char operator[](int) const; // Acceso al i-ésimo dígito

    // Comparación:
    friend bool operator==<Base>(const BigInt<Base>& numero1, const BigInt<Base> &numero2);
    bool operator!=(const BigInt<Base>&) const;
    friend bool operator> <Base>(const BigInt<Base>& numero1, const BigInt<Base> &numero2);
    bool operator>=(const BigInt<Base> &) const;
    friend bool operator< <Base>(const BigInt<Base>& numero1, const BigInt<Base> &numero2);
    bool operator<=(const BigInt<Base> &) const;

    // Incremento/decremento:
    BigInt<Base>& operator++(); // Pre-incremento
    BigInt<Base> operator++(int); // Post-incremento
    BigInt<Base>& operator--(); // Pre-decremento
    BigInt<Base> operator--(int); // Post-decremento

    // // Operadores aritméticos:
    friend BigInt<Base> operator+<Base>(const BigInt<Base>& numero1, const BigInt<Base>& numero2);
    BigInt<Base> operator-(const BigInt<Base> &) const;
    BigInt<Base> operator-() const;
    BigInt<Base> operator*(const BigInt<Base>&) const;
    friend BigInt<Base> operator/<Base>(const BigInt<Base>& numero1, const BigInt<Base>& numero2);
    BigInt<Base> operator%(const BigInt<Base>&) const;
    
    // Potencia a^b
    friend BigInt<Base> pow<Base>(const BigInt<Base>& numero1, const BigInt<Base>& numero2);

    // getter
    std::vector<char> numero(){return numero_;}

  private:
    std::vector<char> numero_;
    int sign_;

};




/**
 * @brief Construct a new Big Int< Base>:: Big Int object
 * 
 * @tparam Base 
 * @param n 
 */
template <size_t Base>
BigInt<Base>::BigInt(long n) {
    if (n == 0) {numero_.push_back('0');}
    if (n < 0) {
        sign_ = -1;
    } else {
        sign_ = 1;
    }
    while (n > 0){
        char temp =  n%10 + '0';
        numero_.push_back(temp);
        n = n/10;
    }
    reverse(numero_.begin(),numero_.end());
}

/**
 * @brief Construct a new Big Int< Base>:: Big Int object
 * 
 * @tparam Base 
 * @param string 
 */
template <size_t Base>
BigInt<Base>::BigInt(std::string& string) {
    unsigned i;
    if (string[0] == '-') {
        sign_ = -1;
        i=1;
    } else {
        sign_ = 1;
        i=0;
    }
    for (; i < string.length(); i++) {
        char d = string[i];
        // if ('0' <= d && d <= '9') {
        //     d = d - '0';
        // } else if ('A' <= d && d <= 'F') {
        //     d = d - 'F';
        // } else {
        //     std::cout << "\n" << d << "no esta en el rango\n";
        // }
        numero_.push_back(d);
    }
}

/**
 * @brief Construct a new Big Int< Base>:: Big Int object
 * 
 * @tparam Base 
 * @param caracters 
 */
template <size_t Base>
BigInt<Base>::BigInt(const char* caracters) {
    std::string string(caracters);
    if (string[0] == '-') {
        sign_ = -1;
    } else {
        sign_ = 1;
    }
    for (unsigned i = 0; i < string.length(); i++) {
        numero_.push_back(string[i]);
    }
}

/**
 * @brief Construct a new Big Int< Base>:: Big Int object
 * 
 * @tparam Base 
 * @param numero 
 */
template <size_t Base>
BigInt<Base>::BigInt(const BigInt<Base>& numero) {
    numero_ = numero.numero_;
    sign_ = numero.sign_;
}

/**
 * @brief operator =
 * 
 * @tparam Base 
 * @param numero 
 * @return BigInt<Base>& 
 */
template <size_t Base>
BigInt<Base>& BigInt<Base>::operator=(const BigInt<Base>& numero) {
    numero_ = numero.numero_;
    sign_ = numero.sign_;
    return *this;
} 

/**
 * @brief operator <<
 * 
 * @param out 
 * @param numero 
 * @return * template <size_t Base>& 
 */
template <size_t Base>
std::ostream& operator<<(std::ostream& out, const BigInt<Base>& numero) {
    if (numero.sign_ == -1 ) {
        out << "-";
    }
    for (int i  = 0;  i < numero.numero_.size(); i++) {
        out << numero.numero_[i]<< " ";
    }
    // out << " <- ";

    // std::vector<char> temp = numero.numero_;
    // temp = reverse(temp);
    // int sum = 0;
    // for (unsigned i = 0; i < temp.size(); i++) {
    //     if (temp[i] == '-') continue;
    //     //std::cout << Base << " " << i << " " << hex_map[temp[i]];
    //     sum += pow(Base,i) * hex_map[temp[i]];
    // }
    // out << sum;
    out << "\n";
    return out;   
}

/**
 * @brief operator >>
 * 
 * @tparam Base 
 * @param in 
 * @param numero 
 * @return std::istream& 
 */
template <size_t Base>
std::istream& operator>>(std::istream& in, BigInt<Base>& numero) {
    std::string string;
    in >> string;
    BigInt<Base> temp(string);
    numero = temp;
    return in;
}

/**
 * @brief operator[]
 * 
 * @tparam Base 
 * @param i 
 * @return char 
 */
template <size_t Base>
char BigInt<Base>::operator[](int i) const {
    return numero_[i];
} 

/**
 * @brief operator ==
 * 
 * @tparam Base 
 * @param numero1 
 * @param numero2 
 * @return true 
 * @return false 
 */
template <size_t Base>
bool operator==(const BigInt<Base>& numero1, const BigInt<Base> &numero2) {
    auto size_num1 = numero1.numero_.size();
    auto size_num2 = numero2.numero_.size();
    if (size_num1 != size_num2) return false;
    for (auto i = 0; i < size_num1; i++) {
        if (numero1.numero_[i] != numero2.numero_[i]) return false;
    } 
    return true;
} 

/**
 * @brief operator !=
 * 
 * @tparam Base 
 * @param numero2 
 * @return true 
 * @return false 
 */
template <size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base>& numero2) const {
    auto size_num1 = numero_.size();
    auto size_num2 = numero2.numero_.size();
    if (size_num1 != size_num2) return true;
    for (auto i = 0; i < size_num1; i++) {
        if (numero_[i] != numero2.numero_[i]) return true;
    } 
    return false;
}

/**
 * @brief operator >
 * 
 * @tparam Base 
 * @param numero1 
 * @param numero2 
 * @return true 
 * @return false 
 */
template <size_t Base>
bool operator>(const BigInt<Base>& numero1, const BigInt<Base> &numero2) {
    auto size_num1 = numero1.numero_.size();
    auto size_num2 = numero2.numero_.size();

    if (numero1.sign_ == 1 && numero2.sign_ == -1) return true;
    if (numero1.sign_ == -1 && numero2.sign_ == 1) return false;

    if (size_num1 > size_num2){ 
        return true;
    } else if (size_num1 < size_num2) {
        return false;
    } else {
        // si son igual size
        for (unsigned i = 0 ; i < size_num1; i++) {
            if(numero1.numero_[i] == numero2.numero_[i]) continue;
            if(numero1.numero_[i] > numero2.numero_[i]) return true;
            if(numero1.numero_[i] < numero2.numero_[i]) return false;
        }
    }
    return false;
} 

/**
 * @brief operator >=
 * 
 * @tparam Base 
 * @param numero2 
 * @return true 
 * @return false 
 */
template <size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base> &numero2) const {
    auto size_num1 = numero_.size();
    auto size_num2 = numero2.numero_.size();
    
    if (sign_ == 1 && numero2.sign_ == -1) return true;
    if (sign_ == -1 && numero2.sign_ == 1) return false;

    if (size_num1 > size_num2){ 
        return true;
    } else if (size_num1 < size_num2) {
        return false;
    } else {
        // si son igual size
        for (unsigned i = 0 ; i < size_num1; i++) {
            if(numero_[i] == numero2.numero_[i]) continue;
            if(numero_[i] > numero2.numero_[i]) return true;
            if(numero_[i] < numero2.numero_[i]) return false;
        }
    }
    return true;
}

/**
 * @brief operator <
 * 
 * @tparam Base 
 * @param numero1 
 * @param numero2 
 * @return true 
 * @return false 
 */
template <size_t Base>
bool operator<(const BigInt<Base>& numero1, const BigInt<Base> &numero2) {
    auto size_num1 = numero1.numero_.size();
    auto size_num2 = numero2.numero_.size();

    if (numero1.sign_ == 1 && numero2.sign_ == -1) return false;
    if (numero1.sign_ == -1 && numero2.sign_ == 1) return true;

    if (size_num1 > size_num2){ 
        return false;
    } else if (size_num1 < size_num2) {
        return true;
    } else {
        // si son igual size
        for (unsigned i = 0 ; i < size_num1; i++) {
            if(numero1.numero_[i] == numero2.numero_[i]) continue;
            if(numero1.numero_[i] > numero2.numero_[i]) return false;
            if(numero1.numero_[i] < numero2.numero_[i]) return true;
        }
    }
    return false;
} 

/**
 * @brief operator <=
 * 
 * @tparam Base 
 * @param numero2 
 * @return true 
 * @return false 
 */
template <size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base> &numero2) const {
    auto size_num1 = numero_.size();
    auto size_num2 = numero2.numero_.size();

    if (sign_ == 1 && numero2.sign_ == -1) return false;
    if (sign_ == -1 && numero2.sign_ == 1) return true;

    if (size_num1 > size_num2){ 
        return false;
    } else if (size_num1 < size_num2) {
        return true;
    } else {
        // si son igual size
        for (unsigned i = 0 ; i < size_num1; i++) {
            if(numero_[i] == numero2.numero_[i]) continue;
            if(numero_[i] > numero2.numero_[i]) return false;
            if(numero_[i] < numero2.numero_[i]) return true;
        }
    }
    return true;
}

/**
 * @brief operaator++
 * 
 * @tparam Base 
 * @return BigInt<Base>& 
 */
template <size_t Base>
BigInt<Base>& BigInt<Base>::operator++() {
    BigInt<Base> aux{"1"};
    *this = *this + aux;
    return *this;
}

/**
 * @brief  operator++
 * 
 * @tparam Base 
 * @return BigInt<Base> 
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator++(int) {
    BigInt<Base> aux{*this};
    ++(*this);
    return aux;
}

/**
 * @brief operator --
 * 
 * @tparam Base 
 * @return BigInt<Base>& 
 */
template <size_t Base>
BigInt<Base>& BigInt<Base>::operator--() {
    BigInt<Base> aux{"1"};
    *this = *this - aux;
    return *this;
}

/**
 * @brief operator --
 * 
 * @tparam Base 
 * @return BigInt<Base> 
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator--(int) {
    BigInt<Base> aux{*this};
    --(*this);
    return aux;
}

/**
 * @brief add two numbers
 * 
 * @param num1 
 * @param num2 
 * @param base 
 * @return std::vector<char> 
 */
std::vector<char> add(std::vector<char> num1, std::vector<char> num2, int base) {
    std::vector<char> res;
    int i = num1.size() - 1, j = num2.size() - 1, carry = 0;
    while (i >= 0 || j >= 0) {
        int a = i >= 0 ? hex_map[num1[i--]] : 0;
        int b = j >= 0 ? hex_map[num2[j--]] : 0;
        int sum = a + b + carry;
        carry = sum / base;
        res.push_back(hex_map2[sum % base]);
    }
    
    if (carry) res.push_back(hex_map2[carry]);
    return reverse(res);
}

/**
 * @brief subtract two number
 * 
 * @param num1 
 * @param num2 
 * @param base 
 * @return std::vector<char> 
 */
std::vector<char> subtract(std::vector<char> num1, std::vector<char> num2, int base) {
    std::vector<char> res;
    int i = num1.size() - 1, j = num2.size() - 1, carry = 0;
    //std::cout << "\n\n";
    while (i >= 0 || j >= 0) {
        int a = i >= 0 ? hex_map[num1[i--]] : 0;
        int b = j >= 0 ? hex_map[num2[j--]] : 0;
        int sub = a - b - carry;
        //std::cout << a << " " << b << " " << carry << "\n";
        if (sub < 0) {
            sub += base;
            carry = 1;
        } else {
            carry = 0;
        }
        res.push_back(hex_map2[sub % base]);
    }
    //std::cout << "\n\n";
    while (res.size() > 1 && res.back() == '0') res.pop_back();
    return reverse(res);
}

/**
 * @brief multiply two numbers
 * 
 * @param num1 
 * @param num2 
 * @param base 
 * @return std::vector<char> 
 */
std::vector<char> multiply(std::vector<char> num1, std::vector<char> num2, int base) {
    std::vector<char> res(num1.size() + num2.size(), '0');
    // std::cout << res.size() << "\n";
    int i, j, carry;
    for (j = num2.size() - 1; j >= 0; j--) {
        carry = 0;
        for (i = num1.size() - 1; i >= 0; i--) {
            int a = hex_map[num2[j]];
            int b = hex_map[num1[i]];
            int mul = (hex_map[res[i + j + 1]]) + a * b + carry;
            carry = mul / base;
            res[i + j + 1] = hex_map2[mul % base];
        }
        res[j] = hex_map2[carry];
    }

    while (res[0] == '0') res.erase(res.begin());
    return res;
}

/**
 * @brief operator +
 * 
 * @tparam Base 
 * @param numero1 
 * @param numero2 
 * @return BigInt<Base> 
 */
template <size_t Base>
BigInt<Base> operator+(const BigInt<Base>& numero1, const BigInt<Base>& numero2) {
    BigInt<Base> resultado("");
    if (numero1.sign_ == 1 && numero2.sign_ == -1) {
        BigInt<Base> a1("");

        BigInt<Base> temp1(numero1);
        temp1.sign_ = 1;
        BigInt<Base> temp2(numero2);
        temp2.sign_ = 1;

        if (temp1 >= temp2) {
            a1.numero_ = subtract(numero1.numero_, numero2.numero_, Base);
            a1.sign_ = 1;
        } else {
            a1.numero_ = subtract(numero2.numero_, numero1.numero_, Base);
            a1.sign_ = -1;
        }
        return a1;
    }
    if (numero1.sign_ == -1 && numero2.sign_ == 1) {
        BigInt<Base> a1("");

        BigInt<Base> temp1(numero1);
        temp1.sign_ = 1;
        BigInt<Base> temp2(numero2);
        temp2.sign_ = 1;

        if (temp1 <= temp2) {
            a1.numero_ = subtract(numero2.numero_, numero1.numero_, Base);
            a1.sign_ = 1;
        } else {
            a1.numero_ = subtract(numero1.numero_, numero2.numero_, Base);
            a1.sign_ = -1;
        }
        return a1;
    }
    resultado.numero_ = add(numero1.numero_, numero2.numero_,Base);

    if (numero1.sign_ == -1 && numero2.sign_ == -1) {
        resultado.sign_ = -1;
    } else {
        resultado.sign_ = 1;
    }
    return resultado;
}

/**
 * @brief operator -
 * 
 * @tparam Base 
 * @param numero2 
 * @return BigInt<Base> 
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator-(const BigInt<Base> &numero2) const {
    BigInt<Base> resultado("");
    BigInt<Base> new_numero2(numero2);
    resultado = *this + (-new_numero2);
    return resultado;
}

/**
 * @brief operator - (invertir)
 * 
 * @tparam Base 
 * @return BigInt<Base> 
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator-() const {
    BigInt<Base> numero(*this);
    if (sign_ == 1) {
        numero.sign_ = -1;
    } else if (sign_ == -1) {
        numero.sign_ = 1;
    } else {
        std::cout << "invertir" << *this << " falló";
    }
    return numero;
}

/**
 * @brief operator *
 * 
 * @tparam Base 
 * @param numero2 
 * @return BigInt<Base> 
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator*(const BigInt<Base>& numero2) const {
    BigInt<Base> res("");
    res.numero_ = multiply(numero_,numero2.numero_,Base);
    res.sign_ = sign_ * numero2.sign_;
    return res;
}

/**
 * @brief operator /
 * 
 * @tparam Base 
 * @param numero1 
 * @param numero2 
 * @return BigInt<Base> 
 */
template <size_t Base>
BigInt<Base> operator/(const BigInt<Base>& numero1, const BigInt<Base>& numero2) {
    BigInt<Base> divisor(numero1);
    BigInt<Base> dividendo(numero2);
    BigInt<Base> cociente("");
    BigInt<Base> curr("");
    BigInt<Base> mayor("");
    BigInt<Base> temp("");
    BigInt<Base> zero("1");

    cociente.sign_ = divisor.sign_ * dividendo.sign_;
    dividendo.sign_ = 1;
    divisor.sign_ = 1;
    bool parar = false;
    
    curr.numero_.push_back(divisor.numero_[0]);
    divisor.numero_.erase(divisor.numero_.begin());

    while(!divisor.numero_.empty()) {
        while(curr < dividendo) {
            if (divisor.numero_.empty()) {break;}
            curr.numero_.push_back(divisor.numero_[0]);
            divisor.numero_.erase(divisor.numero_.begin());
        }

        mayor.numero_.push_back(hex_map2[Base-1]);
        while (curr < (mayor * dividendo)) {
            if (mayor == zero) {
                cociente.numero_.push_back('0');
                parar = true;
                break;
            }
            mayor--;
        }
        if (parar) break;
        cociente.numero_.push_back(mayor.numero_[0]);
        temp = mayor * dividendo;
        curr = curr - temp;
        mayor.numero_.clear();
        //std::cout << divisor << dividendo << curr << mayor << cociente << "\n\n";
        if (!curr.numero_.empty()) while (!curr.numero_.empty() && curr.numero_[0] == '0') curr.numero_.erase(curr.numero_.begin());
    }

    return cociente;
}

/**
 * @brief operator %
 * 
 * @tparam Base 
 * @param numero2 
 * @return BigInt<Base> 
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator%(const BigInt<Base>& numero2) const {
    BigInt<Base> divisor(*this);
    BigInt<Base> dividendo(numero2);
    BigInt<Base> cociente("");
    BigInt<Base> curr("");
    BigInt<Base> mayor("");
    BigInt<Base> temp("");
    BigInt<Base> zero("1");

    cociente.sign_ = divisor.sign_ * dividendo.sign_;
    dividendo.sign_ = 1;
    divisor.sign_ = 1;
    bool parar = false;
    
    curr.numero_.push_back(divisor.numero_[0]);
    divisor.numero_.erase(divisor.numero_.begin());

    while(!divisor.numero_.empty()) {
        while(curr < dividendo) {
            if (divisor.numero_.empty()) {break;}
            curr.numero_.push_back(divisor.numero_[0]);
            divisor.numero_.erase(divisor.numero_.begin());
        }

        mayor.numero_.push_back(hex_map2[Base-1]);
        while (curr < (mayor * dividendo)) {
            if (mayor == zero) {
                cociente.numero_.push_back('0');
                parar = true;
                break;
            }
            mayor--;
        }
        if (parar) break;
        cociente.numero_.push_back(mayor.numero_[0]);
        temp = mayor * dividendo;
        curr = curr - temp;
        mayor.numero_.clear();
        //std::cout << divisor << dividendo << curr << mayor << cociente << "\n\n";
        if (!curr.numero_.empty()) while (!curr.numero_.empty() && curr.numero_[0] == '0') curr.numero_.erase(curr.numero_.begin());
    }

    return curr;
}

/**
 * @brief pow two numbers
 * 
 * @tparam Base 
 * @param numero1 
 * @param numero2 
 * @return BigInt<Base> 
 */
template <size_t Base>
BigInt<Base> pow(const BigInt<Base>& numero1, const BigInt<Base>&numero2) {
    BigInt<Base> res("1");
    BigInt<Base> temp(numero2);
    BigInt<Base> zero("0");
    while (temp > zero ) {
        res = res * numero1;
        --temp;
    }
    return res;
}


#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stack>
#include <bitset>


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


std::vector<bool> C2(std::vector<bool> a) {
    if (a[0] == 0) {
        //std::cout << "postivo";
        while(!a.empty() && a[0] == 0) a.erase(a.begin());
    } else if (a[0] == 1){
        //std::cout << "negativo";
        while(!a.empty() && a[0] == 1) a.erase(a.begin());
        a.flip();
        std::reverse(a.begin(),a.end());
        for (unsigned i = 0; i < a.size(); i++ ) {
            if (a[i] == 0) {
                a[i] = 1;
                break;
            }
            if (a[i] == 1) {
                a[i] = 0;
            }
        }
        std::reverse(a.begin(),a.end());
    }
    return a;
}



std::map<char, int> hex_map = {{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, 
{'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}};

std::map<bool, int> bool_map = {{true, 1}, {false, 0}};

std::map<int, bool> bool_map2 = {{1, true}, {0, false}};

std::map<char, bool> hex_bool = {{'1', true}, {'0', false}};
std::map<bool, char> bool_hex = {{true, '1'}, {false, '0'}};

std::map<int, char> hex_map2= {{0, '0'}, {1 , '1'}, {2, '2'}, {3 , '3'}, {4 , '4'}, {5 , '5'}, 
{6, '6'}, {7, '7'}, {8, '8'}, {9, '9'}, {10, 'A'}, {11, 'B'}, {12 , 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'}};


std::vector<char> reverse(std::vector<char> num) {
    reverse(num.begin(), num.end());
    return num;
}


template <size_t Base>
class BigInt {
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

    void push_back(char i) {numero_.push_back(i);}
    void erase(std::vector<char>::iterator i) {numero_.erase(i);}
    bool empty() {return numero_.empty();}
    auto begin(void) {return numero_.begin();}
    void clear(void) {numero_.clear();}

    operator BigInt<2>();

    // getter
    std::vector<char> numero(){return numero_;}
    void snumero(std::vector<char> a){ numero_ = a;}
    void ssign(int i) { sign_ = i; }

  private:
    std::vector<char> numero_;
    int sign_;

};

template<>
class BigInt<2> {
    public:

    BigInt(std::string string);
    BigInt(std::vector<bool> v);
    BigInt(const char* );
    
    // Asignación:
    BigInt<2>& operator=(const BigInt<2>&);

    friend std::ostream& operator<<(std::ostream& out, const BigInt<2>& numero);
    // friend std::istream& operator>><Base>(std::istream& in, BigInt<Base>& numero);
    friend bool operator==<2>(const BigInt<2>& numero1, const BigInt<2> &numero2);
    bool operator!=(const BigInt<2>&) const;
    friend bool operator> <2>(const BigInt<2>& numero1, const BigInt<2> &numero2);
    bool operator>=(const BigInt<2> &) const;
    friend bool operator< <2>(const BigInt<2>& numero1, const BigInt<2> &numero2);
    bool operator<=(const BigInt<2> &) const;

    // Incremento/decremento:
    BigInt<2>& operator++(); // Pre-incremento
    BigInt<2> operator++(int); // Post-incremento
    BigInt<2>& operator--(); // Pre-decremento
    BigInt<2> operator--(int); // Post-decremento

    friend BigInt<2> operator+<2>(const BigInt<2>& numero1, const BigInt<2>& numero2);
    BigInt<2> operator-(const BigInt<2> &) const;
    BigInt<2> operator-() const;
    BigInt<2> operator*(const BigInt<2>&) const;
    friend BigInt<2> operator/<2>(const BigInt<2>& numero1, const BigInt<2>& numero2);
    BigInt<2> operator%(const BigInt<2>&) const;
    // Potencia a^b
    friend BigInt<2> pow<2>(const BigInt<2>& numero1, const BigInt<2>& numero2);
    
    size_t sizeOFnumero() {
        size_t sum = 0;    
        for (int i = 0; i < vbool_.size();i++) {
            sum += sizeof(vbool_[i]);
        }
        return sum;
    }
    operator BigInt<8>();
    operator BigInt<10>();
    operator BigInt<16>();

    bool operator[](int) const; // Acceso al i-ésimo dígito
    void set(int pos, bool val) { vbool_[pos] = val; }
    void reverse() { std::reverse(vbool_.begin(),vbool_.end()); }
    void flip() { vbool_.flip(); }
    void push_back(bool bit) { vbool_.push_back(bit);}
    int size() {return vbool_.size(); }
    std::vector<bool> vbool() const { return vbool_;}

    void push_back(char i) {vbool_.push_back(i);}
    void erase(std::vector<bool>::iterator i) {vbool_.erase(i);}
    bool empty() {return vbool_.empty();}
    auto begin(void) {return vbool_.begin();}
    void clear(void) {vbool_.clear();}

    private:
        std::vector<bool> vbool_;
};


BigInt<2>::operator BigInt<10>() {
    std::vector<bool> binario = vbool_;
    BigInt<10> sum("0");
    bool negativo = false ;
    while (binario[0] == true) {
        binario.erase(binario.begin());
        negativo = true;
    }
    if (negativo) { 
        binario.flip();
    }
    BigInt<10> result("");
    BigInt<10> iterator("0");
    BigInt<10> two("2");
    std::reverse(binario.begin(),binario.end());
    if(negativo) {
        for(int i = 0 ; i < binario.size(); i++) {
            if (binario[i] == false) {
                binario[i] = true;
                break;
            } else {
                binario[i] = false;
            }

        }
    }
    for(int i = 0 ; i < binario.size(); i++) {
        if (binario[i] == true){
            sum = sum + pow(two,iterator);
            //std::cout << sum;
        }
        iterator++;
    }
    //sum.sign();
    if (negativo) { sum.ssign(-1); }
    return sum;
}

BigInt<2>::operator BigInt<8>() {

    std::vector<bool> binario = vbool_;
    BigInt<10> sum("0");
    bool negativo = false ;
    while (binario[0] == true) {
        binario.erase(binario.begin());
        negativo = true;
    }
    if (negativo) { 
        binario.flip();
    }
    BigInt<10> result("");
    BigInt<10> iterator("0");
    BigInt<10> two("2");
    std::reverse(binario.begin(),binario.end());
    if(negativo) {
        for(int i = 0 ; i < binario.size(); i++) {
            if (binario[i] == false) {
                binario[i] = true;
                break;
            } else {
                binario[i] = false;
            }

        }
    }
    for(int i = 0 ; i < binario.size(); i++) {
        if (binario[i] == true){
            sum = sum + pow(two,iterator);
            //std::cout << sum;
        }
        iterator++;
    }
    if (negativo) { sum.ssign(-1); }

    BigInt<10> divisor("");
    divisor = sum;
    BigInt<10> dividendo("8");
    BigInt<10> resto("");
    BigInt<10> zero("0");
    std::vector<char> c;

    while (divisor != zero) {
        resto = divisor % dividendo;
        divisor = divisor / dividendo;
        if (!resto.empty())c.push_back(resto.numero()[0]);
        if (resto.empty())c.push_back('0');
    }

    BigInt<8> res("");
    std::reverse(c.begin(),c.end());
    res.snumero(c);
    res.ssign(sum.sign());
    return res;

}
BigInt<2>::operator BigInt<16>() {

    std::vector<bool> binario = vbool_;
    BigInt<10> sum("0");
    bool negativo = false ;
    while (binario[0] == true) {
        binario.erase(binario.begin());
        negativo = true;
    }
    if (negativo) { 
        binario.flip();
    }
    BigInt<10> result("");
    BigInt<10> iterator("0");
    BigInt<10> two("2");
    std::reverse(binario.begin(),binario.end());
    if(negativo) {
        for(int i = 0 ; i < binario.size(); i++) {
            if (binario[i] == false) {
                binario[i] = true;
                break;
            } else {
                binario[i] = false;
            }

        }
    }
    for(int i = 0 ; i < binario.size(); i++) {
        if (binario[i] == true){
            sum = sum + pow(two,iterator);
            //std::cout << sum;
        }
        iterator++;
    }
    if (negativo) { sum.ssign(-1); }

    BigInt<10> divisor("");
    divisor = sum;
    BigInt<10> dividendo("16");
    BigInt<10> resto("");
    BigInt<10> zero("0");
    std::vector<char> c;

    while (divisor != zero) {
        resto = divisor % dividendo;
        divisor = divisor / dividendo;
        // std::cout << resto;
        if (!resto.empty()) {
            if (resto.numero().size() > 1) {
                int i = hex_map[resto.numero()[0]] * 10 + hex_map[resto.numero()[1]];
                c.push_back(hex_map2[i]);
            }else {
                c.push_back(resto.numero()[0]);
            }
        }
        if (resto.empty())c.push_back('0');
    }

    BigInt<16> res("");
    std::reverse(c.begin(),c.end());
    res.snumero(c);
    res.ssign(sum.sign());
    return res;

}


template <size_t Base>
BigInt<Base>::operator BigInt<2>() {
    BigInt<2> result("");
    if (Base == 16){
        // Lookup table for converting each digit to its binary representation.
        const std::vector<std::vector<bool>> lookup_table = {
            {0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}, {0, 0, 1, 1},
            {0, 1, 0, 0}, {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1},
            {1, 0, 0, 0}, {1, 0, 0, 1}, {1, 0, 1, 0}, {1, 0, 1, 1},
            {1, 1, 0, 0}, {1, 1, 0, 1}, {1, 1, 1, 0}, {1, 1, 1, 1}
        };

        std::vector<bool> temp_result;
        for (size_t i = 0; i < numero_.size(); ++i) {
            size_t digit = hex_map[numero_.at(i)];
            std::vector<bool> binary_digit = lookup_table[digit];

            // Append the binary representation of the current digit to the temporary result.
            for (bool bit : binary_digit) {
                temp_result.push_back(bit);
            }
        }

        // Pad the temporary vector with zeros on the left.
        size_t bits_per_digit = log2(Base);
        size_t padding_size = (bits_per_digit - temp_result.size() % bits_per_digit) % bits_per_digit;
        for (size_t i = 0; i < padding_size; ++i) {
            temp_result.insert(temp_result.begin(), false);
        }

        // Concatenate the bits in the temporary vector to form the final result.
        for (bool bit : temp_result) {
            result.push_back(bit);
        }
    } else 
    if (Base == 10) {
        std::vector<bool> binaryNum;
        BigInt<Base> op1(*this);
        bool signo = false;
        BigInt<Base> op2("2");
        BigInt<Base> resto("");
        BigInt<Base> uno("1");
        // if (op1.numero_[0] == '-') op1.numero_.erase(op1.numero_.begin());
        //std::cout << op1.numero_[0] << "\n"<< "\n"<< "\n"<< "\n";
        if (op1.sign() == -1) {
            op1.sign_ = 1;
            signo = true;
        }
        bool continuar = true;
        while (continuar) {
            resto = op1 % op2;
            //std::cout << op1 << resto << " ^ \n";
            op1 = op1 / op2;
            //std::cout << op2;
            if (resto == uno) {
                result.push_back(true);
            } else { 
                result.push_back(false);
            }
            //std::cout << op1 << op2  <<"\n\n"  ;
            if (op1 < op2){
                continuar = false;
            }
        }

        if (signo) {
            op1.sign_ = -1;
            signo = false;
        }
        resto = op1 % op2;
        //std::cout << op1 << resto << " ";
        op1 = op1 / op2;
        if (resto == uno) {
            result.push_back(true);
        } else { 
            result.push_back(false);
        }

        result.reverse();
    } else
    if (Base == 8) {
        std::vector<bool> binaryNum;
        std::string binaryString = "";
        std::vector<char> octalNum = numero_;
        // Step 1: Convert each digit to binary and concatenate the results
        for (int i = 0; i < octalNum.size(); i++) {
            int decimalNum = octalNum[i] - '0';
            std::string binaryDigit = "";
            
            while (decimalNum > 0) {
                int remainder = decimalNum % 2;
                binaryDigit = std::to_string(remainder) + binaryDigit;
                decimalNum /= 2;
            }
            
            // Pad binary digit with leading zeros to make it 3 bits
            while (binaryDigit.length() < 3) {
                binaryDigit = "0" + binaryDigit;
            }
            
            binaryString += binaryDigit;
        }
        
        // Step 2: Create bool vector and set each element based on binary string
        for (int i = 0; i < binaryString.length(); i++) {
            result.push_back(binaryString[i] == '1');
        }
        
    }else {
        std::cout << "ni sentido";
    }

    if (sign_ == 1) {
        //std::cout << "postivo";
        result.reverse();
        result.push_back(false);
        result.reverse();
    } else if (sign_ == -1){
        //std::cout << "negativo";
        result.flip();
        result.reverse();
        for (unsigned i = 0; i < result.size(); i++ ) {
            if (result[i] == 0) {
                result.set(i,1);
                break;
            }
            if (result[i] == 1) {
                result.set(i,0);
            }
        }
        result.push_back(true);
        result.reverse();
    }
    return result;
}



/**
 * @brief Construct a new Big Int< Base>:: Big Int object
 * 
 * @tparam Base 
 * @param string 
 */
BigInt<2>::BigInt( std::string string) {
    for (int i = 0; i < string.length(); i++) {

        if (string[i] == '1'){
            vbool_.push_back(true);
        } else {
            vbool_.push_back(false);
        }
    }
}
/**
 * @brief Construct a new Big Int< Base>:: Big Int object
 * 
 * @tparam Base 
 * @param string 
 */
BigInt<2>::BigInt( std::vector<bool> a) {
    vbool_ = a;
}

/**
 * @brief operator <<
 * 
 * @param out 
 * @param numero 
 * @return * template <size_t Base>& 
 */
std::ostream& operator<<(std::ostream& out, const BigInt<2>& numero) {

    for (int i  = 0;  i < numero.vbool_.size(); i++) {
        out << numero.vbool_[i]<< "";
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
 * @brief operator[]
 * 
 * @tparam Base 
 * @param i 
 * @return char 
 */
bool BigInt<2>::operator[](int i) const {
    return vbool_[i];
} 


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
    int i;
    if (string[0] == '-') {
        sign_ = -1;
        i = 1;
    } else {
        sign_ = 1;
        i = 0;
    }
    for (; i < string.length(); i++) {
        numero_.push_back(string[i]);
    }
}
/**
 * @brief Construct a new Big Int< Base>:: Big Int object
 * 
 * @tparam Base 
 * @param caracters 
 */
BigInt<2>::BigInt(const char* caracters) {
    std::string string(caracters);
    for (int i = 0; i < string.length(); i++) {

        if (string[i] == '1'){
            vbool_.push_back(true);
        } else {
            vbool_.push_back(false);
        }
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
 * @brief operator =
 * 
 * @tparam Base 
 * @param numero 
 * @return BigInt<Base>& 
 */
BigInt<2>& BigInt<2>::operator=(const BigInt<2>& numero) {
    vbool_ = numero.vbool_;
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
        out << numero.numero_[i]<< "";
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
 * @brief operator ==
 * 
 * @tparam Base 
 * @param numero1 
 * @param numero2 
 * @return true 
 * @return false 
 */
bool operator==(const BigInt<2>& numero1, const BigInt<2> &numero2) {
    return numero1.vbool() == numero2.vbool();
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
 * @brief operator !=
 * 
 * @tparam Base 
 * @param numero2 
 * @return true 
 * @return false 
 */
bool BigInt<2>::operator!=(const BigInt<2>& numero2) const {
    return !(*this == numero2);
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
 * @brief operator >
 * 
 * @tparam Base 
 * @param numero1 
 * @param numero2 
 * @return true 
 * @return false 
 */
bool operator>(const BigInt<2>& numero1, const BigInt<2> &numero2) {

    if (numero1[0] == 0 && numero2[0] == 1) return true;
    if (numero1[0] == 1 && numero2[0] == 0) return false;

    std::vector<bool> n1 = C2(numero1.vbool());
    std::vector<bool> n2 = C2(numero2.vbool());

    auto size_num1 = n1.size();
    auto size_num2 = n2.size();

    if (size_num1 > size_num2){ 
        return true;
    } else if (size_num1 < size_num2) {
        return false;
    } else {
        // si son igual size
        for (unsigned i = 0 ; i < size_num1; i++) {
            if (n1[i] == 1 && n2[i] == 0) return true;
            if (n1[i] == 0 && n2[i] == 1) return false;
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
 * @brief operator <
 * 
 * @tparam Base 
 * @param numero1 
 * @param numero2 
 * @return true 
 * @return false 
 */
bool operator<(const BigInt<2>& numero2, const BigInt<2> &numero1) {

    if (numero1[0] == 0 && numero2[0] == 1) return true;
    if (numero1[0] == 1 && numero2[0] == 0) return false;

    std::vector<bool> n1 = C2(numero1.vbool());
    std::vector<bool> n2 = C2(numero2.vbool());
    auto size_num1 = n1.size();
    auto size_num2 = n2.size();

    if (size_num1 > size_num2){ 
        return true;
    } else if (size_num1 < size_num2) {
        return false;
    } else {
        // si son igual size
        for (unsigned i = 0 ; i < size_num1; i++) {
            if (n1[i] == 1 && n2[i] == 0) return true;
            if (n1[i] == 0 && n2[i] == 1) return false;
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
 * @brief operator <=
 * 
 * @tparam Base 
 * @param numero2 
 * @return true 
 * @return false 
 */
bool BigInt<2>::operator<=(const BigInt<2> &numero2) const {
    return !(*this > numero2);
}
bool BigInt<2>::operator>=(const BigInt<2> &numero2) const {
    return !(*this < numero2);
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
 * @brief operator +
 * 
 * @tparam Base 
 * @param numero1 
 * @param numero2 
 * @return BigInt<Base> 
 */
BigInt<2> operator+(const BigInt<2>& numero1, const BigInt<2>& numero2) {
    //std::cout << numero1 << numero2;
    bool neg1 = false;
    bool neg2 = false;
    std::vector<bool> a = numero1.vbool();
    std::vector<bool> b = numero2.vbool();
    if (a[0] == true) neg1 = true;
    if (b[0] == true) neg2 = true;
    int max = std::max(a.size(), b.size());
    while (max != a.size()) a.insert(a.begin(),a[0]);
    while (max != b.size()) b.insert(b.begin(),b[0]);
    std::reverse(a.begin(),a.end());
    std::reverse(b.begin(),b.end());

    std::vector<bool> res;
    int carry = 0;
    int resultado;
    for (int i = 0; i < max; i++) {
        resultado = bool_map[a[i]] + bool_map[b[i]] + carry;
        //std::cout << resultado<< "= " << bool_map[a[i]]<< " + " << bool_map[b[i]]<< " + " << carry << "\n";
        if (resultado == 1) {
            carry = 0;
            resultado = 1;
        } else if (resultado == 2) {
            carry = 1;
            resultado = 0;
        } else if (resultado == 3) {
            carry = 1;
            resultado = 1;
        } else if (resultado == 0) {
            carry = 0;
            resultado = 0;
        }
        res.push_back(bool_map2[resultado]);
    }
    //if (neg2 == true && neg1 == true) res.push_back(bool_map2[1]);
    std::reverse(res.begin(),res.end());
    return res;
}

/**
 * @brief operator -
 * 
 * @tparam Base 
 * @param numero2 
 * @return BigInt<Base> 
 */
BigInt<2> BigInt<2>::operator-(const BigInt<2> &numero2) const {
    BigInt<2> resultado("");
    BigInt<2> new_numero2(numero2);
    resultado = *this + (-new_numero2);
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
 * @brief operator - (invertir)
 * 
 * @tparam Base 
 * @return BigInt<Base> 
 */
BigInt<2> BigInt<2>::operator-() const {
    BigInt<2> numero(*this);
    std::vector<bool> a = numero.vbool();
    if (a[0] == 0) {
        //std::cout << "negativo";
        while(!a.empty() && a[0] == 0) a.erase(a.begin());
        a.flip();
        std::reverse(a.begin(),a.end());
        for (unsigned i = 0; i < a.size(); i++ ) {
            if (a[i] == 0) {
                a[i] = 1;
                break;
            }
            if (a[i] == 1) {
                a[i] = 0;
            }
        }
        std::reverse(a.begin(),a.end());
        a.insert(a.begin(),true);
    } else if (a[0] == 1){
        //std::cout << "negativo";
        while(!a.empty() && a[0] == 1) a.erase(a.begin());
        a.flip();
        std::reverse(a.begin(),a.end());
        for (unsigned i = 0; i < a.size(); i++ ) {
            if (a[i] == 0) {
                a[i] = 1;
                break;
            }
            if (a[i] == 1) {
                a[i] = 0;
            }
        }
        std::reverse(a.begin(),a.end());
        a.insert(a.begin(),false);
    }
    return a;
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
 * @brief operator *
 * 
 * @tparam Base 
 * @param numero2 
 * @return BigInt<Base> 
 */
BigInt<2> BigInt<2>::operator*(const BigInt<2>& numero2) const {
    std::vector<bool> num1_bool = this->vbool();
    std::vector<bool> num2_bool = numero2.vbool();
    //std::cout << *this << numero2<< "\n";
    bool neg1 = false;
    bool neg2 = false;
    if (num1_bool[0] == true) neg1 = true;
    if (num2_bool[0] == true) neg2 = true;
    num1_bool = C2(num1_bool);
    num2_bool = C2(num2_bool);
    // std::reverse(num1.begin(),num1.end());
    // std::reverse(num2.begin(),num2.end());


    int base = 2;
    std::vector<char> num1;
    std::vector<char> num2;
    for (auto a : num1_bool) num1.push_back(bool_hex[a]);
    for (auto a : num2_bool) num2.push_back(bool_hex[a]);



    std::vector<char> res(num1.size() + num2.size(), '0');
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

    //std::cout << res.size() << "\n";
    std::vector<bool> resultado;
    for (auto a : res) resultado.push_back(hex_bool[a]);
    std::reverse(resultado.begin(),resultado.end());
    if (neg1 == neg2 )resultado.push_back(false);
    if (neg1 != neg2 ){
        //std::cout << "negativo";
        resultado.flip();
        resultado.push_back(true);
        for (unsigned i = 0; i < resultado.size(); i++ ) {
            if (resultado[i] == 0) {
                resultado[i] = 1;
                break;
            }
            if (resultado[i] == 1) {
                resultado[i] = 0;
            }
        }
    }
    std::reverse(resultado.begin(),resultado.end());
    return resultado;
}

/**
 * @brief operator /
 * 
 * @tparam Base 
 * @param numero1 
 * @param numero2 
 * @return BigInt<Base> 
 */
BigInt<2> operator/(const BigInt<2>& numero1, const BigInt<2>& numero2) {

    BigInt<2> divisor(numero1);
    BigInt<2> dividendo(numero2);
    BigInt<10> op1 = divisor;
    BigInt<10> op2 = dividendo;
    BigInt<10> res("");
    res = op1 / op2;
    BigInt<2> cociente = res;
    return cociente;

    // BigInt<2> cociente("");
    BigInt<2> curr("");
    BigInt<2> mayor("");
    BigInt<2> temp("");
    BigInt<2> zero("1");
    bool parar = false;
    
    std::cout << "ello";
    curr.push_back(divisor[0]);
    divisor.erase(divisor.begin());
    do {
        int i = 0;
        if (!curr.empty()) while (!curr.empty() && curr[0] == '0') curr.erase(curr.begin());
        while(curr < dividendo) {
            if (i != 0 && !divisor.empty()){ 
                cociente.push_back('0');
                i = 0;
            } else {
                i++;
            }
            if (divisor.empty()) {break;}
            curr.push_back(divisor[0]);
            divisor.erase(divisor.begin());

        }

        if (!curr.empty()) while (!curr.empty() && curr[0] == '0') curr.erase(curr.begin());
        mayor.push_back(hex_map2[1]);
        while (curr < (mayor * dividendo)) {
            if (mayor == zero) {
                cociente.push_back('0');
                parar = true;
                break;
            }
            mayor--;
        }
        //std::cout << curr << mayor<< cociente << "\n";
        if (parar) break;
        cociente.push_back(mayor[0]);
        temp = mayor * dividendo;
        curr = curr - temp;
        mayor.clear();
        //std::cout << "resto" << curr;
        //std::cout << divisor << dividendo << curr << mayor << cociente << "\n\n";
        if (!curr.empty()) while (!curr.empty() && curr[0] == '0') curr.erase(curr.begin());
    }while(!divisor.empty()) ;
    return cociente;
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
    BigInt<Base> a("0");
    cociente.sign_ = divisor.sign_ * dividendo.sign_;
    dividendo.sign_ = 1;
    divisor.sign_ = 1;
    bool parar = false;
    curr.numero_.push_back(divisor.numero_[0]);
    divisor.numero_.erase(divisor.numero_.begin());

    do {
        int i = 0;
        if (!curr.numero_.empty()) while (!curr.numero_.empty() && curr.numero_[0] == '0') curr.numero_.erase(curr.numero_.begin());
        while(curr < dividendo) {
            if (!curr.numero_.empty()) while (!curr.numero_.empty() && curr.numero_[0] == '0') curr.numero_.erase(curr.numero_.begin());
            if (i != 0 && !divisor.numero_.empty()){ 
                cociente.numero_.push_back('0');
                i = 0;
                //if (curr < dividendo) i++;
            } else {
                i++;
            }
            if (divisor.numero_.empty()) {break;}
            curr.numero_.push_back(divisor.numero_[0]);
            divisor.numero_.erase(divisor.numero_.begin());
            //if((curr < dividendo)){i++;continue;}

        }

        mayor.numero_.push_back(hex_map2[Base-1]);
        if (!curr.numero_.empty()) while (!curr.numero_.empty() && curr.numero_[0] == '0') curr.numero_.erase(curr.numero_.begin());
        while (curr < (mayor * dividendo)) {
            if (mayor == zero) {
                cociente.numero_.push_back('0');
                parar = true;
                break;
            }
            mayor--;
        }
        //std::cout << curr << mayor<< cociente << "\n";
        //if (parar && !divisor.empty()) {parar= false;continue;}
        // std::cout <<"div1 " << divisor  <<"div2 "<< dividendo <<"curr " << curr  <<"amyor "<< mayor <<"coci " << cociente << "PARAR->" << parar << "] " << "^\n\n";
        if (parar) break;
        cociente.numero_.push_back(mayor.numero_[0]);
        temp = mayor * dividendo;
        curr = curr - temp;
        mayor.numero_.clear();
        //std::cout << "resto" << curr;
        if (!curr.numero_.empty()) while (!curr.numero_.empty() && curr.numero_[0] == '0') curr.numero_.erase(curr.numero_.begin());
    }while(!divisor.numero_.empty());
  

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

    do {
        int i = 0;
        if (!curr.numero_.empty()) while (!curr.numero_.empty() && curr.numero_[0] == '0') curr.numero_.erase(curr.numero_.begin());
        while(curr < dividendo) {
            if (i != 0 && !divisor.numero_.empty()){ 
                cociente.numero_.push_back('0');
                i = 0;
            } else {
                i++;
            }
            if (divisor.numero_.empty()) {break;}
            curr.numero_.push_back(divisor.numero_[0]);
            divisor.numero_.erase(divisor.numero_.begin());

        }

        if (!curr.numero_.empty()) while (!curr.numero_.empty() && curr.numero_[0] == '0') curr.numero_.erase(curr.numero_.begin());
        mayor.numero_.push_back(hex_map2[Base-1]);
        while (curr < (mayor * dividendo)) {
            if (mayor == zero) {
                cociente.numero_.push_back('0');
                parar = true;
                break;
            }
            mayor--;
        }
        //std::cout << curr << mayor<< cociente << "\n";
        if (parar) break;
        cociente.numero_.push_back(mayor.numero_[0]);
        temp = mayor * dividendo;
        curr = curr - temp;
        mayor.numero_.clear();
        //std::cout << divisor << dividendo << curr << mayor << cociente << "\n\n";
        if (!curr.numero_.empty()) while (!curr.numero_.empty() && curr.numero_[0] == '0') curr.numero_.erase(curr.numero_.begin());
    }while(!divisor.numero_.empty()) ;

    return curr;
}

/**
 * @brief operator %
 * 
 * @tparam Base 
 * @param numero2 
 * @return BigInt<Base> 
 */
BigInt<2> BigInt<2>::operator%(const BigInt<2>& numero2) const {
 
    BigInt<2> divisor(*this);
    BigInt<2> dividendo(numero2);
    BigInt<10> op1 = divisor;
    BigInt<10> op2 = dividendo;
    BigInt<10> res("");
    res = op1 / op2;
    BigInt<2> resto = res;
    return resto;

    BigInt<2> cociente("");
    BigInt<2> curr("");
    BigInt<2> mayor("");
    BigInt<2> temp("");
    BigInt<2> zero("1");
    bool parar = false;
    
    std::cout << "ello";
    curr.push_back(divisor[0]);
    divisor.erase(divisor.begin());
    do {
        int i = 0;
        if (!curr.empty()) while (!curr.empty() && curr[0] == '0') curr.erase(curr.begin());
        while(curr < dividendo) {
            if (i != 0 && !divisor.empty()){ 
                cociente.push_back('0');
                i = 0;
            } else {
                i++;
            }
            if (divisor.empty()) {break;}
            curr.push_back(divisor[0]);
            divisor.erase(divisor.begin());

        }
        if (!curr.empty()) while (!curr.empty() && curr[0] == '0') curr.erase(curr.begin());
        mayor.push_back(hex_map2[1]);
        while (curr < (mayor * dividendo)) {
            if (mayor == zero) {
                cociente.push_back('0');
                parar = true;
                break;
            }
            mayor--;
        }
        //std::cout << curr << mayor<< cociente << "\n";
        if (parar) break;
        cociente.push_back(mayor[0]);
        temp = mayor * dividendo;
        curr = curr - temp;
        mayor.clear();
        //std::cout << "resto" << curr;
        //std::cout << divisor << dividendo << curr << mayor << cociente << "\n\n";
        if (!curr.empty()) while (!curr.empty() && curr[0] == '0') curr.erase(curr.begin());
    }while(!divisor.empty()) ;
    return cociente;
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

/**
 * @brief pow two numbers
 * 
 * @tparam Base 
 * @param numero1 
 * @param numero2 
 * @return BigInt<Base> 
 */
BigInt<2> pow(const BigInt<2>& numero1, const BigInt<2>&numero2) {
    BigInt<2> res("01");
    BigInt<2> temp(numero2);
    temp++;
    BigInt<2> uno("01");
    while (temp > uno ) {
        res = res * numero1;
        --temp;
    }
    return res;
}



/**
 * @brief operaator++
 * 
 * @tparam Base 
 * @return BigInt<Base>& 
 */
BigInt<2>& BigInt<2>::operator++() {
    BigInt<2> aux{"01"};
    *this = *this + aux;
    return *this;
}

/**
 * @brief  ++operator
 * 
 * @tparam Base 
 * @return BigInt<Base> 
 */
BigInt<2> BigInt<2>::operator++(int) {
    BigInt<2> aux{*this};
    ++(*this);
    return aux;
}

/**
 * @brief operator --
 * 
 * @tparam Base 
 * @return BigInt<Base>& 
 */
BigInt<2>& BigInt<2>::operator--() {
    BigInt<2> aux{"01"};
    *this = *this - aux;
    return *this;
}

/**
 * @brief operator --
 * 
 * @tparam Base 
 * @return BigInt<Base> 
 */
BigInt<2> BigInt<2>::operator--(int) {
    BigInt<2> aux{*this};
    --(*this);
    return aux;
}